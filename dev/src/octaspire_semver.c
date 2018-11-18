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
#include "octaspire/core/octaspire_semver.h"
#include <string.h>
#include "octaspire/core/octaspire_helpers.h"

struct octaspire_semver_pre_release_elem_t
{
    octaspire_semver_pre_release_elem_type_t  type;
    octaspire_allocator_t                    *allocator;

    union
    {
        size_t               numerical;
        octaspire_string_t * lexical;
    } value;
};

void octaspire_semver_pre_release_elem_release(octaspire_semver_pre_release_elem_t *self)
{
    if (!self)
    {
        return;
    }

    switch (self->type)
    {
        case OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL:
        {
            octaspire_string_release(self->value.lexical);
        }
        break;

        case OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL:
        {
            // NOP
        }
        break;

        case OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_UNKNOWN:
        {
            abort();
        }
        break;
    }

    octaspire_allocator_free(self->allocator, self);
}

octaspire_semver_pre_release_elem_t *octaspire_semver_pre_release_elem_new(
    octaspire_string_t      const * const str,
    octaspire_allocator_t * const allocator)
{
    octaspire_helpers_verify_not_null(str);
    octaspire_helpers_verify_not_null(allocator);

    octaspire_semver_pre_release_elem_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_semver_pre_release_elem_t));

    if (!self)
    {
        return 0;
    }

    self->allocator = allocator;

    if (octaspire_string_contains_only_these_chars_c_string(
            str,
            "0123456789"))
    {
        self->type            = OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL;
        self->value.numerical = atoi(octaspire_string_get_c_string(str));
    }
    else
    {
        octaspire_string_t * copyStr =
            octaspire_string_new_copy(str, self->allocator);

        if (!copyStr)
        {
            octaspire_semver_pre_release_elem_release(self);
            self = 0;
            return 0;
        }

        self->type          = OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL;
        self->value.lexical = copyStr;
    }

    return self;
}

octaspire_semver_pre_release_elem_t *
octaspire_semver_pre_release_elem_new_from_c_string(
    char            const * const str,
    octaspire_allocator_t * const allocator)
{
    octaspire_helpers_verify_not_null(str);
    octaspire_helpers_verify_not_null(allocator);

    octaspire_string_t * tmpStr =
        octaspire_string_new(str, allocator);

    octaspire_helpers_verify_not_null(tmpStr);

    octaspire_semver_pre_release_elem_t * const result =
        octaspire_semver_pre_release_elem_new(tmpStr, allocator);

    octaspire_string_release(tmpStr);
    tmpStr = 0;

    return result;
}

octaspire_semver_pre_release_elem_t *octaspire_semver_pre_release_elem_new_copy(
    octaspire_semver_pre_release_elem_t const * const other,
    octaspire_allocator_t * const allocator)
{
    octaspire_helpers_verify_not_null(other);
    octaspire_helpers_verify_not_null(allocator);

    octaspire_semver_pre_release_elem_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_semver_pre_release_elem_t));

    if (!self)
    {
        return 0;
    }

    self->allocator = allocator;
    self->type      = other->type;

    switch (self->type)
    {
        case OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL:
        {
            self->value.numerical = other->value.numerical;
        }
        break;

        case OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL:
        {
            octaspire_string_t * copyStr =
                octaspire_string_new_copy(other->value.lexical, self->allocator);

            if (!copyStr)
            {
            octaspire_semver_pre_release_elem_release(self);
            self = 0;
            return 0;
            }

            self->value.lexical = copyStr;
        }
        break;

        default:
        {
            abort();
        }
    }

    return self;
}

octaspire_semver_pre_release_elem_t *octaspire_semver_pre_release_elem_numerical_new(
    size_t                  const value,
    octaspire_allocator_t * const allocator)
{
    octaspire_helpers_verify_not_null(allocator);

    octaspire_semver_pre_release_elem_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_semver_pre_release_elem_t));

    if (!self)
    {
        return 0;
    }

    self->allocator = allocator;

    self->type            = OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL;
    self->value.numerical = value;

    return self;
}

