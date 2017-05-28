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
*******************************************************************************

  This file is amalgamated version of the header files, implementation files
  and unit tests of Octaspire Core. It is created automatically by a script.

                            DO NOT EDIT MANUALLY!

  Edit the separate .h and .c files in the source distribution and then let
  the script create this file again with the modifications.

******************************************************************************/
#ifndef OCTASPIRE_CORE_AMALGAMATED_H
#define OCTASPIRE_CORE_AMALGAMATED_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <assert.h>
#include <limits.h>
#include <inttypes.h>
#include <math.h>
#include <wchar.h>



#define OCTASPIRE_CORE_CONFIG_TEST_RES_PATH ""


#ifdef OCTASPIRE_CORE_AMALGAMATED_UNIT_TEST_IMPLEMENTATION
#define OCTASPIRE_CORE_AMALGAMATED_IMPLEMENTATION 1
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../external/murmur3.h
//////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the
// public domain. The author hereby disclaims copyright to this source
// code.

#ifndef OCTASPIRE_CORE_MURMURHASH3_H_
#define OCTASPIRE_CORE_MURMURHASH3_H_


#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------

void MurmurHash3_x86_32 (const void *key, int len, uint32_t seed, void *out);

void MurmurHash3_x86_128(const void *key, int len, uint32_t seed, void *out);

void MurmurHash3_x64_128(const void *key, int len, uint32_t seed, void *out);

//-----------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif // OCTASPIRE_CORE_MURMURHASH3_H_
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../external/murmur3.h
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../build/include/octaspire/core/octaspire_core_config.h
//////////////////////////////////////////////////////////////////////////////////////////////////
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
#ifndef OCTASPIRE_CORE_CONFIG_H
#define OCTASPIRE_CORE_CONFIG_H

#define OCTASPIRE_CORE_CONFIG_VERSION_MAJOR "0"
#define OCTASPIRE_CORE_CONFIG_VERSION_MINOR "34"
#define OCTASPIRE_CORE_CONFIG_VERSION_PATCH "1"

#define OCTASPIRE_CORE_CONFIG_VERSION_STR   "Octaspire Core version 0.34.1"



//#define OCTASPIRE_CORE_CONFIG_MEMORY_ALLOCATOR_REGION_MIN_BLOCK_SIZE_IN_OCTETS 10485800
#define OCTASPIRE_CORE_CONFIG_MEMORY_ALLOCATOR_REGION_MIN_BLOCK_SIZE_IN_OCTETS 104858000

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../build/include/octaspire/core/octaspire_core_config.h
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../include/octaspire/core/octaspire_utf8.h
//////////////////////////////////////////////////////////////////////////////////////////////////
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
#ifndef OCTASPIRE_UTF8_H
#define OCTASPIRE_UTF8_H


#ifdef __cplusplus
extern "C" {
#endif

typedef enum octaspire_utf8_decode_status_t
{
    OCTASPIRE_UTF8_DECODE_STATUS_OK = 0,
    OCTASPIRE_UTF8_DECODE_STATUS_INPUT_IS_NULL,
    OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
    OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER,
    OCTASPIRE_UTF8_DECODE_STATUS_INPUT_NOT_ENOUGH_OCTETS_AVAILABLE
}
octaspire_utf8_decode_status_t;

typedef enum octaspire_utf8_encode_status_t
{
    OCTASPIRE_UTF8_ENCODE_STATUS_OK = 0,
    OCTASPIRE_UTF8_ENCODE_STATUS_ILLEGAL_CHARACTER_NUMBER
}
octaspire_utf8_encode_status_t;

typedef struct octaspire_utf8_character_t
{
    size_t        numoctets;
    unsigned char octets[4];
    char          padding[4];
}
octaspire_utf8_character_t;

octaspire_utf8_encode_status_t octaspire_utf8_encode_character(
    uint32_t const character,
    octaspire_utf8_character_t *result);

octaspire_utf8_decode_status_t octaspire_utf8_decode_character(
    char const * const text,
    size_t const textLengthInOctets,
    uint32_t *result,
    int *numoctets);

octaspire_utf8_decode_status_t octaspire_utf8_decode_character_from_buffer(
    char const * const buffer,
    size_t const bufferLengthInOctets,
    size_t const currentIndex,
    uint32_t *result,
    int *numoctets);

#ifdef __cplusplus
}
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../include/octaspire/core/octaspire_utf8.h
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../include/octaspire/core/octaspire_memory.h
//////////////////////////////////////////////////////////////////////////////////////////////////
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
#ifndef OCTASPIRE_MEMORY_H
#define OCTASPIRE_MEMORY_H


#ifdef __cplusplus
extern "C" {
#endif

struct octaspire_region_t;
typedef struct octaspire_memory_allocator_t octaspire_memory_allocator_t;

octaspire_memory_allocator_t *octaspire_memory_allocator_new_create_region(size_t const minBlockSizeInOctets);
octaspire_memory_allocator_t *octaspire_memory_allocator_new(struct octaspire_region_t *region);

void octaspire_memory_allocator_release(octaspire_memory_allocator_t *self);

void *octaspire_memory_allocator_malloc(
    octaspire_memory_allocator_t *self,
    size_t const size);

void *octaspire_memory_allocator_realloc(
    octaspire_memory_allocator_t *self,
    void *ptr, size_t const size);

void octaspire_memory_allocator_free(
    octaspire_memory_allocator_t *self,
    void *ptr);

void octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
    octaspire_memory_allocator_t *self,
    size_t const count,
    uint32_t const bitQueue0);

void octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged_when_larger_than_32(
    octaspire_memory_allocator_t *self,
    size_t const count,
    uint32_t const bitQueue0,
    uint32_t const bitQueue1,
    uint32_t const bitQueue2,
    uint32_t const bitQueue3,
    uint32_t const bitQueue4,
    uint32_t const bitQueue5,
    uint32_t const bitQueue6,
    uint32_t const bitQueue7,
    uint32_t const bitQueue8,
    uint32_t const bitQueue9,
    uint32_t const bitQueue10,
    uint32_t const bitQueue11,
    uint32_t const bitQueue12,
    uint32_t const bitQueue13,
    uint32_t const bitQueue14,
    uint32_t const bitQueue15,
    uint32_t const bitQueue16,
    uint32_t const bitQueue17,
    uint32_t const bitQueue18,
    uint32_t const bitQueue19);

size_t octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(
    octaspire_memory_allocator_t const * const self);

#ifdef __cplusplus
}
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../include/octaspire/core/octaspire_memory.h
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../include/octaspire/core/octaspire_region.h
//////////////////////////////////////////////////////////////////////////////////////////////////
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
#ifndef OCTASPIRE_REGION_H
#define OCTASPIRE_REGION_H


#ifdef __cplusplus
extern "C" {
#endif

typedef struct octaspire_region_t octaspire_region_t;

octaspire_region_t *octaspire_region_new(size_t const minBlockSizeInOctets);

void octaspire_region_release(octaspire_region_t *self);

void *octaspire_region_malloc(
    octaspire_region_t *self,
    size_t const size);

void *octaspire_region_realloc(
    octaspire_region_t *self,
    void *ptr, size_t const size);

void octaspire_region_free(
    octaspire_region_t *self,
    void *ptr);

void octaspire_region_compact(octaspire_region_t *self);

void octaspire_region_print(octaspire_region_t const * const self);

#ifdef __cplusplus
}
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../include/octaspire/core/octaspire_region.h
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../include/octaspire/core/octaspire_container_vector.h
//////////////////////////////////////////////////////////////////////////////////////////////////
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
#ifndef OCTASPIRE_CONTAINER_VECTOR_H
#define OCTASPIRE_CONTAINER_VECTOR_H


#ifdef __cplusplus
extern "C" {
#endif

typedef struct octaspire_container_vector_t octaspire_container_vector_t;

typedef void  (*octaspire_container_vector_element_callback_t)(void *element);

typedef int (*octaspire_container_vector_element_compare_function_t)(void const *a, void const *b);

octaspire_container_vector_t *octaspire_container_vector_new(
    size_t const elementSize,
    bool const elementIsPointer,
    octaspire_container_vector_element_callback_t elementReleaseCallback,
    octaspire_memory_allocator_t *allocator);

octaspire_container_vector_t *octaspire_container_vector_new_with_preallocated_elements(
    size_t const elementSize,
    bool const elementIsPointer,
    size_t const numElementsPreAllocated,
    octaspire_container_vector_element_callback_t elementReleaseCallback,
    octaspire_memory_allocator_t *allocator);

octaspire_container_vector_t *octaspire_container_vector_new_shallow_copy(
    octaspire_container_vector_t * other,
    octaspire_memory_allocator_t * allocator);

void octaspire_container_vector_release(octaspire_container_vector_t *self);

// Vector can never be compacted smaller than this limit, if set
void octaspire_container_vector_set_compacting_limit_for_preallocated_elements(
    octaspire_container_vector_t * const self,
    size_t const numPreAllocatedElementsAtLeastPresentAtAnyMoment);

size_t octaspire_container_vector_get_length(
    octaspire_container_vector_t const * const self);

size_t octaspire_container_vector_get_length_in_octets(
    octaspire_container_vector_t const * const self);

bool octaspire_container_vector_is_empty(
    octaspire_container_vector_t const * const self);

bool octaspire_container_vector_remove_element_at(
    octaspire_container_vector_t * const self,
    size_t const index);

void *octaspire_container_vector_get_element_at(
    octaspire_container_vector_t * const self,
    size_t const index);

void const *octaspire_container_vector_get_element_at_const(
    octaspire_container_vector_t const * const self,
    size_t const index);

size_t octaspire_container_vector_get_element_size_in_octets(
    octaspire_container_vector_t const * const self);

bool octaspire_container_vector_insert_element_before_the_element_at_index(
    octaspire_container_vector_t *self,
    void const *element,
    ptrdiff_t const index);

bool octaspire_container_vector_insert_element_at(
    octaspire_container_vector_t * const self,
    void const * const element,
    size_t const index);

bool octaspire_container_vector_replace_element_at(
    octaspire_container_vector_t *self,
    size_t const index,
    void const *element);

bool octaspire_container_vector_push_front_element(
    octaspire_container_vector_t *self,
    void const *element);

bool octaspire_container_vector_push_back_element(
    octaspire_container_vector_t * const self,
    void const * const element);

bool octaspire_container_vector_push_back_char(
    octaspire_container_vector_t *self,
    char const element);

void octaspire_container_vector_for_each(
    octaspire_container_vector_t *self,
    octaspire_container_vector_element_callback_t callback);

bool octaspire_container_vector_pop_back_element(
    octaspire_container_vector_t *self);

void *octaspire_container_vector_peek_back_element(
    octaspire_container_vector_t *self);

void const * octaspire_container_vector_peek_back_element_const(
    octaspire_container_vector_t const * const self);

bool octaspire_container_vector_pop_front_element(
    octaspire_container_vector_t *self);

void *octaspire_container_vector_peek_front_element(
    octaspire_container_vector_t *self);

void const * octaspire_container_vector_peek_front_element_const(
    octaspire_container_vector_t const * const self);

octaspire_container_vector_element_callback_t
octaspire_container_vector_get_element_release_callback_const(
    octaspire_container_vector_t const * const self);

bool octaspire_container_vector_clear(
    octaspire_container_vector_t * const self);

void octaspire_container_vector_sort(
    octaspire_container_vector_t * const self,
    octaspire_container_vector_element_compare_function_t elementCompareFunction);

bool octaspire_container_vector_is_valid_index(
    octaspire_container_vector_t const * const self,
    ptrdiff_t const index);

#ifdef __cplusplus
}
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../include/octaspire/core/octaspire_container_vector.h
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../include/octaspire/core/octaspire_container_utf8_string.h
//////////////////////////////////////////////////////////////////////////////////////////////////
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
#ifndef OCTASPIRE_CONTAINER_UTF8_STRING_H
#define OCTASPIRE_CONTAINER_UTF8_STRING_H


#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK,
    OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_ENCODING_ERROR,
    OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_DECODING_ERROR
}
octaspire_container_utf8_string_error_status_t;

typedef struct octaspire_container_utf8_string_t octaspire_container_utf8_string_t;

octaspire_container_utf8_string_t *octaspire_container_utf8_string_new(
    char const * const str,
    octaspire_memory_allocator_t *allocator);

octaspire_container_utf8_string_t *octaspire_container_utf8_string_new_from_buffer(
    char const * const buffer,
    size_t const lengthInOctets,
    octaspire_memory_allocator_t *allocator);

octaspire_container_utf8_string_t *octaspire_container_utf8_string_new_format(
    octaspire_memory_allocator_t *allocator,
    char const * const fmt,
    ...);

octaspire_container_utf8_string_t *octaspire_container_utf8_string_new_vformat(
    octaspire_memory_allocator_t *allocator,
    char const * const fmt,
    va_list arguments);

octaspire_container_utf8_string_t *octaspire_container_utf8_string_new_copy(
    octaspire_container_utf8_string_t const * const other,
    octaspire_memory_allocator_t *allocator);

octaspire_container_utf8_string_t *octaspire_container_utf8_string_new_substring_from_given_index_and_length(
    octaspire_container_utf8_string_t const * const other,
    octaspire_memory_allocator_t *allocator,
    size_t const ucsCharStartIndex,
    size_t const lengthInUcsChars);

void octaspire_container_utf8_string_release(octaspire_container_utf8_string_t *self);

bool octaspire_container_utf8_string_is_empty(
    octaspire_container_utf8_string_t const * const self);

size_t octaspire_container_utf8_string_get_length_in_ucs_characters(
    octaspire_container_utf8_string_t const * const self);

size_t octaspire_container_utf8_string_get_length_in_octets(
    octaspire_container_utf8_string_t const * const self);

uint32_t octaspire_container_utf8_string_get_ucs_character_at_index(
    octaspire_container_utf8_string_t const * const self, size_t const index);

char const * octaspire_container_utf8_string_get_c_string(
    octaspire_container_utf8_string_t const * const self);

bool octaspire_container_utf8_string_is_error(
    octaspire_container_utf8_string_t const * const self);

octaspire_container_utf8_string_error_status_t octaspire_container_utf8_string_get_error_status(
    octaspire_container_utf8_string_t const * const self);

size_t octaspire_container_utf8_string_get_error_position_in_octets(
    octaspire_container_utf8_string_t const * const self);

void octaspire_container_utf8_string_reset_error_status(
    octaspire_container_utf8_string_t * const self);

bool octaspire_container_utf8_string_concatenate(
    octaspire_container_utf8_string_t * const self,
    octaspire_container_utf8_string_t const * const other);

bool octaspire_container_utf8_string_concatenate_c_string(
    octaspire_container_utf8_string_t * const self,
    char const * const str);

bool octaspire_container_utf8_string_concatenate_format(
    octaspire_container_utf8_string_t * const self,
    char const * const fmt,
    ...);

ptrdiff_t octaspire_container_utf8_string_find_first_substring(
    octaspire_container_utf8_string_t const * const self,
    size_t const startFromIndex,
    octaspire_container_utf8_string_t const * const substring);

bool octaspire_container_utf8_string_remove_character_at(
    octaspire_container_utf8_string_t * const self,
    size_t const index);

size_t octaspire_container_utf8_string_remove_characters_at(
    octaspire_container_utf8_string_t * const self,
    size_t const startFromIndex,
    size_t const numCharacters);

size_t octaspire_container_utf8_string_remove_all_substrings(
    octaspire_container_utf8_string_t * const self,
    octaspire_container_utf8_string_t const * const substring);

bool octaspire_container_utf8_string_clear(
    octaspire_container_utf8_string_t * const self);

bool octaspire_container_utf8_string_is_equal(
    octaspire_container_utf8_string_t const * const self,
    octaspire_container_utf8_string_t const * const other);

bool octaspire_container_utf8_string_is_equal_to_c_string(
    octaspire_container_utf8_string_t const * const self,
    char const * const str);

bool octaspire_container_utf8_string_starts_with(
    octaspire_container_utf8_string_t const * const self,
    octaspire_container_utf8_string_t const * const other);

bool octaspire_container_utf8_string_ends_with(
    octaspire_container_utf8_string_t const * const self,
    octaspire_container_utf8_string_t const * const other);

uint32_t octaspire_container_utf8_string_get_hash(
    octaspire_container_utf8_string_t const * const self);

bool octaspire_container_utf8_string_push_back_ucs_character(
    octaspire_container_utf8_string_t *self,
    uint32_t const character);

bool octaspire_container_utf8_string_pop_back_ucs_character(
    octaspire_container_utf8_string_t *self);

bool octaspire_container_utf8_string_insert_string_to(
    octaspire_container_utf8_string_t * const self,
    octaspire_container_utf8_string_t const * const str,
    ptrdiff_t const indexToPutFirstCharacter);

octaspire_container_vector_t *octaspire_container_utf8_string_split(
    octaspire_container_utf8_string_t *self,
    char const * const delimiter);

// TODO make API yhtenäinen, nyt this differs from find_char below
bool octaspire_container_utf8_string_contains_char(
    octaspire_container_utf8_string_t const * const self,
    uint32_t const character);

bool octaspire_container_utf8_string_contains_only_these_chars(
    octaspire_container_utf8_string_t const * const self,
    octaspire_container_utf8_string_t const * const chars);

octaspire_container_vector_t *octaspire_container_utf8_string_find_char(
    octaspire_container_utf8_string_t const * const self,
    octaspire_container_utf8_string_t const * const character,
    size_t const characterIndex);

octaspire_container_vector_t *octaspire_container_utf8_string_find_string(
    octaspire_container_utf8_string_t const * const self,
    octaspire_container_utf8_string_t const * const str,
    size_t const strStartIndex,
    size_t const strLength);

#ifdef __cplusplus
}
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../include/octaspire/core/octaspire_container_utf8_string.h
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../include/octaspire/core/octaspire_container_pair.h
//////////////////////////////////////////////////////////////////////////////////////////////////
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
#ifndef OCTASPIRE_CONTAINER_PAIR_H
#define OCTASPIRE_CONTAINER_PAIR_H


#ifdef __cplusplus
extern "C"
{
#endif

typedef struct octaspire_container_pair_t octaspire_container_pair_t;

typedef void (*octaspire_container_pair_element_callback_t)(void *element);

size_t octaspire_container_pair_t_get_sizeof(void);

octaspire_container_pair_t *octaspire_container_pair_new(
    size_t const firstElementSize,
    bool firstElementIsPointer,
    size_t const secondElementSize,
    bool secondElementIsPointer,
    octaspire_container_pair_element_callback_t firstElementReleaseCallback,
    octaspire_container_pair_element_callback_t secondElementReleaseCallback,
    octaspire_memory_allocator_t *allocator);

octaspire_container_pair_t *octaspire_container_pair_new_shallow_copy(
    octaspire_container_pair_t   *other,
    octaspire_memory_allocator_t *allocator);

void octaspire_container_pair_release(octaspire_container_pair_t *self);

void *octaspire_container_pair_get_first(octaspire_container_pair_t *self);

void const *octaspire_container_pair_get_first_const(octaspire_container_pair_t const * const self);

void *octaspire_container_pair_get_second(octaspire_container_pair_t *self);

void const *octaspire_container_pair_get_second_const(
    octaspire_container_pair_t const * const self);

size_t octaspire_container_pair_get_size_of_first_element_in_octets(
    octaspire_container_pair_t const * const self);

size_t octaspire_container_pair_get_size_of_second_element_in_octets(
    octaspire_container_pair_t const * const self);

void octaspire_container_pair_set(
    octaspire_container_pair_t *self,
    void const *first,
    void const *second);

void octaspire_container_pair_set_first(
    octaspire_container_pair_t *self,
    void const *first);

void octaspire_container_pair_set_second(
    octaspire_container_pair_t *self,
    void const *second);

bool octaspire_container_pair_set_first_to_void_pointer(
    octaspire_container_pair_t *self,
    void *element);

bool octaspire_container_pair_set_second_to_void_pointer(
    octaspire_container_pair_t *self,
    void *second);

void octaspire_container_pair_clear(
    octaspire_container_pair_t * const self);

#ifdef __cplusplus
}
#endif

#endif
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../include/octaspire/core/octaspire_container_pair.h
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../include/octaspire/core/octaspire_stdio.h
//////////////////////////////////////////////////////////////////////////////////////////////////
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
#ifndef OCTASPIRE_STDIO_H
#define OCTASPIRE_STDIO_H


#ifdef __cplusplus
extern "C" {
#endif

typedef struct octaspire_stdio_t octaspire_stdio_t;

octaspire_stdio_t *octaspire_stdio_new(octaspire_memory_allocator_t *allocator);

void octaspire_stdio_release(octaspire_stdio_t *self);

size_t octaspire_stdio_fread(
    octaspire_stdio_t *self,
    void *ptr,
    size_t const size,
    size_t const nmemb,
    FILE *stream);

void octaspire_stdio_set_number_and_type_of_future_reads_to_be_rigged(
    octaspire_stdio_t *self,
    size_t const count,
    uint32_t const bitQueue);

size_t octaspire_stdio_get_number_of_future_reads_to_be_rigged(
    octaspire_stdio_t const * const self);

octaspire_container_utf8_string_t *octaspire_stdio_read_line(octaspire_stdio_t *self, FILE *stream);

#ifdef __cplusplus
}
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../include/octaspire/core/octaspire_stdio.h
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../include/octaspire/core/octaspire_input.h
//////////////////////////////////////////////////////////////////////////////////////////////////
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
#ifndef OCTASPIRE_INPUT_H
#define OCTASPIRE_INPUT_H


#ifdef __cplusplus
extern "C" {
#endif

typedef struct octaspire_input_t octaspire_input_t;

octaspire_input_t *octaspire_input_new_from_c_string(
    char const * const str,
    octaspire_memory_allocator_t *allocator);

octaspire_input_t *octaspire_input_new_from_buffer(
    char const * const buffer,
    size_t const lengthInOctets,
    octaspire_memory_allocator_t *allocator);

octaspire_input_t *octaspire_input_new_from_path(
    char const * const path,
    octaspire_memory_allocator_t *octaspireAllocator,
    octaspire_stdio_t *octaspireStdio);

void octaspire_input_release(octaspire_input_t *self);

size_t octaspire_input_get_length_in_ucs_characters(octaspire_input_t const * const self);

void   octaspire_input_clear(octaspire_input_t *self);

void   octaspire_input_rewind(octaspire_input_t *self);

uint32_t octaspire_input_peek_next_ucs_character(octaspire_input_t *self);
uint32_t octaspire_input_peek_next_next_ucs_character(octaspire_input_t *self);

bool octaspire_input_pop_next_ucs_character(octaspire_input_t *self);

bool octaspire_input_is_good(octaspire_input_t const * const self);

bool octaspire_input_push_back_from_string(
    octaspire_input_t * const self,
    octaspire_container_utf8_string_t const * const str);

bool octaspire_input_push_back_from_c_string(octaspire_input_t * const self, char const * const str);

size_t octaspire_input_get_line_number(octaspire_input_t const * const self);
size_t octaspire_input_get_column_number(octaspire_input_t const * const self);
size_t octaspire_input_get_ucs_character_index(octaspire_input_t const * const self);

void octaspire_input_print(octaspire_input_t const * const self);

#ifdef __cplusplus
}
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../include/octaspire/core/octaspire_input.h
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../include/octaspire/core/octaspire_container_hash_map.h
//////////////////////////////////////////////////////////////////////////////////////////////////
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
#ifndef OCTASPIRE_CONTAINER_HASH_MAP_H
#define OCTASPIRE_CONTAINER_HASH_MAP_H


#ifdef __cplusplus
extern "C"
{
#endif

// Hash map element
typedef struct octaspire_container_hash_map_element_t octaspire_container_hash_map_element_t;

octaspire_container_hash_map_element_t *octaspire_container_hash_map_element_new(
    uint32_t const hash,
    size_t const keySizeInOctets,
    bool const keyIsPointer,
    void const * const key,
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    void const * const value,
    octaspire_memory_allocator_t * const allocator);

void octaspire_container_hash_map_element_release(octaspire_container_hash_map_element_t *self);

uint32_t octaspire_container_hash_map_element_get_hash(
    octaspire_container_hash_map_element_t const * const self);

void *octaspire_container_hash_map_element_get_key(
    octaspire_container_hash_map_element_t const * const self);

octaspire_container_vector_t *octaspire_container_hash_map_element_get_values(
    octaspire_container_hash_map_element_t * const self);

void *octaspire_container_hash_map_element_get_value(
    octaspire_container_hash_map_element_t const * const self);

// Hash map
typedef struct octaspire_container_hash_map_t octaspire_container_hash_map_t;

typedef bool (*octaspire_container_hash_map_key_compare_function_t)(
    void const * const key1,
    void const * const key2);

typedef uint32_t (*octaspire_container_hash_map_key_hash_function_t)(
    void const * const key);

typedef void (*octaspire_container_hash_map_element_callback_function_t)(
    void * element);

octaspire_container_hash_map_t *octaspire_container_hash_map_new(
    size_t const keySizeInOctets,
    bool const keyIsPointer,
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    octaspire_container_hash_map_key_compare_function_t keyCompareFunction,
    octaspire_container_hash_map_key_hash_function_t keyHashFunction,
    octaspire_container_hash_map_element_callback_function_t keyReleaseCallback,
    octaspire_container_hash_map_element_callback_function_t valueReleaseCallback,
    octaspire_memory_allocator_t *allocator);

octaspire_container_hash_map_t *octaspire_container_hash_map_new_with_octaspire_container_utf8_string_keys(
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    octaspire_container_hash_map_element_callback_function_t valueReleaseCallback,
    octaspire_memory_allocator_t *allocator);

void octaspire_container_hash_map_release(octaspire_container_hash_map_t *self);

bool octaspire_container_hash_map_remove(
    octaspire_container_hash_map_t *self,
    uint32_t const hash,
    void const * const key);

bool octaspire_container_hash_map_clear(
    octaspire_container_hash_map_t * const self);

bool octaspire_container_hash_map_add_hash_map(
    octaspire_container_hash_map_t * const self,
    octaspire_container_hash_map_t * const other);

bool octaspire_container_hash_map_put(
    octaspire_container_hash_map_t *self,
    uint32_t const hash,
    void const * const key,
    void const * const value);

octaspire_container_hash_map_element_t *octaspire_container_hash_map_get(
    octaspire_container_hash_map_t *self,
    uint32_t const hash,
    void const * const key);

octaspire_container_hash_map_element_t const * octaspire_container_hash_map_get_const(
    octaspire_container_hash_map_t const * const self,
    uint32_t const hash,
    void const * const key);

size_t octaspire_container_hash_map_get_number_of_elements(
    octaspire_container_hash_map_t const * const self);

octaspire_container_hash_map_element_t *octaspire_container_hash_map_get_at_index(
    octaspire_container_hash_map_t *self,
    size_t const index);

typedef struct octaspire_container_hash_map_element_iterator_t
{
    octaspire_container_hash_map_t *hashMap;
    octaspire_container_hash_map_element_t *element;
    size_t bucketIndex;
    size_t elementInsideBucketIndex;
}
octaspire_container_hash_map_element_iterator_t;

octaspire_container_hash_map_element_iterator_t octaspire_container_hash_map_element_iterator_init(
    octaspire_container_hash_map_t * const self);

bool octaspire_container_hash_map_element_iterator_next(
    octaspire_container_hash_map_element_iterator_t * const self);

#ifdef __cplusplus
}
#endif

#endif
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../include/octaspire/core/octaspire_container_hash_map.h
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../include/octaspire/core/octaspire_helpers.h
//////////////////////////////////////////////////////////////////////////////////////////////////
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
#ifndef OCTASPIRE_HELPERS_H
#define OCTASPIRE_HELPERS_H


#ifdef __cplusplus
extern "C" {
#endif

#define OCTASPIRE_HELPERS_UNUSED_PARAMETER(x) (void)(x)
#define OCTASPIRE_HELPERS_MURMUR3_HASH_SEED 0xFF00FF00

bool  octaspire_helpers_test_bit(uint32_t const bitSet, size_t const index);

char *octaspire_helpers_path_to_buffer(
    char const * const path,
    size_t *octetsAllocated,
    octaspire_memory_allocator_t *allocator,
    octaspire_stdio_t *stdio);

uint32_t octaspire_helpers_calculate_murmur3_hash_for_size_t_argument(size_t const value);
uint32_t octaspire_helpers_calculate_murmur3_hash_for_bool_argument(bool const value);
uint32_t octaspire_helpers_calculate_murmur3_hash_for_int32_t_argument(int32_t const value);
uint32_t octaspire_helpers_calculate_murmur3_hash_for_double_argument(double const value);
uint32_t octaspire_helpers_calculate_murmur3_hash_for_void_pointer_argument(void const * const value);

size_t octaspire_helpers_character_digit_to_number(uint32_t const c);

size_t octaspire_helpers_min_size_t(size_t const a, size_t const b);
size_t octaspire_helpers_max_size_t(size_t const a, size_t const b);

void octaspire_helpers_verify(bool const condition);

#ifdef __cplusplus
}
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../include/octaspire/core/octaspire_helpers.h
//////////////////////////////////////////////////////////////////////////////////////////////////



#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif








#ifdef OCTASPIRE_CORE_AMALGAMATED_IMPLEMENTATION

//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../external/murmur3.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.

// Note - The x86 and x64 versions do _not_ produce the same results, as the
// algorithms are optimized for their respective platforms. You can still
// compile and run any of them on any platform, but your performance with the
// non-native version will be less than optimal.

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// This file is modified version, not the original. It is modified by
// www.octaspire.com
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


#ifdef OCTASPIRE_CLANG_PRAGMAS_ENABLED
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wcast-align"
#endif

//-----------------------------------------------------------------------------
// Platform-specific functions and macros

#ifdef __GNUC__
#define FORCE_INLINE __attribute__((always_inline)) inline
#else
#define FORCE_INLINE inline
#endif


static FORCE_INLINE uint32_t rotl32 ( uint32_t x, int8_t r )
{
  return (x << r) | (x >> (32 - r));
}

static FORCE_INLINE uint64_t rotl64 ( uint64_t x, int8_t r )
{
  return (x << r) | (x >> (64 - r));
}

#define	ROTL32(x,y)	rotl32(x,y)
#define ROTL64(x,y)	rotl64(x,y)

#define BIG_CONSTANT(x) (x##LLU)

//-----------------------------------------------------------------------------
// Block read - if your platform needs to do endian-swapping or can only
// handle aligned reads, do the conversion here

#define getblock(p, i) (p[i])

//-----------------------------------------------------------------------------
// Finalization mix - force all bits of a hash block to avalanche

static FORCE_INLINE uint32_t fmix32 ( uint32_t h )
{
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;

  return h;
}

//----------

static FORCE_INLINE uint64_t fmix64 ( uint64_t k )
{
  k ^= k >> 33;
  k *= BIG_CONSTANT(0xff51afd7ed558ccd);
  k ^= k >> 33;
  k *= BIG_CONSTANT(0xc4ceb9fe1a85ec53);
  k ^= k >> 33;

  return k;
}

//-----------------------------------------------------------------------------

void MurmurHash3_x86_32 ( const void * key, int len,
                          uint32_t seed, void * out )
{
  const uint8_t * data = (const uint8_t*)key;
  const int nblocks = len / 4;
  int i;

  uint32_t h1 = seed;

  uint32_t c1 = 0xcc9e2d51;
  uint32_t c2 = 0x1b873593;

  //----------
  // body

  const uint32_t * blocks = (const uint32_t *)(data + nblocks*4);

  for(i = -nblocks; i; i++)
  {
    uint32_t k1 = getblock(blocks,i);

    k1 *= c1;
    k1 = ROTL32(k1,15);
    k1 *= c2;
    
    h1 ^= k1;
    h1 = ROTL32(h1,13); 
    h1 = h1*5+0xe6546b64;
  }

  //----------
  // tail

  const uint8_t * tail = (const uint8_t*)(data + nblocks*4);

  uint32_t k1 = 0;

  switch(len & 3)
  {
  case 3: k1 ^= tail[2] << 16;
  case 2: k1 ^= tail[1] << 8;
  case 1: k1 ^= tail[0];
          k1 *= c1; k1 = ROTL32(k1,15); k1 *= c2; h1 ^= k1;
  };

  //----------
  // finalization

  h1 ^= len;

  h1 = fmix32(h1);

  *(uint32_t*)out = h1;
} 

//-----------------------------------------------------------------------------

void MurmurHash3_x86_128 ( const void * key, const int len,
                           uint32_t seed, void * out )
{
  const uint8_t * data = (const uint8_t*)key;
  const int nblocks = len / 16;
  int i;

  uint32_t h1 = seed;
  uint32_t h2 = seed;
  uint32_t h3 = seed;
  uint32_t h4 = seed;

  uint32_t c1 = 0x239b961b; 
  uint32_t c2 = 0xab0e9789;
  uint32_t c3 = 0x38b34ae5; 
  uint32_t c4 = 0xa1e38b93;

  //----------
  // body

  const uint32_t * blocks = (const uint32_t *)(data + nblocks*16);

  for(i = -nblocks; i; i++)
  {
    uint32_t k1 = getblock(blocks,i*4+0);
    uint32_t k2 = getblock(blocks,i*4+1);
    uint32_t k3 = getblock(blocks,i*4+2);
    uint32_t k4 = getblock(blocks,i*4+3);

    k1 *= c1; k1  = ROTL32(k1,15); k1 *= c2; h1 ^= k1;

    h1 = ROTL32(h1,19); h1 += h2; h1 = h1*5+0x561ccd1b;

    k2 *= c2; k2  = ROTL32(k2,16); k2 *= c3; h2 ^= k2;

    h2 = ROTL32(h2,17); h2 += h3; h2 = h2*5+0x0bcaa747;

    k3 *= c3; k3  = ROTL32(k3,17); k3 *= c4; h3 ^= k3;

    h3 = ROTL32(h3,15); h3 += h4; h3 = h3*5+0x96cd1c35;

    k4 *= c4; k4  = ROTL32(k4,18); k4 *= c1; h4 ^= k4;

    h4 = ROTL32(h4,13); h4 += h1; h4 = h4*5+0x32ac3b17;
  }

  //----------
  // tail

  const uint8_t * tail = (const uint8_t*)(data + nblocks*16);

  uint32_t k1 = 0;
  uint32_t k2 = 0;
  uint32_t k3 = 0;
  uint32_t k4 = 0;

  switch(len & 15)
  {
  case 15: k4 ^= tail[14] << 16;
  case 14: k4 ^= tail[13] << 8;
  case 13: k4 ^= tail[12] << 0;
           k4 *= c4; k4  = ROTL32(k4,18); k4 *= c1; h4 ^= k4;

  case 12: k3 ^= tail[11] << 24;
  case 11: k3 ^= tail[10] << 16;
  case 10: k3 ^= tail[ 9] << 8;
  case  9: k3 ^= tail[ 8] << 0;
           k3 *= c3; k3  = ROTL32(k3,17); k3 *= c4; h3 ^= k3;

  case  8: k2 ^= tail[ 7] << 24;
  case  7: k2 ^= tail[ 6] << 16;
  case  6: k2 ^= tail[ 5] << 8;
  case  5: k2 ^= tail[ 4] << 0;
           k2 *= c2; k2  = ROTL32(k2,16); k2 *= c3; h2 ^= k2;

  case  4: k1 ^= tail[ 3] << 24;
  case  3: k1 ^= tail[ 2] << 16;
  case  2: k1 ^= tail[ 1] << 8;
  case  1: k1 ^= tail[ 0] << 0;
           k1 *= c1; k1  = ROTL32(k1,15); k1 *= c2; h1 ^= k1;
  };

  //----------
  // finalization

  h1 ^= len; h2 ^= len; h3 ^= len; h4 ^= len;

  h1 += h2; h1 += h3; h1 += h4;
  h2 += h1; h3 += h1; h4 += h1;

  h1 = fmix32(h1);
  h2 = fmix32(h2);
  h3 = fmix32(h3);
  h4 = fmix32(h4);

  h1 += h2; h1 += h3; h1 += h4;
  h2 += h1; h3 += h1; h4 += h1;

  ((uint32_t*)out)[0] = h1;
  ((uint32_t*)out)[1] = h2;
  ((uint32_t*)out)[2] = h3;
  ((uint32_t*)out)[3] = h4;
}

//-----------------------------------------------------------------------------

void MurmurHash3_x64_128 ( const void * key, const int len,
                           const uint32_t seed, void * out )
{
  const uint8_t * data = (const uint8_t*)key;
  const int nblocks = len / 16;
  int i;

  uint64_t h1 = seed;
  uint64_t h2 = seed;

  uint64_t c1 = BIG_CONSTANT(0x87c37b91114253d5);
  uint64_t c2 = BIG_CONSTANT(0x4cf5ad432745937f);

  //----------
  // body

  const uint64_t * blocks = (const uint64_t *)(data);

  for(i = 0; i < nblocks; i++)
  {
    uint64_t k1 = getblock(blocks,i*2+0);
    uint64_t k2 = getblock(blocks,i*2+1);

    k1 *= c1; k1  = ROTL64(k1,31); k1 *= c2; h1 ^= k1;

    h1 = ROTL64(h1,27); h1 += h2; h1 = h1*5+0x52dce729;

    k2 *= c2; k2  = ROTL64(k2,33); k2 *= c1; h2 ^= k2;

    h2 = ROTL64(h2,31); h2 += h1; h2 = h2*5+0x38495ab5;
  }

  //----------
  // tail

  const uint8_t * tail = (const uint8_t*)(data + nblocks*16);

  uint64_t k1 = 0;
  uint64_t k2 = 0;

  switch(len & 15)
  {
  case 15: k2 ^= (uint64_t)(tail[14]) << 48;
  case 14: k2 ^= (uint64_t)(tail[13]) << 40;
  case 13: k2 ^= (uint64_t)(tail[12]) << 32;
  case 12: k2 ^= (uint64_t)(tail[11]) << 24;
  case 11: k2 ^= (uint64_t)(tail[10]) << 16;
  case 10: k2 ^= (uint64_t)(tail[ 9]) << 8;
  case  9: k2 ^= (uint64_t)(tail[ 8]) << 0;
           k2 *= c2; k2  = ROTL64(k2,33); k2 *= c1; h2 ^= k2;

  case  8: k1 ^= (uint64_t)(tail[ 7]) << 56;
  case  7: k1 ^= (uint64_t)(tail[ 6]) << 48;
  case  6: k1 ^= (uint64_t)(tail[ 5]) << 40;
  case  5: k1 ^= (uint64_t)(tail[ 4]) << 32;
  case  4: k1 ^= (uint64_t)(tail[ 3]) << 24;
  case  3: k1 ^= (uint64_t)(tail[ 2]) << 16;
  case  2: k1 ^= (uint64_t)(tail[ 1]) << 8;
  case  1: k1 ^= (uint64_t)(tail[ 0]) << 0;
           k1 *= c1; k1  = ROTL64(k1,31); k1 *= c2; h1 ^= k1;
  };

  //----------
  // finalization

  h1 ^= len; h2 ^= len;

  h1 += h2;
  h2 += h1;

  h1 = fmix64(h1);
  h2 = fmix64(h2);

  h1 += h2;
  h2 += h1;

  ((uint64_t*)out)[0] = h1;
  ((uint64_t*)out)[1] = h2;
}

#ifdef OCTASPIRE_CLANG_PRAGMAS_ENABLED
#pragma clang diagnostic pop
#endif

//-----------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../external/murmur3.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../src/octaspire_region.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

typedef struct octaspire_region_block_t
{
    char                            *buffer;
    size_t                           bufferLengthInOctets;
    size_t                           firstFreeIndex;
    size_t                           sizeOfHeader;
    struct octaspire_region_block_t *next;
}
octaspire_region_block_t;

// Prototypes for private functions /////////////////////////////////////////
static size_t octaspire_region_block_private_get_number_of_octets_available(
    octaspire_region_block_t const * const self);

static bool octaspire_region_block_private_is_valid_index(
    octaspire_region_block_t const * const self,
    size_t const index);

static octaspire_region_block_t *octaspire_region_block_new(size_t const minBlockSizeInOctets);

static bool octaspire_region_block_is_full_of_freed(octaspire_region_block_t const * const self);

static ptrdiff_t octaspire_region_block_private_calculate_alignment_padding_for_size(
    octaspire_region_block_t const * const self,
    size_t const startIndex,
    size_t const size);

static void *octaspire_region_block_malloc(octaspire_region_block_t *self, size_t const size);

static void octaspire_region_private_add_new_head(octaspire_region_t *self, size_t const minSize);

static void octaspire_region_block_measure_wasted(
    octaspire_region_block_t const * const self,
    double *wastedOnPadding,
    double *wastedOnFreed);

static void *octaspire_region_block_realloc(octaspire_region_block_t *self, void *ptr, size_t const size);
/////////////////////////////////////////////////////////////////////////////

static bool octaspire_region_block_is_pointer_inside(
    octaspire_region_block_t const * const self,
    void *ptr)
{
    if ((char*)ptr < self->buffer)
    {
        return false;
    }

    if ((char*)ptr > self->buffer + self->bufferLengthInOctets)
    {
        return false;
    }

    return true;
}

/*
static void octaspire_region_block_private_assert_header_values(
    octaspire_region_block_t *self,
    size_t const index,
    size_t const expectedInUse,
    size_t const expectedUserDataLen,
    size_t const expectedPaddingBefore,
    size_t const expectedPaddingAfter)
{
    octaspire_helpers_verify(index >= 4);
    char const * const ptr = self->buffer + index;

    size_t const * const headerInUse         = (size_t const * const)(ptr - (sizeof(size_t) * 4));
    size_t const * const headerUserDataLen   = (size_t const * const)(ptr - (sizeof(size_t) * 3));
    size_t const * const headerPaddingBefore = (size_t const * const)(ptr - (sizeof(size_t) * 2));
    size_t const * const headerPaddingAfter  = (size_t const * const)(ptr - (sizeof(size_t) * 1));

    octaspire_helpers_verify(expectedInUse         == *headerInUse);
    octaspire_helpers_verify(expectedUserDataLen   == *headerUserDataLen);
    octaspire_helpers_verify(expectedPaddingBefore == *headerPaddingBefore);
    octaspire_helpers_verify(expectedPaddingAfter  == *headerPaddingAfter);
}
*/

static void octaspire_region_block_private_get_header_values(
    octaspire_region_block_t const * const self,
    size_t const index,
    size_t *inUse,
    size_t *userDataLen,
    size_t *paddingBefore,
    size_t *paddingAfter)
{
    //assert(index >= 4);
    char const * const ptr = self->buffer + index;
    size_t const sizeOfSizet = sizeof(size_t);

    memcpy(inUse,         (ptr - (sizeOfSizet * 4)), sizeof(size_t));
    memcpy(userDataLen,   (ptr - (sizeOfSizet * 3)), sizeof(size_t));
    memcpy(paddingBefore, (ptr - (sizeOfSizet * 2)), sizeof(size_t));
    memcpy(paddingAfter,  (ptr -  sizeOfSizet     ), sizeof(size_t));
}

size_t octaspire_region_block_private_get_number_of_octets_available(
    octaspire_region_block_t const * const self)
{
    return self->bufferLengthInOctets - self->firstFreeIndex;
}

bool octaspire_region_block_private_is_valid_index(
    octaspire_region_block_t const * const self,
    size_t const index)
{
    return index < self->bufferLengthInOctets;
}

void octaspire_region_block_release(octaspire_region_block_t *self);

octaspire_region_block_t *octaspire_region_block_new(size_t const minBlockSizeInOctets)
{
    octaspire_region_block_t *self = calloc(1, sizeof(octaspire_region_block_t));

    if (!self)
    {
        return 0;
    }

    self->next = 0;
    self->buffer = calloc(1, minBlockSizeInOctets);

    if (!self->buffer)
    {
        octaspire_region_block_release(self);
        return 0;
    }

    self->bufferLengthInOctets = minBlockSizeInOctets;
    self->firstFreeIndex = 0;
    self->sizeOfHeader   = sizeof(size_t) * 4;
    self->next           = 0;

    return self;
}

bool octaspire_region_block_is_full_of_freed(octaspire_region_block_t const * const self)
{
    size_t inUse         = 0;
    size_t userDataLen   = 0;
    size_t paddingBefore = 0;
    size_t paddingAfter  = 0;

    size_t index = self->sizeOfHeader;

    while (index < self->firstFreeIndex && octaspire_region_block_private_is_valid_index(self, index))
    {
        octaspire_region_block_private_get_header_values(
            self,
            index,
            &inUse,
            &userDataLen,
            &paddingBefore,
            &paddingAfter);

        if (inUse)
        {
            return false;
        }

        size_t const delta = (paddingBefore + userDataLen + paddingAfter + self->sizeOfHeader);

        assert(delta);

        index += delta;
    }

    // TODO XXX make this value configurable
    if (octaspire_region_block_private_get_number_of_octets_available(self) < 128)
    {
        return true;
    }

    return false;
}

void octaspire_region_block_release(octaspire_region_block_t *self)
{
    if (!self)
    {
        return;
    }

    free(self->buffer);
    free(self);
}

ptrdiff_t octaspire_region_block_private_calculate_alignment_padding_for_size(
    octaspire_region_block_t const * const self,
    size_t const startIndex,
    size_t const size)
{
    size_t result = 0;

    while (true)
    {
        char const * const buf = self->buffer + startIndex + result;

        //if ((size_t)buf % size == 0 && (size_t)buf % 16 == 0)
        //if ((size_t)buf % 16 == 0)
        //if ((size_t)buf % 4 == 0 && (size_t)buf % 8 == 0 && (size_t)buf % 16 == 0)

        //if ((size_t)buf % 16 == 0)
        if ((size_t)buf % 8 == 0)
        {
            return (ptrdiff_t)result;
        }

        ++result;

        assert(result <= 409600); // TODO XXX what value to use here, or should no limit be used?

        if (!octaspire_region_block_private_is_valid_index(self, startIndex + result + size))
        {
            return -1;
        }
    }
}

void *octaspire_region_block_malloc(octaspire_region_block_t *self, size_t const size)
{
    ptrdiff_t const paddingBefore = octaspire_region_block_private_calculate_alignment_padding_for_size(
        self,
        self->firstFreeIndex + self->sizeOfHeader,
        size);

    if (paddingBefore < 0)
    {
        return 0;
    }

    ptrdiff_t const paddingAfter  = octaspire_region_block_private_calculate_alignment_padding_for_size(
        self,
        self->firstFreeIndex + self->sizeOfHeader + size,
        self->sizeOfHeader);

    if (paddingAfter < 0)
    {
        return 0;
    }

    if (octaspire_region_block_private_get_number_of_octets_available(self) < ((size_t)paddingBefore + size + (size_t)paddingAfter))
    {
        return 0;
    }

    char *buf = self->buffer + self->firstFreeIndex;

    size_t header[] = {
        1,             // inUse = yes
        size,          // userDataLen
        (size_t)paddingBefore, // amountOfPaddingInTheBeginning
        (size_t)paddingAfter   // amountOfPaddingInTheEnd
    };

    for (size_t i = 0; i < (sizeof(header) / sizeof(header[0])); ++i)
    {
        void *dest = buf + (i * sizeof(header[i]));

        if (dest != memcpy(
            dest,
            &(header[i]),
            sizeof(header[i])))
        {
            return 0;
        }
    }

    void *result = buf + self->sizeOfHeader;
    if (result != memset(result, 0, (size_t)paddingBefore + size + (size_t)paddingAfter))
    {
        return 0;
    }

    /*
    octaspire_region_block_private_assert_header_values(
        self,
        self->firstFreeIndex + self->sizeOfHeader,
        header[0],
        header[1],
        header[2],
        header[3]);
    */

    self->firstFreeIndex += (self->sizeOfHeader + (size_t)paddingBefore + size + (size_t)paddingAfter);

    return result;
}

void octaspire_region_block_free(octaspire_region_block_t *self, void *ptr);

void *octaspire_region_block_realloc(octaspire_region_block_t *self, void *ptr, size_t const size)
{
    //size_t const * const headerUserDataLen = (size_t*)((char*)ptr - (sizeof(size_t) * 3));
    size_t headerUserDataLen = 0;
    memcpy(&headerUserDataLen, ((char*)ptr - (sizeof(size_t) * 3)), sizeof(size_t));

    octaspire_region_block_free(self, ptr);

    // TODO if slot is made smaller, the reserved area could just be shrunk.
    void *newSlot = octaspire_region_block_malloc(self, size);

    if (!newSlot)
    {
        return 0;
    }

    size_t const octetsToCopy = octaspire_helpers_min_size_t(headerUserDataLen, size);

    if (newSlot != memcpy(newSlot, ptr, octetsToCopy))
    {
        abort();
    }

    return newSlot;
}

void octaspire_region_block_free(octaspire_region_block_t *self, void *ptr)
{
    OCTASPIRE_HELPERS_UNUSED_PARAMETER(self);

    //size_t       * const headerInUse          = (size_t*)((char*)ptr - (sizeof(size_t) * 4));
    //size_t const * const headerUserDataLen    = (size_t*)((char*)ptr - (sizeof(size_t) * 3));
    size_t headerInUse = 0;
    size_t headerUserDataLen = 0;

    memcpy(&headerInUse, ((char*)ptr - (sizeof(size_t) * 4)), sizeof(size_t));
    memcpy(&headerUserDataLen, ((char*)ptr - (sizeof(size_t) * 3)), sizeof(size_t));

    // Sanity checks
    octaspire_helpers_verify(headerInUse == 1);
    octaspire_helpers_verify(headerUserDataLen > 0);

    // Mark as free
    headerInUse = 0;
    memcpy(((char*)ptr - (sizeof(size_t) * 4)), &headerInUse, sizeof(size_t));
}

void octaspire_region_block_measure_wasted(
    octaspire_region_block_t const * const self,
    double *wastedOnPadding,
    double *wastedOnFreed)
{
    //size_t usedOctets    = 0;
    size_t paddingOctets = 0;
    size_t freedOctets   = 0;

    size_t inUse         = 0;
    size_t userDataLen   = 0;
    size_t paddingBefore = 0;
    size_t paddingAfter  = 0;

    size_t index = self->sizeOfHeader;

    while (index < self->firstFreeIndex && octaspire_region_block_private_is_valid_index(self, index))
    {
        octaspire_region_block_private_get_header_values(
            self,
            index,
            &inUse,
            &userDataLen,
            &paddingBefore,
            &paddingAfter);

        if (inUse)
        {
            //usedOctets    += userDataLen;
            paddingOctets += (paddingBefore + paddingAfter);
        }
        else
        {
            freedOctets += userDataLen;
            freedOctets += (paddingBefore + paddingAfter);
        }

        size_t const delta = (paddingBefore + userDataLen + paddingAfter + self->sizeOfHeader);

        assert(delta);

        index += delta;
    }

    *wastedOnFreed   = ((double)freedOctets   / (double)self->firstFreeIndex) * 100.0;
    *wastedOnPadding = ((double)paddingOctets / (double)self->firstFreeIndex) * 100.0;
}

static void octaspire_region_block_print(octaspire_region_block_t const * const self)
{
    double const used   = ((double)self->firstFreeIndex / (double)self->bufferLengthInOctets) * 100.0;

    double wastedOnPadding = 0;
    double wastedOnFreed   = 0;

    octaspire_region_block_measure_wasted(self, &wastedOnPadding, &wastedOnFreed);

    printf(
        "block %p (used %g%% wasted on padding of used %g%% wasted on freed (payload + padding) %g%%)\n",
        (void const * const)self,
        used,
        wastedOnPadding,
        wastedOnFreed);

    if (self->next)
    {
        octaspire_region_block_print(self->next);
    }
}























struct octaspire_region_t
{
    size_t                    minBlockSizeInOctets;
    octaspire_region_block_t *head;
    size_t                    numFreesDone;
};

octaspire_region_t *octaspire_region_new(size_t const minBlockSizeInOctets)
{
    octaspire_region_t *self = calloc(1, sizeof(octaspire_region_t));

    if (!self)
    {
        return 0;
    }

    self->head                 = 0;
    self->minBlockSizeInOctets = minBlockSizeInOctets;
    self->head                 = octaspire_region_block_new(self->minBlockSizeInOctets);
    self->numFreesDone         = 0;

    if (!self->head)
    {
        octaspire_region_release(self);
        self = 0;
        return 0;
    }

    return self;
}

void octaspire_region_release(octaspire_region_t *self)
{
    if (!self)
    {
        return;
    }

    while (self->head)
    {
        octaspire_region_block_t *next = self->head->next;
        self->head->next = 0;
        octaspire_region_block_release(self->head);
        self->head = next;
    }

    free(self);
}

void octaspire_region_private_add_new_head(octaspire_region_t *self, size_t const minSize)
{
    octaspire_region_block_t *block = octaspire_region_block_new(
        octaspire_helpers_max_size_t(
            minSize,
            self->minBlockSizeInOctets));

    assert(block);

    block->next = self->head;
    self->head = block;
}

void *octaspire_region_malloc(octaspire_region_t *self, size_t const size)
{
    if (!self->head)
    {
        self->head = octaspire_region_block_new(self->minBlockSizeInOctets);
    }

    void *result = octaspire_region_block_malloc(self->head, size);

    if (!result)
    {
        octaspire_region_private_add_new_head(self, size);
        return octaspire_region_block_malloc(self->head, size);
    }

    return result;
}

void *octaspire_region_realloc(octaspire_region_t *self, void *ptr, size_t const size)
{
    if (!self->head)
    {
        self->head = octaspire_region_block_new(self->minBlockSizeInOctets);
    }

    void *result = octaspire_region_block_realloc(self->head, ptr, size);

    if (!result)
    {
        octaspire_region_private_add_new_head(self, size);
        return octaspire_region_block_realloc(self->head, ptr, size);
    }

    return result;
}

void octaspire_region_compact(octaspire_region_t *self)
{
    octaspire_region_block_t *block = self->head;
    octaspire_region_block_t *prev = 0;

    while (block)
    {
        octaspire_region_block_t *next = block->next;

        if (octaspire_region_block_is_full_of_freed(block))
        {
            if (prev)
            {
                prev->next = block->next;
            }

            block->next = 0;
            octaspire_region_block_release(block);

            if (block == self->head)
            {
                self->head = next;
            }
        }
        else
        {
            prev = block;
        }

        block = next;
    }
}

void octaspire_region_free(octaspire_region_t *self, void *ptr)
{
    if (!ptr)
    {
        // TODO is this ok solution? free does nothing on NULL.
        return;
    }

    if (!self->head)
    {
        self->head = octaspire_region_block_new(self->minBlockSizeInOctets);
    }

    octaspire_region_block_t *block = self->head;

    while (block)
    {
        if (octaspire_region_block_is_pointer_inside(block, ptr))
        {
            octaspire_region_block_free(block, ptr);
            ++(self->numFreesDone);

            // TODO XXX make this value configurable
            // And check the need to do this at all again.
            if (self->numFreesDone > 2048)
            {
                octaspire_region_compact(self);
                self->numFreesDone = 0;
            }

            return;
        }

        block = block->next;
    }

    assert(false);
}

void octaspire_region_print(octaspire_region_t const * const self)
{
    printf("region contains the following blocks\n"
           "------------------------------------\n");
    if (self->head)
    {
        octaspire_region_block_print(self->head);
    }

    printf("\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../src/octaspire_region.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../src/octaspire_memory.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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


struct octaspire_memory_allocator_t
{
    size_t               numberOfFutureAllocationsToBeRigged;
    size_t               bitIndex;
    uint32_t             bitQueue[20];
    octaspire_region_t  *region;
};

octaspire_memory_allocator_t *octaspire_memory_allocator_new_create_region(size_t const minBlockSizeInOctets)
{
    octaspire_region_t *region = octaspire_region_new(minBlockSizeInOctets);

    if (!region)
    {
        return 0;
    }

    return octaspire_memory_allocator_new(region);
}

octaspire_memory_allocator_t *octaspire_memory_allocator_new(struct octaspire_region_t *region)
{
    size_t const size = sizeof(octaspire_memory_allocator_t);

    octaspire_memory_allocator_t *self = malloc(size);

    if (!self)
    {
        return self;
    }

    memset(self, 0, size);

    self->numberOfFutureAllocationsToBeRigged = 0;
    self->bitIndex = 0;

    if (self->bitQueue != memset(self->bitQueue, 0, sizeof(self->bitQueue)))
    {
        abort();
    }

    self->region = region;

    return self;
}

void octaspire_memory_allocator_release(octaspire_memory_allocator_t *self)
{
    if (!self)
    {
        return;
    }

    if (self->region)
    {
        octaspire_region_release(self->region);
        self->region = 0;
    }

    free(self);
}

bool octaspire_memory_allocator_private_test_bit(octaspire_memory_allocator_t const * const self);

bool octaspire_memory_allocator_private_test_bit(octaspire_memory_allocator_t const * const self)
{
    size_t const arrayIndex = (size_t)((float)self->bitIndex / 32.0f);
    size_t const bitIndex   = self->bitIndex % 8;
    assert(bitIndex < 32);
    assert(arrayIndex < (sizeof(self->bitQueue) / sizeof(self->bitQueue[0])));
    return octaspire_helpers_test_bit(self->bitQueue[arrayIndex], bitIndex);
}

void *octaspire_memory_allocator_malloc(
    octaspire_memory_allocator_t *self,
    size_t const size)
{
    if (self->numberOfFutureAllocationsToBeRigged)
    {
        --(self->numberOfFutureAllocationsToBeRigged);

        if (!octaspire_memory_allocator_private_test_bit(self))
        {
            ++(self->bitIndex);
            return 0;
        }

        ++(self->bitIndex);
    }

    assert(size);

    void *result = self->region ? octaspire_region_malloc(self->region, size) : malloc(size);

    if (!result)
    {
        return result;
    }

    // Region sets memory to zero, so there is no need to do it twice if region is in use.
    if (!self->region)
    {
        if (result != memset(result, 0, size))
        {
            abort();
        }
    }

    return result;
}

void *octaspire_memory_allocator_realloc(
    octaspire_memory_allocator_t *self,
    void *ptr, size_t const size)
{
    if (self->numberOfFutureAllocationsToBeRigged)
    {
        --(self->numberOfFutureAllocationsToBeRigged);

        if (!octaspire_memory_allocator_private_test_bit(self))
        {
            ++(self->bitIndex);
            return 0;
        }

        ++(self->bitIndex);
    }

    return self->region ? octaspire_region_realloc(self->region, ptr, size) : realloc(ptr, size);
}

void octaspire_memory_allocator_free(
    octaspire_memory_allocator_t *self,
    void *ptr)
{
    assert(self);
    self->region ? octaspire_region_free(self->region, ptr) : free(ptr);
}

void octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
    octaspire_memory_allocator_t *self,
    size_t const count,
    uint32_t const bitQueue0)
{
    assert(count <= 32);
    self->numberOfFutureAllocationsToBeRigged = count;
    self->bitIndex  = 0;

    if (self->bitQueue != memset(self->bitQueue, 0, sizeof(self->bitQueue)))
    {
        abort();
    }

    self->bitQueue[0] = bitQueue0;
}

void octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged_when_larger_than_32(
    octaspire_memory_allocator_t *self,
    size_t const count,
    uint32_t const bitQueue0,
    uint32_t const bitQueue1,
    uint32_t const bitQueue2,
    uint32_t const bitQueue3,
    uint32_t const bitQueue4,
    uint32_t const bitQueue5,
    uint32_t const bitQueue6,
    uint32_t const bitQueue7,
    uint32_t const bitQueue8,
    uint32_t const bitQueue9,
    uint32_t const bitQueue10,
    uint32_t const bitQueue11,
    uint32_t const bitQueue12,
    uint32_t const bitQueue13,
    uint32_t const bitQueue14,
    uint32_t const bitQueue15,
    uint32_t const bitQueue16,
    uint32_t const bitQueue17,
    uint32_t const bitQueue18,
    uint32_t const bitQueue19)
{
    assert(count <= 640);
    self->numberOfFutureAllocationsToBeRigged = count;
    self->bitIndex = 0;

    if (self->bitQueue != memset(self->bitQueue, 0, sizeof(self->bitQueue)))
    {
        abort();
    }

    self->bitQueue[0]  = bitQueue0;
    self->bitQueue[1]  = bitQueue1;
    self->bitQueue[2]  = bitQueue2;
    self->bitQueue[3]  = bitQueue3;
    self->bitQueue[4]  = bitQueue4;
    self->bitQueue[5]  = bitQueue5;
    self->bitQueue[6]  = bitQueue6;
    self->bitQueue[7]  = bitQueue7;
    self->bitQueue[8]  = bitQueue8;
    self->bitQueue[9]  = bitQueue9;
    self->bitQueue[10] = bitQueue10;
    self->bitQueue[11] = bitQueue11;
    self->bitQueue[12] = bitQueue12;
    self->bitQueue[13] = bitQueue13;
    self->bitQueue[14] = bitQueue14;
    self->bitQueue[15] = bitQueue15;
    self->bitQueue[16] = bitQueue16;
    self->bitQueue[17] = bitQueue17;
    self->bitQueue[18] = bitQueue18;
    self->bitQueue[19] = bitQueue19;
}

size_t octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(
    octaspire_memory_allocator_t const * const self)
{
    return self->numberOfFutureAllocationsToBeRigged;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../src/octaspire_memory.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../src/octaspire_helpers.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

bool octaspire_helpers_test_bit(uint32_t const bitSet, size_t const index)
{
    assert(index < 32);
    return bitSet & ((uint32_t)0x01 << index);
}

char *octaspire_helpers_path_to_buffer(
    char const * const path,
    size_t *octetsAllocated,
    octaspire_memory_allocator_t *allocator,
    octaspire_stdio_t *stdio)
{
    *octetsAllocated = 0;
    FILE *f = fopen(path, "rb");

    if (!f)
    {
        return 0;
    }

    fseek(f, 0, SEEK_END);

    long const length = ftell(f);

    if (length <= 0)
    {
        fclose(f);
        f = 0;
        return 0;
    }

    fseek(f, 0, SEEK_SET);

    char *result = octaspire_memory_allocator_malloc(allocator, sizeof(char) * (size_t)length);

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
        octaspire_memory_allocator_free(allocator, result);
        result = 0;
        *octetsAllocated = 0;
        return 0;
    }

    fclose(f);
    f = 0;

    return result;
}

uint32_t octaspire_helpers_calculate_murmur3_hash_for_size_t_argument(size_t const value)
{
    uint32_t result = 0;
    MurmurHash3_x86_32(&value, sizeof(value), OCTASPIRE_HELPERS_MURMUR3_HASH_SEED, &result);
    return result;
}

uint32_t octaspire_helpers_calculate_murmur3_hash_for_bool_argument(bool const value)
{
    uint32_t result = 0;
    MurmurHash3_x86_32(&value, sizeof(value), OCTASPIRE_HELPERS_MURMUR3_HASH_SEED, &result);
    return result;
}

uint32_t octaspire_helpers_calculate_murmur3_hash_for_int32_t_argument(int32_t const value)
{
    uint32_t result = 0;
    MurmurHash3_x86_32(&value, sizeof(value), OCTASPIRE_HELPERS_MURMUR3_HASH_SEED, &result);
    return result;
}

uint32_t octaspire_helpers_calculate_murmur3_hash_for_double_argument(double const value)
{
    uint32_t result = 0;
    MurmurHash3_x86_32(&value, sizeof(value), OCTASPIRE_HELPERS_MURMUR3_HASH_SEED, &result);
    return result;
}

uint32_t octaspire_helpers_calculate_murmur3_hash_for_void_pointer_argument(void const * const value)
{
    uint32_t result = 0;
    MurmurHash3_x86_32(&value, sizeof(value), OCTASPIRE_HELPERS_MURMUR3_HASH_SEED, &result);
    return result;
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

size_t octaspire_helpers_max_size_t(size_t const a, size_t const b)
{
    if (a > b)
    {
        return a;
    }

    return b;
}

void octaspire_helpers_verify(bool const condition)
{
    if (!condition)
    {
        abort();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../src/octaspire_helpers.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../src/octaspire_utf8.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

typedef enum octaspire_utf8_character_range_t
{
    OCTASPIRE_UTF8_CHARACTER_RANGE_FIRST,
    OCTASPIRE_UTF8_CHARACTER_RANGE_SECOND,
    OCTASPIRE_UTF8_CHARACTER_RANGE_THIRD,
    OCTASPIRE_UTF8_CHARACTER_RANGE_FOURTH,
    OCTASPIRE_UTF8_CHARACTER_RANGE_ILLEGAL
}
octaspire_utf8_character_range_t;

static octaspire_utf8_character_range_t octaspire_utf8_private_rangeof(uint32_t const character);
//static octaspire_utf8_character_range_t   octaspire_utf8_private_rangeof          (octaspire_utf8_character_range_t const range);
static uint32_t                           octaspire_utf8_private_high_order_bits  (octaspire_utf8_character_range_t const range);
static void                               octaspire_utf8_private_set_bit          (uint32_t *bitset, size_t const index, bool const on);
static void                               octaspire_utf8_private_set_bit_of_char  (unsigned char *bitset, size_t const index, bool const on);
static bool                               octaspire_utf8_private_get_bit          (uint32_t const bitset, size_t const index);
static bool                               octaspire_utf8_private_get_bit_of_uint8 (char const bitset, size_t const index);

static int                                octaspire_utf8_private_octets_in_next   (char const * const text, size_t const textLengthInOctets);
static int                                octaspire_utf8_private_octets_in_next_from_buffer   (char const * const buffer, size_t const lengthInOctets, size_t const currentIndex);

octaspire_utf8_decode_status_t octaspire_utf8_private_decode_helper(
    char const * const buffer,
    size_t const numOctetsNeeded,
    size_t const numOctetsAvailable,
    uint32_t *result);

static uint32_t const octaspire_utf8_private_range1_end   = ((uint32_t)0x007F);

static uint32_t const octaspire_utf8_private_range2_start = ((uint32_t)0x0080);
static uint32_t const octaspire_utf8_private_range2_end   = ((uint32_t)0x07FF);

static uint32_t const octaspire_utf8_private_range3_start = ((uint32_t)0x0800);
static uint32_t const octaspire_utf8_private_range3_end   = ((uint32_t)0xFFFF);

static uint32_t const octaspire_utf8_private_range4_start = ((uint32_t)0x00010000);
static uint32_t const octaspire_utf8_private_range4_end   = ((uint32_t)0x0010FFFF);

static octaspire_utf8_character_range_t octaspire_utf8_private_rangeof(uint32_t const character)
{
    if (character <= octaspire_utf8_private_range1_end)
        return OCTASPIRE_UTF8_CHARACTER_RANGE_FIRST;

    if (character >= octaspire_utf8_private_range2_start && character <= octaspire_utf8_private_range2_end)
        return OCTASPIRE_UTF8_CHARACTER_RANGE_SECOND;

    if (character >= octaspire_utf8_private_range3_start && character <= octaspire_utf8_private_range3_end)
        return OCTASPIRE_UTF8_CHARACTER_RANGE_THIRD;

    if (character >= octaspire_utf8_private_range4_start && character <= octaspire_utf8_private_range4_end)
        return OCTASPIRE_UTF8_CHARACTER_RANGE_FOURTH;

    return OCTASPIRE_UTF8_CHARACTER_RANGE_ILLEGAL;
}

static uint32_t octaspire_utf8_private_high_order_bits(octaspire_utf8_character_range_t const range)
{
    if (range == OCTASPIRE_UTF8_CHARACTER_RANGE_FIRST)
        return 0;

    if (range == OCTASPIRE_UTF8_CHARACTER_RANGE_SECOND)
        return 0xC080;

    if (range == OCTASPIRE_UTF8_CHARACTER_RANGE_THIRD)
        return 0xE08080;

    if (range == OCTASPIRE_UTF8_CHARACTER_RANGE_FOURTH)
        return 0xF0808080;

    // Error, illegal range. Should there be another/better way of reporting it?
    return ((uint32_t)0xFFFFFFFF);
}

static void octaspire_utf8_private_set_bit(uint32_t *bitset, size_t const index, bool const on)
{
    assert(index < 32);

    // INVALID_READ_OF_1
    if (on)
    {
        (*bitset) |= (uint32_t)1 << index;
    }
    else
    {
        (*bitset) &= ~((uint32_t)1 << index);
    }
}

static void octaspire_utf8_private_set_bit_of_char(unsigned char *bitset, size_t const index, bool const on)
{
    assert(index < CHAR_BIT);

    if (on)
    {
        (*bitset) |= (unsigned char)(1 << index);
    }
    else
    {
        (*bitset) &= (unsigned char)(~(1 << index));
    }
}

static bool octaspire_utf8_private_get_bit(uint32_t const bitset, size_t const index)
{
    assert(index < 32);
    return (bitset >> index) & 1;
}

static bool octaspire_utf8_private_get_bit_of_uint8(char const bitset, size_t const index)
{
    assert(index < 8);
    return (((uint8_t)bitset) >> index) & 1;
}

octaspire_utf8_encode_status_t octaspire_utf8_encode_character(uint32_t const character, octaspire_utf8_character_t *result)
{
    memset(result->octets, 0, 4);
    result->numoctets = 0;

    // TODO XXX are the upper and lower bounds inclusive or not?
    // Check that and remove the equality operator part if necessary.
    if (character >= 0xD800 && character <= 0xDFFF)
    {
        return OCTASPIRE_UTF8_ENCODE_STATUS_ILLEGAL_CHARACTER_NUMBER;
    }

    octaspire_utf8_character_range_t const range = octaspire_utf8_private_rangeof(character);

    uint32_t bitset = octaspire_utf8_private_high_order_bits(range);

    switch (range)
    {
        case OCTASPIRE_UTF8_CHARACTER_RANGE_FIRST:
        {
            for (size_t i = 0; i < 7; ++i)
            {
                octaspire_utf8_private_set_bit(&bitset, i, octaspire_utf8_private_get_bit(character, i));
            }

            result->numoctets = 1;
        }
        break;

        case OCTASPIRE_UTF8_CHARACTER_RANGE_SECOND:
        {
            for (size_t i = 0; i < 6; ++i)
            {
                octaspire_utf8_private_set_bit(&bitset, i, octaspire_utf8_private_get_bit(character, i));
            }

            for (size_t i = 0; i < 5; ++i)
            {
                octaspire_utf8_private_set_bit(&bitset, 8+i, octaspire_utf8_private_get_bit(character, 6+i));
            }

            result->numoctets = 2;
        }
        break;

        case OCTASPIRE_UTF8_CHARACTER_RANGE_THIRD:
        {
            for (size_t i = 0; i < 6; ++i)
            {
                octaspire_utf8_private_set_bit(&bitset, i, octaspire_utf8_private_get_bit(character, i));
            }

            for (size_t i = 0; i < 6; ++i)
            {
                octaspire_utf8_private_set_bit(&bitset, 8+i, octaspire_utf8_private_get_bit(character, 6+i));
            }

            for (size_t i = 0; i < 4; ++i)
            {
                octaspire_utf8_private_set_bit(&bitset, 16+i, octaspire_utf8_private_get_bit(character, 12+i));
            }

            result->numoctets = 3;
        }
        break;

        case OCTASPIRE_UTF8_CHARACTER_RANGE_FOURTH:
        {
            for (size_t i = 0; i < 6; ++i)
            {
                octaspire_utf8_private_set_bit(&bitset, i, octaspire_utf8_private_get_bit(character, i));
            }

            for (size_t i = 0; i < 6; ++i)
            {
                octaspire_utf8_private_set_bit(&bitset, 8+i, octaspire_utf8_private_get_bit(character, 6+i));
            }

            for (size_t i = 0; i < 6; ++i)
            {
                octaspire_utf8_private_set_bit(&bitset, 16+i, octaspire_utf8_private_get_bit(character, 12+i));
            }

            for (size_t i = 0; i < 3; ++i)
            {
                octaspire_utf8_private_set_bit(&bitset, 24+i, octaspire_utf8_private_get_bit(character, 18+i));
            }

            result->numoctets = 4;
        }
        break;

        case OCTASPIRE_UTF8_CHARACTER_RANGE_ILLEGAL:
        {
            return OCTASPIRE_UTF8_ENCODE_STATUS_ILLEGAL_CHARACTER_NUMBER;
        }
    }

    for (size_t i = 0; i < 8; ++i)
    {
        octaspire_utf8_private_set_bit_of_char(&(result->octets[3]), i, octaspire_utf8_private_get_bit(bitset, i));
    }

    for (size_t i = 0; i < 8; ++i)
    {
        octaspire_utf8_private_set_bit_of_char(&(result->octets[2]), i, octaspire_utf8_private_get_bit(bitset, 8+i));
    }

    for (size_t i = 0; i < 8; ++i)
    {
        octaspire_utf8_private_set_bit_of_char(&(result->octets[1]), i, octaspire_utf8_private_get_bit(bitset, 16+i));
    }

    for (size_t i = 0; i < 8; ++i)
    {
        octaspire_utf8_private_set_bit_of_char(&(result->octets[0]), i, octaspire_utf8_private_get_bit(bitset, 24+i));
    }

    return OCTASPIRE_UTF8_ENCODE_STATUS_OK;
}

static int octaspire_utf8_private_octets_in_next(char const * const text, size_t const textLengthInOctets)
{
    size_t lengthInOctets = 0;

    if (!text || textLengthInOctets == 0 || text[0] == '\0')
    {
        return 0;
    }

    for (size_t i = 0; i < octaspire_helpers_min_size_t(4, textLengthInOctets); ++i)
    {
        if (text[i] == '\0')
        {
            break;
        }
        else
        {
            ++lengthInOctets;
        }
    }

    return octaspire_utf8_private_octets_in_next_from_buffer(text, lengthInOctets, 0);
}

static int octaspire_utf8_private_octets_in_next_from_buffer(char const * const buffer, size_t const lengthInOctets, size_t const currentIndex)
{
    if (!buffer || currentIndex >= lengthInOctets)
        return 0;

    size_t const octetsAvailable = lengthInOctets - currentIndex;

    if (!octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 7))
    {
        return 1;
    }

    if ( octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 7) &&
         octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 6) &&
        !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 5))
    {
        if (octetsAvailable < 2)
        {
            return -1;
        }

        if ( octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 1], 7) &&
            !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 1], 6))
        {
            return 2;
        }

        return -1;
    }

    if ( octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 7) &&
         octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 6) &&
         octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 5) &&
        !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 4))
    {
        if (octetsAvailable < 3)
        {
            return -1;
        }

        if ( octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 1], 7) &&
            !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 1], 6) &&
             octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 2], 7) &&
            !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 2], 6))
        {
            return 3;
        }

        return -1;
    }

    if ( octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 7) &&
         octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 6) &&
         octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 5) &&
         octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 4) &&
        !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 3))
    {
        if (octetsAvailable < 4)
        {
            return -1;
        }

        if ( octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 1], 7) &&
            !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 1], 6) &&
             octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 2], 7) &&
            !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 2], 6) &&
             octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 3], 7) &&
            !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 3], 6))
        {
            return 4;
        }

        return -1;
    }

    return -1;
}

octaspire_utf8_decode_status_t octaspire_utf8_private_decode_helper(
    char const * const buffer,
    size_t const numOctetsNeeded,
    size_t const numOctetsAvailable,
    uint32_t *result)
{
    assert(numOctetsNeeded <= 4);

    if (numOctetsNeeded > numOctetsAvailable || !buffer)
    {
        return OCTASPIRE_UTF8_DECODE_STATUS_INPUT_NOT_ENOUGH_OCTETS_AVAILABLE;
    }

    switch (numOctetsNeeded)
    {
        case 1:
        {
            // 0xxxxxxx

            for (size_t i = 0; i < 7; ++i)
            {
                // INVALID_READ_OF_1
                octaspire_utf8_private_set_bit(result, i, octaspire_utf8_private_get_bit_of_uint8(buffer[0], i));
            }
        }
        break;

        case 2:
        {
            // 110xxxxx 10xxxxxx

            for (size_t i = 0; i < 5; ++i)
            {
                octaspire_utf8_private_set_bit(result, i+6, octaspire_utf8_private_get_bit_of_uint8(buffer[0], i));
            }

            for (size_t i = 0; i < 6; ++i)
            {
                octaspire_utf8_private_set_bit(result, i,  octaspire_utf8_private_get_bit_of_uint8(buffer[1], i));
            }

            if (*result <= 0x7F)
            {
                return OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER;
            }
        }
        break;

        case 3:
        {
            // 1110xxxx 10xxxxxx 10xxxxxx

            for (size_t i = 0; i < 4; ++i)
            {
                octaspire_utf8_private_set_bit(result, i+12, octaspire_utf8_private_get_bit_of_uint8(buffer[0], i));
            }

            for (size_t i = 0; i < 6; ++i)
            {
                octaspire_utf8_private_set_bit(result, i+6, octaspire_utf8_private_get_bit_of_uint8(buffer[1], i));
            }

            for (size_t i = 0; i < 6; ++i)
            {
                octaspire_utf8_private_set_bit(result, i,  octaspire_utf8_private_get_bit_of_uint8(buffer[2], i));
            }

            if (*result <= 2047)
            {
                return OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER;
            }
        }
        break;

        case 4:
        {
            // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

            for (size_t i = 0; i < 3; ++i)
            {
                octaspire_utf8_private_set_bit(result, i+18, octaspire_utf8_private_get_bit_of_uint8(buffer[0], i));
            }

            for (size_t i = 0; i < 6; ++i)
            {
                octaspire_utf8_private_set_bit(result, i+12, octaspire_utf8_private_get_bit_of_uint8(buffer[1], i));
            }

            for (size_t i = 0; i < 6; ++i)
            {
                octaspire_utf8_private_set_bit(result, i+6, octaspire_utf8_private_get_bit_of_uint8(buffer[2], i));
            }

            for (size_t i = 0; i < 6; ++i)
            {
                octaspire_utf8_private_set_bit(result, i,  octaspire_utf8_private_get_bit_of_uint8(buffer[3], i));
            }

            if (*result <= 65535)
            {
                return OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER;
            }
        }
        break;
    }

    return OCTASPIRE_UTF8_DECODE_STATUS_OK;
}

octaspire_utf8_decode_status_t octaspire_utf8_decode_character(char const * const text, size_t const textLengthInOctets, uint32_t *result, int *numoctets)
{
    if (!text || textLengthInOctets == 0 || text[0] == '\0')
    {
        *result = 0;
        *numoctets = 0;
        return OCTASPIRE_UTF8_DECODE_STATUS_INPUT_IS_NULL;
    }

    *result = 0;
    *numoctets = octaspire_utf8_private_octets_in_next(text, textLengthInOctets);

    if (*numoctets <= 0 || *numoctets > 4)
    {
        return OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS;
    }

    if ((size_t)(*numoctets) > textLengthInOctets)
    {
        return OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS;
    }

    size_t numOctetsAvailable = 0;

    for (size_t i = 0; i < octaspire_helpers_min_size_t(4, textLengthInOctets); ++i)
    {
        if (text[i] == '\0')
        {
            break;
        }
        else
        {
            ++numOctetsAvailable;
        }
    }

    return octaspire_utf8_private_decode_helper(text, (size_t)*numoctets, numOctetsAvailable, result);
}

octaspire_utf8_decode_status_t octaspire_utf8_decode_character_from_buffer(
    char const * const buffer,
    size_t const bufferLengthInOctets,
    size_t const currentIndex,
    uint32_t *result,
    int *numoctets)
{
    if (!buffer)
    {
        *result = 0;
        *numoctets = 0;
        return OCTASPIRE_UTF8_DECODE_STATUS_INPUT_IS_NULL;
    }

    *result = 0;
    *numoctets = octaspire_utf8_private_octets_in_next_from_buffer(buffer, bufferLengthInOctets, currentIndex);

    if (*numoctets <= 0 || *numoctets > 4)
    {
        return OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS;
    }

    size_t numOctetsAvailable = 0;

    if (bufferLengthInOctets > currentIndex)
    {
        numOctetsAvailable = bufferLengthInOctets - currentIndex;
    }

    return octaspire_utf8_private_decode_helper(buffer, (size_t)*numoctets, numOctetsAvailable, result);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../src/octaspire_utf8.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../src/octaspire_container_vector.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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


struct octaspire_container_vector_t
{
    void   *elements;
    size_t  elementSize;
    size_t  numElements;
    size_t  numAllocated;
    size_t  compactingLimitForAllocated;
    octaspire_container_vector_element_callback_t elementReleaseCallback;
    octaspire_memory_allocator_t *allocator;
    bool    elementIsPointer;
    char    padding[7];
};

static size_t const OCTASPIRE_CONTAINER_VECTOR_INITIAL_SIZE = 1;

static void *octaspire_container_vector_private_index_to_pointer(
    octaspire_container_vector_t * const self,
    size_t const index)
{
    assert(self->elements);
    assert(index < self->numAllocated);
    return ((char*)self->elements) + (self->elementSize * index);
}

static void const *octaspire_container_vector_private_index_to_pointer_const(
    octaspire_container_vector_t const * const self,
    size_t const index)
{
    return ((char const * const)self->elements) + (self->elementSize * index);
}

static bool octaspire_container_vector_private_grow(
    octaspire_container_vector_t *self,
    float const factor)
{
    size_t const newNumAllocated = (size_t)(self->numAllocated * fmaxf(2, factor));

    void *newElements = octaspire_memory_allocator_realloc(
        self->allocator,
        self->elements,
        self->elementSize * newNumAllocated);

    if (!newElements)
    {
        return false;
    }

    self->elements     = newElements;
    self->numAllocated = newNumAllocated;

    // Initialize new elements to zero.
    for (size_t i = self->numElements; i < self->numAllocated; ++i)
    {
        void *s = ((char*)self->elements) + (i * self->elementSize);

        if (s != memset(s, 0, self->elementSize))
        {
            abort();
        }
    }

    return true;
}

static bool octaspire_container_vector_private_compact(
    octaspire_container_vector_t *self)
{
    if (self->numAllocated <= 1)
    {
        return true;
    }

    if (self->numAllocated <= (self->numElements * 3))
    {
        return true;
    }

    if (self->numAllocated <= self->compactingLimitForAllocated)
    {
        return true;
    }

    size_t newNumAllocated =
        self->numElements ? self->numElements : OCTASPIRE_CONTAINER_VECTOR_INITIAL_SIZE;

    if (newNumAllocated < self->compactingLimitForAllocated)
    {
        newNumAllocated = self->compactingLimitForAllocated;
    }

    void *newElements = octaspire_memory_allocator_realloc(
        self->allocator,
        self->elements,
        self->elementSize * newNumAllocated);

    if (!newElements)
    {
        return false;
    }

    self->elements     = newElements;
    self->numAllocated = newNumAllocated;

    return true;
}

octaspire_container_vector_t *octaspire_container_vector_new(
    size_t const elementSize,
    bool const elementIsPointer,
    octaspire_container_vector_element_callback_t elementReleaseCallback,
    octaspire_memory_allocator_t *allocator)
{
    return octaspire_container_vector_new_with_preallocated_elements(
        elementSize,
        elementIsPointer,
        OCTASPIRE_CONTAINER_VECTOR_INITIAL_SIZE,
        elementReleaseCallback,
        allocator);
}

octaspire_container_vector_t *octaspire_container_vector_new_with_preallocated_elements(
    size_t const elementSize,
    bool const elementIsPointer,
    size_t const numElementsPreAllocated,
    octaspire_container_vector_element_callback_t elementReleaseCallback,
    octaspire_memory_allocator_t *allocator)
{
    octaspire_container_vector_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_container_vector_t));

    if (!self)
    {
        return self;
    }

    self->allocator        = allocator;
    self->elementSize      = elementSize ? elementSize : sizeof(char);
    self->elementIsPointer = elementIsPointer;
    self->numElements      = 0;

    self->numAllocated = numElementsPreAllocated ?
        numElementsPreAllocated : OCTASPIRE_CONTAINER_VECTOR_INITIAL_SIZE;

    self->compactingLimitForAllocated = self->numAllocated;

    self->elements     =
        octaspire_memory_allocator_malloc(self->allocator, self->elementSize * self->numAllocated);

    if (!self->elements)
    {
        octaspire_container_vector_release(self);
        self = 0;
        return 0;
    }

    self->elementReleaseCallback  = elementReleaseCallback;

    return self;
}

octaspire_container_vector_t *octaspire_container_vector_new_shallow_copy(
    octaspire_container_vector_t * other,
    octaspire_memory_allocator_t * allocator)
{
    octaspire_container_vector_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_container_vector_t));

    if (!self)
    {
        return self;
    }

    self->allocator    = allocator;

    self->elementSize  = octaspire_container_vector_get_element_size_in_octets(other);
    self->numElements  = octaspire_container_vector_get_length(other);
    self->numAllocated = self->numElements;
    self->compactingLimitForAllocated = other->compactingLimitForAllocated;

    // This is here to prevent assert on octaspire_memory_allocator_malloc
    // on 0 size of allocation. Should that check be removed, or this?
    if (self->numAllocated == 0)
    {
        self->numAllocated = 1;
    }

    self->elements     = octaspire_memory_allocator_malloc(
        self->allocator,
        self->elementSize * self->numAllocated);

    if (!self->elements)
    {
        octaspire_container_vector_release(self);
        self = 0;
        return 0;
    }

    self->elementReleaseCallback =
        octaspire_container_vector_get_element_release_callback_const(other);

    if (memcpy(
        self->elements,
        octaspire_container_vector_get_element_at_const(other, 0),
        (self->numElements * self->elementSize)) != self->elements)
    {
        abort();
    }

    return self;
}

void octaspire_container_vector_release(octaspire_container_vector_t *self)
{
    if (!self)
    {
        return;
    }

    if (self->elementReleaseCallback)
    {
        octaspire_container_vector_for_each(self, self->elementReleaseCallback);
    }

    assert(self->allocator);

    octaspire_memory_allocator_free(self->allocator, self->elements);
    octaspire_memory_allocator_free(self->allocator, self);
}

// Vector can never be compacted smaller than this limit, if set
void octaspire_container_vector_set_compacting_limit_for_preallocated_elements(
    octaspire_container_vector_t * const self,
    size_t const numPreAllocatedElementsAtLeastPresentAtAnyMoment)
{
    self->compactingLimitForAllocated = numPreAllocatedElementsAtLeastPresentAtAnyMoment;
}

size_t octaspire_container_vector_get_length(
    octaspire_container_vector_t const * const self)
{
    assert(self);
    return self->numElements;
}

size_t octaspire_container_vector_get_length_in_octets(
    octaspire_container_vector_t const * const self)
{
    return self->numElements * self->elementSize;
}

bool octaspire_container_vector_is_empty(
    octaspire_container_vector_t const * const self)
{
    return (self->numElements == 0);
}

bool octaspire_container_vector_remove_element_at(
    octaspire_container_vector_t * const self,
    size_t const index)
{
    if (octaspire_container_vector_is_empty(self))
    {
        return false;
    }

    if (index >= octaspire_container_vector_get_length(self))
    {
        return false;
    }

    if (self->elementReleaseCallback)
    {
        if (self->elementIsPointer)
        {
            self->elementReleaseCallback(*(void**)octaspire_container_vector_private_index_to_pointer(self, index));
        }
        else
        {
            self->elementReleaseCallback(octaspire_container_vector_private_index_to_pointer(self, index));
        }
    }

    if ((index + 1) != self->numElements)
    {
        size_t const numOctetsToMove = (self->numElements - index - 1) * self->elementSize;
        void *moveTarget = octaspire_container_vector_private_index_to_pointer(self, index);
        void *moveSource = octaspire_container_vector_private_index_to_pointer(self, index + 1);

        if (moveTarget != memmove(moveTarget, moveSource, numOctetsToMove))
        {
            abort();
        }
    }

    --(self->numElements);

    return true;
}

void *octaspire_container_vector_get_element_at(
    octaspire_container_vector_t * const self,
    size_t const index)
{
    if (index >= octaspire_container_vector_get_length(self))
    {
        return 0;
    }

    void *result = octaspire_container_vector_private_index_to_pointer(self, index);

    if (self->elementIsPointer)
    {
        return *(void**)result;
    }

    return result;
}

void const *octaspire_container_vector_get_element_at_const(
    octaspire_container_vector_t const * const self,
    size_t const index)
{
    if (index >= octaspire_container_vector_get_length(self))
    {
        return 0;
    }

    void const * const result = octaspire_container_vector_private_index_to_pointer_const(self, index);

    if (self->elementIsPointer)
    {
        return *(void const * const *)result;
    }

    return result;
}

size_t octaspire_container_vector_get_element_size_in_octets(
    octaspire_container_vector_t const * const self)
{
    return self->elementSize;
}

bool octaspire_container_vector_insert_element_before_the_element_at_index(
    octaspire_container_vector_t *self,
    void const *element,
    ptrdiff_t const index)
{
    if (octaspire_container_vector_is_empty(self))
    {
        return false;
    }

    size_t realIndexToUse = 0;

    if (index < 0)
    {
        ptrdiff_t const tmpIdx = (ptrdiff_t)octaspire_container_vector_get_length(self) + index;

        if (tmpIdx < 0)
        {
            abort();
        }

        realIndexToUse = (size_t)tmpIdx;
    }
    else
    {
        if ((size_t)index >= octaspire_container_vector_get_length(self))
        {
            return false;
        }

        realIndexToUse = (size_t)index;
    }

    assert(realIndexToUse < octaspire_container_vector_get_length(self));

    // Make room for the new element
    if (self->numElements >= self->numAllocated)
    {
        if (!octaspire_container_vector_private_grow(self, 2))
        {
            return false;
        }
    }

    size_t const numOctetsToMove = (self->numElements - realIndexToUse) * self->elementSize;
    void *moveTarget = octaspire_container_vector_private_index_to_pointer(self, realIndexToUse + 1);
    void *moveSource = octaspire_container_vector_private_index_to_pointer(self, realIndexToUse);

    if (moveTarget != memmove(moveTarget, moveSource, numOctetsToMove))
    {
        abort();
    }

    // Copy the new element into the vector
    void *copyTarget = octaspire_container_vector_private_index_to_pointer(self, realIndexToUse);

    if (copyTarget != memcpy(copyTarget, element, self->elementSize))
    {
        abort();
    }

    ++(self->numElements);

    return true;
}

bool octaspire_container_vector_insert_element_at(
    octaspire_container_vector_t * const self,
    void const * const element,
    size_t const index)
{
    size_t const originalNumElements = self->numElements;

    while (index >= self->numAllocated)
    {
        if (!octaspire_container_vector_private_grow(
                self,
                ceilf((float)index / (float)self->numAllocated)))
        {
            return false;
        }
    }

    for (size_t i = originalNumElements; i < index; ++i)
    {
        void *s = octaspire_container_vector_private_index_to_pointer(self, i);

        if (s != memset(s, 0, self->elementSize))
        {
            abort();
        }
        ++(self->numElements);
    }

    void *target = octaspire_container_vector_private_index_to_pointer(self, index);

    if (target != memcpy(target, element, self->elementSize))
    {
        abort();
    }

    if (index >= self->numElements)
    {
        ++(self->numElements);
    }

    return true;
}

bool octaspire_container_vector_replace_element_at(
    octaspire_container_vector_t *self,
    size_t const index,
    void const *element)
{
    if (index >= octaspire_container_vector_get_length(self))
    {
        return false;
    }

    if (self->elementReleaseCallback)
    {
        if (self->elementIsPointer)
        {
            self->elementReleaseCallback(*(void**)octaspire_container_vector_private_index_to_pointer(self, index));
        }
        else
        {
            self->elementReleaseCallback(octaspire_container_vector_private_index_to_pointer(self, index));
        }
    }

    return octaspire_container_vector_insert_element_at(self, element, index);
}

bool octaspire_container_vector_push_front_element(
    octaspire_container_vector_t *self,
    void const *element)
{
    if (octaspire_container_vector_is_empty(self))
    {
        return octaspire_container_vector_push_back_element(self, element);
    }

    return octaspire_container_vector_insert_element_before_the_element_at_index(
        self,
        element,
        0);
}

bool octaspire_container_vector_push_back_element(
    octaspire_container_vector_t * const self,
    void const * const element)
{
    return octaspire_container_vector_insert_element_at(
        self,
        element,
        octaspire_container_vector_get_length(self));
}

bool octaspire_container_vector_push_back_char(
    octaspire_container_vector_t *self,
    char const element)
{
    if (self->elementSize != sizeof(element))
    {
        return false;
    }

    return octaspire_container_vector_insert_element_at(
        self,
        &element,
        octaspire_container_vector_get_length(self));
}

void octaspire_container_vector_for_each(
    octaspire_container_vector_t *self,
    octaspire_container_vector_element_callback_t callback)
{
    assert(self);
    assert(callback);

    for (size_t i = 0; i < octaspire_container_vector_get_length(self); ++i)
    {
        callback(octaspire_container_vector_get_element_at(self, i));
    }
}

bool octaspire_container_vector_pop_back_element(
    octaspire_container_vector_t *self)
{
    if (octaspire_container_vector_is_empty(self))
    {
        return false;
    }

    --(self->numElements);

    return octaspire_container_vector_private_compact(self);
}

void *octaspire_container_vector_peek_back_element(
    octaspire_container_vector_t *self)
{
    if (octaspire_container_vector_is_empty(self))
    {
        return 0;
    }

    return octaspire_container_vector_get_element_at(
        self,
        octaspire_container_vector_get_length(self) - 1);
}

void const * octaspire_container_vector_peek_back_element_const(
    octaspire_container_vector_t const * const self)
{
    if (octaspire_container_vector_is_empty(self))
    {
        return 0;
    }

    return octaspire_container_vector_get_element_at_const(
        self,
        octaspire_container_vector_get_length(self) - 1);
}

bool octaspire_container_vector_pop_front_element(
    octaspire_container_vector_t *self)
{
    if (octaspire_container_vector_is_empty(self))
    {
        return false;
    }

    --(self->numElements);

    if (self->numElements > 0)
    {
        void *dest = octaspire_container_vector_private_index_to_pointer(self, 0);
        void *src  = octaspire_container_vector_private_index_to_pointer(self, 1);

        if (dest != memmove(dest, src, (self->elementSize * self->numElements)))
        {
            abort();
        }
    }

    return octaspire_container_vector_private_compact(self);
}

void *octaspire_container_vector_peek_front_element(
    octaspire_container_vector_t *self)
{
    if (octaspire_container_vector_is_empty(self))
    {
        return 0;
    }

    return octaspire_container_vector_get_element_at(self, 0);
}

void const * octaspire_container_vector_peek_front_element_const(
    octaspire_container_vector_t const * const self)
{
    if (octaspire_container_vector_is_empty(self))
    {
        return 0;
    }

    return octaspire_container_vector_get_element_at_const(self, 0);
}

octaspire_container_vector_element_callback_t octaspire_container_vector_get_element_release_callback_const(octaspire_container_vector_t const * const self)
{
    return self->elementReleaseCallback;
}

bool octaspire_container_vector_clear(
    octaspire_container_vector_t * const self)
{
    if (octaspire_container_vector_is_empty(self))
    {
        return false;
    }

    self->numElements = 0;

    return octaspire_container_vector_private_compact(self);
}

void octaspire_container_vector_sort(
    octaspire_container_vector_t * const self,
    octaspire_container_vector_element_compare_function_t elementCompareFunction)
{
    qsort(
        self->elements,
        octaspire_container_vector_get_length(self),
        octaspire_container_vector_get_element_size_in_octets(self),
        elementCompareFunction);
}

bool octaspire_container_vector_is_valid_index(
    octaspire_container_vector_t const * const self,
    ptrdiff_t const index)
{
    // TODO Should indexing with negative indices from back be supported?
    if (index < 0)
    {
        return false;
    }

    size_t const len = octaspire_container_vector_get_length(self);

    if (!len)
    {
        return false;
    }

    return ((size_t)index < len);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../src/octaspire_container_vector.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../src/octaspire_container_utf8_string.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

struct octaspire_container_utf8_string_t
{
    octaspire_container_vector_t                   *octets;
    octaspire_container_vector_t                   *ucsCharacters;
    octaspire_memory_allocator_t                   *allocator;
    size_t                                          errorAtOctet;
    octaspire_container_utf8_string_error_status_t  errorStatus;
    char                                            padding[4];
};

static char const octaspire_container_utf8_string_private_null_octet = '\0';


// Prototypes for private functions /////////////////////////////////////////
static bool octaspire_container_utf8_string_private_check_substring_match_at(
    octaspire_container_utf8_string_t const * const self,
    size_t const startFromIndex,
    octaspire_container_utf8_string_t const * const substring);

static size_t octaspire_container_utf8_string_private_ucs_character_index_to_octets_index(
    octaspire_container_utf8_string_t const * const self,
    size_t const index);

static bool octaspire_container_utf8_string_private_is_string_at_index(
    octaspire_container_utf8_string_t const * const self,
    size_t const selfIndex,
    octaspire_container_utf8_string_t const * const str,
    size_t const strFirstIndex,
    size_t const strLastIndex);
//////////////////////////////////////////////////////////////////////////////


octaspire_container_utf8_string_t *octaspire_container_utf8_string_new(
    char const * const str,
    octaspire_memory_allocator_t *allocator)
{
    return octaspire_container_utf8_string_new_from_buffer(
        str,
        str ? strlen(str) : 0,
        allocator);
}

octaspire_container_utf8_string_t *octaspire_container_utf8_string_new_from_buffer(
    char const * const buffer,
    size_t const lengthInOctets,
    octaspire_memory_allocator_t *allocator)
{
    octaspire_container_utf8_string_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_container_utf8_string_t));

    if (!self)
    {
        return 0;
    }

    self->allocator        = allocator;

    self->octets           = octaspire_container_vector_new_with_preallocated_elements(
        sizeof(char),
        false,
        lengthInOctets,
        0,
        self->allocator);

    if (!self->octets)
    {
        octaspire_container_utf8_string_release(self);
        self = 0;
        return 0;
    }

    // We cannot know how many actual UCS characters there are in buffer, because
    // characters can be encoded between one and four octets. To speed up allocation,
    // without allocating too much space, we preallocate lengthInOctets / 4 characters.
    self->ucsCharacters    = octaspire_container_vector_new_with_preallocated_elements(
        sizeof(uint32_t),
        false,
        lengthInOctets / 4,
        0,
        self->allocator);

    if (!self->ucsCharacters)
    {
        octaspire_container_utf8_string_release(self);
        self = 0;
        return 0;
    }

    self->errorStatus      = OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK;
    self->errorAtOctet     = 0;

    if (buffer && lengthInOctets)
    {
        size_t index = 0;
        uint32_t ucsChar = 0;
        int numOctets = 0;
        while (index < lengthInOctets)
        {
            // TODO XXX is (lengthInOctets - index) correct?
            octaspire_utf8_decode_status_t status =
                octaspire_utf8_decode_character(buffer + index, (lengthInOctets - index), &ucsChar, &numOctets);

            if (status != OCTASPIRE_UTF8_DECODE_STATUS_OK)
            {
                self->errorStatus  = OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_DECODING_ERROR;
                self->errorAtOctet = index;
                break;
            }

            if (numOctets > 0)
            {
                for (int i = 0; i < numOctets; ++i)
                {
                    if (!octaspire_container_vector_push_back_element(self->octets, buffer + index + i))
                    {
                        // This should never happen, because the 'self->octets' is preallocated
                        // to contain enough space. These lines inside the if-clause are problematic
                        // to test with an unit test (cannot?). Assert could be used here.
                        // But maybe this is still a better alternative?
                        octaspire_container_utf8_string_release(self);
                        self = 0;
                        return 0;
                    }
                }

                if (!octaspire_container_vector_push_back_element(self->ucsCharacters, &ucsChar))
                {
                    octaspire_container_utf8_string_release(self);
                    self = 0;
                    return 0;
                }

                index += (size_t)numOctets;
            }
        }
    }

    // Append null byte to allow use with libc
    if (!octaspire_container_vector_push_back_element(
        self->octets,
        &octaspire_container_utf8_string_private_null_octet))
    {
        octaspire_container_utf8_string_release(self);
        self = 0;
        return 0;
    }

    return self;
}

octaspire_container_utf8_string_t *octaspire_container_utf8_string_new_format(
    octaspire_memory_allocator_t *allocator,
    char const * const fmt,
    ...)
{
    va_list arguments;
    va_start(arguments, fmt);

    octaspire_container_utf8_string_t *result =
        octaspire_container_utf8_string_new_vformat(allocator, fmt, arguments);

    va_end(arguments);

    return result;
}

octaspire_container_utf8_string_t *octaspire_container_utf8_string_new_vformat(
    octaspire_memory_allocator_t *allocator,
    char const * const fmt,
    va_list arguments)
{
    va_list copyOfVarArgs;
    va_copy(copyOfVarArgs, arguments);

    octaspire_container_utf8_string_error_status_t errorStatus =
        OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK;

    size_t                                         errorAtOctet = 0;

    octaspire_container_utf8_string_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_container_utf8_string_t));

    if (!self)
    {
        return self;
    }

    self->allocator        = allocator;

    assert(self->allocator);

    self->octets           = octaspire_container_vector_new(sizeof(char), false, 0, self->allocator);
    self->ucsCharacters    = octaspire_container_vector_new(sizeof(uint32_t), false, 0, self->allocator);

    octaspire_container_utf8_string_reset_error_status(self);

#if 0
    octaspire_container_vector_t *vec = octaspire_container_vector_new(
        sizeof(char),
        false,
        0,
        allocator);
#else
    size_t buflen = 8;
    char *buffer = octaspire_memory_allocator_malloc(allocator, buflen);
    //char *buffer = malloc(buflen);
    assert(buffer);
#endif

    octaspire_container_vector_t *vec2 = octaspire_container_vector_new(
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
            errorStatus = OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_ENCODING_ERROR;
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
        n = vsnprintf(
            buffer,
            buflen,
            fmt,
            copyOfVarArgs);

#ifdef OCTASPIRE_CLANG_PRAGMAS_ENABLED
#pragma clang diagnostic pop
#endif

        va_end(copyOfVarArgs);

        if (n < 0)
        {
            // Encoding error in C99 or, on older glibc, the output was truncated.
            // Try again with more space. Because we don't know how much
            // space is required, lets double it (and make sure that the length is not zero). Because we don't know
            // is the reason for failure an encoding error or missing space,
            // we will start counting to prevent looping forever.
            ++negativeResultCounter;

            buflen *= 2;
            char *tmpPtr = octaspire_memory_allocator_realloc(allocator, buffer, buflen);
            //char *tmpPtr = realloc(buffer, buflen);

            if (tmpPtr)
            {
                buffer = tmpPtr;
                memset(buffer, 0, buflen);
            }
            else
            {
                //free(buffer);
                octaspire_memory_allocator_free(allocator, buffer);
                buffer = 0;
                return 0;
            }
        }
        else if ((size_t)n >= buflen)
        {
            // TODO calculate exact size

            buflen *= 2;
            char *tmpPtr = octaspire_memory_allocator_realloc(allocator, buffer, buflen);
            //char *tmpPtr = realloc(buffer, buflen);

            if (tmpPtr)
            {
                buffer = tmpPtr;
                memset(buffer, 0, buflen);
            }
            else
            {
                //free(buffer);
                octaspire_memory_allocator_free(allocator, buffer);
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

                octaspire_container_vector_push_back_element(vec2, &c);
            }

            if (!octaspire_container_vector_push_back_char(
                    vec2,
                    octaspire_container_utf8_string_private_null_octet))
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

    //assert(!octaspire_container_vector_is_empty(vec2));

    if (!octaspire_container_vector_push_back_char(vec2, octaspire_container_utf8_string_private_null_octet))
    {
        abort();
    }

    octaspire_container_utf8_string_t *tmpStr = octaspire_container_utf8_string_new(
        octaspire_container_vector_get_element_at(vec2, 0),
        allocator);

    octaspire_container_utf8_string_release(self);
    self = tmpStr;

    assert(self);


    if (octaspire_container_vector_is_empty(self->octets) ||
            *(char const * const)octaspire_container_vector_peek_back_element_const(self->octets) != octaspire_container_utf8_string_private_null_octet)
    {
        octaspire_container_vector_push_back_element(self->octets, &octaspire_container_utf8_string_private_null_octet);
    }

    if (!octaspire_container_utf8_string_is_error(self))
    {
        if (errorStatus != OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK)
        {
            self->errorStatus  = errorStatus;
            self->errorAtOctet = errorAtOctet;
        }
    }

    octaspire_memory_allocator_free(allocator, buffer);
    //free(buffer);
    buffer = 0;

    octaspire_container_vector_release(vec2);
    vec2 = 0;

    assert(!octaspire_container_vector_is_empty(self->octets));
    assert(octaspire_container_utf8_string_private_null_octet == *(char const * const)octaspire_container_vector_get_element_at(
        self->octets,
        octaspire_container_vector_get_length(self->octets) - 1));

    return self;
}











octaspire_container_utf8_string_t *octaspire_container_utf8_string_new_copy(
    octaspire_container_utf8_string_t const * const other,
    octaspire_memory_allocator_t *allocator)
{
    octaspire_container_utf8_string_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_container_utf8_string_t));

    if (!self)
    {
        return self;
    }

    self->octets        = octaspire_container_vector_new_shallow_copy(other->octets, allocator);
    self->ucsCharacters = octaspire_container_vector_new_shallow_copy(other->ucsCharacters, allocator);
    self->errorStatus   = other->errorStatus;
    self->errorAtOctet  = other->errorAtOctet;
    self->allocator     = allocator;

    return self;
}

octaspire_container_utf8_string_t *octaspire_container_utf8_string_new_substring_from_given_index_and_length(
    octaspire_container_utf8_string_t const * const other,
    octaspire_memory_allocator_t *allocator,
    size_t const ucsCharStartIndex,
    size_t const lengthInUcsChars)
{
    assert(other);
    assert(allocator);

    size_t const endIndex = ucsCharStartIndex + lengthInUcsChars;

    if (endIndex >= octaspire_container_utf8_string_get_length_in_ucs_characters(other))
    {
        return 0;
    }

    octaspire_container_utf8_string_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_container_utf8_string_t));

    if (!self)
    {
        return self;
    }

    self->allocator     = allocator;

    self->octets           = octaspire_container_vector_new_with_preallocated_elements(
        sizeof(char),
        false,
        lengthInUcsChars, // We don't know exact value, this is the smallest value possible
        0,
        self->allocator);

    if (!self->octets)
    {
        octaspire_container_utf8_string_release(self);
        self = 0;
        return 0;
    }

    octaspire_container_vector_push_back_element(
        self->octets,
        &octaspire_container_utf8_string_private_null_octet);

    self->ucsCharacters    = octaspire_container_vector_new_with_preallocated_elements(
        sizeof(uint32_t),
        false,
        lengthInUcsChars,
        0,
        self->allocator);

    if (!self->ucsCharacters)
    {
        octaspire_container_utf8_string_release(self);
        self = 0;
        return 0;
    }

    self->errorStatus   = OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK;
    self->errorAtOctet  = 0;

    for (size_t i = 0; i < lengthInUcsChars; ++i)
    {
        octaspire_container_utf8_string_push_back_ucs_character(
            self,
            octaspire_container_utf8_string_get_ucs_character_at_index(
                other,
                ucsCharStartIndex + i));
    }

    return self;
}

void octaspire_container_utf8_string_release(octaspire_container_utf8_string_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_container_vector_release(self->octets);
    octaspire_container_vector_release(self->ucsCharacters);

    octaspire_memory_allocator_free(self->allocator, self);
}

bool octaspire_container_utf8_string_is_empty(
    octaspire_container_utf8_string_t const * const self)
{
    return octaspire_container_utf8_string_get_length_in_ucs_characters(self) == 0;
}

size_t octaspire_container_utf8_string_get_length_in_ucs_characters(
    octaspire_container_utf8_string_t const * const self)
{
    assert(self);
    return octaspire_container_vector_get_length(self->ucsCharacters);
}

size_t octaspire_container_utf8_string_get_length_in_octets(
    octaspire_container_utf8_string_t const * const self)
{
    // Must have at least the added NULL-byte
    assert(octaspire_container_vector_get_length(self->octets));
    // Subtract one of the length, because of the added NULL-byte.
    return octaspire_container_vector_get_length(self->octets) - 1;
}

uint32_t octaspire_container_utf8_string_get_ucs_character_at_index(
    octaspire_container_utf8_string_t const * const self, size_t const index)
{
    assert(index < octaspire_container_utf8_string_get_length_in_ucs_characters(self));
    return *(uint32_t*)octaspire_container_vector_get_element_at(self->ucsCharacters, index);
}

char const * octaspire_container_utf8_string_get_c_string(
    octaspire_container_utf8_string_t const * const self)
{
    assert(!octaspire_container_vector_is_empty(self->octets));
    assert(*(char const*)octaspire_container_vector_peek_back_element_const(self->octets) == '\0');
    return octaspire_container_vector_peek_front_element_const(self->octets);
}

bool octaspire_container_utf8_string_is_error(
    octaspire_container_utf8_string_t const * const self)
{
    return self->errorStatus != OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK;
}

octaspire_container_utf8_string_error_status_t octaspire_container_utf8_string_get_error_status(
    octaspire_container_utf8_string_t const * const self)
{
    return self->errorStatus;
}

size_t octaspire_container_utf8_string_get_error_position_in_octets(
    octaspire_container_utf8_string_t const * const self)
{
    return self->errorAtOctet;
}

void octaspire_container_utf8_string_reset_error_status(
    octaspire_container_utf8_string_t * const self)
{
    self->errorStatus   = OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK;
    self->errorAtOctet  = 0;
}

bool octaspire_container_utf8_string_concatenate(
    octaspire_container_utf8_string_t * const self,
    octaspire_container_utf8_string_t const * const other)
{
    return octaspire_container_utf8_string_concatenate_c_string(
        self,
        octaspire_container_utf8_string_get_c_string(other));
}

bool octaspire_container_utf8_string_concatenate_c_string(
    octaspire_container_utf8_string_t * const self,
    char const * const str)
{
    octaspire_container_utf8_string_reset_error_status(self);

    if (!str || str[0] == '\0')
    {
        return true;
    }

    // Make sure NULL char is present at the end
    assert(!octaspire_container_vector_is_empty(self->octets));

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
            self->errorStatus  = OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_DECODING_ERROR;
            self->errorAtOctet = index;
            break;
        }

        for (int i = 0; i < numOctets; ++i)
        {
            //if (!octaspire_container_vector_push_back_element(self->octets, str + index + i))
            if (!octaspire_container_vector_insert_element_before_the_element_at_index(self->octets, str + index + i, (ptrdiff_t)(octaspire_container_vector_get_length(self->octets) - 1)))
            {
                result = false;
            }
        }

        if (!octaspire_container_vector_push_back_element(self->ucsCharacters, &ucsChar))
        {
            result = false;
        }

        index += (size_t)numOctets;
    }
/*
    // Append null byte to allow use with libc
    if (!octaspire_container_vector_push_back_element(
        self->octets,
        &octaspire_container_utf8_string_private_null_octet))
    {
        result = false;
    }
*/

    return result;
}

bool octaspire_container_utf8_string_concatenate_format(
    octaspire_container_utf8_string_t * const self,
    char const * const fmt,
    ...)
{
    va_list arguments;
    va_start(arguments, fmt);

    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_vformat(self->allocator, fmt, arguments);

    va_end(arguments);

    if (!str)
    {
        return false;
    }

    bool const result = octaspire_container_utf8_string_concatenate_c_string(
        self,
        octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    return result;
}

bool octaspire_container_utf8_string_private_check_substring_match_at(
    octaspire_container_utf8_string_t const * const self,
    size_t const startFromIndex,
    octaspire_container_utf8_string_t const * const substring)
{
    size_t const selfLength = octaspire_container_utf8_string_get_length_in_ucs_characters(self);

    size_t const substringLength =
        octaspire_container_utf8_string_get_length_in_ucs_characters(substring);

    for (size_t i = 0; i < substringLength; ++i)
    {
        if ((startFromIndex + i) >= selfLength)
        {
            return false;
        }

        if (octaspire_container_utf8_string_get_ucs_character_at_index(self, startFromIndex + i) !=
            octaspire_container_utf8_string_get_ucs_character_at_index(substring, i))
        {
            return false;
        }
    }

    return true;
}

ptrdiff_t octaspire_container_utf8_string_find_first_substring(
    octaspire_container_utf8_string_t const * const self,
    size_t const startFromIndex,
    octaspire_container_utf8_string_t const * const substring)
{
    size_t const selfLength = octaspire_container_utf8_string_get_length_in_ucs_characters(self);

    for (size_t i = startFromIndex; i < (startFromIndex + selfLength); ++i)
    {
        if (octaspire_container_utf8_string_private_check_substring_match_at(self, i, substring))
        {
            return (ptrdiff_t)i;
        }
    }

    return -1;
}

size_t octaspire_container_utf8_string_private_ucs_character_index_to_octets_index(
    octaspire_container_utf8_string_t const * const self,
    size_t const index)
{
    assert(index < octaspire_container_utf8_string_get_length_in_ucs_characters(self));

    size_t resultIndex = 0;

    for (size_t i = 0; i < index; ++i)
    {
        // Init this?
        octaspire_utf8_character_t character;

        if (octaspire_utf8_encode_character(
            *(uint32_t*)octaspire_container_vector_get_element_at(self->ucsCharacters, i),
            &character) != OCTASPIRE_UTF8_ENCODE_STATUS_OK)
        {
            abort();
        }

        resultIndex += character.numoctets;
    }

    return resultIndex;
}

bool octaspire_container_utf8_string_remove_character_at(
    octaspire_container_utf8_string_t * const self,
    size_t const index)
{
    if (index >= octaspire_container_utf8_string_get_length_in_ucs_characters(self))
    {
        return false;
    }

    // Init this?
    octaspire_utf8_character_t character;

    if (octaspire_utf8_encode_character(
        *(uint32_t*)octaspire_container_vector_get_element_at(self->ucsCharacters, index),
        &character) != OCTASPIRE_UTF8_ENCODE_STATUS_OK)
    {
        assert(false);
        return false;
    }

    size_t const octetsIndex =
        octaspire_container_utf8_string_private_ucs_character_index_to_octets_index(self, index);

    for (size_t i = 0; i < character.numoctets; ++i)
    {
        if (!octaspire_container_vector_remove_element_at(self->octets, octetsIndex + i))
        {
            assert(false);
            return false;
        }
    }

    if (!octaspire_container_vector_remove_element_at(self->ucsCharacters, index))
    {
        assert(false);
        return false;
    }

    return true;
}

size_t octaspire_container_utf8_string_remove_characters_at(
    octaspire_container_utf8_string_t * const self,
    size_t const startFromIndex,
    size_t const numCharacters)
{
    assert(numCharacters);

    size_t result = 0;

    for (ptrdiff_t i = (ptrdiff_t)numCharacters - 1; i >= 0; --i)
    {
        if (octaspire_container_utf8_string_remove_character_at(self, startFromIndex + (size_t)i))
        {
            ++result;
        }
    }

    return result;
}

size_t octaspire_container_utf8_string_remove_all_substrings(
    octaspire_container_utf8_string_t * const self,
    octaspire_container_utf8_string_t const * const substring)
{
    size_t result = 0;

    size_t const substringLength =
        octaspire_container_utf8_string_get_length_in_ucs_characters(substring);

    while (true)
    {
        if (octaspire_container_utf8_string_is_empty(self))
        {
            return result;
        }

        ptrdiff_t const substringIndex =
            octaspire_container_utf8_string_find_first_substring(self, 0, substring);

        if (substringIndex < 0)
        {
            return result;
        }

        if (octaspire_container_utf8_string_remove_characters_at(self, (size_t)substringIndex, substringLength))
        {
            ++result;
        }
    }
}

bool octaspire_container_utf8_string_clear(
    octaspire_container_utf8_string_t * const self)
{
    bool const result1 = octaspire_container_vector_clear(self->octets);
    bool const result2 = octaspire_container_vector_clear(self->ucsCharacters);

    self->errorStatus  = OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK;
    self->errorAtOctet = 0;

    if (!octaspire_container_vector_push_back_element(
        self->octets,
        &octaspire_container_utf8_string_private_null_octet))
    {
        return false;
    }

    return result1 && result2;
}

bool octaspire_container_utf8_string_is_equal(
    octaspire_container_utf8_string_t const * const self,
    octaspire_container_utf8_string_t const * const other)
{
    assert(self);
    assert(other);
    assert(self->octets);
    assert(other->octets);

    size_t const len = octaspire_container_vector_get_length(self->octets);

    if (octaspire_container_vector_get_length(other->octets) != len)
    {
        return false;
    }

    return memcmp(
        octaspire_container_vector_get_element_at(self->octets,  0),
        octaspire_container_vector_get_element_at(other->octets, 0),
        len) == 0;
}

bool octaspire_container_utf8_string_is_equal_to_c_string(
    octaspire_container_utf8_string_t const * const self,
    char const * const str)
{
    assert(self);
    assert(str);
    assert(octaspire_container_vector_get_length(self->octets) > 0);

    size_t const len = octaspire_container_vector_get_length(self->octets) - 1;

    if (strlen(str) != len)
    {
        return false;
    }

    return memcmp(octaspire_container_vector_get_element_at(self->octets,  0), str, len) == 0;
}


bool octaspire_container_utf8_string_starts_with(
    octaspire_container_utf8_string_t const * const self,
    octaspire_container_utf8_string_t const * const other)
{
    assert(self && other);

    size_t const myLen = octaspire_container_utf8_string_get_length_in_ucs_characters(self);
    size_t const otherLen = octaspire_container_utf8_string_get_length_in_ucs_characters(other);

    if (myLen < otherLen)
    {
        return false;
    }

    for (size_t i = 0; i < otherLen; ++i)
    {
        if (octaspire_container_utf8_string_get_ucs_character_at_index(self,  i) !=
            octaspire_container_utf8_string_get_ucs_character_at_index(other, i))
        {
            return false;
        }
    }

    return true;
}

bool octaspire_container_utf8_string_ends_with(
    octaspire_container_utf8_string_t const * const self,
    octaspire_container_utf8_string_t const * const other)
{
    assert(self && other);


    size_t const myLen = octaspire_container_utf8_string_get_length_in_ucs_characters(self);
    size_t const otherLen = octaspire_container_utf8_string_get_length_in_ucs_characters(other);

    if (myLen < otherLen)
    {
        return false;
    }

    size_t const myStartIndex = myLen - otherLen;

    for (size_t i = 0; i < otherLen; ++i)
    {
        if (octaspire_container_utf8_string_get_ucs_character_at_index(self, myStartIndex + i) !=
            octaspire_container_utf8_string_get_ucs_character_at_index(other, i))
        {
            return false;
        }
    }

    return true;
}







uint32_t octaspire_container_utf8_string_get_hash(
    octaspire_container_utf8_string_t const * const self)
{
    uint32_t hash = 0;

    size_t const realLen = octaspire_container_vector_get_length(self->octets);

    assert(realLen <= INT_MAX);

    int const len = (int)realLen;

    if (!octaspire_container_vector_is_empty(self->octets))
    {
        MurmurHash3_x86_32(
            octaspire_container_vector_get_element_at(self->octets,  0),
            len,
            OCTASPIRE_HELPERS_MURMUR3_HASH_SEED,
            &hash);
    }

    return hash;
}

bool octaspire_container_utf8_string_push_back_ucs_character(
    octaspire_container_utf8_string_t *self,
    uint32_t const character)
{
    assert(self);

    octaspire_utf8_character_t encoded;

    octaspire_utf8_encode_status_t const status = octaspire_utf8_encode_character(
        character,
        &encoded);

    if (status != OCTASPIRE_UTF8_ENCODE_STATUS_OK)
    {
        return false;
    }

    assert(encoded.numoctets > 0);
    assert(!octaspire_container_vector_is_empty(self->octets));

    // TODO revert (rollback) changes if addition fails at any stage.

    for (size_t i = 0; i < encoded.numoctets; ++i)
    {
        if (!octaspire_container_vector_insert_element_before_the_element_at_index(
                self->octets,
                encoded.octets + 4 - encoded.numoctets + i,
                -1))
        {
            return false;
        }
    }

    if (!octaspire_container_vector_push_back_element(self->ucsCharacters, &character))
    {
        return false;
    }

    return true;
}

bool octaspire_container_utf8_string_pop_back_ucs_character(
    octaspire_container_utf8_string_t *self)
{
    assert(self);

    if (octaspire_container_utf8_string_is_empty(self))
    {
        return false;
    }

    return octaspire_container_utf8_string_remove_character_at(
        self,
        octaspire_container_utf8_string_get_length_in_ucs_characters(self) - 1);
}

bool octaspire_container_utf8_string_insert_string_to(
    octaspire_container_utf8_string_t * const self,
    octaspire_container_utf8_string_t const * const str,
    ptrdiff_t const indexToPutFirstCharacter)
{
    size_t realIndexToUse = 0;

    if (indexToPutFirstCharacter < 0)
    {
        realIndexToUse = (size_t)
            ((ptrdiff_t)octaspire_container_utf8_string_get_length_in_ucs_characters(self) +
            indexToPutFirstCharacter);

        if (realIndexToUse >= octaspire_container_utf8_string_get_length_in_ucs_characters(self))
        {
            return false;
        }
    }
    else
    {
        if ((size_t)indexToPutFirstCharacter >=
            octaspire_container_utf8_string_get_length_in_ucs_characters(self))
        {
            return false;
        }

        realIndexToUse = (size_t)indexToPutFirstCharacter;
    }

    size_t index = realIndexToUse;

    char const * const strAsCstr = octaspire_container_utf8_string_get_c_string(str);

    for (size_t i = 0; i < octaspire_container_utf8_string_get_length_in_octets(str); ++i)
    {
        if (!octaspire_container_vector_insert_element_before_the_element_at_index(self->octets, &(strAsCstr[i]), (ptrdiff_t)index))
        {
            return false;
        }

        ++index;
    }

    index = realIndexToUse;

    for (size_t i = 0; i < octaspire_container_utf8_string_get_length_in_ucs_characters(str); ++i)
    {
        uint32_t const c = octaspire_container_utf8_string_get_ucs_character_at_index(str, i);
        if (!octaspire_container_vector_insert_element_before_the_element_at_index(self->ucsCharacters, &c, (ptrdiff_t)index))
        {
            return false;
        }

        ++index;
    }

    return true;
}

octaspire_container_vector_t *octaspire_container_utf8_string_split(
    octaspire_container_utf8_string_t *self,
    char const * const delimiter)
{
    octaspire_container_utf8_string_t *delimString = octaspire_container_utf8_string_new(
        delimiter,
        self->allocator);

    if (!delimString)
    {
        return 0;
    }

    octaspire_container_vector_t *result = octaspire_container_vector_new(
        sizeof(octaspire_container_utf8_string_t*),
        true,
        (octaspire_container_vector_element_callback_t)octaspire_container_utf8_string_release,
        self->allocator);

    if (!result)
    {
        octaspire_container_utf8_string_release(delimString);
        delimString = 0;
        return 0;
    }

    octaspire_container_utf8_string_t *collectorString = octaspire_container_utf8_string_new(
        "",
        self->allocator);

    if (!collectorString)
    {
        octaspire_container_utf8_string_release(delimString);
        delimString = 0;

        octaspire_container_vector_release(result);
        result = 0;
        return 0;
    }

    for (size_t i = 0; i < octaspire_container_utf8_string_get_length_in_ucs_characters(self); ++i)
    {
        octaspire_container_utf8_string_push_back_ucs_character(
            collectorString,
            octaspire_container_utf8_string_get_ucs_character_at_index(self, i));

        if (octaspire_container_utf8_string_is_equal(collectorString, delimString))
        {
            octaspire_container_utf8_string_clear(collectorString);
        }
        else if (octaspire_container_utf8_string_ends_with(collectorString, delimString))
        {
            size_t const numUcsCharsToGet =
                octaspire_container_utf8_string_get_length_in_ucs_characters(collectorString) -
                octaspire_container_utf8_string_get_length_in_ucs_characters(delimString);

            octaspire_container_utf8_string_t *token =
                octaspire_container_utf8_string_new_substring_from_given_index_and_length(
                    collectorString,
                    collectorString->allocator,
                    0,
                    numUcsCharsToGet);

            assert(token);

            octaspire_container_vector_push_back_element(result, &token);

            octaspire_container_utf8_string_clear(collectorString);
        }
    }

    if (!octaspire_container_utf8_string_is_empty(collectorString))
    {
        if (octaspire_container_utf8_string_is_equal(collectorString, delimString))
        {
            octaspire_container_utf8_string_clear(collectorString);
        }
        else if (octaspire_container_utf8_string_ends_with(collectorString, delimString))
        {
            size_t const numUcsCharsToGet =
                octaspire_container_utf8_string_get_length_in_ucs_characters(collectorString) -
                octaspire_container_utf8_string_get_length_in_ucs_characters(delimString);

            octaspire_container_utf8_string_t *token =
                octaspire_container_utf8_string_new_substring_from_given_index_and_length(
                    collectorString,
                    collectorString->allocator,
                    0,
                    numUcsCharsToGet);

            assert(token);

            octaspire_container_vector_push_back_element(result, &token);

            octaspire_container_utf8_string_clear(collectorString);
        }
        else
        {
            octaspire_container_utf8_string_t *token =
                octaspire_container_utf8_string_new_copy(
                    collectorString,
                    collectorString->allocator);

            assert(token);

            octaspire_container_vector_push_back_element(result, &token);

            octaspire_container_utf8_string_clear(collectorString);
        }

        octaspire_container_utf8_string_clear(collectorString);
    }

    octaspire_container_utf8_string_release(collectorString);
    collectorString = 0;

    octaspire_container_utf8_string_release(delimString);
    delimString = 0;

    return result;
}

bool octaspire_container_utf8_string_contains_char(
    octaspire_container_utf8_string_t const * const self,
    uint32_t const character)
{
    for (size_t i = 0; i < octaspire_container_utf8_string_get_length_in_ucs_characters(self); ++i)
    {
        if (octaspire_container_utf8_string_get_ucs_character_at_index(self, i) == character)
        {
            return true;
        }
    }

    return false;
}

bool octaspire_container_utf8_string_contains_only_these_chars(
    octaspire_container_utf8_string_t const * const self,
    octaspire_container_utf8_string_t const * const chars)
{
    for (size_t i = 0; i < octaspire_container_utf8_string_get_length_in_ucs_characters(self); ++i)
    {
        uint32_t const selfChar = octaspire_container_utf8_string_get_ucs_character_at_index(self,  i);

        bool found = false;

        for (size_t j = 0; j < octaspire_container_utf8_string_get_length_in_ucs_characters(chars); ++j)
        {
            if (octaspire_container_utf8_string_get_ucs_character_at_index(chars, j) == selfChar)
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

octaspire_container_vector_t *octaspire_container_utf8_string_find_char(
    octaspire_container_utf8_string_t const * const self,
    octaspire_container_utf8_string_t const * const character,
    size_t const characterIndex)
{
    if (octaspire_container_utf8_string_get_length_in_ucs_characters(character) <= characterIndex)
    {
        return 0;
    }

    octaspire_container_vector_t *result = octaspire_container_vector_new(
        sizeof(size_t),
        false,
        0,
        self->allocator);

    for (size_t i = 0; i < octaspire_container_utf8_string_get_length_in_ucs_characters(self); ++i)
    {
        if (octaspire_container_utf8_string_get_ucs_character_at_index(self, i) ==
            octaspire_container_utf8_string_get_ucs_character_at_index(character, characterIndex))
        {
            octaspire_container_vector_push_back_element(result, &i);
        }
    }

    return result;
}

bool octaspire_container_utf8_string_private_is_string_at_index(
    octaspire_container_utf8_string_t const * const self,
    size_t const selfIndex,
    octaspire_container_utf8_string_t const * const str,
    size_t const strFirstIndex,
    size_t const strLastIndex)
{
    size_t selfIndex2 = selfIndex;
    for (size_t i = strFirstIndex; i <= strLastIndex; ++i)
    {
        if (selfIndex2 >= octaspire_container_utf8_string_get_length_in_ucs_characters(self))
        {
            return false;
        }

        if (octaspire_container_utf8_string_get_ucs_character_at_index(self, selfIndex2) !=
            octaspire_container_utf8_string_get_ucs_character_at_index(str, i))
        {
            return false;
        }

        ++selfIndex2;
    }

    return true;
}

octaspire_container_vector_t *octaspire_container_utf8_string_find_string(
    octaspire_container_utf8_string_t const * const self,
    octaspire_container_utf8_string_t const * const str,
    size_t const strStartIndex,
    size_t const strLength)
{
    if (!strLength)
    {
        return 0;
    }

    if (strStartIndex >= octaspire_container_utf8_string_get_length_in_ucs_characters(str))
    {
        return 0;
    }

    size_t const strEndIndex = strStartIndex + (strLength - 1);

    if (strEndIndex >= octaspire_container_utf8_string_get_length_in_ucs_characters(str))
    {
        return 0;
    }

    octaspire_container_vector_t *result = octaspire_container_vector_new(
        sizeof(size_t),
        false,
        0,
        self->allocator);

    for (size_t i = 0; i < octaspire_container_utf8_string_get_length_in_ucs_characters(self); ++i)
    {
        if (octaspire_container_utf8_string_private_is_string_at_index(
            self,
            i,
            str,
            strStartIndex,
            strEndIndex))
        {
            octaspire_container_vector_push_back_element(result, &i);
        }
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../src/octaspire_container_utf8_string.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../src/octaspire_container_pair.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

struct octaspire_container_pair_t
{
    void   *first;
    void   *second;
    size_t firstSize;
    size_t secondSize;
    octaspire_container_pair_element_callback_t firstReleaseCallback;
    octaspire_container_pair_element_callback_t secondReleaseCallback;
    octaspire_memory_allocator_t *allocator;
    bool   firstIsPointer;
    bool   secondIsPointer;
    char   padding[6];
};

size_t octaspire_container_pair_t_get_sizeof(void)
{
    return sizeof(octaspire_container_pair_t);
}

octaspire_container_pair_t *octaspire_container_pair_new(
    size_t const firstElementSize,
    bool const firstElementIsPointer,
    size_t const secondElementSize,
    bool const secondElementIsPointer,
    octaspire_container_pair_element_callback_t firstElementReleaseCallback,
    octaspire_container_pair_element_callback_t secondElementReleaseCallback,
    octaspire_memory_allocator_t *allocator)
{
    octaspire_container_pair_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_container_pair_t));

    if (!self)
    {
        return self;
    }

    self->allocator             = allocator;
    self->first                 = 0;
    self->second                = 0;
    self->firstSize             = firstElementSize;
    self->firstIsPointer        = firstElementIsPointer;
    self->secondSize            = secondElementSize;
    self->secondIsPointer       = secondElementIsPointer;
    self->firstReleaseCallback  = firstElementReleaseCallback;
    self->secondReleaseCallback = secondElementReleaseCallback;

    self->first = octaspire_memory_allocator_malloc(self->allocator, self->firstSize);

    if (!self->first)
    {
        octaspire_container_pair_release(self);
        self = 0;
        return 0;
    }

    self->second = octaspire_memory_allocator_malloc(self->allocator, self->secondSize);

    if (!self->second)
    {
        octaspire_container_pair_release(self);
        self = 0;
        return 0;
    }

    return self;
}

octaspire_container_pair_t *octaspire_container_pair_new_shallow_copy(
    octaspire_container_pair_t   *other,
    octaspire_memory_allocator_t *allocator)
{
    octaspire_container_pair_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_container_pair_t));

    if (!self)
    {
        return self;
    }

    self->allocator = allocator;
    self->first                 = 0;
    self->second                = 0;
    self->firstSize             = other->firstSize;
    self->firstIsPointer        = other->firstIsPointer;
    self->secondSize            = other->secondSize;
    self->secondIsPointer       = other->secondIsPointer;
    self->firstReleaseCallback  = other->firstReleaseCallback;
    self->secondReleaseCallback = other->secondReleaseCallback;

    self->first  = octaspire_memory_allocator_malloc(self->allocator, self->firstSize);

    if (!self->first)
    {
        octaspire_container_pair_release(self);
        self = 0;
        return 0;
    }

    self->second = octaspire_memory_allocator_malloc(self->allocator, self->secondSize);

    if (!self->second)
    {
        octaspire_container_pair_release(self);
        self = 0;
        return 0;
    }

    if (self->first != memcpy(self->first,  other->first,  self->firstSize))
    {
        octaspire_container_pair_release(self);
        self = 0;
        return 0;
    }

    if (self->second != memcpy(self->second, other->second, self->secondSize))
    {
        octaspire_container_pair_release(self);
        self = 0;
        return 0;
    }

    return self;
}

void octaspire_container_pair_release(octaspire_container_pair_t *self)
{
    if (!self)
    {
        return;
    }

    if (self->firstReleaseCallback)
    {
        if (self->firstIsPointer)
        {
            if (self->first)
            {
                (self->firstReleaseCallback)(*(void**)self->first);
            }
        }
        else
        {
            (self->firstReleaseCallback)(self->first);
        }
    }

    if (self->first)
    {
        octaspire_memory_allocator_free(self->allocator, self->first);
        self->first = 0;
    }

    if (self->secondReleaseCallback)
    {
        if (self->secondIsPointer)
        {
            if (self->second)
            {
                (self->secondReleaseCallback)(*(void**)self->second);
            }
        }
        else
        {
            (self->secondReleaseCallback)(self->second);
        }
    }

    if (self->second)
    {
        octaspire_memory_allocator_free(self->allocator, self->second);
        self->second = 0;
    }

    octaspire_memory_allocator_free(self->allocator, self);
}

void *octaspire_container_pair_get_first(octaspire_container_pair_t *self)
{
    return self->firstIsPointer ? (*(void**)self->first) : self->first;
}

void const *octaspire_container_pair_get_first_const(octaspire_container_pair_t const * const self)
{
    return self->firstIsPointer ? (*(void const **)self->first) : self->first;
}

void *octaspire_container_pair_get_second(octaspire_container_pair_t *self)
{
    return self->secondIsPointer ? (*(void**)self->second) : self->second;
}

void const *octaspire_container_pair_get_second_const(octaspire_container_pair_t const * const self)
{
    return self->secondIsPointer ? (*(void const **)self->second) : self->second;
}

size_t octaspire_container_pair_get_size_of_first_element_in_octets(
    octaspire_container_pair_t const * const self)
{
    return self->firstSize;
}

size_t octaspire_container_pair_get_size_of_second_element_in_octets(
    octaspire_container_pair_t const * const self)
{
    return self->secondSize;
}

void octaspire_container_pair_set(
    octaspire_container_pair_t *self,
    void const *first,
    void const *second)
{
    octaspire_container_pair_set_first( self, first);
    octaspire_container_pair_set_second(self, second);
}

void octaspire_container_pair_set_first(
    octaspire_container_pair_t *self,
    void const *first)
{
    if (self->first != memcpy(self->first,  first,  self->firstSize))
    {
        abort();
    }
}

void octaspire_container_pair_set_second(
    octaspire_container_pair_t *self,
    void const *second)
{
    if (self->second != memcpy(self->second, second, self->secondSize))
    {
        abort();
    }
}

bool octaspire_container_pair_set_first_to_void_pointer(
    octaspire_container_pair_t *self,
    void *element)
{
    if (self->firstSize != sizeof(element))
    {
        return false;
    }

    octaspire_container_pair_set_first(self, &element);

    return true;
}

bool octaspire_container_pair_set_second_to_void_pointer(
    octaspire_container_pair_t *self,
    void *element)
{
    if (self->secondSize != sizeof(element))
    {
        return false;
    }

    octaspire_container_pair_set_second(self, &element);

    return true;
}

void octaspire_container_pair_clear(
    octaspire_container_pair_t * const self)
{
    if (self->first != memset(self->first,  0, self->firstSize))
    {
        abort();
    }

    if (self->second != memset(self->second, 0, self->secondSize))
    {
        abort();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../src/octaspire_container_pair.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../src/octaspire_container_hash_map.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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



struct octaspire_container_hash_map_element_t
{
    size_t                        keySizeInOctets;
    void                         *key;
    size_t                        valueSizeInOctets;
    octaspire_container_vector_t *values;
    octaspire_memory_allocator_t *allocator;
    uint32_t                      hash;
    bool                          keyIsPointer;
    bool                          valueIsPointer;
    char                          padding[2];
};

octaspire_container_hash_map_element_t *octaspire_container_hash_map_element_new(
    uint32_t const hash,
    size_t const keySizeInOctets,
    bool const keyIsPointer,
    void const * const key,
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    void const * const value,
    octaspire_memory_allocator_t * const allocator)
{
    octaspire_container_hash_map_element_t *self = octaspire_memory_allocator_malloc(
        allocator,
        sizeof(octaspire_container_hash_map_element_t));

    if (!self)
    {
        return self;
    }

    self->allocator = allocator;
    self->hash = hash;
    self->keySizeInOctets = keySizeInOctets;
    self->keyIsPointer    = keyIsPointer;
    self->key = octaspire_memory_allocator_malloc(self->allocator, self->keySizeInOctets);

    if (!self->key)
    {
        octaspire_container_hash_map_element_release(self);
        self = 0;
        return 0;
    }

    if (self->key != memcpy(self->key, key, self->keySizeInOctets))
    {
        abort();
    }

    self->valueSizeInOctets = valueSizeInOctets;
    self->valueIsPointer    = valueIsPointer;
    //self->value = octaspire_memory_allocator_malloc(self->allocator, self->valueSizeInOctets);

    self->values = octaspire_container_vector_new(
        valueSizeInOctets,
        valueIsPointer,
        0,
        allocator);

    if (!self->values)
    {
        octaspire_container_hash_map_element_release(self);
        self = 0;
        return 0;
    }

    if (!octaspire_container_vector_push_back_element(self->values, value))
    {
        abort();
    }

    return self;
}

void octaspire_container_hash_map_element_release(octaspire_container_hash_map_element_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_memory_allocator_free(self->allocator, self->key);
    self->key = 0;

    //octaspire_memory_allocator_free(self->allocator, self->value);
    //self->value= 0;

    octaspire_container_vector_release(self->values);
    self->values = 0;

    octaspire_memory_allocator_free(self->allocator, self);
}

uint32_t octaspire_container_hash_map_element_get_hash(
    octaspire_container_hash_map_element_t const * const self)
{
    assert(self);
    return self->hash;
}

void *octaspire_container_hash_map_element_get_key(
    octaspire_container_hash_map_element_t const * const self)
{
    assert(self);
    return self->keyIsPointer ? (*(void**)self->key) : self->key;
}

octaspire_container_vector_t *octaspire_container_hash_map_element_get_values(
    octaspire_container_hash_map_element_t * const self)
{
    return self->values;
}

void *octaspire_container_hash_map_element_get_value(
    octaspire_container_hash_map_element_t const * const self)
{
    assert(self);
    assert(octaspire_container_vector_get_length(self->values) < 2);
    return octaspire_container_vector_get_element_at(self->values, 0);
    //return self->valueIsPointer ? (*(void**)self->value) : self->value;
}



struct octaspire_container_hash_map_t
{
    size_t                                                   keySizeInOctets;
    size_t                                                   valueSizeInOctets;
    octaspire_memory_allocator_t                            *allocator;
    octaspire_container_vector_t                            *buckets;
    octaspire_container_hash_map_key_compare_function_t      keyCompareFunction;
    octaspire_container_hash_map_key_hash_function_t         keyHashFunction;
    octaspire_container_hash_map_element_callback_function_t keyReleaseCallback;
    octaspire_container_hash_map_element_callback_function_t valueReleaseCallback;
    size_t                                                   numBucketsInUse;
    size_t                                                   numElements;
    bool                                                     keyIsPointer;
    bool                                                     valueIsPointer;
    char                                                     padding[6];
};

static size_t const OCTASPIRE_CONTAINER_HASH_MAP_SMALLEST_SIZE   = 128;
static float  const OCTASPIRE_CONTAINER_HASH_MAP_MAX_LOAD_FACTOR = 0.75f;

// Prototypes for static functions
static octaspire_container_vector_t *octaspire_container_hash_map_private_build_new_buckets(
    octaspire_container_hash_map_t *self,
    size_t const numBuckets,
    octaspire_memory_allocator_t *allocator);

static float octaspire_container_hash_map_private_get_load_factor(
    octaspire_container_hash_map_t const * const self);

static bool octaspire_container_hash_map_private_rehash(
    octaspire_container_hash_map_t * const self);

static void octaspire_container_hash_map_private_release_given_buckets(
    octaspire_container_hash_map_t *self,
    octaspire_container_vector_t **bucketsPtr);


static bool octaspire_container_hash_map_private_rehash(
    octaspire_container_hash_map_t * const self)
{
    assert(self);

    size_t const oldBucketCount = octaspire_container_vector_get_length(self->buckets);
    size_t const newBucketCount = oldBucketCount * 2;

    assert(oldBucketCount && newBucketCount);

    octaspire_container_vector_t *newBuckets =
        octaspire_container_hash_map_private_build_new_buckets(self, newBucketCount, self->allocator);

    self->numBucketsInUse = 0;
    self->numElements     = 0;

    if (!newBuckets)
    {
        return false;
    }

    for (size_t i = 0; i < oldBucketCount; ++i)
    {
        octaspire_container_vector_t *oldBucket =
            (octaspire_container_vector_t*)octaspire_container_vector_get_element_at(
                self->buckets,
                i);

        for (size_t j = 0; j < octaspire_container_vector_get_length(oldBucket); ++j)
        {
            octaspire_container_hash_map_element_t *element =
                (octaspire_container_hash_map_element_t*)octaspire_container_vector_get_element_at(
                    oldBucket,
                    j);

            uint32_t hash = octaspire_container_hash_map_element_get_hash(element);

            size_t const bucketIndex = hash % newBucketCount;

            octaspire_container_vector_t *bucket =
                (octaspire_container_vector_t*)octaspire_container_vector_get_element_at(
                    newBuckets,
                    bucketIndex);

            assert(bucket);

            if (octaspire_container_vector_is_empty(bucket))
            {
                ++(self->numBucketsInUse);
            }

            if (!octaspire_container_vector_push_back_element(bucket, &element))
            {
                return false;
            }

            ++(self->numElements);
        }

        octaspire_container_vector_release(oldBucket);
        oldBucket = 0;
    }

    octaspire_container_vector_release(self->buckets);
    self->buckets = 0;

    self->buckets = newBuckets;

    assert(octaspire_container_hash_map_private_get_load_factor(self) <
        OCTASPIRE_CONTAINER_HASH_MAP_MAX_LOAD_FACTOR);

    return true;
}

static float octaspire_container_hash_map_private_get_load_factor(
    octaspire_container_hash_map_t const * const self)
{
    return (float)self->numBucketsInUse / octaspire_container_vector_get_length(self->buckets);
}

static void octaspire_container_hash_map_private_release_given_buckets(
    octaspire_container_hash_map_t *self,
    octaspire_container_vector_t **bucketsPtr)
{
    assert(self && bucketsPtr && *bucketsPtr);

    octaspire_container_vector_t *buckets = *bucketsPtr;

    size_t const numBuckets = octaspire_container_vector_get_length(buckets);

    for (size_t i = 0; i < numBuckets; ++i)
    {
        octaspire_container_vector_t *bucket =
            (octaspire_container_vector_t*)octaspire_container_vector_get_element_at(
                buckets,
                i);

        assert(bucket);

        for (size_t j = 0; j < octaspire_container_vector_get_length(bucket); ++j)
        {
            octaspire_container_hash_map_element_t *element = (octaspire_container_hash_map_element_t*)
                octaspire_container_vector_get_element_at(bucket, j);

            if (self->valueReleaseCallback)
            {
                for (size_t k = 0; k < octaspire_container_vector_get_length(element->values); ++k)
                {
                    //self->valueReleaseCallback(*(void**)element->value);
                    self->valueReleaseCallback(
                        octaspire_container_vector_get_element_at(element->values, k));
                }
            }

            if (self->keyReleaseCallback)
            {
                if (element->keyIsPointer)
                {
                    self->keyReleaseCallback(*(void**)element->key);
                }
                else
                {
                    self->keyReleaseCallback(element->key);
                }
            }

            octaspire_container_hash_map_element_release(element);
        }

        //octaspire_container_vector_clear(bucket);
        octaspire_container_vector_release(bucket);
        bucket = 0;

    }

    octaspire_container_vector_release(buckets);
    *bucketsPtr = 0;
}

static octaspire_container_vector_t *octaspire_container_hash_map_private_build_new_buckets(
    octaspire_container_hash_map_t *self,
    size_t const numBuckets,
    octaspire_memory_allocator_t *allocator)
{
    octaspire_container_vector_t *buckets = octaspire_container_vector_new_with_preallocated_elements(
        sizeof(octaspire_container_vector_t*),
        true,
        numBuckets,
        0, //(octaspire_container_vector_element_callback_t)octaspire_container_vector_release,
        allocator);

    if (!buckets)
    {
        return 0;
    }

    for (size_t i = 0; i < numBuckets; ++i)
    {
        octaspire_container_vector_t *bucket = octaspire_container_vector_new(
            sizeof(octaspire_container_hash_map_element_t *),
            true,
            0, // (octaspire_container_vector_element_callback_t)octaspire_container_hash_map_element_release,
            allocator);

        if (!bucket)
        {
            octaspire_container_hash_map_private_release_given_buckets(self, &buckets);
            assert(!buckets);
            return 0;
        }

        if (!octaspire_container_vector_push_back_element(buckets, &bucket))
        {
            // This should never happen, because numBuckets buckets are
            // preallocated on the vector. So assert could be
            // used here, but maybe this is still safer?
            octaspire_container_hash_map_private_release_given_buckets(self, &buckets);
            assert(!buckets);
            return 0;
        }
    }

    assert(octaspire_container_vector_get_length(buckets) == numBuckets);

    return buckets;
}

octaspire_container_hash_map_t *octaspire_container_hash_map_new(
    size_t const keySizeInOctets,
    bool const keyIsPointer,
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    octaspire_container_hash_map_key_compare_function_t keyCompareFunction,
    octaspire_container_hash_map_key_hash_function_t keyHashFunction,
    octaspire_container_hash_map_element_callback_function_t keyReleaseCallback,
    octaspire_container_hash_map_element_callback_function_t valueReleaseCallback,
    octaspire_memory_allocator_t *allocator)
{
    octaspire_container_hash_map_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_container_hash_map_t));

    if (!self)
    {
        return self;
    }

    self->keySizeInOctets      = keySizeInOctets;
    self->keyIsPointer         = keyIsPointer;
    self->valueSizeInOctets    = valueSizeInOctets;
    self->valueIsPointer       = valueIsPointer;
    self->allocator            = allocator;
    self->keyCompareFunction   = keyCompareFunction;
    self->keyHashFunction      = keyHashFunction;
    self->keyReleaseCallback   = keyReleaseCallback;
    self->valueReleaseCallback = valueReleaseCallback;
    self->numBucketsInUse      = 0;
    self->numElements          = 0;

    self->buckets = octaspire_container_hash_map_private_build_new_buckets(
        self,
        OCTASPIRE_CONTAINER_HASH_MAP_SMALLEST_SIZE,
        self->allocator);

    if (!self->buckets)
    {
        octaspire_container_hash_map_release(self);
        self = 0;
        return 0;
    }

    return self;
}

octaspire_container_hash_map_t *octaspire_container_hash_map_new_with_octaspire_container_utf8_string_keys(
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    octaspire_container_hash_map_element_callback_function_t valueReleaseCallback,
    octaspire_memory_allocator_t *allocator)
{
    return octaspire_container_hash_map_new(
        sizeof(octaspire_container_utf8_string_t*),
        true,
        valueSizeInOctets,
        valueIsPointer,
        (octaspire_container_hash_map_key_compare_function_t)octaspire_container_utf8_string_is_equal,
        (octaspire_container_hash_map_key_hash_function_t)octaspire_container_utf8_string_get_hash,
        (octaspire_container_hash_map_element_callback_function_t)octaspire_container_utf8_string_release,
        valueReleaseCallback,
        allocator);
}

void octaspire_container_hash_map_release(octaspire_container_hash_map_t *self)
{
    if (!self)
    {
        return;
    }

    if (self->buckets)
    {
        octaspire_container_hash_map_private_release_given_buckets(self, &(self->buckets));
        assert(!(self->buckets));
    }

    self->buckets = 0;

    octaspire_memory_allocator_free(self->allocator, self);
}

bool octaspire_container_hash_map_remove(
    octaspire_container_hash_map_t *self,
    uint32_t const hash,
    void const * const key)
{
    size_t const bucketIndex = hash % octaspire_container_vector_get_length(self->buckets);

    octaspire_container_vector_t *bucket =
        (octaspire_container_vector_t*)octaspire_container_vector_get_element_at(
            self->buckets,
            bucketIndex);

    if (!bucket)
    {
        return false;
    }

    size_t const numElementsInBucket = octaspire_container_vector_get_length(bucket);

    for (size_t i = 0; i < numElementsInBucket; ++i)
    {
        octaspire_container_hash_map_element_t *element =
            (octaspire_container_hash_map_element_t*)octaspire_container_vector_get_element_at(
                bucket,
                i);

        assert(element);

        void const * key2 = octaspire_container_hash_map_element_get_key(element);

        if (self->keyCompareFunction(element->keyIsPointer ? *(void const * const *)key : key, key2))
        {
            if (self->valueReleaseCallback)
            {
                for (size_t j = 0; j < octaspire_container_vector_get_length(element->values); ++j)
                {
                    //self->valueReleaseCallback(*(void**)element->value);
                    self->valueReleaseCallback(
                        octaspire_container_vector_get_element_at(element->values, j));
                }
            }

            if (self->keyReleaseCallback)
            {
                if (element->keyIsPointer)
                {
                    self->keyReleaseCallback(*(void**)element->key);
                }
                else
                {
                    self->keyReleaseCallback(element->key);
                }
            }

            octaspire_container_hash_map_element_release(element);
            if (octaspire_container_vector_remove_element_at(bucket, i))
            {
                --(self->numElements);
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}

bool octaspire_container_hash_map_clear(
    octaspire_container_hash_map_t * const self)
{
    // TODO XXX how to this in best way?

    octaspire_container_vector_t *buckets = octaspire_container_hash_map_private_build_new_buckets(
        self,
        OCTASPIRE_CONTAINER_HASH_MAP_SMALLEST_SIZE,
        self->allocator);

    if (!buckets)
    {
        return false;
    }

    if (self->buckets)
    {
        octaspire_container_hash_map_private_release_given_buckets(self, &(self->buckets));
        assert(!(self->buckets));
    }

    self->buckets = buckets;

    self->numBucketsInUse = 0;
    self->numElements     = 0;

    return true;
}

bool octaspire_container_hash_map_add_hash_map(
    octaspire_container_hash_map_t * const self,
    octaspire_container_hash_map_t * const other)
{
    bool result = true;

    for (size_t i = 0; i < octaspire_container_hash_map_get_number_of_elements(other); ++i)
    {
        octaspire_container_hash_map_element_t *otherElement =
            octaspire_container_hash_map_get_at_index(other, i);

        for (size_t j = 0; j < octaspire_container_vector_get_length(otherElement->values); ++j)
        {
            void * const key   = otherElement->key;
            void * const value = octaspire_container_vector_get_element_at(otherElement->values, j);

            if (!octaspire_container_hash_map_put(
                self,
                otherElement->hash,
                key,
                &value))
            {
                result = false;
            }
        }
    }

    return result;
}

bool octaspire_container_hash_map_put(
    octaspire_container_hash_map_t *self,
    uint32_t const hash,
    void const * const key,
    void const * const value)
{
    assert(self);
    assert(octaspire_container_vector_get_length(self->buckets));

    octaspire_container_hash_map_element_t *element =
        octaspire_container_hash_map_get(self, hash, key);

    if (element)
    {
        return octaspire_container_vector_push_back_element(element->values, value);
    }
    else
    {
        //octaspire_container_hash_map_remove(self, hash, key);

        size_t const bucketIndex = hash % octaspire_container_vector_get_length(self->buckets);

        octaspire_container_vector_t *bucket =
            (octaspire_container_vector_t*)octaspire_container_vector_get_element_at(
                self->buckets,
                bucketIndex);

        assert(bucket);

        if (octaspire_container_vector_is_empty(bucket))
        {
            ++(self->numBucketsInUse);
        }

        element = octaspire_container_hash_map_element_new(
            hash,
            self->keySizeInOctets,
            self->keyIsPointer,
            key,
            self->valueSizeInOctets,
            self->valueIsPointer,
            value,
            self->allocator);

        if (!octaspire_container_vector_push_back_element(bucket, &element))
        {
            return false;
        }

        ++(self->numElements);

        if (octaspire_container_hash_map_private_get_load_factor(self) >=
                OCTASPIRE_CONTAINER_HASH_MAP_MAX_LOAD_FACTOR)
        {
            if (!octaspire_container_hash_map_private_rehash(self))
            {
                return false;
            }
        }

        return true;
    }
}

octaspire_container_hash_map_element_t const * octaspire_container_hash_map_get_const(
    octaspire_container_hash_map_t const * const self,
    uint32_t const hash,
    void const * const key)
{
    size_t const bucketIndex = hash % octaspire_container_vector_get_length(self->buckets);

    octaspire_container_vector_t *bucket =
        (octaspire_container_vector_t*)octaspire_container_vector_get_element_at(
            self->buckets,
            bucketIndex);

    assert(bucket);

    size_t const numElementsInBucket = octaspire_container_vector_get_length(bucket);

    if (numElementsInBucket == 1)
    {
        octaspire_container_hash_map_element_t *element = (octaspire_container_hash_map_element_t*)
            octaspire_container_vector_peek_front_element(bucket);

        assert(element);

        void const * const key2 = octaspire_container_hash_map_element_get_key(element);

        if (self->keyCompareFunction(element->keyIsPointer ? *(void const * const *)key : key, key2))
        {
            return element;
        }

        return 0;
    }

    for (size_t i = 0; i < numElementsInBucket; ++i)
    {
        octaspire_container_hash_map_element_t *element =
            (octaspire_container_hash_map_element_t*)octaspire_container_vector_get_element_at(
                bucket,
                i);

        assert(element);

        void const * const key2 = octaspire_container_hash_map_element_get_key(element);

        if (self->keyCompareFunction(element->keyIsPointer ? *(void const * const *)key : key, key2))
        {
            return element;
        }
    }

    return 0;
}

octaspire_container_hash_map_element_t *octaspire_container_hash_map_get(
    octaspire_container_hash_map_t *self, uint32_t const hash, void const * const key)
{
    size_t const bucketIndex = hash % octaspire_container_vector_get_length(self->buckets);

    octaspire_container_vector_t *bucket =
        (octaspire_container_vector_t*)octaspire_container_vector_get_element_at(
            self->buckets,
            bucketIndex);

    assert(bucket);

    size_t const numElementsInBucket = octaspire_container_vector_get_length(bucket);

    if (numElementsInBucket == 1)
    {
        octaspire_container_hash_map_element_t *element = (octaspire_container_hash_map_element_t*)
            octaspire_container_vector_peek_front_element(bucket);

        assert(element);

        void const * key2 = octaspire_container_hash_map_element_get_key(element);

        if (self->keyCompareFunction(element->keyIsPointer ? *(void const * const *)key : key, key2))
        {
            return element;
        }

        return 0;
    }

    for (size_t i = 0; i < numElementsInBucket; ++i)
    {
        octaspire_container_hash_map_element_t *element =
            (octaspire_container_hash_map_element_t*)octaspire_container_vector_get_element_at(
                bucket,
                i);

        assert(element);

        void const * key2 = octaspire_container_hash_map_element_get_key(element);

        if (self->keyCompareFunction(element->keyIsPointer ? *(void const * const *)key : key, key2))
        {
            return element;
        }
    }

    return 0;
}

size_t octaspire_container_hash_map_get_number_of_elements(octaspire_container_hash_map_t const * const self)
{
    assert(self);
    return self->numElements;
}

octaspire_container_hash_map_element_t *octaspire_container_hash_map_get_at_index(
    octaspire_container_hash_map_t * const self,
    size_t const index)
{
    size_t counter = 0;
    for (size_t i = 0; i < octaspire_container_vector_get_length(self->buckets); ++i)
    {
        octaspire_container_vector_t * const bucket = (octaspire_container_vector_t*)
            octaspire_container_vector_get_element_at(
                self->buckets,
                i);

        size_t const bucketSize = octaspire_container_vector_get_length(bucket);

        if (bucketSize)
        {
            if (index <= (counter + bucketSize - 1))
            {
                return (octaspire_container_hash_map_element_t*)
                    octaspire_container_vector_get_element_at(bucket, index - counter);
            }

            counter += bucketSize;
        }
     }

    return 0;
}

octaspire_container_hash_map_element_iterator_t
octaspire_container_hash_map_element_iterator_init(
    octaspire_container_hash_map_t * const self)
{
    octaspire_container_hash_map_element_iterator_t iterator;

    iterator.hashMap = self;
    iterator.bucketIndex = 0;
    iterator.elementInsideBucketIndex = 0;
    iterator.element = 0;

    if (iterator.bucketIndex < octaspire_container_vector_get_length(self->buckets))
    {
        octaspire_container_vector_t * const bucket = (octaspire_container_vector_t*)
            octaspire_container_vector_get_element_at(
                self->buckets,
                iterator.bucketIndex);

        size_t const bucketSize = octaspire_container_vector_get_length(bucket);

        if (iterator.elementInsideBucketIndex < bucketSize)
        {
            iterator.element = (octaspire_container_hash_map_element_t*)
                    octaspire_container_vector_get_element_at(
                        bucket,
                        iterator.elementInsideBucketIndex);
        }
    }

    return iterator;
}

bool octaspire_container_hash_map_element_iterator_next(
    octaspire_container_hash_map_element_iterator_t * const self)
{
    self->element = 0;

    if (self->bucketIndex < octaspire_container_vector_get_length(self->hashMap->buckets))
    {
        octaspire_container_vector_t *bucket = (octaspire_container_vector_t*)
            octaspire_container_vector_get_element_at(
                self->hashMap->buckets,
                self->bucketIndex);

        size_t bucketSize = octaspire_container_vector_get_length(bucket);

        ++(self->elementInsideBucketIndex);

        if (self->elementInsideBucketIndex < bucketSize)
        {
            self->element = (octaspire_container_hash_map_element_t*)
                    octaspire_container_vector_get_element_at(
                        bucket,
                        self->elementInsideBucketIndex);
        }
        else
        {
            ++(self->bucketIndex);

            if (self->bucketIndex < octaspire_container_vector_get_length(self->hashMap->buckets))
            {
                bucket = (octaspire_container_vector_t*)
                    octaspire_container_vector_get_element_at(
                        self->hashMap->buckets,
                        self->bucketIndex);

                bucketSize = octaspire_container_vector_get_length(bucket);

                self->elementInsideBucketIndex = 0;

                if (self->elementInsideBucketIndex < bucketSize)
                {
                    self->element = (octaspire_container_hash_map_element_t*)
                        octaspire_container_vector_get_element_at(
                            bucket,
                            self->elementInsideBucketIndex);
                }
                else
                {
                    self->element = 0;
                }
            }
        }
    }

    return self->element != 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../src/octaspire_container_hash_map.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../src/octaspire_input.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

struct octaspire_input_t
{
    octaspire_container_utf8_string_t *text;
    size_t                             index;
    size_t                             line;
    size_t                             column;
    octaspire_memory_allocator_t      *allocator;
};

bool octaspire_input_private_is_ucs_character_index_valid(
    octaspire_input_t const * const self,
    size_t index);

octaspire_input_t *octaspire_input_new_from_c_string(
    char const * const str,
    octaspire_memory_allocator_t *allocator)
{
    return octaspire_input_new_from_buffer(str, str ? strlen(str) : 0, allocator);
}

octaspire_input_t *octaspire_input_new_from_buffer(
    char const * const buffer,
    size_t const lengthInOctets,
    octaspire_memory_allocator_t *allocator)
{
    octaspire_input_t *self =
        octaspire_memory_allocator_malloc(allocator, sizeof(octaspire_input_t));

    if (!self)
    {
        return self;
    }

    self->allocator = allocator;

    self->index  = 0;
    self->line   = 1;
    self->column = 1;

    self->text   = octaspire_container_utf8_string_new_from_buffer(buffer, lengthInOctets, self->allocator);

    if (!self->text)
    {
        octaspire_input_release(self);
        self = 0;
        return 0;
    }

    return self;
}

octaspire_input_t *octaspire_input_new_from_path(
    char const * const path,
    octaspire_memory_allocator_t *octaspireAllocator,
    octaspire_stdio_t *octaspireStdio)
{
    size_t octetsAllocated = 0;
    char *buffer = octaspire_helpers_path_to_buffer(path, &octetsAllocated, octaspireAllocator, octaspireStdio);

    if (!buffer)
    {
        return 0;
    }

    octaspire_input_t *self = octaspire_input_new_from_buffer(buffer, octetsAllocated, octaspireAllocator);

    octaspire_memory_allocator_free(octaspireAllocator, buffer);
    buffer = 0;

    return self;
}

void octaspire_input_release(octaspire_input_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_container_utf8_string_release(self->text);
    octaspire_memory_allocator_free(self->allocator, self);
}

size_t octaspire_input_get_length_in_ucs_characters(octaspire_input_t const * const self)
{
    return octaspire_container_utf8_string_get_length_in_ucs_characters(self->text);
}

void   octaspire_input_clear(octaspire_input_t *self)
{
    octaspire_container_utf8_string_clear(self->text);
    self->index  = 0;
    self->line   = 1;
    self->column = 1;
}

void   octaspire_input_rewind(octaspire_input_t *self)
{
    self->index  = 0;
    self->line   = 1;
    self->column = 1;
}

uint32_t octaspire_input_peek_next_ucs_character(octaspire_input_t *self)
{
    if (self->index >= octaspire_container_utf8_string_get_length_in_ucs_characters(self->text))
    {
        return 0;
    }

    return octaspire_container_utf8_string_get_ucs_character_at_index(self->text, self->index);
}

uint32_t octaspire_input_peek_next_next_ucs_character(octaspire_input_t *self)
{
    if ((self->index + 1) >= octaspire_container_utf8_string_get_length_in_ucs_characters(self->text))
    {
        return 0;
    }

    return octaspire_container_utf8_string_get_ucs_character_at_index(self->text, self->index + 1);
}

bool octaspire_input_pop_next_ucs_character(octaspire_input_t *self)
{
    if (!octaspire_input_private_is_ucs_character_index_valid(self, self->index))
    {
        return false;
    }

    uint32_t const result =
        octaspire_container_utf8_string_get_ucs_character_at_index(self->text, self->index);

    ++(self->index);

    if (octaspire_input_private_is_ucs_character_index_valid(self, self->index))
    {
        if (result == '\n')
        {
            self->column = 1;
            ++(self->line);
        }
        else
        {
            ++(self->column);
        }
    }

    return true;
}

bool octaspire_input_is_good(octaspire_input_t const * const self)
{
    return self->index < octaspire_container_utf8_string_get_length_in_ucs_characters(self->text);
}

bool octaspire_input_private_is_ucs_character_index_valid(
    octaspire_input_t const * const self,
    size_t index)
{
    return index < octaspire_container_utf8_string_get_length_in_ucs_characters(self->text);
}

bool octaspire_input_push_back_from_string(
    octaspire_input_t * const self,
    octaspire_container_utf8_string_t const * const str)
{
    return octaspire_input_push_back_from_c_string(
        self,
        octaspire_container_utf8_string_get_c_string(str));
}

bool octaspire_input_push_back_from_c_string(octaspire_input_t * const self, char const * const str)
{
    assert(self);
    return octaspire_container_utf8_string_concatenate_c_string(self->text, str);
}

size_t octaspire_input_get_line_number(octaspire_input_t const * const self)
{
    return self->line;
}

size_t octaspire_input_get_column_number(octaspire_input_t const * const self)
{
    return self->column;
}

size_t octaspire_input_get_ucs_character_index(octaspire_input_t const * const self)
{
    return self->index;
}

void octaspire_input_print(octaspire_input_t const * const self)
{
    printf("\n-------------------------- octaspire input --------------------------\n");
    printf("%s", octaspire_container_utf8_string_get_c_string(self->text));
    printf("---------------------------------------------------------------------\n");
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../src/octaspire_input.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../src/octaspire_stdio.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

struct octaspire_stdio_t
{
    octaspire_memory_allocator_t *allocator;
    size_t   numberOfFutureReadsToBeRigged;
    size_t   bitIndex;
    uint32_t bitQueue;
    char     padding[4];
};

octaspire_stdio_t *octaspire_stdio_new(octaspire_memory_allocator_t *allocator)
{
    size_t const size = sizeof(octaspire_stdio_t);

    octaspire_stdio_t *self = octaspire_memory_allocator_malloc(allocator, size);

    if (!self)
    {
        return self;
    }

    memset(self, 0, size);

    self->allocator = allocator;

    return self;
}

void octaspire_stdio_release(octaspire_stdio_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_memory_allocator_free(self->allocator, self);
}

size_t octaspire_stdio_fread(
    octaspire_stdio_t *self,
    void *ptr,
    size_t const size,
    size_t const nmemb,
    FILE *stream)
{
    if (self->numberOfFutureReadsToBeRigged)
    {
        --(self->numberOfFutureReadsToBeRigged);

        if (!octaspire_helpers_test_bit(self->bitQueue, self->bitIndex))
        {
            ++(self->bitIndex);
            return 0;
        }

        ++(self->bitIndex);
    }

    return fread(ptr, size, nmemb, stream);
}

void octaspire_stdio_set_number_and_type_of_future_reads_to_be_rigged(
    octaspire_stdio_t *self,
    size_t const count,
    uint32_t const bitQueue)
{
    self->numberOfFutureReadsToBeRigged = count;
    self->bitIndex = 0;
    self->bitQueue = bitQueue;
}

size_t octaspire_stdio_get_number_of_future_reads_to_be_rigged(
    octaspire_stdio_t const * const self)
{
    return self->numberOfFutureReadsToBeRigged;
}

octaspire_container_utf8_string_t *octaspire_stdio_read_line(octaspire_stdio_t *self, FILE *stream)
{
    octaspire_container_vector_t *vec = octaspire_container_vector_new(
        sizeof(char),
        false,
        0,
        self->allocator);

    while (true)
    {
        int c = fgetc(stream);
        char const ch = (char)c;

        if (c == EOF)
        {
            octaspire_container_vector_release(vec);
            return 0;
        }
        else if (c == '\n')
        {
            octaspire_container_vector_push_back_element(vec, &ch);
            break;
        }

        octaspire_container_vector_push_back_element(vec, &ch);
    }

    octaspire_container_utf8_string_t* result = octaspire_container_utf8_string_new_from_buffer(
        octaspire_container_vector_get_element_at_const(vec, 0),
        octaspire_container_vector_get_length_in_octets(vec),
        self->allocator);

    octaspire_container_vector_release(vec);
    vec = 0;
    return result;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../src/octaspire_stdio.c
//////////////////////////////////////////////////////////////////////////////////////////////////



#endif // OCTASPIRE_CORE_AMALGAMATED_IMPLEMENTATION








#ifdef OCTASPIRE_CORE_AMALGAMATED_UNIT_TEST_IMPLEMENTATION

//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../external/greatest.h
//////////////////////////////////////////////////////////////////////////////////////////////////
// This file is modified by www.octaspire.com. The original copyright is:

/*
 * Copyright (c) 2011-2016 Scott Vokes <vokes.s@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

// Modifications are released under similar license:

/*
 * Copyright (c) 2017 www.octaspire.com
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef GREATEST_H
#define GREATEST_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef GREATEST_ENABLE_ANSI_COLORS
#define GREATEST_ANSI_COLOR_RED    "\x1B[31m"
#define GREATEST_ANSI_COLOR_GREEN  "\x1B[32m"
#define GREATEST_ANSI_COLOR_YELLOW "\x1B[33m"
#define GREATEST_ANSI_COLOR_DGRAY  "\x1B[1;30m"
#define GREATEST_ANSI_COLOR_RESET  "\x1B[0m"
#else
#define GREATEST_ANSI_COLOR_RED    ""
#define GREATEST_ANSI_COLOR_GREEN  ""
#define GREATEST_ANSI_COLOR_YELLOW ""
#define GREATEST_ANSI_COLOR_DGRAY  ""
#define GREATEST_ANSI_COLOR_RESET  ""
#endif

/* 1.2.2 */
#define GREATEST_VERSION_MAJOR 1
#define GREATEST_VERSION_MINOR 2
#define GREATEST_VERSION_PATCH 2

/* A unit testing system for C, contained in 1 file.
 * It doesn't use dynamic allocation or depend on anything
 * beyond ANSI C89.
 *
 * An up-to-date version can be found at:
 *     https://github.com/silentbicycle/greatest/
 */


/*********************************************************************
 * Minimal test runner template
 *********************************************************************/
#if 0

#include "greatest.h"

TEST foo_should_foo(void) {
    PASS();
}

static void setup_cb(void *data) {
    printf("setup callback for each test case\n");
}

static void teardown_cb(void *data) {
    printf("teardown callback for each test case\n");
}

SUITE(suite) {
    /* Optional setup/teardown callbacks which will be run before/after
     * every test case. If using a test suite, they will be cleared when
     * the suite finishes. */
    SET_SETUP(setup_cb, voidp_to_callback_data);
    SET_TEARDOWN(teardown_cb, voidp_to_callback_data);

    RUN_TEST(foo_should_foo);
}

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

/* Set up, run suite(s) of tests, report pass/fail/skip stats. */
int run_tests(void) {
    GREATEST_INIT();            /* init. greatest internals */
    /* List of suites to run (if any). */
    RUN_SUITE(suite);

    /* Tests can also be run directly, without using test suites. */
    RUN_TEST(foo_should_foo);

    GREATEST_PRINT_REPORT();          /* display results */
    return greatest_all_passed();
}

/* main(), for a standalone command-line test runner.
 * This replaces run_tests above, and adds command line option
 * handling and exiting with a pass/fail status. */
int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* init & parse command-line args */
    RUN_SUITE(suite);
    GREATEST_MAIN_END();        /* display results */
}

#endif
/*********************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/***********
 * Options *
 ***********/

/* Default column width for non-verbose output. */
#ifndef GREATEST_DEFAULT_WIDTH
#define GREATEST_DEFAULT_WIDTH 72
#endif

/* FILE *, for test logging. */
#ifndef GREATEST_STDOUT
#define GREATEST_STDOUT stdout
#endif

/* Remove GREATEST_ prefix from most commonly used symbols? */
#ifndef GREATEST_USE_ABBREVS
#define GREATEST_USE_ABBREVS 1
#endif

/* Set to 0 to disable all use of setjmp/longjmp. */
#ifndef GREATEST_USE_LONGJMP
#define GREATEST_USE_LONGJMP 1
#endif

#if GREATEST_USE_LONGJMP
#include <setjmp.h>
#endif

/* Set to 0 to disable all use of time.h / clock(). */
#ifndef GREATEST_USE_TIME
#define GREATEST_USE_TIME 1
#endif

#if GREATEST_USE_TIME
#include <time.h>
#endif

/* Floating point type, for ASSERT_IN_RANGE. */
#ifndef GREATEST_FLOAT
#define GREATEST_FLOAT double
#define GREATEST_FLOAT_FMT "%g"
#endif

/*********
 * Types *
 *********/

/* Info for the current running suite. */
typedef struct greatest_suite_info {
    unsigned int tests_run;
    unsigned int passed;
    unsigned int failed;
    unsigned int skipped;

#if GREATEST_USE_TIME
    /* timers, pre/post running suite and individual tests */
    clock_t pre_suite;
    clock_t post_suite;
    clock_t pre_test;
    clock_t post_test;
#endif
} greatest_suite_info;

/* Type for a suite function. */
typedef void (greatest_suite_cb)(void);

/* Types for setup/teardown callbacks. If non-NULL, these will be run
 * and passed the pointer to their additional data. */
typedef void (greatest_setup_cb)(void *udata);
typedef void (greatest_teardown_cb)(void *udata);

/* Type for an equality comparison between two pointers of the same type.
 * Should return non-0 if equal, otherwise 0.
 * UDATA is a closure value, passed through from ASSERT_EQUAL_T[m]. */
typedef int greatest_equal_cb(const void *exp, const void *got, void *udata);

/* Type for a callback that prints a value pointed to by T.
 * Return value has the same meaning as printf's.
 * UDATA is a closure value, passed through from ASSERT_EQUAL_T[m]. */
typedef int greatest_printf_cb(const void *t, void *udata);

/* Callbacks for an arbitrary type; needed for type-specific
 * comparisons via GREATEST_ASSERT_EQUAL_T[m].*/
typedef struct greatest_type_info {
    greatest_equal_cb *equal;
    greatest_printf_cb *print;
} greatest_type_info;

typedef struct greatest_memory_cmp_env {
    const unsigned char *exp;
    const unsigned char *got;
    size_t size;
} greatest_memory_cmp_env;

/* Callbacks for string and raw memory types. */
extern greatest_type_info greatest_type_info_string;
extern greatest_type_info greatest_type_info_memory;

typedef enum {
    GREATEST_FLAG_FIRST_FAIL = 0x01,
    GREATEST_FLAG_LIST_ONLY = 0x02
} greatest_flag_t;

/* Struct containing all test runner state. */
typedef struct greatest_run_info {
    unsigned char flags;
    unsigned char verbosity;
    unsigned char pad_0[2];

    unsigned int tests_run;     /* total test count */

    /* currently running test suite */
    greatest_suite_info suite;

    /* overall pass/fail/skip counts */
    unsigned int passed;
    unsigned int failed;
    unsigned int skipped;
    unsigned int assertions;

    /* info to print about the most recent failure */
    unsigned int fail_line;
    unsigned int pad_1;
    const char *fail_file;
    const char *msg;

    /* current setup/teardown hooks and userdata */
    greatest_setup_cb *setup;
    void *setup_udata;
    greatest_teardown_cb *teardown;
    void *teardown_udata;

    /* formatting info for ".....s...F"-style output */
    unsigned int col;
    unsigned int width;

    /* only run a specific suite or test */
    const char *suite_filter;
    const char *test_filter;

#if GREATEST_USE_TIME
    /* overall timers */
    clock_t begin;
    clock_t end;
#endif

#if GREATEST_USE_LONGJMP
    int pad_jmp_buf;
    char octaspire_padding[4];
    jmp_buf jump_dest;
#endif
} greatest_run_info;

struct greatest_report_t {
    /* overall pass/fail/skip counts */
    unsigned int passed;
    unsigned int failed;
    unsigned int skipped;
    unsigned int assertions;
};

/* Global var for the current testing context.
 * Initialized by GREATEST_MAIN_DEFS(). */
extern greatest_run_info greatest_info;

/* Type for ASSERT_ENUM_EQ's ENUM_STR argument. */
typedef const char *greatest_enum_str_fun(int value);

/**********************
 * Exported functions *
 **********************/

/* These are used internally by greatest. */
void greatest_do_pass(const char *name);
void greatest_do_fail(const char *name);
void greatest_do_skip(const char *name);
int greatest_pre_test(const char *name);
void greatest_post_test(const char *name, int res);
void greatest_usage(const char *name);
int greatest_do_assert_equal_t(const void *exp, const void *got,
    greatest_type_info *type_info, void *udata);

/* These are part of the public greatest API. */
void GREATEST_SET_SETUP_CB(greatest_setup_cb *cb, void *udata);
void GREATEST_SET_TEARDOWN_CB(greatest_teardown_cb *cb, void *udata);
int greatest_all_passed(void);
void greatest_set_test_filter(const char *name);
void greatest_set_suite_filter(const char *name);
void greatest_get_report(struct greatest_report_t *report);
unsigned int greatest_get_verbosity(void);
void greatest_set_verbosity(unsigned int verbosity);
void greatest_set_flag(greatest_flag_t flag);


/********************
* Language Support *
********************/

/* If __VA_ARGS__ (C99) is supported, allow parametric testing
* without needing to manually manage the argument struct. */
#if __STDC_VERSION__ >= 19901L || _MSC_VER >= 1800
#define GREATEST_VA_ARGS
#endif


/**********
 * Macros *
 **********/

/* Define a suite. */
#define GREATEST_SUITE(NAME) void NAME(void); void NAME(void)

/* Declare a suite, provided by another compilation unit. */
#define GREATEST_SUITE_EXTERN(NAME) void NAME(void)

/* Start defining a test function.
 * The arguments are not included, to allow parametric testing. */
#define GREATEST_TEST static enum greatest_test_res

/* PASS/FAIL/SKIP result from a test. Used internally. */
typedef enum greatest_test_res {
    GREATEST_TEST_RES_PASS = 0,
    GREATEST_TEST_RES_FAIL = -1,
    GREATEST_TEST_RES_SKIP = 1
} greatest_test_res;

/* Run a suite. */
#define GREATEST_RUN_SUITE(S_NAME) greatest_run_suite(S_NAME, #S_NAME)

/* Run a test in the current suite. */
#define GREATEST_RUN_TEST(TEST)                                         \
    do {                                                                \
        if (greatest_pre_test(#TEST) == 1) {                            \
            enum greatest_test_res res = GREATEST_SAVE_CONTEXT();       \
            if (res == GREATEST_TEST_RES_PASS) {                        \
                res = TEST();                                           \
            }                                                           \
            greatest_post_test(#TEST, res);                             \
        } else if (GREATEST_LIST_ONLY()) {                              \
            fprintf(GREATEST_STDOUT, "  %s\n", #TEST);                  \
        }                                                               \
    } while (0)

/* Ignore a test, don't warn about it being unused. */
#define GREATEST_IGNORE_TEST(TEST) (void)TEST

/* Run a test in the current suite with one void * argument,
 * which can be a pointer to a struct with multiple arguments. */
#define GREATEST_RUN_TEST1(TEST, ENV)                                   \
    do {                                                                \
        if (greatest_pre_test(#TEST) == 1) {                            \
            int res = TEST(ENV);                                        \
            greatest_post_test(#TEST, res);                             \
        } else if (GREATEST_LIST_ONLY()) {                              \
            fprintf(GREATEST_STDOUT, "  %s\n", #TEST);                  \
        }                                                               \
    } while (0)

#ifdef GREATEST_VA_ARGS
#define GREATEST_RUN_TESTp(TEST, ...)                                   \
    do {                                                                \
        if (greatest_pre_test(#TEST) == 1) {                            \
            int res = TEST(__VA_ARGS__);                                \
            greatest_post_test(#TEST, res);                             \
        } else if (GREATEST_LIST_ONLY()) {                              \
            fprintf(GREATEST_STDOUT, "  %s\n", #TEST);                  \
        }                                                               \
    } while (0)
#endif


/* Check if the test runner is in verbose mode. */
#define GREATEST_IS_VERBOSE() ((greatest_info.verbosity) > 0)
#define GREATEST_LIST_ONLY()                                            \
    (greatest_info.flags & GREATEST_FLAG_LIST_ONLY)
#define GREATEST_FIRST_FAIL()                                           \
    (greatest_info.flags & GREATEST_FLAG_FIRST_FAIL)
#define GREATEST_FAILURE_ABORT()                                        \
    (greatest_info.suite.failed > 0 && GREATEST_FIRST_FAIL())

/* Message-less forms of tests defined below. */
#define GREATEST_PASS() GREATEST_PASSm(NULL)
#define GREATEST_FAIL() GREATEST_FAILm(NULL)
#define GREATEST_SKIP() GREATEST_SKIPm(NULL)
#define GREATEST_ASSERT(COND)                                           \
    GREATEST_ASSERTm(#COND, COND)
#define GREATEST_ASSERT_OR_LONGJMP(COND)                                \
    GREATEST_ASSERT_OR_LONGJMPm(#COND, COND)
#define GREATEST_ASSERT_FALSE(COND)                                     \
    GREATEST_ASSERT_FALSEm(#COND, COND)
#define GREATEST_ASSERT_EQ(EXP, GOT)                                    \
    GREATEST_ASSERT_EQm(#EXP " != " #GOT, EXP, GOT)
#define GREATEST_ASSERT_EQ_FMT(EXP, GOT, FMT)                           \
    GREATEST_ASSERT_EQ_FMTm(#EXP " != " #GOT, EXP, GOT, FMT)
#define GREATEST_ASSERT_IN_RANGE(EXP, GOT, TOL)                         \
    GREATEST_ASSERT_IN_RANGEm(#EXP " != " #GOT " +/- " #TOL, EXP, GOT, TOL)
#define GREATEST_ASSERT_EQUAL_T(EXP, GOT, TYPE_INFO, UDATA)             \
    GREATEST_ASSERT_EQUAL_Tm(#EXP " != " #GOT, EXP, GOT, TYPE_INFO, UDATA)
#define GREATEST_ASSERT_STR_EQ(EXP, GOT)                                \
    GREATEST_ASSERT_STR_EQm(#EXP " != " #GOT, EXP, GOT)
#define GREATEST_ASSERT_STRN_EQ(EXP, GOT, SIZE)                         \
    GREATEST_ASSERT_STRN_EQm(#EXP " != " #GOT, EXP, GOT, SIZE)
#define GREATEST_ASSERT_MEM_EQ(EXP, GOT, SIZE)                          \
    GREATEST_ASSERT_MEM_EQm(#EXP " != " #GOT, EXP, GOT, SIZE)
#define GREATEST_ASSERT_ENUM_EQ(EXP, GOT, ENUM_STR)                     \
    GREATEST_ASSERT_ENUM_EQm(#EXP " != " #GOT, EXP, GOT, ENUM_STR)

/* The following forms take an additional message argument first,
 * to be displayed by the test runner. */

/* Fail if a condition is not true, with message. */
#define GREATEST_ASSERTm(MSG, COND)                                     \
    do {                                                                \
        greatest_info.assertions++;                                     \
        if (!(COND)) { GREATEST_FAILm(MSG); }                           \
    } while (0)

/* Fail if a condition is not true, longjmping out of test. */
#define GREATEST_ASSERT_OR_LONGJMPm(MSG, COND)                          \
    do {                                                                \
        greatest_info.assertions++;                                     \
        if (!(COND)) { GREATEST_FAIL_WITH_LONGJMPm(MSG); }              \
    } while (0)

/* Fail if a condition is not false, with message. */
#define GREATEST_ASSERT_FALSEm(MSG, COND)                               \
    do {                                                                \
        greatest_info.assertions++;                                     \
        if ((COND)) { GREATEST_FAILm(MSG); }                            \
    } while (0)

/* Fail if EXP != GOT (equality comparison by ==). */
#define GREATEST_ASSERT_EQm(MSG, EXP, GOT)                              \
    do {                                                                \
        greatest_info.assertions++;                                     \
        if ((EXP) != (GOT)) { GREATEST_FAILm(MSG); }                    \
    } while (0)

/* Fail if EXP != GOT (equality comparison by ==).
 * Warning: FMT, EXP, and GOT will be evaluated more
 * than once on failure. */
#define GREATEST_ASSERT_EQ_FMTm(MSG, EXP, GOT, FMT)                     \
    do {                                                                \
        greatest_info.assertions++;                                     \
        if ((EXP) != (GOT)) {                                           \
            fprintf(GREATEST_STDOUT, "\nExpected: ");                   \
            fprintf(GREATEST_STDOUT, FMT, EXP);                         \
            fprintf(GREATEST_STDOUT, "\n     Got: ");                   \
            fprintf(GREATEST_STDOUT, FMT, GOT);                         \
            fprintf(GREATEST_STDOUT, "\n");                             \
            GREATEST_FAILm(MSG);                                        \
        }                                                               \
    } while (0)

/* Fail if EXP is not equal to GOT, printing enum IDs. */
#define GREATEST_ASSERT_ENUM_EQm(MSG, EXP, GOT, ENUM_STR)               \
    do {                                                                \
        int greatest_EXP = (int)(EXP);                                  \
        int greatest_GOT = (int)(GOT);                                  \
        greatest_enum_str_fun *greatest_ENUM_STR = ENUM_STR;            \
        if (greatest_EXP != greatest_GOT) {                             \
            fprintf(GREATEST_STDOUT, "\nExpected: %s",                  \
                greatest_ENUM_STR(greatest_EXP));                       \
            fprintf(GREATEST_STDOUT, "\n     Got: %s\n",                \
                greatest_ENUM_STR(greatest_GOT));                       \
            GREATEST_FAILm(MSG);                                        \
        }                                                               \
    } while (0)                                                         \

/* Fail if GOT not in range of EXP +|- TOL. */
#define GREATEST_ASSERT_IN_RANGEm(MSG, EXP, GOT, TOL)                   \
    do {                                                                \
        GREATEST_FLOAT greatest_EXP = (EXP);                            \
        GREATEST_FLOAT greatest_GOT = (GOT);                            \
        GREATEST_FLOAT greatest_TOL = (TOL);                            \
        greatest_info.assertions++;                                     \
        if ((greatest_EXP > greatest_GOT &&                             \
                greatest_EXP - greatest_GOT > greatest_TOL) ||          \
            (greatest_EXP < greatest_GOT &&                             \
                greatest_GOT - greatest_EXP > greatest_TOL)) {          \
            fprintf(GREATEST_STDOUT,                                    \
                "\nExpected: " GREATEST_FLOAT_FMT                       \
                " +/- " GREATEST_FLOAT_FMT                              \
                "\n     Got: " GREATEST_FLOAT_FMT                       \
                "\n",                                                   \
                greatest_EXP, greatest_TOL, greatest_GOT);              \
            GREATEST_FAILm(MSG);                                        \
        }                                                               \
    } while (0)

/* Fail if EXP is not equal to GOT, according to strcmp. */
#define GREATEST_ASSERT_STR_EQm(MSG, EXP, GOT)                          \
    do {                                                                \
        GREATEST_ASSERT_EQUAL_Tm(MSG, EXP, GOT,                         \
            &greatest_type_info_string, NULL);                          \
    } while (0)                                                         \

/* Fail if EXP is not equal to GOT, according to strcmp. */
#define GREATEST_ASSERT_STRN_EQm(MSG, EXP, GOT, SIZE)                   \
    do {                                                                \
        size_t size = SIZE;                                             \
        GREATEST_ASSERT_EQUAL_Tm(MSG, EXP, GOT,                         \
            &greatest_type_info_string, &size);                         \
    } while (0)                                                         \

/* Fail if EXP is not equal to GOT, according to memcmp. */
#define GREATEST_ASSERT_MEM_EQm(MSG, EXP, GOT, SIZE)                    \
    do {                                                                \
        greatest_memory_cmp_env env;                                    \
        env.exp = (const unsigned char *)EXP;                           \
        env.got = (const unsigned char *)GOT;                           \
        env.size = SIZE;                                                \
        GREATEST_ASSERT_EQUAL_Tm(MSG, env.exp, env.got,                 \
            &greatest_type_info_memory, &env);                          \
    } while (0)                                                         \

/* Fail if EXP is not equal to GOT, according to a comparison
 * callback in TYPE_INFO. If they are not equal, optionally use a
 * print callback in TYPE_INFO to print them. */
#define GREATEST_ASSERT_EQUAL_Tm(MSG, EXP, GOT, TYPE_INFO, UDATA)       \
    do {                                                                \
        greatest_type_info *type_info = (TYPE_INFO);                    \
        greatest_info.assertions++;                                     \
        if (!greatest_do_assert_equal_t(EXP, GOT,                       \
                type_info, UDATA)) {                                    \
            if (type_info == NULL || type_info->equal == NULL) {        \
                GREATEST_FAILm("type_info->equal callback missing!");   \
            } else {                                                    \
                GREATEST_FAILm(MSG);                                    \
            }                                                           \
        }                                                               \
    } while (0)                                                         \

/* Pass. */
#define GREATEST_PASSm(MSG)                                             \
    do {                                                                \
        greatest_info.msg = MSG;                                        \
        return GREATEST_TEST_RES_PASS;                                  \
    } while (0)

/* Fail. */
#define GREATEST_FAILm(MSG)                                             \
    do {                                                                \
        greatest_info.fail_file = __FILE__;                             \
        greatest_info.fail_line = __LINE__;                             \
        greatest_info.msg = MSG;                                        \
        return GREATEST_TEST_RES_FAIL;                                  \
    } while (0)

/* Optional GREATEST_FAILm variant that longjmps. */
#if GREATEST_USE_LONGJMP
#define GREATEST_FAIL_WITH_LONGJMP() GREATEST_FAIL_WITH_LONGJMPm(NULL)
#define GREATEST_FAIL_WITH_LONGJMPm(MSG)                                \
    do {                                                                \
        greatest_info.fail_file = __FILE__;                             \
        greatest_info.fail_line = __LINE__;                             \
        greatest_info.msg = MSG;                                        \
        longjmp(greatest_info.jump_dest, GREATEST_TEST_RES_FAIL);       \
    } while (0)
#endif

/* Skip the current test. */
#define GREATEST_SKIPm(MSG)                                             \
    do {                                                                \
        greatest_info.msg = MSG;                                        \
        return GREATEST_TEST_RES_SKIP;                                  \
    } while (0)

/* Check the result of a subfunction using ASSERT, etc. */
#define GREATEST_CHECK_CALL(RES)                                        \
    do {                                                                \
        enum greatest_test_res greatest_RES = RES;                      \
        if (greatest_RES != GREATEST_TEST_RES_PASS) {                   \
            return greatest_RES;                                        \
        }                                                               \
    } while (0)                                                         \

#if GREATEST_USE_TIME
#define GREATEST_SET_TIME(NAME)                                         \
    NAME = clock();                                                     \
    if (NAME == (clock_t) -1) {                                         \
        fprintf(GREATEST_STDOUT,                                        \
            "clock error: %s\n", #NAME);                                \
        exit(EXIT_FAILURE);                                             \
    }

#define GREATEST_CLOCK_DIFF(C1, C2)                                     \
    fprintf(GREATEST_STDOUT, GREATEST_ANSI_COLOR_DGRAY " (%lu ticks, %.3f sec)" GREATEST_ANSI_COLOR_RESET, \
        (long unsigned int) (C2) - (long unsigned int)(C1),             \
        (double)((C2) - (C1)) / (1.0 * (double)CLOCKS_PER_SEC))
#else
#define GREATEST_SET_TIME(UNUSED)
#define GREATEST_CLOCK_DIFF(UNUSED1, UNUSED2)
#endif

#if GREATEST_USE_LONGJMP
#define GREATEST_SAVE_CONTEXT()                                         \
        /* setjmp returns 0 (GREATEST_TEST_RES_PASS) on first call */   \
        /* so the test runs, then RES_FAIL from FAIL_WITH_LONGJMP. */   \
        ((enum greatest_test_res)(setjmp(greatest_info.jump_dest)))
#else
#define GREATEST_SAVE_CONTEXT()                                         \
    /*a no-op, since setjmp/longjmp aren't being used */                \
    GREATEST_TEST_RES_PASS
#endif

/* Include several function definitions in the main test file. */
#define GREATEST_MAIN_DEFS()                                            \
                                                                        \
/* Is FILTER a subset of NAME? */                                       \
static int greatest_name_match(const char *name,                        \
    const char *filter) {                                               \
    size_t offset = 0;                                                  \
    size_t filter_len = strlen(filter);                                 \
    while (name[offset] != '\0') {                                      \
        if (name[offset] == filter[0]) {                                \
            if (0 == strncmp(&name[offset], filter, filter_len)) {      \
                return 1;                                               \
            }                                                           \
        }                                                               \
        offset++;                                                       \
    }                                                                   \
                                                                        \
    return 0;                                                           \
}                                                                       \
                                                                        \
int greatest_pre_test(const char *name) {                               \
    if (!GREATEST_LIST_ONLY()                                           \
        && (!GREATEST_FIRST_FAIL() || greatest_info.suite.failed == 0)  \
        && (greatest_info.test_filter == NULL ||                        \
            greatest_name_match(name, greatest_info.test_filter))) {    \
        GREATEST_SET_TIME(greatest_info.suite.pre_test);                \
        if (greatest_info.setup) {                                      \
            greatest_info.setup(greatest_info.setup_udata);             \
        }                                                               \
        return 1;               /* test should be run */                \
    } else {                                                            \
        return 0;               /* skipped */                           \
    }                                                                   \
}                                                                       \
                                                                        \
void greatest_post_test(const char *name, int res) {                    \
    GREATEST_SET_TIME(greatest_info.suite.post_test);                   \
    if (greatest_info.teardown) {                                       \
        void *udata = greatest_info.teardown_udata;                     \
        greatest_info.teardown(udata);                                  \
    }                                                                   \
                                                                        \
    if (res <= GREATEST_TEST_RES_FAIL) {                                \
        greatest_do_fail(name);                                         \
    } else if (res >= GREATEST_TEST_RES_SKIP) {                         \
        greatest_do_skip(name);                                         \
    } else if (res == GREATEST_TEST_RES_PASS) {                         \
        greatest_do_pass(name);                                         \
    }                                                                   \
    greatest_info.suite.tests_run++;                                    \
    greatest_info.col++;                                                \
    if (GREATEST_IS_VERBOSE()) {                                        \
        GREATEST_CLOCK_DIFF(greatest_info.suite.pre_test,               \
            greatest_info.suite.post_test);                             \
        fprintf(GREATEST_STDOUT, "\n");                                 \
    } else if (greatest_info.col % greatest_info.width == 0) {          \
        fprintf(GREATEST_STDOUT, "\n");                                 \
        greatest_info.col = 0;                                          \
    }                                                                   \
    fflush(GREATEST_STDOUT);                                            \
}                                                                       \
                                                                        \
static void report_suite(void) {                                        \
    if (greatest_info.suite.tests_run > 0) {                            \
        fprintf(GREATEST_STDOUT,                                        \
            "\n%u test%s - %u passed, %u failed, %u skipped",           \
            greatest_info.suite.tests_run,                              \
            greatest_info.suite.tests_run == 1 ? "" : "s",              \
            greatest_info.suite.passed,                                 \
            greatest_info.suite.failed,                                 \
            greatest_info.suite.skipped);                               \
        GREATEST_CLOCK_DIFF(greatest_info.suite.pre_suite,              \
            greatest_info.suite.post_suite);                            \
        fprintf(GREATEST_STDOUT, "\n");                                 \
    }                                                                   \
}                                                                       \
                                                                        \
static void update_counts_and_reset_suite(void) {                       \
    greatest_info.setup = NULL;                                         \
    greatest_info.setup_udata = NULL;                                   \
    greatest_info.teardown = NULL;                                      \
    greatest_info.teardown_udata = NULL;                                \
    greatest_info.passed += greatest_info.suite.passed;                 \
    greatest_info.failed += greatest_info.suite.failed;                 \
    greatest_info.skipped += greatest_info.suite.skipped;               \
    greatest_info.tests_run += greatest_info.suite.tests_run;           \
    memset(&greatest_info.suite, 0, sizeof(greatest_info.suite));       \
    greatest_info.col = 0;                                              \
}                                                                       \
                                                                        \
static void greatest_run_suite(greatest_suite_cb *suite_cb,             \
                               const char *suite_name) {                \
    if (greatest_info.suite_filter &&                                   \
        !greatest_name_match(suite_name, greatest_info.suite_filter)) { \
        return;                                                         \
    }                                                                   \
    update_counts_and_reset_suite();                                    \
    if (GREATEST_FIRST_FAIL() && greatest_info.failed > 0) { return; }  \
    fprintf(GREATEST_STDOUT, "\n" GREATEST_ANSI_COLOR_YELLOW "* Suite %s:" GREATEST_ANSI_COLOR_RESET "\n", suite_name);  \
    GREATEST_SET_TIME(greatest_info.suite.pre_suite);                   \
    suite_cb();                                                         \
    GREATEST_SET_TIME(greatest_info.suite.post_suite);                  \
    report_suite();                                                     \
}                                                                       \
                                                                        \
void greatest_do_pass(const char *name) {                               \
    if (GREATEST_IS_VERBOSE()) {                                        \
        fprintf(GREATEST_STDOUT, "PASS %s: %s",                         \
            name, greatest_info.msg ? greatest_info.msg : "");          \
    } else {                                                            \
        fprintf(GREATEST_STDOUT, GREATEST_ANSI_COLOR_GREEN "." GREATEST_ANSI_COLOR_RESET);  \
    }                                                                   \
    greatest_info.suite.passed++;                                       \
}                                                                       \
                                                                        \
void greatest_do_fail(const char *name) {                               \
    if (GREATEST_IS_VERBOSE()) {                                        \
        fprintf(GREATEST_STDOUT,                                        \
            "FAIL %s: %s (%s:%u)",                                      \
            name, greatest_info.msg ? greatest_info.msg : "",           \
            greatest_info.fail_file, greatest_info.fail_line);          \
    } else {                                                            \
        fprintf(GREATEST_STDOUT, GREATEST_ANSI_COLOR_RED "F" GREATEST_ANSI_COLOR_RESET);    \
        greatest_info.col++;                                            \
        /* add linebreak if in line of '.'s */                          \
        if (greatest_info.col != 0) {                                   \
            fprintf(GREATEST_STDOUT, "\n");                             \
            greatest_info.col = 0;                                      \
        }                                                               \
        fprintf(GREATEST_STDOUT, GREATEST_ANSI_COLOR_RED "FAIL" GREATEST_ANSI_COLOR_RESET " %s: %s (%s:%u)\n",  \
            name,                                                       \
            greatest_info.msg ? greatest_info.msg : "",                 \
            greatest_info.fail_file, greatest_info.fail_line);          \
    }                                                                   \
    greatest_info.suite.failed++;                                       \
}                                                                       \
                                                                        \
void greatest_do_skip(const char *name) {                               \
    if (GREATEST_IS_VERBOSE()) {                                        \
        fprintf(GREATEST_STDOUT, "SKIP %s: %s",                         \
            name,                                                       \
            greatest_info.msg ?                                         \
            greatest_info.msg : "" );                                   \
    } else {                                                            \
        fprintf(GREATEST_STDOUT, "s");                                  \
    }                                                                   \
    greatest_info.suite.skipped++;                                      \
}                                                                       \
                                                                        \
int greatest_do_assert_equal_t(const void *exp, const void *got,        \
        greatest_type_info *type_info, void *udata) {                   \
    int eq = 0;                                                         \
    if (type_info == NULL || type_info->equal == NULL) {                \
        return 0;                                                       \
    }                                                                   \
    eq = type_info->equal(exp, got, udata);                             \
    if (!eq) {                                                          \
        if (type_info->print != NULL) {                                 \
            fprintf(GREATEST_STDOUT, "\nExpected: ");                   \
            (void)type_info->print(exp, udata);                         \
            fprintf(GREATEST_STDOUT, "\n     Got: ");                   \
            (void)type_info->print(got, udata);                         \
            fprintf(GREATEST_STDOUT, "\n");                             \
        } else {                                                        \
            fprintf(GREATEST_STDOUT,                                    \
                "GREATEST_ASSERT_EQUAL_T failure at %s:%u\n",           \
                greatest_info.fail_file,                                \
                greatest_info.fail_line);                               \
        }                                                               \
    }                                                                   \
    return eq;                                                          \
}                                                                       \
                                                                        \
void greatest_usage(const char *name) {                                 \
    fprintf(GREATEST_STDOUT,                                            \
        "Usage: %s [-hlfv] [-s SUITE] [-t TEST]\n"                      \
        "  -h, --help  print this Help\n"                               \
        "  -l          List suites and their tests, then exit\n"        \
        "  -f          Stop runner after first failure\n"               \
        "  -v          Verbose output\n"                                \
        "  -s SUITE    only run suites containing string SUITE\n"       \
        "  -t TEST     only run tests containing string TEST\n",        \
        name);                                                          \
}                                                                       \
                                                                        \
static void greatest_parse_args(int argc, char **argv) {                \
    int i = 0;                                                          \
    for (i = 1; i < argc; i++) {                                        \
        if (0 == strncmp("-t", argv[i], 2)) {                           \
            if (argc <= i + 1) {                                        \
                greatest_usage(argv[0]);                                \
                exit(EXIT_FAILURE);                                     \
            }                                                           \
            greatest_info.test_filter = argv[i+1];                      \
            i++;                                                        \
        } else if (0 == strncmp("-s", argv[i], 2)) {                    \
            if (argc <= i + 1) {                                        \
                greatest_usage(argv[0]);                                \
                exit(EXIT_FAILURE);                                     \
            }                                                           \
            greatest_info.suite_filter = argv[i+1];                     \
            i++;                                                        \
        } else if (0 == strncmp("-f", argv[i], 2)) {                    \
            greatest_info.flags |= GREATEST_FLAG_FIRST_FAIL;            \
        } else if (0 == strncmp("-v", argv[i], 2)) {                    \
            greatest_info.verbosity++;                                  \
        } else if (0 == strncmp("-l", argv[i], 2)) {                    \
            greatest_info.flags |= GREATEST_FLAG_LIST_ONLY;             \
        } else if (0 == strncmp("-h", argv[i], 2) ||                    \
                   0 == strncmp("--help", argv[i], 6)) {                \
            greatest_usage(argv[0]);                                    \
            exit(EXIT_SUCCESS);                                         \
        } else if (0 == strncmp("--", argv[i], 2)) {                    \
            break;                                                      \
        } else {                                                        \
            fprintf(GREATEST_STDOUT,                                    \
                "Unknown argument '%s'\n", argv[i]);                    \
            greatest_usage(argv[0]);                                    \
            exit(EXIT_FAILURE);                                         \
        }                                                               \
    }                                                                   \
}                                                                       \
                                                                        \
int greatest_all_passed(void) { return (greatest_info.failed == 0); }   \
                                                                        \
void greatest_set_test_filter(const char *name) {                       \
    greatest_info.test_filter = name;                                   \
}                                                                       \
                                                                        \
void greatest_set_suite_filter(const char *name) {                      \
    greatest_info.suite_filter = name;                                  \
}                                                                       \
                                                                        \
void greatest_get_report(struct greatest_report_t *report) {            \
    if (report) {                                                       \
        report->passed = greatest_info.passed;                          \
        report->failed = greatest_info.failed;                          \
        report->skipped = greatest_info.skipped;                        \
        report->assertions = greatest_info.assertions;                  \
    }                                                                   \
}                                                                       \
                                                                        \
unsigned int greatest_get_verbosity(void) {                             \
    return greatest_info.verbosity;                                     \
}                                                                       \
                                                                        \
void greatest_set_verbosity(unsigned int verbosity) {                   \
    greatest_info.verbosity = (unsigned char)verbosity;                 \
}                                                                       \
                                                                        \
void greatest_set_flag(greatest_flag_t flag) {                          \
    greatest_info.flags |= flag;                                        \
}                                                                       \
                                                                        \
void GREATEST_SET_SETUP_CB(greatest_setup_cb *cb, void *udata) {        \
    greatest_info.setup = cb;                                           \
    greatest_info.setup_udata = udata;                                  \
}                                                                       \
                                                                        \
void GREATEST_SET_TEARDOWN_CB(greatest_teardown_cb *cb,                 \
                                    void *udata) {                      \
    greatest_info.teardown = cb;                                        \
    greatest_info.teardown_udata = udata;                               \
}                                                                       \
                                                                        \
static int greatest_string_equal_cb(const void *exp, const void *got,   \
    void *udata) {                                                      \
    size_t *size = (size_t *)udata;                                     \
    return (size != NULL                                                \
        ? (0 == strncmp((const char *)exp, (const char *)got, *size))   \
        : (0 == strcmp((const char *)exp, (const char *)got)));         \
}                                                                       \
                                                                        \
static int greatest_string_printf_cb(const void *t, void *udata) {      \
    (void)udata; /* note: does not check \0 termination. */             \
    return fprintf(GREATEST_STDOUT, "%s", (const char *)t);             \
}                                                                       \
                                                                        \
greatest_type_info greatest_type_info_string = {                        \
    greatest_string_equal_cb,                                           \
    greatest_string_printf_cb,                                          \
};                                                                      \
                                                                        \
static int greatest_memory_equal_cb(const void *exp, const void *got,   \
    void *udata) {                                                      \
    greatest_memory_cmp_env *env = (greatest_memory_cmp_env *)udata;    \
    return (0 == memcmp(exp, got, env->size));                          \
}                                                                       \
                                                                        \
static int greatest_memory_printf_cb(const void *t, void *udata) {      \
    greatest_memory_cmp_env *env = (greatest_memory_cmp_env *)udata;    \
    const unsigned char *buf = (const unsigned char *)t;                \
    unsigned char diff_mark = ' ';                                      \
    FILE *out = GREATEST_STDOUT;                                        \
    size_t i, line_i, line_len = 0;                                     \
    int len = 0;   /* format hexdump with differences highlighted */    \
    for (i = 0; i < env->size; i+= line_len) {                          \
        diff_mark = ' ';                                                \
        line_len = env->size - i;                                       \
        if (line_len > 16) { line_len = 16; }                           \
        for (line_i = i; line_i < i + line_len; line_i++) {             \
            if (env->exp[line_i] != env->got[line_i]) diff_mark = 'X';  \
        }                                                               \
        len += fprintf(out, "\n%04x %c ", (unsigned int)i, diff_mark);  \
        for (line_i = i; line_i < i + line_len; line_i++) {             \
            int m = env->exp[line_i] == env->got[line_i]; /* match? */  \
            len += fprintf(out, "%02x%c", buf[line_i], m ? ' ' : '<');  \
        }                                                               \
        for (line_i = 0; line_i < 16 - line_len; line_i++) {            \
            len += fprintf(out, "   ");                                 \
        }                                                               \
        fprintf(out, " ");                                              \
        for (line_i = i; line_i < i + line_len; line_i++) {             \
            unsigned char c = buf[line_i];                              \
            len += fprintf(out, "%c", isprint(c) ? c : '.');            \
        }                                                               \
    }                                                                   \
    len += fprintf(out, "\n");                                          \
    return len;                                                         \
}                                                                       \
                                                                        \
greatest_type_info greatest_type_info_memory = {                        \
    greatest_memory_equal_cb,                                           \
    greatest_memory_printf_cb,                                          \
};                                                                      \
                                                                        \
greatest_run_info greatest_info

/* Init internals. */
#define GREATEST_INIT()                                                 \
    do {                                                                \
        /* Suppress unused function warning if features aren't used */  \
        (void)greatest_run_suite;                                       \
        (void)greatest_parse_args;                                      \
                                                                        \
        memset(&greatest_info, 0, sizeof(greatest_info));               \
        greatest_info.width = GREATEST_DEFAULT_WIDTH;                   \
        GREATEST_SET_TIME(greatest_info.begin);                         \
    } while (0)                                                         \

/* Handle command-line arguments, etc. */
#define GREATEST_MAIN_BEGIN()                                           \
    do {                                                                \
        GREATEST_INIT();                                                \
        greatest_parse_args(argc, argv);                                \
    } while (0)

/* Report passes, failures, skipped tests, the number of
 * assertions, and the overall run time. */
#define GREATEST_PRINT_REPORT()                                         \
    do {                                                                \
        if (!GREATEST_LIST_ONLY()) {                                    \
            update_counts_and_reset_suite();                            \
            GREATEST_SET_TIME(greatest_info.end);                       \
            fprintf(GREATEST_STDOUT,                                    \
                "\nTotal: %u test%s",                                   \
                greatest_info.tests_run,                                \
                greatest_info.tests_run == 1 ? "" : "s");               \
            GREATEST_CLOCK_DIFF(greatest_info.begin,                    \
                greatest_info.end);                                     \
            fprintf(GREATEST_STDOUT, ", %u assertion%s\n",              \
                greatest_info.assertions,                               \
                greatest_info.assertions == 1 ? "" : "s");              \
            fprintf(GREATEST_STDOUT,                                    \
                GREATEST_ANSI_COLOR_GREEN "Pass: %u, fail: %u, skip: %u.\n" GREATEST_ANSI_COLOR_RESET,  \
                greatest_info.passed,                                   \
                greatest_info.failed, greatest_info.skipped);           \
        }                                                               \
    } while (0)

/* Report results, exit with exit status based on results. */
#define GREATEST_MAIN_END()                                             \
    do {                                                                \
        GREATEST_PRINT_REPORT();                                        \
        return (greatest_all_passed() ? EXIT_SUCCESS : EXIT_FAILURE);   \
    } while (0)

/* Make abbreviations without the GREATEST_ prefix for the
 * most commonly used symbols. */
#if GREATEST_USE_ABBREVS
#define TEST           GREATEST_TEST
#define SUITE          GREATEST_SUITE
#define SUITE_EXTERN   GREATEST_SUITE_EXTERN
#define RUN_TEST       GREATEST_RUN_TEST
#define RUN_TEST1      GREATEST_RUN_TEST1
#define RUN_SUITE      GREATEST_RUN_SUITE
#define IGNORE_TEST    GREATEST_IGNORE_TEST
#define ASSERT         GREATEST_ASSERT
#define ASSERTm        GREATEST_ASSERTm
#define ASSERT_FALSE   GREATEST_ASSERT_FALSE
#define ASSERT_EQ      GREATEST_ASSERT_EQ
#define ASSERT_EQ_FMT  GREATEST_ASSERT_EQ_FMT
#define ASSERT_IN_RANGE GREATEST_ASSERT_IN_RANGE
#define ASSERT_EQUAL_T GREATEST_ASSERT_EQUAL_T
#define ASSERT_STR_EQ  GREATEST_ASSERT_STR_EQ
#define ASSERT_STRN_EQ GREATEST_ASSERT_STRN_EQ
#define ASSERT_MEM_EQ  GREATEST_ASSERT_MEM_EQ
#define ASSERT_ENUM_EQ GREATEST_ASSERT_ENUM_EQ
#define ASSERT_FALSEm  GREATEST_ASSERT_FALSEm
#define ASSERT_EQm     GREATEST_ASSERT_EQm
#define ASSERT_EQ_FMTm GREATEST_ASSERT_EQ_FMTm
#define ASSERT_IN_RANGEm GREATEST_ASSERT_IN_RANGEm
#define ASSERT_EQUAL_Tm GREATEST_ASSERT_EQUAL_Tm
#define ASSERT_STR_EQm GREATEST_ASSERT_STR_EQm
#define ASSERT_STRN_EQm GREATEST_ASSERT_STRN_EQm
#define ASSERT_MEM_EQm GREATEST_ASSERT_MEM_EQm
#define ASSERT_ENUM_EQm GREATEST_ASSERT_ENUM_EQm
#define PASS           GREATEST_PASS
#define FAIL           GREATEST_FAIL
#define SKIP           GREATEST_SKIP
#define PASSm          GREATEST_PASSm
#define FAILm          GREATEST_FAILm
#define SKIPm          GREATEST_SKIPm
#define SET_SETUP      GREATEST_SET_SETUP_CB
#define SET_TEARDOWN   GREATEST_SET_TEARDOWN_CB
#define CHECK_CALL     GREATEST_CHECK_CALL

#ifdef GREATEST_VA_ARGS
#define RUN_TESTp      GREATEST_RUN_TESTp
#endif

#if GREATEST_USE_LONGJMP
#define ASSERT_OR_LONGJMP  GREATEST_ASSERT_OR_LONGJMP
#define ASSERT_OR_LONGJMPm GREATEST_ASSERT_OR_LONGJMPm
#define FAIL_WITH_LONGJMP  GREATEST_FAIL_WITH_LONGJMP
#define FAIL_WITH_LONGJMPm GREATEST_FAIL_WITH_LONGJMPm
#endif

#endif /* USE_ABBREVS */

#ifdef __cplusplus
}
#endif

#endif
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../external/greatest.h
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../test/test_helpers.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

static octaspire_memory_allocator_t *octaspireHelpersTestAllocator = 0;
static octaspire_stdio_t            *octaspireHelpersTestStdio = 0;

TEST octaspire_helpers_test_bit_when_only_highest_order_bit_is_set_test(void)
{
    uint32_t const bitSet = 0x80000000;

    for (size_t i = 0; i < 31; ++i)
    {
        ASSERT_FALSE(octaspire_helpers_test_bit(bitSet, i));
    }

    ASSERT(octaspire_helpers_test_bit(bitSet, 31));

    PASS();
}

TEST octaspire_helpers_test_bit_when_only_lowest_order_bit_is_set_test(void)
{
    uint32_t const bitSet = 0x00000001;

    ASSERT(octaspire_helpers_test_bit(bitSet, 0));

    for (size_t i = 1; i < 32; ++i)
    {
        ASSERT_FALSE(octaspire_helpers_test_bit(bitSet, i));
    }

    PASS();
}

TEST octaspire_helpers_test_bit_when_all_bits_are_set_test(void)
{
    uint32_t const bitSet = 0xFFFFFFFF;

    for (size_t i = 0; i < 32; ++i)
    {
        ASSERT(octaspire_helpers_test_bit(bitSet, i));
    }

    PASS();
}

TEST octaspire_helpers_test_bit_when_no_bits_are_set_test(void)
{
    uint32_t const bitSet = 0x00000000;

    for (size_t i = 0; i < 32; ++i)
    {
        ASSERT_FALSE(octaspire_helpers_test_bit(bitSet, i));
    }

    PASS();
}

TEST octaspire_helpers_test_bit_when_every_bit_at_even_index_is_set_test(void)
{
    uint32_t const bitSet = 0x55555555;

    for (size_t i = 0; i < 32; ++i)
    {
        if (i % 2 == 0)
        {
            ASSERT(octaspire_helpers_test_bit(bitSet, i));
        }
        else
        {
            ASSERT_FALSE(octaspire_helpers_test_bit(bitSet, i));
        }
    }

    PASS();
}

TEST octaspire_helpers_test_bit_when_every_bit_at_odd_index_is_set_test(void)
{
    uint32_t const bitSet = 0xAAAAAAAA;

    for (size_t i = 0; i < 32; ++i)
    {
        if (i % 2 != 0)
        {
            ASSERT(octaspire_helpers_test_bit(bitSet, i));
        }
        else
        {
            ASSERT_FALSE(octaspire_helpers_test_bit(bitSet, i));
        }
    }

    PASS();
}

TEST octaspire_helpers_path_to_buffer_test(void)
{
    size_t octetsAllocated = 0;

    char * buffer = octaspire_helpers_path_to_buffer(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_helpers_path_to_buffer_test",
        &octetsAllocated,
        octaspireHelpersTestAllocator,
        octaspireHelpersTestStdio);

    ASSERT(buffer);
    ASSERT_EQ(2 + 3 + 4, octetsAllocated);

    // Copyright sign 0xa9               2 octet
    // Equal sign     0x2260             3 octets
    // Linear b syllable b008 a 0x10000  4 octets
    char const * const expected = "\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    ASSERT_EQ(octetsAllocated, strlen(expected));

    ASSERT_MEM_EQ(expected, buffer, octetsAllocated);

    octaspire_memory_allocator_free(octaspireHelpersTestAllocator, buffer);
    buffer = 0;

    PASS();
}

TEST octaspire_helpers_path_to_buffer_failure_on_nonexisting_file_test(void)
{
    size_t octetsAllocated = 0;

    char * buffer = octaspire_helpers_path_to_buffer(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_helpers_path_to_buffer_failure_on_nonexisting_file_test",
        &octetsAllocated,
        octaspireHelpersTestAllocator,
        octaspireHelpersTestStdio);

    ASSERT_FALSE(buffer);
    ASSERT_EQ(0, octetsAllocated);

    octaspire_memory_allocator_free(octaspireHelpersTestAllocator, buffer);
    buffer = 0;

    PASS();
}

TEST octaspire_helpers_path_to_buffer_failure_on_empty_file_test(void)
{
    size_t octetsAllocated = 0;

    char * buffer = octaspire_helpers_path_to_buffer(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_helpers_path_to_buffer_failure_on_empty_file_test",
        &octetsAllocated,
        octaspireHelpersTestAllocator,
        octaspireHelpersTestStdio);

    ASSERT_FALSE(buffer);
    ASSERT_EQ(0, octetsAllocated);

    octaspire_memory_allocator_free(octaspireHelpersTestAllocator, buffer);
    buffer = 0;

    PASS();
}

TEST octaspire_helpers_path_to_buffer_allocation_failure_test(void)
{
    size_t octetsAllocated = 0;

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireHelpersTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireHelpersTestAllocator));

    char * buffer = octaspire_helpers_path_to_buffer(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_helpers_path_to_buffer_test",
        &octetsAllocated,
        octaspireHelpersTestAllocator,
        octaspireHelpersTestStdio);

    ASSERT_EQ(0, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireHelpersTestAllocator));

    ASSERT_FALSE(buffer);
    ASSERT_EQ(0, octetsAllocated);

    octaspire_memory_allocator_free(octaspireHelpersTestAllocator, buffer);
    buffer = 0;

    PASS();
}

TEST octaspire_helpers_path_to_buffer_read_failure_test(void)
{
    size_t octetsAllocated = 0;

    octaspire_stdio_set_number_and_type_of_future_reads_to_be_rigged(octaspireHelpersTestStdio, 1, 0);
    ASSERT_EQ(1, octaspire_stdio_get_number_of_future_reads_to_be_rigged(octaspireHelpersTestStdio));

    char * buffer = octaspire_helpers_path_to_buffer(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_helpers_path_to_buffer_test",
        &octetsAllocated,
        octaspireHelpersTestAllocator,
        octaspireHelpersTestStdio);

    ASSERT_EQ(0, octaspire_stdio_get_number_of_future_reads_to_be_rigged(octaspireHelpersTestStdio));

    ASSERT_FALSE(buffer);
    ASSERT_EQ(0, octetsAllocated);

    octaspire_memory_allocator_free(octaspireHelpersTestAllocator, buffer);
    buffer = 0;

    PASS();
}

static size_t octaspireHelpersSuiteNumTimesRun = 0;

GREATEST_SUITE(octaspire_helpers_suite)
{
    octaspireHelpersSuiteNumTimesRun = 0;

    octaspireHelpersTestAllocator       = octaspire_memory_allocator_new_create_region(
        OCTASPIRE_CORE_CONFIG_MEMORY_ALLOCATOR_REGION_MIN_BLOCK_SIZE_IN_OCTETS);

    octaspireHelpersTestStdio  = octaspire_stdio_new(octaspireHelpersTestAllocator);

second_run:

    assert(octaspireHelpersTestAllocator);
    assert(octaspireHelpersTestStdio);

    RUN_TEST(octaspire_helpers_test_bit_when_only_highest_order_bit_is_set_test);
    RUN_TEST(octaspire_helpers_test_bit_when_only_lowest_order_bit_is_set_test);
    RUN_TEST(octaspire_helpers_test_bit_when_all_bits_are_set_test);
    RUN_TEST(octaspire_helpers_test_bit_when_no_bits_are_set_test);
    RUN_TEST(octaspire_helpers_test_bit_when_every_bit_at_even_index_is_set_test);
    RUN_TEST(octaspire_helpers_test_bit_when_every_bit_at_odd_index_is_set_test);
    RUN_TEST(octaspire_helpers_path_to_buffer_test);
    RUN_TEST(octaspire_helpers_path_to_buffer_failure_on_nonexisting_file_test);
    RUN_TEST(octaspire_helpers_path_to_buffer_failure_on_empty_file_test);
    RUN_TEST(octaspire_helpers_path_to_buffer_allocation_failure_test);
    RUN_TEST(octaspire_helpers_path_to_buffer_read_failure_test);

    octaspire_stdio_release(octaspireHelpersTestStdio);
    octaspireHelpersTestStdio = 0;

    octaspire_memory_allocator_release(octaspireHelpersTestAllocator);
    octaspireHelpersTestAllocator = 0;

    ++octaspireHelpersSuiteNumTimesRun;

    if (octaspireHelpersSuiteNumTimesRun < 2)
    {
        // Second run without region allocator

        octaspireHelpersTestAllocator      = octaspire_memory_allocator_new(0);
        octaspireHelpersTestStdio = octaspire_stdio_new(octaspireHelpersTestAllocator);

        goto second_run;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../test/test_helpers.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../test/test_utf8.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

static octaspire_memory_allocator_t *octaspireUtf8TestAllocator = 0;

TEST octaspire_utf8_private_rangeof_test(void)
{
    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_FIRST, octaspire_utf8_private_rangeof(0));
    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_FIRST, octaspire_utf8_private_rangeof(1));
    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_FIRST, octaspire_utf8_private_rangeof(126));
    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_FIRST, octaspire_utf8_private_rangeof(127));

    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_SECOND, octaspire_utf8_private_rangeof(128));
    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_SECOND, octaspire_utf8_private_rangeof(129));
    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_SECOND, octaspire_utf8_private_rangeof(1000));
    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_SECOND, octaspire_utf8_private_rangeof(2047));

    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_THIRD, octaspire_utf8_private_rangeof(2048));
    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_THIRD, octaspire_utf8_private_rangeof(2049));
    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_THIRD, octaspire_utf8_private_rangeof(32000));
    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_THIRD, octaspire_utf8_private_rangeof(65535));

    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_FOURTH, octaspire_utf8_private_rangeof(65536));
    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_FOURTH, octaspire_utf8_private_rangeof(65537));
    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_FOURTH, octaspire_utf8_private_rangeof(100000));
    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_FOURTH, octaspire_utf8_private_rangeof(1114111));

    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_ILLEGAL, octaspire_utf8_private_rangeof(1114112));
    ASSERT_EQ(OCTASPIRE_UTF8_CHARACTER_RANGE_ILLEGAL, octaspire_utf8_private_rangeof(1114113));

    PASS();
}

TEST octaspire_utf8_private_high_order_bits_test(void)
{
    ASSERT_EQ(((uint32_t)0x0),        octaspire_utf8_private_high_order_bits(OCTASPIRE_UTF8_CHARACTER_RANGE_FIRST));
    ASSERT_EQ(((uint32_t)0xC080),     octaspire_utf8_private_high_order_bits(OCTASPIRE_UTF8_CHARACTER_RANGE_SECOND));
    ASSERT_EQ(((uint32_t)0xE08080),   octaspire_utf8_private_high_order_bits(OCTASPIRE_UTF8_CHARACTER_RANGE_THIRD));
    ASSERT_EQ(((uint32_t)0xF0808080), octaspire_utf8_private_high_order_bits(OCTASPIRE_UTF8_CHARACTER_RANGE_FOURTH));
    ASSERT_EQ(((uint32_t)0xFFFFFFFF), octaspire_utf8_private_high_order_bits(OCTASPIRE_UTF8_CHARACTER_RANGE_ILLEGAL));

    PASS();
}

TEST octaspire_utf8_private_set_bit_test(void)
{
    uint32_t bitset = 0;

    for (size_t i = 0; i < 32; ++i)
    {
        octaspire_utf8_private_set_bit(&bitset, i, true);
        ASSERT_EQ(pow(2, i), bitset);
        octaspire_utf8_private_set_bit(&bitset, i, false);
        ASSERT_EQ(0, bitset);
    }

    PASS();
}

TEST octaspire_utf8_private_get_bit_test(void)
{
    uint32_t bitset = 0;

    for (size_t i = 0; i < 32; ++i)
    {
        octaspire_utf8_private_set_bit(&bitset, i, true);
        ASSERT_EQ(pow(2, i), bitset);

        for (size_t j = 0; j < 32; ++j)
        {
            ASSERT_EQ((j == i) ? true : false, octaspire_utf8_private_get_bit(bitset, j));
        }

        octaspire_utf8_private_set_bit(&bitset, i, false);
        ASSERT_EQ(0, bitset);
    }

    PASS();
}

TEST octaspire_utf8_encode_character_NUL_test(void)
{
    octaspire_utf8_character_t encoded;

    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_OK, octaspire_utf8_encode_character('\0', &encoded));

    ASSERT_EQ(1, encoded.numoctets);

    ASSERT_EQ(0, encoded.octets[0]);
    ASSERT_EQ(0, encoded.octets[1]);
    ASSERT_EQ(0, encoded.octets[2]);
    ASSERT_EQ(0, encoded.octets[3]);

    PASS();
}

TEST octaspire_utf8_encode_character_SOH_test(void)
{
    octaspire_utf8_character_t encoded;

    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_OK, octaspire_utf8_encode_character(1, &encoded));

    ASSERT_EQ(1, encoded.numoctets);

    ASSERT_EQ(0, encoded.octets[0]);
    ASSERT_EQ(0, encoded.octets[1]);
    ASSERT_EQ(0, encoded.octets[2]);
    ASSERT_EQ(1, encoded.octets[3]);

    PASS();
}

TEST octaspire_utf8_encode_character_space_test(void)
{
    octaspire_utf8_character_t encoded;

    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_OK, octaspire_utf8_encode_character(' ', &encoded));

    ASSERT_EQ(1, encoded.numoctets);

    ASSERT_EQ(0,  encoded.octets[0]);
    ASSERT_EQ(0,  encoded.octets[1]);
    ASSERT_EQ(0,  encoded.octets[2]);
    ASSERT_EQ(32, encoded.octets[3]);

    PASS();
}

TEST octaspire_utf8_encode_character_A_test(void)
{
    octaspire_utf8_character_t encoded;

    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_OK, octaspire_utf8_encode_character('A', &encoded));

    ASSERT_EQ(1, encoded.numoctets);

    ASSERT_EQ(0,  encoded.octets[0]);
    ASSERT_EQ(0,  encoded.octets[1]);
    ASSERT_EQ(0,  encoded.octets[2]);
    ASSERT_EQ(65, encoded.octets[3]);

    PASS();
}

TEST octaspire_utf8_encode_character_control_U_PLUS_0080_test(void)
{
    octaspire_utf8_character_t encoded;

    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_OK, octaspire_utf8_encode_character(0x80, &encoded));

    ASSERT_EQ(2, encoded.numoctets);

    ASSERT_EQ(0,    encoded.octets[0]);
    ASSERT_EQ(0,    encoded.octets[1]);
    ASSERT_EQ(0xc2, encoded.octets[2]);
    ASSERT_EQ(0x80, encoded.octets[3]);

    PASS();
}

TEST octaspire_utf8_encode_character_latin_small_letter_a_with_diaeresis_test(void)
{
    octaspire_utf8_character_t encoded;

    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_OK, octaspire_utf8_encode_character(0xE4, &encoded));

    ASSERT_EQ(2, encoded.numoctets);

    ASSERT_EQ(0,    encoded.octets[0]);
    ASSERT_EQ(0,    encoded.octets[1]);
    ASSERT_EQ(0xc3, encoded.octets[2]);
    ASSERT_EQ(0xa4, encoded.octets[3]);

    PASS();
}

TEST octaspire_utf8_encode_character_latin_small_letter_y_with_diaeresis_test(void)
{
    octaspire_utf8_character_t encoded;

    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_OK, octaspire_utf8_encode_character(0xFF, &encoded));

    ASSERT_EQ(2, encoded.numoctets);

    ASSERT_EQ(0,    encoded.octets[0]);
    ASSERT_EQ(0,    encoded.octets[1]);
    ASSERT_EQ(0xc3, encoded.octets[2]);
    ASSERT_EQ(0xbf, encoded.octets[3]);

    PASS();
}

TEST octaspire_utf8_encode_character_copyright_sign_test(void)
{
    octaspire_utf8_character_t encoded;

    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_OK, octaspire_utf8_encode_character(0xA9, &encoded));

    ASSERT_EQ(2, encoded.numoctets);

    ASSERT_EQ(0,    encoded.octets[0]);
    ASSERT_EQ(0,    encoded.octets[1]);
    ASSERT_EQ(0xc2, encoded.octets[2]);
    ASSERT_EQ(0xa9, encoded.octets[3]);

    PASS();
}

TEST octaspire_utf8_encode_character_not_equal_symbol_test(void)
{
    octaspire_utf8_character_t encoded;

    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_OK, octaspire_utf8_encode_character(0x2260, &encoded));

    ASSERT_EQ(3, encoded.numoctets);

    ASSERT_EQ(0x0,  encoded.octets[0]);
    ASSERT_EQ(0xe2, encoded.octets[1]);
    ASSERT_EQ(0x89, encoded.octets[2]);
    ASSERT_EQ(0xa0, encoded.octets[3]);

    PASS();
}

TEST octaspire_utf8_encode_character_linear_b_syllable_b008_a_test(void)
{
    octaspire_utf8_character_t encoded;

    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_OK, octaspire_utf8_encode_character(0x10000, &encoded));

    ASSERT_EQ(4, encoded.numoctets);

    ASSERT_EQ(0xf0, encoded.octets[0]);
    ASSERT_EQ(0x90, encoded.octets[1]);
    ASSERT_EQ(0x80, encoded.octets[2]);
    ASSERT_EQ(0x80, encoded.octets[3]);

    PASS();
}

TEST octaspire_utf8_encode_character_of_illegal_range_test(void)
{
    octaspire_utf8_character_t encoded;

    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_ILLEGAL_CHARACTER_NUMBER, octaspire_utf8_encode_character(0xFFFFFFFF, &encoded));

    ASSERT_EQ(0, encoded.numoctets);

    ASSERT_EQ(0x0, encoded.octets[0]);
    ASSERT_EQ(0x0, encoded.octets[1]);
    ASSERT_EQ(0x0, encoded.octets[2]);
    ASSERT_EQ(0x0, encoded.octets[3]);

    PASS();
}

TEST octaspire_utf8_encode_character_illegal_range_from_U_PLUS_D800_to_U_PLUS_DFFF_test(void)
{
    octaspire_utf8_character_t encoded;

    // Lower limit minus one
    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_OK, octaspire_utf8_encode_character(0xD7ff, &encoded));
    ASSERT_EQ(3,    encoded.numoctets);
    ASSERT_EQ(0,    encoded.octets[0]);
    ASSERT_EQ(0xed, encoded.octets[1]);
    ASSERT_EQ(0x9f, encoded.octets[2]);
    ASSERT_EQ(0xbf, encoded.octets[3]);

    // Lower limit
    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_ILLEGAL_CHARACTER_NUMBER, octaspire_utf8_encode_character(0xD800, &encoded));
    ASSERT_EQ(0, encoded.numoctets);
    ASSERT_EQ(0, encoded.octets[0]);
    ASSERT_EQ(0, encoded.octets[1]);
    ASSERT_EQ(0, encoded.octets[2]);
    ASSERT_EQ(0, encoded.octets[3]);

    // Lower limit plus one
    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_ILLEGAL_CHARACTER_NUMBER, octaspire_utf8_encode_character(0xD801, &encoded));
    ASSERT_EQ(0, encoded.numoctets);
    ASSERT_EQ(0, encoded.octets[0]);
    ASSERT_EQ(0, encoded.octets[1]);
    ASSERT_EQ(0, encoded.octets[2]);
    ASSERT_EQ(0, encoded.octets[3]);

    // In the middle between lower and upper limit
    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_ILLEGAL_CHARACTER_NUMBER, octaspire_utf8_encode_character(0xdbff, &encoded));
    ASSERT_EQ(0, encoded.numoctets);
    ASSERT_EQ(0, encoded.octets[0]);
    ASSERT_EQ(0, encoded.octets[1]);
    ASSERT_EQ(0, encoded.octets[2]);
    ASSERT_EQ(0, encoded.octets[3]);

    // Upper limit minus one
    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_ILLEGAL_CHARACTER_NUMBER, octaspire_utf8_encode_character(0xDFFE, &encoded));
    ASSERT_EQ(0, encoded.numoctets);
    ASSERT_EQ(0, encoded.octets[0]);
    ASSERT_EQ(0, encoded.octets[1]);
    ASSERT_EQ(0, encoded.octets[2]);
    ASSERT_EQ(0, encoded.octets[3]);

    // Upper limit
    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_ILLEGAL_CHARACTER_NUMBER, octaspire_utf8_encode_character(0xDFFF, &encoded));
    ASSERT_EQ(0, encoded.numoctets);
    ASSERT_EQ(0, encoded.octets[0]);
    ASSERT_EQ(0, encoded.octets[1]);
    ASSERT_EQ(0, encoded.octets[2]);
    ASSERT_EQ(0, encoded.octets[3]);

    // Upper limit plus one
    ASSERT_EQ(OCTASPIRE_UTF8_ENCODE_STATUS_OK, octaspire_utf8_encode_character(0xE000, &encoded));
    ASSERT_EQ(3,    encoded.numoctets);
    ASSERT_EQ(0,    encoded.octets[0]);
    ASSERT_EQ(0xee, encoded.octets[1]);
    ASSERT_EQ(0x80, encoded.octets[2]);
    ASSERT_EQ(0x80, encoded.octets[3]);

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_is_empty_string_test(void)
{
    char const *text = "";
    ASSERT_EQ(0,  strlen(text));
    ASSERT_EQ(0, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_is_null_test(void)
{
    char const *text = 0;
    ASSERT_EQ(0, octaspire_utf8_private_octets_in_next(text, 0));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_is_invalid_of_length_one_octet_0x80_test(void)
{
    char const *text = "\x80";
    ASSERT_EQ(1,  strlen(text));
    ASSERT_EQ(-1, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_is_invalid_of_length_two_octets_0xC0FF_test(void)
{
    char const *text = "\xC0\xFF";
    ASSERT_EQ(2,  strlen(text));
    ASSERT_EQ(-1, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_is_invalid_of_length_three_octets_0xE080FF_test(void)
{
    char const *text = "\xE0\x80\xFF";
    ASSERT_EQ(3,  strlen(text));
    ASSERT_EQ(-1, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_is_invalid_of_length_four_octets_0xF08080FF_test(void)
{
    char const *text = "\xF0\x80\x80\xFF";
    ASSERT_EQ(4,  strlen(text));
    ASSERT_EQ(-1, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_one_octet_0x01_test(void)
{
    char const *text = "\x01";
    ASSERT_EQ(1,  strlen(text));
    ASSERT_EQ(1, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_two_octets_0xC080_test(void)
{
    char const *text = "\xC0\x80";
    ASSERT_EQ(2,  strlen(text));
    ASSERT_EQ(2, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_two_octets_with_error_0xC000_test(void)
{
    char const *text = "\xC0\x00";
    ASSERT_EQ(1,  strlen(text));
    ASSERT_EQ(-1, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_two_octets_with_error_0xC070_test(void)
{
    char const *text = "\xC0\x70";
    ASSERT_EQ(2,  strlen(text));
    ASSERT_EQ(-1, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_three_octets_0xE08080_test(void)
{
    char const *text = "\xE0\x80\x80";
    ASSERT_EQ(3,  strlen(text));
    ASSERT_EQ(3, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_three_octets_with_error_0xE00080_test(void)
{
    char const *text = "\xE0\x00\x80";
    ASSERT_EQ(1,  strlen(text));
    ASSERT_EQ(-1, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_three_octets_with_error_0xE08000_test(void)
{
    char const *text = "\xE0\x80\x00";
    ASSERT_EQ(2,  strlen(text));
    ASSERT_EQ(-1, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_three_octets_with_error_0xE08070_test(void)
{
    char const *text = "\xE0\x80\x70";
    ASSERT_EQ(3,  strlen(text));
    ASSERT_EQ(-1, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_four_octets_0xF0808080_test(void)
{
    char const *text = "\xF0\x80\x80\x80";
    ASSERT_EQ(4,  strlen(text));
    ASSERT_EQ(4, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_four_octets_with_error_0xF0008080_test(void)
{
    char const *text = "\xF0\x00\x80\x80";
    ASSERT_EQ(1,  strlen(text));
    ASSERT_EQ(-1, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_four_octets_with_error_0xF0800080_test(void)
{
    char const *text = "\xF0\x80\x00\x80";
    ASSERT_EQ(2,  strlen(text));
    ASSERT_EQ(-1, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_four_octets_with_error_0xF0808000_test(void)
{
    char const *text = "\xF0\x80\x80\x00";
    ASSERT_EQ(3,  strlen(text));
    ASSERT_EQ(-1, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_four_octets_with_error_0xF0808070_test(void)
{
    char const *text = "\xF0\x80\x80\x70";
    ASSERT_EQ(4,  strlen(text));
    ASSERT_EQ(-1, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_one_of_five_octets_0x01F0808080_test(void)
{
    char const *text = "\x01\xF0\x80\x80\x80";
    ASSERT_EQ(5,  strlen(text));
    ASSERT_EQ(1, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_two_of_six_octets_0xC080F0808080_test(void)
{
    char const *text = "\xC0\x80\xF0\x80\x80\x80";
    ASSERT_EQ(6,  strlen(text));
    ASSERT_EQ(2, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_three_of_seven_octets_0xE08080F0808080_test(void)
{
    char const *text = "\xE0\x80\x80\xF0\x80\x80\x80";
    ASSERT_EQ(7,  strlen(text));
    ASSERT_EQ(3, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_octets_in_next_that_has_length_of_four_of_eight_octets_0xF0808080F0808080_test(void)
{
    char const *text = "\xF0\x80\x80\x80\xF0\x80\x80\x80";
    ASSERT_EQ(8,  strlen(text));
    ASSERT_EQ(4, octaspire_utf8_private_octets_in_next(text, strlen(text)));

    PASS();
}

TEST octaspire_utf8_private_decode_helper_error_with_more_octets_being_needed_than_available_test(void)
{
    char const *buffer = 0;
    uint32_t    result = 0;

    octaspire_utf8_decode_status_t const expected =
        OCTASPIRE_UTF8_DECODE_STATUS_INPUT_NOT_ENOUGH_OCTETS_AVAILABLE;

    for (size_t numOctetsNeeded = 1; numOctetsNeeded < 5; ++numOctetsNeeded)
    {
        ASSERT_EQ(
            expected,
            octaspire_utf8_private_decode_helper(buffer, numOctetsNeeded, 0, &result));
    }

    for (size_t numOctetsNeeded = 2; numOctetsNeeded < 5; ++numOctetsNeeded)
    {
        ASSERT_EQ(
            expected,
            octaspire_utf8_private_decode_helper(buffer, numOctetsNeeded, 1, &result));
    }

    for (size_t numOctetsNeeded = 3; numOctetsNeeded < 5; ++numOctetsNeeded)
    {
        ASSERT_EQ(
            expected,
            octaspire_utf8_private_decode_helper(buffer, numOctetsNeeded, 2, &result));
    }

    ASSERT_EQ(expected, octaspire_utf8_private_decode_helper(buffer, 4, 3, &result));

    PASS();
}

TEST octaspire_utf8_decode_character_null_string_test(void)
{
    char const *text = 0;
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(OCTASPIRE_UTF8_DECODE_STATUS_INPUT_IS_NULL, octaspire_utf8_decode_character(text, 0, &result, &numoctets));
    ASSERT_EQ(0, result);
    ASSERT_EQ(0, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_from_buffer_null_string_test(void)
{
    size_t const currentIndex = 0;
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_INPUT_IS_NULL,
        octaspire_utf8_decode_character_from_buffer(
            0,
            0,
            currentIndex,
            &result,
            &numoctets));

    ASSERT_EQ(0, result);
    ASSERT_EQ(0, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_empty_string_test(void)
{
    char const *text = "";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_INPUT_IS_NULL,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0, result);
    ASSERT_EQ(0, numoctets);

    PASS();
}

// TODO XXX Should this case be exactly the same as the above case with c-string?
// Now return value is different when decoded from c-string and buffer.
TEST octaspire_utf8_decode_character_from_buffer_empty_string_test(void)
{
    octaspire_container_vector_t *buffer =
        octaspire_container_vector_new(sizeof(char), false, 0, octaspireUtf8TestAllocator);

    size_t const currentIndex = 0;
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_INPUT_IS_NULL,
        octaspire_utf8_decode_character_from_buffer(
            octaspire_container_vector_get_element_at(buffer, 0),
            octaspire_container_vector_get_length_in_octets(buffer),
            currentIndex,
            &result,
            &numoctets));

    ASSERT_EQ(0, result);
    ASSERT_EQ(0, numoctets);

    octaspire_container_vector_release(buffer);
    buffer = 0;

    PASS();
}

TEST octaspire_utf8_decode_character_a_test(void)
{
    char const *text = "a";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_OK,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(97, result);
    ASSERT_EQ(1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_from_buffer_a_test(void)
{
    octaspire_container_vector_t *buffer =
        octaspire_container_vector_new(sizeof(char), false, 0, octaspireUtf8TestAllocator);

    octaspire_container_vector_push_back_char(buffer, 'a');
    size_t const currentIndex = 0;
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_OK,
        octaspire_utf8_decode_character_from_buffer(
            octaspire_container_vector_get_element_at(buffer, 0),
            octaspire_container_vector_get_length_in_octets(buffer),
            currentIndex,
            &result,
            &numoctets));

    ASSERT_EQ(97, result);
    ASSERT_EQ(1, numoctets);

    octaspire_container_vector_release(buffer);
    buffer = 0;

    PASS();
}

TEST octaspire_utf8_decode_character_the_copyright_sign_test(void)
{
    char const *text = "©";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_OK,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0xa9, result);
    ASSERT_EQ(2,    numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_not_equal_sign_test(void)
{
    char const *text = "≠";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_OK,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0x2260, result);
    ASSERT_EQ(3,      numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_linear_b_syllable_b008_a_test(void)
{
    char const *text = "𐀀";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_OK,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0x10000, result);
    ASSERT_EQ(4,       numoctets);

    PASS();
}

TEST octaspire_utf8_decode_a_short_string_test(void)
{
    char const *text = "A≢Α.한국어日本語𣎴";
    uint32_t result = 0;
    int numoctets = 0;

    uint32_t expectedResults[11]   =
    {
        0x0041,
        0x2262,
        0x0391,
        0x002E,
        0xD55C,
        0xAD6D,
        0xC5B4,
        0x65E5,
        0x672C,
        0x8A9E,
        0x233B4
    };

    int      expectedNumOctets[11] =
    {
        1,
        3,
        2,
        1,
        3,
        3,
        3,
        3,
        3,
        3,
        4
    };

    for (size_t i = 0; i < 11; ++i)
    {
        ASSERT_EQ(
            OCTASPIRE_UTF8_DECODE_STATUS_OK,
            octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

        ASSERT_EQ(expectedResults[i],   result);
        ASSERT_EQ(expectedNumOctets[i], numoctets);

        text += numoctets;
    }

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_INPUT_IS_NULL,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,     result);
    ASSERT_EQ(0,     numoctets);

    PASS();
}

// Is this good test? Is there potential out of bounds read possibility
// in the decoding part (from the encoded.octets) if the counting
// has error.
TEST octaspire_utf8_encode_and_then_decode_a_short_string_test(void)
{
    uint32_t result = 0;
    int numoctets = 0;

    uint32_t expectedResults[11]   =
    {
        0x0041,
        0x2262,
        0x0391,
        0x002E,
        0xD55C,
        0xAD6D,
        0xC5B4,
        0x65E5,
        0x672C,
        0x8A9E,
        0x233B4
    };

    size_t expectedNumOctets[11] =
    {
        1,
        3,
        2,
        1,
        3,
        3,
        3,
        3,
        3,
        3,
        4
    };

    octaspire_utf8_character_t encoded;


    for (size_t i = 0; i < 11; ++i)
    {
        ASSERT_EQ(
            OCTASPIRE_UTF8_ENCODE_STATUS_OK,
            octaspire_utf8_encode_character(expectedResults[i], &encoded));

        ASSERT_EQ(
            OCTASPIRE_UTF8_DECODE_STATUS_OK,
            octaspire_utf8_decode_character(
                (char const * const)(encoded.octets + (4 - expectedNumOctets[i])),
                expectedNumOctets[i],
                &result,
                &numoctets));

        ASSERT_EQ(expectedResults[i],   result);
        ASSERT_EQ(((int)expectedNumOctets[i]), numoctets);
    }

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_overlong_representations_of_the_null_character_test(void)
{
    // C0 80
    char const *text = "\xC0\x80";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0, result);
    ASSERT_EQ(2, numoctets);

    // E0 80 80
    text = "\xE0\x80\x80";
    result = 0;
    numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0, result);
    ASSERT_EQ(3, numoctets);

    // F0 80 80 80
    text = "\xF0\x80\x80\x80";
    result = 0;
    numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0, result);
    ASSERT_EQ(4, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_0x80_test(void)
{
    char const *text = "\x80";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_from_buffer_illegal_octet_0x80_test(void)
{
    octaspire_container_vector_t *buffer =
        octaspire_container_vector_new(sizeof(char), false, 0, octaspireUtf8TestAllocator);

    octaspire_container_vector_push_back_char(buffer, '\x80');
    size_t const currentIndex = 0;
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character_from_buffer(
            octaspire_container_vector_get_element_at(buffer, 0),
            octaspire_container_vector_get_length_in_octets(buffer),
            currentIndex,
            &result,
            &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    octaspire_container_vector_release(buffer);
    buffer = 0;

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xC0_0x01_test(void)
{
    char const *text = "\xC0\x01";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xC0_test(void)
{
    char const *text = "\xC0";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xE0_0x80_0x01_test(void)
{
    char const *text = "\xE0\x80\x01";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xE0_0x80_test(void)
{
    char const *text = "\xE0\x80";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xE0_test(void)
{
    char const *text = "\xE0";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xF0_0x80_0x80_0x01_test(void)
{
    char const *text = "\xF0\x80\x80\x01";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xF0_0x80_0x80_test(void)
{
    char const *text = "\xF0\x80\x80";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xF0_0x80_test(void)
{
    char const *text = "\xF0\x80";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xF0_test(void)
{
    char const *text = "\xF0";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xF0_0xC0_0xC0_0xC0_test(void)
{
    char const *text = "\xF0\xC0\xC0\xC0";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xE0_0xC0_0xC0_test(void)
{
    char const *text = "\xE0\xC0\xC0";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xC0_0xC0_test(void)
{
    char const *text = "\xC0\xC0";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_0xFF_test(void)
{
    char const *text = "\xFF";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_0xFE_test(void)
{
    char const *text = "\xFE";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xFE_0xFE_0xFF_0xFF_test(void)
{
    char const *text = "\xFE\xFE\xFF\xFF";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xC0_0xAF_test(void)
{
    char const *text = "\xC0\xAF";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0x2F, result);
    ASSERT_EQ(2,    numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xE0_0x80_0xAF_test(void)
{
    char const *text = "\xE0\x80\xAF";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0x2F, result);
    ASSERT_EQ(3,    numoctets);

    PASS();
}

TEST octaspire_utf8_decode_character_illegal_octet_sequence_0xF0_0x80_0x80_0xAF_test(void)
{
    char const *text = "\xF0\x80\x80\xAF";
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER,
        octaspire_utf8_decode_character(text, strlen(text), &result, &numoctets));

    ASSERT_EQ(0x2F, result);
    ASSERT_EQ(4,    numoctets);

    PASS();
}

static size_t octaspireUtf8SuiteNumTimesRun = 0;

GREATEST_SUITE(octaspire_utf8_suite)
{
    octaspireUtf8SuiteNumTimesRun = 0;

    octaspireUtf8TestAllocator = octaspire_memory_allocator_new_create_region(
        OCTASPIRE_CORE_CONFIG_MEMORY_ALLOCATOR_REGION_MIN_BLOCK_SIZE_IN_OCTETS);

second_run:

    assert(octaspireUtf8TestAllocator);

    RUN_TEST(octaspire_utf8_private_rangeof_test);
    RUN_TEST(octaspire_utf8_private_high_order_bits_test);
    RUN_TEST(octaspire_utf8_private_set_bit_test);
    RUN_TEST(octaspire_utf8_private_get_bit_test);
    RUN_TEST(octaspire_utf8_encode_character_NUL_test);
    RUN_TEST(octaspire_utf8_encode_character_SOH_test);
    RUN_TEST(octaspire_utf8_encode_character_space_test);
    RUN_TEST(octaspire_utf8_encode_character_A_test);
    RUN_TEST(octaspire_utf8_encode_character_control_U_PLUS_0080_test);
    RUN_TEST(octaspire_utf8_encode_character_latin_small_letter_a_with_diaeresis_test);
    RUN_TEST(octaspire_utf8_encode_character_latin_small_letter_y_with_diaeresis_test);
    RUN_TEST(octaspire_utf8_encode_character_copyright_sign_test);
    RUN_TEST(octaspire_utf8_encode_character_not_equal_symbol_test);
    RUN_TEST(octaspire_utf8_encode_character_linear_b_syllable_b008_a_test);
    RUN_TEST(octaspire_utf8_encode_character_of_illegal_range_test);
    RUN_TEST(octaspire_utf8_encode_character_illegal_range_from_U_PLUS_D800_to_U_PLUS_DFFF_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_is_empty_string_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_is_null_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_is_invalid_of_length_one_octet_0x80_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_is_invalid_of_length_two_octets_0xC0FF_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_is_invalid_of_length_three_octets_0xE080FF_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_is_invalid_of_length_four_octets_0xF08080FF_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_one_octet_0x01_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_two_octets_0xC080_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_two_octets_with_error_0xC000_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_two_octets_with_error_0xC070_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_three_octets_0xE08080_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_three_octets_with_error_0xE00080_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_three_octets_with_error_0xE08000_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_three_octets_with_error_0xE08070_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_four_octets_0xF0808080_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_four_octets_with_error_0xF0008080_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_four_octets_with_error_0xF0800080_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_four_octets_with_error_0xF0808000_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_four_octets_with_error_0xF0808070_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_one_of_five_octets_0x01F0808080_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_two_of_six_octets_0xC080F0808080_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_three_of_seven_octets_0xE08080F0808080_test);
    RUN_TEST(octaspire_utf8_private_octets_in_next_that_has_length_of_four_of_eight_octets_0xF0808080F0808080_test);
    RUN_TEST(octaspire_utf8_private_decode_helper_error_with_more_octets_being_needed_than_available_test);
    RUN_TEST(octaspire_utf8_decode_character_null_string_test);
    RUN_TEST(octaspire_utf8_decode_character_from_buffer_null_string_test);
    RUN_TEST(octaspire_utf8_decode_character_empty_string_test);
    RUN_TEST(octaspire_utf8_decode_character_from_buffer_empty_string_test);
    RUN_TEST(octaspire_utf8_decode_character_a_test);
    RUN_TEST(octaspire_utf8_decode_character_from_buffer_a_test);
    RUN_TEST(octaspire_utf8_decode_character_the_copyright_sign_test);
    RUN_TEST(octaspire_utf8_decode_character_not_equal_sign_test);
    RUN_TEST(octaspire_utf8_decode_character_linear_b_syllable_b008_a_test);
    RUN_TEST(octaspire_utf8_decode_a_short_string_test);
    RUN_TEST(octaspire_utf8_encode_and_then_decode_a_short_string_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_overlong_representations_of_the_null_character_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_0x80_test);
    RUN_TEST(octaspire_utf8_decode_character_from_buffer_illegal_octet_0x80_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xC0_0x01_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xC0_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xE0_0x80_0x01_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xE0_0x80_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xE0_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xF0_0x80_0x80_0x01_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xF0_0x80_0x80_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xF0_0x80_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xF0_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xF0_0xC0_0xC0_0xC0_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xE0_0xC0_0xC0_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xC0_0xC0_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_0xFF_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_0xFE_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xFE_0xFE_0xFF_0xFF_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xC0_0xAF_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xE0_0x80_0xAF_test);
    RUN_TEST(octaspire_utf8_decode_character_illegal_octet_sequence_0xF0_0x80_0x80_0xAF_test);

    octaspire_memory_allocator_release(octaspireUtf8TestAllocator);
    octaspireUtf8TestAllocator = 0;

    ++octaspireUtf8SuiteNumTimesRun;

    if (octaspireUtf8SuiteNumTimesRun < 2)
    {
        // Second run without region allocator

        octaspireUtf8TestAllocator = octaspire_memory_allocator_new(0);

        goto second_run;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../test/test_utf8.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../test/test_memory.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

TEST octaspire_memory_allocator_new_test(void)
{
    octaspire_memory_allocator_t *allocator = octaspire_memory_allocator_new(0);

    ASSERT(allocator);

    ASSERT_EQ(0, allocator->numberOfFutureAllocationsToBeRigged);
    ASSERT_EQ(0, allocator->bitIndex);

    size_t const bitQueueLen = sizeof(allocator->bitQueue) / sizeof(allocator->bitQueue[0]);
    ASSERT_EQ(20, bitQueueLen);

    for (size_t i = 0; i < bitQueueLen; ++i)
    {
        ASSERT_EQ(0, allocator->bitQueue[i]);
    }


    octaspire_memory_allocator_release(allocator);
    allocator = 0;

    PASS();
}

// How to test this efficiently, etc.?
/*
TEST octaspire_memory_allocator_new_failure_test(void)
{
    octaspire_memory_allocator_t *allocator = octaspire_memory_allocator_new();

    ASSERT_FALSE(allocator);

    octaspire_memory_allocator_release(allocator);
    allocator = 0;

    PASS();
}
*/

TEST octaspire_memory_allocator_malloc_test(void)
{
    octaspire_memory_allocator_t *allocator = octaspire_memory_allocator_new(0);

    size_t *ptrs[100];

    size_t const elemsize = sizeof(ptrs[0]);
    size_t const nelems   = sizeof(ptrs) / elemsize;

    for (size_t i = 0; i < nelems; ++i)
    {
        ptrs[i] = octaspire_memory_allocator_malloc(allocator, elemsize);
        ASSERT(ptrs[i]);
        ASSERT_EQ(0, *(ptrs[i]));
        *(ptrs[i]) = i;
    }

    for (size_t i = 0; i < nelems; ++i)
    {
        ASSERT_EQ(i, *(ptrs[i]));
    }

    for (size_t i = 0; i < nelems; ++i)
    {
        octaspire_memory_allocator_free(allocator, ptrs[i]);
        ptrs[i] = 0;
    }

    octaspire_memory_allocator_release(allocator);
    allocator = 0;

    PASS();
}

#if 0
TEST octaspire_memory_allocator_realloc_failure_test(void)
{
    octaspire_memory_allocator_t *allocator = octaspire_memory_allocator_new(0);

    ASSERT_EQ(0, octaspire_memory_allocator_realloc(allocator, 0, SIZE_MAX));

    octaspire_memory_allocator_release(allocator);
    allocator = 0;

    PASS();
}
#endif

TEST octaspire_memory_allocator_free_test(void)
{
    octaspire_memory_allocator_t *allocator = octaspire_memory_allocator_new(0);

    octaspire_memory_allocator_free(allocator, 0);
    octaspire_memory_allocator_free(allocator, octaspire_memory_allocator_malloc(allocator, 10));

    octaspire_memory_allocator_release(allocator);
    allocator = 0;

    PASS();
}

#if 0
TEST octaspire_memory_allocator_malloc_failure_test(void)
{
    octaspire_memory_allocator_t *allocator = octaspire_memory_allocator_new(0);

    ASSERT_EQ(0, octaspire_memory_allocator_malloc(allocator, SIZE_MAX));

    octaspire_memory_allocator_release(allocator);
    allocator = 0;

    PASS();
}
#endif

TEST octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged_when_larger_than_32_test(void)
{
    octaspire_memory_allocator_t *allocator = octaspire_memory_allocator_new(0);

    ASSERT_EQ(0, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    size_t const count = 640;

    uint32_t const bitPattern = 0x55; // 0101 0101

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged_when_larger_than_32(
        allocator,
        count,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern,
        bitPattern);

   ASSERT_EQ(count, allocator->numberOfFutureAllocationsToBeRigged);
   ASSERT_EQ(0,     allocator->bitIndex);

   for (size_t i = 0; i < (sizeof(allocator->bitQueue) / sizeof(allocator->bitQueue[0])); ++i)
   {
       ASSERT_EQ(bitPattern, allocator->bitQueue[i]);
   }

   ASSERT_EQ(count, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

   for (size_t i = 0; i < count; ++i)
   {
       if (i % 2 == 0)
       {
           ASSERT(octaspire_memory_allocator_private_test_bit(allocator));
       }
       else
       {
           ASSERT_FALSE(octaspire_memory_allocator_private_test_bit(allocator));
       }

       ++(allocator->bitIndex);
   }

   ASSERT_EQ(count, allocator->bitIndex);

   octaspire_memory_allocator_release(allocator);
   allocator = 0;

   PASS();
}

TEST octaspire_memory_allocator_setting_and_getting_future_allocations_to_fail_and_using_with_malloc_test(void)
{
    octaspire_memory_allocator_t *allocator = octaspire_memory_allocator_new(0);

    ASSERT_EQ(0, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    size_t count = 32;

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(allocator, count, 0);

    ASSERT_EQ(count, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    for (size_t i = count; i > 0; --i)
    {
        ASSERT_FALSE(octaspire_memory_allocator_malloc(allocator, 1));
        ASSERT_EQ(i - 1, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(allocator));
    }

    ASSERT_EQ(0, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    void *ptr = octaspire_memory_allocator_malloc(allocator, 1);
    ASSERT(ptr);
    octaspire_memory_allocator_free(allocator, ptr);
    ptr = 0;

    ASSERT_EQ(0, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    octaspire_memory_allocator_release(allocator);
    allocator = 0;

    PASS();
}

TEST octaspire_memory_allocator_setting_and_getting_future_allocations_to_fail_and_using_with_realloc_test(void)
{
    octaspire_memory_allocator_t *allocator = octaspire_memory_allocator_new(0);

    ASSERT_EQ(0, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    void *buffer = octaspire_memory_allocator_malloc(allocator, 1);

    ASSERT(buffer);

    size_t count = 32;

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(allocator, count, 0);

    ASSERT_EQ(count, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    for (size_t i = count; i > 0; --i)
    {
        ASSERT_FALSE(octaspire_memory_allocator_realloc(allocator, buffer, 2));
        ASSERT_EQ(i - 1, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(allocator));
    }

    ASSERT_EQ(0, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    void *ptr = octaspire_memory_allocator_realloc(allocator, buffer, 2);
    ASSERT(ptr);
    octaspire_memory_allocator_free(allocator, ptr);
    ptr = 0;

    ASSERT_EQ(0, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    octaspire_memory_allocator_release(allocator);
    allocator = 0;

    PASS();
}



GREATEST_SUITE(octaspire_memory_suite)
{
    RUN_TEST(octaspire_memory_allocator_new_test);
    //RUN_TEST(octaspire_memory_allocator_new_failure_test);
    RUN_TEST(octaspire_memory_allocator_malloc_test);
    //RUN_TEST(octaspire_memory_allocator_realloc_failure_test);
    RUN_TEST(octaspire_memory_allocator_free_test);
    //RUN_TEST(octaspire_memory_allocator_malloc_failure_test);
    RUN_TEST(octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged_when_larger_than_32_test);
    RUN_TEST(octaspire_memory_allocator_setting_and_getting_future_allocations_to_fail_and_using_with_malloc_test);
    RUN_TEST(octaspire_memory_allocator_setting_and_getting_future_allocations_to_fail_and_using_with_realloc_test);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../test/test_memory.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../test/test_region.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

TEST octaspire_region_block_new_test(void)
{
    octaspire_region_block_t *regionBlock = octaspire_region_block_new(1024);

    ASSERT(regionBlock);

    ASSERT   (regionBlock->buffer);
    ASSERT_EQ(1024, regionBlock->bufferLengthInOctets);
    ASSERT_EQ(0,    regionBlock->firstFreeIndex);

    octaspire_region_block_release(regionBlock);
    regionBlock = 0;

    PASS();
}

TEST octaspire_region_block_malloc_test(void)
{
    octaspire_region_block_t *regionBlock = octaspire_region_block_new(1024*1024);

    size_t *ptrs[100];

    size_t const elemsize = sizeof(ptrs[0]);
    size_t const nelems   = sizeof(ptrs) / elemsize;

    for (size_t i = 0; i < nelems; ++i)
    {
        ptrs[i] = octaspire_region_block_malloc(regionBlock, elemsize);
        ASSERT(ptrs[i]);
        ASSERT_EQ(0, *(ptrs[i]));
        *(ptrs[i]) = i;
    }

    for (size_t i = 0; i < nelems; ++i)
    {
        ASSERT_EQ(i, *(ptrs[i]));
    }

    void *ptr = regionBlock->buffer + (sizeof(size_t) * 4);
    for (size_t i = 0; i < 100; ++i)
    {
        size_t headerInUse = 0;
        memcpy(&headerInUse, ((char*)ptr - (sizeof(size_t) * 4)), sizeof(size_t));

        size_t headerUserDataLen = 0;
        memcpy(&headerUserDataLen, ((char*)ptr - (sizeof(size_t) * 3)), sizeof(size_t));

        ASSERT_EQ(1,              headerInUse);
        ASSERT_EQ(sizeof(size_t), headerUserDataLen);
    }

    for (size_t i = 0; i < nelems; ++i)
    {
        octaspire_region_block_free(regionBlock, ptrs[i]);
        ptrs[i] = 0;
    }

    octaspire_region_block_release(regionBlock);
    regionBlock = 0;

    PASS();
}

GREATEST_SUITE(octaspire_region_suite)
{
    RUN_TEST(octaspire_region_block_new_test);
    RUN_TEST(octaspire_region_block_malloc_test);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../test/test_region.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../test/test_stdio.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

static octaspire_memory_allocator_t *octaspireStdioTestAllocator = 0;

TEST octaspire_stdio_new_test(void)
{
    octaspire_stdio_t *stdio = octaspire_stdio_new(octaspireStdioTestAllocator);

    ASSERT(stdio);

    ASSERT_EQ(0, stdio->numberOfFutureReadsToBeRigged);
    ASSERT_EQ(0, stdio->bitIndex);
    ASSERT_EQ(0, stdio->bitQueue);
    ASSERT_EQ(octaspireStdioTestAllocator, stdio->allocator);

    octaspire_stdio_release(stdio);
    stdio = 0;

    PASS();
}

TEST octaspire_stdio_new_allocation_failure_test(void)
{
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireStdioTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireStdioTestAllocator));

    octaspire_stdio_t *stdio = octaspire_stdio_new(octaspireStdioTestAllocator);

    ASSERT_FALSE(stdio);

    ASSERT_EQ(
        0,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireStdioTestAllocator));

    octaspire_stdio_release(stdio);
    stdio = 0;

    PASS();
}

TEST octaspire_stdio_fread_test(void)
{
    octaspire_stdio_t *stdio = octaspire_stdio_new(octaspireStdioTestAllocator);

    ASSERT(stdio);

    FILE *f = fopen(OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_stdio_fread_test", "rb");

    ASSERT(f);

    char octet = 0;
    char const * const expected = "0123456789qwertyuiop";

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(1, octaspire_stdio_fread(stdio, &octet, sizeof(octet), 1, f));
        ASSERT_EQ(expected[i], octet);
    }

    fclose(f);
    f = 0;

    octaspire_stdio_release(stdio);
    stdio = 0;

    PASS();
}

TEST octaspire_stdio_fread_rigging_and_failure_test(void)
{
    octaspire_stdio_t *stdio = octaspire_stdio_new(octaspireStdioTestAllocator);

    ASSERT(stdio);

    FILE *f = fopen(OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_stdio_fread_test", "rb");

    ASSERT(f);

    char octet = 0;
    char const * const expected = "0123456789qwertyuiop";

    // 0101 0101 0101 0101 0101
    //    5    5    5    5    5
    octaspire_stdio_set_number_and_type_of_future_reads_to_be_rigged(stdio, 20, 0x55555);

    ASSERT_EQ(20, octaspire_stdio_get_number_of_future_reads_to_be_rigged(stdio));

    size_t index = 0;
    for (size_t i = 0; i < strlen(expected); ++i)
    {
        if (i % 2)
        {
            ASSERT_EQ(0, octaspire_stdio_fread(stdio, &octet, sizeof(octet), 1, f));
        }
        else
        {
            ASSERT_EQ(1, octaspire_stdio_fread(stdio, &octet, sizeof(octet), 1, f));
            ASSERT_EQ(expected[index], octet);
            ++index;
        }
    }

    ASSERT_EQ(0, octaspire_stdio_get_number_of_future_reads_to_be_rigged(stdio));

    fclose(f);
    f = 0;

    octaspire_stdio_release(stdio);
    stdio = 0;

    PASS();
}

static size_t octaspireStdioSuiteNumTimesRun = 0;

GREATEST_SUITE(octaspire_stdio_suite)
{
    octaspireStdioSuiteNumTimesRun = 0;

    octaspireStdioTestAllocator = octaspire_memory_allocator_new_create_region(
        OCTASPIRE_CORE_CONFIG_MEMORY_ALLOCATOR_REGION_MIN_BLOCK_SIZE_IN_OCTETS);

second_run:

    assert(octaspireStdioTestAllocator);

    RUN_TEST(octaspire_stdio_new_test);
    RUN_TEST(octaspire_stdio_new_allocation_failure_test);
    RUN_TEST(octaspire_stdio_fread_test);
    RUN_TEST(octaspire_stdio_fread_rigging_and_failure_test);

    octaspire_memory_allocator_release(octaspireStdioTestAllocator);
    octaspireStdioTestAllocator = 0;

    ++octaspireStdioSuiteNumTimesRun;

    if (octaspireStdioSuiteNumTimesRun < 2)
    {
        // Second run without region allocator

        octaspireStdioTestAllocator      = octaspire_memory_allocator_new(0);

        goto second_run;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../test/test_stdio.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../test/test_input.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

static octaspire_memory_allocator_t *octaspireInputTestAllocator = 0;
static octaspire_stdio_t            *octaspireInputTestStdio = 0;

TEST octaspire_input_new_from_c_string_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    ASSERT(input->text);

    size_t const numUcsChars =
        octaspire_container_utf8_string_get_length_in_ucs_characters(input->text);

    ASSERT_EQ(6, numUcsChars);

    ASSERT_EQ(0x61,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 0));
    ASSERT_EQ(0x62,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 1));
    ASSERT_EQ(0x63,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 2));
    ASSERT_EQ(0xa9,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 3));
    ASSERT_EQ(0x2260,  octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 4));
    ASSERT_EQ(0x10000, octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 5));

    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);

    ASSERT_EQ(6, octaspire_input_get_length_in_ucs_characters(input));

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_c_string_called_with_null_string_test(void)
{
    octaspire_input_t *input = octaspire_input_new_from_c_string(0, octaspireInputTestAllocator);

    ASSERT(input);

    ASSERT(input->text);

    ASSERT_EQ(0,         octaspire_container_utf8_string_get_length_in_ucs_characters(input->text));
    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);

    ASSERT_EQ(0, octaspire_input_get_length_in_ucs_characters(input));

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_c_string_with_allocation_failure_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireInputTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT_EQ(
        0,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    ASSERT_FALSE(input);

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_buffer_test(void)
{
    char const buffer[] =
    {
        'a',
        'b',
        'c',
        '\xC2',
        '\xA9',
        '\xE2',
        '\x89',
        '\xA0',
        '\xF0',
        '\x90',
        '\x80',
        '\x80'
    };

    octaspire_input_t *input = octaspire_input_new_from_buffer(
        buffer, sizeof(buffer) / sizeof(buffer[0]),
        octaspireInputTestAllocator);

    ASSERT(input);

    ASSERT(input->text);

    size_t const numUcsChars =
        octaspire_container_utf8_string_get_length_in_ucs_characters(input->text);

    ASSERT_EQ(6, numUcsChars);

    ASSERT_EQ(0x61,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 0));
    ASSERT_EQ(0x62,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 1));
    ASSERT_EQ(0x63,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 2));
    ASSERT_EQ(0xa9,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 3));
    ASSERT_EQ(0x2260,  octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 4));
    ASSERT_EQ(0x10000, octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 5));

    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);

    ASSERT_EQ(6, octaspire_input_get_length_in_ucs_characters(input));

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_buffer_with_allocation_failure_0x00_test(void)
{
    char const buffer[] =
    {
        'a',
        'b',
        'c',
        '\xC2',
        '\xA9',
        '\xE2',
        '\x89',
        '\xA0',
        '\xF0',
        '\x90',
        '\x80',
        '\x80'
    };

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireInputTestAllocator,
        1,
        0x00);

    ASSERT_EQ(
        1,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    octaspire_input_t *input = octaspire_input_new_from_buffer(
        buffer, sizeof(buffer) / sizeof(buffer[0]),
        octaspireInputTestAllocator);

    ASSERT_EQ(
        0,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    ASSERT_FALSE(input);

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_buffer_with_allocation_failure_0x01_test(void)
{
    char const buffer[] =
    {
        'a',
        'b',
        'c',
        '\xC2',
        '\xA9',
        '\xE2',
        '\x89',
        '\xA0',
        '\xF0',
        '\x90',
        '\x80',
        '\x80'
    };

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireInputTestAllocator,
        2,
        0x01);

    ASSERT_EQ(
        2,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    octaspire_input_t *input = octaspire_input_new_from_buffer(
        buffer, sizeof(buffer) / sizeof(buffer[0]),
        octaspireInputTestAllocator);

    ASSERT_EQ(
        0,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    ASSERT_FALSE(input);

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_path_test(void)
{
    octaspire_input_t *input = octaspire_input_new_from_path(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_input_new_from_path_test",
        octaspireInputTestAllocator,
        octaspireInputTestStdio);

    ASSERT(input);

    ASSERT(input->text);

    size_t const numUcsChars =
        octaspire_container_utf8_string_get_length_in_ucs_characters(input->text);

    ASSERT_EQ(6, numUcsChars);

    ASSERT_EQ(0x61,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 0));
    ASSERT_EQ(0x62,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 1));
    ASSERT_EQ(0x63,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 2));
    ASSERT_EQ(0xa9,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 3));
    ASSERT_EQ(0x2260,  octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 4));
    ASSERT_EQ(0x10000, octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 5));

    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);

    ASSERT_EQ(6, octaspire_input_get_length_in_ucs_characters(input));

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_path_failure_on_nonexisting_file_test(void)
{
    octaspire_input_t *input = octaspire_input_new_from_path(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_input_new_from_path_failure_on_nonexisting_file_test",
        octaspireInputTestAllocator,
        octaspireInputTestStdio);

    ASSERT_FALSE(input);

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_path_allocation_failure_test(void)
{
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireInputTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    octaspire_input_t *input = octaspire_input_new_from_path(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_input_new_from_path_test",
        octaspireInputTestAllocator,
        octaspireInputTestStdio);

    ASSERT_EQ(
        0,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    ASSERT_FALSE(input);

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_get_length_in_ucs_characters_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    ASSERT_EQ(6, octaspire_input_get_length_in_ucs_characters(input));

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_clear_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    ASSERT(input->text);

    size_t const numUcsChars =
        octaspire_container_utf8_string_get_length_in_ucs_characters(input->text);

    ASSERT_EQ(6, numUcsChars);

    ASSERT_EQ(0x61,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 0));
    ASSERT_EQ(0x62,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 1));
    ASSERT_EQ(0x63,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 2));
    ASSERT_EQ(0xa9,    octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 3));
    ASSERT_EQ(0x2260,  octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 4));
    ASSERT_EQ(0x10000, octaspire_container_utf8_string_get_ucs_character_at_index(input->text, 5));

    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);

    ASSERT_EQ(6, octaspire_input_get_length_in_ucs_characters(input));

    octaspire_input_clear(input);

    ASSERT(input->text);

    ASSERT_EQ(0, octaspire_container_utf8_string_get_length_in_ucs_characters(input->text));

    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);

    ASSERT_EQ(0, octaspire_input_get_length_in_ucs_characters(input));

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_rewind_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);

    ASSERT_EQ(6, octaspire_input_get_length_in_ucs_characters(input));

    while (octaspire_input_is_good(input))
    {
        ASSERT(octaspire_input_pop_next_ucs_character(input));
    }

    ASSERT_FALSE(octaspire_input_is_good(input));

    octaspire_input_rewind(input);
    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);
    ASSERT(octaspire_input_is_good(input));

    uint32_t expected[] = {0x61, 0x62, 0x63, 0xa9, 0x2260, 0x10000};

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT(octaspire_input_is_good(input));
        ASSERT_EQ(expected[i], octaspire_input_peek_next_ucs_character(input));
        ASSERT(octaspire_input_pop_next_ucs_character(input));
    }

    ASSERT_FALSE(octaspire_input_is_good(input));

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_peek_next_ucs_character_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    uint32_t expected[] = {0x61, 0x62, 0x63, 0xa9, 0x2260, 0x10000};

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT(octaspire_input_is_good(input));
        ASSERT_EQ(expected[i], octaspire_input_peek_next_ucs_character(input));
        ASSERT(octaspire_input_pop_next_ucs_character(input));
    }

    ASSERT_FALSE(octaspire_input_is_good(input));

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_FALSE(octaspire_input_is_good(input));
        ASSERT_EQ(0, octaspire_input_peek_next_ucs_character(input));
    }

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_pop_next_ucs_character_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    uint32_t expected[] = {0x61, 0x62, 0x63, 0xa9, 0x2260, 0x10000};

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT(octaspire_input_is_good(input));
        ASSERT_EQ(expected[i], octaspire_input_peek_next_ucs_character(input));
        ASSERT(octaspire_input_pop_next_ucs_character(input));
    }

    ASSERT_FALSE(octaspire_input_is_good(input));

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_FALSE(octaspire_input_is_good(input));
        ASSERT_EQ(0, octaspire_input_peek_next_ucs_character(input));
        ASSERT_FALSE(octaspire_input_pop_next_ucs_character(input));
    }

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_pop_next_ucs_character_current_line_and_column_are_calculated_correctly_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80\ndef\nghi";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    size_t expected_line[]   = {1, 1, 1, 1, 1, 1, 1,      2, 2, 2, 2,    3, 3, 3};
    size_t expected_column[] = {1, 2, 3, 4, 5, 6, 7,      1, 2, 3, 4,    1, 2, 3};

    ASSERT_EQ(
        sizeof(expected_line) / sizeof(expected_line[0]),
        octaspire_input_get_length_in_ucs_characters(input));

    ASSERT_EQ(
        sizeof(expected_column) / sizeof(expected_column[0]),
        octaspire_input_get_length_in_ucs_characters(input));

    for (size_t i = 0; i < octaspire_input_get_length_in_ucs_characters(input); ++i)
    {
        ASSERT(octaspire_input_is_good(input));

        ASSERT_EQ(expected_line[i],   input->line);
        ASSERT_EQ(expected_column[i], input->column);

        ASSERT(octaspire_input_pop_next_ucs_character(input));
    }

    ASSERT_FALSE(octaspire_input_is_good(input));

    size_t const lastIndex = octaspire_input_get_length_in_ucs_characters(input) - 1;

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQ(expected_column[lastIndex], input->column);
        ASSERT_FALSE(octaspire_input_is_good(input));
        ASSERT_EQ(expected_line[lastIndex],   input->line);
        ASSERT_EQ(expected_column[lastIndex], input->column);
        ASSERT_FALSE(octaspire_input_pop_next_ucs_character(input));
    }

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_is_good_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT(octaspire_input_is_good(input));
        ASSERT(octaspire_input_pop_next_ucs_character(input));
    }

    ASSERT_FALSE(octaspire_input_is_good(input));

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_FALSE(octaspire_input_is_good(input));
        ASSERT_FALSE(octaspire_input_pop_next_ucs_character(input));
    }

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_private_is_ucs_character_index_valid_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    for (size_t i = 0; i < 1024; ++i)
    {
        bool const valid = octaspire_input_private_is_ucs_character_index_valid(input, i);
        if (i < octaspire_input_get_length_in_ucs_characters(input))
        {
            ASSERT(valid);
        }
        else
        {
            ASSERT_FALSE(valid);
        }
    }

    octaspire_input_release(input);
    input = 0;

    PASS();
}

static size_t octaspireInputSuiteNumTimesRun = 0;

GREATEST_SUITE(octaspire_input_suite)
{
    octaspireInputSuiteNumTimesRun = 0;

    octaspireInputTestAllocator = octaspire_memory_allocator_new_create_region(
        OCTASPIRE_CORE_CONFIG_MEMORY_ALLOCATOR_REGION_MIN_BLOCK_SIZE_IN_OCTETS);

    octaspireInputTestStdio = octaspire_stdio_new(octaspireInputTestAllocator);

second_run:

    assert(octaspireInputTestAllocator);
    assert(octaspireInputTestStdio);

    RUN_TEST(octaspire_input_new_from_c_string_test);
    RUN_TEST(octaspire_input_new_from_c_string_called_with_null_string_test);
    RUN_TEST(octaspire_input_new_from_c_string_with_allocation_failure_test);
    RUN_TEST(octaspire_input_new_from_buffer_test);
    RUN_TEST(octaspire_input_new_from_buffer_with_allocation_failure_0x00_test);
    RUN_TEST(octaspire_input_new_from_buffer_with_allocation_failure_0x01_test);
    RUN_TEST(octaspire_input_new_from_path_test);
    RUN_TEST(octaspire_input_new_from_path_failure_on_nonexisting_file_test);
    RUN_TEST(octaspire_input_new_from_path_allocation_failure_test);
    RUN_TEST(octaspire_input_get_length_in_ucs_characters_test);
    RUN_TEST(octaspire_input_clear_test);
    RUN_TEST(octaspire_input_rewind_test);
    RUN_TEST(octaspire_input_peek_next_ucs_character_test);
    RUN_TEST(octaspire_input_pop_next_ucs_character_test);
    RUN_TEST(octaspire_input_pop_next_ucs_character_current_line_and_column_are_calculated_correctly_test);
    RUN_TEST(octaspire_input_is_good_test);
    RUN_TEST(octaspire_input_private_is_ucs_character_index_valid_test);

    octaspire_stdio_release(octaspireInputTestStdio);
    octaspireInputTestStdio = 0;

    octaspire_memory_allocator_release(octaspireInputTestAllocator);
    octaspireInputTestAllocator = 0;

    ++octaspireInputSuiteNumTimesRun;

    if (octaspireInputSuiteNumTimesRun < 2)
    {
        // Second run without region allocator

        octaspireInputTestAllocator      = octaspire_memory_allocator_new(0);
        octaspireInputTestStdio = octaspire_stdio_new(octaspireInputTestAllocator);

        goto second_run;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../test/test_input.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../test/test_container_vector.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

static octaspire_memory_allocator_t *octaspireContainerVectorTestAllocator = 0;

TEST octaspire_container_vector_private_index_to_pointer_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_container_vector_push_back_element(vec, &i);
    }

    for (size_t i = 0; i < len; ++i)
    {
        size_t const * expected = (size_t const *)(vec->elements) + i;

        ASSERT_EQ(
            expected,
            (size_t const *)octaspire_container_vector_private_index_to_pointer(vec, i));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_private_index_to_pointer_const_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_container_vector_push_back_element(vec, &i);
    }

    for (size_t i = 0; i < len; ++i)
    {
        size_t const * expected = (size_t const *)(vec->elements) + i;

        ASSERT_EQ(
            expected,
            (size_t const *)octaspire_container_vector_private_index_to_pointer_const(vec, i));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_private_grow_with_factor_2_success_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(double), false, 0, octaspireContainerVectorTestAllocator);

    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;
    size_t const       originalNumAllocated = vec->numAllocated;

    char *expectedInitializedMemory =
        octaspire_memory_allocator_malloc(octaspireContainerVectorTestAllocator, originalElementSize);

    float const factor = 2;

    ASSERT(octaspire_container_vector_private_grow(vec, factor));
    ASSERT(vec->elements);
    ASSERT_EQ(originalElementSize,           vec->elementSize);
    ASSERT_EQ(originalNumElements,           vec->numElements);

    ASSERT_EQ(
        (size_t)((float)originalNumAllocated * factor),
        vec->numAllocated);

    for (size_t i = 0; i < vec->numAllocated; ++i)
    {
        ASSERT_MEM_EQ(
            expectedInitializedMemory,
            vec->elements + (i * originalElementSize),
            originalElementSize);
    }

    ASSERT(octaspire_container_vector_private_grow(vec, factor));
    ASSERT(vec->elements);
    ASSERT_EQ(originalElementSize,                      vec->elementSize);
    ASSERT_EQ(originalNumElements,                      vec->numElements);
    ASSERT_EQ(
        (size_t)((float)originalNumAllocated * (factor * factor)),
        vec->numAllocated);

    for (size_t i = 0; i < vec->numAllocated; ++i)
    {
        ASSERT_MEM_EQ(
            expectedInitializedMemory,
            vec->elements + (i * originalElementSize),
            originalElementSize);
    }

    octaspire_container_vector_release(vec);
    vec = 0;
    octaspire_memory_allocator_free(octaspireContainerVectorTestAllocator, expectedInitializedMemory);

    PASS();
}

TEST octaspire_container_vector_private_grow_with_factor_100_success_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(char), false, 0, octaspireContainerVectorTestAllocator);

    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;
    size_t const       originalNumAllocated = vec->numAllocated;

    char *expectedInitializedMemory =
        octaspire_memory_allocator_malloc(octaspireContainerVectorTestAllocator, originalElementSize);

    float const factor = 100;

    ASSERT(octaspire_container_vector_private_grow(vec, factor));
    ASSERT(vec->elements);
    ASSERT_EQ(originalElementSize,           vec->elementSize);
    ASSERT_EQ(originalNumElements,           vec->numElements);

    ASSERT_EQ(
        (size_t)((float)originalNumAllocated * factor),
        vec->numAllocated);

    for (size_t i = 0; i < vec->numAllocated; ++i)
    {
        ASSERT_MEM_EQ(
            expectedInitializedMemory,
            vec->elements + (i * originalElementSize),
            originalElementSize);
    }

    ASSERT(octaspire_container_vector_private_grow(vec, factor));
    ASSERT(vec->elements);
    ASSERT_EQ(originalElementSize,                      vec->elementSize);
    ASSERT_EQ(originalNumElements,                      vec->numElements);

    ASSERT_EQ(
        (size_t)((float)originalNumAllocated * (factor * factor)),
        vec->numAllocated);

    for (size_t i = 0; i < vec->numAllocated; ++i)
    {
        ASSERT_MEM_EQ(
            expectedInitializedMemory,
            vec->elements + (i * originalElementSize),
            originalElementSize);
    }

    octaspire_container_vector_release(vec);
    vec = 0;
    octaspire_memory_allocator_free(octaspireContainerVectorTestAllocator, expectedInitializedMemory);

    PASS();
}

TEST octaspire_container_vector_private_grow_with_factor_2_even_when_zero_is_given_as_factor_success_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(double), false, 0, octaspireContainerVectorTestAllocator);

    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;
    size_t const       originalNumAllocated = vec->numAllocated;

    char *expectedInitializedMemory =
        octaspire_memory_allocator_malloc(octaspireContainerVectorTestAllocator, originalElementSize);

    float const badFactor = 0;
    float const factor = 2;

    ASSERT(octaspire_container_vector_private_grow(vec, badFactor));
    ASSERT(vec->elements);
    ASSERT_EQ(originalElementSize,           vec->elementSize);
    ASSERT_EQ(originalNumElements,           vec->numElements);

    ASSERT_EQ(
        (size_t)((float)originalNumAllocated * factor),
        vec->numAllocated);

    for (size_t i = 0; i < vec->numAllocated; ++i)
    {
        ASSERT_MEM_EQ(
            expectedInitializedMemory,
            vec->elements + (i * originalElementSize),
            originalElementSize);
    }

    ASSERT(octaspire_container_vector_private_grow(vec, badFactor));
    ASSERT(vec->elements);
    ASSERT_EQ(originalElementSize,                      vec->elementSize);
    ASSERT_EQ(originalNumElements,                      vec->numElements);
    ASSERT_EQ(
        (size_t)((float)originalNumAllocated * (factor * factor)),
        vec->numAllocated);

    for (size_t i = 0; i < vec->numAllocated; ++i)
    {
        ASSERT_MEM_EQ(
            expectedInitializedMemory,
            vec->elements + (i * originalElementSize),
            originalElementSize);
    }

    octaspire_container_vector_release(vec);
    vec = 0;
    octaspire_memory_allocator_free(octaspireContainerVectorTestAllocator, expectedInitializedMemory);

    PASS();
}

TEST octaspire_container_vector_private_grow_with_factor_2_even_when_one_is_given_as_factor_success_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(double), false, 0, octaspireContainerVectorTestAllocator);

    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;
    size_t const       originalNumAllocated = vec->numAllocated;

    char *expectedInitializedMemory =
        octaspire_memory_allocator_malloc(octaspireContainerVectorTestAllocator, originalElementSize);

    float const badFactor = 1;
    float const factor = 2;

    ASSERT(octaspire_container_vector_private_grow(vec, badFactor));
    ASSERT(vec->elements);
    ASSERT_EQ(originalElementSize,           vec->elementSize);
    ASSERT_EQ(originalNumElements,           vec->numElements);

    ASSERT_EQ(
        (size_t)((float)originalNumAllocated * factor),
        vec->numAllocated);

    for (size_t i = 0; i < vec->numAllocated; ++i)
    {
        ASSERT_MEM_EQ(
            expectedInitializedMemory,
            vec->elements + (i * originalElementSize),
            originalElementSize);
    }

    ASSERT(octaspire_container_vector_private_grow(vec, badFactor));
    ASSERT(vec->elements);
    ASSERT_EQ(originalElementSize,                      vec->elementSize);
    ASSERT_EQ(originalNumElements,                      vec->numElements);
    ASSERT_EQ(
        (size_t)((float)originalNumAllocated * (factor * factor)),
        vec->numAllocated);

    for (size_t i = 0; i < vec->numAllocated; ++i)
    {
        ASSERT_MEM_EQ(
            expectedInitializedMemory,
            vec->elements + (i * originalElementSize),
            originalElementSize);
    }

    octaspire_container_vector_release(vec);
    vec = 0;
    octaspire_memory_allocator_free(octaspireContainerVectorTestAllocator, expectedInitializedMemory);

    PASS();
}

TEST octaspire_container_vector_private_grow_failure_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    void const * const originalElements     = vec->elements;
    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;
    size_t const       originalNumAllocated = vec->numAllocated;

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerVectorTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerVectorTestAllocator));

    ASSERT_FALSE(octaspire_container_vector_private_grow(vec, 2));

    ASSERT_EQ(
        0,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerVectorTestAllocator));

    ASSERT_EQ(originalElements,     vec->elements);
    ASSERT_EQ(originalElementSize,  vec->elementSize);
    ASSERT_EQ(originalNumElements,  vec->numElements);
    ASSERT_EQ(originalNumAllocated, vec->numAllocated);

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_private_compact_success_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT(octaspire_container_vector_private_grow(vec, 1000));

    for (size_t i = 0; i < 250; ++i)
    {
        octaspire_container_vector_push_back_element(vec, &i);
    }

    //void              *originalElements     = vec->elements;
    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;

    ASSERT(octaspire_container_vector_private_compact(vec));

    //ASSERT_EQ(originalElements,              vec->elements);
    ASSERT_EQ(originalElementSize,           vec->elementSize);
    ASSERT_EQ(originalNumElements,           vec->numElements);
    // Compacting should have made self->numAllocated == self->numElements
    ASSERT_EQ(originalNumElements,           vec->numAllocated);

    // TODO Continue here

    for (size_t i = 0; i < vec->numElements; ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_private_compact_failure_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT(octaspire_container_vector_private_grow(vec, 1000));

    for (size_t i = 0; i < 250; ++i)
    {
        octaspire_container_vector_push_back_element(vec, &i);
    }

    void              *originalElements     = vec->elements;
    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;
    size_t const       originalNumAllocated = vec->numAllocated;

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator, 1, 0);

    ASSERT_FALSE(octaspire_container_vector_private_compact(vec));

    ASSERT_EQ(0, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    ASSERT_EQ(originalElements,     vec->elements);
    ASSERT_EQ(originalElementSize,  vec->elementSize);
    ASSERT_EQ(originalNumElements,  vec->numElements);
    ASSERT_EQ(originalNumAllocated, vec->numAllocated);

    for (size_t i = 0; i < vec->numElements; ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_new_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT(vec);

    ASSERT(vec->elements);
    ASSERT_EQ(sizeof(size_t),                          vec->elementSize);
    ASSERT_EQ(0,                                       vec->numElements);
    ASSERT_EQ(OCTASPIRE_CONTAINER_VECTOR_INITIAL_SIZE, vec->numAllocated);
    ASSERT_EQ(0,                                       vec->elementReleaseCallback);
    ASSERT_EQ(octaspireContainerVectorTestAllocator,                               vec->allocator);

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_new_failure_test(void)
{
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator, 1, 0);

    ASSERT_EQ(1, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_FALSE(vec);

    ASSERT_EQ(0, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_new_with_preallocated_elements_test(void)
{
    size_t const numPreAllocated = 100;

    octaspire_container_vector_t *vec = octaspire_container_vector_new_with_preallocated_elements(
        sizeof(size_t),
        false,
        numPreAllocated,
        0,
        octaspireContainerVectorTestAllocator);

    ASSERT(vec);

    ASSERT(vec->elements);
    ASSERT_EQ(sizeof(size_t),       vec->elementSize);
    ASSERT_EQ(0,                    vec->numElements);
    ASSERT_EQ(numPreAllocated,      vec->numAllocated);
    ASSERT_EQ(0,                    vec->elementReleaseCallback);
    ASSERT_EQ(octaspireContainerVectorTestAllocator,            vec->allocator);

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_new_with_preallocated_elements_allocation_failure_on_first_allocation_test(void)
{
    size_t const numPreAllocated = 100;

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    octaspire_container_vector_t *vec = octaspire_container_vector_new_with_preallocated_elements(
        sizeof(size_t),
        false,
        numPreAllocated,
        0,
        octaspireContainerVectorTestAllocator);

    ASSERT_EQ(0, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    ASSERT_FALSE(vec);

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_new_with_preallocated_elements_allocation_failure_on_second_allocation_test(void)
{
    size_t const numPreAllocated = 100;

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator, 2, 0x01);
    ASSERT_EQ(2, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    octaspire_container_vector_t *vec = octaspire_container_vector_new_with_preallocated_elements(
        sizeof(size_t),
        false,
        numPreAllocated,
        0,
        octaspireContainerVectorTestAllocator);

    ASSERT_EQ(0, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    ASSERT_FALSE(vec);

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}



// TODO XXX test octaspire_container_vector_new_with_preallocated_elements
// It has newer allocation failure test that must also be tested




TEST octaspire_container_vector_new_shallow_copy_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT(vec);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_push_back_element(vec, &i));
    }

    ASSERT_EQ(
        len,
        octaspire_container_vector_get_length(vec));

    octaspire_container_vector_t *cpy=
        octaspire_container_vector_new_shallow_copy(vec, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(
        octaspire_container_vector_get_length(vec),
        octaspire_container_vector_get_length(cpy));

    for (size_t i = 0; i < octaspire_container_vector_get_length(cpy); ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(cpy, i));
    }

    ASSERT_EQ(vec->elementSize, cpy->elementSize);
    ASSERT_EQ(vec->numElements, cpy->numElements);

    // Copy is compact
    ASSERT_EQ(cpy->numElements, cpy->numAllocated);
    ASSERT_MEM_EQ(vec->elements, cpy->elements, cpy->numElements);
    ASSERT_EQ(vec->elementReleaseCallback, cpy->elementReleaseCallback);
    ASSERT_EQ(vec->allocator, cpy->allocator);

    octaspire_container_vector_release(vec);
    vec = 0;

    octaspire_container_vector_release(cpy);
    cpy = 0;

    PASS();
}

TEST octaspire_container_vector_new_shallow_copy_allocation_failure_on_first_allocation_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT(vec);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_push_back_element(vec, &i));
    }

    ASSERT_EQ(
        len,
        octaspire_container_vector_get_length(vec));

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    ASSERT_FALSE(octaspire_container_vector_new_shallow_copy(vec, octaspireContainerVectorTestAllocator));

    ASSERT_EQ(0, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_new_shallow_copy_allocation_failure_on_second_allocation_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT(vec);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_push_back_element(vec, &i));
    }

    ASSERT_EQ(
        len,
        octaspire_container_vector_get_length(vec));

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator, 2, 0x01);
    ASSERT_EQ(2, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    ASSERT_FALSE(octaspire_container_vector_new_shallow_copy(vec, octaspireContainerVectorTestAllocator));

    ASSERT_EQ(0, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_release_null_test(void)
{
    octaspire_container_vector_release(0);
    PASS();
}

void octaspire_container_vector_test_element_callback1(void *element);
void octaspire_container_vector_test_element_callback3_shrink_vector(void *element);
void octaspire_container_vector_test_element_callback2_grow_vector(void *element);

static size_t octaspireContainerVectorTestElementCallback1TimesCalled = 0;

void octaspire_container_vector_test_element_callback1(void *element)
{
    OCTASPIRE_HELPERS_UNUSED_PARAMETER(element);
    ++octaspireContainerVectorTestElementCallback1TimesCalled;
}

void octaspire_container_vector_test_element_callback2_grow_vector(void *element)
{
    octaspire_container_vector_t *vec = element;

    ++octaspireContainerVectorTestElementCallback1TimesCalled;

    if (octaspireContainerVectorTestElementCallback1TimesCalled < 100)
    {
        octaspire_container_vector_push_back_element(vec, &vec);
    }
}

void octaspire_container_vector_test_element_callback3_shrink_vector(void *element)
{
    octaspire_container_vector_t *vec = element;

    ++octaspireContainerVectorTestElementCallback1TimesCalled;

    if (!octaspire_container_vector_is_empty(vec))
    {
        octaspire_container_vector_pop_back_element(vec);
    }
}

TEST octaspire_container_vector_release_element_callback_called_for_all_elements_test(void)
{
    octaspireContainerVectorTestElementCallback1TimesCalled = 0;

    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, octaspire_container_vector_test_element_callback1, octaspireContainerVectorTestAllocator);

    ASSERT(vec);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_push_back_element(vec, &i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    ASSERT_EQ(len, octaspireContainerVectorTestElementCallback1TimesCalled);

    PASS();
}

TEST octaspire_container_vector_get_length_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(i, octaspire_container_vector_get_length(vec));
        octaspire_container_vector_push_back_element(vec, &i);
        ASSERT_EQ(i + 1, octaspire_container_vector_get_length(vec));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_is_empty_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT(octaspire_container_vector_is_empty(vec));
    }

    for (size_t i = 0; i < 100; ++i)
    {
        octaspire_container_vector_push_back_element(vec, &i);
        ASSERT_FALSE(octaspire_container_vector_is_empty(vec));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_remove_element_at_index_0_of_100_elements_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_container_vector_push_back_element(vec, &i);
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    ASSERT(octaspire_container_vector_remove_element_at(vec, 0));

    for (size_t i = 0; i < len - 1; ++i)
    {
            ASSERT_EQ(i + 1, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_remove_element_at_index_50_of_100_elements_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_container_vector_push_back_element(vec, &i);
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    ASSERT(octaspire_container_vector_remove_element_at(vec, 50));

    for (size_t i = 0; i < len - 1; ++i)
    {
        if (i < 50)
        {
            ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
        }
        else
        {
            ASSERT_EQ(i + 1, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
        }
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_remove_element_at_index_99_of_100_elements_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_container_vector_push_back_element(vec, &i);
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    ASSERT(octaspire_container_vector_remove_element_at(vec, 99));

    for (size_t i = 0; i < len - 1; ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_remove_element_at_failure_removing_index_100_of_100_elements_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_container_vector_push_back_element(vec, &i);
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    ASSERT_FALSE(octaspire_container_vector_remove_element_at(vec, 100));

    ASSERT_EQ(len, octaspire_container_vector_get_length(vec));

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_remove_element_at_failure_removing_indices_100_to_200_of_100_elements_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_container_vector_push_back_element(vec, &i);
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    for (size_t i = 100; i < 201; ++i)
    {
        ASSERT_FALSE(octaspire_container_vector_remove_element_at(vec, i));
    }

    ASSERT_EQ(len, octaspire_container_vector_get_length(vec));

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_remove_element_at_remove_all_100_elements_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_container_vector_push_back_element(vec, &i);
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_remove_element_at(vec, 0));

        ASSERT_EQ(len - (i + 1), octaspire_container_vector_get_length(vec));

        for (size_t j = 0; j < octaspire_container_vector_get_length(vec); ++j)
        {
            ASSERT_EQ(j + i + 1, *(size_t*)octaspire_container_vector_get_element_at(vec, j));
        }
    }

    ASSERT_EQ(0, octaspire_container_vector_get_length(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_get_element_at_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_FALSE((size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_FALSE((size_t*)octaspire_container_vector_get_element_at(vec, i));
        octaspire_container_vector_push_back_element(vec, &i);
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    ASSERT_FALSE((size_t*)octaspire_container_vector_get_element_at(vec, len + 1));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_get_element_at_const_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_FALSE((size_t const *)octaspire_container_vector_get_element_at_const(vec, i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_FALSE((size_t const *)octaspire_container_vector_get_element_at_const(vec, i));
        octaspire_container_vector_push_back_element(vec, &i);
        ASSERT_EQ(i, *(size_t const *)octaspire_container_vector_get_element_at_const(vec, i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(i, *(size_t const *)octaspire_container_vector_get_element_at_const(vec, i));
    }

    ASSERT_FALSE((size_t const *)octaspire_container_vector_get_element_at_const(vec, len + 1));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_get_element_size_in_octets_when_element_is_of_type_uint8_t_test(void)
{
    size_t const expectedSize = sizeof(uint8_t);

    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(expectedSize, false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(expectedSize, octaspire_container_vector_get_element_size_in_octets(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_get_element_size_in_octets_when_element_is_of_type_int_test(void)
{
    size_t const expectedSize = sizeof(int);

    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(expectedSize, false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(expectedSize, octaspire_container_vector_get_element_size_in_octets(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_get_element_size_in_octets_when_element_is_of_type_size_t_test(void)
{
    size_t const expectedSize = sizeof(size_t);

    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(expectedSize, false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(expectedSize, octaspire_container_vector_get_element_size_in_octets(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_get_element_size_in_octets_when_element_is_of_type_double_test(void)
{
    size_t const expectedSize = sizeof(double);

    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(expectedSize, false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(expectedSize, octaspire_container_vector_get_element_size_in_octets(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_get_element_size_in_octets_when_element_is_of_type_void_ptr_test(void)
{
    size_t const expectedSize = sizeof(void*);

    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(expectedSize, true, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(expectedSize, octaspire_container_vector_get_element_size_in_octets(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_get_element_size_in_octets_when_element_size_is_10000_test(void)
{
    size_t const expectedSize = 10000;

    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(expectedSize, false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(expectedSize, octaspire_container_vector_get_element_size_in_octets(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_get_element_size_in_octets_when_element_size_is_illegal_zero_test(void)
{
    size_t const expectedSize = sizeof(char);

    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(0, false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(expectedSize, octaspire_container_vector_get_element_size_in_octets(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_insert_element_before_the_element_at_index_minus_one_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t value = 2;

    octaspire_container_vector_push_front_element(vec, &value);

    value = 1;

    ASSERT(octaspire_container_vector_insert_element_before_the_element_at_index(vec, &value, -1));

    ASSERT_EQ(2,  octaspire_container_vector_get_length(vec));
    ASSERT_EQ(1, *(size_t*)octaspire_container_vector_get_element_at(vec, 0));
    ASSERT_EQ(2, *(size_t*)octaspire_container_vector_get_element_at(vec, 1));

    value = 9;

    ASSERT(octaspire_container_vector_insert_element_before_the_element_at_index(vec, &value, -1));

    ASSERT_EQ(3,  octaspire_container_vector_get_length(vec));
    ASSERT_EQ(1, *(size_t*)octaspire_container_vector_get_element_at(vec, 0));
    ASSERT_EQ(9, *(size_t*)octaspire_container_vector_get_element_at(vec, 1));
    ASSERT_EQ(2, *(size_t*)octaspire_container_vector_get_element_at(vec, 2));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_insert_element_before_the_element_at_index_zero_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    octaspire_container_vector_push_front_element(vec, &len);

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_insert_element_before_the_element_at_index(vec, &i, 0));
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, 0));
    }

    ASSERT_EQ(len + 1, octaspire_container_vector_get_length(vec));
    ASSERT_EQ(len, *(size_t*)octaspire_container_vector_peek_back_element(vec));

    for (size_t i = 0; i < octaspire_container_vector_get_length(vec) - 1; ++i)
    {
        ASSERT_EQ(len - (i + 1), *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_insert_element_before_the_element_at_index_called_on_empty_vector_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(
            octaspire_container_vector_insert_element_before_the_element_at_index(vec, &i, 0));
    }

    ASSERT(octaspire_container_vector_is_empty(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_insert_element_before_the_element_at_index_the_end_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    octaspire_container_vector_push_front_element(vec, &len);

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(
            octaspire_container_vector_insert_element_before_the_element_at_index(
                vec,
                &i,
                (ptrdiff_t)octaspire_container_vector_get_length(vec) - 1));

        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    ASSERT_EQ(len + 1, octaspire_container_vector_get_length(vec));
    ASSERT_EQ(len, *(size_t*)octaspire_container_vector_peek_back_element(vec));

    for (size_t i = 0; i < octaspire_container_vector_get_length(vec); ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_insert_element_before_the_element_at_index_past_the_end_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const value = 100;

    octaspire_container_vector_push_front_element(vec, &value);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(
            octaspire_container_vector_insert_element_before_the_element_at_index(
                vec,
                &i,
                10));

        ASSERT_EQ(1, octaspire_container_vector_get_length(vec));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_insert_element_before_the_element_at_index_allocation_failure_test(void)
{
    size_t const value = 123;

    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT(octaspire_container_vector_push_front_element(vec, &value));

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerVectorTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerVectorTestAllocator));

    ASSERT_FALSE(
        octaspire_container_vector_insert_element_before_the_element_at_index(
            vec,
            &value,
            0));

    ASSERT_EQ(
        0,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerVectorTestAllocator));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_insert_element_before_the_element_at_index_the_middle_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_push_back_element(vec, &i));
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_peek_back_element(vec));
    }

    ASSERT_EQ(len, octaspire_container_vector_get_length(vec));

    ASSERT(octaspire_container_vector_insert_element_before_the_element_at_index(vec, &len, 50));

    ASSERT_EQ(len + 1, octaspire_container_vector_get_length(vec));

    for (size_t i = 0; i < octaspire_container_vector_get_length(vec); ++i)
    {
        if (i < 50)
        {
            ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
        }
        else if (i == 50)
        {
            ASSERT_EQ(100, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
        }
        else
        {
            ASSERT_EQ(i - 1, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
        }
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_insert_element_at_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_container_vector_push_back_element(vec, &i);
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    size_t a = 900;
    size_t b = 901;
    size_t c = 902;

    ASSERT(octaspire_container_vector_insert_element_at(vec, &a, 0));
    ASSERT_EQ(a, *(size_t*)octaspire_container_vector_get_element_at(vec, 0));
    for (size_t i = 1; i < len; ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    ASSERT(octaspire_container_vector_insert_element_at(vec, &b, 50));
    ASSERT_EQ(b, *(size_t*)octaspire_container_vector_get_element_at(vec, 50));
    ASSERT_EQ(a, *(size_t*)octaspire_container_vector_get_element_at(vec, 0));
    for (size_t i = 1; i < len; ++i)
    {
        if (i != 50)
        {
            ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
        }
    }

    ASSERT(octaspire_container_vector_insert_element_at(vec, &c, 102));
    ASSERT_EQ(a, *(size_t*)octaspire_container_vector_get_element_at(vec, 0));
    ASSERT_EQ(b, *(size_t*)octaspire_container_vector_get_element_at(vec, 50));
    for (size_t i = 1; i < len; ++i)
    {
        if (i != 50)
        {
            ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
        }
    }
    ASSERT_EQ(c, *(size_t*)octaspire_container_vector_get_element_at(vec, 102));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_insert_element_at_index_100_of_empty_vector_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t a = 900;
    size_t const index = 100;
    ASSERT(octaspire_container_vector_insert_element_at(vec, &a, index));

    ASSERT_EQ(index + 1, octaspire_container_vector_get_length(vec));

    for (size_t i = 0; i < (index - 1); ++i)
    {
        ASSERT_EQ(0, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    ASSERT_EQ(a, *(size_t*)octaspire_container_vector_get_element_at(vec, index));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_insert_element_at_failure_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const element = 0;

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerVectorTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerVectorTestAllocator));

    ASSERT_FALSE(octaspire_container_vector_insert_element_at(vec, &element, 4));

    ASSERT_EQ(
        0,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerVectorTestAllocator));

    ASSERT_EQ(0, octaspire_container_vector_get_length(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_push_front_element_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_push_front_element(vec, &i));
        ASSERT_EQ(i + 1, octaspire_container_vector_get_length(vec));
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, 0));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(len - (i + 1), *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_push_back_element_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_push_back_element(vec, &i));
        ASSERT_EQ(i + 1, octaspire_container_vector_get_length(vec));
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_get_element_at(vec, i));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_push_back_char_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(char), false, 0, octaspireContainerVectorTestAllocator);

    char const len = 127;

    for (char i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_push_back_char(vec, i));
        ASSERT_EQ((size_t)i + 1, octaspire_container_vector_get_length(vec));
        ASSERT_EQ((char)i, *(char*)octaspire_container_vector_get_element_at(vec, (size_t)i));
    }

    for (char i = 0; i < len; ++i)
    {
        ASSERT_EQ((char)i, *(char*)octaspire_container_vector_get_element_at(vec, (size_t)i));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_push_back_char_to_vector_containing_floats_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(float), false, 0, octaspireContainerVectorTestAllocator);

    char const len = 127;

    for (char i = 0; i < len; ++i)
    {
        ASSERT_FALSE(octaspire_container_vector_push_back_char(vec, i));
        ASSERT_EQ(0, octaspire_container_vector_get_length(vec));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_for_each_called_on_empty_vector_test(void)
{
    octaspireContainerVectorTestElementCallback1TimesCalled = 0;

    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    octaspire_container_vector_for_each(vec, octaspire_container_vector_test_element_callback1);

    ASSERT_EQ(0, octaspireContainerVectorTestElementCallback1TimesCalled);

    octaspireContainerVectorTestElementCallback1TimesCalled = 0;
    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_for_each_called_on_vector_with_one_element_test(void)
{
    octaspireContainerVectorTestElementCallback1TimesCalled = 0;

    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const element = 999;

    octaspire_container_vector_push_back_element(vec, &element);

    octaspire_container_vector_for_each(vec, octaspire_container_vector_test_element_callback1);

    ASSERT_EQ(1, octaspireContainerVectorTestElementCallback1TimesCalled);

    octaspireContainerVectorTestElementCallback1TimesCalled = 0;
    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_for_each_called_on_vector_with_hundred_elements_test(void)
{
    octaspireContainerVectorTestElementCallback1TimesCalled = 0;

    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        octaspire_container_vector_push_back_element(vec, &i);
    }

    octaspire_container_vector_for_each(vec, octaspire_container_vector_test_element_callback1);

    ASSERT_EQ(100, octaspireContainerVectorTestElementCallback1TimesCalled);

    octaspireContainerVectorTestElementCallback1TimesCalled = 0;
    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_for_each_called_on_vector_that_grows_during_iteration_test(void)
{
    octaspireContainerVectorTestElementCallback1TimesCalled = 0;

    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(octaspire_container_vector_t*), true, 0, octaspireContainerVectorTestAllocator);

    octaspire_container_vector_push_back_element(vec, &vec);

    octaspire_container_vector_for_each(vec, octaspire_container_vector_test_element_callback2_grow_vector);

    ASSERT_EQ(100, octaspireContainerVectorTestElementCallback1TimesCalled);

    octaspireContainerVectorTestElementCallback1TimesCalled = 0;
    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_for_each_called_on_vector_that_shrinks_during_iteration_test(void)
{
    octaspireContainerVectorTestElementCallback1TimesCalled = 0;

    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(octaspire_container_vector_t*), true, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        octaspire_container_vector_push_back_element(vec, &vec);
    }

    octaspire_container_vector_for_each(
        vec,
        octaspire_container_vector_test_element_callback3_shrink_vector);

    ASSERT_EQ(50, octaspireContainerVectorTestElementCallback1TimesCalled);

    octaspireContainerVectorTestElementCallback1TimesCalled = 0;
    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_pop_back_element_called_on_empty_vector_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(octaspire_container_vector_pop_back_element(vec));
    }

    ASSERT_EQ(0, octaspire_container_vector_get_length(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_pop_back_element_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_push_back_element(vec, &i));
    }

    ASSERT_EQ(len, octaspire_container_vector_get_length(vec));

    for (size_t i = len; i != 0; --i)
    {
        ASSERT_EQ(i-1, *(size_t*)octaspire_container_vector_peek_back_element(vec));
        ASSERT(octaspire_container_vector_pop_back_element(vec));
        ASSERT_EQ(i-1, octaspire_container_vector_get_length(vec));

        if (i > 1)
        {
            ASSERT_FALSE(octaspire_container_vector_is_empty(vec));
            ASSERT_EQ(i - 2, *(size_t*)octaspire_container_vector_peek_back_element(vec));
        }
    }

    ASSERT_EQ(0, octaspire_container_vector_get_length(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}



















TEST octaspire_container_vector_peek_back_element_called_on_empty_vector_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(octaspire_container_vector_peek_back_element(vec));
    }

    ASSERT_EQ(0, octaspire_container_vector_get_length(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_peek_back_element_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_push_back_element(vec, &i));
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_peek_back_element(vec));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_peek_back_element_const_called_on_empty_vector_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(octaspire_container_vector_peek_back_element_const(vec));
    }

    ASSERT_EQ(0, octaspire_container_vector_get_length(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_peek_back_element_const_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_push_back_element(vec, &i));
        ASSERT_EQ(i, *(size_t const *)octaspire_container_vector_peek_back_element_const(vec));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_pop_front_element_called_on_empty_vector_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    void const * const originalElements     = vec->elements;
    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;
    size_t const       originalNumAllocated = vec->numAllocated;

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_FALSE(octaspire_container_vector_pop_front_element(vec));
    }

    ASSERT_EQ(originalElements,     vec->elements);
    ASSERT_EQ(originalElementSize,  vec->elementSize);
    ASSERT_EQ(originalNumElements,  vec->numElements);
    ASSERT_EQ(originalNumAllocated, vec->numAllocated);

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_pop_front_element_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_push_back_element(vec, &i));
        ASSERT_EQ(i, *(size_t const *)octaspire_container_vector_peek_back_element_const(vec));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_pop_front_element(vec));
        ASSERT_EQ(len - 1 - i, octaspire_container_vector_get_length(vec));

        if (!octaspire_container_vector_is_empty(vec))
        {
            ASSERT_EQ(i + 1, *(size_t const *)octaspire_container_vector_peek_front_element_const(vec));
        }
        else
        {
            ASSERT_EQ(len - 1, i);
        }
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_peek_front_element_called_on_empty_vector_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(octaspire_container_vector_peek_front_element(vec));
    }

    ASSERT_EQ(0, octaspire_container_vector_get_length(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_peek_front_element_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_push_front_element(vec, &i));
        ASSERT_EQ(i, *(size_t*)octaspire_container_vector_peek_front_element(vec));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_peek_front_element_const_called_on_empty_vector_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(octaspire_container_vector_peek_front_element_const(vec));
    }

    ASSERT_EQ(0, octaspire_container_vector_get_length(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_peek_front_element_const_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_push_front_element(vec, &i));
        ASSERT_EQ(i, *(size_t const *)octaspire_container_vector_peek_front_element_const(vec));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_get_element_release_callback_const_when_it_is_null_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(0, octaspire_container_vector_get_element_release_callback_const(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_get_element_release_callback_const_test(void)
{
    octaspire_container_vector_element_callback_t const expected =
        (octaspire_container_vector_element_callback_t)octaspire_container_vector_release;

    octaspire_container_vector_t *vec = octaspire_container_vector_new(
        sizeof(octaspire_container_vector_t*),
        true,
        expected,
        octaspireContainerVectorTestAllocator);

    ASSERT_EQ(
        expected,
        octaspire_container_vector_get_element_release_callback_const(vec));

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_clear_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_container_vector_push_front_element(vec, &i));
        ASSERT_EQ(i, *(size_t const *)octaspire_container_vector_peek_front_element_const(vec));
    }

    ASSERT_EQ(len, octaspire_container_vector_get_length(vec));

    ASSERT(octaspire_container_vector_clear(vec));

    ASSERT_EQ(0, octaspire_container_vector_get_length(vec));

    ASSERT_EQ(0, vec->numElements);
    ASSERT_EQ(1, vec->numAllocated);

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_vector_clear_called_on_empty_vector_test(void)
{
    octaspire_container_vector_t *vec =
        octaspire_container_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(0, octaspire_container_vector_get_length(vec));

    ASSERT_FALSE(octaspire_container_vector_clear(vec));

    ASSERT_EQ(0, octaspire_container_vector_get_length(vec));

    ASSERT_EQ(0, vec->numElements);
    ASSERT_EQ(1, vec->numAllocated);

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

static size_t octaspireContainerVectorSuiteNumTimesRun = 0;

GREATEST_SUITE(octaspire_container_vector_suite)
{
    octaspireContainerVectorSuiteNumTimesRun = 0;

    octaspireContainerVectorTestAllocator = octaspire_memory_allocator_new_create_region(
        OCTASPIRE_CORE_CONFIG_MEMORY_ALLOCATOR_REGION_MIN_BLOCK_SIZE_IN_OCTETS);

second_run:

    assert(octaspireContainerVectorTestAllocator);

    RUN_TEST(octaspire_container_vector_private_index_to_pointer_test);
    RUN_TEST(octaspire_container_vector_private_index_to_pointer_const_test);
    RUN_TEST(octaspire_container_vector_private_grow_with_factor_2_success_test);
    RUN_TEST(octaspire_container_vector_private_grow_with_factor_100_success_test);
    RUN_TEST(octaspire_container_vector_private_grow_with_factor_2_even_when_zero_is_given_as_factor_success_test);
    RUN_TEST(octaspire_container_vector_private_grow_with_factor_2_even_when_one_is_given_as_factor_success_test);
    RUN_TEST(octaspire_container_vector_private_grow_failure_test);
    RUN_TEST(octaspire_container_vector_private_compact_success_test);
    RUN_TEST(octaspire_container_vector_private_compact_failure_test);
    RUN_TEST(octaspire_container_vector_new_test);
    RUN_TEST(octaspire_container_vector_new_failure_test);
    RUN_TEST(octaspire_container_vector_new_with_preallocated_elements_test);
    RUN_TEST(octaspire_container_vector_new_with_preallocated_elements_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_container_vector_new_with_preallocated_elements_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_container_vector_new_shallow_copy_test);
    RUN_TEST(octaspire_container_vector_new_shallow_copy_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_container_vector_new_shallow_copy_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_container_vector_release_null_test);
    RUN_TEST(octaspire_container_vector_release_element_callback_called_for_all_elements_test);
    RUN_TEST(octaspire_container_vector_get_length_test);
    RUN_TEST(octaspire_container_vector_is_empty_test);
    RUN_TEST(octaspire_container_vector_remove_element_at_index_0_of_100_elements_test);
    RUN_TEST(octaspire_container_vector_remove_element_at_index_50_of_100_elements_test);
    RUN_TEST(octaspire_container_vector_remove_element_at_index_99_of_100_elements_test);
    RUN_TEST(octaspire_container_vector_remove_element_at_failure_removing_index_100_of_100_elements_test);
    RUN_TEST(octaspire_container_vector_remove_element_at_failure_removing_indices_100_to_200_of_100_elements_test);
    RUN_TEST(octaspire_container_vector_remove_element_at_remove_all_100_elements_test);
    RUN_TEST(octaspire_container_vector_get_element_at_test);
    RUN_TEST(octaspire_container_vector_get_element_at_const_test);
    RUN_TEST(octaspire_container_vector_get_element_size_in_octets_when_element_is_of_type_uint8_t_test);
    RUN_TEST(octaspire_container_vector_get_element_size_in_octets_when_element_is_of_type_int_test);
    RUN_TEST(octaspire_container_vector_get_element_size_in_octets_when_element_is_of_type_size_t_test);
    RUN_TEST(octaspire_container_vector_get_element_size_in_octets_when_element_is_of_type_double_test);
    RUN_TEST(octaspire_container_vector_get_element_size_in_octets_when_element_is_of_type_void_ptr_test);
    RUN_TEST(octaspire_container_vector_get_element_size_in_octets_when_element_size_is_10000_test);
    RUN_TEST(octaspire_container_vector_get_element_size_in_octets_when_element_size_is_illegal_zero_test);
    RUN_TEST(octaspire_container_vector_insert_element_before_the_element_at_index_minus_one_test);
    RUN_TEST(octaspire_container_vector_insert_element_before_the_element_at_index_zero_test);
    RUN_TEST(octaspire_container_vector_insert_element_before_the_element_at_index_called_on_empty_vector_test);
    RUN_TEST(octaspire_container_vector_insert_element_before_the_element_at_index_the_end_test);
    RUN_TEST(octaspire_container_vector_insert_element_before_the_element_at_index_past_the_end_test);
    RUN_TEST(octaspire_container_vector_insert_element_before_the_element_at_index_allocation_failure_test);
    RUN_TEST(octaspire_container_vector_insert_element_before_the_element_at_index_the_middle_test);
    RUN_TEST(octaspire_container_vector_insert_element_at_test);
    RUN_TEST(octaspire_container_vector_insert_element_at_index_100_of_empty_vector_test);
    RUN_TEST(octaspire_container_vector_insert_element_at_failure_test);
    RUN_TEST(octaspire_container_vector_push_front_element_test);
    RUN_TEST(octaspire_container_vector_push_back_element_test);
    RUN_TEST(octaspire_container_vector_push_back_char_test);
    RUN_TEST(octaspire_container_vector_push_back_char_to_vector_containing_floats_test);
    RUN_TEST(octaspire_container_vector_for_each_called_on_empty_vector_test);
    RUN_TEST(octaspire_container_vector_for_each_called_on_vector_with_one_element_test);
    RUN_TEST(octaspire_container_vector_for_each_called_on_vector_with_hundred_elements_test);
    RUN_TEST(octaspire_container_vector_for_each_called_on_vector_that_grows_during_iteration_test);
    RUN_TEST(octaspire_container_vector_for_each_called_on_vector_that_shrinks_during_iteration_test);
    RUN_TEST(octaspire_container_vector_pop_back_element_called_on_empty_vector_test);
    RUN_TEST(octaspire_container_vector_pop_back_element_test);
    RUN_TEST(octaspire_container_vector_peek_back_element_called_on_empty_vector_test);
    RUN_TEST(octaspire_container_vector_peek_back_element_test);
    RUN_TEST(octaspire_container_vector_peek_back_element_const_called_on_empty_vector_test);
    RUN_TEST(octaspire_container_vector_peek_back_element_const_test);
    RUN_TEST(octaspire_container_vector_pop_front_element_called_on_empty_vector_test);
    RUN_TEST(octaspire_container_vector_pop_front_element_test);
    RUN_TEST(octaspire_container_vector_peek_front_element_called_on_empty_vector_test);
    RUN_TEST(octaspire_container_vector_peek_front_element_test);
    RUN_TEST(octaspire_container_vector_peek_front_element_const_called_on_empty_vector_test);
    RUN_TEST(octaspire_container_vector_peek_front_element_const_test);
    RUN_TEST(octaspire_container_vector_get_element_release_callback_const_when_it_is_null_test);
    RUN_TEST(octaspire_container_vector_get_element_release_callback_const_test);
    RUN_TEST(octaspire_container_vector_clear_test);
    RUN_TEST(octaspire_container_vector_clear_called_on_empty_vector_test);

    octaspire_memory_allocator_release(octaspireContainerVectorTestAllocator);
    octaspireContainerVectorTestAllocator = 0;

    ++octaspireContainerVectorSuiteNumTimesRun;

    if (octaspireContainerVectorSuiteNumTimesRun < 2)
    {
        // Second run without region allocator

        octaspireContainerVectorTestAllocator = octaspire_memory_allocator_new(0);

        goto second_run;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../test/test_container_vector.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../test/test_container_utf8_string.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

static octaspire_memory_allocator_t *octaspireContainerUtf8StringTestAllocator = 0;

TEST octaspire_container_utf8_string_new_called_with_null_argument_test(void)
{
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(0, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("", octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_with_simple_ascii_string_test(void)
{
    char const * const expected = "Hello World!";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(expected, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(strlen((char const * const)expected), octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(strlen((char const * const)expected), octaspire_container_utf8_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ(expected, octaspire_container_utf8_string_get_c_string(str));

    for (size_t i = 0; i < octaspire_container_utf8_string_get_length_in_ucs_characters(str); ++i)
    {
        ASSERT_EQ((uint32_t)(expected[i]), octaspire_container_utf8_string_get_ucs_character_at_index(str, i));
    }

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_with_some_multioctet_ucs_characters_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_with_simple_ascii_string_with_error_test(void)
{
    char const * const input    = "Hello World\xC0\xB3";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_DECODING_ERROR, str->errorStatus);
    ASSERT_EQ(11,                                                          str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                                   str->allocator);

    ASSERT(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(11, octaspire_container_utf8_string_get_error_position_in_octets(str));

    char const * const expected = "Hello World";

    ASSERT_EQ(strlen((char const * const)expected), octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(strlen((char const * const)expected), octaspire_container_utf8_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ(expected, octaspire_container_utf8_string_get_c_string(str));

    for (size_t i = 0; i < octaspire_container_utf8_string_get_length_in_ucs_characters(str); ++i)
    {
        ASSERT_EQ((uint32_t)(expected[i]), octaspire_container_utf8_string_get_ucs_character_at_index(str, i));
    }

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_from_buffer_with_some_multioctet_ucs_characters_test(void)
{
    char const * const input               = "©Hello World! © ≠𐀀How are you?";
    size_t const       lengthInOctets      = strlen(input);
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_from_buffer_allocation_failure_on_first_allocation_test(void)
{
    char const * const input               = "©Hello World! © ≠𐀀How are you?";
    size_t const       lengthInOctets      = strlen(input);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    ASSERT_FALSE(str);

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_from_buffer_allocation_failure_on_second_allocation_test(void)
{
    char const * const input               = "©Hello World! © ≠𐀀How are you?";
    size_t const       lengthInOctets      = strlen(input);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 2, 0x01);
    ASSERT_EQ(2, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    ASSERT_FALSE(str);

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_from_buffer_allocation_failure_on_third_allocation_test(void)
{
    char const * const input               = "©Hello World! © ≠𐀀How are you?";
    size_t const       lengthInOctets      = strlen(input);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 3, 0x03);
    ASSERT_EQ(3, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    ASSERT_FALSE(str);

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_from_buffer_allocation_failure_on_fourth_allocation_test(void)
{
    char const * const input               = "©Hello World! © ≠𐀀How are you?";
    size_t const       lengthInOctets      = strlen(input);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 4, 0x07);
    ASSERT_EQ(4, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    ASSERT_FALSE(str);

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_from_buffer_allocation_failure_on_sixth_1_allocation_test(void)
{
    char const * const input               = "𐀀𐀀𐀀";
    size_t const       lengthInOctets      = strlen(input);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 6, 0x1F);
    ASSERT_EQ(6, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    ASSERT_FALSE(str);

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_from_buffer_allocation_failure_on_sixth_2_allocation_test(void)
{
    char const * const input               = "©Hello World! © ≠𐀀How are you?";
    size_t const       lengthInOctets      = strlen(input);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 6, 0x1F);
    ASSERT_EQ(6, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    ASSERT_FALSE(str);

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_format_with_string_test(void)
{
    char const * const name  = "Mike";
    char const * const input = "Hello! My name is %s. What's yours?";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_format(octaspireContainerUtf8StringTestAllocator, input, name);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(37, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "Hello! My name is Mike. What's yours?";

    ASSERT_STR_EQ(
        expected,
        octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_format_with_size_t_test(void)
{
    size_t const value = 62039;
    char const * const input = "©Hello World! © ≠𐀀How are you? My age is %zu. What's yours?";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_format(octaspireContainerUtf8StringTestAllocator, input, value);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(68, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(61, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you? My age is 62039. What's yours?";

    ASSERT_STR_EQ(
        expected,
        octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_format_with_doubles_test(void)
{
    double const value1 = 12.001;
    double const value2 = 2015.12;
    double const value3 = 4.9;
    char const * const input = "The doubles are %g, %g and %g\n";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_format(octaspireContainerUtf8StringTestAllocator, input, value1, value2, value3);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(40, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(40, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    char const * const expected = "The doubles are 12.001, 2015.12 and 4.9\n";

    ASSERT_STR_EQ(
        expected,
        octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_format_with_string_and_size_t_test(void)
{
    size_t const value = 62039;
    char const * const name  = "©Hello";
    char const * const input = "©Hello World! © ≠𐀀How are you? My name is \"%s\" and my age is %zu. What's yours?";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_format(octaspireContainerUtf8StringTestAllocator, input, name, value);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(93, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(85, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you? My name is \"\xC2\xA9Hello\" and my age is 62039. What's yours?";

    ASSERT_MEM_EQ(
        expected,
        octaspire_container_utf8_string_get_c_string(str),
        octaspire_container_utf8_string_get_length_in_octets(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_format_with_string_and_size_t_on_otherwise_empty_format_string_test(void)
{
    size_t const value = 62039;
    char const * const name  = "Hello";
    char const * const input = "%s%zu";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_format(octaspireContainerUtf8StringTestAllocator, input, name, value);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(10, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(10, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "Hello62039";

    ASSERT_STR_EQ(
        expected,
        octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_format_with_empty_format_string_test(void)
{
    char const * const input = "";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_format(octaspireContainerUtf8StringTestAllocator, input);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

#if 0
// This test causes valgrind errors on thinkpad. Not on raspberry 2.
TEST octaspire_container_utf8_string_new_format_encoding_error_test(void)
{
    // The idea for the line below (use of WEOF and %lc) to make
    // vsnprintf (that is used internally by octaspire_container_utf8_string_new_format)
    // to return negative value (encoding error in C99) is from groups.google.com/forum/m/#!topic/comp.std.c/llvkxXr5wE.I am not sure about the
    // portability of this test on different platforms.
    wint_t const value = WEOF;
    char const * const input = "%lc";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_format(octaspireContainerUtf8StringTestAllocator, input, value);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_ENCODING_ERROR, str->errorStatus);
    ASSERT_EQ(0,                                                           str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                                   str->allocator);

    ASSERT(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_ENCODING_ERROR, octaspire_container_utf8_string_get_error_status(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}
#endif

#if 0
TEST octaspire_container_utf8_string_new_format_decoding_error_test(void)
{
    char const * const value = "wo\xFF\xFF\xFF\xFFld";
    char const * const input = "Hello %s";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_format(octaspireContainerUtf8StringTestAllocator, input, value);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_DECODING_ERROR, str->errorStatus);
    ASSERT_EQ(8,                                                           str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                                   str->allocator);

    ASSERT(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_DECODING_ERROR, octaspire_container_utf8_string_get_error_status(str));
    ASSERT_EQ(8, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(8, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(8, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "Hello wo";

    ASSERT_MEM_EQ(
        expected,
        octaspire_container_utf8_string_get_c_string(str),
        octaspire_container_utf8_string_get_length_in_octets(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}
#endif


#if 0
TEST octaspire_container_utf8_string_new_format_decoding_error_another_test(void)
{
    float        const value1 = 42.01f;
    char const * const value2 = "wo\xFF\xFF\xFF\xFFld";
    char const * const input = "Hello © %g %s";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new_format(octaspireContainerUtf8StringTestAllocator, input, value1, value2);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_DECODING_ERROR, str->errorStatus);
    ASSERT_EQ(17,                                                          str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                                   str->allocator);

    ASSERT(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_DECODING_ERROR, octaspire_container_utf8_string_get_error_status(str));
    ASSERT_EQ(17, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(17, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(16, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "Hello \xC2\xA9 42.01 wo";

    ASSERT_MEM_EQ(
        expected,
        octaspire_container_utf8_string_get_c_string(str),
        octaspire_container_utf8_string_get_length_in_octets(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}
#endif

TEST octaspire_container_utf8_string_new_copy_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_t *cpy =
        octaspire_container_utf8_string_new_copy(str, octaspireContainerUtf8StringTestAllocator);

    ASSERT_EQ(
        octaspire_container_utf8_string_get_length_in_octets(str),
        octaspire_container_utf8_string_get_length_in_octets(cpy));

    ASSERT_MEM_EQ(
        octaspire_container_vector_get_element_at_const(str->octets, 0),
        octaspire_container_vector_get_element_at_const(cpy->octets, 0),
        octaspire_container_utf8_string_get_length_in_octets(str));

    ASSERT_EQ(
        octaspire_container_vector_get_length_in_octets(str->ucsCharacters),
        octaspire_container_vector_get_length_in_octets(cpy->ucsCharacters));

    ASSERT_MEM_EQ(
        octaspire_container_vector_get_element_at_const(str->ucsCharacters, 0),
        octaspire_container_vector_get_element_at_const(cpy->ucsCharacters, 0),
        octaspire_container_vector_get_length_in_octets(str->ucsCharacters));

    ASSERT_EQ(str->errorStatus,  cpy->errorStatus);
    ASSERT_EQ(str->errorAtOctet, cpy->errorAtOctet);

    ASSERT_EQ(cpy->allocator,     octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_release(str);
    str = 0;

    octaspire_container_utf8_string_release(cpy);
    cpy = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_copy_failure_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_CONTAINER_UTF8_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_container_utf8_string_get_c_string(str));

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    ASSERT_FALSE(octaspire_container_utf8_string_new_copy(str, octaspireContainerUtf8StringTestAllocator));

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_get_length_in_ucs_characters_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    //ASSERT_EQ(37, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_get_length_in_ucs_characters_called_with_empty_string_test(void)
{
    char const * const input = "";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_get_length_in_octets_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_container_utf8_string_get_length_in_octets(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_get_length_in_octets_called_with_empty_string_test(void)
{
    char const * const input = "";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_container_utf8_string_get_length_in_octets(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_get_ucs_character_at_index_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

#define EXPECTED_LENGTH 30

    ASSERT_EQ(EXPECTED_LENGTH, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    uint32_t expected[EXPECTED_LENGTH] =
    {
        0xA9,    // Copyright symbol
        0x48,    // H
        0x65,    // e
        0x6C,    // l
        0x6C,    // l
        0x6F,    // o
        0x20,    // SPACE
        0x57,    // W
        0x6F,    // o
        0x72,    // r
        0x6C,    // l
        0x64,    // d
        0x21,    // !
        0x20,    // SPACE
        0xA9,    // Copyright symbol
        0x20,    // SPACE
        0x2260,  // NOT EQUAL SIGN
        0x10000, // LINEAR B SYLLABLE B008 A
        0x48,    // H
        0x6F,    // o
        0x77,    // w
        0x20,    // SPACE
        0x61,    // a
        0x72,    // r
        0x65,    // e
        0x20,    // SPACE
        0x79,    // y
        0x6F,    // o
        0x75,    // u
        0x3F,    // ?
    };

    for (size_t i = 0; i < EXPECTED_LENGTH; ++i)
    {
        ASSERT_EQ(expected[i], octaspire_container_utf8_string_get_ucs_character_at_index(str, i));
    }

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_get_c_string_test(void)
{
    char const * const input    = "Hello World! ©";
    char const * const expected = "Hello World! \xc2\xa9";

    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(15, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(14, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    ASSERT_STR_EQ(
        expected,
        octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_get_c_string_called_with_empty_string_test(void)
{
    char const * const input    = "";

    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    ASSERT_EQ('\0', *octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_is_error_false_case_test(void)
{
    char const * const input    = "Hello World";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_is_error_true_case_test(void)
{
    char const * const input    = "Hello World\xC0\xB3";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(octaspire_container_utf8_string_is_error(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_get_error_position_in_octets_called_when_has_error_test(void)
{
    char const * const input    = "Hello World\xC0\xB3";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_EQ(11, octaspire_container_utf8_string_get_error_position_in_octets(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_get_error_position_in_octets_called_when_has_no_error_test(void)
{
    char const * const input    = "Hello World";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_reset_error_status_called_when_there_is_error_test(void)
{
    char const * const input    = "Hello World\xC0\xB3";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(11, octaspire_container_utf8_string_get_error_position_in_octets(str));

    octaspire_container_utf8_string_reset_error_status(str);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_reset_error_status_called_when_there_is_no_error_test(void)
{
    char const * const input    = "Hello World";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    octaspire_container_utf8_string_reset_error_status(str);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_concatenate_c_string_called_with_null_and_empty_string_arguments_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_concatenate_c_string(str, 0);
    octaspire_container_utf8_string_concatenate_c_string(str, "");

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

// TODO XXX Add test cases for allocation failures in concatenate_c_string...

TEST octaspire_container_utf8_string_concatenate_c_string_test(void)
{
    char const * const input  = "©Hello World!";
    char const * const input2 = " © ≠𐀀How are you?";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_concatenate_c_string(str, input2);

    ASSERT_FALSE(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_concatenate_c_string_with_decode_error_test(void)
{
    char const * const input  = "©Hello World!";
    char const * const input2 = " © ≠𐀀How are you?\xC0\xB3";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_concatenate_c_string(str, input2);

    ASSERT(octaspire_container_utf8_string_is_error(str));
    ASSERT_EQ(23, octaspire_container_utf8_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_container_utf8_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_container_utf8_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_concatenate_c_string_allocation_failure_one_test(void)
{
    char const * const input  = "©Hello World!";
    char const * const input2 = " © ≠𐀀How are you?";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 1, 0);

    ASSERT_FALSE(octaspire_container_utf8_string_concatenate_c_string(str, input2));

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_concatenate_c_string_allocation_failure_two_test(void)
{
    char const * const input  = "a";
    char const * const input2 = "bcd";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerUtf8StringTestAllocator,
        2, 0x00000002);

    ASSERT_FALSE(octaspire_container_utf8_string_concatenate_c_string(str, input2));

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_concatenate_c_string_allocation_failure_three_test(void)
{
    char const * const input  = "a";
    char const * const input2 = "b";
    octaspire_container_utf8_string_t *str =
        octaspire_container_utf8_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerUtf8StringTestAllocator,
        2, 0x00000001);

    ASSERT_FALSE(octaspire_container_utf8_string_concatenate_c_string(str, input2));

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_c_strings_end_always_in_null_byte_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new("", octaspireContainerUtf8StringTestAllocator);
    ASSERT_FALSE(octaspire_container_vector_is_empty(str->octets));

    ASSERT_EQ(
        octaspire_container_utf8_string_private_null_octet,
        *(char const * const)octaspire_container_vector_get_element_at(
            str->octets,
            octaspire_container_vector_get_length(str->octets) - 1));

    octaspire_container_utf8_string_release(str);
    str = 0;


    str = octaspire_container_utf8_string_new("a", octaspireContainerUtf8StringTestAllocator);
    ASSERT_FALSE(octaspire_container_vector_is_empty(str->octets));

    ASSERT_EQ(
        octaspire_container_utf8_string_private_null_octet,
        *(char const * const)octaspire_container_vector_get_element_at(
            str->octets,
            octaspire_container_vector_get_length(str->octets) - 1));

    octaspire_container_utf8_string_release(str);
    str = 0;


    str = octaspire_container_utf8_string_new_format(octaspireContainerUtf8StringTestAllocator, "");
    ASSERT_FALSE(octaspire_container_vector_is_empty(str->octets));

    ASSERT_EQ(
        octaspire_container_utf8_string_private_null_octet,
        *(char const * const)octaspire_container_vector_get_element_at(
            str->octets,
            octaspire_container_vector_get_length(str->octets) - 1));

    octaspire_container_utf8_string_release(str);
    str = 0;


    size_t const size = 112;
    str = octaspire_container_utf8_string_new_format(octaspireContainerUtf8StringTestAllocator, "%zu", size);
    ASSERT_FALSE(octaspire_container_vector_is_empty(str->octets));

    ASSERT_EQ(
        octaspire_container_utf8_string_private_null_octet,
        *(char const * const)octaspire_container_vector_get_element_at(
            str->octets,
            octaspire_container_vector_get_length(str->octets) - 1));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_format_numbers_into_vector_test(void)
{
    octaspire_container_vector_t *vec = octaspire_container_vector_new(
        sizeof(octaspire_container_utf8_string_t*),
        true,
        (octaspire_container_vector_element_callback_t)octaspire_container_utf8_string_release,
        octaspireContainerUtf8StringTestAllocator);

    size_t const numElements = 256;

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new_format(
            octaspireContainerUtf8StringTestAllocator,
            "%zu",
            i);

        octaspire_container_vector_push_back_element(vec, &str);

    }

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_container_utf8_string_t const * const str =
            octaspire_container_vector_get_element_at_const(vec, i);

        ASSERT_EQ(i, (size_t)atoi(octaspire_container_utf8_string_get_c_string(str)));
    }

    octaspire_container_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_container_utf8_string_new_format_number_test(void)
{
    size_t const i = 2000;
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new_format(
            octaspireContainerUtf8StringTestAllocator,
            "%zu",
            i);

    ASSERT_EQ(i, (size_t)atoi(octaspire_container_utf8_string_get_c_string(str)));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_find_char_a_from_string_a123a56a89a_using_index_zero_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "a123a56a89a",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *character =
        octaspire_container_utf8_string_new("a123",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && character);

    octaspire_container_vector_t *indices = octaspire_container_utf8_string_find_char(
        str,
        character,
        0);

    ASSERT(indices);

    ASSERT_EQ(4, octaspire_container_vector_get_length(indices));

    ASSERT_EQ(0,  *(size_t*)octaspire_container_vector_get_element_at(indices, 0));
    ASSERT_EQ(4,  *(size_t*)octaspire_container_vector_get_element_at(indices, 1));
    ASSERT_EQ(7,  *(size_t*)octaspire_container_vector_get_element_at(indices, 2));
    ASSERT_EQ(10, *(size_t*)octaspire_container_vector_get_element_at(indices, 3));

    octaspire_container_vector_release(indices);
    indices = 0;

    octaspire_container_utf8_string_release(character);
    character = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_find_char_q_from_string_a123a56q89q_using_index_one_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "a123a56q89q",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *character =
        octaspire_container_utf8_string_new("aq123",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && character);

    octaspire_container_vector_t *indices = octaspire_container_utf8_string_find_char(
        str,
        character,
        1);

    ASSERT(indices);

    ASSERT_EQ(2, octaspire_container_vector_get_length(indices));

    ASSERT_EQ(7,  *(size_t*)octaspire_container_vector_get_element_at(indices, 0));
    ASSERT_EQ(10, *(size_t*)octaspire_container_vector_get_element_at(indices, 1));

    octaspire_container_vector_release(indices);
    indices = 0;

    octaspire_container_utf8_string_release(character);
    character = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_find_char_c_from_string_a123c56q89q_using_index_two_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "a123c56q89q",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *character =
        octaspire_container_utf8_string_new("aqc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && character);

    octaspire_container_vector_t *indices = octaspire_container_utf8_string_find_char(
        str,
        character,
        2);

    ASSERT(indices);

    ASSERT_EQ(1, octaspire_container_vector_get_length(indices));

    ASSERT_EQ(4, *(size_t*)octaspire_container_vector_get_element_at(indices, 0));

    octaspire_container_vector_release(indices);
    indices = 0;

    octaspire_container_utf8_string_release(character);
    character = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_find_char_c_from_string_a123y56q89q_using_index_two_failure_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "a123y56q89q",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *character =
        octaspire_container_utf8_string_new("aqc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && character);

    octaspire_container_vector_t *indices = octaspire_container_utf8_string_find_char(
        str,
        character,
        2);

    ASSERT(indices);

    ASSERT_EQ(0, octaspire_container_vector_get_length(indices));

    octaspire_container_vector_release(indices);
    indices = 0;

    octaspire_container_utf8_string_release(character);
    character = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_find_string_cat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_zero_and_length_of_3_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "cat dog cat zebra car kitten cat",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *lookFor =
        octaspire_container_utf8_string_new("cat",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_container_vector_t *indices = octaspire_container_utf8_string_find_string(
        str,
        lookFor,
        0,
        3);

    ASSERT(indices);

    ASSERT_EQ(3, octaspire_container_vector_get_length(indices));

    ASSERT_EQ(0,   *(size_t*)octaspire_container_vector_get_element_at(indices, 0));
    ASSERT_EQ(8,   *(size_t*)octaspire_container_vector_get_element_at(indices, 1));
    ASSERT_EQ(29,  *(size_t*)octaspire_container_vector_get_element_at(indices, 2));

    octaspire_container_vector_release(indices);
    indices = 0;

    octaspire_container_utf8_string_release(lookFor);
    lookFor = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_find_string_cat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_one_and_length_of_3_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "cat dog cat zebra car kitten cat",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *lookFor =
        octaspire_container_utf8_string_new(">cat<",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_container_vector_t *indices = octaspire_container_utf8_string_find_string(
        str,
        lookFor,
        1,
        3);

    ASSERT(indices);

    ASSERT_EQ(3, octaspire_container_vector_get_length(indices));

    ASSERT_EQ(0,   *(size_t*)octaspire_container_vector_get_element_at(indices, 0));
    ASSERT_EQ(8,   *(size_t*)octaspire_container_vector_get_element_at(indices, 1));
    ASSERT_EQ(29,  *(size_t*)octaspire_container_vector_get_element_at(indices, 2));

    octaspire_container_vector_release(indices);
    indices = 0;

    octaspire_container_utf8_string_release(lookFor);
    lookFor = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_find_string_dog_from_string_dog_cat_zebra_using_index_zero_and_length_of_three_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "dog cat zebra",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *lookFor =
        octaspire_container_utf8_string_new("dog",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_container_vector_t *indices = octaspire_container_utf8_string_find_string(
        str,
        lookFor,
        0,
        3);

    ASSERT(indices);

    ASSERT_EQ(1, octaspire_container_vector_get_length(indices));

    ASSERT_EQ(0,   *(size_t*)octaspire_container_vector_get_element_at(indices, 0));

    octaspire_container_vector_release(indices);
    indices = 0;

    octaspire_container_utf8_string_release(lookFor);
    lookFor = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_find_string_dog_from_string_cat_zebra_dog_using_index_zero_and_length_of_three_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "cat zebra dog",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *lookFor =
        octaspire_container_utf8_string_new("dog",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_container_vector_t *indices = octaspire_container_utf8_string_find_string(
        str,
        lookFor,
        0,
        3);

    ASSERT(indices);

    ASSERT_EQ(1, octaspire_container_vector_get_length(indices));

    ASSERT_EQ(10,   *(size_t*)octaspire_container_vector_get_element_at(indices, 0));

    octaspire_container_vector_release(indices);
    indices = 0;

    octaspire_container_utf8_string_release(lookFor);
    lookFor = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_find_string_dog_from_string_cat_zebra_kitten_using_index_zero_and_length_of_three_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "cat zebra kitten",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *lookFor =
        octaspire_container_utf8_string_new("dog",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_container_vector_t *indices = octaspire_container_utf8_string_find_string(
        str,
        lookFor,
        0,
        3);

    ASSERT(indices);

    ASSERT_EQ(0, octaspire_container_vector_get_length(indices));

    octaspire_container_vector_release(indices);
    indices = 0;

    octaspire_container_utf8_string_release(lookFor);
    lookFor = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_find_string_kitten_from_string_cat_using_index_zero_and_length_of_six_failure_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "cat",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *lookFor =
        octaspire_container_utf8_string_new("kitten",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_container_vector_t *indices = octaspire_container_utf8_string_find_string(
        str,
        lookFor,
        0,
        6);

    ASSERT(indices);

    ASSERT_EQ(0, octaspire_container_vector_get_length(indices));

    octaspire_container_vector_release(indices);
    indices = 0;

    octaspire_container_utf8_string_release(lookFor);
    lookFor = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_private_check_substring_match_at_middle_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "123kitten456",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *substring =
        octaspire_container_utf8_string_new("kitten",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    for (size_t i = 0; i < octaspire_container_utf8_string_get_length_in_ucs_characters(str); ++i)
    {
        ASSERT_EQ(i == 3 ? true : false,
            octaspire_container_utf8_string_private_check_substring_match_at(
                str,
                i,
                substring));
    }

    octaspire_container_utf8_string_release(substring);
    substring = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_private_check_substring_match_at_the_beginning_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "kitten456",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *substring =
        octaspire_container_utf8_string_new("kitten",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    for (size_t i = 0; i < octaspire_container_utf8_string_get_length_in_ucs_characters(str); ++i)
    {
        ASSERT_EQ(i == 0 ? true : false,
            octaspire_container_utf8_string_private_check_substring_match_at(
                str,
                i,
                substring));
    }

    octaspire_container_utf8_string_release(substring);
    substring = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_private_check_substring_match_at_the_end_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "123kitten",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *substring =
        octaspire_container_utf8_string_new("kitten",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    for (size_t i = 0; i < octaspire_container_utf8_string_get_length_in_ucs_characters(str); ++i)
    {
        ASSERT_EQ(i == 3 ? true : false,
            octaspire_container_utf8_string_private_check_substring_match_at(
                str,
                i,
                substring));
    }

    octaspire_container_utf8_string_release(substring);
    substring = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_find_first_substring_abc_from_123abc456abc_starting_from_index_0_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "123abc456abc",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *substring =
        octaspire_container_utf8_string_new("abc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    ASSERT_EQ(
        3,
        octaspire_container_utf8_string_find_first_substring(
            str,
            0,
            substring));

    octaspire_container_utf8_string_release(substring);
    substring = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_find_first_substring_abc_from_123abc456abc_starting_from_index_4_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "123abc456abc",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *substring =
        octaspire_container_utf8_string_new("abc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    ASSERT_EQ(
        9,
        octaspire_container_utf8_string_find_first_substring(
            str,
            4,
            substring));

    octaspire_container_utf8_string_release(substring);
    substring = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_find_first_substring_abcd_from_123abc456abc_starting_from_index_0_failure_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "123abc456abc",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *substring =
        octaspire_container_utf8_string_new("abcd",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    ASSERT_EQ(
        -1,
        octaspire_container_utf8_string_find_first_substring(
            str,
            0,
            substring));

    octaspire_container_utf8_string_release(substring);
    substring = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_private_ucs_character_index_to_octets_index_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "0123456789",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    for (size_t i = 0; i < octaspire_container_utf8_string_get_length_in_ucs_characters(str); ++i)
    {
        ASSERT_EQ(i, octaspire_container_utf8_string_private_ucs_character_index_to_octets_index(str, i));
    }

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_remove_character_at_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "0123456789",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(octaspire_container_utf8_string_remove_character_at(str, 1));
    ASSERT_STR_EQ("023456789", octaspire_container_utf8_string_get_c_string(str));

    ASSERT(octaspire_container_utf8_string_remove_character_at(str, 0));
    ASSERT_STR_EQ("23456789", octaspire_container_utf8_string_get_c_string(str));

    ASSERT(octaspire_container_utf8_string_remove_character_at(str, 7));
    ASSERT_STR_EQ("2345678", octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_remove_characters_at_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "0123456789",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT_EQ(3, octaspire_container_utf8_string_remove_characters_at(str, 7, 3));
    ASSERT_STR_EQ("0123456", octaspire_container_utf8_string_get_c_string(str));

    ASSERT_EQ(3, octaspire_container_utf8_string_remove_characters_at(str, 2, 3));
    ASSERT_STR_EQ("0156", octaspire_container_utf8_string_get_c_string(str));

    ASSERT_EQ(3, octaspire_container_utf8_string_remove_characters_at(str, 0, 3));
    ASSERT_STR_EQ("6", octaspire_container_utf8_string_get_c_string(str));

    ASSERT_EQ(1, octaspire_container_utf8_string_remove_characters_at(str, 0, 1));
    ASSERT_STR_EQ("", octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_remove_all_substrings_kitten_from_string_kitten_cat_kitten_dog_kitten_zebra_kitten_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new(
            "kitten cat kitten dog kitten zebra kitten",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *substring =
        octaspire_container_utf8_string_new("kitten",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    ASSERT_EQ(4, octaspire_container_utf8_string_remove_all_substrings(str, substring));

    ASSERT_STR_EQ(
        " cat  dog  zebra ",
        octaspire_container_utf8_string_get_c_string(str));

    octaspire_container_utf8_string_release(substring);
    substring = 0;

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_container_utf8_string_insert_string_to_bc_into_index_1_of_ade_test(void)
{
    octaspire_container_utf8_string_t *strTarget = octaspire_container_utf8_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *strAddition =
        octaspire_container_utf8_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_container_utf8_string_insert_string_to(strTarget, strAddition, 1));

    ASSERT_EQ(5, octaspire_container_utf8_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "abcde",
        octaspire_container_utf8_string_get_c_string(strTarget));

    octaspire_container_utf8_string_release(strAddition);
    strAddition = 0;

    octaspire_container_utf8_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_container_utf8_string_insert_string_to_bc_into_index_minus_1_of_ade_test(void)
{
    octaspire_container_utf8_string_t *strTarget = octaspire_container_utf8_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *strAddition =
        octaspire_container_utf8_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_container_utf8_string_insert_string_to(strTarget, strAddition, -1));

    ASSERT_EQ(5, octaspire_container_utf8_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "adbce",
        octaspire_container_utf8_string_get_c_string(strTarget));

    octaspire_container_utf8_string_release(strAddition);
    strAddition = 0;

    octaspire_container_utf8_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_container_utf8_string_insert_string_to_bc_into_index_minus_3_of_ade_test(void)
{
    octaspire_container_utf8_string_t *strTarget = octaspire_container_utf8_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *strAddition =
        octaspire_container_utf8_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_container_utf8_string_insert_string_to(strTarget, strAddition, -3));

    ASSERT_EQ(5, octaspire_container_utf8_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "bcade",
        octaspire_container_utf8_string_get_c_string(strTarget));

    octaspire_container_utf8_string_release(strAddition);
    strAddition = 0;

    octaspire_container_utf8_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_container_utf8_string_insert_string_to_bc_into_index_minus_4_of_ade_failure_test(void)
{
    octaspire_container_utf8_string_t *strTarget = octaspire_container_utf8_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *strAddition =
        octaspire_container_utf8_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT_FALSE(octaspire_container_utf8_string_insert_string_to(strTarget, strAddition, -4));

    ASSERT_EQ(3, octaspire_container_utf8_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "ade",
        octaspire_container_utf8_string_get_c_string(strTarget));

    octaspire_container_utf8_string_release(strAddition);
    strAddition = 0;

    octaspire_container_utf8_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_container_utf8_string_insert_string_to_bc_into_index_3_of_ade_failure_test(void)
{
    octaspire_container_utf8_string_t *strTarget = octaspire_container_utf8_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *strAddition =
        octaspire_container_utf8_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT_FALSE(octaspire_container_utf8_string_insert_string_to(strTarget, strAddition, 3));

    ASSERT_EQ(3, octaspire_container_utf8_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "ade",
        octaspire_container_utf8_string_get_c_string(strTarget));

    octaspire_container_utf8_string_release(strAddition);
    strAddition = 0;

    octaspire_container_utf8_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_container_utf8_string_insert_string_to_bc_into_index_0_of_ade_test(void)
{
    octaspire_container_utf8_string_t *strTarget = octaspire_container_utf8_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *strAddition =
        octaspire_container_utf8_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_container_utf8_string_insert_string_to(strTarget, strAddition, 0));

    ASSERT_EQ(5, octaspire_container_utf8_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "bcade",
        octaspire_container_utf8_string_get_c_string(strTarget));

    octaspire_container_utf8_string_release(strAddition);
    strAddition = 0;

    octaspire_container_utf8_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_container_utf8_string_insert_string_to_bc_into_index_2_of_ade_test(void)
{
    octaspire_container_utf8_string_t *strTarget = octaspire_container_utf8_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_container_utf8_string_t *strAddition =
        octaspire_container_utf8_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_container_utf8_string_insert_string_to(strTarget, strAddition, 2));

    ASSERT_EQ(5, octaspire_container_utf8_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "adbce",
        octaspire_container_utf8_string_get_c_string(strTarget));

    octaspire_container_utf8_string_release(strAddition);
    strAddition = 0;

    octaspire_container_utf8_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_container_utf8_string_pop_back_ucs_character_test(void)
{
    octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);
    ASSERT_EQ(3, octaspire_container_utf8_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("abc", octaspire_container_utf8_string_get_c_string(str));

    ASSERT(octaspire_container_utf8_string_pop_back_ucs_character(str));
    ASSERT_EQ(2, octaspire_container_utf8_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("ab", octaspire_container_utf8_string_get_c_string(str));

    ASSERT(octaspire_container_utf8_string_pop_back_ucs_character(str));
    ASSERT_EQ(1, octaspire_container_utf8_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("a", octaspire_container_utf8_string_get_c_string(str));

    ASSERT(octaspire_container_utf8_string_pop_back_ucs_character(str));
    ASSERT_EQ(0, octaspire_container_utf8_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("", octaspire_container_utf8_string_get_c_string(str));

    for (size_t i = 0; i < 10; ++i)
    {
        ASSERT_FALSE(octaspire_container_utf8_string_pop_back_ucs_character(str));
        ASSERT_EQ(0, octaspire_container_utf8_string_get_length_in_ucs_characters(str));
        ASSERT_STR_EQ("", octaspire_container_utf8_string_get_c_string(str));
    }

    octaspire_container_utf8_string_release(str);
    str = 0;

    PASS();
}

static size_t octaspireContainerUtf8StringSuiteNumTimesRun = 0;

GREATEST_SUITE(octaspire_container_utf8_string_suite)
{
    octaspireContainerUtf8StringSuiteNumTimesRun = 0;

    octaspireContainerUtf8StringTestAllocator = octaspire_memory_allocator_new_create_region(
        OCTASPIRE_CORE_CONFIG_MEMORY_ALLOCATOR_REGION_MIN_BLOCK_SIZE_IN_OCTETS);

second_run:

    assert(octaspireContainerUtf8StringTestAllocator);

    RUN_TEST(octaspire_container_utf8_string_new_called_with_null_argument_test);
    RUN_TEST(octaspire_container_utf8_string_new_with_simple_ascii_string_test);
    RUN_TEST(octaspire_container_utf8_string_new_with_some_multioctet_ucs_characters_test);
    RUN_TEST(octaspire_container_utf8_string_new_with_simple_ascii_string_with_error_test);
    RUN_TEST(octaspire_container_utf8_string_new_from_buffer_with_some_multioctet_ucs_characters_test);
    RUN_TEST(octaspire_container_utf8_string_new_from_buffer_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_container_utf8_string_new_from_buffer_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_container_utf8_string_new_from_buffer_allocation_failure_on_third_allocation_test);
    RUN_TEST(octaspire_container_utf8_string_new_from_buffer_allocation_failure_on_fourth_allocation_test);



    RUN_TEST(octaspire_container_utf8_string_new_from_buffer_allocation_failure_on_sixth_1_allocation_test);
    RUN_TEST(octaspire_container_utf8_string_new_from_buffer_allocation_failure_on_sixth_2_allocation_test);
    RUN_TEST(octaspire_container_utf8_string_new_format_with_string_test);
    RUN_TEST(octaspire_container_utf8_string_new_format_with_size_t_test);
    RUN_TEST(octaspire_container_utf8_string_new_format_with_doubles_test);
    RUN_TEST(octaspire_container_utf8_string_new_format_with_string_and_size_t_test);
    RUN_TEST(octaspire_container_utf8_string_new_format_with_string_and_size_t_on_otherwise_empty_format_string_test);
    RUN_TEST(octaspire_container_utf8_string_new_format_with_empty_format_string_test);
    //RUN_TEST(octaspire_container_utf8_string_new_format_encoding_error_test);
    //RUN_TEST(octaspire_container_utf8_string_new_format_decoding_error_test);
    //RUN_TEST(octaspire_container_utf8_string_new_format_decoding_error_another_test);
    RUN_TEST(octaspire_container_utf8_string_new_copy_test);
    RUN_TEST(octaspire_container_utf8_string_new_copy_failure_test);
    RUN_TEST(octaspire_container_utf8_string_get_length_in_ucs_characters_test);
    RUN_TEST(octaspire_container_utf8_string_get_length_in_ucs_characters_called_with_empty_string_test);
    RUN_TEST(octaspire_container_utf8_string_get_length_in_octets_test);
    RUN_TEST(octaspire_container_utf8_string_get_length_in_octets_called_with_empty_string_test);
    RUN_TEST(octaspire_container_utf8_string_get_ucs_character_at_index_test);
    RUN_TEST(octaspire_container_utf8_string_get_c_string_test);
    RUN_TEST(octaspire_container_utf8_string_get_c_string_called_with_empty_string_test);
    RUN_TEST(octaspire_container_utf8_string_is_error_false_case_test);
    RUN_TEST(octaspire_container_utf8_string_is_error_true_case_test);
    RUN_TEST(octaspire_container_utf8_string_get_error_position_in_octets_called_when_has_error_test);
    RUN_TEST(octaspire_container_utf8_string_get_error_position_in_octets_called_when_has_no_error_test);
    RUN_TEST(octaspire_container_utf8_string_reset_error_status_called_when_there_is_error_test);
    RUN_TEST(octaspire_container_utf8_string_reset_error_status_called_when_there_is_no_error_test);
    RUN_TEST(octaspire_container_utf8_string_concatenate_c_string_called_with_null_and_empty_string_arguments_test);
    RUN_TEST(octaspire_container_utf8_string_concatenate_c_string_test);
    RUN_TEST(octaspire_container_utf8_string_concatenate_c_string_with_decode_error_test);
    RUN_TEST(octaspire_container_utf8_string_concatenate_c_string_allocation_failure_one_test);
    RUN_TEST(octaspire_container_utf8_string_concatenate_c_string_allocation_failure_two_test);
    RUN_TEST(octaspire_container_utf8_string_concatenate_c_string_allocation_failure_three_test);
    RUN_TEST(octaspire_container_utf8_string_c_strings_end_always_in_null_byte_test);
    RUN_TEST(octaspire_container_utf8_string_new_format_numbers_into_vector_test);
    RUN_TEST(octaspire_container_utf8_string_new_format_number_test);
    RUN_TEST(octaspire_container_utf8_string_find_char_a_from_string_a123a56a89a_using_index_zero_test);
    RUN_TEST(octaspire_container_utf8_string_find_char_q_from_string_a123a56q89q_using_index_one_test);
    RUN_TEST(octaspire_container_utf8_string_find_char_c_from_string_a123c56q89q_using_index_two_test);
    RUN_TEST(octaspire_container_utf8_string_find_char_c_from_string_a123y56q89q_using_index_two_failure_test);
    RUN_TEST(octaspire_container_utf8_string_find_string_cat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_zero_and_length_of_3_test);
    RUN_TEST(octaspire_container_utf8_string_find_string_cat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_one_and_length_of_3_test);
    RUN_TEST(octaspire_container_utf8_string_find_string_dog_from_string_dog_cat_zebra_using_index_zero_and_length_of_three_test);
    RUN_TEST(octaspire_container_utf8_string_find_string_dog_from_string_cat_zebra_dog_using_index_zero_and_length_of_three_test);
    RUN_TEST(octaspire_container_utf8_string_find_string_dog_from_string_cat_zebra_kitten_using_index_zero_and_length_of_three_test);
    RUN_TEST(octaspire_container_utf8_string_find_string_kitten_from_string_cat_using_index_zero_and_length_of_six_failure_test);
    RUN_TEST(octaspire_container_utf8_string_private_check_substring_match_at_middle_test);
    RUN_TEST(octaspire_container_utf8_string_private_check_substring_match_at_the_beginning_test);
    RUN_TEST(octaspire_container_utf8_string_private_check_substring_match_at_the_end_test);
    RUN_TEST(octaspire_container_utf8_string_find_first_substring_abc_from_123abc456abc_starting_from_index_0_test);
    RUN_TEST(octaspire_container_utf8_string_find_first_substring_abc_from_123abc456abc_starting_from_index_4_test);
    RUN_TEST(octaspire_container_utf8_string_find_first_substring_abcd_from_123abc456abc_starting_from_index_0_failure_test);
    RUN_TEST(octaspire_container_utf8_string_private_ucs_character_index_to_octets_index_test);
    RUN_TEST(octaspire_container_utf8_string_remove_character_at_test);
    RUN_TEST(octaspire_container_utf8_string_remove_characters_at_test);
    RUN_TEST(octaspire_container_utf8_string_remove_all_substrings_kitten_from_string_kitten_cat_kitten_dog_kitten_zebra_kitten_test);
    RUN_TEST(octaspire_container_utf8_string_insert_string_to_bc_into_index_1_of_ade_test);
    RUN_TEST(octaspire_container_utf8_string_insert_string_to_bc_into_index_minus_1_of_ade_test);
    RUN_TEST(octaspire_container_utf8_string_insert_string_to_bc_into_index_minus_3_of_ade_test);
    RUN_TEST(octaspire_container_utf8_string_insert_string_to_bc_into_index_minus_4_of_ade_failure_test);
    RUN_TEST(octaspire_container_utf8_string_insert_string_to_bc_into_index_3_of_ade_failure_test);
    RUN_TEST(octaspire_container_utf8_string_insert_string_to_bc_into_index_0_of_ade_test);
    RUN_TEST(octaspire_container_utf8_string_insert_string_to_bc_into_index_2_of_ade_test);
    RUN_TEST(octaspire_container_utf8_string_pop_back_ucs_character_test);

    octaspire_memory_allocator_release(octaspireContainerUtf8StringTestAllocator);
    octaspireContainerUtf8StringTestAllocator = 0;

    ++octaspireContainerUtf8StringSuiteNumTimesRun;

    if (octaspireContainerUtf8StringSuiteNumTimesRun < 2)
    {
        // Second run without region allocator

        octaspireContainerUtf8StringTestAllocator = octaspire_memory_allocator_new(0);

        goto second_run;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../test/test_container_utf8_string.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../test/test_container_pair.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

static octaspire_memory_allocator_t *octaspireContainerPairTestAllocator = 0;

TEST octaspire_container_pair_new_short_and_long_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    ASSERT(p->first);
    ASSERT(p->second);

    ASSERT_EQ(0, *(short const*)p->first);
    ASSERT_EQ(0, *(long const*)p->second);

    ASSERT_EQ(sizeof(short), p->firstSize);
    ASSERT_EQ(sizeof(long),  p->secondSize);
    ASSERT_EQ(0,             p->firstReleaseCallback);
    ASSERT_EQ(0,             p->secondReleaseCallback);
    ASSERT_EQ(octaspireContainerPairTestAllocator,     p->allocator);

    short const expectedFirst  = 11;
    long  const expectedSecond = 12;
    octaspire_container_pair_set(p, &expectedFirst, &expectedSecond);

    ASSERT_EQ(expectedFirst,  *(short const *)p->first);
    ASSERT_EQ(expectedSecond, *(long const *) p->second);

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_new_long_and_short_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    ASSERT(p->first);
    ASSERT(p->second);

    ASSERT_EQ(0, *(long const*)p->first);
    ASSERT_EQ(0, *(short const*)p->second);

    ASSERT_EQ(sizeof(long), p->firstSize);
    ASSERT_EQ(sizeof(short),  p->secondSize);
    ASSERT_EQ(0,             p->firstReleaseCallback);
    ASSERT_EQ(0,             p->secondReleaseCallback);
    ASSERT_EQ(octaspireContainerPairTestAllocator,     p->allocator);

    long  const expectedFirst  = 11;
    short const expectedSecond = 12;
    octaspire_container_pair_set(p, &expectedFirst, &expectedSecond);

    ASSERT_EQ(expectedFirst,  *(long const*) p->first);
    ASSERT_EQ(expectedSecond, *(short const*)p->second);

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_new_uint32_t_and_double_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(uint32_t),
        false,
        sizeof(double),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    ASSERT(p->first);
    ASSERT(p->second);

    ASSERT_IN_RANGE(0, *(uint32_t*)p->first, 0.000001);
    ASSERT_IN_RANGE(0, *(double*)p->second,  0.000001);

    ASSERT_EQ(sizeof(uint32_t), p->firstSize);
    ASSERT_EQ(sizeof(double),   p->secondSize);
    ASSERT_EQ(0,                p->firstReleaseCallback);
    ASSERT_EQ(0,                p->secondReleaseCallback);
    ASSERT_EQ(octaspireContainerPairTestAllocator,        p->allocator);

    uint32_t  const expectedFirst  = 11;
    double    const expectedSecond = 12.12;
    octaspire_container_pair_set(p, &expectedFirst, &expectedSecond);

    ASSERT_EQ(expectedFirst,  *(uint32_t const*)p->first);
    ASSERT_IN_RANGE(expectedSecond, *(double const*)p->second, 0.000001);

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_new_allocation_failure_on_first_allocation_test(void)
{
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_new_allocation_failure_on_second_allocation_test(void)
{
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        2,
        0x01);

    ASSERT_EQ(
        2,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_new_allocation_failure_on_third_allocation_test(void)
{
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        3,
        0x03);

    ASSERT_EQ(
        3,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_new_shallow_copy_uint32_t_and_double_test(void)
{
    octaspire_container_pair_t *expected = octaspire_container_pair_new(
        sizeof(uint32_t),
        false,
        sizeof(double),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(expected);

    uint32_t  const expectedFirst  = 11;
    double    const expectedSecond = 12.12;
    octaspire_container_pair_set(expected, &expectedFirst, &expectedSecond);

    octaspire_container_pair_t *p = octaspire_container_pair_new_shallow_copy(
        expected,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    ASSERT(p->first);
    ASSERT(p->second);

    ASSERT_EQ(*(uint32_t const*)expected->first,  *(uint32_t const*)p->first);
    ASSERT_IN_RANGE(*(double const*)expected->second, *(double const*)p->second, 0.000001);

    ASSERT_EQ(sizeof(uint32_t), p->firstSize);
    ASSERT_EQ(sizeof(double),   p->secondSize);
    ASSERT_EQ(0,                p->firstReleaseCallback);
    ASSERT_EQ(0,                p->secondReleaseCallback);
    ASSERT_EQ(octaspireContainerPairTestAllocator,        p->allocator);

    octaspire_container_pair_release(p);
    p = 0;

    octaspire_container_pair_release(expected);
    expected = 0;

    PASS();
}

TEST octaspire_container_pair_new_shallow_copy_failure_on_first_allocation_test(void)
{
    octaspire_container_pair_t *expected = octaspire_container_pair_new(
        sizeof(uint32_t),
        false,
        sizeof(double),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(expected);

    uint32_t  const expectedFirst  = 11;
    double    const expectedSecond = 12.12;
    octaspire_container_pair_set(expected, &expectedFirst, &expectedSecond);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_container_pair_t *p = octaspire_container_pair_new_shallow_copy(
        expected,
        octaspireContainerPairTestAllocator);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_container_pair_release(p);
    p = 0;

    octaspire_container_pair_release(expected);
    expected = 0;

    PASS();
}

TEST octaspire_container_pair_new_shallow_copy_failure_on_second_allocation_test(void)
{
    octaspire_container_pair_t *expected = octaspire_container_pair_new(
        sizeof(uint32_t),
        false,
        sizeof(double),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(expected);

    uint32_t  const expectedFirst  = 11;
    double    const expectedSecond = 12.12;
    octaspire_container_pair_set(expected, &expectedFirst, &expectedSecond);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        2,
        0x1);

    ASSERT_EQ(
        2,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_container_pair_t *p = octaspire_container_pair_new_shallow_copy(
        expected,
        octaspireContainerPairTestAllocator);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_container_pair_release(p);
    p = 0;

    octaspire_container_pair_release(expected);
    expected = 0;

    PASS();
}

TEST octaspire_container_pair_new_shallow_copy_failure_on_third_allocation_test(void)
{
    octaspire_container_pair_t *expected = octaspire_container_pair_new(
        sizeof(uint32_t),
        false,
        sizeof(double),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(expected);

    uint32_t  const expectedFirst  = 11;
    double    const expectedSecond = 12.12;
    octaspire_container_pair_set(expected, &expectedFirst, &expectedSecond);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        3,
        0x3);

    ASSERT_EQ(
        3,
        octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_container_pair_t *p = octaspire_container_pair_new_shallow_copy(
        expected,
        octaspireContainerPairTestAllocator);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_container_pair_release(p);
    p = 0;

    octaspire_container_pair_release(expected);
    expected = 0;

    PASS();
}

static size_t octaspire_container_pair_release_test_private_release_callback_for_first_callcount = 0;

static void octaspire_container_pair_release_test_private_release_callback_for_first(void *element)
{
    OCTASPIRE_HELPERS_UNUSED_PARAMETER(element);
    ++octaspire_container_pair_release_test_private_release_callback_for_first_callcount;
}

static size_t octaspire_container_pair_release_test_private_release_callback_for_second_callcount = 0;

static void octaspire_container_pair_release_test_private_release_callback_for_second(void *element)
{
    OCTASPIRE_HELPERS_UNUSED_PARAMETER(element);
    ++octaspire_container_pair_release_test_private_release_callback_for_second_callcount;
}

TEST octaspire_container_pair_release_test(void)
{
    octaspire_container_pair_release_test_private_release_callback_for_first_callcount  = 0;
    octaspire_container_pair_release_test_private_release_callback_for_second_callcount = 0;

    octaspire_container_utf8_string_t *second = octaspire_container_utf8_string_new(
        "second element of the pair in octaspire_container_pair_release_test",
        octaspireContainerPairTestAllocator);

    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(size_t),
        false,
        sizeof(octaspire_container_utf8_string_t*),
        true,
        octaspire_container_pair_release_test_private_release_callback_for_first,
        octaspire_container_pair_release_test_private_release_callback_for_second,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    size_t const first  = 11;
    octaspire_container_pair_set(p, &first, &second);

    ASSERT_EQ(first,  *(size_t const *)p->first);
    ASSERT_EQ(second, *(octaspire_container_utf8_string_t **)p->second);

    octaspire_container_pair_release(p);
    p = 0;

    octaspire_container_utf8_string_release(second);
    second = 0;

    ASSERT_EQ(1, octaspire_container_pair_release_test_private_release_callback_for_first_callcount);
    ASSERT_EQ(1, octaspire_container_pair_release_test_private_release_callback_for_second_callcount);

    PASS();
}

TEST octaspire_container_pair_get_first_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    long  const expectedFirst = -11;
    short const second        =  12;
    octaspire_container_pair_set(p, &expectedFirst, &second);

    ASSERT_EQ(expectedFirst, *(long const*)octaspire_container_pair_get_first(p));

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_get_first_const_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    long  const expectedFirst = -11;
    short const second        =  12;
    octaspire_container_pair_set(p, &expectedFirst, &second);

    ASSERT_EQ(expectedFirst, *(long const*)octaspire_container_pair_get_first_const(p));

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_get_second_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    long  const first           =  11;
    short const expectedSecond  = -12;
    octaspire_container_pair_set(p, &first, &expectedSecond);

    ASSERT_EQ(expectedSecond, *(short const*)octaspire_container_pair_get_second(p));

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_get_second_const_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    long  const first           =  11;
    short const expectedSecond  = -12;
    octaspire_container_pair_set(p, &first, &expectedSecond);

    ASSERT_EQ(expectedSecond, *(short const*)octaspire_container_pair_get_second_const(p));

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_get_size_of_first_element_in_octets_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    ASSERT_EQ(sizeof(long), octaspire_container_pair_get_size_of_first_element_in_octets(p));

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_get_size_of_second_element_in_octets_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    ASSERT_EQ(sizeof(short), octaspire_container_pair_get_size_of_second_element_in_octets(p));

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_set_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    short const expectedFirst  = 11;
    long  const expectedSecond = 12;
    octaspire_container_pair_set(p, &expectedFirst, &expectedSecond);

    ASSERT_EQ(expectedFirst,  *(short const *)p->first);
    ASSERT_EQ(expectedSecond, *(long const *) p->second);

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_set_first_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    short const expectedFirst  = 11;
    long  const expectedSecond = 0;
    octaspire_container_pair_set_first(p, &expectedFirst);

    ASSERT_EQ(expectedFirst,  *(short const *)p->first);
    ASSERT_EQ(expectedSecond, *(long const *) p->second);

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_set_second_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    short const expectedFirst  = 0;
    long  const expectedSecond = 11;
    octaspire_container_pair_set_second(p, &expectedSecond);

    ASSERT_EQ(expectedFirst,  *(short const *)p->first);
    ASSERT_EQ(expectedSecond, *(long const *) p->second);

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_set_first_to_void_pointer_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(void*),
        true,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    void *expectedFirst = p;
    long  const expectedSecond = 0;
    ASSERT(octaspire_container_pair_set_first_to_void_pointer(p, expectedFirst));

    ASSERT_EQ(expectedFirst,  *(void **)p->first);
    ASSERT_EQ(expectedSecond, *(long const *)p->second);

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_set_first_to_void_pointer_failure_on_element_size_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(char),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    void *ptr = 0;
    ASSERT_FALSE(octaspire_container_pair_set_first_to_void_pointer(p, ptr));

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_set_second_to_void_pointer_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(long),
        false,
        sizeof(void*),
        true,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    void *expectedSecond = p;
    long  const expectedFirst = 0;
    ASSERT(octaspire_container_pair_set_second_to_void_pointer(p, expectedSecond));

    ASSERT_EQ(expectedFirst,  *(long const *)p->first);
    ASSERT_EQ(expectedSecond, *(void const **)p->second);

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_set_second_to_void_pointer_failure_on_element_size_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(long),
        false,
        sizeof(char),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    void *ptr = 0;
    ASSERT_FALSE(octaspire_container_pair_set_second_to_void_pointer(p, ptr));

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_container_pair_clear_test(void)
{
    octaspire_container_pair_t *p = octaspire_container_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    short const expectedFirst  = 11;
    long  const expectedSecond = 12;
    octaspire_container_pair_set(p, &expectedFirst, &expectedSecond);

    ASSERT_EQ(11, *(short const*)p->first);
    ASSERT_EQ(12, *(long const*)p->second);

    octaspire_container_pair_clear(p);

    ASSERT_EQ(0, *(short const*)p->first);
    ASSERT_EQ(0, *(long const*)p->second);

    octaspire_container_pair_release(p);
    p = 0;

    PASS();
}

static size_t octaspireContainerPairSuiteNumTimesRun = 0;

GREATEST_SUITE(octaspire_container_pair_suite)
{
    octaspireContainerPairSuiteNumTimesRun = 0;

    octaspireContainerPairTestAllocator = octaspire_memory_allocator_new_create_region(
        OCTASPIRE_CORE_CONFIG_MEMORY_ALLOCATOR_REGION_MIN_BLOCK_SIZE_IN_OCTETS);

second_run:

    RUN_TEST(octaspire_container_pair_new_short_and_long_test);
    RUN_TEST(octaspire_container_pair_new_long_and_short_test);
    RUN_TEST(octaspire_container_pair_new_uint32_t_and_double_test);
    RUN_TEST(octaspire_container_pair_new_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_container_pair_new_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_container_pair_new_allocation_failure_on_third_allocation_test);
    RUN_TEST(octaspire_container_pair_new_shallow_copy_uint32_t_and_double_test);
    RUN_TEST(octaspire_container_pair_new_shallow_copy_failure_on_first_allocation_test);
    RUN_TEST(octaspire_container_pair_new_shallow_copy_failure_on_second_allocation_test);
    RUN_TEST(octaspire_container_pair_new_shallow_copy_failure_on_third_allocation_test);
    RUN_TEST(octaspire_container_pair_release_test);
    RUN_TEST(octaspire_container_pair_get_first_test);
    RUN_TEST(octaspire_container_pair_get_first_const_test);
    RUN_TEST(octaspire_container_pair_get_second_test);
    RUN_TEST(octaspire_container_pair_get_second_const_test);
    RUN_TEST(octaspire_container_pair_get_size_of_first_element_in_octets_test);
    RUN_TEST(octaspire_container_pair_get_size_of_second_element_in_octets_test);
    RUN_TEST(octaspire_container_pair_set_test);
    RUN_TEST(octaspire_container_pair_set_first_test);
    RUN_TEST(octaspire_container_pair_set_second_test);
    RUN_TEST(octaspire_container_pair_set_first_to_void_pointer_test);
    RUN_TEST(octaspire_container_pair_set_first_to_void_pointer_failure_on_element_size_test);
    RUN_TEST(octaspire_container_pair_set_second_to_void_pointer_test);
    RUN_TEST(octaspire_container_pair_set_second_to_void_pointer_failure_on_element_size_test);
    RUN_TEST(octaspire_container_pair_clear_test);

    octaspire_memory_allocator_release(octaspireContainerPairTestAllocator);
    octaspireContainerPairTestAllocator = 0;

    ++octaspireContainerPairSuiteNumTimesRun;

    if (octaspireContainerPairSuiteNumTimesRun < 2)
    {
        // Second run without region allocator

        octaspireContainerPairTestAllocator = octaspire_memory_allocator_new(0);

        goto second_run;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../test/test_container_pair.c
//////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        ../test/test_container_hash_map.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

static octaspire_memory_allocator_t *octaspireContainerHashMapTestAllocator = 0;



TEST octaspire_container_hash_map_element_new_allocation_failure_on_first_allocation_test(void)
{
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    size_t const value = 0;
    octaspire_container_hash_map_element_t *element = octaspire_container_hash_map_element_new(
        0,
        sizeof(value),
        false,
        &value,
        sizeof(value),
        false,
        &value,
        octaspireContainerHashMapTestAllocator);

    ASSERT_FALSE(element);
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_container_hash_map_element_release(element);
    element = 0;

    PASS();
}

TEST octaspire_container_hash_map_element_new_allocation_failure_on_second_allocation_test(void)
{
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 2, 0x01);
    ASSERT_EQ(2, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    size_t const value = 0;
    octaspire_container_hash_map_element_t *element = octaspire_container_hash_map_element_new(
        0,
        sizeof(value),
        false,
        &value,
        sizeof(value),
        false,
        &value,
        octaspireContainerHashMapTestAllocator);

    ASSERT_FALSE(element);
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_container_hash_map_element_release(element);
    element = 0;

    PASS();
}

TEST octaspire_container_hash_map_element_new_allocation_failure_on_third_allocation_test(void)
{
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 3, 0x03);
    ASSERT_EQ(3, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    size_t const value = 0;
    octaspire_container_hash_map_element_t *element = octaspire_container_hash_map_element_new(
        0,
        sizeof(value),
        false,
        &value,
        sizeof(value),
        false,
        &value,
        octaspireContainerHashMapTestAllocator);

    ASSERT_FALSE(element);
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_container_hash_map_element_release(element);
    element = 0;

    PASS();
}

static bool octaspire_container_hash_map_new_test_key_compare_function_for_size_t_keys(
    void const * const key1,
    void const * const key2);

static uint32_t octaspire_container_hash_map_new_test_key_hash_function_for_size_t_keys(
    void const * const key);

static bool octaspire_container_hash_map_new_test_key_compare_function_for_size_t_keys(
    void const * const key1,
    void const * const key2)
{
    return *(size_t const * const)key1 == *(size_t const * const)key2;
}

static uint32_t octaspire_container_hash_map_new_test_key_hash_function_for_size_t_keys(
    void const * const key)
{
    size_t const value = *(size_t const * const)key;
    return (uint32_t)value;
}

TEST octaspire_container_hash_map_private_rehash_allocation_failure_on_first_allocation_test(void)
{
    octaspire_container_hash_map_t *hashMap = octaspire_container_hash_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_container_hash_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_container_hash_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 1, 0x00);
    ASSERT_EQ(1, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    ASSERT_FALSE(octaspire_container_hash_map_private_rehash(hashMap));
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_container_hash_map_release(hashMap);
    hashMap = 0;

    PASS();
}

#if 0
TEST octaspire_container_hash_map_private_rehash_allocation_failure_on_second_allocation_test(void)
{
    octaspire_container_hash_map_t *hashMap = octaspire_container_hash_map_new(
        sizeof(size_t),
        sizeof(size_t),
        octaspire_container_hash_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_container_hash_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    for (size_t value = 0; value < 5; ++value)
    {
        octaspire_container_hash_map_put(
            hashMap,
            0, //octaspire_helpers_calculate_murmur3_hash_for_size_t_argument(value),
            &value,
            &value);
    }

    // Should have 513 success, and number 514 should be failure
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged_when_larger_than_32(
        octaspireContainerHashMapTestAllocator,
        515,
        0xFF, // 0
        0xFF, // 1
        0xFF, // 2
        0xFF, // 3
        0xFF, // 4
        0xFF, // 5
        0xFF, // 6
        0xFF, // 7
        0xFF, // 8
        0xFF, // 9
        0xFF, // 10
        0xFF, // 11
        0xFF, // 12
        0xFF, // 13
        0xFF, // 14
        0xFF, // 15
        0xFF, // 16  512 success at this point
        0x03, // 17  +2  success
        0x00, // 18
        0x00);

    ASSERT_EQ(515, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    ASSERT_FALSE(octaspire_container_hash_map_private_rehash(hashMap));

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_container_hash_map_release(hashMap);
    hashMap = 0;

    PASS();
}
#endif

TEST octaspire_container_hash_map_new_keys_uint32_t_and_values_size_t_test(void)
{
    octaspire_container_hash_map_t *hashMap = octaspire_container_hash_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_container_hash_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_container_hash_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        uint32_t hash = (uint32_t)i;

        octaspire_container_hash_map_put(hashMap, hash, &i, &i);
    }

    ASSERT_EQ(numElements, octaspire_container_hash_map_get_number_of_elements(hashMap));

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_container_hash_map_element_t *element =
            octaspire_container_hash_map_get(hashMap, (uint32_t)i, &i);

        ASSERT_EQ(i,   octaspire_container_hash_map_element_get_hash(element));
        ASSERT_EQ(i,   *(size_t*)octaspire_container_hash_map_element_get_key(element));
        ASSERT_EQ(i,   *(size_t*)octaspire_container_hash_map_element_get_value(element));
    }

    octaspire_container_hash_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_container_hash_map_add_same_key_many_times_test(void)
{
    octaspire_container_hash_map_t *hashMap = octaspire_container_hash_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_container_hash_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_container_hash_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    size_t const key = 1024;

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT(octaspire_container_hash_map_put(
            hashMap,
            octaspire_helpers_calculate_murmur3_hash_for_size_t_argument(key),
            &key,
            &i));

        octaspire_container_hash_map_element_t * const element = octaspire_container_hash_map_get(
            hashMap,
            octaspire_helpers_calculate_murmur3_hash_for_size_t_argument(key),
            &key);

        ASSERT(element);

        ASSERT_EQ(key, *(size_t*)octaspire_container_hash_map_element_get_key(element));

        octaspire_container_vector_t * const values =
            octaspire_container_hash_map_element_get_values(element);

        ASSERT_EQ(i + 1,   octaspire_container_vector_get_length(values));

        for (size_t j = 0; j < octaspire_container_vector_get_length(values) ; ++j)
        {
            ASSERT_EQ(j,   *(size_t*)octaspire_container_vector_get_element_at(values, j));
        }
    }

    octaspire_container_hash_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_container_hash_map_new_allocation_failure_on_first_allocation_test(void)
{
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    octaspire_container_hash_map_t *hashMap = octaspire_container_hash_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_container_hash_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_container_hash_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT_FALSE(hashMap);
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_container_hash_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_container_hash_map_new_allocation_failure_on_second_allocation_test(void)
{
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 2, 0x01);
    ASSERT_EQ(2, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    octaspire_container_hash_map_t *hashMap = octaspire_container_hash_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_container_hash_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_container_hash_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT_FALSE(hashMap);
    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_container_hash_map_release(hashMap);
    hashMap = 0;

    PASS();
}

static bool octaspire_container_hash_map_new_test_key_compare_function_for_ostring_t_keys(
    void const * const key1,
    void const * const key2);

static uint32_t octaspire_container_hash_map_new_test_key_hash_function_for_ostring_t_keys(
    void const * const key);

static bool octaspire_container_hash_map_new_test_key_compare_function_for_ostring_t_keys(
    void const * const key1,
    void const * const key2)
{
    assert(key1);
    assert(key2);

    return octaspire_container_utf8_string_is_equal(
        (octaspire_container_utf8_string_t const * const)key1,
        (octaspire_container_utf8_string_t const * const)key2);
}

static uint32_t octaspire_container_hash_map_new_test_key_hash_function_for_ostring_t_keys(
    void const * const key)
{
    assert(key);
    return octaspire_container_utf8_string_get_hash((octaspire_container_utf8_string_t const * const)key);
}

TEST octaspire_container_hash_map_new_keys_ostring_t_and_values_ostring_t_test(void)
{
    octaspire_container_hash_map_t *hashMap = octaspire_container_hash_map_new(
        sizeof(octaspire_container_utf8_string_t *),
        true,
        sizeof(octaspire_container_utf8_string_t *),
        true,
        octaspire_container_hash_map_new_test_key_compare_function_for_ostring_t_keys,
        octaspire_container_hash_map_new_test_key_hash_function_for_ostring_t_keys,
        (octaspire_container_hash_map_element_callback_function_t)octaspire_container_utf8_string_release,
        (octaspire_container_hash_map_element_callback_function_t)octaspire_container_utf8_string_release,
        octaspireContainerHashMapTestAllocator);

    size_t const numElements = 32;

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t const hash = octaspire_container_utf8_string_get_hash(str);

        octaspire_container_utf8_string_t *cpyStr = octaspire_container_utf8_string_new_copy(str, octaspireContainerHashMapTestAllocator);
        ASSERT(octaspire_container_utf8_string_is_equal(str, cpyStr));
        octaspire_container_hash_map_put(hashMap, hash, &cpyStr, &str);

        ASSERT_EQ(i+1, octaspire_container_hash_map_get_number_of_elements(hashMap));
    }

    ASSERT_EQ(numElements, octaspire_container_hash_map_get_number_of_elements(hashMap));

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t hash = octaspire_container_utf8_string_get_hash(str);

        octaspire_container_hash_map_element_t *element =
            octaspire_container_hash_map_get(hashMap, hash, &str);

        ASSERT(element);

        ASSERT_EQ(hash, octaspire_container_hash_map_element_get_hash(element));

        ASSERT(octaspire_container_utf8_string_is_equal(str, (octaspire_container_utf8_string_t*)octaspire_container_hash_map_element_get_key(element)));

        ASSERT(octaspire_container_utf8_string_is_equal(str, (octaspire_container_utf8_string_t*)octaspire_container_hash_map_element_get_value(element)));

        octaspire_container_utf8_string_release(str);
        str = 0;
    }

    octaspire_container_hash_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_container_hash_map_new_with_octaspire_container_utf8_string_keys_test(void)
{
    octaspire_container_hash_map_t *hashMap =
        octaspire_container_hash_map_new_with_octaspire_container_utf8_string_keys(
            sizeof(octaspire_container_utf8_string_t *),
            true,
            (octaspire_container_hash_map_element_callback_function_t)
                octaspire_container_utf8_string_release,
            octaspireContainerHashMapTestAllocator);

    size_t const numElements = 32;

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t const hash = octaspire_container_utf8_string_get_hash(str);

        octaspire_container_utf8_string_t *cpyStr = octaspire_container_utf8_string_new_copy(str, octaspireContainerHashMapTestAllocator);
        ASSERT(octaspire_container_utf8_string_is_equal(str, cpyStr));
        octaspire_container_hash_map_put(hashMap, hash, &cpyStr, &str);

        ASSERT_EQ(i+1, octaspire_container_hash_map_get_number_of_elements(hashMap));
    }

    ASSERT_EQ(numElements, octaspire_container_hash_map_get_number_of_elements(hashMap));

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_container_utf8_string_t *str = octaspire_container_utf8_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t hash = octaspire_container_utf8_string_get_hash(str);

        octaspire_container_hash_map_element_t *element =
            octaspire_container_hash_map_get(hashMap, hash, &str);

        ASSERT(element);

        ASSERT_EQ(hash, octaspire_container_hash_map_element_get_hash(element));

        ASSERT(octaspire_container_utf8_string_is_equal(str, (octaspire_container_utf8_string_t*)octaspire_container_hash_map_element_get_key(element)));

        ASSERT(octaspire_container_utf8_string_is_equal(str, (octaspire_container_utf8_string_t*)octaspire_container_hash_map_element_get_value(element)));

        octaspire_container_utf8_string_release(str);
        str = 0;
    }

    octaspire_container_hash_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_container_hash_map_element_iterator_test(void)
{
    octaspire_container_hash_map_t *hashMap = octaspire_container_hash_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_container_hash_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_container_hash_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    octaspire_container_hash_map_element_iterator_t iterator =
        octaspire_container_hash_map_element_iterator_init(hashMap);

    ASSERT_EQ(hashMap, iterator.hashMap);
    ASSERT_EQ(0,       iterator.element);
    ASSERT_EQ(0,       iterator.bucketIndex);
    ASSERT_EQ(0,       iterator.elementInsideBucketIndex);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(octaspire_container_hash_map_element_iterator_next(&iterator));

        ASSERT_EQ(hashMap, iterator.hashMap);
        ASSERT_EQ(0,       iterator.element);
    }

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        uint32_t hash = (uint32_t)i;

        octaspire_container_hash_map_put(hashMap, hash, &i, &i);
    }

    ASSERT_EQ(numElements, octaspire_container_hash_map_get_number_of_elements(hashMap));

    iterator =
        octaspire_container_hash_map_element_iterator_init(hashMap);

    ASSERT_EQ(hashMap, iterator.hashMap);

    size_t counter = 0;
    while (iterator.element)
    {
        ASSERT_EQ(hashMap, iterator.hashMap);
        ASSERT_EQ(counter, octaspire_container_hash_map_element_get_hash(iterator.element));
        ASSERT_EQ(counter, *(size_t*)octaspire_container_hash_map_element_get_key(iterator.element));
        ASSERT_EQ(counter, *(size_t*)octaspire_container_hash_map_element_get_value(iterator.element));

        ++counter;
        octaspire_container_hash_map_element_iterator_next(&iterator);
    }

    ASSERT_EQ(numElements, counter);

    octaspire_container_hash_map_release(hashMap);
    hashMap = 0;

    PASS();
}

static size_t octaspireContainerHashMapSuiteNumTimesRun = 0;

GREATEST_SUITE(octaspire_container_hash_map_suite)
{
    octaspireContainerHashMapSuiteNumTimesRun = 0;

    octaspireContainerHashMapTestAllocator = octaspire_memory_allocator_new_create_region(
        OCTASPIRE_CORE_CONFIG_MEMORY_ALLOCATOR_REGION_MIN_BLOCK_SIZE_IN_OCTETS);

second_run:

    assert(octaspireContainerHashMapTestAllocator);

    RUN_TEST(octaspire_container_hash_map_element_new_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_container_hash_map_element_new_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_container_hash_map_element_new_allocation_failure_on_third_allocation_test);
    RUN_TEST(octaspire_container_hash_map_private_rehash_allocation_failure_on_first_allocation_test);
    //RUN_TEST(octaspire_container_hash_map_private_rehash_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_container_hash_map_new_keys_uint32_t_and_values_size_t_test);
    RUN_TEST(octaspire_container_hash_map_add_same_key_many_times_test);
    RUN_TEST(octaspire_container_hash_map_new_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_container_hash_map_new_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_container_hash_map_new_keys_ostring_t_and_values_ostring_t_test);
    RUN_TEST(octaspire_container_hash_map_new_with_octaspire_container_utf8_string_keys_test);
    RUN_TEST(octaspire_container_hash_map_element_iterator_test);

    octaspire_memory_allocator_release(octaspireContainerHashMapTestAllocator);
    octaspireContainerHashMapTestAllocator = 0;

    ++octaspireContainerHashMapSuiteNumTimesRun;

    if (octaspireContainerHashMapSuiteNumTimesRun < 2)
    {
        // Second run without region octaspireContainerHashMapTestAllocator

        octaspireContainerHashMapTestAllocator = octaspire_memory_allocator_new(0);

        goto second_run;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          ../test/test_container_hash_map.c
//////////////////////////////////////////////////////////////////////////////////////////////////





void octaspire_core_amalgamated_write_test_file(
    char const * const name,
    char const * const buffer,
    size_t const bufferSize)
{
    FILE *stream = fopen(name, "wb");

    if (!stream)
    {
        abort();
    }

    if (!buffer || !bufferSize)
    {
        if (fwrite("", sizeof(char), 0, stream) != 0)
        {
            fclose(stream);
            stream = 0;
            abort();
        }
    }
    else
    {
        if (fwrite(buffer, sizeof(char), bufferSize, stream) != bufferSize)
        {
            fclose(stream);
            stream = 0;
            abort();
        }
    }

    if (fclose(stream) != 0)
    {
        abort();
    }

    printf("  Wrote file '%s'\n", name);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    // This banner is created with figlet using font 'small'
    unsigned char octaspire_core_amalgamated_version_banner[] = {
      0x20, 0x20, 0x5f, 0x5f, 0x5f, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5f, 0x20,
      0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
      0x20, 0x20, 0x20, 0x5f, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
      0x20, 0x20, 0x20, 0x20, 0x5f, 0x5f, 0x5f, 0x20, 0x20, 0x20, 0x20, 0x20,
      0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x0a, 0x20, 0x2f, 0x20,
      0x5f, 0x20, 0x5c, 0x20, 0x5f, 0x5f, 0x7c, 0x20, 0x7c, 0x5f, 0x20, 0x5f,
      0x5f, 0x20, 0x5f, 0x20, 0x5f, 0x5f, 0x5f, 0x5f, 0x20, 0x5f, 0x5f, 0x28,
      0x5f, 0x29, 0x5f, 0x20, 0x5f, 0x20, 0x5f, 0x5f, 0x5f, 0x20, 0x20, 0x20,
      0x2f, 0x20, 0x5f, 0x5f, 0x7c, 0x5f, 0x5f, 0x5f, 0x20, 0x5f, 0x20, 0x5f,
      0x20, 0x5f, 0x5f, 0x5f, 0x20, 0x0a, 0x7c, 0x20, 0x28, 0x5f, 0x29, 0x20,
      0x2f, 0x20, 0x5f, 0x7c, 0x20, 0x20, 0x5f, 0x2f, 0x20, 0x5f, 0x60, 0x20,
      0x28, 0x5f, 0x2d, 0x3c, 0x20, 0x27, 0x5f, 0x20, 0x5c, 0x20, 0x7c, 0x20,
      0x27, 0x5f, 0x2f, 0x20, 0x2d, 0x5f, 0x29, 0x20, 0x7c, 0x20, 0x28, 0x5f,
      0x5f, 0x2f, 0x20, 0x5f, 0x20, 0x5c, 0x20, 0x27, 0x5f, 0x2f, 0x20, 0x2d,
      0x5f, 0x29, 0x0a, 0x20, 0x5c, 0x5f, 0x5f, 0x5f, 0x2f, 0x5c, 0x5f, 0x5f,
      0x7c, 0x5c, 0x5f, 0x5f, 0x5c, 0x5f, 0x5f, 0x2c, 0x5f, 0x2f, 0x5f, 0x5f,
      0x2f, 0x20, 0x2e, 0x5f, 0x5f, 0x2f, 0x5f, 0x7c, 0x5f, 0x7c, 0x20, 0x5c,
      0x5f, 0x5f, 0x5f, 0x7c, 0x20, 0x20, 0x5c, 0x5f, 0x5f, 0x5f, 0x5c, 0x5f,
      0x5f, 0x5f, 0x2f, 0x5f, 0x7c, 0x20, 0x5c, 0x5f, 0x5f, 0x5f, 0x7c, 0x0a,
      0x20, 0x20, 0x41, 0x6d, 0x61, 0x6c, 0x67, 0x61, 0x6d, 0x61, 0x74, 0x65,
      0x64, 0x20, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x7c, 0x5f, 0x7c,
      0x73, 0x74, 0x61, 0x6e, 0x64, 0x2d, 0x61, 0x6c, 0x6f, 0x6e, 0x65, 0x20,
      0x75, 0x6e, 0x69, 0x74, 0x20, 0x74, 0x65, 0x73, 0x74, 0x20, 0x72, 0x75,
      0x6e, 0x6e, 0x65, 0x72, 0x20, 0x20, 0x20, 0x20, 0x0a, 0x0a, '\0'
    };

    printf(
        "%s  %s\n\n",
        octaspire_core_amalgamated_version_banner,
        OCTASPIRE_CORE_CONFIG_VERSION_STR);

    printf(
        "  This is stand-alone unit test runner for the amalgamated version of\n"
        "  Octaspire Core. Some of the unit tests test reading of files from\n"
        "  the filesystem. The full source distribution has these files in\n"
        "  the 'test/resource' directory. But because this amalgamated\n"
        "  distribution can have only one file, to be able to run all\n"
        "  the tests succesfully something must be done. What do you\n"
        "  want to do? Select 'a', 'b', 'c' or any other key:\n"
        "\n"
        "  a) Let this program to write those files to disk to the current working\n"
        "     directory. All existing files with the same name will be OVERWRITTEN.\n"
        "     The files to be written are of form 'octaspire_XYZ_test', where XYZ\n"
        "     is the name of the test.\n"
        "\n"
        "  b) Let those tests to fail on missing files, or succeed if the files are\n"
        "     already present in the current working directory.\n"
        "\n"
        "  c) Abort and quit this program.\n"
        "\n"
        "  > ");

    int const c = getchar();

    switch (c)
    {
        case 'a':
        {
            printf("Writing test files to current working directory...\n");

            octaspire_core_amalgamated_write_test_file(
                "octaspire_helpers_path_to_buffer_failure_on_empty_file_test", 0, 0);



            char const octaspire_helpers_path_to_buffer_test[] = {
                0xc2, 0xa9, 0xe2, 0x89, 0xa0, 0xf0, 0x90, 0x80, 0x80
            };
            size_t const octaspire_helpers_path_to_buffer_test_len = 9;

            octaspire_core_amalgamated_write_test_file(
                "octaspire_helpers_path_to_buffer_test",
                octaspire_helpers_path_to_buffer_test,
                octaspire_helpers_path_to_buffer_test_len);


            char const octaspire_input_new_from_path_test[] = {
              0x61, 0x62, 0x63, 0xc2, 0xa9, 0xe2, 0x89, 0xa0, 0xf0, 0x90, 0x80, 0x80
            };
            size_t const octaspire_input_new_from_path_test_len = 12;

            octaspire_core_amalgamated_write_test_file(
                "octaspire_input_new_from_path_test",
                octaspire_input_new_from_path_test,
                octaspire_input_new_from_path_test_len);



            char const octaspire_stdio_fread_test[] = {
              0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x71, 0x77,
              0x65, 0x72, 0x74, 0x79, 0x75, 0x69, 0x6f, 0x70, 0x0a
            };
            size_t const octaspire_stdio_fread_test_len = 21;

            octaspire_core_amalgamated_write_test_file(
                "octaspire_stdio_fread_test",
                octaspire_stdio_fread_test,
                octaspire_stdio_fread_test_len);




            printf("Done.\n");
        }
        break;

        case 'b':
        {
            printf("Tests reading files will fail, if the required files are not available.\n");
        }
        break;

        case 'c':
        default:
        {
            printf("Going to quit now, as requested\n");
            return EXIT_FAILURE;
        }
        break;
    }

    GREATEST_MAIN_BEGIN();
    RUN_SUITE(octaspire_helpers_suite);
    RUN_SUITE(octaspire_utf8_suite);
    RUN_SUITE(octaspire_memory_suite);
    RUN_SUITE(octaspire_region_suite);
    RUN_SUITE(octaspire_stdio_suite);
    RUN_SUITE(octaspire_input_suite);
    RUN_SUITE(octaspire_container_vector_suite);
    RUN_SUITE(octaspire_container_utf8_string_suite);
    RUN_SUITE(octaspire_container_pair_suite);
    RUN_SUITE(octaspire_container_hash_map_suite);
    GREATEST_MAIN_END();
}


#endif // OCTASPIRE_CORE_AMALGAMATED_UNIT_TEST_IMPLEMENTATION

