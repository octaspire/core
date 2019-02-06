/******************************************************************************
Octaspire Core - Containers and other utility libraries in standard C99
Copyright 2017 www.octaspire.com

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
******************************************************************************/
#include "octaspire/core/octaspire_string.h"
#include <assert.h>
#include <limits.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "external/jenkins_one_at_a_time.h"
#include "octaspire/core/octaspire_memory.h"
#include "octaspire/core/octaspire_utf8.h"
#include "octaspire/core/octaspire_helpers.h"

struct octaspire_string_t
{
    octaspire_vector_t                   *octets;
    octaspire_vector_t                   *ucsCharacters;
    octaspire_allocator_t                          *allocator;
    size_t                                          errorAtOctet;
    octaspire_string_error_status_t  errorStatus;
};

static char const octaspire_string_private_null_octet = '\0';


// Prototypes for private functions /////////////////////////////////////////
static bool octaspire_string_private_check_substring_match_at(
    octaspire_string_t const * const self,
    size_t const startFromIndex,
    octaspire_string_t const * const substring);

static bool octaspire_string_private_is_string_at_index(
    octaspire_string_t const * const self,
    size_t const selfIndex,
    octaspire_string_t const * const str,
    size_t const strFirstIndex,
    size_t const strLastIndex);

static bool octaspire_string_private_ensure_octets_are_up_to_date(
    octaspire_string_t const * const self);

//////////////////////////////////////////////////////////////////////////////


octaspire_string_t *octaspire_string_new(
    char const * const str,
    octaspire_allocator_t *allocator)
{
    return octaspire_string_new_from_buffer(
        str,
        str ? strlen(str) : 0,
        allocator);
}

octaspire_string_t *octaspire_string_new_from_buffer(
    char const * const buffer,
    size_t const lengthInOctets,
    octaspire_allocator_t *allocator)
{
    octaspire_string_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_string_t));

    if (!self)
    {
        return 0;
    }

    self->allocator        = allocator;

    // We cannot know how many actual UCS characters there are in buffer, because
    // characters can be encoded between one and four octets. To speed up allocation,
    // without allocating too much space, we preallocate lengthInOctets / 4 characters.
    self->ucsCharacters    = octaspire_vector_new_with_preallocated_elements(
        sizeof(uint32_t),
        false,
        lengthInOctets / 4,
        0,
        self->allocator);

    if (!self->ucsCharacters)
    {
        octaspire_string_release(self);
        self = 0;
        return 0;
    }

    self->errorStatus  = OCTASPIRE_STRING_ERROR_STATUS_OK;

    self->octets = octaspire_vector_new(
        sizeof(char),
        false,
        0,
        self->allocator);

    self->errorAtOctet = 0;

    if (buffer && lengthInOctets)
    {
        size_t index = 0;
        uint32_t ucsChar = 0;
        int numOctets = 0;
        while (index < lengthInOctets)
        {
            // TODO XXX is (lengthInOctets - index) correct?
            octaspire_utf8_decode_status_t const status = octaspire_utf8_decode_character(
                buffer + index,
                (lengthInOctets - index),
                &ucsChar,
                &numOctets);

            if (status != OCTASPIRE_UTF8_DECODE_STATUS_OK)
            {
                self->errorStatus  = OCTASPIRE_STRING_ERROR_STATUS_DECODING_ERROR;
                self->errorAtOctet = index;
                break;
            }

            if (numOctets > 0)
            {
                if (!octaspire_vector_push_back_element(self->ucsCharacters, &ucsChar))
                {
                    octaspire_string_release(self);
                    self = 0;
                    return 0;
                }

                index += (size_t)numOctets;
            }
        }
    }

    return self;
}

octaspire_string_t *octaspire_string_new_format(
    octaspire_allocator_t *allocator,
    char const * const fmt,
    ...)
{
    va_list arguments;
    va_start(arguments, fmt);

    octaspire_string_t *result =
        octaspire_string_new_vformat(allocator, fmt, arguments);

    va_end(arguments);

    return result;
}

