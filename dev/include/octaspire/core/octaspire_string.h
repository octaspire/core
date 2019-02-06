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
#ifndef OCTASPIRE_STRING_H
#define OCTASPIRE_STRING_H

#include <stdarg.h>
#include <stdlib.h>
#include "octaspire_utf8.h"
#include "octaspire_vector.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    OCTASPIRE_STRING_ERROR_STATUS_OK,
    OCTASPIRE_STRING_ERROR_STATUS_ENCODING_ERROR,
    OCTASPIRE_STRING_ERROR_STATUS_DECODING_ERROR
}
octaspire_string_error_status_t;

typedef struct octaspire_string_t octaspire_string_t;

octaspire_string_t *octaspire_string_new(
    char const * const str,
    octaspire_allocator_t *allocator);

octaspire_string_t *octaspire_string_new_from_buffer(
    char const * const buffer,
    size_t const lengthInOctets,
    octaspire_allocator_t *allocator);

octaspire_string_t *octaspire_string_new_format(
    octaspire_allocator_t *allocator,
    char const * const fmt,
    ...);

octaspire_string_t *octaspire_string_new_vformat(
    octaspire_allocator_t *allocator,
    char const * const fmt,
    va_list arguments);

octaspire_string_t *octaspire_string_new_copy(
    octaspire_string_t const * const other,
    octaspire_allocator_t *allocator);

octaspire_string_t *octaspire_string_new_substring_from_given_index_and_length(
    octaspire_string_t const * const other,
    octaspire_allocator_t *allocator,
    size_t const ucsCharStartIndex,
    size_t const lengthInUcsChars);

void octaspire_string_release(octaspire_string_t *self);

bool octaspire_string_set_from_c_string(
    octaspire_string_t * const self,
    char const * const str);

bool octaspire_string_is_empty(
    octaspire_string_t const * const self);

size_t octaspire_string_get_length_in_ucs_characters(
    octaspire_string_t const * const self);

size_t octaspire_string_get_length_in_octets(
    octaspire_string_t const * const self);

bool octaspire_string_is_index_valid(
    octaspire_string_t const * const self,
    ptrdiff_t const possiblyNegativeIndex);

uint32_t octaspire_string_get_ucs_character_at_index(
    octaspire_string_t const * const self,
    ptrdiff_t const possiblyNegativeIndex);

char const * octaspire_string_get_c_string(
    octaspire_string_t const * const self);

bool octaspire_string_is_error(
    octaspire_string_t const * const self);

octaspire_string_error_status_t octaspire_string_get_error_status(
    octaspire_string_t const * const self);

size_t octaspire_string_get_error_position_in_octets(
    octaspire_string_t const * const self);

void octaspire_string_reset_error_status(
    octaspire_string_t * const self);

bool octaspire_string_concatenate(
    octaspire_string_t * const self,
    octaspire_string_t const * const other);

bool octaspire_string_concatenate_c_string(
    octaspire_string_t * const self,
    char const * const str);

bool octaspire_string_concatenate_format(
    octaspire_string_t * const self,
    char const * const fmt,
    ...);

ptrdiff_t octaspire_string_find_first_substring(
    octaspire_string_t const * const self,
    ptrdiff_t const startFromIndexPossiblyNegative,
    octaspire_string_t const * const substring);

bool octaspire_string_remove_character_at(
    octaspire_string_t * const self,
    ptrdiff_t const possiblyNegativeIndex);

size_t octaspire_string_remove_characters_at(
    octaspire_string_t * const self,
    ptrdiff_t const startFromIndexPossiblyNegative,
    size_t const numCharacters);

size_t octaspire_string_remove_all_substrings(
    octaspire_string_t * const self,
    octaspire_string_t const * const substring);

bool octaspire_string_clear(
    octaspire_string_t * const self);

bool octaspire_string_is_equal(
    octaspire_string_t const * const self,
    octaspire_string_t const * const other);

bool octaspire_string_is_equal_to_c_string(
    octaspire_string_t const * const self,
    char const * const str);

size_t octaspire_string_levenshtein_distance(
    octaspire_string_t const * const self,
    octaspire_string_t const * const other);

int octaspire_string_compare(
    octaspire_string_t const * const self,
    octaspire_string_t const * const other);

int octaspire_string_compare_to_c_string(
    octaspire_string_t const * const self,
    char const * const str);

bool octaspire_string_starts_with(
    octaspire_string_t const * const self,
    octaspire_string_t const * const other);

bool octaspire_string_starts_with_c_string(
    octaspire_string_t const * const self,
    char const * const str);

bool octaspire_string_ends_with(
    octaspire_string_t const * const self,
    octaspire_string_t const * const other);

bool octaspire_string_ends_with_c_string(
    octaspire_string_t const * const self,
    char const * const str);

uint32_t octaspire_string_get_hash(
    octaspire_string_t const * const self);

bool octaspire_string_push_back_ucs_character(
    octaspire_string_t *self,
    uint32_t const character);

bool octaspire_string_pop_front_ucs_character(
    octaspire_string_t *self);

bool octaspire_string_pop_back_ucs_character(
    octaspire_string_t *self);

bool octaspire_string_insert_string_to(
    octaspire_string_t * const self,
    octaspire_string_t const * const str,
    ptrdiff_t const indexToPutFirstCharacterPossiblyNegative);

bool octaspire_string_overwrite_with_string_at(
    octaspire_string_t * const self,
    octaspire_string_t const * const str,
    ptrdiff_t const indexToPutFirstCharacterPossiblyNegative);

octaspire_vector_t *octaspire_string_split(
    octaspire_string_t *self,
    char const * const delimiter);

// TODO make API consistent, now this differs from find_char below
bool octaspire_string_contains_char(
    octaspire_string_t const * const self,
    uint32_t const character);

bool octaspire_string_contains_only_these_chars(
    octaspire_string_t const * const self,
    octaspire_string_t const * const chars);

bool octaspire_string_contains_only_these_chars_c_string(
    octaspire_string_t const * const self,
    char const * const chars);

octaspire_vector_t *octaspire_string_find_char(
    octaspire_string_t const * const self,
    octaspire_string_t const * const character,
    ptrdiff_t const characterIndexPossiblyNegative);

octaspire_vector_t *octaspire_string_find_string(
    octaspire_string_t const * const self,
    octaspire_string_t const * const str,
    ptrdiff_t const strStartIndexPossiblyNegative,
    size_t const strLength);

#ifdef __cplusplus
}
#endif

#endif