octaspire_semver_pre_release_elem_type_t
octaspire_semver_pre_release_elem_get_type(
    octaspire_semver_pre_release_elem_t const * const self)
{
    return self->type;
}

bool octaspire_semver_pre_release_elem_is_lexical_type(
    octaspire_semver_pre_release_elem_t const * const self)
{
    return octaspire_semver_pre_release_elem_get_type(self) ==
        OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL;
}

bool octaspire_semver_pre_release_elem_is_numerical_type(
    octaspire_semver_pre_release_elem_t const * const self)
{
    return octaspire_semver_pre_release_elem_get_type(self) ==
        OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL;
}

size_t octaspire_semver_pre_release_elem_get_numerical_value(
    octaspire_semver_pre_release_elem_t const * const self)
{
    octaspire_helpers_verify_true(
        octaspire_semver_pre_release_elem_is_numerical_type(self));

    return self->value.numerical;
}

void octaspire_semver_pre_release_elem_make_numerical(
    octaspire_semver_pre_release_elem_t * const self,
    size_t const value)
{
    if (octaspire_semver_pre_release_elem_is_lexical_type(self))
    {
        octaspire_helpers_verify_not_null(self->value.lexical);
        octaspire_string_release(self->value.lexical);
        self->value.lexical = 0;
    }

    self->type = OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL;
    self->value.numerical = value;
}

bool octaspire_semver_pre_release_elem_make_lexical(
    octaspire_semver_pre_release_elem_t * const self,
    char const * const value)
{
    octaspire_string_t * const tmpStr = octaspire_string_new(
        value,
        self->allocator);

    if (!tmpStr)
    {
        return false;
    }

    if (octaspire_semver_pre_release_elem_is_lexical_type(self))
    {
        octaspire_helpers_verify_not_null(self->value.lexical);
        octaspire_string_release(self->value.lexical);
        self->value.lexical = 0;
    }

    self->type = OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL;
    self->value.lexical = tmpStr;
    return true;
}


octaspire_string_t const * octaspire_semver_pre_release_elem_get_lexical_value(
    octaspire_semver_pre_release_elem_t const * const self)
{
    octaspire_helpers_verify_true(
        octaspire_semver_pre_release_elem_is_lexical_type(self));

    return self->value.lexical;
}

char const * octaspire_semver_pre_release_elem_get_lexical_value_as_c_string(
    octaspire_semver_pre_release_elem_t const * const self)
{
    octaspire_helpers_verify_true(
        octaspire_semver_pre_release_elem_is_lexical_type(self));

    return octaspire_string_get_c_string(
        octaspire_semver_pre_release_elem_get_lexical_value(self));
}


struct octaspire_semver_t
{
    size_t                 major;
    size_t                 minor;
    size_t                 patch;
    octaspire_vector_t    *preRelease;
    octaspire_vector_t    *buildMetadata;
    octaspire_allocator_t *allocator;
};