octaspire_string_t *octaspire_string_new_vformat(
    octaspire_allocator_t *allocator,
    char const * const fmt,
    va_list arguments)
{
    va_list copyOfVarArgs;
    va_copy(copyOfVarArgs, arguments);

    octaspire_string_error_status_t errorStatus =
        OCTASPIRE_STRING_ERROR_STATUS_OK;

    size_t                                         errorAtOctet = 0;

    octaspire_string_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_string_t));

    if (!self)
    {
        va_end(copyOfVarArgs);
        return self;
    }

    self->allocator        = allocator;

    assert(self->allocator);

    self->octets = octaspire_vector_new(
        sizeof(char),
        false,
        0,
        self->allocator);

    self->ucsCharacters     = octaspire_vector_new(sizeof(uint32_t), false, 0, self->allocator);

    octaspire_string_reset_error_status(self);

    size_t buflen = 8;
    char *buffer = octaspire_allocator_malloc(allocator, buflen);
    assert(buffer);

    octaspire_vector_t *vec2 = octaspire_vector_new(
        sizeof(char),
        false,
        0,
        allocator);

    assert(vec2);

    int negativeResultCounter = -1;

    bool firstRound = true;
    while (true)
    {
        if (negativeResultCounter > 1000)
        {
            errorStatus = OCTASPIRE_STRING_ERROR_STATUS_ENCODING_ERROR;
            // TODO XXX what octet index to put here? Negative index, or just unused on this error type?
            errorAtOctet = 0;
            break;
        }

        int n = 0;

        if (firstRound)
        {
            firstRound = false;
        }
        else
        {
            va_copy(copyOfVarArgs, arguments);
        }

#ifdef OCTASPIRE_CLANG_PRAGMAS_ENABLED
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-nonliteral"
#endif

    #ifdef OCTASPIRE_PLAN9_IMPLEMENTATION
        n = vsnprintf(
            buffer,
            buflen - 1,
            fmt,
            copyOfVarArgs);
    #else
        n = vsnprintf(
            buffer,
            buflen,
            fmt,
            copyOfVarArgs);
    #endif

#ifdef OCTASPIRE_CLANG_PRAGMAS_ENABLED
#pragma clang diagnostic pop
#endif

        va_end(copyOfVarArgs);

        if (n < 0)
        {
            // Encoding error in C99 or, on older glibc, the output was truncated.
            // Try again with more space. Because we don't know how much
            // space is required, lets double it (and make sure that the length is not zero).
            // Because we don't know is the reason for failure an encoding error or missing space,
            // we will start counting to prevent looping forever.
            ++negativeResultCounter;

            buflen *= 2;
            char *tmpPtr = octaspire_allocator_realloc(allocator, buffer, buflen);
            //char *tmpPtr = realloc(buffer, buflen);

            if (tmpPtr)
            {
                buffer = tmpPtr;
                memset(buffer, 0, buflen);
            }
            else
            {
                octaspire_allocator_free(allocator, buffer);
                buffer = 0;
                return 0;
            }
        }
        else if ((size_t)n >= buflen)
        {
            // TODO calculate exact size

            buflen *= 2;
            char *tmpPtr = octaspire_allocator_realloc(allocator, buffer, buflen);
            //char *tmpPtr = realloc(buffer, buflen);

            if (tmpPtr)
            {
                buffer = tmpPtr;
                memset(buffer, 0, buflen);
            }
            else
            {
                octaspire_allocator_free(allocator, buffer);
                buffer = 0;
                return 0;
            }
        }
        else if (n > 0)
        {
            assert((size_t)n < buflen);
            // Success
            for (size_t i = 0; i < (size_t)n; ++i)
            {
                char const c = buffer[i];

                octaspire_vector_push_back_element(vec2, &c);
            }

            if (!octaspire_vector_push_back_char(
                    vec2,
                    octaspire_string_private_null_octet))
            {
                abort();
            }

            break;
        }
        else
        {
            // Empty string
            break;
            //assert(false);
        }
    }

    //assert(!octaspire_vector_is_empty(vec2));

    if (!octaspire_vector_push_back_char(vec2, octaspire_string_private_null_octet))
    {
        abort();
    }

    octaspire_string_t *tmpStr = octaspire_string_new(
        octaspire_vector_get_element_at(vec2, 0),
        allocator);

    octaspire_string_release(self);
    self = tmpStr;

    assert(self);

    if (!octaspire_string_is_error(self))
    {
        if (errorStatus != OCTASPIRE_STRING_ERROR_STATUS_OK)
        {
            self->errorStatus  = errorStatus;
            self->errorAtOctet = errorAtOctet;
        }
    }

    octaspire_allocator_free(allocator, buffer);
    buffer = 0;

    octaspire_vector_release(vec2);
    vec2 = 0;

    return self;
}

octaspire_string_t *octaspire_string_new_copy(
    octaspire_string_t const * const other,
    octaspire_allocator_t *allocator)
{
    octaspire_string_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_string_t));

    if (!self)
    {
        return self;
    }

    self->octets            = octaspire_vector_new_shallow_copy(other->octets, allocator);

    self->ucsCharacters     = octaspire_vector_new_shallow_copy(other->ucsCharacters, allocator);
    self->errorStatus       = other->errorStatus;
    self->errorAtOctet      = other->errorAtOctet;
    self->allocator         = allocator;

    return self;
}

octaspire_string_t *octaspire_string_new_substring_from_given_index_and_length(
    octaspire_string_t const * const other,
    octaspire_allocator_t *allocator,
    size_t const ucsCharStartIndex,
    size_t const lengthInUcsChars)
{
    assert(other);
    assert(allocator);

    size_t const endIndex = ucsCharStartIndex + lengthInUcsChars;

    if (endIndex >= octaspire_string_get_length_in_ucs_characters(other))
    {
        return 0;
    }

    octaspire_string_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_string_t));

    if (!self)
    {
        return self;
    }

    self->allocator         = allocator;

    self->octets = octaspire_vector_new(
        sizeof(char),
        false,
        0,
        self->allocator);

    self->ucsCharacters     = octaspire_vector_new_with_preallocated_elements(
        sizeof(uint32_t),
        false,
        lengthInUcsChars,
        0,
        self->allocator);

    if (!self->ucsCharacters)
    {
        octaspire_string_release(self);
        self = 0;
        return 0;
    }

    self->errorStatus   = OCTASPIRE_STRING_ERROR_STATUS_OK;
    self->errorAtOctet  = 0;

    for (size_t i = 0; i < lengthInUcsChars; ++i)
    {
        octaspire_string_push_back_ucs_character(
            self,
            octaspire_string_get_ucs_character_at_index(
                other,
                (ptrdiff_t)(ucsCharStartIndex + i)));
    }

    return self;
}

