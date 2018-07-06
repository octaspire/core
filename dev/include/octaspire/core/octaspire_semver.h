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
#ifndef OCTASPIRE_SEMVER_H
#define OCTASPIRE_SEMVER_H

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "octaspire_vector.h"
#include "octaspire_string.h"

#ifdef __cplusplus
extern "C"       {
#endif

typedef enum octaspire_semver_pre_release_elem_type_t
{
    OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_UNKNOWN,
    OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL,
    OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL
}
octaspire_semver_pre_release_elem_type_t;

typedef struct octaspire_semver_pre_release_elem_t
    octaspire_semver_pre_release_elem_t;

void octaspire_semver_pre_release_elem_release(
    octaspire_semver_pre_release_elem_t *self);

octaspire_semver_pre_release_elem_t *octaspire_semver_pre_release_elem_new(
  octaspire_string_t      const * const str,
  octaspire_allocator_t * const allocator);

octaspire_semver_pre_release_elem_t *
octaspire_semver_pre_release_elem_new_copy(
    octaspire_semver_pre_release_elem_t const * const other,
    octaspire_allocator_t * const allocator);

octaspire_semver_pre_release_elem_t *
octaspire_semver_pre_release_elem_numerical_new(
    size_t                  const value,
    octaspire_allocator_t * const allocator);

octaspire_semver_pre_release_elem_type_t
octaspire_semver_pre_release_elem_get_type(
    octaspire_semver_pre_release_elem_t const * const self);

bool octaspire_semver_pre_release_elem_is_lexical_type(
    octaspire_semver_pre_release_elem_t const * const self);

bool octaspire_semver_pre_release_elem_is_numerical_type(
    octaspire_semver_pre_release_elem_t const * const self);

size_t octaspire_semver_pre_release_elem_get_numerical_value(
    octaspire_semver_pre_release_elem_t const * const self);

void octaspire_semver_pre_release_elem_make_numerical(
    octaspire_semver_pre_release_elem_t * const self,
    size_t const value);

bool octaspire_semver_pre_release_elem_make_lexical(
    octaspire_semver_pre_release_elem_t * const self,
    char const * const value);

octaspire_string_t const * octaspire_semver_pre_release_elem_get_lexical_value(
    octaspire_semver_pre_release_elem_t const * const self);

char const * octaspire_semver_pre_release_elem_get_lexical_value_as_c_string(
    octaspire_semver_pre_release_elem_t const * const self);


typedef struct octaspire_semver_t octaspire_semver_t;

octaspire_semver_t *octaspire_semver_new(
    size_t                const         major,
    size_t                const         minor,
    size_t                const         patch,
    octaspire_vector_t    const * const preRelease,
    octaspire_vector_t    const * const buildMetadata,
    octaspire_allocator_t       * const allocator);

octaspire_semver_pre_release_elem_t *
octaspire_semver_pre_release_elem_new_from_c_string(
    char            const * const str,
    octaspire_allocator_t * const allocator);

octaspire_semver_t *octaspire_semver_new_copy(
    octaspire_semver_t    const * const other,
    octaspire_allocator_t       * const allocator);

octaspire_semver_t *octaspire_semver_new_prerelease(
    size_t                const         major,
    size_t                const         minor,
    size_t                const         patch,
    octaspire_allocator_t       * const allocator,
    ...);

octaspire_semver_t *octaspire_semver_new_prerelease_va(
    size_t                const         major,
    size_t                const         minor,
    size_t                const         patch,
    octaspire_allocator_t       * const allocator,
    va_list                             preRelease);

void octaspire_semver_release(octaspire_semver_t *self);

bool octaspire_semver_add_prerelease(
    octaspire_semver_t * const self,
    char const * const preRelease);

bool octaspire_semver_add_prerelease_numerical(
    octaspire_semver_t * const self,
    size_t const preRelease);

bool octaspire_semver_remove_prerelease(
    octaspire_semver_t * const self,
    char const * const prerelease);

bool octaspire_semver_remove_prerelease_numerical(
    octaspire_semver_t * const self,
    size_t const prerelease);

octaspire_semver_pre_release_elem_type_t octaspire_semver_get_prerelease_at(
    octaspire_semver_t const * const self,
    size_t const index,
    size_t * outNumerical,
    char const ** outLexical);

char const * octaspire_semver_get_build_metadata_at(
    octaspire_semver_t const * const self,
    size_t const index);

bool octaspire_semver_add_buildmetadata(
    octaspire_semver_t * const self,
    char const * const buildMetaData);

octaspire_string_t * octaspire_semver_to_string(
    octaspire_semver_t const * const self);

int octaspire_semver_compare(
    octaspire_semver_t const * const self,
    octaspire_semver_t const * const other);

bool octaspire_semver_is_smaller_than(
    octaspire_semver_t const * const self,
    octaspire_semver_t const * const other);

bool octaspire_semver_is_smaller_or_equal_to(
    octaspire_semver_t const * const self,
    octaspire_semver_t const * const other);

bool octaspire_semver_is_greater_than(
    octaspire_semver_t const * const self,
    octaspire_semver_t const * const other);

bool octaspire_semver_is_greater_or_equal_to(
    octaspire_semver_t const * const self,
    octaspire_semver_t const * const other);

bool octaspire_semver_is_equal_to_c_string(
    octaspire_semver_t const * const self,
    char const * const str);

bool octaspire_semver_is_equal_to(
    octaspire_semver_t const * const self,
    octaspire_semver_t const * const other);

bool octaspire_semver_is_unequal_to(
    octaspire_semver_t const * const self,
    octaspire_semver_t const * const other);

size_t octaspire_semver_get_major(
    octaspire_semver_t const * const self);

size_t octaspire_semver_get_minor(
    octaspire_semver_t const * const self);

size_t octaspire_semver_get_patch(
    octaspire_semver_t const * const self);

size_t octaspire_semver_get_num_pre_release_identifiers(
    octaspire_semver_t const * const self);

size_t octaspire_semver_get_num_build_metadata_identifiers(
    octaspire_semver_t const * const self);

size_t octaspire_semver_get_length(octaspire_semver_t const * const self);

bool octaspire_semver_add_or_subtract(
    octaspire_semver_t       * const self,
    octaspire_semver_t const * const other,
    bool                       const add);

bool octaspire_semver_pop_back(
    octaspire_semver_t * const self);

bool octaspire_semver_pop_front(
    octaspire_semver_t * const self);

#ifdef __cplusplus
/* extern "C" */ }
#endif

#endif