octaspire_semver_t *octaspire_semver_new(
    size_t                const         major,
    size_t                const         minor,
    size_t                const         patch,
    octaspire_vector_t    const * const preRelease,
    octaspire_vector_t    const * const buildMetadata,
    octaspire_allocator_t       * const allocator)
{
    if (!allocator)
    {
        return 0;
    }

    octaspire_semver_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_semver_t));

    if (!self)
    {
        return 0;
    }

    self->allocator = allocator;
    self->major     = major;
    self->minor     = minor;
    self->patch     = patch;

    self->preRelease = octaspire_vector_new(
        sizeof(octaspire_semver_pre_release_elem_t*),
        true,
        (octaspire_vector_element_callback_t)octaspire_semver_pre_release_elem_release,
        self->allocator);

    if (!self->preRelease)
    {
        octaspire_semver_release(self);
        self = 0;
        return 0;
    }

    self->buildMetadata = octaspire_vector_new(
        sizeof(octaspire_string_t*),
        true,
        (octaspire_vector_element_callback_t)octaspire_string_release,
        self->allocator);

    if (!self->buildMetadata)
    {
        octaspire_semver_release(self);
        self = 0;
        return 0;
    }

    if (preRelease)
    {
        for (size_t i = 0; i < octaspire_vector_get_length(preRelease); ++i)
        {
            octaspire_string_t const * const str =
                octaspire_vector_get_element_at_const(preRelease, i);

            octaspire_helpers_verify_not_null(str);

            octaspire_semver_pre_release_elem_t * preReleaseElem =
                octaspire_semver_pre_release_elem_new(str, self->allocator);

            if (!preReleaseElem)
            {
                octaspire_semver_release(self);
                self = 0;
                return 0;
            }

            if (!octaspire_vector_push_back_element(
                    self->preRelease,
                    &preReleaseElem))
            {
                octaspire_semver_pre_release_elem_release(preReleaseElem);

                octaspire_semver_release(self);
                self = 0;
                return 0;
            }
        }
    }

    if (buildMetadata)
    {
        for (size_t i = 0; i < octaspire_vector_get_length(buildMetadata); ++i)
        {
            octaspire_string_t * str =
                octaspire_string_new_copy(
                    octaspire_vector_get_element_at_const(buildMetadata, i),
                    self->allocator);

            if (!str)
            {
                octaspire_semver_release(self);
                self = 0;
                return 0;
            }

            if (!octaspire_vector_push_back_element(self->buildMetadata, &str))
            {
                octaspire_string_release(str);
                str  = 0;
                octaspire_semver_release(self);
                self = 0;
                return 0;
            }
        }
    }

    return self;
}

octaspire_semver_t *octaspire_semver_new_copy(
    octaspire_semver_t    const * const other,
    octaspire_allocator_t       * const allocator)
{
    octaspire_helpers_verify_not_null(other);

    if (!allocator)
    {
        return 0;
    }

    octaspire_semver_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_semver_t));

    if (!self)
    {
        return 0;
    }

    self->allocator = allocator;
    self->major     = other->major;
    self->minor     = other->minor;
    self->patch     = other->patch;

    self->preRelease = octaspire_vector_new(
        sizeof(octaspire_semver_pre_release_elem_t*),
        true,
        (octaspire_vector_element_callback_t)octaspire_semver_pre_release_elem_release,
        self->allocator);

    if (!self->preRelease)
    {
        octaspire_semver_release(self);
        self = 0;
        return 0;
    }

    self->buildMetadata = octaspire_vector_new(
        sizeof(octaspire_string_t*),
        true,
        (octaspire_vector_element_callback_t)octaspire_string_release,
        self->allocator);

    if (!self->buildMetadata)
    {
        octaspire_semver_release(self);
        self = 0;
        return 0;
    }

    if (other->preRelease)
    {
        for (size_t i = 0; i < octaspire_vector_get_length(other->preRelease); ++i)
        {
            octaspire_semver_pre_release_elem_t * preReleaseElem =
                octaspire_vector_get_element_at(other->preRelease, i);

            octaspire_helpers_verify_not_null(preReleaseElem);

            octaspire_semver_pre_release_elem_t * const copyOfPreReleaseElem =
                octaspire_semver_pre_release_elem_new_copy(
                    preReleaseElem,
                    self->allocator);

            if (!copyOfPreReleaseElem)
            {
                octaspire_semver_release(self);
                self = 0;
                return 0;
            }

            if (!octaspire_vector_push_back_element(
                    self->preRelease,
                    &copyOfPreReleaseElem))
            {
                octaspire_semver_pre_release_elem_release(preReleaseElem);
                preReleaseElem = 0;

                octaspire_semver_release(self);
                self = 0;
                return 0;
            }
        }
    }

    if (other->buildMetadata)
    {
        for (size_t i = 0; i < octaspire_vector_get_length(other->buildMetadata); ++i)
        {
            octaspire_string_t * str =
                octaspire_string_new_copy(
                    octaspire_vector_get_element_at_const(other->buildMetadata, i),
                    self->allocator);

            if (!str)
            {
                octaspire_semver_release(self);
                self = 0;
                return 0;
            }

            if (!octaspire_vector_push_back_element(self->buildMetadata, &str))
            {
                octaspire_string_release(str);
                str  = 0;
                octaspire_semver_release(self);
                self = 0;
                return 0;
            }
        }
    }

    return self;
}

