/******************************************************************************
Octaspire Core - Containers and other utility libraries in standard C99
Copyright 2017 - 2019 www.octaspire.com

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
#include "octaspire/core/octaspire_helpers.h"
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "external/jenkins_one_at_a_time.h"

bool octaspire_helpers_test_bit(uint32_t const bitSet, size_t const index)
{
    assert(index < 32);
    return bitSet & ((uint32_t)0x01 << index);
}

char *octaspire_helpers_path_to_buffer(
    char const * const path,
    size_t *octetsAllocated,
    octaspire_allocator_t *allocator,
    octaspire_stdio_t *stdio)
{
    *octetsAllocated = 0;

#ifdef _MSC_VER
    FILE *f = 0;
    errno_t const err = fopen_s(&f, path, "rb");

    if (err)
    {
        return 0;
    }

    octaspire_helpers_verify_not_null(f);
#else
    FILE *f = fopen(path, "rb");

    if (!f)
    {
        return 0;
    }
#endif

    fseek(f, 0, SEEK_END);

    long const length = ftell(f);

    if (length <= 0)
    {
        fclose(f);
        f = 0;
        return 0;
    }

    fseek(f, 0, SEEK_SET);

    char *result = octaspire_allocator_malloc(allocator, sizeof(char) * (size_t)length);

    if (!result)
    {
        fclose(f);
        f = 0;
        return 0;
    }

    *octetsAllocated = (size_t)length;

    if (*octetsAllocated != octaspire_stdio_fread(stdio, result, sizeof(char), *octetsAllocated, f))
    {
        fclose(f);
        f = 0;
        octaspire_allocator_free(allocator, result);
        result = 0;
        *octetsAllocated = 0;
        return 0;
    }

    fclose(f);
    f = 0;

    return result;
}

uint32_t octaspire_helpers_calculate_hash_for_size_t_argument(size_t const value)
{
    return jenkins_one_at_a_time_hash(&value, sizeof(value));
}

uint32_t octaspire_helpers_calculate_hash_for_bool_argument(bool const value)
{
    return jenkins_one_at_a_time_hash(&value, sizeof(value));
}

uint32_t octaspire_helpers_calculate_hash_for_int32_t_argument(int32_t const value)
{
    return jenkins_one_at_a_time_hash(&value, sizeof(value));
}

uint32_t octaspire_helpers_calculate_hash_for_double_argument(double const value)
{
    return jenkins_one_at_a_time_hash(&value, sizeof(value));
}

uint32_t octaspire_helpers_calculate_hash_for_void_pointer_argument(void const * const value)
{
    return jenkins_one_at_a_time_hash(&value, sizeof(value));
}

uint32_t octaspire_helpers_calculate_hash_for_memory_buffer_argument(
    void const * const value,
    size_t const lengthInOctets)
{
    return jenkins_one_at_a_time_hash(value, lengthInOctets);
}

size_t octaspire_helpers_character_digit_to_number(uint32_t const c)
{
    return c - '0';
}

size_t octaspire_helpers_min_size_t(size_t const a, size_t const b)
{
    if (a < b)
    {
        return a;
    }

    return b;
}

int octaspire_helpers_min_int(int const a, int const b)
{
    if (a < b)
    {
        return a;
    }

    return b;
}

size_t octaspire_helpers_min3_size_t(
    size_t const a,
    size_t const b,
    size_t const c)
{
    if (a < b)
    {
        return octaspire_helpers_min_size_t(a, c);
    }

    return octaspire_helpers_min_size_t(b, c);
}

int octaspire_helpers_min3_int(
    int const a,
    int const b,
    int const c)
{
    if (a < b)
    {
        return octaspire_helpers_min_int(a, c);
    }

    return octaspire_helpers_min_int(b, c);
}

size_t octaspire_helpers_max_size_t(size_t const a, size_t const b)
{
    if (a > b)
    {
        return a;
    }

    return b;
}

void octaspire_helpers_verify_true(bool const condition)
{
    if (!condition)
    {
        abort();
    }
}

void octaspire_helpers_verify_null(void const * const ptr)
{
    if (ptr)
    {
        abort();
    }
}

void octaspire_helpers_verify_not_null(void const * const ptr)
{
    if (!ptr)
    {
        abort();
    }
}

void octaspire_helpers_verify_not_null_void_funptr_void_ptr_const(
    void (*ptr)(void * const))
{
    if (!ptr)
    {
        abort();
    }
}

float octaspire_helpers_maxf(float const a, float const b)
{
    if (a > b)
    {
        return a;
    }

    return b;
}

float octaspire_helpers_ceilf(float const value)
{
    return (float)ceil((double)value);
}

bool octaspire_helpers_is_even_size_t(size_t const value)
{
    return (value % 2 == 0);
}

bool octaspire_helpers_is_odd_size_t( size_t const value)
{
    return (!octaspire_helpers_is_even_size_t(value));
}

static uint8_t const octaspire_helpers_base64_private_bad_num = 64;

static uint8_t octaspire_helpers_base64_private_base64_char_into_num(char const c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return (uint8_t)c - 65;
    }

    if (c >= 'a' && c <= 'z')
    {
        return 26 + ((uint8_t)c - 97);
    }

    if (c >= '0' && c <= '9')
    {
        return 52 + ((uint8_t)c - 48);
    }

    if (c == '+')
    {
        return 62;
    }

    if (c == '/')
    {
        return 63;
    }

    return octaspire_helpers_base64_private_bad_num;
}

uint8_t octaspire_helpers_get_char_or_default_from_buf(
    uint8_t const * const input,
    size_t const inLen,
    size_t const getAtIndex,
    uint8_t const defaultChar)
{
    if (!input || getAtIndex >= inLen)
    {
        return defaultChar;
    }

    return input[getAtIndex];
}

size_t octaspire_helpers_measure_length_of_last_line(
    octaspire_string_t const * const str)
{
    size_t result = 0;
    while (result < octaspire_string_get_length_in_ucs_characters(str))
    {
        ++result;
        if (octaspire_string_get_ucs_character_at_index(
            str,
            -(ptrdiff_t)result) == '\n')
        {
            return result;
        }
    }

    return result;
}

static size_t octaspire_helpers_base64_private_skip_whitespace(
    char const * const input,
    size_t const inLen,
    size_t index)
{
    while (index < inLen && isspace((int)input[index]))
    {
        ++index;
    }

    return index;
}

octaspire_vector_t * octaspire_helpers_base64_decode(
    char const * const input,
    int32_t const inputLenOrNegativeToMeasure,
    octaspire_allocator_t * const allocator)
{
    if (inputLenOrNegativeToMeasure < 2)
    {
        return 0;
    }

    size_t numPadding = 0;

    octaspire_vector_t * result = octaspire_vector_new(
        sizeof(char),
        false,
        0,
        allocator);

    if (!result)
    {
        return result;
    }

    // Negative length means that the length must be measured here.
    size_t const inLen = (inputLenOrNegativeToMeasure < 0)
        ? strlen(input)
        : (size_t)inputLenOrNegativeToMeasure;

    uint32_t indices[4] = {0, 0, 0, 0};
    size_t   numIndices = 0;

    for (size_t i = 0; i <= inLen; /*NOP*/)
    {
        if (numIndices == 4)
        {
            // Generate the number with 24 bits.
            uint32_t const num24bits =
                ((indices[0] & 63) << (24 -  6)) +
                ((indices[1] & 63) << (24 - 12)) +
                ((indices[2] & 63) << (24 - 18)) +
                ( indices[3] & 63);

            // Break the number with 24 bits into the three original octets
            // and save those into the result.

            for (size_t j = 0; j < 3; ++j)
            {
                char octet = (char)((num24bits >> (16 - (j * 8))) & 0xFF);
                if (!octaspire_vector_push_back_element(result, &octet))
                {
                    octaspire_vector_release(result);
                    result = 0;
                    return result;
                }
            }

            numIndices = 0;
        }

        i = octaspire_helpers_base64_private_skip_whitespace(input, inLen, i);

        if (i >= inLen)
        {
            break;
        }

        char currentChar = input[i];

        if (currentChar == '=')
        {
            ++numPadding;
            currentChar = 'A';
        }

        uint32_t const index =
            octaspire_helpers_base64_private_base64_char_into_num(currentChar);

        if (index == octaspire_helpers_base64_private_bad_num)
        {
            octaspire_vector_release(result);
            result = 0;
            return result;
        }

        indices[numIndices] = index;
        ++numIndices;
        ++i;
    }

    if (numIndices != 0 || numPadding >= octaspire_vector_get_length(result))
    {
        octaspire_vector_release(result);
        result = 0;
        return result;
    }

    for (size_t i = 0; i < numPadding; ++i)
    {
        while (isspace(
            (int)*(char const * const)
            octaspire_vector_peek_back_element_const(result)))
        {
            if (!octaspire_vector_pop_back_element(result))
            {
                octaspire_vector_release(result);
                result = 0;
                return result;
            }
        }

        if (!octaspire_vector_pop_back_element(result))
        {
            octaspire_vector_release(result);
            result = 0;
            return result;
        }
    }

    return result;
}