void octaspire_string_release(octaspire_string_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_vector_release(self->octets);
    octaspire_vector_release(self->ucsCharacters);

    octaspire_allocator_free(self->allocator, self);
}

bool octaspire_string_set_from_c_string(
    octaspire_string_t * const self,
    char const * const str)
{
    octaspire_helpers_verify_not_null(self);
    octaspire_helpers_verify_not_null(str);

    if (!octaspire_string_clear(self))
    {
        return false;
    }

    if (!octaspire_string_concatenate_c_string(self, str))
    {
        return false;
    }

    return true;
}

bool octaspire_string_is_empty(
    octaspire_string_t const * const self)
{
    return octaspire_string_get_length_in_ucs_characters(self) == 0;
}

size_t octaspire_string_get_length_in_ucs_characters(
    octaspire_string_t const * const self)
{
    assert(self);
    return octaspire_vector_get_length(self->ucsCharacters);
}

size_t octaspire_string_get_length_in_octets(
    octaspire_string_t const * const self)
{
    octaspire_string_private_ensure_octets_are_up_to_date(self);

    if (octaspire_vector_is_empty(self->octets))
    {
        return 0;
    }

    assert(*(char const*)octaspire_vector_peek_back_element_const(self->octets) == '\0');
    // Subtract one because of '\0' at the end
    return octaspire_vector_get_length(self->octets) - 1;
}

typedef struct octaspire_string_private_index_t
{
    size_t index;
    bool   isValid;
    char   padding[7];

} octaspire_string_private_index_t;

static octaspire_string_private_index_t octaspire_string_private_is_index_valid(
    octaspire_string_t const * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    octaspire_string_private_index_t result = {.isValid=false, .index=0};

    if (possiblyNegativeIndex < 0)
    {
        ptrdiff_t tmpIndex =
            (ptrdiff_t)octaspire_string_get_length_in_ucs_characters(self) +
            possiblyNegativeIndex;

        if (tmpIndex >= 0 &&
            (size_t)tmpIndex < octaspire_string_get_length_in_ucs_characters(self))
        {
            result.index   = (size_t)tmpIndex;
            result.isValid = true;

            return result;
        }
    }

    // To allow to be used with overwrite or push back
    result.index   = (size_t)possiblyNegativeIndex;

    if ((size_t)possiblyNegativeIndex < octaspire_string_get_length_in_ucs_characters(self))
    {
        result.isValid = true;

        return result;
    }

    return result;
}

bool octaspire_string_is_index_valid(
    octaspire_string_t const * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    const octaspire_string_private_index_t index =
        octaspire_string_private_is_index_valid(
            self,
            possiblyNegativeIndex);

    return index.isValid;
}

uint32_t octaspire_string_get_ucs_character_at_index(
    octaspire_string_t const * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    octaspire_string_private_index_t const realIndex =
        octaspire_string_private_is_index_valid(self, possiblyNegativeIndex);

    if (!realIndex.isValid)
    {
        abort();
    }

    return *(uint32_t*)octaspire_vector_get_element_at(
        self->ucsCharacters,
        (ptrdiff_t)realIndex.index);
}

char const * octaspire_string_get_c_string(
    octaspire_string_t const * const self)
{
    octaspire_string_private_ensure_octets_are_up_to_date(self);

    static char const * const emptyStr = "";
    if (octaspire_vector_is_empty(self->octets))
    {
        return emptyStr;
    }

    octaspire_helpers_verify_true(
        *(char const*)octaspire_vector_peek_back_element_const(self->octets) ==
            '\0');

    return octaspire_vector_peek_front_element_const(self->octets);
}

bool octaspire_string_is_error(
    octaspire_string_t const * const self)
{
    return self->errorStatus != OCTASPIRE_STRING_ERROR_STATUS_OK;
}

octaspire_string_error_status_t octaspire_string_get_error_status(
    octaspire_string_t const * const self)
{
    return self->errorStatus;
}

size_t octaspire_string_get_error_position_in_octets(
    octaspire_string_t const * const self)
{
    return self->errorAtOctet;
}

void octaspire_string_reset_error_status(
    octaspire_string_t * const self)
{
    self->errorStatus   = OCTASPIRE_STRING_ERROR_STATUS_OK;
    self->errorAtOctet  = 0;
}

bool octaspire_string_concatenate(
    octaspire_string_t * const self,
    octaspire_string_t const * const other)
{
    return octaspire_string_concatenate_c_string(
        self,
        octaspire_string_get_c_string(other));
}