octaspire_semver_t *octaspire_semver_new_prerelease(
    size_t                const         major,
    size_t                const         minor,
    size_t                const         patch,
    octaspire_allocator_t       * const allocator,
    ...)
{
    va_list arguments;
    va_start(arguments, allocator);

    octaspire_semver_t * result = octaspire_semver_new_prerelease_va(
        major,
        minor,
        patch,
        allocator,
        arguments);

    va_end(arguments);
    return result;
}

octaspire_semver_t *octaspire_semver_new_prerelease_va(
    size_t                const         major,
    size_t                const         minor,
    size_t                const         patch,
    octaspire_allocator_t       * const allocator,
    va_list                             preRelease)
{
    octaspire_vector_t * const preReleaseVec = octaspire_vector_new(
        sizeof(octaspire_string_t*),
        true,
        (octaspire_vector_element_callback_t)octaspire_string_release,
        allocator);

    if (!preReleaseVec)
    {
        return 0;
    }

    while (true)
    {
        char const * const arg = va_arg(preRelease, char*);

        if (!arg || !strlen(arg))
        {
            break;
        }

        octaspire_string_t * const str =
            octaspire_string_new(arg, allocator);

        if (!arg)
        {
            octaspire_vector_release(preReleaseVec);
            return 0;
        }

        if (!octaspire_vector_push_back_element(
            preReleaseVec,
            &str))
        {
            octaspire_vector_release(preReleaseVec);
            return 0;
        }
    }

    octaspire_semver_t * const result =
        octaspire_semver_new(major, minor, patch, preReleaseVec, 0, allocator);

    octaspire_vector_release(preReleaseVec);
    return result;
}

void octaspire_semver_release(octaspire_semver_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_vector_release(self->preRelease);
    octaspire_vector_release(self->buildMetadata);

    octaspire_allocator_free(self->allocator, self);
}

bool octaspire_semver_add_prerelease(
    octaspire_semver_t * const self,
    char const * const preRelease)
{
    octaspire_string_t * str =
        octaspire_string_new(preRelease, self->allocator);

    if (!str)
    {
        return false;
    }

    octaspire_semver_pre_release_elem_t * preReleaseElem =
        octaspire_semver_pre_release_elem_new(str, self->allocator);

    octaspire_string_release(str);
    str = 0;

    if (!preReleaseElem)
    {
        return false;
    }

    if (!octaspire_vector_push_back_element(
            self->preRelease,
            &preReleaseElem))
    {
        octaspire_semver_pre_release_elem_release(preReleaseElem);
        preReleaseElem = 0;
        return false;
    }

    return true;
}

bool octaspire_semver_add_prerelease_numerical(
    octaspire_semver_t * const self,
    size_t const preRelease)
{
    octaspire_semver_pre_release_elem_t * preReleaseElem =
        octaspire_semver_pre_release_elem_numerical_new(preRelease, self->allocator);

    if (!preReleaseElem)
    {
        return false;
    }

    if (!octaspire_vector_push_back_element(
            self->preRelease,
            &preReleaseElem))
    {
        octaspire_semver_pre_release_elem_release(preReleaseElem);
        preReleaseElem = 0;
        return false;
    }

    return true;
}

bool octaspire_semver_remove_prerelease(
    octaspire_semver_t * const self,
    char const * const prerelease)
{
    for (size_t i = 0;
         i < octaspire_semver_get_num_pre_release_identifiers(self);
         ++i)
    {
        octaspire_semver_pre_release_elem_t const * const elem =
            octaspire_vector_get_element_at_const(self->preRelease, i);

        octaspire_helpers_verify_not_null(elem);

        if (elem->type == OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL)
        {
            if (octaspire_string_is_equal_to_c_string(
                    elem->value.lexical,
                    prerelease))
            {
                if (!octaspire_vector_remove_element_at(self->preRelease, i))
                {
                    return false;
                }
                return true;
            }
        }
    }

    return false;
}