octaspire_string_t * octaspire_helpers_base64_encode(
    char const * const input,
    size_t const inLen,
    size_t const lineLen,
    octaspire_allocator_t * const allocator)
{
    char const * const base64chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    octaspire_string_t * result = octaspire_string_new(
        "",
        allocator);

    if (!result)
    {
        return result;
    }

    size_t numPadding = inLen % 3;

    if (numPadding)
    {
        numPadding = 3 - numPadding;
    }

    size_t currentLineLen = 0;

    for (size_t i = 0; i < inLen; i += 3)
    {
        // Three octets of input is converted into a number with 24 bits.
        // Any missing characters are replaced with the NULL char.

        uint32_t num24bits = 0;

        for (size_t j = 0; j < 3; ++j)
        {
            uint32_t const val = (uint32_t)octaspire_helpers_get_char_or_default_from_buf(
                (uint8_t const * const)input,
                (size_t)inLen,
                i + j,
                '\0');

            num24bits += (val << (16 - (j * 8)));
        }

        // This 24 bit number is broken down into four 6 bit numbers.
        // Number 63 has bit pattern 111111.
        uint8_t n[4];
        n[0] = (num24bits >> (24 -  6)) & 63;
        n[1] = (num24bits >> (24 - 12)) & 63;
        n[2] = (num24bits >> (24 - 18)) & 63;
        n[3] = (num24bits             ) & 63;

        // Four six bit numbers are used as indices into the
        // array of base64 characters.
        for (size_t j = 0; j < 4; ++j)
        {
            if (!octaspire_string_push_back_ucs_character(
                result,
                (uint32_t)base64chars[n[j]]))
            {
                octaspire_string_release(result);
                result = 0;
                return result;
            }

            ++currentLineLen;

            if (lineLen && currentLineLen >= lineLen)
            {
                if (!octaspire_string_push_back_ucs_character(
                        result,
                        '\n'))
                {
                    octaspire_string_release(result);
                    result = 0;
                    return result;
                }

                currentLineLen = 0;
            }
        }
    }

    if (numPadding)
    {
        size_t numZerosRemoved = 0;

        for (size_t i = 0;
            i < octaspire_string_get_length_in_ucs_characters(result);
            ++i)
        {
            if (octaspire_string_get_ucs_character_at_index(result, -1) != '\n')
            {
                ++numZerosRemoved;
                --currentLineLen;
            }
            else
            {
                currentLineLen = octaspire_helpers_measure_length_of_last_line(result);
            }

            if (!octaspire_string_pop_back_ucs_character(result))
            {
                octaspire_string_release(result);
                result = 0;
                return result;
            }

            if (numZerosRemoved == numPadding)
            {
                break;
            }
        }
    }

    for (size_t i = 0; i < numPadding; ++i)
    {
        if (lineLen && currentLineLen >= lineLen)
        {
            if (!octaspire_string_push_back_ucs_character(
                    result,
                    '\n'))
            {
                octaspire_string_release(result);
                result = 0;
                return result;
            }

            currentLineLen = 0;
        }

        if (!octaspire_string_push_back_ucs_character(
                result,
                (uint32_t)'='))
        {
            octaspire_string_release(result);
            result = 0;

            return result;
        }

        ++currentLineLen;
    }

    return result;
}