bool octaspire_string_concatenate_c_string(
    octaspire_string_t * const self,
    char const * const str)
{
    octaspire_string_reset_error_status(self);

    if (!str || str[0] == '\0')
    {
        return true;
    }

    if (!octaspire_vector_clear(self->octets))
    {
        return false;
    }

    size_t const strLen = strlen(str);

    bool result = true;

    size_t index = 0;
    uint32_t ucsChar = 0;
    int numOctets = 0;
    while (str[index] != '\0')
    {
        octaspire_utf8_decode_status_t status =
            octaspire_utf8_decode_character(str + index, (strLen - index), &ucsChar, &numOctets);

        assert(numOctets >= 0);

        if (status != OCTASPIRE_UTF8_DECODE_STATUS_OK)
        {
            self->errorStatus  = OCTASPIRE_STRING_ERROR_STATUS_DECODING_ERROR;
            self->errorAtOctet = index;
            break;
        }

        if (!octaspire_vector_push_back_element(self->ucsCharacters, &ucsChar))
        {
            result = false;
        }

        index += (size_t)numOctets;
    }

    return result;
}

bool octaspire_string_concatenate_format(
    octaspire_string_t * const self,
    char const * const fmt,
    ...)
{
    va_list arguments;
    va_start(arguments, fmt);

    octaspire_string_t *str =
        octaspire_string_new_vformat(self->allocator, fmt, arguments);

    va_end(arguments);

    if (!str)
    {
        return false;
    }

    if (!octaspire_vector_clear(self->octets))
    {
        return false;
    }

    bool result = octaspire_string_concatenate_c_string(
        self,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    return result;
}

bool octaspire_string_private_check_substring_match_at(
    octaspire_string_t const * const self,
    size_t const startFromIndex,
    octaspire_string_t const * const substring)
{
    size_t const selfLength = octaspire_string_get_length_in_ucs_characters(self);

    size_t const substringLength =
        octaspire_string_get_length_in_ucs_characters(substring);

    for (size_t i = 0; i < substringLength; ++i)
    {
        if ((startFromIndex + i) >= selfLength)
        {
            return false;
        }

        if (octaspire_string_get_ucs_character_at_index(
                self,
                (ptrdiff_t)(startFromIndex + i)) !=
            octaspire_string_get_ucs_character_at_index(
                substring,
                (ptrdiff_t)i))
        {
            return false;
        }
    }

    return true;
}

ptrdiff_t octaspire_string_find_first_substring(
    octaspire_string_t const * const self,
    ptrdiff_t const startFromIndexPossiblyNegative,
    octaspire_string_t const * const substring)
{
    octaspire_string_private_index_t const realIndex =
        octaspire_string_private_is_index_valid(self, startFromIndexPossiblyNegative);

    if (!realIndex.isValid)
    {
        return -1;
    }

    size_t const selfLength = octaspire_string_get_length_in_ucs_characters(self);

    for (size_t i = realIndex.index; i < (realIndex.index + selfLength); ++i)
    {
        if (octaspire_string_private_check_substring_match_at(
                self,
                i,
                substring))
        {
            return (ptrdiff_t)i;
        }
    }

    return -1;
}

bool octaspire_string_remove_character_at(
    octaspire_string_t * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    octaspire_string_private_index_t const realIndex =
        octaspire_string_private_is_index_valid(self, possiblyNegativeIndex);

    if (!realIndex.isValid)
    {
        return false;
    }

    if (!octaspire_vector_clear(self->octets))
    {
        return false;
    }

    if (!octaspire_vector_remove_element_at(
            self->ucsCharacters,
            (ptrdiff_t)realIndex.index))
    {
        assert(false);
        return false;
    }

    return true;
}

size_t octaspire_string_remove_characters_at(
    octaspire_string_t * const self,
    ptrdiff_t const startFromIndexPossiblyNegative,
    size_t const numCharacters)
{
    if (!numCharacters)
    {
        return numCharacters;
    }

    octaspire_string_private_index_t const realIndex =
        octaspire_string_private_is_index_valid(
            self,
            startFromIndexPossiblyNegative);

    if (!realIndex.isValid)
    {
        return 0;
    }

    if (!octaspire_vector_clear(self->octets))
    {
        return false;
    }

    size_t result = 0;

    for (ptrdiff_t i = (ptrdiff_t)numCharacters - 1; i >= 0; --i)
    {
        if (octaspire_string_remove_character_at(
                self,
                (ptrdiff_t)(realIndex.index + (size_t)i)))
        {
            ++result;
        }
    }

    return result;
}

size_t octaspire_string_remove_all_substrings(
    octaspire_string_t * const self,
    octaspire_string_t const * const substring)
{
    if (!octaspire_vector_clear(self->octets))
    {
        abort();
    }

    size_t result = 0;

    size_t const substringLength =
        octaspire_string_get_length_in_ucs_characters(substring);

    while (true)
    {
        if (octaspire_string_is_empty(self))
        {
            return result;
        }

        ptrdiff_t const substringIndex =
            octaspire_string_find_first_substring(self, 0, substring);

        if (substringIndex < 0)
        {
            return result;
        }

        if (octaspire_string_remove_characters_at(
            self,
            substringIndex,
            substringLength))
        {
            ++result;
        }
    }
}

bool octaspire_string_clear(
    octaspire_string_t * const self)
{
    self->errorStatus       = OCTASPIRE_STRING_ERROR_STATUS_OK;
    self->errorAtOctet      = 0;

    if (!octaspire_vector_clear(self->octets))
    {
        return false;
    }

    return octaspire_vector_clear(self->ucsCharacters);
}

bool octaspire_string_is_equal(
    octaspire_string_t const * const self,
    octaspire_string_t const * const other)
{
    assert(self);
    assert(other);

    size_t const myLen = octaspire_string_get_length_in_ucs_characters(self);

    if (myLen != octaspire_string_get_length_in_ucs_characters(other))
    {
        return false;
    }

    for (size_t i = 0; i < myLen; ++i)
    {
        uint32_t ucsChar1 =
            *(uint32_t const * const)octaspire_vector_get_element_at(
                self->ucsCharacters,
                (ptrdiff_t)i);

        uint32_t ucsChar2 =
            *(uint32_t const * const)octaspire_vector_get_element_at(
                other->ucsCharacters,
                (ptrdiff_t)i);

        if (ucsChar1 != ucsChar2)
        {
            return false;
        }

    }

    return true;
}

bool octaspire_string_is_equal_to_c_string(
    octaspire_string_t const * const self,
    char const * const str)
{
    assert(self);
    assert(str);

    octaspire_string_private_ensure_octets_are_up_to_date(self);

    if (octaspire_vector_is_empty(self->octets))
    {
        return (strlen(str) == 0);
    }

    assert(*(char const*)octaspire_vector_peek_back_element_const(self->octets) == '\0');

    size_t const len = octaspire_string_get_length_in_octets(self);

    if (strlen(str) != len)
    {
        return false;
    }

    return memcmp(octaspire_vector_get_element_at(self->octets,  0), str, len) == 0;
}

static int octaspire_string_levenshtein_distance_helper_get_slot(
    octaspire_vector_t const * const vectors,
    size_t                     const i,
    size_t                     const j)
{
    octaspire_vector_t const * const row = octaspire_vector_get_element_at_const(
        vectors,
        i);

    int const * const result =
        octaspire_vector_get_element_at_const(row, j);

    octaspire_helpers_verify_not_null(result);
    return *result;
}

static bool octaspire_string_levenshtein_distance_helper_set_slot(
    octaspire_vector_t * const vectors,
    size_t               const i,
    size_t               const j,
    int                  const slot)
{
    octaspire_vector_t * const row = octaspire_vector_get_element_at(
        vectors,
        i);

    return octaspire_vector_replace_element_at(row, j, &slot);
}

size_t octaspire_string_levenshtein_distance(
    octaspire_string_t const * const self,
    octaspire_string_t const * const other)
{
    size_t const selfLen = octaspire_string_get_length_in_ucs_characters(self);

    size_t const otherLen =
        octaspire_string_get_length_in_ucs_characters(other);

    octaspire_vector_t * vectors = octaspire_vector_new(
        sizeof(octaspire_vector_t *),
        true,
        (octaspire_vector_element_callback_t)octaspire_vector_release,
        self->allocator);

    // Create vector of vectors

    for (size_t i = 0; i < selfLen+1; ++i)
    {
        octaspire_vector_t * row = octaspire_vector_new(
            sizeof(int),
            false,
            0,
            self->allocator);

        octaspire_vector_push_back_element(vectors, &row);

        if (i == 0)
        {
            octaspire_vector_push_back_int(row, i);

            for (size_t j = 1; j < otherLen+1; ++j)
            {
                octaspire_vector_push_back_int(row, j);
            }
        }
        else
        {
            octaspire_vector_push_back_int(row, i);

            for (size_t j = 1; j < otherLen+1; ++j)
            {
                octaspire_vector_push_back_int(row, 0);
            }
        }
    }

    // Main loop.

    for (size_t j = 1; j < otherLen+1; ++j)
    {
        for (size_t i = 1; i < selfLen+1; ++i)
        {
            if (octaspire_string_get_ucs_character_at_index(self, i-1) ==
                octaspire_string_get_ucs_character_at_index(other, j-1))
            {
                octaspire_string_levenshtein_distance_helper_set_slot(
                    vectors,
                    i,
                    j,
                    octaspire_string_levenshtein_distance_helper_get_slot(
                        vectors,
                        i - 1,
                        j - 1));
            }
            else
            {
                octaspire_string_levenshtein_distance_helper_set_slot(
                    vectors,
                    i,
                    j,
                    octaspire_helpers_min3_int(
                        octaspire_string_levenshtein_distance_helper_get_slot(
                            vectors,
                            i - 1,
                            j) + 1,      // deletion
                        octaspire_string_levenshtein_distance_helper_get_slot(
                            vectors,
                            i,
                            j - 1) + 1,  // insertion
                        octaspire_string_levenshtein_distance_helper_get_slot(
                            vectors,
                            i - 1,
                            j - 1) + 1)); // substitution
            }
        }
    }

    int result = octaspire_string_levenshtein_distance_helper_get_slot(
        vectors,
        selfLen,
        otherLen);

    octaspire_vector_release(vectors);
    vectors = 0;

    return result;
}

int octaspire_string_compare(
    octaspire_string_t const * const self,
    octaspire_string_t const * const other)
{
    assert(self);
    assert(other);

    return octaspire_string_compare_to_c_string(
        self,
        octaspire_string_get_c_string(other));
}

int octaspire_string_compare_to_c_string(
    octaspire_string_t const * const self,
    char const * const str)
{
    assert(self);
    assert(str);

    octaspire_string_private_ensure_octets_are_up_to_date(self);

    if (octaspire_vector_is_empty(self->octets))
    {
        return 0;
    }

    assert(*(char const*)octaspire_vector_peek_back_element_const(self->octets) == '\0');

    return strcmp(octaspire_string_get_c_string(self), str);
}

bool octaspire_string_starts_with(
    octaspire_string_t const * const self,
    octaspire_string_t const * const other)
{
    assert(self && other);

    size_t const myLen = octaspire_string_get_length_in_ucs_characters(self);
    size_t const otherLen = octaspire_string_get_length_in_ucs_characters(other);

    if (myLen < otherLen)
    {
        return false;
    }

    for (size_t i = 0; i < otherLen; ++i)
    {
        if (octaspire_string_get_ucs_character_at_index(
                self,
                (ptrdiff_t)i) !=
            octaspire_string_get_ucs_character_at_index(
                other,
                (ptrdiff_t)i))
        {
            return false;
        }
    }

    return true;
}

bool octaspire_string_starts_with_c_string(
    octaspire_string_t const * const self,
    char const * const str)
{
    assert(self && str);

    octaspire_string_t * other = octaspire_string_new(str, self->allocator);
    octaspire_helpers_verify_not_null(other);

    bool const result = octaspire_string_starts_with(self, other);

    octaspire_string_release(other);
    other = 0;

    return result;
}

bool octaspire_string_ends_with(
    octaspire_string_t const * const self,
    octaspire_string_t const * const other)
{
    assert(self && other);

    size_t const myLen = octaspire_string_get_length_in_ucs_characters(self);
    size_t const otherLen = octaspire_string_get_length_in_ucs_characters(other);

    if (myLen < otherLen)
    {
        return false;
    }

    size_t const myStartIndex = myLen - otherLen;

    for (size_t i = 0; i < otherLen; ++i)
    {
        if (octaspire_string_get_ucs_character_at_index(
                self,
                (ptrdiff_t)(myStartIndex + i)) !=
            octaspire_string_get_ucs_character_at_index(
                other,
                (ptrdiff_t)i))
        {
            return false;
        }
    }

    return true;
}

bool octaspire_string_ends_with_c_string(
    octaspire_string_t const * const self,
    char const * const str)
{
    assert(self && str);

    octaspire_string_t * other = octaspire_string_new(str, self->allocator);
    octaspire_helpers_verify_not_null(other);

    bool const result = octaspire_string_ends_with(self, other);

    octaspire_string_release(other);
    other = 0;

    return result;
}

uint32_t octaspire_string_get_hash(
    octaspire_string_t const * const self)
{
    uint32_t hash = 0;

    octaspire_string_private_ensure_octets_are_up_to_date(self);

    if (octaspire_vector_is_empty(self->octets))
    {
        return 0;
    }

    assert(*(char const*)octaspire_vector_peek_back_element_const(self->octets) == '\0');

    size_t const len = octaspire_vector_get_length(self->octets);

    if (!octaspire_vector_is_empty(self->octets))
    {
        hash = jenkins_one_at_a_time_hash(
            octaspire_vector_get_element_at(self->octets, 0), len);
    }

    return hash;
}

bool octaspire_string_push_back_ucs_character(
    octaspire_string_t *self,
    uint32_t const character)
{
    assert(self);

    if (!octaspire_vector_push_back_element(self->ucsCharacters, &character))
    {
        return false;
    }

    return octaspire_vector_clear(self->octets);
}

bool octaspire_string_pop_front_ucs_character(
    octaspire_string_t *self)
{
    assert(self);

    if (octaspire_string_is_empty(self))
    {
        return false;
    }

    if (!octaspire_vector_clear(self->octets))
    {
        return false;
    }

    return octaspire_string_remove_character_at(self, 0);
}

bool octaspire_string_pop_back_ucs_character(
    octaspire_string_t *self)
{
    assert(self);

    if (octaspire_string_is_empty(self))
    {
        return false;
    }

    if (!octaspire_vector_clear(self->octets))
    {
        return false;
    }

    return octaspire_string_remove_character_at(
        self,
        (ptrdiff_t)
            (octaspire_string_get_length_in_ucs_characters(self) - 1));
}

bool octaspire_string_insert_string_to(
    octaspire_string_t * const self,
    octaspire_string_t const * const str,
    ptrdiff_t const indexToPutFirstCharacterPossiblyNegative)
{
    octaspire_string_private_index_t const realIndex =
        octaspire_string_private_is_index_valid(
            self,
            indexToPutFirstCharacterPossiblyNegative);

    if (!realIndex.isValid)
    {
        return false;
    }

    if (!octaspire_vector_clear(self->octets))
    {
        return false;
    }

    for (size_t i = 0; i < octaspire_string_get_length_in_ucs_characters(str); ++i)
    {
        uint32_t const c =
            octaspire_string_get_ucs_character_at_index(
                str,
                (ptrdiff_t)i);

        if (!octaspire_vector_insert_element_before_the_element_at_index(
            self->ucsCharacters,
            &c,
            (ptrdiff_t)(realIndex.index + i)))
        {
            return false;
        }
    }

    return true;
}

bool octaspire_string_overwrite_with_string_at(
    octaspire_string_t * const self,
    octaspire_string_t const * const str,
    ptrdiff_t const indexToPutFirstCharacterPossiblyNegative)
{
    octaspire_string_private_index_t const realIndex =
        octaspire_string_private_is_index_valid(
            self,
            indexToPutFirstCharacterPossiblyNegative);

    if (!realIndex.isValid)
    {
        // New chars are pushed back if index is too large,
        // so no need to check that.
        if (indexToPutFirstCharacterPossiblyNegative < 0)
        {
            return false;
        }
    }

    if (!octaspire_vector_clear(self->octets))
    {
        return false;
    }

    for (size_t i = 0;
         i < octaspire_string_get_length_in_ucs_characters(str);
         ++i)
    {
        uint32_t const c =
            octaspire_string_get_ucs_character_at_index(
                str,
                (ptrdiff_t)i);

        if (!octaspire_vector_replace_element_at_index_or_push_back(
            self->ucsCharacters,
            &c,
            (ptrdiff_t)(realIndex.index + i)))
        {
            return false;
        }
    }

    return true;
}

octaspire_vector_t *octaspire_string_split(
    octaspire_string_t *self,
    char const * const delimiter)
{
    octaspire_string_t *delimString = octaspire_string_new(
        delimiter,
        self->allocator);

    if (!delimString)
    {
        return 0;
    }

    octaspire_vector_t *result = octaspire_vector_new(
        sizeof(octaspire_string_t*),
        true,
        (octaspire_vector_element_callback_t)octaspire_string_release,
        self->allocator);

    if (!result)
    {
        octaspire_string_release(delimString);
        delimString = 0;
        return 0;
    }

    octaspire_string_t *collectorString = octaspire_string_new(
        "",
        self->allocator);

    if (!collectorString)
    {
        octaspire_string_release(delimString);
        delimString = 0;

        octaspire_vector_release(result);
        result = 0;
        return 0;
    }

    for (size_t i = 0;
         i < octaspire_string_get_length_in_ucs_characters(self);
         ++i)
    {
        octaspire_string_push_back_ucs_character(
            collectorString,
            octaspire_string_get_ucs_character_at_index(
                self,
                (ptrdiff_t)i));

        if (octaspire_string_is_equal(collectorString, delimString))
        {
            octaspire_string_clear(collectorString);
        }
        else if (octaspire_string_ends_with(collectorString, delimString))
        {
            size_t const numUcsCharsToGet =
                octaspire_string_get_length_in_ucs_characters(collectorString) -
                octaspire_string_get_length_in_ucs_characters(delimString);

            octaspire_string_t *token =
                octaspire_string_new_substring_from_given_index_and_length(
                    collectorString,
                    collectorString->allocator,
                    0,
                    numUcsCharsToGet);

            assert(token);

            octaspire_vector_push_back_element(result, &token);

            octaspire_string_clear(collectorString);
        }
    }

    if (!octaspire_string_is_empty(collectorString))
    {
        if (octaspire_string_is_equal(collectorString, delimString))
        {
            octaspire_string_clear(collectorString);
        }
        else if (octaspire_string_ends_with(collectorString, delimString))
        {
            size_t const numUcsCharsToGet =
                octaspire_string_get_length_in_ucs_characters(collectorString) -
                octaspire_string_get_length_in_ucs_characters(delimString);

            octaspire_string_t *token =
                octaspire_string_new_substring_from_given_index_and_length(
                    collectorString,
                    collectorString->allocator,
                    0,
                    numUcsCharsToGet);

            assert(token);

            octaspire_vector_push_back_element(result, &token);

            octaspire_string_clear(collectorString);
        }
        else
        {
            octaspire_string_t *token =
                octaspire_string_new_copy(
                    collectorString,
                    collectorString->allocator);

            assert(token);

            octaspire_vector_push_back_element(result, &token);

            octaspire_string_clear(collectorString);
        }

        octaspire_string_clear(collectorString);
    }

    octaspire_string_release(collectorString);
    collectorString = 0;

    octaspire_string_release(delimString);
    delimString = 0;

    return result;
}

bool octaspire_string_contains_char(
    octaspire_string_t const * const self,
    uint32_t const character)
{
    for (size_t i = 0;
         i < octaspire_string_get_length_in_ucs_characters(self);
         ++i)
    {
        if (octaspire_string_get_ucs_character_at_index(
                self,
                (ptrdiff_t)i) == character)
        {
            return true;
        }
    }

    return false;
}

bool octaspire_string_contains_only_these_chars(
    octaspire_string_t const * const self,
    octaspire_string_t const * const chars)
{
    for (size_t i = 0;
         i < octaspire_string_get_length_in_ucs_characters(self);
         ++i)
    {
        uint32_t const selfChar =
            octaspire_string_get_ucs_character_at_index(
                self,
                (ptrdiff_t)i);

        bool found = false;

        for (size_t j = 0;
             j < octaspire_string_get_length_in_ucs_characters(chars);
             ++j)
        {
            if (octaspire_string_get_ucs_character_at_index(
                chars,
                (ptrdiff_t)j) == selfChar)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            return false;
        }
    }

    return true;
}

bool octaspire_string_contains_only_these_chars_c_string(
    octaspire_string_t const * const self,
    char const * const chars)
{
    // TODO maybe a more efficient implementation.

    octaspire_string_t * const str =
        octaspire_string_new(chars, self->allocator);

    octaspire_helpers_verify_not_null(str);

    bool const result =
        octaspire_string_contains_only_these_chars(self, str);

    octaspire_string_release(str);
    return result;
}

octaspire_vector_t *octaspire_string_find_char(
    octaspire_string_t const * const self,
    octaspire_string_t const * const character,
    ptrdiff_t const characterIndexPossiblyNegative)
{
    octaspire_string_private_index_t const realIndex =
        octaspire_string_private_is_index_valid(
            character,
            characterIndexPossiblyNegative);

    if (!realIndex.isValid)
    {
        return 0;
    }

    octaspire_vector_t *result = octaspire_vector_new(
        sizeof(size_t),
        false,
        0,
        self->allocator);

    for (size_t i = 0;
         i < octaspire_string_get_length_in_ucs_characters(self);
         ++i)
    {
        if (octaspire_string_get_ucs_character_at_index(
                self,
                (ptrdiff_t)i) ==
            octaspire_string_get_ucs_character_at_index(
                character,
                (ptrdiff_t)realIndex.index))
        {
            octaspire_vector_push_back_element(result, &i);
        }
    }

    return result;
}

static bool octaspire_string_private_ensure_octets_are_up_to_date(
    octaspire_string_t const * const self)
{
    if (!octaspire_vector_is_empty(self->octets))
    {
        return true;
    }

    for (size_t i = 0; i < octaspire_vector_get_length(self->ucsCharacters); ++i)
    {
        octaspire_utf8_character_t encoded;

        uint32_t const ucsChar = *(uint32_t const * const)
            octaspire_vector_get_element_at_const(
                self->ucsCharacters,
                (ptrdiff_t)i);

        octaspire_utf8_encode_status_t const status = octaspire_utf8_encode_character(
            ucsChar,
            &encoded);

        if (status != OCTASPIRE_UTF8_ENCODE_STATUS_OK)
        {
            return false;
        }

        for (size_t j = 0; j < encoded.numoctets; ++j)
        {
            // Ugly; force into non-const.
            if (!octaspire_vector_push_back_element(
                    (octaspire_vector_t * const)self->octets,
                    encoded.octets + 4 - encoded.numoctets + j))
            {
                return false;
            }
        }
    }

    // Append null byte to allow use with libc
    // Ugly; force into non-const.
    if (!octaspire_vector_push_back_element(
        (octaspire_vector_t * const)self->octets,
        &octaspire_string_private_null_octet))
    {
        return false;
    }

    return true;
}

bool octaspire_string_private_is_string_at_index(
    octaspire_string_t const * const self,
    size_t const selfIndex,
    octaspire_string_t const * const str,
    size_t const strFirstIndex,
    size_t const strLastIndex)
{
    size_t selfIndex2 = selfIndex;
    for (size_t i = strFirstIndex; i <= strLastIndex; ++i)
    {
        if (selfIndex2 >= octaspire_string_get_length_in_ucs_characters(self))
        {
            return false;
        }

        if (octaspire_string_get_ucs_character_at_index(
                self,
                (ptrdiff_t)selfIndex2) !=
            octaspire_string_get_ucs_character_at_index(
                str,
                (ptrdiff_t)i))
        {
            return false;
        }

        ++selfIndex2;
    }

    return true;
}

octaspire_vector_t *octaspire_string_find_string(
    octaspire_string_t const * const self,
    octaspire_string_t const * const str,
    ptrdiff_t const strStartIndexPossiblyNegative,
    size_t const strLength)
{
    if (!strLength)
    {
        return 0;
    }

    octaspire_string_private_index_t const realIndex =
        octaspire_string_private_is_index_valid(str, strStartIndexPossiblyNegative);

    if (!realIndex.isValid)
    {
        return 0;
    }

    size_t const strEndIndex = realIndex.index + (strLength - 1);

    if (strEndIndex >= octaspire_string_get_length_in_ucs_characters(str))
    {
        return 0;
    }

    octaspire_vector_t *result = octaspire_vector_new(
        sizeof(size_t),
        false,
        0,
        self->allocator);

    for (size_t i = 0; i < octaspire_string_get_length_in_ucs_characters(self); ++i)
    {
        if (octaspire_string_private_is_string_at_index(
            self,
            i,
            str,
            realIndex.index,
            strEndIndex))
        {
            octaspire_vector_push_back_element(result, &i);
        }
    }

    return result;
}