bool octaspire_semver_remove_prerelease_numerical(
    octaspire_semver_t * const self,
    size_t const prerelease)
{
    for (size_t i = 0;
         i < octaspire_semver_get_num_pre_release_identifiers(self);
         ++i)
    {
        octaspire_semver_pre_release_elem_t const * const elem =
            octaspire_vector_get_element_at_const(self->preRelease, i);

        octaspire_helpers_verify_not_null(elem);

        if (elem->type == OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL)
        {
            if (elem->value.numerical == prerelease)
            {
                if (!octaspire_vector_remove_element_at(self->preRelease, i))
                {
                    return false;
                }
                return true;
            }
        }
    }

    return false;
}

bool octaspire_semver_add_buildmetadata(
    octaspire_semver_t * const self,
    char const * const buildMetaData)
{
    octaspire_string_t * str =
        octaspire_string_new(buildMetaData, self->allocator);

    if (!str)
    {
        return false;
    }

    if (!octaspire_vector_push_back_element(self->buildMetadata, &str))
    {
        octaspire_string_release(str);
        str = 0;
        return false;
    }

    return true;
}

octaspire_semver_pre_release_elem_type_t octaspire_semver_get_prerelease_at(
    octaspire_semver_t const * const self,
    size_t const index,
    size_t * outNumerical,
    char const ** outLexical)
{
    if (index >= octaspire_semver_get_num_pre_release_identifiers(self))
    {
        return OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_UNKNOWN;
    }

    octaspire_semver_pre_release_elem_t const * const elem =
        octaspire_vector_get_element_at_const(self->preRelease, index);

    octaspire_helpers_verify_not_null(elem);

    if (elem->type == OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL)
    {
        *outLexical = octaspire_string_get_c_string(elem->value.lexical);
        return OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL;
    }

    *outNumerical = elem->value.numerical;
    return OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL;
}

char const * octaspire_semver_get_build_metadata_at(
    octaspire_semver_t const * const self,
    size_t const index)
{
    if (index >= octaspire_semver_get_num_build_metadata_identifiers(self))
    {
        return 0;
    }

    return octaspire_string_get_c_string(
        octaspire_vector_get_element_at(self->buildMetadata, index));
}

octaspire_string_t * octaspire_semver_to_string(
    octaspire_semver_t const * const self)
{
    octaspire_helpers_verify_not_null(self);

    octaspire_string_t * const result =
        octaspire_string_new_format(
            self->allocator,
            "%zu.%zu.%zu",
            self->major,
            self->minor,
            self->patch);

    for (size_t i = 0; i < octaspire_vector_get_length(self->preRelease); ++i)
    {
        if (i == 0)
        {
            if (!octaspire_string_concatenate_c_string(result, "-"))
            {
                octaspire_string_release(result);
                return 0;
            }
        }

        octaspire_semver_pre_release_elem_t const * const elem =
            octaspire_vector_get_element_at_const(self->preRelease, i);

        octaspire_helpers_verify_not_null(elem);

        switch (elem->type)
        {
            case OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL:
            {
                octaspire_helpers_verify_not_null(elem->value.lexical);

                if (!octaspire_string_concatenate_format(
                        result,
                        "%s%s",
                        octaspire_string_get_c_string(elem->value.lexical),
                        ((i+1) < octaspire_vector_get_length(self->preRelease))
                        ? "." : ""))
                {
                    octaspire_string_release(result);
                    return 0;
                }
            }
            break;

            case OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL:
            {
                if (!octaspire_string_concatenate_format(
                        result,
                        "%zu%s",
                        elem->value.numerical,
                        ((i+1) < octaspire_vector_get_length(self->preRelease))
                        ? "." : ""))
                {
                    octaspire_string_release(result);
                    return 0;
                }
            }
            break;

            case OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_UNKNOWN:
            {
                abort();
            }
            break;
        }
    }

    for (size_t i = 0;
         i < octaspire_vector_get_length(self->buildMetadata);
         ++i)
    {
        if (i == 0)
        {
            if (!octaspire_string_concatenate_c_string(result, "+"))
            {
                octaspire_string_release(result);
                return 0;
            }
        }

        octaspire_string_t const * const elem =
            octaspire_vector_get_element_at_const(self->buildMetadata, i);

        octaspire_helpers_verify_not_null(elem);

        if (!octaspire_string_concatenate_format(
                result,
                "%s%s",
                octaspire_string_get_c_string(elem),
                ((i+1) < octaspire_vector_get_length(self->buildMetadata))
                ? "." : ""))
        {
            octaspire_string_release(result);
            return 0;
        }
    }

    return result;
}

int octaspire_semver_compare(
    octaspire_semver_t const * const self,
    octaspire_semver_t const * const other)
{
    octaspire_helpers_verify_not_null(self);
    octaspire_helpers_verify_not_null(other);

    int diff = self->major - other->major;

    if (diff)
    {
        return (diff < 0) ? -1 : 1;
    }

    diff = self->minor - other->minor;

    if (diff)
    {
        return (diff < 0) ? -1 : 1;
    }

    diff = self->patch - other->patch;

    if (diff)
    {
        return (diff < 0) ? -1 : 1;
    }

    size_t const selfLen =
        octaspire_vector_get_length(self->preRelease);

    size_t const otherLen =
        octaspire_vector_get_length(other->preRelease);

    if (!selfLen)
    {
        if (!otherLen)
        {
            return 0;
        }

        return 1;
    }

    if (!otherLen)
    {
        return -1;
    }

    for (size_t i = 0; i < octaspire_helpers_min_size_t(selfLen, otherLen); ++i)
    {
        octaspire_semver_pre_release_elem_t const * const selfElem =
            octaspire_vector_get_element_at_const(self->preRelease, i);

        octaspire_semver_pre_release_elem_t const * const otherElem =
            octaspire_vector_get_element_at_const(other->preRelease, i);

        if (selfElem->type != otherElem->type)
        {
            return (selfElem->type == OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL)
                ? -1
                :  1;
        }

        switch (selfElem->type)
        {
            case OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL:
            {
                int const diff = octaspire_string_compare(
                    selfElem->value.lexical,
                    otherElem->value.lexical);

                if (diff)
                {
                    return (diff < 0) ? -1 : 1;
                }
            }
            break;

            case OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL:
            {
                int const diff =
                    selfElem->value.numerical - otherElem->value.numerical;

                if (diff)
                {
                    return (diff < 0) ? -1 : 1;
                }
            }
            break;

            case OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_UNKNOWN:
            {
                abort();
            }
            break;
        }
    }

    if (selfLen == otherLen)
    {
        return 0;
    }

    diff = selfLen - otherLen;
    return (diff < 0) ? -1 : 1;
}

bool octaspire_semver_is_smaller_than(
    octaspire_semver_t const * const self,
    octaspire_semver_t const * const other)
{
    return (octaspire_semver_compare(self, other) == -1);
}

bool octaspire_semver_is_smaller_or_equal_to(
    octaspire_semver_t const * const self,
    octaspire_semver_t const * const other)
{
    return (octaspire_semver_compare(self, other) <= 0);
}

bool octaspire_semver_is_greater_than(
    octaspire_semver_t const * const self,
    octaspire_semver_t const * const other)
{
    return (octaspire_semver_compare(self, other) == 1);
}

bool octaspire_semver_is_greater_or_equal_to(
    octaspire_semver_t const * const self,
    octaspire_semver_t const * const other)
{
    return (octaspire_semver_compare(self, other) >= 0);
}

bool octaspire_semver_is_equal_to(
    octaspire_semver_t const * const self,
    octaspire_semver_t const * const other)
{
    return (octaspire_semver_compare(self, other) == 0);
}

bool octaspire_semver_is_equal_to_c_string(
    octaspire_semver_t const * const self,
    char const * const str)
{
    octaspire_string_t * selfAsStr = octaspire_semver_to_string(self);
    octaspire_helpers_verify_not_null(selfAsStr);
    bool const result = octaspire_string_is_equal_to_c_string(selfAsStr, str);
    octaspire_string_release(selfAsStr);
    selfAsStr = 0;
    return result;
}

bool octaspire_semver_is_unequal_to(
    octaspire_semver_t const * const self,
    octaspire_semver_t const * const other)
{
    return (!octaspire_semver_is_equal_to(self, other));
}

size_t octaspire_semver_get_major(
    octaspire_semver_t const * const self)
{
    return self->major;
}

size_t octaspire_semver_get_minor(
    octaspire_semver_t const * const self)
{
    return self->minor;
}

size_t octaspire_semver_get_patch(
    octaspire_semver_t const * const self)
{
    return self->patch;
}

size_t octaspire_semver_get_num_pre_release_identifiers(
    octaspire_semver_t const * const self)
{
    return octaspire_vector_get_length(self->preRelease);
}

size_t octaspire_semver_get_num_build_metadata_identifiers(
    octaspire_semver_t const * const self)
{
    return octaspire_vector_get_length(self->buildMetadata);
}

size_t octaspire_semver_get_length(octaspire_semver_t const * const self)
{
    return 3 +
        octaspire_semver_get_num_pre_release_identifiers(self) +
        octaspire_semver_get_num_build_metadata_identifiers(self);
}

bool octaspire_semver_add_or_subtract(
    octaspire_semver_t       * const self,
    octaspire_semver_t const * const other,
    bool                       const add)
{
    octaspire_helpers_verify_not_null(self);
    octaspire_helpers_verify_not_null(other);

    if (other->major)
    {
        if (other->minor || other->patch)
        {
            return false;
        }

        if (add)
        {
            self->major += other->major;
            self->minor = 0;
            self->patch = 0;
        }
        else
        {
            if (self->major < other->major)
            {
                return false;
            }

            self->major -= other->major;
        }
    }

    if (other->minor)
    {
        if (other->major || other->patch)
        {
            return false;
        }

        if (add)
        {
            self->minor += other->minor;
            self->patch = 0;
        }
        else
        {
            if (self->minor < other->minor)
            {
                return false;
            }

            self->minor -= other->minor;
        }
    }

    if (other->patch)
    {
        if (other->major || other->minor)
        {
            return false;
        }

        if (add)
        {
            self->patch += other->patch;
        }
        else
        {
            if (self->patch < other->patch)
            {
                return false;
            }

            self->patch -= other->patch;
        }
    }

    for (size_t i = 0;
         i < octaspire_semver_get_num_pre_release_identifiers(other);
         ++i)
    {
        size_t outNumerical     = 0;
        char const * outLexical = 0;
        octaspire_semver_pre_release_elem_type_t const type =
            octaspire_semver_get_prerelease_at(other, i, &outNumerical, &outLexical);

        octaspire_helpers_verify_true(type != OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_UNKNOWN);

        switch (type)
        {
        case OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL:
        {
            if (add)
            {
                if (!octaspire_semver_add_prerelease(self, outLexical))
                {
                    return false;
                }
            }
            else
            {
                if (!octaspire_semver_remove_prerelease(self, outLexical))
                {
                    return false;
                }
            }
        }
        break;

        case OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL:
        {
            if (add)
            {
                if (!octaspire_semver_add_prerelease_numerical(self, outNumerical))
                {
                    return false;
                }
            }
            else
            {
                if (!octaspire_semver_remove_prerelease_numerical(self, outNumerical))
                {
                    return false;
                }
            }
        }
        break;

        case OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_UNKNOWN:
        {
            abort();
        }
        break;
        }
    }

    return true;
}

bool octaspire_semver_pop_back(
    octaspire_semver_t * const self)
{
    if (!octaspire_vector_is_empty(self->buildMetadata))
    {
        return octaspire_vector_pop_back_element(self->buildMetadata);
    }

    if (!octaspire_vector_is_empty(self->preRelease))
    {
        return octaspire_vector_pop_back_element(self->preRelease);
    }

    return true;
}

bool octaspire_semver_pop_front(
    octaspire_semver_t * const self)
{
    if (!octaspire_vector_is_empty(self->buildMetadata))
    {
        return octaspire_vector_pop_front_element(self->buildMetadata);
    }

    if (!octaspire_vector_is_empty(self->preRelease))
    {
        return octaspire_vector_pop_front_element(self->preRelease);
    }

    return true;
}

