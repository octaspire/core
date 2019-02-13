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
*******************************************************************************

  This file is amalgamated version of the header files, implementation files
  and unit tests of Octaspire Core. It is created automatically by a script.

                            DO NOT EDIT MANUALLY!

  Edit the separate .h and .c files in the source distribution and then let
  the script create this file again with the modifications.

******************************************************************************/
#ifndef OCTASPIRE_CORE_AMALGAMATED_H
#define OCTASPIRE_CORE_AMALGAMATED_H

#ifdef OCTASPIRE_PLAN9_IMPLEMENTATION

#include <u.h>
#include <libc.h>
#include <mp.h>
#include <stdio.h>
#include <ctype.h>

typedef long               int32_t;
typedef unsigned long      uint32_t;
typedef char               bool;
typedef char               int8_t;
typedef unsigned char      uint8_t;
typedef long               ptrdiff_t;
typedef unsigned long      size_t;
typedef unsigned long long uintmax_t;

#define true 1
#define false 0

#define CHAR_BIT 8
#define INT_MAX 2147483647
#define INT32_MAX 2147483647
#define UINTMAX_MAX 0xFFFFFFFF
#define va_copy(x,y) (x) = (y)
#define PRId32 "ld"
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void exit(int32_t const status)
{
    exits(status == 0 ? "" : "error");
}

int isnan(double const x)
{
    return x != x;
}

#else

#include <ctype.h>
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

#endif

#undef OCTASPIRE_CORE_CONFIG_TEST_RES_PATH
#define OCTASPIRE_CORE_CONFIG_TEST_RES_PATH ""

#ifdef OCTASPIRE_CORE_AMALGAMATED_UNIT_TEST_IMPLEMENTATION
#define OCTASPIRE_CORE_AMALGAMATED_IMPLEMENTATION 1
#endif

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/external/jenkins_one_at_a_time.h
//////////////////////////////////////////////////////////////////////////////////////////////////
// Based on public domain code from:
// burtleburtle.net/bob/hash/doobs.html
#ifndef OCTASPIRE_CORE_JENKINS_ONE_AT_A_TIME_H
#define OCTASPIRE_CORE_JENKINS_ONE_AT_A_TIME_H


#ifdef __cplusplus
extern "C"
{
#endif

uint32_t jenkins_one_at_a_time_hash(void const * const data, size_t const lengthInOctets);

#ifdef __cplusplus
}
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/external/jenkins_one_at_a_time.h
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/include/octaspire/core/octaspire_core_config.h
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
#define OCTASPIRE_CORE_CONFIG_VERSION_MINOR "119"
#define OCTASPIRE_CORE_CONFIG_VERSION_PATCH "1"

#define OCTASPIRE_CORE_CONFIG_VERSION_STR "Octaspire Core version " \
    OCTASPIRE_CORE_CONFIG_VERSION_MAJOR "." \
    OCTASPIRE_CORE_CONFIG_VERSION_MINOR "." \
    OCTASPIRE_CORE_CONFIG_VERSION_PATCH

#ifndef OCTASPIRE_CORE_CONFIG_TEST_RES_PATH
#define OCTASPIRE_CORE_CONFIG_TEST_RES_PATH ""
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/include/octaspire/core/octaspire_core_config.h
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/include/octaspire/core/octaspire_utf8.h
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
extern "C"       {
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
    octaspire_utf8_character_t * const result);

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
/* extern "C" */ }
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/include/octaspire/core/octaspire_utf8.h
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/include/octaspire/core/octaspire_memory.h
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
extern "C"       {
#endif

typedef void *(*octaspire_allocator_custom_malloc_function_t)(size_t size);
typedef void  (*octaspire_allocator_custom_free_function_t)(void *ptr);
typedef void *(*octaspire_allocator_custom_realloc_function_t)(void *ptr, size_t size);

typedef struct octaspire_allocator_config_t
{
    octaspire_allocator_custom_malloc_function_t  customMallocFunction;
    octaspire_allocator_custom_free_function_t    customFreeFunction;
    octaspire_allocator_custom_realloc_function_t customReallocFunction;
}
octaspire_allocator_config_t;

octaspire_allocator_config_t octaspire_allocator_config_default(void);


typedef struct octaspire_allocator_t octaspire_allocator_t;

octaspire_allocator_t *octaspire_allocator_new(
    octaspire_allocator_config_t const * config);

void octaspire_allocator_release(octaspire_allocator_t *self);

void *octaspire_allocator_malloc(
    octaspire_allocator_t *self,
    size_t const size);

void *octaspire_allocator_realloc(
    octaspire_allocator_t *self,
    void *ptr, size_t const size);

void octaspire_allocator_free(
    octaspire_allocator_t *self,
    void *ptr);

void octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
    octaspire_allocator_t *self,
    size_t const count,
    uint32_t const bitQueue0);

void octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged_when_larger_than_32(
    octaspire_allocator_t *self,
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

size_t octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
    octaspire_allocator_t const * const self);

#ifdef __cplusplus
/* extern "C" */ }
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/include/octaspire/core/octaspire_memory.h
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/include/octaspire/core/octaspire_vector.h
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
#ifndef OCTASPIRE_VECTOR_H
#define OCTASPIRE_VECTOR_H


#ifdef __cplusplus
extern "C"       {
#endif

typedef struct octaspire_vector_t octaspire_vector_t;

typedef void  (*octaspire_vector_element_callback_t)(void *element);

typedef int (*octaspire_vector_element_compare_function_t)(void const *a, void const *b);

octaspire_vector_t *octaspire_vector_new(
    size_t const elementSize,
    bool const elementIsPointer,
    octaspire_vector_element_callback_t elementReleaseCallback,
    octaspire_allocator_t *allocator);

octaspire_vector_t *octaspire_vector_new_for_octaspire_string_elements(
    octaspire_allocator_t *allocator);

octaspire_vector_t *octaspire_vector_new_with_preallocated_elements(
    size_t const elementSize,
    bool const elementIsPointer,
    size_t const numElementsPreAllocated,
    octaspire_vector_element_callback_t elementReleaseCallback,
    octaspire_allocator_t *allocator);

octaspire_vector_t *octaspire_vector_new_shallow_copy(
    octaspire_vector_t * other,
    octaspire_allocator_t * allocator);

void octaspire_vector_release(octaspire_vector_t *self);

// Vector can never be compacted smaller than this limit, if set
void octaspire_vector_set_compacting_limit_for_preallocated_elements(
    octaspire_vector_t * const self,
    size_t const numPreAllocatedElementsAtLeastPresentAtAnyMoment);

size_t octaspire_vector_get_length(
    octaspire_vector_t const * const self);

size_t octaspire_vector_get_length_in_octets(
    octaspire_vector_t const * const self);

bool octaspire_vector_is_empty(
    octaspire_vector_t const * const self);

bool octaspire_vector_remove_element_at(
    octaspire_vector_t * const self,
    ptrdiff_t const possiblyNegativeIndex);

void *octaspire_vector_get_element_at(
    octaspire_vector_t * const self,
    ptrdiff_t const possiblyNegativeIndex);

void const *octaspire_vector_get_element_at_const(
    octaspire_vector_t const * const self,
    ptrdiff_t const possiblyNegativeIndex);

void *octaspire_vector_get_raw_data_for_element_at(
    octaspire_vector_t * const self,
    ptrdiff_t const possiblyNegativeIndex);

void const *octaspire_vector_get_raw_data_for_element_at_const(
    octaspire_vector_t const * const self,
    ptrdiff_t const possiblyNegativeIndex);

size_t octaspire_vector_get_element_size_in_octets(
    octaspire_vector_t const * const self);

bool octaspire_vector_insert_element_before_the_element_at_index(
    octaspire_vector_t *self,
    void const *element,
    ptrdiff_t const possiblyNegativeIndex);

bool octaspire_vector_replace_element_at_index_or_push_back(
    octaspire_vector_t *self,
    void const *element,
    ptrdiff_t const possiblyNegativeIndex);

bool octaspire_vector_insert_element_at(
    octaspire_vector_t * const self,
    void const * const element,
    size_t const index);

bool octaspire_vector_replace_element_at(
    octaspire_vector_t *self,
    ptrdiff_t const possiblyNegativeIndex,
    void const *element);

bool octaspire_vector_push_front_element(
    octaspire_vector_t *self,
    void const *element);

bool octaspire_vector_push_back_element(
    octaspire_vector_t * const self,
    void const * const element);

bool octaspire_vector_push_back_char(
    octaspire_vector_t *self,
    char const element);

bool octaspire_vector_push_back_int(
    octaspire_vector_t *self,
    int const element);

void octaspire_vector_for_each(
    octaspire_vector_t *self,
    octaspire_vector_element_callback_t callback);

bool octaspire_vector_pop_back_element(
    octaspire_vector_t *self);

void *octaspire_vector_peek_back_element(
    octaspire_vector_t *self);

void const * octaspire_vector_peek_back_element_const(
    octaspire_vector_t const * const self);

bool octaspire_vector_pop_front_element(
    octaspire_vector_t *self);

void *octaspire_vector_peek_front_element(
    octaspire_vector_t *self);

void const * octaspire_vector_peek_front_element_const(
    octaspire_vector_t const * const self);

octaspire_vector_element_callback_t
octaspire_vector_get_element_release_callback_const(
    octaspire_vector_t const * const self);

bool octaspire_vector_clear(
    octaspire_vector_t * const self);

void octaspire_vector_sort(
    octaspire_vector_t * const self,
    octaspire_vector_element_compare_function_t elementCompareFunction);

bool octaspire_vector_is_valid_index(
    octaspire_vector_t const * const self,
    ptrdiff_t const index);

bool octaspire_vector_swap(
    octaspire_vector_t * const self,
    ptrdiff_t const indexA,
    ptrdiff_t const indexB);

/*
void octaspire_vector_debug_print(
    octaspire_vector_t const * const self,
    FILE * const stream);
*/


typedef struct octaspire_vector_permutation_iterator_t
    octaspire_vector_permutation_iterator_t;

octaspire_vector_permutation_iterator_t
*octaspire_vector_permutation_iterator_new(
    octaspire_vector_t * const vector,
    octaspire_allocator_t * const allocator);

void octaspire_vector_permutation_iterator_release(
    octaspire_vector_permutation_iterator_t * const self);

bool octaspire_vector_permutation_iterator_next(
    octaspire_vector_permutation_iterator_t * const self);

#ifdef __cplusplus
/* extern "C" */ }
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/include/octaspire/core/octaspire_vector.h
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/include/octaspire/core/octaspire_list.h
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
#ifndef OCTASPIRE_CONTAINER_LIST_H
#define OCTASPIRE_CONTAINER_LIST_H


#ifdef __cplusplus
extern "C"
{
#endif

typedef struct octaspire_list_node_t octaspire_list_node_t;

typedef void (*octaspire_list_element_callback_t)(void *element);

octaspire_list_node_t *octaspire_list_node_new(
    octaspire_list_node_t * const previous,
    octaspire_list_node_t * const next,
    size_t const elementSize,
    bool const elementIsPointer,
    octaspire_list_element_callback_t const elementReleaseCallback,
    void const * const element,
    octaspire_allocator_t * const allocator);

void octaspire_list_node_release(octaspire_list_node_t *self);

void *octaspire_list_node_get_element(octaspire_list_node_t *self);

void const *octaspire_list_node_get_element_const(
    octaspire_list_node_t const * const self);

size_t octaspire_list_node_get_size_of_element_in_octets(
    octaspire_list_node_t const * const self);

void octaspire_list_node_set_next(
    octaspire_list_node_t * const self,
    octaspire_list_node_t * const next);

octaspire_list_node_t *octaspire_list_node_get_next(
    octaspire_list_node_t * const self);

octaspire_list_node_t const *octaspire_list_node_get_next_const(
    octaspire_list_node_t const * const self);

void octaspire_list_node_set_previous(
    octaspire_list_node_t * const self,
    octaspire_list_node_t * const previous);

octaspire_list_node_t *octaspire_list_node_get_previous(
    octaspire_list_node_t * const self);

octaspire_list_node_t const *octaspire_list_node_get_previous_const(
    octaspire_list_node_t const * const self);



typedef struct octaspire_list_t octaspire_list_t;

octaspire_list_t *octaspire_list_new(
    size_t const elementSize,
    bool const elementIsPointer,
    octaspire_list_element_callback_t const elementReleaseCallback,
    octaspire_allocator_t *allocator);

void octaspire_list_release(octaspire_list_t *self);

octaspire_list_node_t *octaspire_list_get_front(
    octaspire_list_t *self);

octaspire_list_node_t const *octaspire_list_get_front_const(
    octaspire_list_t const * const self);

octaspire_list_node_t *octaspire_list_get_back(
    octaspire_list_t *self);

octaspire_list_node_t const *octaspire_list_get_back_const(
    octaspire_list_t const * const self);

bool octaspire_list_push_front(
    octaspire_list_t *self,
    void const * const element);

bool octaspire_list_push_back(
    octaspire_list_t *self,
    void const * const element);

bool octaspire_list_pop_front(
    octaspire_list_t * const self);

bool octaspire_list_pop_back(
    octaspire_list_t * const self);

bool octaspire_list_remove(
    octaspire_list_t * const self,
    octaspire_list_node_t * const node);

bool octaspire_list_clear(
    octaspire_list_t * const self);

size_t octaspire_list_get_length(
    octaspire_list_t const * const self);

bool octaspire_list_is_empty(
    octaspire_list_t const * const self);

octaspire_list_node_t *octaspire_list_get_at(
    octaspire_list_t * const self,
    ptrdiff_t const possiblyNegativeIndex);

octaspire_list_node_t const *octaspire_list_get_at_const(
    octaspire_list_t const * const self,
    ptrdiff_t const possiblyNegativeIndex);


typedef struct octaspire_list_node_iterator_t
{
    octaspire_list_t      *list;
    octaspire_list_node_t *currentNode;
}
octaspire_list_node_iterator_t;

octaspire_list_node_iterator_t octaspire_list_node_iterator_init(
    octaspire_list_t * const self);

bool octaspire_list_node_iterator_next(
    octaspire_list_node_iterator_t * const self);

#ifdef __cplusplus
}
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/include/octaspire/core/octaspire_list.h
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/include/octaspire/core/octaspire_queue.h
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
#ifndef OCTASPIRE_QUEUE_H
#define OCTASPIRE_QUEUE_H


#ifdef __cplusplus
extern "C"
{
#endif

typedef void (*octaspire_queue_element_callback_t)(void *element);

typedef struct octaspire_queue_t octaspire_queue_t;

octaspire_queue_t *octaspire_queue_new(
    size_t const elementSize,
    bool const elementIsPointer,
    octaspire_queue_element_callback_t const elementReleaseCallback,
    octaspire_allocator_t *allocator);

octaspire_queue_t *octaspire_queue_new_with_max_length(
    size_t const maxLength,
    size_t const elementSize,
    bool const elementIsPointer,
    octaspire_queue_element_callback_t const elementReleaseCallback,
    octaspire_allocator_t *allocator);

void octaspire_queue_release(octaspire_queue_t *self);

void *octaspire_queue_peek(
    octaspire_queue_t * const self);

void const *octaspire_queue_peek_const(
    octaspire_queue_t const * const self);

bool octaspire_queue_pop(
    octaspire_queue_t * const self);

bool octaspire_queue_push(
    octaspire_queue_t *self,
    void const * const element);

bool octaspire_queue_clear(
    octaspire_queue_t * const self);

size_t octaspire_queue_get_length(
    octaspire_queue_t const * const self);

bool octaspire_queue_is_empty(
    octaspire_queue_t const * const self);

void *octaspire_queue_get_at(
    octaspire_queue_t * const self,
    ptrdiff_t const possiblyNegativeIndex);

void const *octaspire_queue_get_at_const(
    octaspire_queue_t const * const self,
    ptrdiff_t const possiblyNegativeIndex);

size_t octaspire_queue_get_max_length(
    octaspire_queue_t const * const self);

bool octaspire_queue_has_max_length(
    octaspire_queue_t const * const self);

bool octaspire_queue_set_max_length(
    octaspire_queue_t * const self,
    size_t maxLength);

bool octaspire_queue_set_has_max_length(
    octaspire_queue_t * const self,
    bool hasMaxLength);



typedef struct octaspire_queue_iterator_t
{
    octaspire_queue_t *queue;
    octaspire_list_node_iterator_t iterator;
}
octaspire_queue_iterator_t;

octaspire_queue_iterator_t octaspire_queue_iterator_init(
    octaspire_queue_t * const self);

bool octaspire_queue_iterator_next(
    octaspire_queue_iterator_t * const self);

#ifdef __cplusplus
}
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/include/octaspire/core/octaspire_queue.h
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/include/octaspire/core/octaspire_string.h
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
#ifndef OCTASPIRE_STRING_H
#define OCTASPIRE_STRING_H


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

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/include/octaspire/core/octaspire_string.h
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/include/octaspire/core/octaspire_pair.h
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

typedef struct octaspire_pair_t octaspire_pair_t;

typedef void (*octaspire_pair_element_callback_t)(void *element);

size_t octaspire_pair_t_get_sizeof(void);

octaspire_pair_t *octaspire_pair_new(
    size_t const firstElementSize,
    bool const firstElementIsPointer,
    size_t const secondElementSize,
    bool const secondElementIsPointer,
    octaspire_pair_element_callback_t firstElementReleaseCallback,
    octaspire_pair_element_callback_t secondElementReleaseCallback,
    octaspire_allocator_t *allocator);

octaspire_pair_t *octaspire_pair_new_shallow_copy(
    octaspire_pair_t   *other,
    octaspire_allocator_t *allocator);

void octaspire_pair_release(octaspire_pair_t *self);

void *octaspire_pair_get_first(octaspire_pair_t *self);

void const *octaspire_pair_get_first_const(octaspire_pair_t const * const self);

void *octaspire_pair_get_second(octaspire_pair_t *self);

void const *octaspire_pair_get_second_const(
    octaspire_pair_t const * const self);

size_t octaspire_pair_get_size_of_first_element_in_octets(
    octaspire_pair_t const * const self);

size_t octaspire_pair_get_size_of_second_element_in_octets(
    octaspire_pair_t const * const self);

void octaspire_pair_set(
    octaspire_pair_t *self,
    void const *first,
    void const *second);

void octaspire_pair_set_first(
    octaspire_pair_t *self,
    void const *first);

void octaspire_pair_set_second(
    octaspire_pair_t *self,
    void const *second);

bool octaspire_pair_set_first_to_void_pointer(
    octaspire_pair_t *self,
    void *element);

bool octaspire_pair_set_second_to_void_pointer(
    octaspire_pair_t *self,
    void *second);

void octaspire_pair_clear(
    octaspire_pair_t * const self);

#ifdef __cplusplus
}
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/include/octaspire/core/octaspire_pair.h
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/include/octaspire/core/octaspire_stdio.h
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
extern "C"       {
#endif

typedef struct octaspire_stdio_t octaspire_stdio_t;

octaspire_stdio_t *octaspire_stdio_new(octaspire_allocator_t *allocator);

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

octaspire_string_t *octaspire_stdio_read_line(octaspire_stdio_t *self, FILE *stream);

#ifdef __cplusplus
/* extern "C" */ }
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/include/octaspire/core/octaspire_stdio.h
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/include/octaspire/core/octaspire_input.h
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
extern "C"       {
#endif

typedef struct octaspire_input_t octaspire_input_t;

octaspire_input_t *octaspire_input_new_from_c_string(
    char const * const str,
    octaspire_allocator_t *allocator);

octaspire_input_t *octaspire_input_new_from_buffer(
    char const * const buffer,
    size_t const lengthInOctets,
    octaspire_allocator_t *allocator);

octaspire_input_t *octaspire_input_new_from_path(
    char const * const path,
    octaspire_allocator_t *octaspireAllocator,
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
    octaspire_string_t const * const str);

bool octaspire_input_push_back_from_c_string(octaspire_input_t * const self, char const * const str);

size_t octaspire_input_get_line_number(octaspire_input_t const * const self);
size_t octaspire_input_get_column_number(octaspire_input_t const * const self);
size_t octaspire_input_get_ucs_character_index(octaspire_input_t const * const self);

void octaspire_input_print(octaspire_input_t const * const self);

#ifdef __cplusplus
/* extern "C" */ }
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/include/octaspire/core/octaspire_input.h
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/include/octaspire/core/octaspire_map.h
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
#ifndef OCTASPIRE_MAP_H
#define OCTASPIRE_MAP_H


#ifdef __cplusplus
extern "C"       {
#endif

// Hash map element
typedef struct octaspire_map_element_t octaspire_map_element_t;

octaspire_map_element_t *octaspire_map_element_new(
    uint32_t const hash,
    size_t const keySizeInOctets,
    bool const keyIsPointer,
    void const * const key,
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    void const * const value,
    octaspire_allocator_t * const allocator);

void octaspire_map_element_release(octaspire_map_element_t *self);

uint32_t octaspire_map_element_get_hash(
    octaspire_map_element_t const * const self);

void *octaspire_map_element_get_key(
    octaspire_map_element_t const * const self);

octaspire_vector_t *octaspire_map_element_get_values(
    octaspire_map_element_t * const self);

void *octaspire_map_element_get_value(
    octaspire_map_element_t const * const self);

void const *octaspire_map_element_get_key_const(
    octaspire_map_element_t const * const self);

void const *octaspire_map_element_get_value_const(
    octaspire_map_element_t const * const self);


// Hash map
typedef struct octaspire_map_t octaspire_map_t;

typedef bool (*octaspire_map_key_compare_function_t)(
    void const * const key1,
    void const * const key2);

typedef uint32_t (*octaspire_map_key_hash_function_t)(
    void const * const key);

typedef void (*octaspire_map_element_callback_t)(
    void * element);

octaspire_map_t *octaspire_map_new(
    size_t const keySizeInOctets,
    bool const keyIsPointer,
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    octaspire_map_key_compare_function_t keyCompareFunction,
    octaspire_map_key_hash_function_t keyHashFunction,
    octaspire_map_element_callback_t keyReleaseCallback,
    octaspire_map_element_callback_t valueReleaseCallback,
    octaspire_allocator_t *allocator);

octaspire_map_t *octaspire_map_new_with_octaspire_string_keys(
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    octaspire_map_element_callback_t valueReleaseCallback,
    octaspire_allocator_t *allocator);

octaspire_map_t *octaspire_map_new_with_size_t_keys(
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    octaspire_map_element_callback_t valueReleaseCallback,
    octaspire_allocator_t *allocator);

void octaspire_map_release(octaspire_map_t *self);

bool octaspire_map_remove(
    octaspire_map_t *self,
    uint32_t const hash,
    void const * const key);

bool octaspire_map_clear(
    octaspire_map_t * const self);

bool octaspire_map_add_hash_map(
    octaspire_map_t * const self,
    octaspire_map_t * const other);

bool octaspire_map_put(
    octaspire_map_t *self,
    uint32_t const hash,
    void const * const key,
    void const * const value);

octaspire_map_element_t *octaspire_map_get(
    octaspire_map_t *self,
    uint32_t const hash,
    void const * const key);

octaspire_map_element_t const * octaspire_map_get_const(
    octaspire_map_t const * const self,
    uint32_t const hash,
    void const * const key);

bool octaspire_map_is_empty(
    octaspire_map_t const * const self);

size_t octaspire_map_get_number_of_elements(
    octaspire_map_t const * const self);

octaspire_map_element_t *octaspire_map_get_at_index(
    octaspire_map_t * const self,
    ptrdiff_t const possiblyNegativeIndex);


typedef struct octaspire_map_element_iterator_t
{
    octaspire_map_t *hashMap;
    octaspire_map_element_t *element;
    size_t bucketIndex;
    size_t elementInsideBucketIndex;
}
octaspire_map_element_iterator_t;

octaspire_map_element_iterator_t octaspire_map_element_iterator_init(
    octaspire_map_t * const self);

bool octaspire_map_element_iterator_next(
    octaspire_map_element_iterator_t * const self);


typedef struct octaspire_map_element_const_iterator_t
{
    octaspire_map_t const *hashMap;
    octaspire_map_element_t const *element;
    size_t bucketIndex;
    size_t elementInsideBucketIndex;
}
octaspire_map_element_const_iterator_t;

octaspire_map_element_const_iterator_t
octaspire_map_element_const_iterator_init(
    octaspire_map_t const * const self);

bool octaspire_map_element_const_iterator_next(
    octaspire_map_element_const_iterator_t * const self);



uint32_t octaspire_map_helper_size_t_get_hash(
    size_t const value);

#ifdef __cplusplus
/* extern "C" */ }
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/include/octaspire/core/octaspire_map.h
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/include/octaspire/core/octaspire_helpers.h
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
extern "C"       {
#endif

#define OCTASPIRE_HELPERS_UNUSED_PARAMETER(x) (void)(x)

bool  octaspire_helpers_test_bit(uint32_t const bitSet, size_t const index);

char *octaspire_helpers_path_to_buffer(
    char const * const path,
    size_t *octetsAllocated,
    octaspire_allocator_t *allocator,
    octaspire_stdio_t *stdio);

uint32_t octaspire_helpers_calculate_hash_for_size_t_argument(size_t const value);
uint32_t octaspire_helpers_calculate_hash_for_bool_argument(bool const value);
uint32_t octaspire_helpers_calculate_hash_for_int32_t_argument(int32_t const value);
uint32_t octaspire_helpers_calculate_hash_for_double_argument(double const value);
uint32_t octaspire_helpers_calculate_hash_for_void_pointer_argument(void const * const value);

uint32_t octaspire_helpers_calculate_hash_for_memory_buffer_argument(
    void const * const value,
    size_t const lengthInOctets);

size_t octaspire_helpers_character_digit_to_number(uint32_t const c);

size_t octaspire_helpers_min_size_t(size_t const a, size_t const b);
int octaspire_helpers_min_int(int const a, int const b);

size_t octaspire_helpers_min3_size_t(
    size_t const a,
    size_t const b,
    size_t const c);

int octaspire_helpers_min3_int(
    int const a,
    int const b,
    int const c);

size_t octaspire_helpers_max_size_t(size_t const a, size_t const b);

void octaspire_helpers_verify_true(bool const condition);
void octaspire_helpers_verify_null(void const * const ptr);
void octaspire_helpers_verify_not_null(void const * const ptr);

void octaspire_helpers_verify_not_null_void_funptr_void_ptr_const(
        void (*ptr)(void * const));

float octaspire_helpers_maxf(float const a, float const b);
float octaspire_helpers_ceilf(float const value);

bool octaspire_helpers_is_even_size_t(size_t const value);
bool octaspire_helpers_is_odd_size_t( size_t const value);

uint8_t octaspire_helpers_get_char_or_default_from_buf(
    uint8_t const * const input,
    size_t const inLen,
    size_t const getAtIndex,
    uint8_t const defaultChar);

size_t octaspire_helpers_measure_length_of_last_line(
    octaspire_string_t const * const str);

octaspire_vector_t * octaspire_helpers_base64_decode(
    char const * const input,
    int32_t const inputLenOrNegativeToMeasure,
    octaspire_allocator_t * const allocator);

octaspire_string_t * octaspire_helpers_base64_encode(
    char const * const input,
    size_t const inLen,
    size_t const lineLen,
    octaspire_allocator_t * const allocator);

#ifdef __cplusplus
/* extern "C" */ }
#endif

#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/include/octaspire/core/octaspire_helpers.h
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/include/octaspire/core/octaspire_semver.h
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
#ifndef OCTASPIRE_SEMVER_H
#define OCTASPIRE_SEMVER_H



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

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/include/octaspire/core/octaspire_semver.h
//////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef OCTASPIRE_CORE_AMALGAMATED_IMPLEMENTATION
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/external/jenkins_one_at_a_time.c
//////////////////////////////////////////////////////////////////////////////////////////////////
// Based on public domain code from:
// burtleburtle.net/bob/hash/doobs.html


uint32_t jenkins_one_at_a_time_hash(void const * const data, size_t const lengthInOctets)
{
    uint32_t hash = 0;

    for (size_t i = 0; i < lengthInOctets; ++i)
    {
        hash += ((uint8_t const * const)data)[i];
        hash += (hash << 10);
        hash ^= (hash >>  6);
    }

    hash += (hash <<  3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/external/jenkins_one_at_a_time.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/src/octaspire_memory.c
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


struct octaspire_allocator_t
{
    size_t                                               numberOfFutureAllocationsToBeRigged;
    size_t                                               bitIndex;
    uint32_t                                             bitQueue[20];
    octaspire_allocator_custom_malloc_function_t  customMallocFunction;
    octaspire_allocator_custom_free_function_t    customFreeFunction;
    octaspire_allocator_custom_realloc_function_t customReallocFunction;
};

octaspire_allocator_config_t octaspire_allocator_config_default(void)
{
    octaspire_allocator_config_t result =
    {
        .customMallocFunction  = 0,
        .customFreeFunction    = 0,
        .customReallocFunction = 0
    };

    return result;
}

octaspire_allocator_t *octaspire_allocator_new(
    octaspire_allocator_config_t const * config)
{
    octaspire_allocator_config_t defaultConfig = octaspire_allocator_config_default();

    if (!config)
    {
        config = &defaultConfig;
    }

    size_t const size = sizeof(octaspire_allocator_t);

    octaspire_allocator_t *self = malloc(size);

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

    self->customMallocFunction  = config->customMallocFunction;
    self->customFreeFunction    = config->customFreeFunction;
    self->customReallocFunction = config->customReallocFunction;

    return self;
}

void octaspire_allocator_release(octaspire_allocator_t *self)
{
    if (!self)
    {
        return;
    }

    free(self);
}

bool octaspire_allocator_private_test_bit(octaspire_allocator_t const * const self);

bool octaspire_allocator_private_test_bit(octaspire_allocator_t const * const self)
{
    size_t const arrayIndex = (size_t)((float)self->bitIndex / 32.0f);
    size_t const bitIndex   = self->bitIndex % 8;
    assert(bitIndex < 32);
    assert(arrayIndex < (sizeof(self->bitQueue) / sizeof(self->bitQueue[0])));
    return octaspire_helpers_test_bit(self->bitQueue[arrayIndex], bitIndex);
}

void *octaspire_allocator_malloc(
    octaspire_allocator_t *self,
    size_t const size)
{
    if (self->numberOfFutureAllocationsToBeRigged)
    {
        --(self->numberOfFutureAllocationsToBeRigged);

        if (!octaspire_allocator_private_test_bit(self))
        {
            ++(self->bitIndex);
            return 0;
        }

        ++(self->bitIndex);
    }

    assert(size);

    void * const result =
        self->customMallocFunction ? self->customMallocFunction(size) : malloc(size);

    if (!result)
    {
        return result;
    }

    if (!self->customMallocFunction)
    {
        if (result != memset(result, 0, size))
        {
            abort();
        }
    }

    return result;
}

void *octaspire_allocator_realloc(
    octaspire_allocator_t *self,
    void *ptr, size_t const size)
{
    if (self->numberOfFutureAllocationsToBeRigged)
    {
        --(self->numberOfFutureAllocationsToBeRigged);

        if (!octaspire_allocator_private_test_bit(self))
        {
            ++(self->bitIndex);
            return 0;
        }

        ++(self->bitIndex);
    }

    return self->customReallocFunction ? self->customReallocFunction(ptr, size) : realloc(ptr, size);
}

void octaspire_allocator_free(
    octaspire_allocator_t *self,
    void *ptr)
{
    assert(self);

    self->customFreeFunction ? self->customFreeFunction(ptr) : free(ptr);
}

void octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
    octaspire_allocator_t *self,
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

void octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged_when_larger_than_32(
    octaspire_allocator_t *self,
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

size_t octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
    octaspire_allocator_t const * const self)
{
    return self->numberOfFutureAllocationsToBeRigged;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/src/octaspire_memory.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/src/octaspire_helpers.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/src/octaspire_helpers.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/src/octaspire_utf8.c
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
static uint32_t octaspire_utf8_private_high_order_bits  (octaspire_utf8_character_range_t const range);

static int octaspire_utf8_private_octets_in_next(char const * const text, size_t const textLengthInOctets);

static int octaspire_utf8_private_octets_in_next_from_buffer(
    char const * const buffer,
    size_t const lengthInOctets,
    size_t const currentIndex);

octaspire_utf8_decode_status_t octaspire_utf8_private_decode_helper(
    char const * const buffer,
    size_t const numOctetsNeeded,
    size_t const numOctetsAvailable,
    uint32_t * const result);

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

octaspire_utf8_encode_status_t octaspire_utf8_encode_character(
    uint32_t const character,
    octaspire_utf8_character_t * const result)
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
            uint32_t const mask = 0x7F;       // Least significant 7 bits on
            bitset |= ((bitset & ~mask) | (character & mask));

            result->numoctets = 1;
        }
        break;

        case OCTASPIRE_UTF8_CHARACTER_RANGE_SECOND:
        {
            uint32_t const mask = 0x3F;     // Least significant 6 bits on
            bitset |= ((bitset & ~mask) | (character & mask));

            uint32_t const bitsetMask = 0x1F00; // Least significant bits 8,9,10,11,12 on
            uint32_t const charMask   = 0x7C0;  // Least significant bits 6,7, 8, 9,10 on
            bitset |= ((bitset & ~bitsetMask) | (((character & charMask) << 2) & bitsetMask));

            result->numoctets = 2;
        }
        break;

        case OCTASPIRE_UTF8_CHARACTER_RANGE_THIRD:
        {
            uint32_t mask = 0x3F;       // Least significant 6 bits on
            bitset |= ((bitset & ~mask) | (character & mask));

            uint32_t bitsetMask = 0x3F00; // Least significant bits 8,9,10,11,12,13 on
            uint32_t charMask   = 0xFC0;  // Least significant bits 6,7, 8, 9,10,11 on
            bitset |= ((bitset & ~bitsetMask) | (((character & charMask) << 2) & bitsetMask));

            bitsetMask = 0xF0000; // Least significant bits 16,17,18,19 on
            charMask   = 0xF000;  // Least significant bits 12,13,14,15 on
            bitset |= ((bitset & ~bitsetMask) | (((character & charMask) << 4) & bitsetMask));

            result->numoctets = 3;
        }
        break;

        case OCTASPIRE_UTF8_CHARACTER_RANGE_FOURTH:
        {
            uint32_t mask = 0x3F;       // Least significant 6 bits on
            bitset |= ((bitset & ~mask) | (character & mask));

            uint32_t bitsetMask = 0x3F00; // Least significant bits 8,9,10,11,12,13 on
            uint32_t charMask   = 0xFC0;  // Least significant bits 6,7, 8, 9,10,11 on
            bitset |= ((bitset & ~bitsetMask) | (((character & charMask) << 2) & bitsetMask));

            bitsetMask = 0x3F0000; // Least significant bits 16,17,18,19,20,21 on
            charMask   = 0x3F000; // Least significant bits 12,13,14,15,16,17 on
            bitset |= ((bitset & ~bitsetMask) | (((character & charMask) << 4) & bitsetMask));

            bitsetMask = 0x7000000; // Least significant bits 24,25,26 on
            charMask   = 0x1C0000;  // Most significant bits 18,19,20 on
            bitset |= ((bitset & ~bitsetMask) | (((character & charMask) << 6) & bitsetMask));

            result->numoctets = 4;
        }
        break;

        case OCTASPIRE_UTF8_CHARACTER_RANGE_ILLEGAL:
        {
            return OCTASPIRE_UTF8_ENCODE_STATUS_ILLEGAL_CHARACTER_NUMBER;
        }
    }

    uint8_t const resultMask = 0xFF; // First 8 bits on
    uint32_t      inputMask  = 0xFF; // Least significant 8 bits on
    result->octets[3] = ((result->octets[3] & ~resultMask) | (bitset & inputMask));

    inputMask  = 0x0000FF00; // Lest significant 8 bits off then 8 bits on
    result->octets[2] = ((result->octets[2] & ~resultMask) | ((bitset & inputMask) >> 8));

    inputMask  = 0x00FF0000; // Least significant 16 bits off then 8 bits on
    result->octets[1] = ((result->octets[1] & ~resultMask) | ((bitset & inputMask) >> 16));

    inputMask  = 0xFF000000; // Least significant 24 bits off then 8 bits on
    result->octets[0] = ((result->octets[0] & ~resultMask) | ((bitset & inputMask) >> 24));

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

static int octaspire_utf8_private_octets_in_next_from_buffer(
    char const * const buffer,
    size_t const lengthInOctets,
    size_t const currentIndex)
{
    if (!buffer || currentIndex >= lengthInOctets)
        return 0;

    size_t const octetsAvailable = lengthInOctets - currentIndex;

    uint8_t const octet0 = buffer[currentIndex];
    if (((octet0 >> 7) & 1) == 0) // If 0xxxxxx
    {
        return 1;
    }

    if (((octet0 >> 5) & 7) == 6) // If 110xxxxx
    {
        if (octetsAvailable < 2)
        {
            return -1;
        }

        uint8_t const octet1 = buffer[currentIndex + 1];
        if (((octet1 >> 6) & 3) == 2) // If 10xxxxxx
        {
            return 2;
        }

        return -1;
    }

    if (((octet0 >> 4) & 15) == 14) // If 1110xxxx
    {
        if (octetsAvailable < 3)
        {
            return -1;
        }

        uint8_t const octet1 = buffer[currentIndex + 1];
        uint8_t const octet2 = buffer[currentIndex + 2];

        if ((((octet1 >> 6) & 3) == 2) && (((octet2 >> 6) & 3) == 2)) // If 10xxxxxx && 10xxxxxx
        {
            return 3;
        }

        return -1;
    }

    if (((octet0 >> 3) & 31) == 30) // If 11110xxx
    {
        if (octetsAvailable < 4)
        {
            return -1;
        }

        uint8_t const octet1 = buffer[currentIndex + 1];
        uint8_t const octet2 = buffer[currentIndex + 2];
        uint8_t const octet3 = buffer[currentIndex + 3];

        // If 10xxxxxx && 10xxxxxx && 10xxxxxx
        if ((((octet1 >> 6) & 3) == 2) && (((octet2 >> 6) & 3) == 2) && (((octet3 >> 6) & 3) == 2))
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
    uint32_t * const result)
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

            uint32_t const resultMask = 0x7F; // 7 least significant bits on
            uint8_t  const inputMask  = 0x7F; // 7 least significant bits on
            *result = 0;
            *result |= ((*result & ~resultMask) | (buffer[0] & inputMask));
        }
        break;

        case 2:
        {
            // 110xxxxx 10xxxxxx

            uint32_t resultMask = 0x7C0; // 6 least significant bits off, then 5 on
            uint8_t  inputMask  = 0x1F;  // 5 least significant bits on
            *result = 0;
            *result |= ((*result & ~resultMask) | ((buffer[0] & inputMask) << 6));

            resultMask = 0x3F; // 6 least significant bits on
            inputMask  = 0x3F; // 6 least significant bits on
            *result |= ((*result & ~resultMask) | (buffer[1] & inputMask));

            if (*result <= 0x7F)
            {
                return OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER;
            }
        }
        break;

        case 3:
        {
            // 1110xxxx 10xxxxxx 10xxxxxx

            uint32_t resultMask = 0xF000; // 12 least significant bits off, then 4 on
            uint8_t  inputMask  = 0xF;    // 4 least significant bits on
            *result = 0;
            *result |= ((*result & ~resultMask) | ((buffer[0] & inputMask) << 12));

            resultMask = 0xFC0; // 6 least significant bits off, then 6 on
            inputMask  = 0x3F;  // 6 least significant bits on
            *result |= ((*result & ~resultMask) | ((buffer[1] & inputMask) << 6));

            resultMask = 0x3F; // 6 least significant bits on
            inputMask  = 0x3F; // 6 least significant bits on
            *result |= ((*result & ~resultMask) | (buffer[2] & inputMask));

            if (*result <= 2047)
            {
                return OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER;
            }
        }
        break;

        case 4:
        {
            // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

            uint32_t resultMask = 0x1C0000; // 18 least significant bits off, then 3 on
            uint8_t  inputMask  = 0x7;      // 3 least significant bits on
            *result = 0;
            *result |= ((*result & ~resultMask) | ((buffer[0] & inputMask) << 18));

            resultMask = 0x3F000; // 12 least significant bits off, then 6 on
            inputMask  = 0x3F;    // 6 least significant bits on
            *result |= ((*result & ~resultMask) | ((buffer[1] & inputMask) << 12));

            resultMask = 0xFC0; // 6 least significant bits off, then 6 on
            inputMask  = 0x3F;  // 6 least significant bits on
            *result |= ((*result & ~resultMask) | ((buffer[2] & inputMask) << 6));

            resultMask = 0x3F; // 6 least significant bits on
            inputMask  = 0x3F; // 6 least significant bits on
            *result |= ((*result & ~resultMask) | (buffer[3] & inputMask));

            if (*result <= 65535)
            {
                return OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER;
            }
        }
        break;
    }

    return OCTASPIRE_UTF8_DECODE_STATUS_OK;
}

octaspire_utf8_decode_status_t octaspire_utf8_decode_character(
    char const * const text,
    size_t const textLengthInOctets,
    uint32_t *result,
    int *numoctets)
{
    *result = 0;
    *numoctets = octaspire_utf8_private_octets_in_next(text, textLengthInOctets);

    size_t const numoctetsRef = *numoctets;

    if (numoctetsRef <= 0 || numoctetsRef > 4)
    {
        if (!text || textLengthInOctets == 0 || text[0] == '\0')
        {
            return OCTASPIRE_UTF8_DECODE_STATUS_INPUT_IS_NULL;
        }

        return OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS;
    }

    if (numoctetsRef > textLengthInOctets)
    {
        return OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS;
    }

    return octaspire_utf8_private_decode_helper(text, numoctetsRef, numoctetsRef, result);
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

    *numoctets =
        octaspire_utf8_private_octets_in_next_from_buffer(buffer, bufferLengthInOctets, currentIndex);

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
// END OF          dev/src/octaspire_utf8.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/src/octaspire_vector.c
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


struct octaspire_vector_t
{
    void   *elements;
    size_t  elementSize;
    size_t  numElements;
    size_t  numAllocated;
    size_t  compactingLimitForAllocated;
    octaspire_vector_element_callback_t elementReleaseCallback;
    octaspire_allocator_t *allocator;
    bool    elementIsPointer;
    char    padding[7];
};

static size_t const OCTASPIRE_VECTOR_INITIAL_SIZE = 1;

static void *octaspire_vector_private_index_to_pointer(
    octaspire_vector_t * const self,
    size_t const index)
{
    assert(self->elements);
    assert(index < self->numAllocated);
    return ((char*)self->elements) + (self->elementSize * index);
}

static void const *octaspire_vector_private_index_to_pointer_const(
    octaspire_vector_t const * const self,
    size_t const index)
{
    return ((char const * const)self->elements) + (self->elementSize * index);
}

static bool octaspire_vector_private_grow(
    octaspire_vector_t *self,
    float const factor)
{
    size_t const newNumAllocated = (size_t)(self->numAllocated * octaspire_helpers_maxf(2, factor));

    void *newElements = octaspire_allocator_realloc(
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

static bool octaspire_vector_private_compact(
    octaspire_vector_t *self)
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
        self->numElements ? self->numElements : OCTASPIRE_VECTOR_INITIAL_SIZE;

    if (newNumAllocated < self->compactingLimitForAllocated)
    {
        newNumAllocated = self->compactingLimitForAllocated;
    }

    void *newElements = octaspire_allocator_realloc(
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

octaspire_vector_t *octaspire_vector_new(
    size_t const elementSize,
    bool const elementIsPointer,
    octaspire_vector_element_callback_t elementReleaseCallback,
    octaspire_allocator_t *allocator)
{
    return octaspire_vector_new_with_preallocated_elements(
        elementSize,
        elementIsPointer,
        OCTASPIRE_VECTOR_INITIAL_SIZE,
        elementReleaseCallback,
        allocator);
}

octaspire_vector_t *octaspire_vector_new_for_octaspire_string_elements(
    octaspire_allocator_t *allocator)
{
    return octaspire_vector_new(
        sizeof(octaspire_string_t*),
        true,
        (octaspire_vector_element_callback_t)octaspire_string_release,
        allocator);
}

octaspire_vector_t *octaspire_vector_new_with_preallocated_elements(
    size_t const elementSize,
    bool const elementIsPointer,
    size_t const numElementsPreAllocated,
    octaspire_vector_element_callback_t elementReleaseCallback,
    octaspire_allocator_t *allocator)
{
    octaspire_vector_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_vector_t));

    if (!self)
    {
        return self;
    }

    self->allocator        = allocator;
    self->elementSize      = elementSize ? elementSize : sizeof(char);
    self->elementIsPointer = elementIsPointer;
    self->numElements      = 0;

    self->numAllocated = numElementsPreAllocated ?
        numElementsPreAllocated : OCTASPIRE_VECTOR_INITIAL_SIZE;

    self->compactingLimitForAllocated = self->numAllocated;

    self->elements     =
        octaspire_allocator_malloc(self->allocator, self->elementSize * self->numAllocated);

    if (!self->elements)
    {
        octaspire_vector_release(self);
        self = 0;
        return 0;
    }

    self->elementReleaseCallback  = elementReleaseCallback;

    return self;
}

octaspire_vector_t *octaspire_vector_new_shallow_copy(
    octaspire_vector_t * other,
    octaspire_allocator_t * allocator)
{
    octaspire_vector_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_vector_t));

    if (!self)
    {
        return self;
    }

    self->allocator    = allocator;

    self->elementSize  = octaspire_vector_get_element_size_in_octets(other);
    self->numElements  = octaspire_vector_get_length(other);
    self->numAllocated = self->numElements;
    self->compactingLimitForAllocated = other->compactingLimitForAllocated;

    // This is here to prevent assert on octaspire_allocator_malloc
    // on 0 size of allocation. Should that check be removed, or this?
    if (self->numAllocated == 0)
    {
        self->numAllocated = 1;
    }

    self->elements     = octaspire_allocator_malloc(
        self->allocator,
        self->elementSize * self->numAllocated);

    if (!self->elements)
    {
        octaspire_vector_release(self);
        self = 0;
        return 0;
    }

    self->elementReleaseCallback =
        octaspire_vector_get_element_release_callback_const(other);

    if (memcpy(
        self->elements,
        octaspire_vector_get_element_at_const(other, 0),
        (self->numElements * self->elementSize)) != self->elements)
    {
        abort();
    }

    return self;
}

void octaspire_vector_release(octaspire_vector_t *self)
{
    if (!self)
    {
        return;
    }

    if (self->elementReleaseCallback)
    {
        octaspire_vector_for_each(self, self->elementReleaseCallback);
    }

    assert(self->allocator);

    octaspire_allocator_free(self->allocator, self->elements);
    octaspire_allocator_free(self->allocator, self);
}

// Vector can never be compacted smaller than this limit, if set
void octaspire_vector_set_compacting_limit_for_preallocated_elements(
    octaspire_vector_t * const self,
    size_t const numPreAllocatedElementsAtLeastPresentAtAnyMoment)
{
    self->compactingLimitForAllocated = numPreAllocatedElementsAtLeastPresentAtAnyMoment;
}

size_t octaspire_vector_get_length(
    octaspire_vector_t const * const self)
{
    assert(self);
    return self->numElements;
}

size_t octaspire_vector_get_length_in_octets(
    octaspire_vector_t const * const self)
{
    return self->numElements * self->elementSize;
}

bool octaspire_vector_is_empty(
    octaspire_vector_t const * const self)
{
    return (self->numElements == 0);
}

typedef struct octaspire_vector_private_index_t
{
    size_t index;
    bool   isValid;
    char   padding[7];

} octaspire_vector_private_index_t;

static octaspire_vector_private_index_t octaspire_vector_private_is_index_valid(
    octaspire_vector_t const * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    octaspire_vector_private_index_t result = {.isValid=true, .index=(size_t)possiblyNegativeIndex};

    size_t const selfLen = octaspire_vector_get_length(self);

    if (possiblyNegativeIndex < 0)
    {
        ptrdiff_t const tmpIndex = (ptrdiff_t)selfLen + possiblyNegativeIndex;

        if (tmpIndex >= 0 && (size_t)tmpIndex < selfLen)
        {
            result.index = (size_t)tmpIndex;
            return result;
        }
    }

    if ((size_t)possiblyNegativeIndex < selfLen)
    {
        return result;
    }

    result.isValid = false;
    result.index   = 0;
    return result;
}

bool octaspire_vector_remove_element_at(
    octaspire_vector_t * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    octaspire_vector_private_index_t const realIndex =
        octaspire_vector_private_is_index_valid(self, possiblyNegativeIndex);

    if (!realIndex.isValid)
    {
        return false;
    }

    if (self->elementReleaseCallback)
    {
        if (self->elementIsPointer)
        {
            void* const * const tmpPtr =
                octaspire_vector_private_index_to_pointer(
                    self,
                    realIndex.index);

            octaspire_helpers_verify_not_null(tmpPtr);

            self->elementReleaseCallback(*tmpPtr);
        }
        else
        {
            self->elementReleaseCallback(
                octaspire_vector_private_index_to_pointer(self, realIndex.index));
        }
    }

    if ((realIndex.index + 1) != self->numElements)
    {
        size_t const numOctetsToMove = (self->numElements - realIndex.index - 1) * self->elementSize;
        void *moveTarget = octaspire_vector_private_index_to_pointer(self, realIndex.index);
        void *moveSource = octaspire_vector_private_index_to_pointer(self, realIndex.index + 1);

        if (moveTarget != memmove(moveTarget, moveSource, numOctetsToMove))
        {
            abort();
        }
    }

    --(self->numElements);

    return true;
}

void *octaspire_vector_get_element_at(
    octaspire_vector_t * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    void * const result =
        octaspire_vector_get_raw_data_for_element_at(
            self,
            possiblyNegativeIndex);

    if (!result)
    {
        return result;
    }

    if (self->elementIsPointer)
    {
        return *(void**)result;
    }

    return result;
}

void const *octaspire_vector_get_element_at_const(
    octaspire_vector_t const * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    void const * const result =
        octaspire_vector_get_raw_data_for_element_at_const(
            self,
            possiblyNegativeIndex);

    if (!result)
    {
        return result;
    }

    if (self->elementIsPointer)
    {
        octaspire_helpers_verify_not_null(result);
        return *(void const * const *)result;
    }

    return result;
}

void *octaspire_vector_get_raw_data_for_element_at(
    octaspire_vector_t * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    octaspire_vector_private_index_t const realIndex =
        octaspire_vector_private_is_index_valid(self, possiblyNegativeIndex);

    if (!realIndex.isValid)
    {
        return 0;
    }

    return octaspire_vector_private_index_to_pointer(self, realIndex.index);
}

void const *octaspire_vector_get_raw_data_for_element_at_const(
    octaspire_vector_t const * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    octaspire_vector_private_index_t const realIndex =
        octaspire_vector_private_is_index_valid(self, possiblyNegativeIndex);

    if (!realIndex.isValid)
    {
        return 0;
    }

    return octaspire_vector_private_index_to_pointer_const(
        self,
        realIndex.index);
}

size_t octaspire_vector_get_element_size_in_octets(
    octaspire_vector_t const * const self)
{
    return self->elementSize;
}

bool octaspire_vector_insert_element_before_the_element_at_index(
    octaspire_vector_t *self,
    void const *element,
    ptrdiff_t const possiblyNegativeIndex)
{
    octaspire_vector_private_index_t const realIndex =
        octaspire_vector_private_is_index_valid(
            self,
            possiblyNegativeIndex);

    if (!realIndex.isValid)
    {
        return false;
    }

    assert(realIndex.index < octaspire_vector_get_length(self));

    // Make room for the new element
    if (self->numElements >= self->numAllocated)
    {
        if (!octaspire_vector_private_grow(self, 2))
        {
            return false;
        }
    }

    size_t const numOctetsToMove = (self->numElements - realIndex.index) * self->elementSize;
    void *moveTarget = octaspire_vector_private_index_to_pointer(self, realIndex.index + 1);
    void *moveSource = octaspire_vector_private_index_to_pointer(self, realIndex.index);

    if (moveTarget != memmove(moveTarget, moveSource, numOctetsToMove))
    {
        abort();
    }

    // Copy the new element into the vector
    void *copyTarget = octaspire_vector_private_index_to_pointer(self, realIndex.index);

    if (copyTarget != memcpy(copyTarget, element, self->elementSize))
    {
        abort();
    }

    ++(self->numElements);

    return true;
}

bool octaspire_vector_replace_element_at_index_or_push_back(
    octaspire_vector_t *self,
    void const *element,
    ptrdiff_t const possiblyNegativeIndex)
{
    octaspire_vector_private_index_t const realIndex =
        octaspire_vector_private_is_index_valid(
            self,
            possiblyNegativeIndex);

    if (!realIndex.isValid)
    {
        return octaspire_vector_push_back_element(self, element);
    }

    return octaspire_vector_insert_element_at(self, element, realIndex.index);
}

bool octaspire_vector_insert_element_at(
    octaspire_vector_t * const self,
    void const * const element,
    size_t const index)
{
    size_t const originalNumElements = self->numElements;

    while (index >= self->numAllocated)
    {
        if (!octaspire_vector_private_grow(
                self,
                octaspire_helpers_ceilf((float)index / (float)self->numAllocated)))
        {
            return false;
        }
    }

    // octaspire_vector_private_grow initializes new memory into zero,
    // so no need do it here again.

    long const numAdded = (index - originalNumElements);
    if (numAdded > 0)
    {
        self->numElements += numAdded;
    }

    void *target = octaspire_vector_private_index_to_pointer(self, index);

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

bool octaspire_vector_replace_element_at(
    octaspire_vector_t *self,
    ptrdiff_t const possiblyNegativeIndex,
    void const *element)
{
    octaspire_vector_private_index_t const realIndex =
        octaspire_vector_private_is_index_valid(
            self,
            possiblyNegativeIndex);

    if (!realIndex.isValid)
    {
        return false;
    }

    if (self->elementReleaseCallback)
    {
        if (self->elementIsPointer)
        {
            void* const * const tmpPtr =
                octaspire_vector_private_index_to_pointer(
                    self,
                    realIndex.index);

            octaspire_helpers_verify_not_null(tmpPtr);
            self->elementReleaseCallback(*tmpPtr);
        }
        else
        {
            self->elementReleaseCallback(
                octaspire_vector_private_index_to_pointer(self, realIndex.index));
        }
    }

    return octaspire_vector_insert_element_at(self, element, realIndex.index);
}

bool octaspire_vector_push_front_element(
    octaspire_vector_t *self,
    void const *element)
{
    if (octaspire_vector_is_empty(self))
    {
        return octaspire_vector_push_back_element(self, element);
    }

    return octaspire_vector_insert_element_before_the_element_at_index(
        self,
        element,
        0);
}

bool octaspire_vector_push_back_element(
    octaspire_vector_t * const self,
    void const * const element)
{
    return octaspire_vector_insert_element_at(
        self,
        element,
        octaspire_vector_get_length(self));
}

bool octaspire_vector_push_back_char(
    octaspire_vector_t *self,
    char const element)
{
    if (self->elementSize != sizeof(element))
    {
        return false;
    }

    return octaspire_vector_insert_element_at(
        self,
        &element,
        octaspire_vector_get_length(self));
}

bool octaspire_vector_push_back_int(
    octaspire_vector_t *self,
    int const element)
{
    if (self->elementSize != sizeof(element))
    {
        return false;
    }

    return octaspire_vector_insert_element_at(
        self,
        &element,
        octaspire_vector_get_length(self));
}

void octaspire_vector_for_each(
    octaspire_vector_t *self,
    octaspire_vector_element_callback_t callback)
{
    assert(self);
    assert(callback);

    for (size_t i = 0; i < octaspire_vector_get_length(self); ++i)
    {
        callback(octaspire_vector_get_element_at(self, (ptrdiff_t)i));
    }
}

bool octaspire_vector_pop_back_element(
    octaspire_vector_t *self)
{
    if (octaspire_vector_is_empty(self))
    {
        return false;
    }

    if (!octaspire_vector_remove_element_at(self, -1))
    {
        return false;
    }

    return octaspire_vector_private_compact(self);
}

void *octaspire_vector_peek_back_element(
    octaspire_vector_t *self)
{
    if (octaspire_vector_is_empty(self))
    {
        return 0;
    }

    return octaspire_vector_get_element_at(
        self,
        (ptrdiff_t)(octaspire_vector_get_length(self) - 1));
}

void const * octaspire_vector_peek_back_element_const(
    octaspire_vector_t const * const self)
{
    if (octaspire_vector_is_empty(self))
    {
        return 0;
    }

    return octaspire_vector_get_element_at_const(
        self,
        (ptrdiff_t)(octaspire_vector_get_length(self) - 1));
}

bool octaspire_vector_pop_front_element(
    octaspire_vector_t *self)
{
    if (octaspire_vector_is_empty(self))
    {
        return false;
    }

    if (!octaspire_vector_remove_element_at(self, 0))
    {
        return false;
    }

    return octaspire_vector_private_compact(self);
}

void *octaspire_vector_peek_front_element(
    octaspire_vector_t *self)
{
    if (octaspire_vector_is_empty(self))
    {
        return 0;
    }

    return octaspire_vector_get_element_at(self, 0);
}

void const * octaspire_vector_peek_front_element_const(
    octaspire_vector_t const * const self)
{
    if (octaspire_vector_is_empty(self))
    {
        return 0;
    }

    return octaspire_vector_get_element_at_const(self, 0);
}

octaspire_vector_element_callback_t
octaspire_vector_get_element_release_callback_const(octaspire_vector_t const * const self)
{
    return self->elementReleaseCallback;
}

bool octaspire_vector_clear(
    octaspire_vector_t * const self)
{
    if (octaspire_vector_is_empty(self))
    {
        return true;
    }

    while (!octaspire_vector_is_empty(self))
    {
        if (!octaspire_vector_remove_element_at(self, -1))
        {
            return false;
        }
    }

    return octaspire_vector_private_compact(self);
}

void octaspire_vector_sort(
    octaspire_vector_t * const self,
    octaspire_vector_element_compare_function_t elementCompareFunction)
{
    qsort(
        self->elements,
        octaspire_vector_get_length(self),
        octaspire_vector_get_element_size_in_octets(self),
        elementCompareFunction);
}

bool octaspire_vector_is_valid_index(
    octaspire_vector_t const * const self,
    ptrdiff_t const index)
{
    octaspire_vector_private_index_t result =
        octaspire_vector_private_is_index_valid(self, index);

    return result.isValid;
}

bool octaspire_vector_swap(
    octaspire_vector_t * const self,
    ptrdiff_t const indexA,
    ptrdiff_t const indexB)
{
    if (!octaspire_vector_is_valid_index(self, indexA))
    {
        return false;
    }

    if (!octaspire_vector_is_valid_index(self, indexB))
    {
        return false;
    }

    void *tmpBuffer =
        octaspire_allocator_malloc(self->allocator, self->elementSize);

    if (!tmpBuffer)
    {
        return false;
    }

    void * const elementA =
        octaspire_vector_get_raw_data_for_element_at(self, indexA);

    void * const elementB =
        octaspire_vector_get_raw_data_for_element_at(self, indexB);

    if (tmpBuffer != memcpy(tmpBuffer, elementA, self->elementSize))
    {
        abort();
    }

    if (elementA != memcpy(elementA, elementB, self->elementSize))
    {
        abort();
    }

    if (elementB != memcpy(elementB, tmpBuffer, self->elementSize))
    {
        abort();
    }

    octaspire_allocator_free(self->allocator, tmpBuffer);
    tmpBuffer = 0;

    return true;
}

/*
void octaspire_vector_debug_print(
    octaspire_vector_t const * const self,
    FILE * const stream)
{
    octaspire_helpers_verify_not_null(self);
    octaspire_helpers_verify_not_null(stream);

    fprintf(stream, "[");

    for (size_t i = 0; i < octaspire_vector_get_length(self); ++i)
    {
        char const * const ptr =
            octaspire_vector_private_index_to_pointer_const(
                self,
                i);

        for (size_t j = 0;
             j < octaspire_vector_get_element_size_in_octets(self);
             ++j)
        {
            unsigned int const tmpUint = (unsigned int)*(ptr + j);
            fprintf(stream, "%02X", tmpUint);
        }

        if ((i + 1) < octaspire_vector_get_length(self))
        {
            fprintf(stream, "|");
        }
    }

    fprintf(stream, "]\n");
}
*/



struct octaspire_vector_permutation_iterator_t
{
    octaspire_allocator_t        *allocator;
    octaspire_vector_t *vector;
    octaspire_vector_t *counts;
    size_t                        stepsLeft;
    size_t                        i;
};

octaspire_vector_permutation_iterator_t
*octaspire_vector_permutation_iterator_new(
    octaspire_vector_t * const vector,
    octaspire_allocator_t * const allocator)
{
    octaspire_vector_permutation_iterator_t *self =
        octaspire_allocator_malloc(
            allocator,
            sizeof(octaspire_vector_permutation_iterator_t));

    if (!self)
    {
        return self;
    }

    self->allocator        = allocator;
    self->vector           = vector;

    self->counts = octaspire_vector_new(sizeof(int), false, 0, allocator);

    if (!self->counts)
    {
        octaspire_vector_permutation_iterator_release(self);
        self = 0;
        return 0;
    }

    self->stepsLeft     = octaspire_vector_get_length(self->vector);
    self->i             = 1;

    for (size_t i = 0; i < self->stepsLeft; ++i)
    {
        int const zero = 0;
        if (!octaspire_vector_push_back_element(self->counts, &zero))
        {
            octaspire_vector_permutation_iterator_release(self);
            self = 0;
            return 0;
        }
    }

    return self;
}

void octaspire_vector_permutation_iterator_release(
    octaspire_vector_permutation_iterator_t * const self)
{
    if (!self)
    {
        return;
    }

    octaspire_vector_release(self->counts);
    self->counts = 0;

    octaspire_allocator_free(self->allocator, self);
}

bool octaspire_vector_permutation_iterator_next(
    octaspire_vector_permutation_iterator_t * const self)
{
    octaspire_helpers_verify_not_null(self);
    octaspire_helpers_verify_not_null(self->vector);
    octaspire_helpers_verify_not_null(self->counts);

    octaspire_helpers_verify_true(
        octaspire_vector_get_length(self->counts) ==
        octaspire_vector_get_length(self->vector));

    while (self->i < octaspire_vector_get_length(self->vector))
    {
        int ci = *(int const * const) octaspire_vector_get_element_at(
            self->counts,
            (ptrdiff_t)self->i);

        if (ci < (int)self->i)
        {
            if (self->i % 2 == 0)
            {
                octaspire_helpers_verify_true(octaspire_vector_swap(
                        self->vector,
                        0,
                        (ptrdiff_t)self->i));
            }
            else
            {
                octaspire_helpers_verify_true(octaspire_vector_swap(
                        self->vector,
                        ci,
                        (ptrdiff_t)self->i));
            }

            ++ci;

            octaspire_helpers_verify_true(
                octaspire_vector_replace_element_at(
                    self->counts,
                    (ptrdiff_t)self->i,
                    &ci));

            self->i = 1;

            if (self->stepsLeft == 0)
            {
                return true;
            }

            --(self->stepsLeft);

            return true;
        }
        else
        {
            ci = 0;

            octaspire_helpers_verify_true(
                octaspire_vector_replace_element_at(
                    self->counts,
                    (ptrdiff_t)self->i,
                    &ci));

            ++(self->i);
        }
    }

    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/src/octaspire_vector.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/src/octaspire_list.c
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

struct octaspire_list_node_t
{
    void                                        *element;
    octaspire_list_node_t             *next;
    octaspire_list_node_t             *previous;
    octaspire_allocator_t                       *allocator;
    size_t                                       elementSize;
    octaspire_list_element_callback_t  elementReleaseCallback;
    bool                                         elementIsPointer;
    char                                         padding[7];
};

octaspire_list_node_t *octaspire_list_node_new(
    octaspire_list_node_t * const previous,
    octaspire_list_node_t * const next,
    size_t const elementSize,
    bool const elementIsPointer,
    octaspire_list_element_callback_t const elementReleaseCallback,
    void const * const element,
    octaspire_allocator_t * const allocator)
{
    octaspire_list_node_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_list_node_t));

    if (!self)
    {
        return self;
    }

    self->allocator              = allocator;
    self->elementSize            = elementSize;
    self->elementIsPointer       = elementIsPointer;
    self->elementReleaseCallback = elementReleaseCallback;
    self->next                   = next;
    self->previous               = previous;

    self->element = octaspire_allocator_malloc(self->allocator, elementSize);

    if (!self->element)
    {
        octaspire_list_node_release(self);
        self = 0;
        return self;
    }

    if (self->element != memcpy(self->element, element, self->elementSize))
    {
        octaspire_list_node_release(self);
        self = 0;
        return self;
    }

    return self;
}

void octaspire_list_node_release(octaspire_list_node_t *self)
{
    if (!self)
    {
        return;
    }

    if (self->elementReleaseCallback)
    {
        self->elementReleaseCallback(self->elementIsPointer ? *(void**)self->element : self->element);
    }

    octaspire_allocator_free(self->allocator, self->element);
    self->element = 0;

    octaspire_allocator_free(self->allocator, self);
}

void *octaspire_list_node_get_element(octaspire_list_node_t *self)
{
    octaspire_helpers_verify_not_null(self);

    if (!self->element)
    {
        return self->element;
    }

    return self->elementIsPointer ? *(void**)self->element : self->element;
}

void const *octaspire_list_node_get_element_const(
    octaspire_list_node_t const * const self)
{
    octaspire_helpers_verify_not_null(self);

    if (!self->element)
    {
        return self->element;
    }

    return self->elementIsPointer ? *(void**)self->element : self->element;
}

size_t octaspire_list_node_get_size_of_element_in_octets(
    octaspire_list_node_t const * const self)
{
    octaspire_helpers_verify_not_null(self);
    return self->elementSize;
}

void octaspire_list_node_set_next(
    octaspire_list_node_t * const self,
    octaspire_list_node_t * const next)
{
    octaspire_helpers_verify_not_null(self);
    self->next = next;
}

octaspire_list_node_t *octaspire_list_node_get_next(
    octaspire_list_node_t * const self)
{
    octaspire_helpers_verify_not_null(self);
    return self->next;
}

octaspire_list_node_t const *octaspire_list_node_get_next_const(
    octaspire_list_node_t const * const self)
{
    octaspire_helpers_verify_not_null(self);
    return self->next;
}

void octaspire_list_node_set_previous(
    octaspire_list_node_t * const self,
    octaspire_list_node_t * const previous)
{
    octaspire_helpers_verify_not_null(self);
    self->previous = previous;
}

octaspire_list_node_t *octaspire_list_node_get_previous(
    octaspire_list_node_t * const self)
{
    octaspire_helpers_verify_not_null(self);
    return self->previous;
}

octaspire_list_node_t const *octaspire_list_node_get_previous_const(
    octaspire_list_node_t const * const self)
{
    octaspire_helpers_verify_not_null(self);
    return self->previous;
}


struct octaspire_list_t
{
    octaspire_allocator_t                       *allocator;
    octaspire_list_node_t             *front;
    octaspire_list_node_t             *back;
    size_t                                       elementSize;
    octaspire_list_element_callback_t  elementReleaseCallback;
    size_t                                       numElements;
    bool                                         elementIsPointer;
    char                                         padding[7];
};

octaspire_list_t *octaspire_list_new(
    size_t const elementSize,
    bool const elementIsPointer,
    octaspire_list_element_callback_t const elementReleaseCallback,
    octaspire_allocator_t *allocator)
{
    octaspire_list_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_list_t));

    if (!self)
    {
        return self;
    }

    self->allocator              = allocator;
    self->front                  = 0;
    self->back                   = 0;
    self->elementSize            = elementSize;
    self->elementReleaseCallback = elementReleaseCallback;
    self->numElements            = 0;
    self->elementIsPointer       = elementIsPointer;

    return self;
}

void octaspire_list_release(octaspire_list_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_helpers_verify_true(octaspire_list_clear(self));
    octaspire_allocator_free(self->allocator, self);
}

octaspire_list_node_t *octaspire_list_get_front(
    octaspire_list_t *self)
{
    octaspire_helpers_verify_not_null(self);
    return self->front;
}

octaspire_list_node_t const *octaspire_list_get_front_const(
    octaspire_list_t const * const self)
{
    octaspire_helpers_verify_not_null(self);
    return self->front;
}

octaspire_list_node_t *octaspire_list_get_back(
    octaspire_list_t *self)
{
    octaspire_helpers_verify_not_null(self);
    return self->back;
}

octaspire_list_node_t const *octaspire_list_get_back_const(
    octaspire_list_t const * const self)
{
    octaspire_helpers_verify_not_null(self);
    return self->back;
}

bool octaspire_list_push_front(
    octaspire_list_t *self,
    void const * const element)
{
    octaspire_helpers_verify_not_null(self);

    octaspire_list_node_t *newFirst = octaspire_list_node_new(
        0,
        self->front,
        self->elementSize,
        self->elementIsPointer,
        self->elementReleaseCallback,
        element,
        self->allocator);

    if (!newFirst)
    {
        return false;
    }

    if (self->front)
    {
        octaspire_list_node_set_previous(self->front, newFirst);
    }

    self->front = newFirst;

    if (octaspire_list_get_length(self) == 0)
    {
        self->back = self->front;
    }

    ++(self->numElements);

    return true;
}

bool octaspire_list_push_back(
    octaspire_list_t *self,
    void const * const element)
{
    octaspire_helpers_verify_not_null(self);

    octaspire_list_node_t *newLast = octaspire_list_node_new(
        self->back,
        0,
        self->elementSize,
        self->elementIsPointer,
        self->elementReleaseCallback,
        element,
        self->allocator);

    if (!newLast)
    {
        return false;
    }

    if (self->back)
    {
        octaspire_list_node_set_next(self->back, newLast);
    }

    self->back = newLast;

    if (octaspire_list_get_length(self) == 0)
    {
        self->front = self->back;
    }

    // Sanity checks
    if (self->numElements > 0)
    {
        octaspire_helpers_verify_not_null(octaspire_list_node_get_previous(self->back));
    }
    else
    {
        octaspire_helpers_verify_null(octaspire_list_node_get_previous(self->back));
    }

    ++(self->numElements);

    return true;
}

bool octaspire_list_pop_front(
    octaspire_list_t * const self)
{
    octaspire_helpers_verify_not_null(self);

    if (self->front)
    {
        octaspire_list_node_t *oldFirst = self->front;

        self->front = octaspire_list_node_get_next(self->front);

        if (self->front)
        {
            octaspire_list_node_set_previous(self->front, 0);
        }

        octaspire_list_node_set_next(oldFirst, 0);

        octaspire_helpers_verify_null(octaspire_list_node_get_previous(oldFirst));
        octaspire_helpers_verify_true(self->numElements > 0);

        --(self->numElements);

        if (octaspire_list_get_length(self) == 0)
        {
            self->back = self->front;
        }

        octaspire_list_node_release(oldFirst);
        oldFirst = 0;

        return true;
    }

    return true;
}

bool octaspire_list_pop_back(
    octaspire_list_t * const self)
{
    octaspire_helpers_verify_not_null(self);

    if (self->back)
    {
        octaspire_list_node_t *oldLast = self->back;

        self->back = octaspire_list_node_get_previous(self->back);

        if (self->back)
        {
            octaspire_list_node_set_next(self->back, 0);
        }

        octaspire_list_node_set_previous(oldLast, 0);

        octaspire_helpers_verify_null(octaspire_list_node_get_next(oldLast));
        octaspire_helpers_verify_true(self->numElements > 0);

        --(self->numElements);

        if (octaspire_list_get_length(self) == 0)
        {
            self->front = self->back;
        }

        octaspire_list_node_release(oldLast);
        oldLast = 0;

        return true;
    }

    return true;
}

bool octaspire_list_remove(
    octaspire_list_t * const self,
    octaspire_list_node_t * const node)
{
    octaspire_helpers_verify_not_null(self);

    if (node == octaspire_list_get_front_const(self))
    {
        return octaspire_list_pop_front(self);
    }
    else if (node == octaspire_list_get_back_const(self))
    {
        return octaspire_list_pop_back(self);
    }
    else
    {
        octaspire_list_node_t * const prev =
            octaspire_list_node_get_previous(node);

        octaspire_list_node_t * const next =
            octaspire_list_node_get_next(node);

        if (prev)
        {
            octaspire_list_node_set_next(prev, next);
        }

        if (next)
        {
            octaspire_list_node_set_previous(next, prev);
        }

        octaspire_list_node_set_next(node, 0);
        octaspire_list_node_set_previous(node, 0);

        octaspire_helpers_verify_true(self->numElements > 0);

        --(self->numElements);

        if (octaspire_list_get_length(self) == 0)
        {
            self->front = self->back;
        }

        octaspire_list_node_release(node);
        return true;
    }
}

bool octaspire_list_clear(
    octaspire_list_t * const self)
{
    octaspire_helpers_verify_not_null(self);

    while (!octaspire_list_is_empty(self))
    {
        if (!octaspire_list_pop_front(self))
        {
            return false;
        }

    }

    return true;
}

size_t octaspire_list_get_length(
    octaspire_list_t const * const self)
{
    octaspire_helpers_verify_not_null(self);
    return self->numElements;
}

bool octaspire_list_is_empty(
    octaspire_list_t const * const self)
{
    return (self->front == 0);
}

octaspire_list_node_t *octaspire_list_get_at(
    octaspire_list_t * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    octaspire_helpers_verify_not_null(self);

    if (possiblyNegativeIndex < 0)
    {
        size_t const index = (size_t)(-(possiblyNegativeIndex + 1));
        size_t counter = 0;
        octaspire_list_node_t * node = octaspire_list_get_back(self);

        while (true)
        {
            if (counter == index)
            {
                return node;
            }

            node = octaspire_list_node_get_previous(node);

            if (!node)
            {
                break;
            }

            ++counter;
        }

        return 0;
    }
    else
    {
        size_t const index = (size_t)possiblyNegativeIndex;
        size_t counter = 0;
        octaspire_list_node_t * node = octaspire_list_get_front(self);

        while (true)
        {
            if (counter == index)
            {
                return node;
            }

            node = octaspire_list_node_get_next(node);

            if (!node)
            {
                break;
            }

            ++counter;
        }

        return 0;
    }
}

octaspire_list_node_t const *octaspire_list_get_at_const(
    octaspire_list_t const * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    octaspire_helpers_verify_not_null(self);

    if (possiblyNegativeIndex < 0)
    {
        size_t const index = (size_t)(-(possiblyNegativeIndex + 1));
        size_t counter = 0;

        octaspire_list_node_t const * node =
            octaspire_list_get_back_const(self);

        while (true)
        {
            if (counter == index)
            {
                return node;
            }

            node = octaspire_list_node_get_previous_const(node);

            if (!node)
            {
                break;
            }

            ++counter;
        }

        return 0;
    }
    else
    {
        size_t const index = (size_t)possiblyNegativeIndex;
        size_t counter = 0;
        octaspire_list_node_t const * node =
            octaspire_list_get_front_const(self);

        while (true)
        {
            if (counter == index)
            {
                return node;
            }

            node = octaspire_list_node_get_next_const(node);

            if (!node)
            {
                break;
            }

            ++counter;
        }

        return 0;
    }
}


octaspire_list_node_iterator_t octaspire_list_node_iterator_init(
    octaspire_list_t * const self)
{
    octaspire_list_node_iterator_t iterator;

    iterator.list = self;
    iterator.currentNode = octaspire_list_get_front(self);

    return iterator;
}

bool octaspire_list_node_iterator_next(
    octaspire_list_node_iterator_t * const self)
{
    if (!self->currentNode)
    {
        return false;
    }

    self->currentNode = octaspire_list_node_get_next(self->currentNode);

    return (self->currentNode != 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/src/octaspire_list.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/src/octaspire_queue.c
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

struct octaspire_queue_t
{
    octaspire_allocator_t      *allocator;
    octaspire_list_t *list;
    size_t                      maxLength;
    bool                        hasMaxLength;
    char                        padding[7];
};

static bool octaspire_queue_private_ensure_max_length(
    octaspire_queue_t * const self)
{
    if (self->hasMaxLength)
    {
        while (octaspire_queue_get_length(self) > self->maxLength)
        {
            if (!octaspire_queue_pop(self))
            {
                return false;
            }
        }
    }

    return true;
}

octaspire_queue_t *octaspire_queue_new(
    size_t const elementSize,
    bool const elementIsPointer,
    octaspire_queue_element_callback_t const elementReleaseCallback,
    octaspire_allocator_t *allocator)
{
    octaspire_queue_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_queue_t));

    if (!self)
    {
        return self;
    }

    self->allocator    = allocator;
    self->hasMaxLength = false;
    self->maxLength    = 0;

    self->list = octaspire_list_new(
        elementSize,
        elementIsPointer,
        elementReleaseCallback,
        allocator);

    if (!self->list)
    {
        octaspire_queue_release(self);
        self = 0;
        return self;
    }

    return self;
}

octaspire_queue_t *octaspire_queue_new_with_max_length(
    size_t const maxLength,
    size_t const elementSize,
    bool const elementIsPointer,
    octaspire_queue_element_callback_t const elementReleaseCallback,
    octaspire_allocator_t *allocator)
{
    octaspire_queue_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_queue_t));

    if (!self)
    {
        return self;
    }

    self->allocator    = allocator;
    self->hasMaxLength = true;
    self->maxLength    = maxLength;

    self->list = octaspire_list_new(
        elementSize,
        elementIsPointer,
        elementReleaseCallback,
        allocator);

    if (!self->list)
    {
        octaspire_queue_release(self);
        self = 0;
        return self;
    }

    return self;
}

void octaspire_queue_release(octaspire_queue_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_list_release(self->list);
    self->list = 0;

    octaspire_helpers_verify_not_null(self->allocator);
    octaspire_allocator_free(self->allocator, self);
}

void *octaspire_queue_peek(
    octaspire_queue_t * const self)
{
    octaspire_list_node_t * const node = octaspire_list_get_front(self->list);

    if (!node)
    {
        return 0;
    }

    return octaspire_list_node_get_element(node);
}

void const *octaspire_queue_peek_const(
    octaspire_queue_t const * const self)
{
    octaspire_list_node_t const * const node =
        octaspire_list_get_front(self->list);

    if (!node)
    {
        return 0;
    }

    return octaspire_list_node_get_element_const(node);
}

bool octaspire_queue_pop(
    octaspire_queue_t * const self)
{
    return octaspire_list_pop_front(self->list);
}

bool octaspire_queue_push(
    octaspire_queue_t *self,
    void const * const element)
{
    if (!octaspire_list_push_back(self->list, element))
    {
        return false;
    }

    return octaspire_queue_private_ensure_max_length(self);
}

bool octaspire_queue_clear(
    octaspire_queue_t * const self)
{
    return octaspire_list_clear(self->list);
}

size_t octaspire_queue_get_length(
    octaspire_queue_t const * const self)
{
    return octaspire_list_get_length(self->list);
}

bool octaspire_queue_is_empty(
    octaspire_queue_t const * const self)
{
    return octaspire_list_is_empty(self->list);
}

void *octaspire_queue_get_at(
    octaspire_queue_t * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    octaspire_list_node_t * const node =
        octaspire_list_get_at(self->list, possiblyNegativeIndex);

    if (!node)
    {
        return 0;
    }

    return octaspire_list_node_get_element(node);
}

void const *octaspire_queue_get_at_const(
    octaspire_queue_t const * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    octaspire_list_node_t const * const node =
        octaspire_list_get_at(self->list, possiblyNegativeIndex);

    if (!node)
    {
        return 0;
    }

    return octaspire_list_node_get_element_const(node);
}

size_t octaspire_queue_get_max_length(
    octaspire_queue_t const * const self)
{
    return self->maxLength;
}

bool octaspire_queue_has_max_length(
    octaspire_queue_t const * const self)
{
    return self->hasMaxLength;
}

bool octaspire_queue_set_max_length(
    octaspire_queue_t * const self,
    size_t maxLength)
{
    self->maxLength = maxLength;
    return octaspire_queue_private_ensure_max_length(self);
}

bool octaspire_queue_set_has_max_length(
    octaspire_queue_t * const self,
    bool hasMaxLength)
{
    self->hasMaxLength = hasMaxLength;
    return octaspire_queue_set_max_length(self, self->maxLength);
}


octaspire_queue_iterator_t octaspire_queue_iterator_init(
    octaspire_queue_t * const self)
{
    octaspire_queue_iterator_t iterator;

    iterator.queue = self;
    iterator.iterator = octaspire_list_node_iterator_init(self->list);

    return iterator;
}

bool octaspire_queue_iterator_next(
    octaspire_queue_iterator_t * const self)
{
    return octaspire_list_node_iterator_next(&(self->iterator));
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/src/octaspire_queue.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/src/octaspire_string.c
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

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/src/octaspire_string.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/src/octaspire_pair.c
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

struct octaspire_pair_t
{
    void   *first;
    void   *second;
    size_t firstSize;
    size_t secondSize;
    octaspire_pair_element_callback_t firstReleaseCallback;
    octaspire_pair_element_callback_t secondReleaseCallback;
    octaspire_allocator_t *allocator;
    bool   firstIsPointer;
    bool   secondIsPointer;
    char   padding[6];
};

size_t octaspire_pair_t_get_sizeof(void)
{
    return sizeof(octaspire_pair_t);
}

octaspire_pair_t *octaspire_pair_new(
    size_t const firstElementSize,
    bool const firstElementIsPointer,
    size_t const secondElementSize,
    bool const secondElementIsPointer,
    octaspire_pair_element_callback_t firstElementReleaseCallback,
    octaspire_pair_element_callback_t secondElementReleaseCallback,
    octaspire_allocator_t *allocator)
{
    octaspire_pair_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_pair_t));

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

    self->first = octaspire_allocator_malloc(self->allocator, self->firstSize);

    if (!self->first)
    {
        octaspire_pair_release(self);
        self = 0;
        return 0;
    }

    self->second = octaspire_allocator_malloc(self->allocator, self->secondSize);

    if (!self->second)
    {
        octaspire_pair_release(self);
        self = 0;
        return 0;
    }

    return self;
}

octaspire_pair_t *octaspire_pair_new_shallow_copy(
    octaspire_pair_t   *other,
    octaspire_allocator_t *allocator)
{
    octaspire_pair_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_pair_t));

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

    self->first  = octaspire_allocator_malloc(self->allocator, self->firstSize);

    if (!self->first)
    {
        octaspire_pair_release(self);
        self = 0;
        return 0;
    }

    self->second = octaspire_allocator_malloc(self->allocator, self->secondSize);

    if (!self->second)
    {
        octaspire_pair_release(self);
        self = 0;
        return 0;
    }

    if (self->first != memcpy(self->first,  other->first,  self->firstSize))
    {
        octaspire_pair_release(self);
        self = 0;
        return 0;
    }

    if (self->second != memcpy(self->second, other->second, self->secondSize))
    {
        octaspire_pair_release(self);
        self = 0;
        return 0;
    }

    return self;
}

void octaspire_pair_release(octaspire_pair_t *self)
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
        octaspire_allocator_free(self->allocator, self->first);
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
        octaspire_allocator_free(self->allocator, self->second);
        self->second = 0;
    }

    octaspire_allocator_free(self->allocator, self);
}

void *octaspire_pair_get_first(octaspire_pair_t *self)
{
    return self->firstIsPointer ? (*(void**)self->first) : self->first;
}

void const *octaspire_pair_get_first_const(octaspire_pair_t const * const self)
{
    return self->firstIsPointer ? (*(void const **)self->first) : self->first;
}

void *octaspire_pair_get_second(octaspire_pair_t *self)
{
    return self->secondIsPointer ? (*(void**)self->second) : self->second;
}

void const *octaspire_pair_get_second_const(octaspire_pair_t const * const self)
{
    return self->secondIsPointer ? (*(void const **)self->second) : self->second;
}

size_t octaspire_pair_get_size_of_first_element_in_octets(
    octaspire_pair_t const * const self)
{
    return self->firstSize;
}

size_t octaspire_pair_get_size_of_second_element_in_octets(
    octaspire_pair_t const * const self)
{
    return self->secondSize;
}

void octaspire_pair_set(
    octaspire_pair_t *self,
    void const *first,
    void const *second)
{
    octaspire_pair_set_first( self, first);
    octaspire_pair_set_second(self, second);
}

void octaspire_pair_set_first(
    octaspire_pair_t *self,
    void const *first)
{
    octaspire_helpers_verify_not_null(self);
    octaspire_helpers_verify_not_null(first);
    if (self->first != memcpy(self->first,  first,  self->firstSize))
    {
        abort();
    }
}

void octaspire_pair_set_second(
    octaspire_pair_t *self,
    void const *second)
{
    if (self->second != memcpy(self->second, second, self->secondSize))
    {
        abort();
    }
}

bool octaspire_pair_set_first_to_void_pointer(
    octaspire_pair_t *self,
    void *element)
{
    if (self->firstSize != sizeof(element))
    {
        return false;
    }

    octaspire_pair_set_first(self, &element);

    return true;
}

bool octaspire_pair_set_second_to_void_pointer(
    octaspire_pair_t *self,
    void *element)
{
    if (self->secondSize != sizeof(element))
    {
        return false;
    }

    octaspire_pair_set_second(self, &element);

    return true;
}

void octaspire_pair_clear(
    octaspire_pair_t * const self)
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
// END OF          dev/src/octaspire_pair.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/src/octaspire_map.c
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



struct octaspire_map_element_t
{
    size_t                        keySizeInOctets;
    void                         *key;
    size_t                        valueSizeInOctets;
    octaspire_vector_t *values;
    octaspire_allocator_t        *allocator;
    uint32_t                      hash;
    bool                          keyIsPointer;
    bool                          valueIsPointer;
    char                          padding[2];
};

octaspire_map_element_t *octaspire_map_element_new(
    uint32_t const hash,
    size_t const keySizeInOctets,
    bool const keyIsPointer,
    void const * const key,
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    void const * const value,
    octaspire_allocator_t * const allocator)
{
    octaspire_map_element_t *self = octaspire_allocator_malloc(
        allocator,
        sizeof(octaspire_map_element_t));

    if (!self)
    {
        return self;
    }

    self->allocator = allocator;
    self->hash = hash;
    self->keySizeInOctets = keySizeInOctets;
    self->keyIsPointer    = keyIsPointer;
    self->key = octaspire_allocator_malloc(self->allocator, self->keySizeInOctets);

    if (!self->key)
    {
        octaspire_map_element_release(self);
        self = 0;
        return 0;
    }

    if (self->key != memcpy(self->key, key, self->keySizeInOctets))
    {
        abort();
    }

    self->valueSizeInOctets = valueSizeInOctets;
    self->valueIsPointer    = valueIsPointer;
    //self->value = octaspire_allocator_malloc(self->allocator, self->valueSizeInOctets);

    self->values = octaspire_vector_new(
        valueSizeInOctets,
        valueIsPointer,
        0,
        allocator);

    if (!self->values)
    {
        octaspire_map_element_release(self);
        self = 0;
        return 0;
    }

    if (!octaspire_vector_push_back_element(self->values, value))
    {
        abort();
    }

    return self;
}

void octaspire_map_element_release(octaspire_map_element_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_allocator_free(self->allocator, self->key);
    self->key = 0;

    //octaspire_allocator_free(self->allocator, self->value);
    //self->value= 0;

    octaspire_vector_release(self->values);
    self->values = 0;

    octaspire_allocator_free(self->allocator, self);
}

uint32_t octaspire_map_element_get_hash(
    octaspire_map_element_t const * const self)
{
    assert(self);
    return self->hash;
}

void *octaspire_map_element_get_key(
    octaspire_map_element_t const * const self)
{
    assert(self);
    return self->keyIsPointer ? (*(void**)self->key) : self->key;
}

octaspire_vector_t *octaspire_map_element_get_values(
    octaspire_map_element_t * const self)
{
    return self->values;
}

void *octaspire_map_element_get_value(
    octaspire_map_element_t const * const self)
{
    assert(self);
    assert(octaspire_vector_get_length(self->values) < 2);
    return octaspire_vector_get_element_at(self->values, 0);
    //return self->valueIsPointer ? (*(void**)self->value) : self->value;
}

void const *octaspire_map_element_get_key_const(
    octaspire_map_element_t const * const self)
{
    assert(self);
    return self->keyIsPointer ? (*(void const**)self->key) : self->key;
}

void const *octaspire_map_element_get_value_const(
    octaspire_map_element_t const * const self)
{
    assert(self);
    assert(octaspire_vector_get_length(self->values) < 2);
    return octaspire_vector_get_element_at_const(self->values, 0);
}



struct octaspire_map_t
{
    size_t                                                   keySizeInOctets;
    size_t                                                   valueSizeInOctets;
    octaspire_allocator_t                                   *allocator;
    octaspire_vector_t                            *buckets;
    octaspire_map_key_compare_function_t      keyCompareFunction;
    octaspire_map_key_hash_function_t         keyHashFunction;
    octaspire_map_element_callback_t     keyReleaseCallback;
    octaspire_map_element_callback_t     valueReleaseCallback;
    size_t                                                   numBucketsInUse;
    size_t                                                   numElements;
    bool                                                     keyIsPointer;
    bool                                                     valueIsPointer;
    char                                                     padding[6];
};

static size_t const OCTASPIRE_MAP_SMALLEST_SIZE   = 128;
static float  const OCTASPIRE_MAP_MAX_LOAD_FACTOR = 0.75f;

// Prototypes for static functions
static octaspire_vector_t *octaspire_map_private_build_new_buckets(
    octaspire_map_t *self,
    size_t const numBuckets,
    octaspire_allocator_t *allocator);

static float octaspire_map_private_get_load_factor(
    octaspire_map_t const * const self);

static bool octaspire_map_private_rehash(
    octaspire_map_t * const self);

static void octaspire_map_private_release_given_buckets(
    octaspire_map_t *self,
    octaspire_vector_t **bucketsPtr);


static bool octaspire_map_private_rehash(
    octaspire_map_t * const self)
{
    assert(self);

    size_t const oldBucketCount = octaspire_vector_get_length(self->buckets);
    size_t const newBucketCount = oldBucketCount * 2;

    assert(oldBucketCount && newBucketCount);

    octaspire_vector_t *newBuckets =
        octaspire_map_private_build_new_buckets(self, newBucketCount, self->allocator);

    self->numBucketsInUse = 0;
    self->numElements     = 0;

    if (!newBuckets)
    {
        return false;
    }

    for (size_t i = 0; i < oldBucketCount; ++i)
    {
        octaspire_vector_t *oldBucket =
            (octaspire_vector_t*)octaspire_vector_get_element_at(
                self->buckets,
                (ptrdiff_t)i);

        for (size_t j = 0; j < octaspire_vector_get_length(oldBucket); ++j)
        {
            octaspire_map_element_t *element =
                (octaspire_map_element_t*)octaspire_vector_get_element_at(
                    oldBucket,
                    (ptrdiff_t)j);

            uint32_t hash = octaspire_map_element_get_hash(element);

            size_t const bucketIndex = hash % newBucketCount;

            octaspire_vector_t *bucket =
                (octaspire_vector_t*)octaspire_vector_get_element_at(
                    newBuckets,
                    (ptrdiff_t)bucketIndex);

            assert(bucket);

            if (octaspire_vector_is_empty(bucket))
            {
                ++(self->numBucketsInUse);
            }

            if (!octaspire_vector_push_back_element(bucket, &element))
            {
                return false;
            }

            ++(self->numElements);
        }

        octaspire_vector_release(oldBucket);
        oldBucket = 0;
    }

    octaspire_vector_release(self->buckets);
    self->buckets = 0;

    self->buckets = newBuckets;

    assert(octaspire_map_private_get_load_factor(self) <
        OCTASPIRE_MAP_MAX_LOAD_FACTOR);

    return true;
}

static float octaspire_map_private_get_load_factor(
    octaspire_map_t const * const self)
{
    return (float)self->numBucketsInUse / octaspire_vector_get_length(self->buckets);
}

static void octaspire_map_private_release_given_buckets(
    octaspire_map_t *self,
    octaspire_vector_t **bucketsPtr)
{
    assert(self && bucketsPtr && *bucketsPtr);

    octaspire_vector_t *buckets = *bucketsPtr;

    size_t const numBuckets = octaspire_vector_get_length(buckets);

    for (size_t i = 0; i < numBuckets; ++i)
    {
        octaspire_vector_t *bucket =
            (octaspire_vector_t*)octaspire_vector_get_element_at(
                buckets,
                (ptrdiff_t)i);

        assert(bucket);

        for (size_t j = 0; j < octaspire_vector_get_length(bucket); ++j)
        {
            octaspire_map_element_t *element = (octaspire_map_element_t*)
                octaspire_vector_get_element_at(bucket, (ptrdiff_t)j);

            if (self->valueReleaseCallback)
            {
                for (size_t k = 0; k < octaspire_vector_get_length(element->values); ++k)
                {
                    //self->valueReleaseCallback(*(void**)element->value);
                    self->valueReleaseCallback(
                        octaspire_vector_get_element_at(
                            element->values,
                            (ptrdiff_t)k));
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

            octaspire_map_element_release(element);
        }

        //octaspire_vector_clear(bucket);
        octaspire_vector_release(bucket);
        bucket = 0;

    }

    octaspire_vector_release(buckets);
    *bucketsPtr = 0;
}

static octaspire_vector_t *octaspire_map_private_build_new_buckets(
    octaspire_map_t *self,
    size_t const numBuckets,
    octaspire_allocator_t *allocator)
{
    octaspire_vector_t *buckets = octaspire_vector_new_with_preallocated_elements(
        sizeof(octaspire_vector_t*),
        true,
        numBuckets,
        0, //(octaspire_vector_element_callback_t)octaspire_vector_release,
        allocator);

    if (!buckets)
    {
        return 0;
    }

    for (size_t i = 0; i < numBuckets; ++i)
    {
        octaspire_vector_t *bucket = octaspire_vector_new(
            sizeof(octaspire_map_element_t *),
            true,
            0, // (octaspire_vector_element_callback_t)octaspire_map_element_release,
            allocator);

        if (!bucket)
        {
            octaspire_map_private_release_given_buckets(self, &buckets);
            assert(!buckets);
            return 0;
        }

        if (!octaspire_vector_push_back_element(buckets, &bucket))
        {
            // This should never happen, because numBuckets buckets are
            // preallocated on the vector. So assert could be
            // used here, but maybe this is still safer?
            octaspire_map_private_release_given_buckets(self, &buckets);
            assert(!buckets);
            return 0;
        }
    }

    assert(octaspire_vector_get_length(buckets) == numBuckets);

    return buckets;
}

octaspire_map_t *octaspire_map_new(
    size_t const keySizeInOctets,
    bool const keyIsPointer,
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    octaspire_map_key_compare_function_t keyCompareFunction,
    octaspire_map_key_hash_function_t keyHashFunction,
    octaspire_map_element_callback_t keyReleaseCallback,
    octaspire_map_element_callback_t valueReleaseCallback,
    octaspire_allocator_t *allocator)
{
    octaspire_map_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_map_t));

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

    self->buckets = octaspire_map_private_build_new_buckets(
        self,
        OCTASPIRE_MAP_SMALLEST_SIZE,
        self->allocator);

    if (!self->buckets)
    {
        octaspire_map_release(self);
        self = 0;
        return 0;
    }

    return self;
}

octaspire_map_t *octaspire_map_new_with_octaspire_string_keys(
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    octaspire_map_element_callback_t valueReleaseCallback,
    octaspire_allocator_t *allocator)
{
    return octaspire_map_new(
        sizeof(octaspire_string_t*),
        true,
        valueSizeInOctets,
        valueIsPointer,
        (octaspire_map_key_compare_function_t)octaspire_string_is_equal,
        (octaspire_map_key_hash_function_t)octaspire_string_get_hash,
        (octaspire_map_element_callback_t)octaspire_string_release,
        valueReleaseCallback,
        allocator);
}

static bool octaspire_map_helper_private_size_t_is_equal(
    size_t const * const first,
    size_t const * const second)
{
    return *first == *second;
}

uint32_t octaspire_map_helper_size_t_get_hash(
    size_t const value)
{
    return jenkins_one_at_a_time_hash(&value, sizeof(value));
}

octaspire_map_t *octaspire_map_new_with_size_t_keys(
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    octaspire_map_element_callback_t valueReleaseCallback,
    octaspire_allocator_t *allocator)
{
    return octaspire_map_new(
        sizeof(size_t),
        false,
        valueSizeInOctets,
        valueIsPointer,
        (octaspire_map_key_compare_function_t)
            octaspire_map_helper_private_size_t_is_equal,
        (octaspire_map_key_hash_function_t)octaspire_map_helper_size_t_get_hash,
        (octaspire_map_element_callback_t)0,
        valueReleaseCallback,
        allocator);
}

void octaspire_map_release(octaspire_map_t *self)
{
    if (!self)
    {
        return;
    }

    if (self->buckets)
    {
        octaspire_map_private_release_given_buckets(self, &(self->buckets));
        assert(!(self->buckets));
    }

    self->buckets = 0;

    octaspire_allocator_free(self->allocator, self);
}

bool octaspire_map_remove(
    octaspire_map_t *self,
    uint32_t const hash,
    void const * const key)
{
    size_t const bucketIndex = hash % octaspire_vector_get_length(self->buckets);

    octaspire_vector_t *bucket =
        (octaspire_vector_t*)octaspire_vector_get_element_at(
            self->buckets,
            (ptrdiff_t)bucketIndex);

    if (!bucket)
    {
        return false;
    }

    size_t const numElementsInBucket = octaspire_vector_get_length(bucket);

    for (size_t i = 0; i < numElementsInBucket; ++i)
    {
        octaspire_map_element_t *element =
            (octaspire_map_element_t*)octaspire_vector_get_element_at(
                bucket,
                (ptrdiff_t)i);

        assert(element);

        void const * key2 = octaspire_map_element_get_key(element);

        if (self->keyCompareFunction(element->keyIsPointer ? *(void const * const *)key : key, key2))
        {
            if (self->valueReleaseCallback)
            {
                for (size_t j = 0; j < octaspire_vector_get_length(element->values); ++j)
                {
                    //self->valueReleaseCallback(*(void**)element->value);
                    self->valueReleaseCallback(
                        octaspire_vector_get_element_at(
                            element->values,
                            (ptrdiff_t)j));
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

            octaspire_map_element_release(element);
            if (octaspire_vector_remove_element_at(bucket, (ptrdiff_t)i))
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

bool octaspire_map_clear(
    octaspire_map_t * const self)
{
    // TODO XXX how to this in best way?

    octaspire_vector_t *buckets = octaspire_map_private_build_new_buckets(
        self,
        OCTASPIRE_MAP_SMALLEST_SIZE,
        self->allocator);

    if (!buckets)
    {
        return false;
    }

    if (self->buckets)
    {
        octaspire_map_private_release_given_buckets(self, &(self->buckets));
        assert(!(self->buckets));
    }

    self->buckets = buckets;

    self->numBucketsInUse = 0;
    self->numElements     = 0;

    return true;
}

bool octaspire_map_add_hash_map(
    octaspire_map_t * const self,
    octaspire_map_t * const other)
{
    bool result = true;

    for (size_t i = 0; i < octaspire_map_get_number_of_elements(other); ++i)
    {
        octaspire_map_element_t *otherElement =
            octaspire_map_get_at_index(other, (ptrdiff_t)i);

        for (size_t j = 0; j < octaspire_vector_get_length(otherElement->values); ++j)
        {
            void * const key   = otherElement->key;
            void * const value = octaspire_vector_get_element_at(
                otherElement->values,
                (ptrdiff_t)j);

            if (!octaspire_map_put(
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

bool octaspire_map_put(
    octaspire_map_t *self,
    uint32_t const hash,
    void const * const key,
    void const * const value)
{
    assert(self);
    assert(octaspire_vector_get_length(self->buckets));

    octaspire_map_element_t *element =
        octaspire_map_get(self, hash, key);

    if (element)
    {
        return octaspire_vector_push_back_element(element->values, value);
    }
    else
    {
        //octaspire_map_remove(self, hash, key);

        size_t const bucketIndex = hash % octaspire_vector_get_length(self->buckets);

        octaspire_vector_t *bucket =
            (octaspire_vector_t*)octaspire_vector_get_element_at(
                self->buckets,
                (ptrdiff_t)bucketIndex);

        assert(bucket);

        if (octaspire_vector_is_empty(bucket))
        {
            ++(self->numBucketsInUse);
        }

        element = octaspire_map_element_new(
            hash,
            self->keySizeInOctets,
            self->keyIsPointer,
            key,
            self->valueSizeInOctets,
            self->valueIsPointer,
            value,
            self->allocator);

        if (!octaspire_vector_push_back_element(bucket, &element))
        {
            return false;
        }

        ++(self->numElements);

        if (octaspire_map_private_get_load_factor(self) >=
                OCTASPIRE_MAP_MAX_LOAD_FACTOR)
        {
            if (!octaspire_map_private_rehash(self))
            {
                return false;
            }
        }

        return true;
    }
}

octaspire_map_element_t const * octaspire_map_get_const(
    octaspire_map_t const * const self,
    uint32_t const hash,
    void const * const key)
{
    size_t const bucketIndex = hash % octaspire_vector_get_length(self->buckets);

    octaspire_vector_t *bucket =
        (octaspire_vector_t*)octaspire_vector_get_element_at(
            self->buckets,
            (ptrdiff_t)bucketIndex);

    assert(bucket);

    size_t const numElementsInBucket = octaspire_vector_get_length(bucket);

    if (numElementsInBucket == 1)
    {
        octaspire_map_element_t *element = (octaspire_map_element_t*)
            octaspire_vector_peek_front_element(bucket);

        assert(element);

        void const * const key2 = octaspire_map_element_get_key(element);

        if (self->keyCompareFunction(element->keyIsPointer ? *(void const * const *)key : key, key2))
        {
            return element;
        }

        return 0;
    }

    for (size_t i = 0; i < numElementsInBucket; ++i)
    {
        octaspire_map_element_t *element =
            (octaspire_map_element_t*)octaspire_vector_get_element_at(
                bucket,
                (ptrdiff_t)i);

        assert(element);

        void const * const key2 = octaspire_map_element_get_key(element);

        if (self->keyCompareFunction(element->keyIsPointer ? *(void const * const *)key : key, key2))
        {
            return element;
        }
    }

    return 0;
}

octaspire_map_element_t *octaspire_map_get(
    octaspire_map_t *self, uint32_t const hash, void const * const key)
{
    size_t const bucketIndex = hash % octaspire_vector_get_length(self->buckets);

    octaspire_vector_t *bucket =
        (octaspire_vector_t*)octaspire_vector_get_element_at(
            self->buckets,
            (ptrdiff_t)bucketIndex);

    assert(bucket);

    size_t const numElementsInBucket = octaspire_vector_get_length(bucket);

    if (numElementsInBucket == 1)
    {
        octaspire_map_element_t *element = (octaspire_map_element_t*)
            octaspire_vector_peek_front_element(bucket);

        assert(element);

        void const * key2 = octaspire_map_element_get_key(element);

        if (self->keyCompareFunction(element->keyIsPointer ? *(void const * const *)key : key, key2))
        {
            return element;
        }

        return 0;
    }

    for (size_t i = 0; i < numElementsInBucket; ++i)
    {
        octaspire_map_element_t *element =
            (octaspire_map_element_t*)octaspire_vector_get_element_at(
                bucket,
                (ptrdiff_t)i);

        assert(element);

        void const * key2 = octaspire_map_element_get_key(element);

        if (self->keyCompareFunction(element->keyIsPointer ? *(void const * const *)key : key, key2))
        {
            return element;
        }
    }

    return 0;
}

bool octaspire_map_is_empty(octaspire_map_t const * const self)
{
    return (octaspire_map_get_number_of_elements(self) == 0);
}

size_t octaspire_map_get_number_of_elements(octaspire_map_t const * const self)
{
    assert(self);
    return self->numElements;
}

octaspire_map_element_t *octaspire_map_get_at_index(
    octaspire_map_t * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    if (possiblyNegativeIndex < 0)
    {
        if (octaspire_vector_is_empty(self->buckets))
        {
            return 0;
        }

        size_t index   = (size_t)(-(possiblyNegativeIndex+1));
        size_t counter = 0;
        for (ptrdiff_t i = (ptrdiff_t)octaspire_vector_get_length(self->buckets) - 1; i >= 0; --i)
        {
            octaspire_vector_t * const bucket = (octaspire_vector_t*)
                octaspire_vector_get_element_at(
                    self->buckets,
                    i);

            size_t const bucketSize = octaspire_vector_get_length(bucket);

            if (bucketSize)
            {
                if (index <= (counter + bucketSize - 1))
                {
                    return (octaspire_map_element_t*)
                        octaspire_vector_get_element_at(
                            bucket,
                            -((ptrdiff_t)(index - counter)));
                }

                counter += bucketSize;
            }
        }

        return 0;
    }
    else
    {
        size_t counter = 0;
        for (size_t i = 0; i < octaspire_vector_get_length(self->buckets); ++i)
        {
            octaspire_vector_t * const bucket = (octaspire_vector_t*)
                octaspire_vector_get_element_at(
                    self->buckets,
                    (ptrdiff_t)i);

            size_t const bucketSize = octaspire_vector_get_length(bucket);

            if (bucketSize)
            {
                if ((size_t)possiblyNegativeIndex <= (counter + bucketSize - 1))
                {
                    return (octaspire_map_element_t*)
                        octaspire_vector_get_element_at(
                            bucket,
                            possiblyNegativeIndex - (ptrdiff_t)counter);
                }

                counter += bucketSize;
            }
        }

        return 0;
    }
}

octaspire_map_element_iterator_t
octaspire_map_element_iterator_init(
    octaspire_map_t * const self)
{
    octaspire_map_element_iterator_t iterator;

    iterator.hashMap = self;
    iterator.bucketIndex = 0;
    iterator.elementInsideBucketIndex = 0;
    iterator.element = 0;

    while (!(iterator.element))
    {
        if (iterator.bucketIndex < octaspire_vector_get_length(self->buckets))
        {
            octaspire_vector_t * const bucket = (octaspire_vector_t*)
                octaspire_vector_get_element_at(
                    self->buckets,
                    (ptrdiff_t)(iterator.bucketIndex));

            size_t const bucketSize = octaspire_vector_get_length(bucket);

            for (; iterator.elementInsideBucketIndex < bucketSize; ++(iterator.elementInsideBucketIndex))
            {
                iterator.element = (octaspire_map_element_t*)
                    octaspire_vector_get_element_at(
                        bucket,
                        (ptrdiff_t)(iterator.elementInsideBucketIndex));

                if (iterator.element)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }

        if (iterator.element)
        {
            return iterator;
        }

        ++(iterator.bucketIndex);
        iterator.elementInsideBucketIndex = 0;
    }

    return iterator;
}

bool octaspire_map_element_iterator_next(
    octaspire_map_element_iterator_t * const self)
{
    self->element = 0;
    ++(self->elementInsideBucketIndex);

    while (!(self->element))
    {
        if (self->bucketIndex < octaspire_vector_get_length(self->hashMap->buckets))
        {
            octaspire_vector_t * const bucket = (octaspire_vector_t*)
                octaspire_vector_get_element_at(
                    self->hashMap->buckets,
                    (ptrdiff_t)(self->bucketIndex));

            size_t const bucketSize = octaspire_vector_get_length(bucket);

            for (; self->elementInsideBucketIndex < bucketSize; ++(self->elementInsideBucketIndex))
            {
                self->element = (octaspire_map_element_t*)
                    octaspire_vector_get_element_at(
                        bucket,
                        (ptrdiff_t)(self->elementInsideBucketIndex));

                if (self->element)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }

        if (self->element)
        {
            return self->element != 0;
        }

        ++(self->bucketIndex);
        self->elementInsideBucketIndex = 0;
    }

    return self->element != 0;
}


octaspire_map_element_const_iterator_t
octaspire_map_element_const_iterator_init(
    octaspire_map_t const * const self)
{
    octaspire_map_element_const_iterator_t iterator;

    iterator.hashMap = self;
    iterator.bucketIndex = 0;
    iterator.elementInsideBucketIndex = 0;
    iterator.element = 0;

    while (!(iterator.element))
    {
        if (iterator.bucketIndex < octaspire_vector_get_length(self->buckets))
        {
            octaspire_vector_t const * const bucket =
                (octaspire_vector_t const *)
                octaspire_vector_get_element_at_const(
                    self->buckets,
                    (ptrdiff_t)(iterator.bucketIndex));

            size_t const bucketSize = octaspire_vector_get_length(bucket);

            for (; iterator.elementInsideBucketIndex < bucketSize; ++(iterator.elementInsideBucketIndex))
            {
                iterator.element = (octaspire_map_element_t const *)
                    octaspire_vector_get_element_at_const(
                        bucket,
                        (ptrdiff_t)(iterator.elementInsideBucketIndex));

                if (iterator.element)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }

        if (iterator.element)
        {
            return iterator;
        }

        ++(iterator.bucketIndex);
        iterator.elementInsideBucketIndex = 0;
    }

    return iterator;
}

bool octaspire_map_element_const_iterator_next(
    octaspire_map_element_const_iterator_t * const self)
{
    self->element = 0;
    ++(self->elementInsideBucketIndex);

    while (!(self->element))
    {
        if (self->bucketIndex < octaspire_vector_get_length(self->hashMap->buckets))
        {
            octaspire_vector_t const * const bucket =
                (octaspire_vector_t const *)
                octaspire_vector_get_element_at_const(
                    self->hashMap->buckets,
                    (ptrdiff_t)(self->bucketIndex));

            size_t const bucketSize = octaspire_vector_get_length(bucket);

            for (; self->elementInsideBucketIndex < bucketSize; ++(self->elementInsideBucketIndex))
            {
                self->element = (octaspire_map_element_t const *)
                    octaspire_vector_get_element_at_const(
                        bucket,
                        (ptrdiff_t)(self->elementInsideBucketIndex));

                if (self->element)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }

        if (self->element)
        {
            return self->element != 0;
        }

        ++(self->bucketIndex);
        self->elementInsideBucketIndex = 0;
    }

    return self->element != 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/src/octaspire_map.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/src/octaspire_input.c
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
    octaspire_string_t *text;
    size_t                             index;
    size_t                             line;
    size_t                             column;
    octaspire_allocator_t             *allocator;
};

bool octaspire_input_private_is_ucs_character_index_valid(
    octaspire_input_t const * const self,
    size_t index);

octaspire_input_t *octaspire_input_new_from_c_string(
    char const * const str,
    octaspire_allocator_t *allocator)
{
    return octaspire_input_new_from_buffer(str, str ? strlen(str) : 0, allocator);
}

octaspire_input_t *octaspire_input_new_from_buffer(
    char const * const buffer,
    size_t const lengthInOctets,
    octaspire_allocator_t *allocator)
{
    octaspire_input_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_input_t));

    if (!self)
    {
        return self;
    }

    self->allocator = allocator;

    self->index  = 0;
    self->line   = 1;
    self->column = 1;

    self->text   = octaspire_string_new_from_buffer(buffer, lengthInOctets, self->allocator);

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
    octaspire_allocator_t *octaspireAllocator,
    octaspire_stdio_t *octaspireStdio)
{
    size_t octetsAllocated = 0;

    char *buffer = octaspire_helpers_path_to_buffer(
        path,
        &octetsAllocated,
        octaspireAllocator,
        octaspireStdio);

    if (!buffer)
    {
        return 0;
    }

    octaspire_input_t *self = octaspire_input_new_from_buffer(buffer, octetsAllocated, octaspireAllocator);

    octaspire_allocator_free(octaspireAllocator, buffer);
    buffer = 0;

    return self;
}

void octaspire_input_release(octaspire_input_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_string_release(self->text);
    octaspire_allocator_free(self->allocator, self);
}

size_t octaspire_input_get_length_in_ucs_characters(octaspire_input_t const * const self)
{
    return octaspire_string_get_length_in_ucs_characters(self->text);
}

void   octaspire_input_clear(octaspire_input_t *self)
{
    octaspire_string_clear(self->text);
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
    if (self->index >= octaspire_string_get_length_in_ucs_characters(self->text))
    {
        return 0;
    }

    return octaspire_string_get_ucs_character_at_index(
        self->text,
        (ptrdiff_t)(self->index));
}

uint32_t octaspire_input_peek_next_next_ucs_character(octaspire_input_t *self)
{
    if ((self->index + 1) >= octaspire_string_get_length_in_ucs_characters(self->text))
    {
        return 0;
    }

    return octaspire_string_get_ucs_character_at_index(
        self->text,
        (ptrdiff_t)(self->index + 1));
}

bool octaspire_input_pop_next_ucs_character(octaspire_input_t *self)
{
    if (!octaspire_input_private_is_ucs_character_index_valid(self, self->index))
    {
        return false;
    }

    uint32_t const result =
        octaspire_string_get_ucs_character_at_index(
            self->text,
            (ptrdiff_t)(self->index));

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
    return self->index < octaspire_string_get_length_in_ucs_characters(self->text);
}

bool octaspire_input_private_is_ucs_character_index_valid(
    octaspire_input_t const * const self,
    size_t index)
{
    return index < octaspire_string_get_length_in_ucs_characters(self->text);
}

bool octaspire_input_push_back_from_string(
    octaspire_input_t * const self,
    octaspire_string_t const * const str)
{
    return octaspire_input_push_back_from_c_string(
        self,
        octaspire_string_get_c_string(str));
}

bool octaspire_input_push_back_from_c_string(octaspire_input_t * const self, char const * const str)
{
    assert(self);
    return octaspire_string_concatenate_c_string(self->text, str);
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
    printf("%s", octaspire_string_get_c_string(self->text));
    printf("---------------------------------------------------------------------\n");
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/src/octaspire_input.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/src/octaspire_stdio.c
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
    octaspire_allocator_t *allocator;
    size_t   numberOfFutureReadsToBeRigged;
    size_t   bitIndex;
    uint32_t bitQueue;
    char     padding[4];
};

octaspire_stdio_t *octaspire_stdio_new(octaspire_allocator_t *allocator)
{
    size_t const size = sizeof(octaspire_stdio_t);

    octaspire_stdio_t *self = octaspire_allocator_malloc(allocator, size);

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

    octaspire_allocator_free(self->allocator, self);
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

octaspire_string_t *octaspire_stdio_read_line(octaspire_stdio_t *self, FILE *stream)
{
    octaspire_vector_t *vec = octaspire_vector_new(
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
            octaspire_vector_release(vec);
            return 0;
        }
        else if (c == '\n')
        {
            octaspire_vector_push_back_element(vec, &ch);
            break;
        }

        octaspire_vector_push_back_element(vec, &ch);
    }

    octaspire_string_t* result = octaspire_string_new_from_buffer(
        octaspire_vector_get_element_at_const(vec, 0),
        octaspire_vector_get_length_in_octets(vec),
        self->allocator);

    octaspire_vector_release(vec);
    vec = 0;
    return result;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/src/octaspire_stdio.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/src/octaspire_semver.c
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

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/src/octaspire_semver.c
//////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
}
#endif

#endif // OCTASPIRE_CORE_AMALGAMATED_IMPLEMENTATION

#ifdef OCTASPIRE_CORE_AMALGAMATED_UNIT_TEST_IMPLEMENTATION
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

#ifdef GREATEST_USE_LONGJMP
#include <setjmp.h>
#endif

/* Set to 0 to disable all use of time.h / clock(). */
#ifndef GREATEST_USE_TIME
#define GREATEST_USE_TIME 1
#endif

#ifdef GREATEST_USE_TIME
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

#ifdef GREATEST_USE_TIME
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

#ifdef GREATEST_USE_TIME
    /* overall timers */
    clock_t begin;
    clock_t end;
#endif

#ifdef GREATEST_USE_LONGJMP
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
#ifdef GREATEST_USE_LONGJMP
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

#ifdef GREATEST_USE_TIME
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

#ifdef GREATEST_USE_LONGJMP
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
#ifdef GREATEST_USE_ABBREVS
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

#ifdef GREATEST_USE_LONGJMP
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
// START OF        dev/test/test_helpers.c
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

static octaspire_allocator_t *octaspireHelpersTestAllocator = 0;
static octaspire_stdio_t     *octaspireHelpersTestStdio = 0;

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

    octaspire_allocator_free(octaspireHelpersTestAllocator, buffer);
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

    octaspire_allocator_free(octaspireHelpersTestAllocator, buffer);
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

    octaspire_allocator_free(octaspireHelpersTestAllocator, buffer);
    buffer = 0;

    PASS();
}

TEST octaspire_helpers_path_to_buffer_allocation_failure_test(void)
{
    size_t octetsAllocated = 0;

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireHelpersTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireHelpersTestAllocator));

    char * buffer = octaspire_helpers_path_to_buffer(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_helpers_path_to_buffer_test",
        &octetsAllocated,
        octaspireHelpersTestAllocator,
        octaspireHelpersTestStdio);

    ASSERT_EQ(0, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireHelpersTestAllocator));

    ASSERT_FALSE(buffer);
    ASSERT_EQ(0, octetsAllocated);

    octaspire_allocator_free(octaspireHelpersTestAllocator, buffer);
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

    octaspire_allocator_free(octaspireHelpersTestAllocator, buffer);
    buffer = 0;

    PASS();
}

TEST octaspire_helpers_is_even_size_t_test(void)
{
    ASSERT(octaspire_helpers_is_even_size_t(0));

    for (size_t i = 2; i < 1024; i += 2)
    {
        ASSERT(octaspire_helpers_is_even_size_t(i));
    }

    ASSERT_FALSE(octaspire_helpers_is_even_size_t(1));

    for (size_t i = 3; i < 1024; i += 2)
    {
        ASSERT_FALSE(octaspire_helpers_is_even_size_t(i));
    }

    PASS();
}

TEST octaspire_helpers_is_odd_size_t_test(void)
{
    ASSERT_FALSE(octaspire_helpers_is_odd_size_t(0));

    for (size_t i = 1; i < 1024; i += 2)
    {
        ASSERT(octaspire_helpers_is_odd_size_t(i));
    }

    ASSERT_FALSE(octaspire_helpers_is_odd_size_t(2));

    for (size_t i = 4; i < 1024; i += 2)
    {
        ASSERT_FALSE(octaspire_helpers_is_odd_size_t(i));
    }

    PASS();
}

TEST octaspire_helpers_calculate_hash_for_memory_buffer_argument_test(void)
{
    char const buffer[] = {'a', 'b', 'c'};

    ASSERT_EQ(
        3977453403,
        octaspire_helpers_calculate_hash_for_memory_buffer_argument(
            buffer,
            sizeof(buffer)));

    char const * const buffer2 = "123456789=?qwertyuiop#_.:,!++?";

    ASSERT_EQ(
        3026418028,
        octaspire_helpers_calculate_hash_for_memory_buffer_argument(
            buffer2,
            strlen(buffer2)));

    PASS();
}

TEST octaspire_helpers_base64_encode_qwerty1_line_len_0_test(void)
{
    char const * const input = "qwerty1";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        0,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ("cXdlcnR5MQ==", octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_qwerty1_line_len_10_test(void)
{
    char const * const input = "qwerty1";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        10,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ("cXdlcnR5MQ\n==", octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_qwerty1_test(void)
{
    char const * const input = "cXdlcnR5MQ==";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected = "qwerty1";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_qwerty1_with_embedded_whitespace_test(void)
{
    char const * const input = "\ncX\nd l\ncnR5\nM Q= \n= \n ";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected = "qwerty1";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_a_line_len_0_test(void)
{
    char const * const input = "a";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        0,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ("YQ==", octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_a_line_len_1_test(void)
{
    char const * const input = "a";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        1,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ("Y\nQ\n=\n=", octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_a_test(void)
{
    char const * const input = "YQ==";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected = "a";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_a_with_embedded_whitespace_test(void)
{
    char const * const input = " Y\t \t \t\t Q  = =  \t \n";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected = "a";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_empty_string_line_length_0_test(void)
{
    char const * const input = "";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        0,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ("", octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_empty_string_line_length_20_test(void)
{
    char const * const input = "";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        20,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ("", octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_empty_string_test(void)
{
    char const * const input = "";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT_EQ(0, decoded);

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_empty_string_with_whitespace_test(void)
{
    char const * const input = " \t \n ";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT_EQ(0, decoded);

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_base64_characters_line_length_0_test(void)
{
    char const * const input =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        0,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ(
        "QUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVphYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5e"
        "jAxMjM0NTY3ODkrLw==",
        octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_base64_characters_line_length_64_test(void)
{
    char const * const input =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        64,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ(
        "QUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVphYmNkZWZnaGlqa2xtbm9wcXJzdHV2\nd3h5e"
        "jAxMjM0NTY3ODkrLw==",
        octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_base64_characters_test(void)
{
    char const * const input =
        "QUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVphYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5e"
        "jAxMjM0NTY3ODkrLw==";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_base64_characters_with_whitespace_test(void)
{
    char const * const input =
        " QU JD   RE\tVGR0hJ\nSktMTU5PUFFSU\n1RVVl  dYW VphYmNkZWZna\tGlqa2xtbm9wcXJzdHV2d 3h5e"
        "jAx M j M 0NTY\t\t\n 3ODkr Lw= =";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_printable_ascii_characters_line_len_0_test(void)
{
    char const * const input =
        " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abc"
        "defghijklmnopqrstuvwxyz{|}~";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        0,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ(
        "ICEiIyQlJicoKSorLC0uLzAxMjM0NTY3ODk6Ozw9Pj9AQUJDREVGR0hJSktMTU5PUFFSU1R"
        "VVldYWVpbXF1eX2BhYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5ent8fX4=",
        octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_printable_ascii_characters_line_len_10_test(void)
{
    char const * const input =
        " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abc"
        "defghijklmnopqrstuvwxyz{|}~";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        10,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ(
        "ICEiIyQlJi\ncoKSorLC0u\nLzAxMjM0NT\nY3ODk6Ozw9\nPj9AQUJDRE\nVGR0hJSktM\nTU5PUFFSU1\nR"
        "VVldYWVpb\nXF1eX2BhYm\nNkZWZnaGlq\na2xtbm9wcX\nJzdHV2d3h5\nent8fX4=",
        octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_printable_ascii_characters_test(void)
{
    char const * const input =
        "ICEiIyQlJicoKSorLC0uLzAxMjM0NTY3ODk6Ozw9Pj9AQUJDREVGR0hJSktMTU5PUFFSU1R"
        "VVldYWVpbXF1eX2BhYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5ent8fX4=";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected =
        " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abc"
        "defghijklmnopqrstuvwxyz{|}~";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_printable_ascii_characters_with_whitespace_test(void)
{
    char const * const input =
        " I C EiI yQ  lJ  icoK\tSorLC0uLzAx\n\nMjM0NTY3O Dk6Ozw9Pj9AQUJDREVGR0hJSktMTU5PUFFSU1R"
        " V V l  d  Y  W    Vpb\nXF1eX\n\t 2B hYmN k  ZWZnaGlqa2xtbm9wcXJzdHV2d3 h 5ent8fX4=  ";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected =
        " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abc"
        "defghijklmnopqrstuvwxyz{|}~";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_all_octets_one_by_one_line_len_0_test(void)
{
    unsigned char input[0xFF + 1];

    for (size_t i = 0; i <= 0xFF; ++i)
        input[i] = (unsigned char)i;

    char const * const expected[] =
    {
        "AA==","AQ==","Ag==","Aw==","BA==","BQ==","Bg==","Bw==","CA==","CQ==",
        "Cg==","Cw==","DA==","DQ==","Dg==","Dw==","EA==","EQ==","Eg==","Ew==",
        "FA==","FQ==","Fg==","Fw==","GA==","GQ==","Gg==","Gw==","HA==","HQ==",
        "Hg==","Hw==","IA==","IQ==","Ig==","Iw==","JA==","JQ==","Jg==","Jw==",
        "KA==","KQ==","Kg==","Kw==","LA==","LQ==","Lg==","Lw==","MA==","MQ==",
        "Mg==","Mw==","NA==","NQ==","Ng==","Nw==","OA==","OQ==","Og==","Ow==",
        "PA==","PQ==","Pg==","Pw==","QA==","QQ==","Qg==","Qw==","RA==","RQ==",
        "Rg==","Rw==","SA==","SQ==","Sg==","Sw==","TA==","TQ==","Tg==","Tw==",
        "UA==","UQ==","Ug==","Uw==","VA==","VQ==","Vg==","Vw==","WA==","WQ==",
        "Wg==","Ww==","XA==","XQ==","Xg==","Xw==","YA==","YQ==","Yg==","Yw==",
        "ZA==","ZQ==","Zg==","Zw==","aA==","aQ==","ag==","aw==","bA==","bQ==",
        "bg==","bw==","cA==","cQ==","cg==","cw==","dA==","dQ==","dg==","dw==",
        "eA==","eQ==","eg==","ew==","fA==","fQ==","fg==","fw==","gA==","gQ==",
        "gg==","gw==","hA==","hQ==","hg==","hw==","iA==","iQ==","ig==","iw==",
        "jA==","jQ==","jg==","jw==","kA==","kQ==","kg==","kw==","lA==","lQ==",
        "lg==","lw==","mA==","mQ==","mg==","mw==","nA==","nQ==","ng==","nw==",
        "oA==","oQ==","og==","ow==","pA==","pQ==","pg==","pw==","qA==","qQ==",
        "qg==","qw==","rA==","rQ==","rg==","rw==","sA==","sQ==","sg==","sw==",
        "tA==","tQ==","tg==","tw==","uA==","uQ==","ug==","uw==","vA==","vQ==",
        "vg==","vw==","wA==","wQ==","wg==","ww==","xA==","xQ==","xg==","xw==",
        "yA==","yQ==","yg==","yw==","zA==","zQ==","zg==","zw==","0A==","0Q==",
        "0g==","0w==","1A==","1Q==","1g==","1w==","2A==","2Q==","2g==","2w==",
        "3A==","3Q==","3g==","3w==","4A==","4Q==","4g==","4w==","5A==","5Q==",
        "5g==","5w==","6A==","6Q==","6g==","6w==","7A==","7Q==","7g==","7w==",
        "8A==","8Q==","8g==","8w==","9A==","9Q==","9g==","9w==","+A==","+Q==",
        "+g==","+w==","/A==","/Q==","/g==","/w==",
    };

    size_t const inputLen = sizeof(input) / sizeof(input[0]);
    ASSERT_EQ(inputLen, sizeof(expected) / sizeof(expected[0]));

    for (size_t i = 0; i < inputLen; ++i)
    {
        octaspire_string_t * encoded = octaspire_helpers_base64_encode(
            (char const * const)(input + i),
            1,
            0,
            octaspireHelpersTestAllocator);

        ASSERT(encoded);

        ASSERT_STR_EQ(
            expected[i],
            octaspire_string_get_c_string(encoded));

        octaspire_string_release(encoded);
        encoded = 0;
    }

    PASS();
}

TEST octaspire_helpers_base64_encode_all_octets_line_len_0_test(void)
{
    unsigned char input[0xFF + 1];

    for (size_t i = 0; i <= 0xFF; ++i)
        input[i] = (unsigned char)i;

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        (char const * const)input,
        sizeof(input) / sizeof(input[0]),
        0,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    char const * const expected =
        "AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4vMDEyM"
        "zQ1Njc4OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5fYGFiY2RlZm"
        "doaWprbG1ub3BxcnN0dXZ3eHl6e3x9fn+AgYKDhIWGh4iJiouMjY6PkJGSk5SVlpeYmZq"
        "bnJ2en6ChoqOkpaanqKmqq6ytrq+wsbKztLW2t7i5uru8vb6/wMHCw8TFxsfIycrLzM3O"
        "z9DR0tPU1dbX2Nna29zd3t/g4eLj5OXm5+jp6uvs7e7v8PHy8/T19vf4+fr7/P3+/w==";

    ASSERT_EQ(strlen(expected), octaspire_string_get_length_in_octets(encoded));

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_all_octets_line_len_69_test(void)
{
    unsigned char input[0xFF + 1];

    for (size_t i = 0; i <= 0xFF; ++i)
        input[i] = (unsigned char)i;

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        (char const * const)input,
        sizeof(input) / sizeof(input[0]),
        69,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    char const * const expected =
        "AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4vMDEyM\n"
        "zQ1Njc4OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5fYGFiY2RlZm\n"
        "doaWprbG1ub3BxcnN0dXZ3eHl6e3x9fn+AgYKDhIWGh4iJiouMjY6PkJGSk5SVlpeYmZq\n"
        "bnJ2en6ChoqOkpaanqKmqq6ytrq+wsbKztLW2t7i5uru8vb6/wMHCw8TFxsfIycrLzM3O\n"
        "z9DR0tPU1dbX2Nna29zd3t/g4eLj5OXm5+jp6uvs7e7v8PHy8/T19vf4+fr7/P3+/w==";

    ASSERT_EQ(strlen(expected), octaspire_string_get_length_in_octets(encoded));

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_and_then_decode_all_octets_line_len_69_test(void)
{
    unsigned char input[0xFF + 1];

    for (size_t i = 0; i <= 0xFF; ++i)
        input[i] = (unsigned char)i;

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        (char const * const)input,
        sizeof(input) / sizeof(input[0]),
        69,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        octaspire_string_get_c_string(encoded),
        (int32_t)octaspire_string_get_length_in_octets(encoded),
        octaspireHelpersTestAllocator);

    ASSERT_EQ(0xFF + 1, octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < octaspire_vector_get_length(decoded); ++i)
    {
        ASSERT_EQ(
            input[i],
            *(unsigned char const * const)
                octaspire_vector_get_element_at_const(decoded, (ptrdiff_t)i));
    }

    octaspire_string_release(encoded);
    encoded = 0;

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

GREATEST_SUITE(octaspire_helpers_suite)
{
    octaspireHelpersTestAllocator = octaspire_allocator_new(0);
    octaspireHelpersTestStdio     = octaspire_stdio_new(octaspireHelpersTestAllocator);

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

    RUN_TEST(octaspire_helpers_is_even_size_t_test);
    RUN_TEST(octaspire_helpers_is_odd_size_t_test);

    RUN_TEST(octaspire_helpers_calculate_hash_for_memory_buffer_argument_test);

    RUN_TEST(octaspire_helpers_base64_encode_qwerty1_line_len_0_test);
    RUN_TEST(octaspire_helpers_base64_encode_qwerty1_line_len_10_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_qwerty1_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_qwerty1_with_embedded_whitespace_test);
    RUN_TEST(octaspire_helpers_base64_encode_a_line_len_0_test);
    RUN_TEST(octaspire_helpers_base64_encode_a_line_len_1_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_a_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_a_with_embedded_whitespace_test);
    RUN_TEST(octaspire_helpers_base64_encode_empty_string_line_length_0_test);
    RUN_TEST(octaspire_helpers_base64_encode_empty_string_line_length_20_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_empty_string_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_empty_string_with_whitespace_test);
    RUN_TEST(octaspire_helpers_base64_encode_base64_characters_line_length_0_test);
    RUN_TEST(octaspire_helpers_base64_encode_base64_characters_line_length_64_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_base64_characters_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_base64_characters_with_whitespace_test);
    RUN_TEST(octaspire_helpers_base64_encode_printable_ascii_characters_line_len_0_test);
    RUN_TEST(octaspire_helpers_base64_encode_printable_ascii_characters_line_len_10_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_printable_ascii_characters_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_printable_ascii_characters_with_whitespace_test);
    RUN_TEST(octaspire_helpers_base64_encode_all_octets_one_by_one_line_len_0_test);
    RUN_TEST(octaspire_helpers_base64_encode_all_octets_line_len_0_test);
    RUN_TEST(octaspire_helpers_base64_encode_all_octets_line_len_69_test);
    RUN_TEST(octaspire_helpers_base64_encode_and_then_decode_all_octets_line_len_69_test);

    octaspire_stdio_release(octaspireHelpersTestStdio);
    octaspireHelpersTestStdio = 0;

    octaspire_allocator_release(octaspireHelpersTestAllocator);
    octaspireHelpersTestAllocator = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/test/test_helpers.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/test/test_utf8.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

static octaspire_allocator_t *octaspireUtf8TestAllocator = 0;

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
    octaspire_vector_t *buffer =
        octaspire_vector_new(sizeof(char), false, 0, octaspireUtf8TestAllocator);

    size_t const currentIndex = 0;
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_INPUT_IS_NULL,
        octaspire_utf8_decode_character_from_buffer(
            octaspire_vector_get_element_at(buffer, 0),
            octaspire_vector_get_length_in_octets(buffer),
            currentIndex,
            &result,
            &numoctets));

    ASSERT_EQ(0, result);
    ASSERT_EQ(0, numoctets);

    octaspire_vector_release(buffer);
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
    octaspire_vector_t *buffer =
        octaspire_vector_new(sizeof(char), false, 0, octaspireUtf8TestAllocator);

    octaspire_vector_push_back_char(buffer, 'a');
    size_t const currentIndex = 0;
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_OK,
        octaspire_utf8_decode_character_from_buffer(
            octaspire_vector_get_element_at(buffer, 0),
            octaspire_vector_get_length_in_octets(buffer),
            currentIndex,
            &result,
            &numoctets));

    ASSERT_EQ(97, result);
    ASSERT_EQ(1, numoctets);

    octaspire_vector_release(buffer);
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
    octaspire_vector_t *buffer =
        octaspire_vector_new(sizeof(char), false, 0, octaspireUtf8TestAllocator);

    octaspire_vector_push_back_char(buffer, '\x80');
    size_t const currentIndex = 0;
    uint32_t result = 0;
    int numoctets = 0;

    ASSERT_EQ(
        OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
        octaspire_utf8_decode_character_from_buffer(
            octaspire_vector_get_element_at(buffer, 0),
            octaspire_vector_get_length_in_octets(buffer),
            currentIndex,
            &result,
            &numoctets));

    ASSERT_EQ(0,  result);
    ASSERT_EQ(-1, numoctets);

    octaspire_vector_release(buffer);
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

GREATEST_SUITE(octaspire_utf8_suite)
{
    octaspireUtf8TestAllocator = octaspire_allocator_new(0);
    assert(octaspireUtf8TestAllocator);

    RUN_TEST(octaspire_utf8_private_rangeof_test);
    RUN_TEST(octaspire_utf8_private_high_order_bits_test);
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

    octaspire_allocator_release(octaspireUtf8TestAllocator);
    octaspireUtf8TestAllocator = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/test/test_utf8.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/test/test_memory.c
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

TEST octaspire_allocator_new_test(void)
{
    octaspire_allocator_t *allocator = octaspire_allocator_new(0);

    ASSERT(allocator);

    ASSERT_EQ(0, allocator->numberOfFutureAllocationsToBeRigged);
    ASSERT_EQ(0, allocator->bitIndex);

    size_t const bitQueueLen = sizeof(allocator->bitQueue) / sizeof(allocator->bitQueue[0]);
    ASSERT_EQ(20, bitQueueLen);

    for (size_t i = 0; i < bitQueueLen; ++i)
    {
        ASSERT_EQ(0, allocator->bitQueue[i]);
    }


    octaspire_allocator_release(allocator);
    allocator = 0;

    PASS();
}

// How to test this efficiently, etc.?
/*
TEST octaspire_allocator_new_failure_test(void)
{
    octaspire_allocator_t *allocator = octaspire_allocator_new();

    ASSERT_FALSE(allocator);

    octaspire_allocator_release(allocator);
    allocator = 0;

    PASS();
}
*/

TEST octaspire_allocator_malloc_test(void)
{
    octaspire_allocator_t *allocator = octaspire_allocator_new(0);

    size_t *ptrs[100];

    size_t const elemsize = sizeof(ptrs[0]);
    size_t const nelems   = sizeof(ptrs) / elemsize;

    for (size_t i = 0; i < nelems; ++i)
    {
        ptrs[i] = octaspire_allocator_malloc(allocator, elemsize);
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
        octaspire_allocator_free(allocator, ptrs[i]);
        ptrs[i] = 0;
    }

    octaspire_allocator_release(allocator);
    allocator = 0;

    PASS();
}

TEST octaspire_allocator_free_test(void)
{
    octaspire_allocator_t *allocator = octaspire_allocator_new(0);

    octaspire_allocator_free(allocator, 0);
    octaspire_allocator_free(allocator, octaspire_allocator_malloc(allocator, 10));

    octaspire_allocator_release(allocator);
    allocator = 0;

    PASS();
}

TEST octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged_when_larger_than_32_test(void)
{
    octaspire_allocator_t *allocator = octaspire_allocator_new(0);

    ASSERT_EQ(0, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    size_t const count = 640;

    uint32_t const bitPattern = 0x55; // 0101 0101

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged_when_larger_than_32(
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

   ASSERT_EQ(count, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

   for (size_t i = 0; i < count; ++i)
   {
       if (i % 2 == 0)
       {
           ASSERT(octaspire_allocator_private_test_bit(allocator));
       }
       else
       {
           ASSERT_FALSE(octaspire_allocator_private_test_bit(allocator));
       }

       ++(allocator->bitIndex);
   }

   ASSERT_EQ(count, allocator->bitIndex);

   octaspire_allocator_release(allocator);
   allocator = 0;

   PASS();
}

TEST octaspire_allocator_setting_and_getting_future_allocations_to_fail_and_using_with_malloc_test(void)
{
    octaspire_allocator_t *allocator = octaspire_allocator_new(0);

    ASSERT_EQ(0, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    size_t count = 32;

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(allocator, count, 0);

    ASSERT_EQ(count, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    for (size_t i = count; i > 0; --i)
    {
        ASSERT_FALSE(octaspire_allocator_malloc(allocator, 1));
        ASSERT_EQ(i - 1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(allocator));
    }

    ASSERT_EQ(0, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    void *ptr = octaspire_allocator_malloc(allocator, 1);
    ASSERT(ptr);
    octaspire_allocator_free(allocator, ptr);
    ptr = 0;

    ASSERT_EQ(0, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    octaspire_allocator_release(allocator);
    allocator = 0;

    PASS();
}

TEST octaspire_allocator_setting_and_getting_future_allocations_to_fail_and_using_with_realloc_test(void)
{
    octaspire_allocator_t *allocator = octaspire_allocator_new(0);

    ASSERT_EQ(0, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    void *buffer = octaspire_allocator_malloc(allocator, 1);

    ASSERT(buffer);

    size_t count = 32;

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(allocator, count, 0);

    ASSERT_EQ(count, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    for (size_t i = count; i > 0; --i)
    {
        ASSERT_FALSE(octaspire_allocator_realloc(allocator, buffer, 2));
        ASSERT_EQ(i - 1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(allocator));
    }

    ASSERT_EQ(0, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    void *ptr = octaspire_allocator_realloc(allocator, buffer, 2);
    ASSERT(ptr);
    octaspire_allocator_free(allocator, ptr);
    ptr = 0;

    ASSERT_EQ(0, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(allocator));

    octaspire_allocator_release(allocator);
    allocator = 0;

    PASS();
}

GREATEST_SUITE(octaspire_memory_suite)
{
    RUN_TEST(octaspire_allocator_new_test);
    //RUN_TEST(octaspire_allocator_new_failure_test);
    RUN_TEST(octaspire_allocator_malloc_test);
    RUN_TEST(octaspire_allocator_free_test);
    RUN_TEST(octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged_when_larger_than_32_test);
    RUN_TEST(octaspire_allocator_setting_and_getting_future_allocations_to_fail_and_using_with_malloc_test);
    RUN_TEST(octaspire_allocator_setting_and_getting_future_allocations_to_fail_and_using_with_realloc_test);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/test/test_memory.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/test/test_stdio.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

static octaspire_allocator_t *octaspireStdioTestAllocator = 0;

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
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireStdioTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireStdioTestAllocator));

    octaspire_stdio_t *stdio = octaspire_stdio_new(octaspireStdioTestAllocator);

    ASSERT_FALSE(stdio);

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireStdioTestAllocator));

    octaspire_stdio_release(stdio);
    stdio = 0;

    PASS();
}

TEST octaspire_stdio_fread_test(void)
{
    octaspire_stdio_t *stdio = octaspire_stdio_new(octaspireStdioTestAllocator);

    ASSERT(stdio);

#ifdef _MSC_VER
    FILE *f = 0;
    errno_t const err =
        fopen_s(&f, OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_stdio_fread_test", "rb");
    ASSERT(!err);
#else
    FILE *f = fopen(OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_stdio_fread_test", "rb");
#endif

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

#ifdef _MSC_VER
    FILE *f = 0;
    errno_t const err =
        fopen_s(&f, OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_stdio_fread_test", "rb");
    ASSERT(!err);
#else
    FILE *f = fopen(OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_stdio_fread_test", "rb");
#endif

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

GREATEST_SUITE(octaspire_stdio_suite)
{
    octaspireStdioTestAllocator = octaspire_allocator_new(0);

    assert(octaspireStdioTestAllocator);

    RUN_TEST(octaspire_stdio_new_test);
    RUN_TEST(octaspire_stdio_new_allocation_failure_test);
    RUN_TEST(octaspire_stdio_fread_test);
    RUN_TEST(octaspire_stdio_fread_rigging_and_failure_test);

    octaspire_allocator_release(octaspireStdioTestAllocator);
    octaspireStdioTestAllocator = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/test/test_stdio.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/test/test_input.c
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

static octaspire_allocator_t *octaspireInputTestAllocator = 0;
static octaspire_stdio_t     *octaspireInputTestStdio = 0;

TEST octaspire_input_new_from_c_string_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    ASSERT(input->text);

    size_t const numUcsChars =
        octaspire_string_get_length_in_ucs_characters(input->text);

    ASSERT_EQ(6, numUcsChars);

    ASSERT_EQ(0x61,    octaspire_string_get_ucs_character_at_index(input->text, 0));
    ASSERT_EQ(0x62,    octaspire_string_get_ucs_character_at_index(input->text, 1));
    ASSERT_EQ(0x63,    octaspire_string_get_ucs_character_at_index(input->text, 2));
    ASSERT_EQ(0xa9,    octaspire_string_get_ucs_character_at_index(input->text, 3));
    ASSERT_EQ(0x2260,  octaspire_string_get_ucs_character_at_index(input->text, 4));
    ASSERT_EQ(0x10000, octaspire_string_get_ucs_character_at_index(input->text, 5));

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

    ASSERT_EQ(0,         octaspire_string_get_length_in_ucs_characters(input->text));
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

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireInputTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

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
        octaspire_string_get_length_in_ucs_characters(input->text);

    ASSERT_EQ(6, numUcsChars);

    ASSERT_EQ(0x61,    octaspire_string_get_ucs_character_at_index(input->text, 0));
    ASSERT_EQ(0x62,    octaspire_string_get_ucs_character_at_index(input->text, 1));
    ASSERT_EQ(0x63,    octaspire_string_get_ucs_character_at_index(input->text, 2));
    ASSERT_EQ(0xa9,    octaspire_string_get_ucs_character_at_index(input->text, 3));
    ASSERT_EQ(0x2260,  octaspire_string_get_ucs_character_at_index(input->text, 4));
    ASSERT_EQ(0x10000, octaspire_string_get_ucs_character_at_index(input->text, 5));

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

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireInputTestAllocator,
        1,
        0x00);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    octaspire_input_t *input = octaspire_input_new_from_buffer(
        buffer, sizeof(buffer) / sizeof(buffer[0]),
        octaspireInputTestAllocator);

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

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

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireInputTestAllocator,
        2,
        0x01);

    ASSERT_EQ(
        2,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    octaspire_input_t *input = octaspire_input_new_from_buffer(
        buffer, sizeof(buffer) / sizeof(buffer[0]),
        octaspireInputTestAllocator);

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

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
        octaspire_string_get_length_in_ucs_characters(input->text);

    ASSERT_EQ(6, numUcsChars);

    ASSERT_EQ(0x61,    octaspire_string_get_ucs_character_at_index(input->text, 0));
    ASSERT_EQ(0x62,    octaspire_string_get_ucs_character_at_index(input->text, 1));
    ASSERT_EQ(0x63,    octaspire_string_get_ucs_character_at_index(input->text, 2));
    ASSERT_EQ(0xa9,    octaspire_string_get_ucs_character_at_index(input->text, 3));
    ASSERT_EQ(0x2260,  octaspire_string_get_ucs_character_at_index(input->text, 4));
    ASSERT_EQ(0x10000, octaspire_string_get_ucs_character_at_index(input->text, 5));

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
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireInputTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    octaspire_input_t *input = octaspire_input_new_from_path(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_input_new_from_path_test",
        octaspireInputTestAllocator,
        octaspireInputTestStdio);

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

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
        octaspire_string_get_length_in_ucs_characters(input->text);

    ASSERT_EQ(6, numUcsChars);

    ASSERT_EQ(0x61,    octaspire_string_get_ucs_character_at_index(input->text, 0));
    ASSERT_EQ(0x62,    octaspire_string_get_ucs_character_at_index(input->text, 1));
    ASSERT_EQ(0x63,    octaspire_string_get_ucs_character_at_index(input->text, 2));
    ASSERT_EQ(0xa9,    octaspire_string_get_ucs_character_at_index(input->text, 3));
    ASSERT_EQ(0x2260,  octaspire_string_get_ucs_character_at_index(input->text, 4));
    ASSERT_EQ(0x10000, octaspire_string_get_ucs_character_at_index(input->text, 5));

    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);

    ASSERT_EQ(6, octaspire_input_get_length_in_ucs_characters(input));

    octaspire_input_clear(input);

    ASSERT(input->text);

    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(input->text));

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

GREATEST_SUITE(octaspire_input_suite)
{
    octaspireInputTestAllocator = octaspire_allocator_new(0);
    octaspireInputTestStdio     = octaspire_stdio_new(octaspireInputTestAllocator);

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

    octaspire_allocator_release(octaspireInputTestAllocator);
    octaspireInputTestAllocator = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/test/test_input.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/test/test_vector.c
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

static octaspire_allocator_t *octaspireContainerVectorTestAllocator = 0;

TEST octaspire_vector_private_index_to_pointer_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);
    }

    for (size_t i = 0; i < len; ++i)
    {
        size_t const * expected = (size_t const *)(vec->elements) + i;

        ASSERT_EQ(
            expected,
            (size_t const *)octaspire_vector_private_index_to_pointer(vec, i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_private_index_to_pointer_const_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);
    }

    for (size_t i = 0; i < len; ++i)
    {
        size_t const * expected = (size_t const *)(vec->elements) + i;

        ASSERT_EQ(
            expected,
            (size_t const *)octaspire_vector_private_index_to_pointer_const(vec, i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_private_grow_with_factor_2_success_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(double), false, 0, octaspireContainerVectorTestAllocator);

    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;
    size_t const       originalNumAllocated = vec->numAllocated;

    char *expectedInitializedMemory =
        octaspire_allocator_malloc(octaspireContainerVectorTestAllocator, originalElementSize);

    float const factor = 2;

    ASSERT(octaspire_vector_private_grow(vec, factor));
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

    ASSERT(octaspire_vector_private_grow(vec, factor));
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

    octaspire_vector_release(vec);
    vec = 0;
    octaspire_allocator_free(octaspireContainerVectorTestAllocator, expectedInitializedMemory);

    PASS();
}

TEST octaspire_vector_private_grow_with_factor_100_success_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(char), false, 0, octaspireContainerVectorTestAllocator);

    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;
    size_t const       originalNumAllocated = vec->numAllocated;

    char *expectedInitializedMemory =
        octaspire_allocator_malloc(octaspireContainerVectorTestAllocator, originalElementSize);

    float const factor = 100;

    ASSERT(octaspire_vector_private_grow(vec, factor));
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

    ASSERT(octaspire_vector_private_grow(vec, factor));
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

    octaspire_vector_release(vec);
    vec = 0;
    octaspire_allocator_free(octaspireContainerVectorTestAllocator, expectedInitializedMemory);

    PASS();
}

TEST octaspire_vector_private_grow_with_factor_2_even_when_zero_is_given_as_factor_success_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(double), false, 0, octaspireContainerVectorTestAllocator);

    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;
    size_t const       originalNumAllocated = vec->numAllocated;

    char *expectedInitializedMemory =
        octaspire_allocator_malloc(octaspireContainerVectorTestAllocator, originalElementSize);

    float const badFactor = 0;
    float const factor = 2;

    ASSERT(octaspire_vector_private_grow(vec, badFactor));
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

    ASSERT(octaspire_vector_private_grow(vec, badFactor));
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

    octaspire_vector_release(vec);
    vec = 0;
    octaspire_allocator_free(octaspireContainerVectorTestAllocator, expectedInitializedMemory);

    PASS();
}

TEST octaspire_vector_private_grow_with_factor_2_even_when_one_is_given_as_factor_success_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(double), false, 0, octaspireContainerVectorTestAllocator);

    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;
    size_t const       originalNumAllocated = vec->numAllocated;

    char *expectedInitializedMemory =
        octaspire_allocator_malloc(octaspireContainerVectorTestAllocator, originalElementSize);

    float const badFactor = 1;
    float const factor = 2;

    ASSERT(octaspire_vector_private_grow(vec, badFactor));
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

    ASSERT(octaspire_vector_private_grow(vec, badFactor));
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

    octaspire_vector_release(vec);
    vec = 0;
    octaspire_allocator_free(octaspireContainerVectorTestAllocator, expectedInitializedMemory);

    PASS();
}

TEST octaspire_vector_private_grow_failure_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    void const * const originalElements     = vec->elements;
    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;
    size_t const       originalNumAllocated = vec->numAllocated;

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerVectorTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerVectorTestAllocator));

    ASSERT_FALSE(octaspire_vector_private_grow(vec, 2));

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerVectorTestAllocator));

    ASSERT_EQ(originalElements,     vec->elements);
    ASSERT_EQ(originalElementSize,  vec->elementSize);
    ASSERT_EQ(originalNumElements,  vec->numElements);
    ASSERT_EQ(originalNumAllocated, vec->numAllocated);

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_private_compact_success_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT(octaspire_vector_private_grow(vec, 1000));

    for (size_t i = 0; i < 250; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);
    }

    //void              *originalElements     = vec->elements;
    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;

    ASSERT(octaspire_vector_private_compact(vec));

    //ASSERT_EQ(originalElements,              vec->elements);
    ASSERT_EQ(originalElementSize,           vec->elementSize);
    ASSERT_EQ(originalNumElements,           vec->numElements);
    // Compacting should have made self->numAllocated == self->numElements
    ASSERT_EQ(originalNumElements,           vec->numAllocated);

    // TODO Continue here

    for (size_t i = 0; i < vec->numElements; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_private_compact_failure_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT(octaspire_vector_private_grow(vec, 1000));

    for (size_t i = 0; i < 250; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);
    }

    void              *originalElements     = vec->elements;
    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;
    size_t const       originalNumAllocated = vec->numAllocated;

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator, 1, 0);

    ASSERT_FALSE(octaspire_vector_private_compact(vec));

    ASSERT_EQ(0, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    ASSERT_EQ(originalElements,     vec->elements);
    ASSERT_EQ(originalElementSize,  vec->elementSize);
    ASSERT_EQ(originalNumElements,  vec->numElements);
    ASSERT_EQ(originalNumAllocated, vec->numAllocated);

    for (size_t i = 0; i < vec->numElements; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_new_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT(vec);

    ASSERT(vec->elements);
    ASSERT_EQ(sizeof(size_t),                          vec->elementSize);
    ASSERT_EQ(0,                                       vec->numElements);
    ASSERT_EQ(OCTASPIRE_VECTOR_INITIAL_SIZE, vec->numAllocated);
    ASSERT_EQ(0,                                       vec->elementReleaseCallback);
    ASSERT_EQ(octaspireContainerVectorTestAllocator,                               vec->allocator);

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_new_failure_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator, 1, 0);

    ASSERT_EQ(1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_FALSE(vec);

    ASSERT_EQ(0, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_new_for_octaspire_string_elements_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new_for_octaspire_string_elements(
            octaspireContainerVectorTestAllocator);

    ASSERT(vec);

    ASSERT(vec->elements);
    ASSERT_EQ(sizeof(octaspire_string_t*),             vec->elementSize);
    ASSERT_EQ(0,                                       vec->numElements);
    ASSERT_EQ(OCTASPIRE_VECTOR_INITIAL_SIZE,           vec->numAllocated);

    ASSERT_EQ(
        (octaspire_vector_element_callback_t)octaspire_string_release,
        vec->elementReleaseCallback);

    ASSERT_EQ(octaspireContainerVectorTestAllocator,   vec->allocator);

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_new_for_octaspire_string_elements_failure_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerVectorTestAllocator,
        1,
        0);

    ASSERT_EQ(1,
              octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
                  octaspireContainerVectorTestAllocator));

    octaspire_vector_t *vec =
        octaspire_vector_new_for_octaspire_string_elements(
            octaspireContainerVectorTestAllocator);

    ASSERT_FALSE(vec);

    ASSERT_EQ(0,
              octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
                  octaspireContainerVectorTestAllocator));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_new_with_preallocated_elements_test(void)
{
    size_t const numPreAllocated = 100;

    octaspire_vector_t *vec = octaspire_vector_new_with_preallocated_elements(
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

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_new_with_preallocated_elements_allocation_failure_on_first_allocation_test(void)
{
    size_t const numPreAllocated = 100;

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    octaspire_vector_t *vec = octaspire_vector_new_with_preallocated_elements(
        sizeof(size_t),
        false,
        numPreAllocated,
        0,
        octaspireContainerVectorTestAllocator);

    ASSERT_EQ(0, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    ASSERT_FALSE(vec);

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_new_with_preallocated_elements_allocation_failure_on_second_allocation_test(void)
{
    size_t const numPreAllocated = 100;

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator, 2, 0x01);
    ASSERT_EQ(2, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    octaspire_vector_t *vec = octaspire_vector_new_with_preallocated_elements(
        sizeof(size_t),
        false,
        numPreAllocated,
        0,
        octaspireContainerVectorTestAllocator);

    ASSERT_EQ(0, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    ASSERT_FALSE(vec);

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}



// TODO XXX test octaspire_vector_new_with_preallocated_elements
// It has newer allocation failure test that must also be tested




TEST octaspire_vector_new_shallow_copy_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT(vec);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_push_back_element(vec, &i));
    }

    ASSERT_EQ(
        len,
        octaspire_vector_get_length(vec));

    octaspire_vector_t *cpy=
        octaspire_vector_new_shallow_copy(vec, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(
        octaspire_vector_get_length(vec),
        octaspire_vector_get_length(cpy));

    for (size_t i = 0; i < octaspire_vector_get_length(cpy); ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                cpy,
                (ptrdiff_t)i));
    }

    ASSERT_EQ(vec->elementSize, cpy->elementSize);
    ASSERT_EQ(vec->numElements, cpy->numElements);

    // Copy is compact
    ASSERT_EQ(cpy->numElements, cpy->numAllocated);
    ASSERT_MEM_EQ(vec->elements, cpy->elements, cpy->numElements);
    ASSERT_EQ(vec->elementReleaseCallback, cpy->elementReleaseCallback);
    ASSERT_EQ(vec->allocator, cpy->allocator);

    octaspire_vector_release(vec);
    vec = 0;

    octaspire_vector_release(cpy);
    cpy = 0;

    PASS();
}

TEST octaspire_vector_new_shallow_copy_allocation_failure_on_first_allocation_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT(vec);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_push_back_element(vec, &i));
    }

    ASSERT_EQ(
        len,
        octaspire_vector_get_length(vec));

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    ASSERT_FALSE(octaspire_vector_new_shallow_copy(vec, octaspireContainerVectorTestAllocator));

    ASSERT_EQ(0, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_new_shallow_copy_allocation_failure_on_second_allocation_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT(vec);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_push_back_element(vec, &i));
    }

    ASSERT_EQ(
        len,
        octaspire_vector_get_length(vec));

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator, 2, 0x01);
    ASSERT_EQ(2, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    ASSERT_FALSE(octaspire_vector_new_shallow_copy(vec, octaspireContainerVectorTestAllocator));

    ASSERT_EQ(0, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerVectorTestAllocator));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_release_null_test(void)
{
    octaspire_vector_release(0);
    PASS();
}

void octaspire_vector_test_element_callback1(void *element);
void octaspire_vector_test_element_callback3_shrink_vector(void *element);
void octaspire_vector_test_element_callback2_grow_vector(void *element);

static size_t octaspireContainerVectorTestElementCallback1TimesCalled = 0;

void octaspire_vector_test_element_callback1(void *element)
{
    OCTASPIRE_HELPERS_UNUSED_PARAMETER(element);
    ++octaspireContainerVectorTestElementCallback1TimesCalled;
}

void octaspire_vector_test_element_callback2_grow_vector(void *element)
{
    octaspire_vector_t *vec = element;

    ++octaspireContainerVectorTestElementCallback1TimesCalled;

    if (octaspireContainerVectorTestElementCallback1TimesCalled < 100)
    {
        octaspire_vector_push_back_element(vec, &vec);
    }
}

void octaspire_vector_test_element_callback3_shrink_vector(void *element)
{
    octaspire_vector_t *vec = element;

    ++octaspireContainerVectorTestElementCallback1TimesCalled;

    if (!octaspire_vector_is_empty(vec))
    {
        octaspire_vector_pop_back_element(vec);
    }
}

TEST octaspire_vector_release_element_callback_called_for_all_elements_test(void)
{
    octaspireContainerVectorTestElementCallback1TimesCalled = 0;

    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, octaspire_vector_test_element_callback1, octaspireContainerVectorTestAllocator);

    ASSERT(vec);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_push_back_element(vec, &i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    ASSERT_EQ(len, octaspireContainerVectorTestElementCallback1TimesCalled);

    PASS();
}

TEST octaspire_vector_get_length_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(i, octaspire_vector_get_length(vec));
        octaspire_vector_push_back_element(vec, &i);
        ASSERT_EQ(i + 1, octaspire_vector_get_length(vec));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_is_empty_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT(octaspire_vector_is_empty(vec));
    }

    for (size_t i = 0; i < 100; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);
        ASSERT_FALSE(octaspire_vector_is_empty(vec));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_remove_element_at_index_minus_one_100_times_of_100_elements_test(void)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);

        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_remove_element_at(vec, -1));

        if (i < (len - 1))
        {
            ASSERT_EQ(
                len - 2 - i,
                *(size_t*)octaspire_vector_peek_back_element(vec));

            for (size_t j = 0; j < octaspire_vector_get_length(vec); ++j)
            {
                ASSERT_EQ(
                    j,
                    *(size_t*)octaspire_vector_get_element_at(vec, (ptrdiff_t)j));
            }
        }
    }

    ASSERT(octaspire_vector_is_empty(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_remove_element_at_index_0_of_100_elements_test(void)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);

        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    ASSERT(octaspire_vector_remove_element_at(vec, 0));

    for (size_t i = 0; i < len - 1; ++i)
    {
            ASSERT_EQ(
                i + 1,
                *(size_t*)octaspire_vector_get_element_at(
                    vec,
                    (ptrdiff_t)i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_remove_element_at_index_50_of_100_elements_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);

        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    ASSERT(octaspire_vector_remove_element_at(vec, 50));

    for (size_t i = 0; i < len - 1; ++i)
    {
        if (i < 50)
        {
            ASSERT_EQ(
                i,
                *(size_t*)octaspire_vector_get_element_at(
                    vec,
                    (ptrdiff_t)i));
        }
        else
        {
            ASSERT_EQ(
                i + 1,
                *(size_t*)octaspire_vector_get_element_at(
                    vec,
                    (ptrdiff_t)i));
        }
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_remove_element_at_index_99_of_100_elements_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);

        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    ASSERT(octaspire_vector_remove_element_at(vec, 99));

    for (size_t i = 0; i < len - 1; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_remove_element_at_failure_removing_index_100_of_100_elements_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    ASSERT_FALSE(octaspire_vector_remove_element_at(vec, 100));

    ASSERT_EQ(len, octaspire_vector_get_length(vec));

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_remove_element_at_failure_removing_indices_100_to_200_of_100_elements_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);

        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    for (size_t i = 100; i < 201; ++i)
    {
        ASSERT_FALSE(octaspire_vector_remove_element_at(
            vec,
            (ptrdiff_t)i));
    }

    ASSERT_EQ(len, octaspire_vector_get_length(vec));

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_remove_element_at_remove_all_100_elements_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_remove_element_at(vec, 0));

        ASSERT_EQ(len - (i + 1), octaspire_vector_get_length(vec));

        for (size_t j = 0; j < octaspire_vector_get_length(vec); ++j)
        {
            ASSERT_EQ(
                j + i + 1,
                *(size_t*)octaspire_vector_get_element_at(
                    vec,
                    (ptrdiff_t)j));
        }
    }

    ASSERT_EQ(0, octaspire_vector_get_length(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_get_element_at_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_FALSE((size_t*)octaspire_vector_get_element_at(
            vec,
            (ptrdiff_t)i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_FALSE((size_t*)octaspire_vector_get_element_at(
            vec,
            (ptrdiff_t)i));

        octaspire_vector_push_back_element(vec, &i);

        ASSERT_EQ(i, *(size_t*)octaspire_vector_get_element_at(
            vec,
            (ptrdiff_t)i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    ASSERT_FALSE((size_t*)octaspire_vector_get_element_at(
        vec,
        (ptrdiff_t)(len + 1)));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_get_element_at_const_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_FALSE((size_t const *)octaspire_vector_get_element_at_const(
            vec,
            (ptrdiff_t)i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_FALSE((size_t const *)octaspire_vector_get_element_at_const(
            vec,
            (ptrdiff_t)i));

        octaspire_vector_push_back_element(vec, &i);

        ASSERT_EQ(
            i,
            *(size_t const *)octaspire_vector_get_element_at_const(
                vec,
                (ptrdiff_t)i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t const *)octaspire_vector_get_element_at_const(
                vec,
                (ptrdiff_t)i));
    }

    ASSERT_FALSE((size_t const *)octaspire_vector_get_element_at_const(
        vec,
        (ptrdiff_t)(len + 1)));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_get_element_at_called_with_negative_indices_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);

        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    for (ptrdiff_t i = -1; i > -((ptrdiff_t)len); --i)
    {
        ASSERT_EQ(
            (size_t)((ptrdiff_t)len + i),
            *(size_t*)octaspire_vector_get_element_at(vec, i));
    }

    for (ptrdiff_t i = len + 1; i < (ptrdiff_t)(3 * len); ++i)
    {
        ASSERT_EQ(0, (size_t*)octaspire_vector_get_element_at(vec, -i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_get_element_at_const_called_with_negative_indices_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);

        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    for (ptrdiff_t i = -1; i > -((ptrdiff_t)len); --i)
    {
        ASSERT_EQ(
            (size_t)((ptrdiff_t)len + i),
            *(size_t const * const)octaspire_vector_get_element_at_const(
                vec,
                i));
    }

    for (ptrdiff_t i = len + 1; i < (ptrdiff_t)(3 * len); ++i)
    {
        ASSERT_EQ(0, (size_t const * const)octaspire_vector_get_element_at_const(vec, -i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_get_element_size_in_octets_when_element_is_of_type_uint8_t_test(void)
{
    size_t const expectedSize = sizeof(uint8_t);

    octaspire_vector_t *vec =
        octaspire_vector_new(expectedSize, false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(expectedSize, octaspire_vector_get_element_size_in_octets(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_get_element_size_in_octets_when_element_is_of_type_int_test(void)
{
    size_t const expectedSize = sizeof(int);

    octaspire_vector_t *vec =
        octaspire_vector_new(expectedSize, false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(expectedSize, octaspire_vector_get_element_size_in_octets(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_get_element_size_in_octets_when_element_is_of_type_size_t_test(void)
{
    size_t const expectedSize = sizeof(size_t);

    octaspire_vector_t *vec =
        octaspire_vector_new(expectedSize, false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(expectedSize, octaspire_vector_get_element_size_in_octets(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_get_element_size_in_octets_when_element_is_of_type_double_test(void)
{
    size_t const expectedSize = sizeof(double);

    octaspire_vector_t *vec =
        octaspire_vector_new(expectedSize, false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(expectedSize, octaspire_vector_get_element_size_in_octets(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_get_element_size_in_octets_when_element_is_of_type_void_ptr_test(void)
{
    size_t const expectedSize = sizeof(void*);

    octaspire_vector_t *vec =
        octaspire_vector_new(expectedSize, true, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(expectedSize, octaspire_vector_get_element_size_in_octets(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_get_element_size_in_octets_when_element_size_is_10000_test(void)
{
    size_t const expectedSize = 10000;

    octaspire_vector_t *vec =
        octaspire_vector_new(expectedSize, false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(expectedSize, octaspire_vector_get_element_size_in_octets(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_get_element_size_in_octets_when_element_size_is_illegal_zero_test(void)
{
    size_t const expectedSize = sizeof(char);

    octaspire_vector_t *vec =
        octaspire_vector_new(0, false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(expectedSize, octaspire_vector_get_element_size_in_octets(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_insert_element_before_the_element_at_index_minus_one_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t value = 2;

    octaspire_vector_push_front_element(vec, &value);

    value = 1;

    ASSERT(octaspire_vector_insert_element_before_the_element_at_index(vec, &value, -1));

    ASSERT_EQ(2,  octaspire_vector_get_length(vec));
    ASSERT_EQ(1, *(size_t*)octaspire_vector_get_element_at(vec, 0));
    ASSERT_EQ(2, *(size_t*)octaspire_vector_get_element_at(vec, 1));

    value = 9;

    ASSERT(octaspire_vector_insert_element_before_the_element_at_index(vec, &value, -1));

    ASSERT_EQ(3,  octaspire_vector_get_length(vec));
    ASSERT_EQ(1, *(size_t*)octaspire_vector_get_element_at(vec, 0));
    ASSERT_EQ(9, *(size_t*)octaspire_vector_get_element_at(vec, 1));
    ASSERT_EQ(2, *(size_t*)octaspire_vector_get_element_at(vec, 2));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_insert_element_before_the_element_at_index_zero_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    octaspire_vector_push_front_element(vec, &len);

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_insert_element_before_the_element_at_index(vec, &i, 0));
        ASSERT_EQ(i, *(size_t*)octaspire_vector_get_element_at(vec, 0));
    }

    ASSERT_EQ(len + 1, octaspire_vector_get_length(vec));
    ASSERT_EQ(len, *(size_t*)octaspire_vector_peek_back_element(vec));

    for (size_t i = 0; i < octaspire_vector_get_length(vec) - 1; ++i)
    {
        ASSERT_EQ(
            len - (i + 1),
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_insert_element_before_the_element_at_index_called_on_empty_vector_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(
            octaspire_vector_insert_element_before_the_element_at_index(vec, &i, 0));
    }

    ASSERT(octaspire_vector_is_empty(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_insert_element_before_the_element_at_index_the_end_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    octaspire_vector_push_front_element(vec, &len);

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(
            octaspire_vector_insert_element_before_the_element_at_index(
                vec,
                &i,
                (ptrdiff_t)octaspire_vector_get_length(vec) - 1));

        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    ASSERT_EQ(len + 1, octaspire_vector_get_length(vec));
    ASSERT_EQ(len, *(size_t*)octaspire_vector_peek_back_element(vec));

    for (size_t i = 0; i < octaspire_vector_get_length(vec); ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_insert_element_before_the_element_at_index_past_the_end_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const value = 100;

    octaspire_vector_push_front_element(vec, &value);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(
            octaspire_vector_insert_element_before_the_element_at_index(
                vec,
                &i,
                10));

        ASSERT_EQ(1, octaspire_vector_get_length(vec));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_insert_element_before_the_element_at_index_allocation_failure_test(void)
{
    size_t const value = 123;

    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT(octaspire_vector_push_front_element(vec, &value));

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerVectorTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerVectorTestAllocator));

    ASSERT_FALSE(
        octaspire_vector_insert_element_before_the_element_at_index(
            vec,
            &value,
            0));

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerVectorTestAllocator));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_insert_element_before_the_element_at_index_the_middle_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_push_back_element(vec, &i));
        ASSERT_EQ(i, *(size_t*)octaspire_vector_peek_back_element(vec));
    }

    ASSERT_EQ(len, octaspire_vector_get_length(vec));

    ASSERT(octaspire_vector_insert_element_before_the_element_at_index(vec, &len, 50));

    ASSERT_EQ(len + 1, octaspire_vector_get_length(vec));

    for (size_t i = 0; i < octaspire_vector_get_length(vec); ++i)
    {
        if (i < 50)
        {
            ASSERT_EQ(
                i,
                *(size_t*)octaspire_vector_get_element_at(
                    vec,
                    (ptrdiff_t)i));
        }
        else if (i == 50)
        {
            ASSERT_EQ(
                100,
                *(size_t*)octaspire_vector_get_element_at(
                    vec,
                    (ptrdiff_t)i));
        }
        else
        {
            ASSERT_EQ(
                i - 1,
                *(size_t*)octaspire_vector_get_element_at(
                    vec,
                    (ptrdiff_t)i));
        }
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_insert_element_at_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);

        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    size_t a = 900;
    size_t b = 901;
    size_t c = 902;

    ASSERT(octaspire_vector_insert_element_at(vec, &a, 0));
    ASSERT_EQ(a, *(size_t*)octaspire_vector_get_element_at(vec, 0));
    for (size_t i = 1; i < len; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    ASSERT(octaspire_vector_insert_element_at(vec, &b, 50));
    ASSERT_EQ(b, *(size_t*)octaspire_vector_get_element_at(vec, 50));
    ASSERT_EQ(a, *(size_t*)octaspire_vector_get_element_at(vec, 0));
    for (size_t i = 1; i < len; ++i)
    {
        if (i != 50)
        {
            ASSERT_EQ(
                i,
                *(size_t*)octaspire_vector_get_element_at(
                    vec,
                    (ptrdiff_t)i));
        }
    }

    ASSERT(octaspire_vector_insert_element_at(vec, &c, 102));
    ASSERT_EQ(a, *(size_t*)octaspire_vector_get_element_at(vec, 0));
    ASSERT_EQ(b, *(size_t*)octaspire_vector_get_element_at(vec, 50));
    for (size_t i = 1; i < len; ++i)
    {
        if (i != 50)
        {
            ASSERT_EQ(
                i,
                *(size_t*)octaspire_vector_get_element_at(
                    vec,
                    (ptrdiff_t)i));
        }
    }
    ASSERT_EQ(c, *(size_t*)octaspire_vector_get_element_at(vec, 102));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_replace_element_at_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const first       = 10;
    size_t const last        = 20;
    size_t const replacement = 99;

    ASSERT(octaspire_vector_push_back_element(vec, &first));
    ASSERT(octaspire_vector_push_back_element(vec, &last));

    ASSERT_FALSE(octaspire_vector_replace_element_at(vec,  2, &replacement));
    ASSERT_FALSE(octaspire_vector_replace_element_at(vec, -3, &replacement));

    // First
    ASSERT(octaspire_vector_replace_element_at(vec, 0, &replacement));

    ASSERT_EQ(
        replacement,
        *(size_t const * const)octaspire_vector_get_element_at(vec, 0));

    ASSERT_EQ(
        last,
        *(size_t const * const)octaspire_vector_get_element_at(vec, 1));

    // Last
    ASSERT(octaspire_vector_replace_element_at(vec, 1, &replacement));

    ASSERT_EQ(
        replacement,
        *(size_t const * const)octaspire_vector_get_element_at(vec, 0));

    ASSERT_EQ(
        replacement,
        *(size_t const * const)octaspire_vector_get_element_at(vec, 1));

    size_t const newReplacement = 99;

    // First using negative indices
    ASSERT(octaspire_vector_replace_element_at(vec, -2, &newReplacement));

    ASSERT_EQ(
        newReplacement,
        *(size_t const * const)octaspire_vector_get_element_at(vec, 0));

    ASSERT_EQ(
        replacement,
        *(size_t const * const)octaspire_vector_get_element_at(vec, 1));

    // Last using negative indices
    ASSERT(octaspire_vector_replace_element_at(vec, -1, &newReplacement));

    ASSERT_EQ(
        newReplacement,
        *(size_t const * const)octaspire_vector_get_element_at(vec, 0));

    ASSERT_EQ(
        newReplacement,
        *(size_t const * const)octaspire_vector_get_element_at(vec, 1));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_replace_element_at_index_or_push_back_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t expected = 123;

    ASSERT(octaspire_vector_replace_element_at_index_or_push_back(vec, &expected, 0));
    ASSERT_EQ(1, octaspire_vector_get_length(vec));
    ASSERT_EQ(expected, *(size_t*)octaspire_vector_get_element_at(vec, 0));

    expected = 987;

    ASSERT(octaspire_vector_replace_element_at_index_or_push_back(vec, &expected, 0));
    ASSERT_EQ(1, octaspire_vector_get_length(vec));
    ASSERT_EQ(expected, *(size_t*)octaspire_vector_get_element_at(vec, 0));

    expected = 297;

    ASSERT(octaspire_vector_replace_element_at_index_or_push_back(vec, &expected, 1));
    ASSERT_EQ(2,        octaspire_vector_get_length(vec));
    ASSERT_EQ(987,      *(size_t*)octaspire_vector_get_element_at(vec, 0));
    ASSERT_EQ(expected, *(size_t*)octaspire_vector_get_element_at(vec, 1));

    expected = 777;

    ASSERT(octaspire_vector_replace_element_at_index_or_push_back(vec, &expected, 1));
    ASSERT_EQ(2,        octaspire_vector_get_length(vec));
    ASSERT_EQ(987,      *(size_t*)octaspire_vector_get_element_at(vec, 0));
    ASSERT_EQ(expected, *(size_t*)octaspire_vector_get_element_at(vec, 1));

    expected = 222;

    ASSERT(octaspire_vector_replace_element_at_index_or_push_back(vec, &expected, 0));
    ASSERT_EQ(2,        octaspire_vector_get_length(vec));
    ASSERT_EQ(expected, *(size_t*)octaspire_vector_get_element_at(vec, 0));
    ASSERT_EQ(777,      *(size_t*)octaspire_vector_get_element_at(vec, 1));

    expected = 1111;

    ASSERT(octaspire_vector_replace_element_at_index_or_push_back(vec, &expected, 2));
    ASSERT_EQ(3,        octaspire_vector_get_length(vec));
    ASSERT_EQ(222,      *(size_t*)octaspire_vector_get_element_at(vec, 0));
    ASSERT_EQ(777,      *(size_t*)octaspire_vector_get_element_at(vec, 1));
    ASSERT_EQ(expected, *(size_t*)octaspire_vector_get_element_at(vec, 2));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_insert_element_at_index_100_of_empty_vector_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t a = 900;
    size_t const index = 100;
    ASSERT(octaspire_vector_insert_element_at(vec, &a, index));

    ASSERT_EQ(index + 1, octaspire_vector_get_length(vec));

    for (size_t i = 0; i < (index - 1); ++i)
    {
        ASSERT_EQ(
            0,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    ASSERT_EQ(a, *(size_t*)octaspire_vector_get_element_at(vec, index));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_insert_element_at_failure_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const element = 0;

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerVectorTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerVectorTestAllocator));

    ASSERT_FALSE(octaspire_vector_insert_element_at(vec, &element, 4));

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerVectorTestAllocator));

    ASSERT_EQ(0, octaspire_vector_get_length(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_push_front_element_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_push_front_element(vec, &i));
        ASSERT_EQ(i + 1, octaspire_vector_get_length(vec));
        ASSERT_EQ(i, *(size_t*)octaspire_vector_get_element_at(vec, 0));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(
            len - (i + 1),
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_push_back_element_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_push_back_element(vec, &i));
        ASSERT_EQ(i + 1, octaspire_vector_get_length(vec));

        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_push_back_char_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(char), false, 0, octaspireContainerVectorTestAllocator);

    char const len = 127;

    for (char i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_push_back_char(vec, i));
        ASSERT_EQ((size_t)i + 1, octaspire_vector_get_length(vec));

        ASSERT_EQ(
            (char)i,
            *(char*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    for (char i = 0; i < len; ++i)
    {
        ASSERT_EQ(
            (char)i,
            *(char*)octaspire_vector_get_element_at(
                vec,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_push_back_char_to_vector_containing_floats_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(float), false, 0, octaspireContainerVectorTestAllocator);

    char const len = 127;

    for (char i = 0; i < len; ++i)
    {
        ASSERT_FALSE(octaspire_vector_push_back_char(vec, i));
        ASSERT_EQ(0, octaspire_vector_get_length(vec));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_for_each_called_on_empty_vector_test(void)
{
    octaspireContainerVectorTestElementCallback1TimesCalled = 0;

    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    octaspire_vector_for_each(vec, octaspire_vector_test_element_callback1);

    ASSERT_EQ(0, octaspireContainerVectorTestElementCallback1TimesCalled);

    octaspireContainerVectorTestElementCallback1TimesCalled = 0;
    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_for_each_called_on_vector_with_one_element_test(void)
{
    octaspireContainerVectorTestElementCallback1TimesCalled = 0;

    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const element = 999;

    octaspire_vector_push_back_element(vec, &element);

    octaspire_vector_for_each(vec, octaspire_vector_test_element_callback1);

    ASSERT_EQ(1, octaspireContainerVectorTestElementCallback1TimesCalled);

    octaspireContainerVectorTestElementCallback1TimesCalled = 0;
    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_for_each_called_on_vector_with_hundred_elements_test(void)
{
    octaspireContainerVectorTestElementCallback1TimesCalled = 0;

    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        octaspire_vector_push_back_element(vec, &i);
    }

    octaspire_vector_for_each(vec, octaspire_vector_test_element_callback1);

    ASSERT_EQ(100, octaspireContainerVectorTestElementCallback1TimesCalled);

    octaspireContainerVectorTestElementCallback1TimesCalled = 0;
    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_for_each_called_on_vector_that_grows_during_iteration_test(void)
{
    octaspireContainerVectorTestElementCallback1TimesCalled = 0;

    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(octaspire_vector_t*), true, 0, octaspireContainerVectorTestAllocator);

    octaspire_vector_push_back_element(vec, &vec);

    octaspire_vector_for_each(vec, octaspire_vector_test_element_callback2_grow_vector);

    ASSERT_EQ(100, octaspireContainerVectorTestElementCallback1TimesCalled);

    octaspireContainerVectorTestElementCallback1TimesCalled = 0;
    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_for_each_called_on_vector_that_shrinks_during_iteration_test(void)
{
    octaspireContainerVectorTestElementCallback1TimesCalled = 0;

    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(octaspire_vector_t*), true, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        octaspire_vector_push_back_element(vec, &vec);
    }

    octaspire_vector_for_each(
        vec,
        octaspire_vector_test_element_callback3_shrink_vector);

    ASSERT_EQ(50, octaspireContainerVectorTestElementCallback1TimesCalled);

    octaspireContainerVectorTestElementCallback1TimesCalled = 0;
    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_pop_back_element_called_on_empty_vector_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(octaspire_vector_pop_back_element(vec));
    }

    ASSERT_EQ(0, octaspire_vector_get_length(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_pop_back_element_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_push_back_element(vec, &i));
    }

    ASSERT_EQ(len, octaspire_vector_get_length(vec));

    for (size_t i = len; i != 0; --i)
    {
        ASSERT_EQ(i-1, *(size_t*)octaspire_vector_peek_back_element(vec));
        ASSERT(octaspire_vector_pop_back_element(vec));
        ASSERT_EQ(i-1, octaspire_vector_get_length(vec));

        if (i > 1)
        {
            ASSERT_FALSE(octaspire_vector_is_empty(vec));
            ASSERT_EQ(i - 2, *(size_t*)octaspire_vector_peek_back_element(vec));
        }
    }

    ASSERT_EQ(0, octaspire_vector_get_length(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}



















TEST octaspire_vector_peek_back_element_called_on_empty_vector_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(octaspire_vector_peek_back_element(vec));
    }

    ASSERT_EQ(0, octaspire_vector_get_length(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_peek_back_element_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_push_back_element(vec, &i));
        ASSERT_EQ(i, *(size_t*)octaspire_vector_peek_back_element(vec));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_peek_back_element_const_called_on_empty_vector_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(octaspire_vector_peek_back_element_const(vec));
    }

    ASSERT_EQ(0, octaspire_vector_get_length(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_peek_back_element_const_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_push_back_element(vec, &i));
        ASSERT_EQ(i, *(size_t const *)octaspire_vector_peek_back_element_const(vec));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_pop_front_element_called_on_empty_vector_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    void const * const originalElements     = vec->elements;
    size_t const       originalElementSize  = vec->elementSize;
    size_t const       originalNumElements  = vec->numElements;
    size_t const       originalNumAllocated = vec->numAllocated;

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT_FALSE(octaspire_vector_pop_front_element(vec));
    }

    ASSERT_EQ(originalElements,     vec->elements);
    ASSERT_EQ(originalElementSize,  vec->elementSize);
    ASSERT_EQ(originalNumElements,  vec->numElements);
    ASSERT_EQ(originalNumAllocated, vec->numAllocated);

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_pop_front_element_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_push_back_element(vec, &i));
        ASSERT_EQ(i, *(size_t const *)octaspire_vector_peek_back_element_const(vec));
    }

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_pop_front_element(vec));
        ASSERT_EQ(len - 1 - i, octaspire_vector_get_length(vec));

        if (!octaspire_vector_is_empty(vec))
        {
            ASSERT_EQ(i + 1, *(size_t const *)octaspire_vector_peek_front_element_const(vec));
        }
        else
        {
            ASSERT_EQ(len - 1, i);
        }
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_peek_front_element_called_on_empty_vector_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(octaspire_vector_peek_front_element(vec));
    }

    ASSERT_EQ(0, octaspire_vector_get_length(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_peek_front_element_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_push_front_element(vec, &i));
        ASSERT_EQ(i, *(size_t*)octaspire_vector_peek_front_element(vec));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_peek_front_element_const_called_on_empty_vector_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(octaspire_vector_peek_front_element_const(vec));
    }

    ASSERT_EQ(0, octaspire_vector_get_length(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_peek_front_element_const_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_push_front_element(vec, &i));
        ASSERT_EQ(i, *(size_t const *)octaspire_vector_peek_front_element_const(vec));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_get_element_release_callback_const_when_it_is_null_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(0, octaspire_vector_get_element_release_callback_const(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_get_element_release_callback_const_test(void)
{
    octaspire_vector_element_callback_t const expected =
        (octaspire_vector_element_callback_t)octaspire_vector_release;

    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(octaspire_vector_t*),
        true,
        expected,
        octaspireContainerVectorTestAllocator);

    ASSERT_EQ(
        expected,
        octaspire_vector_get_element_release_callback_const(vec));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_clear_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    size_t const len = 100;

    for (size_t i = 0; i < len; ++i)
    {
        ASSERT(octaspire_vector_push_front_element(vec, &i));
        ASSERT_EQ(i, *(size_t const *)octaspire_vector_peek_front_element_const(vec));
    }

    ASSERT_EQ(len, octaspire_vector_get_length(vec));

    ASSERT(octaspire_vector_clear(vec));

    ASSERT_EQ(0, octaspire_vector_get_length(vec));

    ASSERT_EQ(0, vec->numElements);
    ASSERT_EQ(1, vec->numAllocated);

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_clear_called_on_empty_vector_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    ASSERT_EQ(0, octaspire_vector_get_length(vec));

    ASSERT(octaspire_vector_clear(vec));

    ASSERT_EQ(0, octaspire_vector_get_length(vec));

    ASSERT_EQ(0, vec->numElements);
    ASSERT_EQ(1, vec->numAllocated);

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_is_valid_index_test(void)
{
    octaspire_vector_t *vec =
        octaspire_vector_new(sizeof(size_t), false, 0, octaspireContainerVectorTestAllocator);

    for (ptrdiff_t i = -10; i < 10; ++i)
    {
        ASSERT_FALSE(octaspire_vector_is_valid_index(vec, i));
    }

    size_t const element = 999;
    ASSERT(octaspire_vector_push_back_element(vec, &element));

    for (ptrdiff_t i = -10; i < 10; ++i)
    {
        ASSERT_EQ((i == -1 || i == 0), octaspire_vector_is_valid_index(vec, i));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_swap_indices_0_and_2_of_vector_containing_three_size_t_test(void)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 3; ++i)
    {
        ASSERT(octaspire_vector_push_back_element(vec, &i));
    }

    ASSERT(octaspire_vector_swap(vec, 0, 2));

    ASSERT_EQ(3, octaspire_vector_get_length(vec));

    ASSERT_EQ(
        2,
        *(size_t const * const)octaspire_vector_get_element_at(vec, 0));

    ASSERT_EQ(
        1,
        *(size_t const * const)octaspire_vector_get_element_at(vec, 1));

    ASSERT_EQ(
        0,
        *(size_t const * const)octaspire_vector_get_element_at(vec, 2));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_swap_indices_0_and_1_of_vector_containing_two_size_t_test(void)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 2; ++i)
    {
        ASSERT(octaspire_vector_push_back_element(vec, &i));
    }

    ASSERT(octaspire_vector_swap(vec, 0, 1));

    ASSERT_EQ(2, octaspire_vector_get_length(vec));

    ASSERT_EQ(
        1,
        *(size_t const * const)octaspire_vector_get_element_at(vec, 0));

    ASSERT_EQ(
        0,
        *(size_t const * const)octaspire_vector_get_element_at(vec, 1));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_swap_indices_2_and_3_of_vector_containing_six_chars_test(void)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(char),
        false,
        0,
        octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 6; ++i)
    {
        char const c = (char)i;
        ASSERT(octaspire_vector_push_back_element(vec, &c));
    }

    ASSERT(octaspire_vector_swap(vec, 2, 3));

    ASSERT_EQ(6, octaspire_vector_get_length(vec));

    ASSERT_EQ(
        0,
        *(char const * const)octaspire_vector_get_element_at(vec, 0));

    ASSERT_EQ(
        1,
        *(char const * const)octaspire_vector_get_element_at(vec, 1));

    ASSERT_EQ(
        3,
        *(char const * const)octaspire_vector_get_element_at(vec, 2));

    ASSERT_EQ(
        2,
        *(char const * const)octaspire_vector_get_element_at(vec, 3));

    ASSERT_EQ(
        4,
        *(char const * const)octaspire_vector_get_element_at(vec, 4));

    ASSERT_EQ(
        5,
        *(char const * const)octaspire_vector_get_element_at(vec, 5));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_swap_indices_0_and_5_of_vector_containing_six_chars_test(void)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(char),
        false,
        0,
        octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 6; ++i)
    {
        char const c = (char)i;
        ASSERT(octaspire_vector_push_back_element(vec, &c));
    }

    ASSERT(octaspire_vector_swap(vec, 0, 5));

    ASSERT_EQ(6, octaspire_vector_get_length(vec));

    ASSERT_EQ(
        0,
        *(char const * const)octaspire_vector_get_element_at(vec, 5));

    ASSERT_EQ(
        1,
        *(char const * const)octaspire_vector_get_element_at(vec, 1));

    ASSERT_EQ(
        2,
        *(char const * const)octaspire_vector_get_element_at(vec, 2));

    ASSERT_EQ(
        3,
        *(char const * const)octaspire_vector_get_element_at(vec, 3));

    ASSERT_EQ(
        4,
        *(char const * const)octaspire_vector_get_element_at(vec, 4));

    ASSERT_EQ(
        5,
        *(char const * const)octaspire_vector_get_element_at(vec, 0));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_swap_indices_0_and_5_of_vector_containing_six_shorts_test(void)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(short),
        false,
        0,
        octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 6; ++i)
    {
        short const s = (short)i;
        ASSERT(octaspire_vector_push_back_element(vec, &s));
    }

    ASSERT(octaspire_vector_swap(vec, 0, 5));

    ASSERT_EQ(6, octaspire_vector_get_length(vec));

    ASSERT_EQ(
        0,
        *(short const * const)octaspire_vector_get_element_at(vec, 5));

    ASSERT_EQ(
        1,
        *(short const * const)octaspire_vector_get_element_at(vec, 1));

    ASSERT_EQ(
        2,
        *(short const * const)octaspire_vector_get_element_at(vec, 2));

    ASSERT_EQ(
        3,
        *(short const * const)octaspire_vector_get_element_at(vec, 3));

    ASSERT_EQ(
        4,
        *(short const * const)octaspire_vector_get_element_at(vec, 4));

    ASSERT_EQ(
        5,
        *(short const * const)octaspire_vector_get_element_at(vec, 0));

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_permutation_iterator_0_short_test(void)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(short),
        false,
        0,
        octaspireContainerVectorTestAllocator);

    ASSERT_EQ(0, octaspire_vector_get_length(vec));

    octaspire_vector_permutation_iterator_t *iter =
        octaspire_vector_permutation_iterator_new(
            vec,
            octaspireContainerVectorTestAllocator);

    ASSERT(iter);

    ASSERT_EQ(0, octaspire_vector_get_element_at_const(vec, 0));
    ASSERT_FALSE(octaspire_vector_permutation_iterator_next(iter));
    ASSERT_EQ(0, octaspire_vector_get_element_at_const(vec, 0));

    octaspire_vector_permutation_iterator_release(iter);
    iter = 0;

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_permutation_iterator_1_short_test(void)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(short),
        false,
        0,
        octaspireContainerVectorTestAllocator);

    short const s = 0;
    ASSERT(octaspire_vector_push_back_element(vec, &s));

    ASSERT_EQ(1, octaspire_vector_get_length(vec));

    ASSERT_EQ(
        0,
        *(short const * const)octaspire_vector_get_element_at_const(
            vec,
            0));

    octaspire_vector_permutation_iterator_t *iter =
        octaspire_vector_permutation_iterator_new(
            vec,
            octaspireContainerVectorTestAllocator);

    ASSERT(iter);

    ASSERT_EQ(
        0,
        *(short const * const)octaspire_vector_get_element_at_const(vec, 0));

    for (size_t i = 0; i < 10; ++i)
    {
        ASSERT_FALSE(octaspire_vector_permutation_iterator_next(iter));

        ASSERT_EQ(
            0,
            *(short const * const)octaspire_vector_get_element_at_const(vec, 0));
    }

    octaspire_vector_permutation_iterator_release(iter);
    iter = 0;

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

static bool octaspire_vector_permutation_iterator_2_shorts_test_helper(
    octaspire_vector_t const * const vec,
    short const expected1,
    short const expected2)
{
    if (expected1 !=
        *(short const * const)octaspire_vector_get_element_at_const(vec, 0))
    {
        return false;
    }

    if (expected2 != 
        *(short const * const)octaspire_vector_get_element_at_const(vec, 1))
    {
        return false;
    }

    return true;
}

TEST octaspire_vector_permutation_iterator_2_shorts_test(void)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(short),
        false,
        0,
        octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 2; ++i)
    {
        short const s = (short)i;
        ASSERT(octaspire_vector_push_back_element(vec, &s));
    }

    ASSERT_EQ(2, octaspire_vector_get_length(vec));

    for (size_t i = 0; i < octaspire_vector_get_length(vec); ++i)
    {
        ASSERT_EQ(
            (short)i,
            *(short const * const)octaspire_vector_get_element_at_const(
                vec,
                (ptrdiff_t)i));
    }

    octaspire_vector_permutation_iterator_t *iter =
        octaspire_vector_permutation_iterator_new(
            vec,
            octaspireContainerVectorTestAllocator);

    ASSERT(iter);

    ASSERT(octaspire_vector_permutation_iterator_2_shorts_test_helper(
            vec, 0, 1));

    ASSERT(octaspire_vector_permutation_iterator_next(iter));

    ASSERT(octaspire_vector_permutation_iterator_2_shorts_test_helper(
            vec, 1, 0));

    for (size_t i = 0; i < 10; ++i)
    {
        ASSERT_FALSE(octaspire_vector_permutation_iterator_next(iter));
        ASSERT(octaspire_vector_permutation_iterator_2_shorts_test_helper(
                vec, 1, 0));
    }

    octaspire_vector_permutation_iterator_release(iter);
    iter = 0;

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

static bool octaspire_vector_permutation_iterator_3_longs_test_helper(
    octaspire_vector_t const * const vec,
    long const * const expected)
{
    if (expected[0] !=
        *(long const * const)octaspire_vector_get_element_at_const(vec, 0))
    {
        return false;
    }

    if (expected[1] != 
        *(long const * const)octaspire_vector_get_element_at_const(vec, 1))
    {
        return false;
    }

    if (expected[2] != 
        *(long const * const)octaspire_vector_get_element_at_const(vec, 2))
    {
        return false;
    }

    return true;
}

TEST octaspire_vector_permutation_iterator_3_longs_test(void)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(long),
        false,
        0,
        octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 3; ++i)
    {
        long const l = (long)i;
        ASSERT(octaspire_vector_push_back_element(vec, &l));
    }

    ASSERT_EQ(3, octaspire_vector_get_length(vec));

    for (size_t i = 0; i < octaspire_vector_get_length(vec); ++i)
    {
        ASSERT_EQ(
            (long)i,
            *(long const * const)octaspire_vector_get_element_at_const(
                vec,
                (ptrdiff_t)i));
    }

    octaspire_vector_permutation_iterator_t *iter =
        octaspire_vector_permutation_iterator_new(
            vec,
            octaspireContainerVectorTestAllocator);

    ASSERT(iter);

    long expected[6][3] = {
        {0, 1, 2},
        {1, 0, 2},
        {2, 0, 1},
        {0, 2, 1},
        {1, 2, 0},
        {2, 1, 0}
    };

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT(octaspire_vector_permutation_iterator_3_longs_test_helper(
                vec, expected[i]));

        if (i < 5)
        {
            ASSERT(octaspire_vector_permutation_iterator_next(iter));
        }
        else
        {
            ASSERT_FALSE(octaspire_vector_permutation_iterator_next(iter));
        }
    }

    for (size_t i = 0; i < 10; ++i)
    {
        ASSERT_FALSE(octaspire_vector_permutation_iterator_next(iter));
        ASSERT(octaspire_vector_permutation_iterator_3_longs_test_helper(
                vec, expected[5]));
    }

    octaspire_vector_permutation_iterator_release(iter);
    iter = 0;

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

static bool octaspire_vector_permutation_iterator_4_size_ts_test_helper(
    octaspire_vector_t const * const vec,
    size_t const * const expected)
{
    for (size_t i = 0; i < 4; ++i)
    {
        if (expected[i] !=
            *(size_t const * const)octaspire_vector_get_element_at_const(
                vec,
                (ptrdiff_t)i))
        {
            return false;
        }
    }

    return true;
}

TEST octaspire_vector_permutation_iterator_4_size_ts_test(void)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerVectorTestAllocator);

    for (size_t i = 0; i < 4; ++i)
    {
        ASSERT(octaspire_vector_push_back_element(vec, &i));
    }

    ASSERT_EQ(4, octaspire_vector_get_length(vec));

    for (size_t i = 0; i < octaspire_vector_get_length(vec); ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t const * const)octaspire_vector_get_element_at_const(
                vec,
                (ptrdiff_t)i));
    }

    octaspire_vector_permutation_iterator_t *iter =
        octaspire_vector_permutation_iterator_new(
            vec,
            octaspireContainerVectorTestAllocator);

    ASSERT(iter);

    size_t expected[24][4] = {
        {0, 1, 2, 3},
        {1, 0, 2, 3},
        {2, 0, 1, 3},
        {0, 2, 1, 3},
        {1, 2, 0, 3},
        {2, 1, 0, 3},
        {3, 1, 0, 2},
        {1, 3, 0, 2},
        {0, 3, 1, 2},
        {3, 0, 1, 2},
        {1, 0, 3, 2},
        {0, 1, 3, 2},
        {0, 2, 3, 1},
        {2, 0, 3, 1},
        {3, 0, 2, 1},
        {0, 3, 2, 1},
        {2, 3, 0, 1},
        {3, 2, 0, 1},
        {3, 2, 1, 0},
        {2, 3, 1, 0},
        {1, 3, 2, 0},
        {3, 1, 2, 0},
        {2, 1, 3, 0},
        {1, 2, 3, 0}
    };

    for (size_t i = 0; i < 24; ++i)
    {
        ASSERT(octaspire_vector_permutation_iterator_4_size_ts_test_helper(
                vec, expected[i]));

        if (i < 23)
        {
            ASSERT(octaspire_vector_permutation_iterator_next(iter));
        }
        else
        {
            ASSERT_FALSE(octaspire_vector_permutation_iterator_next(iter));
        }
    }

    for (size_t i = 0; i < 10; ++i)
    {
        ASSERT_FALSE(octaspire_vector_permutation_iterator_next(iter));
        ASSERT(octaspire_vector_permutation_iterator_4_size_ts_test_helper(
                vec, expected[23]));
    }

    octaspire_vector_permutation_iterator_release(iter);
    iter = 0;

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_vector_permutation_iterator_2_pointers_test(void)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(size_t*),
        true,
        0,
        octaspireContainerVectorTestAllocator);

    size_t const first  = 0;
    size_t const second = 1;

    size_t const * const p1 = &first;
    size_t const * const p2 = &second;

    ASSERT(octaspire_vector_push_back_element(vec, &p1));
    ASSERT(octaspire_vector_push_back_element(vec, &p2));

    ASSERT_EQ(2, octaspire_vector_get_length(vec));

    for (size_t i = 0; i < octaspire_vector_get_length(vec); ++i)
    {
        ASSERT_EQ(
            i,
            *(size_t const * const)octaspire_vector_get_element_at_const(
                vec,
                (ptrdiff_t)i));
    }

    octaspire_vector_permutation_iterator_t *iter =
        octaspire_vector_permutation_iterator_new(
            vec,
            octaspireContainerVectorTestAllocator);

    ASSERT(iter);

    ASSERT(octaspire_vector_permutation_iterator_next(iter));

    ASSERT_EQ(
        1,
        *(size_t const * const)octaspire_vector_get_element_at_const(vec, 0));

    ASSERT_EQ(
        0,
        *(size_t const * const)octaspire_vector_get_element_at_const(vec, 1));

    for (size_t i = 0; i < 10; ++i)
    {
        ASSERT_FALSE(octaspire_vector_permutation_iterator_next(iter));

        ASSERT_EQ(
            1,
            *(size_t const * const)octaspire_vector_get_element_at_const(
                vec,
                0));

        ASSERT_EQ(
            0,
            *(size_t const * const)octaspire_vector_get_element_at_const(
                vec,
                1));
    }

    octaspire_vector_permutation_iterator_release(iter);
    iter = 0;

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

GREATEST_SUITE(octaspire_vector_suite)
{
    octaspireContainerVectorTestAllocator = octaspire_allocator_new(0);
    assert(octaspireContainerVectorTestAllocator);

    RUN_TEST(octaspire_vector_private_index_to_pointer_test);
    RUN_TEST(octaspire_vector_private_index_to_pointer_const_test);
    RUN_TEST(octaspire_vector_private_grow_with_factor_2_success_test);
    RUN_TEST(octaspire_vector_private_grow_with_factor_100_success_test);
    RUN_TEST(octaspire_vector_private_grow_with_factor_2_even_when_zero_is_given_as_factor_success_test);
    RUN_TEST(octaspire_vector_private_grow_with_factor_2_even_when_one_is_given_as_factor_success_test);
    RUN_TEST(octaspire_vector_private_grow_failure_test);
    RUN_TEST(octaspire_vector_private_compact_success_test);
    RUN_TEST(octaspire_vector_private_compact_failure_test);
    RUN_TEST(octaspire_vector_new_test);
    RUN_TEST(octaspire_vector_new_failure_test);
    RUN_TEST(octaspire_vector_new_for_octaspire_string_elements_test);
    RUN_TEST(octaspire_vector_new_for_octaspire_string_elements_failure_test);
    RUN_TEST(octaspire_vector_new_with_preallocated_elements_test);
    RUN_TEST(octaspire_vector_new_with_preallocated_elements_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_vector_new_with_preallocated_elements_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_vector_new_shallow_copy_test);
    RUN_TEST(octaspire_vector_new_shallow_copy_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_vector_new_shallow_copy_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_vector_release_null_test);
    RUN_TEST(octaspire_vector_release_element_callback_called_for_all_elements_test);
    RUN_TEST(octaspire_vector_get_length_test);
    RUN_TEST(octaspire_vector_is_empty_test);

    RUN_TEST(octaspire_vector_remove_element_at_index_minus_one_100_times_of_100_elements_test);
    RUN_TEST(octaspire_vector_remove_element_at_index_0_of_100_elements_test);
    RUN_TEST(octaspire_vector_remove_element_at_index_50_of_100_elements_test);
    RUN_TEST(octaspire_vector_remove_element_at_index_99_of_100_elements_test);
    RUN_TEST(octaspire_vector_remove_element_at_failure_removing_index_100_of_100_elements_test);
    RUN_TEST(octaspire_vector_remove_element_at_failure_removing_indices_100_to_200_of_100_elements_test);
    RUN_TEST(octaspire_vector_remove_element_at_remove_all_100_elements_test);

    RUN_TEST(octaspire_vector_get_element_at_test);
    RUN_TEST(octaspire_vector_get_element_at_const_test);

    RUN_TEST(octaspire_vector_get_element_at_called_with_negative_indices_test);
    RUN_TEST(octaspire_vector_get_element_at_const_called_with_negative_indices_test);

    RUN_TEST(octaspire_vector_get_element_size_in_octets_when_element_is_of_type_uint8_t_test);
    RUN_TEST(octaspire_vector_get_element_size_in_octets_when_element_is_of_type_int_test);
    RUN_TEST(octaspire_vector_get_element_size_in_octets_when_element_is_of_type_size_t_test);
    RUN_TEST(octaspire_vector_get_element_size_in_octets_when_element_is_of_type_double_test);
    RUN_TEST(octaspire_vector_get_element_size_in_octets_when_element_is_of_type_void_ptr_test);
    RUN_TEST(octaspire_vector_get_element_size_in_octets_when_element_size_is_10000_test);
    RUN_TEST(octaspire_vector_get_element_size_in_octets_when_element_size_is_illegal_zero_test);
    RUN_TEST(octaspire_vector_insert_element_before_the_element_at_index_minus_one_test);
    RUN_TEST(octaspire_vector_insert_element_before_the_element_at_index_zero_test);
    RUN_TEST(octaspire_vector_insert_element_before_the_element_at_index_called_on_empty_vector_test);
    RUN_TEST(octaspire_vector_insert_element_before_the_element_at_index_the_end_test);
    RUN_TEST(octaspire_vector_insert_element_before_the_element_at_index_past_the_end_test);
    RUN_TEST(octaspire_vector_insert_element_before_the_element_at_index_allocation_failure_test);
    RUN_TEST(octaspire_vector_insert_element_before_the_element_at_index_the_middle_test);
    RUN_TEST(octaspire_vector_insert_element_at_test);

    RUN_TEST(octaspire_vector_replace_element_at_test);

    RUN_TEST(octaspire_vector_replace_element_at_index_or_push_back_test);

    RUN_TEST(octaspire_vector_insert_element_at_index_100_of_empty_vector_test);
    RUN_TEST(octaspire_vector_insert_element_at_failure_test);
    RUN_TEST(octaspire_vector_push_front_element_test);
    RUN_TEST(octaspire_vector_push_back_element_test);
    RUN_TEST(octaspire_vector_push_back_char_test);
    RUN_TEST(octaspire_vector_push_back_char_to_vector_containing_floats_test);
    RUN_TEST(octaspire_vector_for_each_called_on_empty_vector_test);
    RUN_TEST(octaspire_vector_for_each_called_on_vector_with_one_element_test);
    RUN_TEST(octaspire_vector_for_each_called_on_vector_with_hundred_elements_test);
    RUN_TEST(octaspire_vector_for_each_called_on_vector_that_grows_during_iteration_test);
    RUN_TEST(octaspire_vector_for_each_called_on_vector_that_shrinks_during_iteration_test);
    RUN_TEST(octaspire_vector_pop_back_element_called_on_empty_vector_test);
    RUN_TEST(octaspire_vector_pop_back_element_test);
    RUN_TEST(octaspire_vector_peek_back_element_called_on_empty_vector_test);
    RUN_TEST(octaspire_vector_peek_back_element_test);
    RUN_TEST(octaspire_vector_peek_back_element_const_called_on_empty_vector_test);
    RUN_TEST(octaspire_vector_peek_back_element_const_test);
    RUN_TEST(octaspire_vector_pop_front_element_called_on_empty_vector_test);
    RUN_TEST(octaspire_vector_pop_front_element_test);
    RUN_TEST(octaspire_vector_peek_front_element_called_on_empty_vector_test);
    RUN_TEST(octaspire_vector_peek_front_element_test);
    RUN_TEST(octaspire_vector_peek_front_element_const_called_on_empty_vector_test);
    RUN_TEST(octaspire_vector_peek_front_element_const_test);
    RUN_TEST(octaspire_vector_get_element_release_callback_const_when_it_is_null_test);
    RUN_TEST(octaspire_vector_get_element_release_callback_const_test);
    RUN_TEST(octaspire_vector_clear_test);
    RUN_TEST(octaspire_vector_clear_called_on_empty_vector_test);

    RUN_TEST(octaspire_vector_is_valid_index_test);

    RUN_TEST(octaspire_vector_swap_indices_0_and_2_of_vector_containing_three_size_t_test);
    RUN_TEST(octaspire_vector_swap_indices_0_and_1_of_vector_containing_two_size_t_test);
    RUN_TEST(octaspire_vector_swap_indices_2_and_3_of_vector_containing_six_chars_test);
    RUN_TEST(octaspire_vector_swap_indices_0_and_5_of_vector_containing_six_chars_test);
    RUN_TEST(octaspire_vector_swap_indices_0_and_5_of_vector_containing_six_shorts_test);

    RUN_TEST(octaspire_vector_permutation_iterator_0_short_test);
    RUN_TEST(octaspire_vector_permutation_iterator_1_short_test);
    RUN_TEST(octaspire_vector_permutation_iterator_2_shorts_test);
    RUN_TEST(octaspire_vector_permutation_iterator_3_longs_test);
    RUN_TEST(octaspire_vector_permutation_iterator_4_size_ts_test);
    RUN_TEST(octaspire_vector_permutation_iterator_2_pointers_test);

    octaspire_allocator_release(octaspireContainerVectorTestAllocator);
    octaspireContainerVectorTestAllocator = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/test/test_vector.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/test/test_list.c
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

static octaspire_allocator_t *octaspireContainerListTestAllocator = 0;

TEST octaspire_list_new_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_new_allocation_failure_on_first_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerListTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerListTestAllocator));

    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT_EQ(0, list);

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerListTestAllocator));

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_release_called_with_null_pointer_test(void)
{
    octaspire_list_release(0);

    PASS();
}

TEST octaspire_list_get_front_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    ASSERT_EQ(0, octaspire_list_get_front(list));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_front(list, &i));

        octaspire_list_node_t const * const front =
            octaspire_list_get_front(list);

        ASSERT_EQ(i, *((size_t const * const)octaspire_list_node_get_element_const(front)));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_get_front_const_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    ASSERT_EQ(0, octaspire_list_get_front_const(list));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_front(list, &i));

        octaspire_list_node_t const * const front =
            octaspire_list_get_front_const(list);

        ASSERT_EQ(i, *((size_t const * const)octaspire_list_node_get_element_const(front)));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_get_back_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    ASSERT_EQ(0, octaspire_list_get_back(list));

    size_t const numElements = 10;

    octaspire_list_node_t const *first = 0;
    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));

        octaspire_list_node_t const * const back =
            octaspire_list_get_back(list);

        if (i == 0)
        {
            first = back;
        }

        ASSERT_EQ(first, octaspire_list_get_front(list));
        ASSERT_EQ(i, *((size_t const * const)octaspire_list_node_get_element_const(back)));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_get_back_const_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    ASSERT_EQ(0, octaspire_list_get_back_const(list));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));

        octaspire_list_node_t const * const back =
            octaspire_list_get_back_const(list);

        ASSERT_EQ(i, *((size_t const * const)octaspire_list_node_get_element_const(back)));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_clear_called_on_empty_list_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
            sizeof(size_t),
            false,
            0,
            octaspireContainerListTestAllocator);

    ASSERT(list);

    ASSERT_EQ(0, octaspire_list_get_length(list));

    ASSERT(octaspire_list_clear(list));

    ASSERT_EQ(0, octaspire_list_get_length(list));

    ASSERT_EQ(0, list->numElements);

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_clear_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));
    }

    ASSERT_EQ(numElements, list->numElements);

    ASSERT(octaspire_list_clear(list));

    ASSERT_EQ(0, octaspire_list_get_length(list));
    ASSERT_EQ(0, list->numElements);

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_push_back_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    ASSERT_EQ(0, octaspire_list_get_length(list));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));

        ASSERT_EQ(i + 1, octaspire_list_get_length(list));
        octaspire_list_node_t const * front = octaspire_list_get_front(list);
        octaspire_list_node_t const * back  = octaspire_list_get_back(list);

        ASSERT_EQ(0,     *((size_t const * const)octaspire_list_node_get_element_const(front)));
        ASSERT_EQ(i,     *((size_t const * const)octaspire_list_node_get_element_const(back)));
    }

    ASSERT_EQ(numElements, list->numElements);

    octaspire_list_node_t const * node = octaspire_list_get_front(list);

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(node);
        ASSERT_EQ(i, *((size_t const * const)octaspire_list_node_get_element_const(node)));
        node = octaspire_list_node_get_next_const(node);
    }

    ASSERT(node == 0);

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_push_front_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    ASSERT_EQ(0, octaspire_list_get_length(list));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_front(list, &i));

        ASSERT_EQ(i + 1, octaspire_list_get_length(list));
        octaspire_list_node_t const * front = octaspire_list_get_front(list);
        octaspire_list_node_t const * back  = octaspire_list_get_back(list);

        ASSERT_EQ(i,     *((size_t const * const)octaspire_list_node_get_element_const(front)));
        ASSERT_EQ(0,     *((size_t const * const)octaspire_list_node_get_element_const(back)));
    }

    ASSERT_EQ(numElements, list->numElements);

    octaspire_list_node_t const * node = octaspire_list_get_front(list);

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(node);
        ASSERT_EQ(numElements - 1 - i, *((size_t const * const)octaspire_list_node_get_element_const(node)));
        node = octaspire_list_node_get_next_const(node);
    }

    ASSERT(node == 0);

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_pop_front_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));
    }

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_list_node_t const * node = octaspire_list_get_front(list);
        ASSERT(node);
        ASSERT_EQ(i, *((size_t const * const)octaspire_list_node_get_element_const(node)));

        ASSERT(octaspire_list_pop_front(list));
    }

    ASSERT_EQ(0, octaspire_list_get_length(list));
    ASSERT_EQ(0, octaspire_list_get_front(list));
    ASSERT_EQ(0, octaspire_list_get_back(list));

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_pop_back_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));
    }

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_list_node_t const * const first1 =
            octaspire_list_get_front_const(list);

        ASSERT(first1);
        ASSERT_EQ(0, *((size_t const * const)octaspire_list_node_get_element_const(first1)));

        ASSERT(octaspire_list_pop_back(list));

        if (i < (numElements - 1))
        {
            // Make sure that front doesn't change
            octaspire_list_node_t const * const first2 =
                octaspire_list_get_front_const(list);

            ASSERT(first2);
            ASSERT_EQ(first1, first2);

            // Check back
            octaspire_list_node_t const * const last =
                octaspire_list_get_back_const(list);

            ASSERT(last);

            ASSERT_EQ(
                numElements - 2 - i,
                *((size_t const * const)octaspire_list_node_get_element_const(last)));
        }
    }

    ASSERT_EQ(0, octaspire_list_get_length(list));
    ASSERT_EQ(0, octaspire_list_get_front(list));
    ASSERT_EQ(0, octaspire_list_get_back(list));

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_remove_middle_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    size_t const numElements = 10;

    octaspire_list_node_t * node = 0;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));

        if (i == 5)
        {
            node = octaspire_list_get_back(list);
        }
    }

    ASSERT(node);
    ASSERT(octaspire_list_remove(list, node));

    ASSERT_EQ(numElements - 1, octaspire_list_get_length(list));

    for (size_t i = 0; i < (numElements - 1); ++i)
    {
        node = octaspire_list_get_at(list, (ptrdiff_t)i);

        ASSERT(node);

        if (i < 5)
        {
            ASSERT_EQ(
                i < 5 ? i : (i + 1),
                *((size_t const * const)octaspire_list_node_get_element_const(node)));
        }
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_remove_first_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    size_t const numElements = 10;

    octaspire_list_node_t * node = 0;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));

        if (i == 0)
        {
            node = octaspire_list_get_back(list);
        }
    }

    ASSERT(node);
    ASSERT(octaspire_list_remove(list, node));

    ASSERT_EQ(numElements - 1, octaspire_list_get_length(list));

    for (size_t i = 0; i < (numElements - 1); ++i)
    {
        node = octaspire_list_get_at(list, (ptrdiff_t)i);

        ASSERT(node);

        ASSERT_EQ(
            (i + 1),
            *((size_t const * const)octaspire_list_node_get_element_const(node)));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_remove_last_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    size_t const numElements = 10;

    octaspire_list_node_t * node = 0;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));

        if (i == (numElements - 1))
        {
            node = octaspire_list_get_back(list);
        }
    }

    ASSERT(node);
    ASSERT(octaspire_list_remove(list, node));

    ASSERT_EQ(numElements - 1, octaspire_list_get_length(list));

    for (size_t i = 0; i < (numElements - 1); ++i)
    {
        node = octaspire_list_get_at(list, (ptrdiff_t)i);

        ASSERT(node);

        ASSERT_EQ(
            i,
            *((size_t const * const)octaspire_list_node_get_element_const(node)));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_remove_even_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));
    }

    octaspire_list_node_t *node = octaspire_list_get_front(list);
    size_t index = 0;

    while (node)
    {
        octaspire_list_node_t * const next = octaspire_list_node_get_next(node);

        if (index % 2 == 0)
        {
            octaspire_list_remove(list, node);
            node = 0;
        }

        ++index;

        node = next;
    }

    ASSERT_EQ(5, octaspire_list_get_length(list));

    node = octaspire_list_get_front(list);
    index = 0;

    while (node)
    {
        octaspire_list_node_t * const next = octaspire_list_node_get_next(node);

        if (index % 2 == 0)
        {
            ++index;
        }

        ASSERT_EQ(
            index,
            *((size_t const * const)octaspire_list_node_get_element_const(node)));

        ++index;

        node = next;
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_get_at_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));
    }

    // Positive indices
    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_list_node_t const * const node =
            octaspire_list_get_at(list, (ptrdiff_t)i);

        ASSERT_EQ(
            i,
            *((size_t const * const)octaspire_list_node_get_element_const(node)));
    }

    // Negative indices
    for (size_t i = 0; i < numElements; ++i)
    {
        ptrdiff_t tmpIndex = -1 - (ptrdiff_t)i;
        octaspire_list_node_t const * const node =
            octaspire_list_get_at(list, tmpIndex);

        ASSERT_EQ(
            numElements - 1 - i,
            *((size_t const * const)octaspire_list_node_get_element_const(node)));
    }

    // Test failure
    ASSERT_FALSE(octaspire_list_get_at(list, numElements + 1));
    ASSERT_FALSE(octaspire_list_get_at(list, -((ptrdiff_t)(numElements + 2))));

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_get_at_const_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));
    }

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_list_node_t const * const node =
            octaspire_list_get_at_const(list, (ptrdiff_t)i);

        ASSERT_EQ(
            i,
            *((size_t const * const)octaspire_list_node_get_element_const(node)));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_node_iterator_called_on_empty_list_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    octaspire_list_node_iterator_t iter =
        octaspire_list_node_iterator_init(list);

    for (size_t i = 0; i < 10; ++i)
    {
        ASSERT_EQ(iter.list, list);
        ASSERT_FALSE(iter.currentNode);
        ASSERT_FALSE(octaspire_list_node_iterator_next(&iter));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_node_iterator_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));
    }

    octaspire_list_node_iterator_t iter =
        octaspire_list_node_iterator_init(list);

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(iter.currentNode);

        size_t const fromIter =
            *(size_t const * const)octaspire_list_node_get_element_const(
                iter.currentNode);

        ASSERT_EQ(iter.list, list);
        ASSERT_EQ(i, fromIter);

        if ((i + 1) < numElements)
        {
            ASSERT(octaspire_list_node_iterator_next(&iter));
        }
    }

    ASSERT_FALSE(octaspire_list_node_iterator_next(&iter));
    ASSERT_FALSE(iter.currentNode);

    octaspire_list_release(list);
    list = 0;

    PASS();
}

GREATEST_SUITE(octaspire_list_suite)
{
    octaspireContainerListTestAllocator = octaspire_allocator_new(0);
    assert(octaspireContainerListTestAllocator);

    RUN_TEST(octaspire_list_new_test);
    RUN_TEST(octaspire_list_new_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_list_release_called_with_null_pointer_test);
    RUN_TEST(octaspire_list_get_front_test);
    RUN_TEST(octaspire_list_get_front_const_test);
    RUN_TEST(octaspire_list_get_back_test);
    RUN_TEST(octaspire_list_get_back_const_test);
    RUN_TEST(octaspire_list_clear_called_on_empty_list_test);
    RUN_TEST(octaspire_list_clear_test);
    RUN_TEST(octaspire_list_push_back_test);
    RUN_TEST(octaspire_list_push_front_test);
    RUN_TEST(octaspire_list_pop_front_test);
    RUN_TEST(octaspire_list_pop_back_test);
    RUN_TEST(octaspire_list_remove_middle_test);
    RUN_TEST(octaspire_list_remove_first_test);
    RUN_TEST(octaspire_list_remove_last_test);
    RUN_TEST(octaspire_list_remove_even_test);
    RUN_TEST(octaspire_list_get_at_test);
    RUN_TEST(octaspire_list_get_at_const_test);
    RUN_TEST(octaspire_list_node_iterator_called_on_empty_list_test);
    RUN_TEST(octaspire_list_node_iterator_test);

    octaspire_allocator_release(octaspireContainerListTestAllocator);
    octaspireContainerListTestAllocator = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/test/test_list.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/test/test_queue.c
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

static octaspire_allocator_t *octaspireContainerQueueTestAllocator = 0;

TEST octaspire_queue_new_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);
    ASSERT_EQ(0, octaspire_queue_get_max_length(queue));
    ASSERT_FALSE(octaspire_queue_has_max_length(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_new_allocation_failure_on_first_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerQueueTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerQueueTestAllocator));

    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT_EQ(0, queue);

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerQueueTestAllocator));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_new_with_max_length_of_56_with_size_t_elements_test(void)
{
    size_t const maxLength = 56;

    octaspire_queue_t *queue = octaspire_queue_new_with_max_length(
        maxLength,
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);
    ASSERT_EQ(maxLength, octaspire_queue_get_max_length(queue));
    ASSERT(octaspire_queue_has_max_length(queue));

    for (size_t i = 0; i < (3 * maxLength); ++i)
    {
        octaspire_queue_push(queue, &i);

        ASSERT(octaspire_queue_get_length(queue) <= maxLength);

        ASSERT_EQ(
            i < maxLength ? 0 : (i + 1 - maxLength),
            *(size_t const * const)octaspire_queue_peek(queue));

        size_t firstExpectedNumber = 0;

        if (i >= (maxLength-1))
        {
            firstExpectedNumber += (i - (maxLength - 1));
        }

        for (size_t j = 0; j < octaspire_queue_get_length(queue); ++j)
        {
            size_t const storedNum =
                *(size_t const * const)octaspire_queue_get_at_const(
                    queue,
                    (ptrdiff_t)j);

            size_t const expectedNum = firstExpectedNumber + j;

            ASSERT_EQ(expectedNum, storedNum);
        }
    }

    ASSERT_EQ(maxLength, octaspire_queue_get_length(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_new_with_max_length_of_10_with_ostring_ptr_elements_test(void)
{
    size_t const maxLength = 10;

    octaspire_queue_t *queue = octaspire_queue_new_with_max_length(
        maxLength,
        sizeof(octaspire_string_t*),
        true,
        (octaspire_queue_element_callback_t)octaspire_string_release,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);
    ASSERT_EQ(maxLength, octaspire_queue_get_max_length(queue));
    ASSERT(octaspire_queue_has_max_length(queue));

    for (size_t i = 0; i < (3 * maxLength); ++i)
    {
        octaspire_string_t * const str = octaspire_string_new_format(
            octaspireContainerQueueTestAllocator,
            "This is string %zu.",
            i);

        octaspire_queue_push(queue, &str);

        ASSERT(octaspire_queue_get_length(queue) <= maxLength);

        size_t firstExpectedNumber = 0;

        if (i >= maxLength)
        {
            firstExpectedNumber += (i - (maxLength - 1));
        }

        for (size_t j = 0; j < octaspire_queue_get_length(queue); ++j)
        {
            octaspire_string_t const * const storedStr =
                octaspire_queue_get_at_const(
                    queue,
                    (ptrdiff_t)j);

            octaspire_string_t * expectedStr =
                octaspire_string_new_format(
                    octaspireContainerQueueTestAllocator,
                    "This is string %zu.",
                    firstExpectedNumber + j);

            ASSERT(octaspire_string_is_equal(expectedStr, storedStr));

            octaspire_string_release(expectedStr);
            expectedStr = 0;
        }
    }

    ASSERT_EQ(maxLength, octaspire_queue_get_length(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_release_called_with_null_pointer_test(void)
{
    octaspire_queue_release(0);

    PASS();
}

TEST octaspire_queue_peek_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    ASSERT_EQ(0, octaspire_queue_peek(queue));

    size_t const expected = 123;
    ASSERT(octaspire_queue_push(queue, &expected));
    ASSERT_EQ(expected, *(size_t const * const)octaspire_queue_peek(queue));

    size_t const next = 9876;
    ASSERT(octaspire_queue_push(queue, &next));
    ASSERT_EQ(expected, *(size_t const * const)octaspire_queue_peek(queue));

    ASSERT(octaspire_queue_pop(queue));
    ASSERT_EQ(next, *(size_t const * const)octaspire_queue_peek(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_peek_const_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    ASSERT_EQ(0, octaspire_queue_peek_const(queue));

    size_t const expected = 123;
    ASSERT(octaspire_queue_push(queue, &expected));
    ASSERT_EQ(expected, *(size_t const * const)octaspire_queue_peek_const(queue));

    size_t const next = 9876;
    ASSERT(octaspire_queue_push(queue, &next));
    ASSERT_EQ(expected, *(size_t const * const)octaspire_queue_peek_const(queue));

    ASSERT(octaspire_queue_pop(queue));
    ASSERT_EQ(next, *(size_t const * const)octaspire_queue_peek_const(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_pop_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    size_t const numElements = 100;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));
    }

    ASSERT_EQ(numElements, octaspire_queue_get_length(queue));

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_pop(queue));
        size_t const * const ptr = (size_t const * const)octaspire_queue_peek(queue);

        if (i != (numElements -1))
        {
            ASSERT(ptr);
            ASSERT_EQ(i + 1, *ptr);
        }
        else
        {
            ASSERT_FALSE(ptr);
        }
    }

    ASSERT_EQ(0, octaspire_queue_get_length(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_push_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    size_t const numElements = 100;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT_EQ(i, octaspire_queue_get_length(queue));
        ASSERT(octaspire_queue_push(queue, &i));
        ASSERT_EQ(i + 1, octaspire_queue_get_length(queue));
        size_t const * const ptr = (size_t const * const)octaspire_queue_peek(queue);
        ASSERT_EQ(0, *ptr);

        for (size_t j = 0; j < octaspire_queue_get_length(queue); ++j)
        {
            size_t const * const jth =
                (size_t const * const)octaspire_queue_get_at(
                    queue,
                    (ptrdiff_t)j);

            ASSERT_EQ(j, *jth);
        }
    }

    ASSERT_EQ(numElements, octaspire_queue_get_length(queue));

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_pop(queue));
        size_t const * const ptr = (size_t const * const)octaspire_queue_peek(queue);

        if (i != (numElements -1))
        {
            ASSERT(ptr);
            ASSERT_EQ(i + 1, *ptr);
        }
        else
        {
            ASSERT_FALSE(ptr);
        }
    }

    ASSERT_EQ(0, octaspire_queue_get_length(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_clear_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    ASSERT(octaspire_queue_clear(queue));
    ASSERT(octaspire_queue_is_empty(queue));
    ASSERT_EQ(0, octaspire_queue_get_length(queue));
    ASSERT_FALSE(octaspire_queue_peek(queue));

    size_t const value = 10;
    ASSERT(octaspire_queue_push(queue, &value));

    ASSERT(octaspire_queue_clear(queue));
    ASSERT(octaspire_queue_is_empty(queue));
    ASSERT_EQ(0, octaspire_queue_get_length(queue));
    ASSERT_FALSE(octaspire_queue_peek(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_get_length_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    ASSERT_EQ(0, octaspire_queue_get_length(queue));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));
        ASSERT_EQ(i + 1, octaspire_queue_get_length(queue));
    }

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_pop(queue));
        ASSERT_EQ(numElements - 1 - i, octaspire_queue_get_length(queue));
    }

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_is_empty_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    ASSERT(octaspire_queue_is_empty(queue));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));
        ASSERT_FALSE(octaspire_queue_is_empty(queue));
    }

    for (size_t i = 0; i < (numElements - 1); ++i)
    {
        ASSERT(octaspire_queue_pop(queue));
        ASSERT_FALSE(octaspire_queue_is_empty(queue));
    }

    ASSERT(octaspire_queue_pop(queue));
    ASSERT(octaspire_queue_is_empty(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_get_at_failure_on_too_large_index_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    ASSERT_FALSE(octaspire_queue_get_at(queue, 0));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));

        size_t j;
        for (j = 0; j < i; ++j)
        {
            ASSERT(octaspire_queue_get_at(queue, (ptrdiff_t)j));
        }

        ++j;
        ASSERT_FALSE(octaspire_queue_get_at(queue, (ptrdiff_t)j));
    }

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_get_at_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    size_t const numElements = 100;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));

        for (size_t j = 0; j < i; ++j)
        {
            size_t const * const ptr =
                octaspire_queue_get_at(queue, (ptrdiff_t)j);

            ASSERT(ptr);
            ASSERT_EQ(j, *ptr);
        }

        // Negative index
        size_t * const ptr =
            octaspire_queue_get_at(queue, -1);

        ASSERT(ptr);
        ASSERT_EQ(i, *ptr);

        // Failure test
        ASSERT_FALSE(octaspire_queue_get_at(
            queue,
            -((ptrdiff_t)(i + 2))));

        ASSERT_FALSE(octaspire_queue_get_at(
            queue,
            (ptrdiff_t)(i + 1)));
    }

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_get_at_const_failure_on_too_large_index_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    ASSERT_FALSE(octaspire_queue_get_at_const(queue, 0));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));

        size_t j;
        for (j = 0; j < i; ++j)
        {
            ASSERT(octaspire_queue_get_at_const(queue, (ptrdiff_t)j));
        }

        ++j;
        ASSERT_FALSE(octaspire_queue_get_at_const(queue, (ptrdiff_t)j));
    }

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_get_at_const_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    size_t const numElements = 100;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));

        for (size_t j = 0; j < i; ++j)
        {
            size_t const * const ptr =
                octaspire_queue_get_at_const(
                    queue,
                    (ptrdiff_t)j);
            ASSERT(ptr);
            ASSERT_EQ(j, *ptr);
        }

        // Negative index
        size_t const * const ptr =
            octaspire_queue_get_at_const(queue, -1);

        ASSERT(ptr);
        ASSERT_EQ(i, *ptr);

        // Failure test
        ASSERT_FALSE(octaspire_queue_get_at_const(
            queue,
            -((ptrdiff_t)(i + 2))));

        ASSERT_FALSE(octaspire_queue_get_at_const(
            queue,
            (ptrdiff_t)(i + 1)));
    }

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_get_set_has_max_length_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT_EQ(0, octaspire_queue_get_max_length(queue));
    ASSERT_FALSE(octaspire_queue_has_max_length(queue));

    size_t const value = 100;

    for (size_t i = 0; i < value; ++i)
    {
        ASSERT(octaspire_queue_set_max_length(queue, i));
        ASSERT_EQ(i, octaspire_queue_get_max_length(queue));
        ASSERT_EQ(0, octaspire_queue_get_length(queue));
    }

    size_t const numElements = 256;
    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));
    }

    ASSERT_EQ(numElements, octaspire_queue_get_length(queue));
    ASSERT_FALSE(octaspire_queue_has_max_length(queue));

    for (size_t i = value; i > 0; --i)
    {
        ASSERT(octaspire_queue_set_max_length(queue, i));
        ASSERT(octaspire_queue_set_has_max_length(queue, true));
        ASSERT(octaspire_queue_has_max_length(queue));
        ASSERT_EQ(i, octaspire_queue_get_max_length(queue));
        ASSERT_EQ(i, octaspire_queue_get_length(queue));
    }

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_iterator_called_on_empty_queue_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    octaspire_queue_iterator_t iter =
        octaspire_queue_iterator_init(queue);

    for (size_t i = 0; i < 10; ++i)
    {
        ASSERT_EQ(iter.queue, queue);
        ASSERT_FALSE(iter.iterator.currentNode);
        ASSERT_FALSE(octaspire_queue_iterator_next(&iter));
    }

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_iterator_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));
    }

    octaspire_queue_iterator_t iter =
        octaspire_queue_iterator_init(queue);

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(iter.iterator.currentNode);

        size_t const fromIter =
            *(size_t const * const)octaspire_list_node_get_element_const(
                iter.iterator.currentNode);

        ASSERT_EQ(iter.queue, queue);
        ASSERT_EQ(i, fromIter);

        if ((i + 1) < numElements)
        {
            ASSERT(octaspire_queue_iterator_next(&iter));
        }
    }

    ASSERT_FALSE(octaspire_queue_iterator_next(&iter));
    ASSERT_FALSE(iter.iterator.currentNode);

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

GREATEST_SUITE(octaspire_queue_suite)
{
    octaspireContainerQueueTestAllocator = octaspire_allocator_new(0);
    assert(octaspireContainerQueueTestAllocator);

    RUN_TEST(octaspire_queue_new_test);
    RUN_TEST(octaspire_queue_new_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_queue_new_with_max_length_of_56_with_size_t_elements_test);
    RUN_TEST(octaspire_queue_new_with_max_length_of_10_with_ostring_ptr_elements_test);
    RUN_TEST(octaspire_queue_release_called_with_null_pointer_test);
    RUN_TEST(octaspire_queue_peek_test);
    RUN_TEST(octaspire_queue_peek_const_test);
    RUN_TEST(octaspire_queue_pop_test);
    RUN_TEST(octaspire_queue_push_test);
    RUN_TEST(octaspire_queue_clear_test);
    RUN_TEST(octaspire_queue_get_length_test);
    RUN_TEST(octaspire_queue_is_empty_test);
    RUN_TEST(octaspire_queue_get_at_failure_on_too_large_index_test);
    RUN_TEST(octaspire_queue_get_at_test);
    RUN_TEST(octaspire_queue_get_at_const_failure_on_too_large_index_test);
    RUN_TEST(octaspire_queue_get_at_const_test);
    RUN_TEST(octaspire_queue_get_set_has_max_length_test);
    RUN_TEST(octaspire_queue_iterator_called_on_empty_queue_test);
    RUN_TEST(octaspire_queue_iterator_test);

    octaspire_allocator_release(octaspireContainerQueueTestAllocator);
    octaspireContainerQueueTestAllocator = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/test/test_queue.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/test/test_string.c
//////////////////////////////////////////////////////////////////////////////////////////////////
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

static octaspire_allocator_t *octaspireContainerUtf8StringTestAllocator = 0;

TEST octaspire_string_new_called_with_null_argument_test(void)
{
    octaspire_string_t *str =
        octaspire_string_new(0, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_with_simple_ascii_string_test(void)
{
    char const * const expected = "Hello World!";
    octaspire_string_t *str =
        octaspire_string_new(expected, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(strlen((char const * const)expected), octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(strlen((char const * const)expected), octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ(expected, octaspire_string_get_c_string(str));

    for (size_t i = 0; i < octaspire_string_get_length_in_ucs_characters(str); ++i)
    {
        ASSERT_EQ(
            (uint32_t)(expected[i]),
            octaspire_string_get_ucs_character_at_index(
                str,
                (ptrdiff_t)i));
    }

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_with_some_multioctet_ucs_characters_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_with_simple_ascii_string_with_error_test(void)
{
    char const * const input    = "Hello World\xC0\xB3";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_DECODING_ERROR, str->errorStatus);
    ASSERT_EQ(11,                                                          str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                                   str->allocator);

    ASSERT(octaspire_string_is_error(str));
    ASSERT_EQ(11, octaspire_string_get_error_position_in_octets(str));

    char const * const expected = "Hello World";

    ASSERT_EQ(strlen((char const * const)expected), octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(strlen((char const * const)expected), octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ(expected, octaspire_string_get_c_string(str));

    for (size_t i = 0;
         i < octaspire_string_get_length_in_ucs_characters(str);
         ++i)
    {
        ASSERT_EQ(
            (uint32_t)(expected[i]),
            octaspire_string_get_ucs_character_at_index(
                str,
                (ptrdiff_t)i));
    }

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_from_buffer_with_some_multioctet_ucs_characters_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    size_t const       lengthInOctets      = strlen(input);
    octaspire_string_t *str =
        octaspire_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_from_buffer_allocation_failure_on_first_allocation_test(void)
{
#ifdef _MSC_VER
    char const * const input = u8"©Hello World! © ≠𐀀How are you?";
#else
    char const * const input = "©Hello World! © ≠𐀀How are you?";
#endif

    size_t const       lengthInOctets      = strlen(input);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    octaspire_string_t *str =
        octaspire_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    ASSERT_FALSE(str);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_from_buffer_allocation_failure_on_second_allocation_test(void)
{
#ifdef _MSC_VER
    char const * const input = u8"©Hello World! © ≠𐀀How are you?";
#else
    char const * const input = "©Hello World! © ≠𐀀How are you?";
#endif

    size_t const       lengthInOctets      = strlen(input);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 2, 0x01);
    ASSERT_EQ(2, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    octaspire_string_t *str =
        octaspire_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    ASSERT_FALSE(str);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_from_buffer_allocation_failure_on_third_allocation_test(void)
{
#ifdef _MSC_VER
    char const * const input = u8"©Hello World! © ≠𐀀How are you?";
#else
    char const * const input = "©Hello World! © ≠𐀀How are you?";
#endif

    size_t const       lengthInOctets      = strlen(input);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 3, 0x03);
    ASSERT_EQ(3, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    octaspire_string_t *str =
        octaspire_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    ASSERT_FALSE(str);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_from_buffer_allocation_failure_on_sixth_2_allocation_test(void)
{
#ifdef _MSC_VER
    char const * const input = u8"©Hello World! © ≠𐀀How are you?";
#else
    char const * const input = "©Hello World! © ≠𐀀How are you?";
#endif

    size_t const       lengthInOctets      = strlen(input);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 6, 0x1F);
    ASSERT_EQ(6, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    octaspire_string_t *str =
        octaspire_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    ASSERT_FALSE(str);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_format_with_string_test(void)
{
    char const * const name  = "Mike";
    char const * const input = "Hello! My name is %s. What's yours?";
    octaspire_string_t *str =
        octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, input, name);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(37, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "Hello! My name is Mike. What's yours?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_format_with_size_t_test(void)
{
    size_t const value = 62039;

    char const * const input = "©Hello World! © ≠𐀀How are you? My age is %zu. What's yours?";

    octaspire_string_t *str =
        octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, input, value);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(68, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(61, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you? My age is 62039. What's yours?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_format_with_doubles_test(void)
{
    double const value1 = 12.001;
    double const value2 = 2015.12;
    double const value3 = 4.9;
    char const * const input = "The doubles are %g, %g and %g\n";
    octaspire_string_t *str =
        octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, input, value1, value2, value3);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(40, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(40, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = "The doubles are 12.001, 2015.12 and 4.9\n";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_format_with_string_and_size_t_test(void)
{
    size_t const value = 62039;

    char const * const name  = "©Hello";

    char const * const input =
        "©Hello World! © ≠𐀀How are you? My name is \"%s\" and my age is %zu. What's yours?";

    octaspire_string_t *str =
        octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, input, name, value);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(93, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(85, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you? My name is \"\xC2\xA9Hello\" and my age is 62039. What's yours?";

    ASSERT_MEM_EQ(
        expected,
        octaspire_string_get_c_string(str),
        octaspire_string_get_length_in_octets(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_format_with_string_and_size_t_on_otherwise_empty_format_string_test(void)
{
    size_t const value = 62039;
    char const * const name  = "Hello";
    char const * const input = "%s%zu";
    octaspire_string_t *str =
        octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, input, name, value);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(10, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(10, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "Hello62039";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_format_with_empty_format_string_test(void)
{
    char const * const input = "";
    octaspire_string_t *str =
        octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, input);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_copy_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_t *cpy =
        octaspire_string_new_copy(str, octaspireContainerUtf8StringTestAllocator);

    ASSERT_EQ(
        octaspire_string_get_length_in_octets(str),
        octaspire_string_get_length_in_octets(cpy));

    ASSERT_MEM_EQ(
        octaspire_vector_get_element_at_const(str->octets, 0),
        octaspire_vector_get_element_at_const(cpy->octets, 0),
        octaspire_string_get_length_in_octets(str));

    ASSERT_EQ(
        octaspire_vector_get_length_in_octets(str->ucsCharacters),
        octaspire_vector_get_length_in_octets(cpy->ucsCharacters));

    ASSERT_MEM_EQ(
        octaspire_vector_get_element_at_const(str->ucsCharacters, 0),
        octaspire_vector_get_element_at_const(cpy->ucsCharacters, 0),
        octaspire_vector_get_length_in_octets(str->ucsCharacters));

    ASSERT_EQ(str->errorStatus,  cpy->errorStatus);
    ASSERT_EQ(str->errorAtOctet, cpy->errorAtOctet);

    ASSERT_EQ(cpy->allocator,     octaspireContainerUtf8StringTestAllocator);

    octaspire_string_release(str);
    str = 0;

    octaspire_string_release(cpy);
    cpy = 0;

    PASS();
}

TEST octaspire_string_new_copy_failure_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    ASSERT_FALSE(octaspire_string_new_copy(str, octaspireContainerUtf8StringTestAllocator));

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_length_in_ucs_characters_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    //ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_length_in_ucs_characters_called_with_empty_string_test(void)
{
    char const * const input = "";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_length_in_octets_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_length_in_octets_called_with_empty_string_test(void)
{
    char const * const input = "";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_string_get_length_in_octets(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_ucs_character_at_index_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

#define EXPECTED_LENGTH 30

    ASSERT_EQ(EXPECTED_LENGTH, octaspire_string_get_length_in_ucs_characters(str));

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
        ASSERT_EQ(
            expected[i],
            octaspire_string_get_ucs_character_at_index(
                str,
                (ptrdiff_t)i));
    }

    for (size_t i = 0; i < EXPECTED_LENGTH; ++i)
    {
        ptrdiff_t const index = -((ptrdiff_t)(i + 1));
        ASSERT_EQ(
            expected[EXPECTED_LENGTH - 1 - i],
            octaspire_string_get_ucs_character_at_index(str, index));
    }

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_c_string_test(void)
{
    char const * const input    = "Hello World! ©";
    char const * const expected = "Hello World! \xc2\xa9";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(15, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(14, octaspire_string_get_length_in_ucs_characters(str));

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_c_string_called_with_empty_string_test(void)
{
    char const * const input    = "";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));

    ASSERT_EQ('\0', *octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_is_error_false_case_test(void)
{
    char const * const input    = "Hello World";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_is_error_true_case_test(void)
{
    char const * const input    = "Hello World\xC0\xB3";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(octaspire_string_is_error(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_error_position_in_octets_called_when_has_error_test(void)
{
    char const * const input    = "Hello World\xC0\xB3";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_EQ(11, octaspire_string_get_error_position_in_octets(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_error_position_in_octets_called_when_has_no_error_test(void)
{
    char const * const input    = "Hello World";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_reset_error_status_called_when_there_is_error_test(void)
{
    char const * const input    = "Hello World\xC0\xB3";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(octaspire_string_is_error(str));
    ASSERT_EQ(11, octaspire_string_get_error_position_in_octets(str));

    octaspire_string_reset_error_status(str);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_reset_error_status_called_when_there_is_no_error_test(void)
{
    char const * const input    = "Hello World";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    octaspire_string_reset_error_status(str);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_concatenate_c_string_called_with_null_and_empty_string_arguments_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_string_concatenate_c_string(str, 0);
    octaspire_string_concatenate_c_string(str, "");

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

// TODO XXX Add test cases for allocation failures in concatenate_c_string...

TEST octaspire_string_concatenate_c_string_test(void)
{
    char const * const input  = "©Hello World!";
    char const * const input2 = " © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_string_concatenate_c_string(str, input2);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

#ifndef _MSC_VER
TEST octaspire_string_concatenate_c_string_with_decode_error_test(void)
{
    char const * const input  = "©Hello World!";
    char const * const input2 = " © ≠𐀀How are you?\xC0\xB3";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_string_concatenate_c_string(str, input2);

    ASSERT(octaspire_string_is_error(str));
    ASSERT_EQ(23, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}
#endif

TEST octaspire_string_concatenate_c_string_allocation_failure_one_test(void)
{
#ifdef _MSC_VER
    char const * const input  = u8"©Hello World!";
    char const * const input2 = u8" © ≠𐀀How are you?";
#else
    char const * const input  = "©Hello World!";
    char const * const input2 = " © ≠𐀀How are you?";
#endif

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 1, 0);

    ASSERT_FALSE(octaspire_string_concatenate_c_string(str, input2));

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_concatenate_c_string_allocation_failure_two_test(void)
{
    char const * const input  = "a";
    char const * const input2 = "bcd";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerUtf8StringTestAllocator,
        2, 0x00000002);

    ASSERT_FALSE(octaspire_string_concatenate_c_string(str, input2));

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_c_strings_end_always_in_null_byte_test(void)
{
    octaspire_string_t *str = octaspire_string_new("", octaspireContainerUtf8StringTestAllocator);
    ASSERT(octaspire_vector_is_empty(str->octets));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    str = octaspire_string_new("a", octaspireContainerUtf8StringTestAllocator);
    ASSERT(octaspire_vector_is_empty(str->octets));
    ASSERT_STR_EQ("a", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;


    str = octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, "");
    ASSERT(octaspire_vector_is_empty(str->octets));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;


    size_t const size = 112;
    str = octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, "%zu", size);
    ASSERT(octaspire_vector_is_empty(str->octets));
    ASSERT_STR_EQ("112", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_format_numbers_into_vector_test(void)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(octaspire_string_t*),
        true,
        (octaspire_vector_element_callback_t)octaspire_string_release,
        octaspireContainerUtf8StringTestAllocator);

    size_t const numElements = 256;

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerUtf8StringTestAllocator,
            "%zu",
            i);

        octaspire_vector_push_back_element(vec, &str);

    }

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t const * const str =
            octaspire_vector_get_element_at_const(vec, (ptrdiff_t)i);

        ASSERT_EQ(i, (size_t)atoi(octaspire_string_get_c_string(str)));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_string_new_format_number_test(void)
{
    size_t const i = 2000;
    octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerUtf8StringTestAllocator,
            "%zu",
            i);

    ASSERT_EQ(i, (size_t)atoi(octaspire_string_get_c_string(str)));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_char_a_from_string_a123a56a89a_using_negative_indice_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "a123a56a89a",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *character =
        octaspire_string_new("a123",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && character);

    // Test failure first
    octaspire_vector_t *indices = octaspire_string_find_char(
        str,
        character,
        -5);

    ASSERT_FALSE(indices);

    // Test success
    indices = octaspire_string_find_char(
        str,
        character,
        -4);

    ASSERT(indices);

    ASSERT_EQ(4, octaspire_vector_get_length(indices));

    ASSERT_EQ(0,  *(size_t*)octaspire_vector_get_element_at(indices, 0));
    ASSERT_EQ(4,  *(size_t*)octaspire_vector_get_element_at(indices, 1));
    ASSERT_EQ(7,  *(size_t*)octaspire_vector_get_element_at(indices, 2));
    ASSERT_EQ(10, *(size_t*)octaspire_vector_get_element_at(indices, 3));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(character);
    character = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_char_a_from_string_a123a56a89a_using_index_zero_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "a123a56a89a",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *character =
        octaspire_string_new("a123",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && character);

    octaspire_vector_t *indices = octaspire_string_find_char(
        str,
        character,
        0);

    ASSERT(indices);

    ASSERT_EQ(4, octaspire_vector_get_length(indices));

    ASSERT_EQ(0,  *(size_t*)octaspire_vector_get_element_at(indices, 0));
    ASSERT_EQ(4,  *(size_t*)octaspire_vector_get_element_at(indices, 1));
    ASSERT_EQ(7,  *(size_t*)octaspire_vector_get_element_at(indices, 2));
    ASSERT_EQ(10, *(size_t*)octaspire_vector_get_element_at(indices, 3));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(character);
    character = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_char_q_from_string_a123a56q89q_using_index_one_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "a123a56q89q",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *character =
        octaspire_string_new("aq123",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && character);

    octaspire_vector_t *indices = octaspire_string_find_char(
        str,
        character,
        1);

    ASSERT(indices);

    ASSERT_EQ(2, octaspire_vector_get_length(indices));

    ASSERT_EQ(7,  *(size_t*)octaspire_vector_get_element_at(indices, 0));
    ASSERT_EQ(10, *(size_t*)octaspire_vector_get_element_at(indices, 1));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(character);
    character = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_char_c_from_string_a123c56q89q_using_index_two_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "a123c56q89q",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *character =
        octaspire_string_new("aqc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && character);

    octaspire_vector_t *indices = octaspire_string_find_char(
        str,
        character,
        2);

    ASSERT(indices);

    ASSERT_EQ(1, octaspire_vector_get_length(indices));

    ASSERT_EQ(4, *(size_t*)octaspire_vector_get_element_at(indices, 0));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(character);
    character = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_char_c_from_string_a123y56q89q_using_index_two_failure_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "a123y56q89q",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *character =
        octaspire_string_new("aqc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && character);

    octaspire_vector_t *indices = octaspire_string_find_char(
        str,
        character,
        2);

    ASSERT(indices);

    ASSERT_EQ(0, octaspire_vector_get_length(indices));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(character);
    character = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_string_Xcat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_minus_3_and_length_of_3_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "cat dog cat zebra car kitten cat",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *lookFor =
        octaspire_string_new("Xcat",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_vector_t *indices = octaspire_string_find_string(
        str,
        lookFor,
        -3,
        3);

    ASSERT(indices);

    ASSERT_EQ(3, octaspire_vector_get_length(indices));

    ASSERT_EQ(0,   *(size_t*)octaspire_vector_get_element_at(indices, 0));
    ASSERT_EQ(8,   *(size_t*)octaspire_vector_get_element_at(indices, 1));
    ASSERT_EQ(29,  *(size_t*)octaspire_vector_get_element_at(indices, 2));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(lookFor);
    lookFor = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_string_cat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_zero_and_length_of_3_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "cat dog cat zebra car kitten cat",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *lookFor =
        octaspire_string_new("cat",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_vector_t *indices = octaspire_string_find_string(
        str,
        lookFor,
        0,
        3);

    ASSERT(indices);

    ASSERT_EQ(3, octaspire_vector_get_length(indices));

    ASSERT_EQ(0,   *(size_t*)octaspire_vector_get_element_at(indices, 0));
    ASSERT_EQ(8,   *(size_t*)octaspire_vector_get_element_at(indices, 1));
    ASSERT_EQ(29,  *(size_t*)octaspire_vector_get_element_at(indices, 2));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(lookFor);
    lookFor = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_string_cat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_one_and_length_of_3_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "cat dog cat zebra car kitten cat",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *lookFor =
        octaspire_string_new(">cat<",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_vector_t *indices = octaspire_string_find_string(
        str,
        lookFor,
        1,
        3);

    ASSERT(indices);

    ASSERT_EQ(3, octaspire_vector_get_length(indices));

    ASSERT_EQ(0,   *(size_t*)octaspire_vector_get_element_at(indices, 0));
    ASSERT_EQ(8,   *(size_t*)octaspire_vector_get_element_at(indices, 1));
    ASSERT_EQ(29,  *(size_t*)octaspire_vector_get_element_at(indices, 2));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(lookFor);
    lookFor = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_string_dog_from_string_dog_cat_zebra_using_index_zero_and_length_of_three_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "dog cat zebra",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *lookFor =
        octaspire_string_new("dog",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_vector_t *indices = octaspire_string_find_string(
        str,
        lookFor,
        0,
        3);

    ASSERT(indices);

    ASSERT_EQ(1, octaspire_vector_get_length(indices));

    ASSERT_EQ(0,   *(size_t*)octaspire_vector_get_element_at(indices, 0));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(lookFor);
    lookFor = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_string_dog_from_string_cat_zebra_dog_using_index_zero_and_length_of_three_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "cat zebra dog",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *lookFor =
        octaspire_string_new("dog",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_vector_t *indices = octaspire_string_find_string(
        str,
        lookFor,
        0,
        3);

    ASSERT(indices);

    ASSERT_EQ(1, octaspire_vector_get_length(indices));

    ASSERT_EQ(10,   *(size_t*)octaspire_vector_get_element_at(indices, 0));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(lookFor);
    lookFor = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_string_dog_from_string_cat_zebra_kitten_using_index_zero_and_length_of_three_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "cat zebra kitten",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *lookFor =
        octaspire_string_new("dog",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_vector_t *indices = octaspire_string_find_string(
        str,
        lookFor,
        0,
        3);

    ASSERT(indices);

    ASSERT_EQ(0, octaspire_vector_get_length(indices));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(lookFor);
    lookFor = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_string_kitten_from_string_cat_using_index_zero_and_length_of_six_failure_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "cat",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *lookFor =
        octaspire_string_new("kitten",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_vector_t *indices = octaspire_string_find_string(
        str,
        lookFor,
        0,
        6);

    ASSERT(indices);

    ASSERT_EQ(0, octaspire_vector_get_length(indices));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(lookFor);
    lookFor = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_private_check_substring_match_at_middle_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "123kitten456",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("kitten",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    for (size_t i = 0; i < octaspire_string_get_length_in_ucs_characters(str); ++i)
    {
        ASSERT_EQ(i == 3 ? true : false,
            octaspire_string_private_check_substring_match_at(
                str,
                i,
                substring));
    }

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_private_check_substring_match_at_the_beginning_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "kitten456",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("kitten",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    for (size_t i = 0; i < octaspire_string_get_length_in_ucs_characters(str); ++i)
    {
        ASSERT_EQ(i == 0 ? true : false,
            octaspire_string_private_check_substring_match_at(
                str,
                i,
                substring));
    }

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_private_check_substring_match_at_the_end_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "123kitten",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("kitten",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    for (size_t i = 0; i < octaspire_string_get_length_in_ucs_characters(str); ++i)
    {
        ASSERT_EQ(i == 3 ? true : false,
            octaspire_string_private_check_substring_match_at(
                str,
                i,
                substring));
    }

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_first_substring_abc_from_123abc456abc_starting_from_index_0_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "123abc456abc",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("abc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    ASSERT_EQ(
        3,
        octaspire_string_find_first_substring(
            str,
            0,
            substring));

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_first_substring_abc_from_123abc456abc_starting_from_index_minus_three_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "123abc456abc",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("abc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    ASSERT_EQ(
        9,
        octaspire_string_find_first_substring(
            str,
            -3,
            substring));

    ASSERT_EQ(
        9,
        octaspire_string_find_first_substring(
            str,
            -4,
            substring));

    ASSERT_EQ(
        3,
        octaspire_string_find_first_substring(
            str,
            -9,
            substring));

    ASSERT_EQ(
        3,
        octaspire_string_find_first_substring(
            str,
            -12,
            substring));

    // Not found
    ASSERT_EQ(
        -1,
        octaspire_string_find_first_substring(
            str,
            -2,
            substring));

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_first_substring_abc_from_123abc456abc_starting_from_index_4_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "123abc456abc",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("abc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    ASSERT_EQ(
        9,
        octaspire_string_find_first_substring(
            str,
            4,
            substring));

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_first_substring_abcd_from_123abc456abc_starting_from_index_0_failure_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "123abc456abc",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("abcd",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    ASSERT_EQ(
        -1,
        octaspire_string_find_first_substring(
            str,
            0,
            substring));

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_remove_character_at_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "0123456789",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(octaspire_string_remove_character_at(str, 1));
    ASSERT_STR_EQ("023456789", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, 0));
    ASSERT_STR_EQ("23456789", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, 7));
    ASSERT_STR_EQ("2345678", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, -1));
    ASSERT_STR_EQ("234567", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, -1));
    ASSERT_STR_EQ("23456", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, -5));
    ASSERT_STR_EQ("3456", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, -4));
    ASSERT_STR_EQ("456", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, -2));
    ASSERT_STR_EQ("46", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_remove_character_at_called_on_string_with_two_os_with_diaeresis_test(void)
{
    char const * const expected =
        "öö";

    char const * const expected2 =
        "ö";

    octaspire_string_t *str = octaspire_string_new(
        expected,
        octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);
    ASSERT_EQ(2, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ(expected, octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, 1));
    ASSERT_EQ(1, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ(expected2, octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, 0));
    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_remove_characters_at_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
        "0123456789",
        octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT_EQ(3, octaspire_string_remove_characters_at(str, 7, 3));
    ASSERT_STR_EQ("0123456", octaspire_string_get_c_string(str));

    ASSERT_EQ(3, octaspire_string_remove_characters_at(str, 2, 3));
    ASSERT_STR_EQ("0156", octaspire_string_get_c_string(str));

    ASSERT_EQ(3, octaspire_string_remove_characters_at(str, 0, 3));
    ASSERT_STR_EQ("6", octaspire_string_get_c_string(str));

    ASSERT_EQ(1, octaspire_string_remove_characters_at(str, 0, 1));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    // Using negative indices
    str = octaspire_string_new(
        "0123456789",
        octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    // Failures
    ASSERT_EQ(0, octaspire_string_remove_characters_at(str, -11, 3));
    ASSERT_STR_EQ("0123456789", octaspire_string_get_c_string(str));

    ASSERT_EQ(0, octaspire_string_remove_characters_at(str, -12, 3));
    ASSERT_STR_EQ("0123456789", octaspire_string_get_c_string(str));

    // Success
    ASSERT_EQ(3, octaspire_string_remove_characters_at(str, -3, 3));
    ASSERT_STR_EQ("0123456", octaspire_string_get_c_string(str));

    ASSERT_EQ(3, octaspire_string_remove_characters_at(str, -5, 3));
    ASSERT_STR_EQ("0156", octaspire_string_get_c_string(str));

    ASSERT_EQ(3, octaspire_string_remove_characters_at(str, -4, 3));
    ASSERT_STR_EQ("6", octaspire_string_get_c_string(str));

    ASSERT_EQ(1, octaspire_string_remove_characters_at(str, -1, 1));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_remove_all_substrings_kitten_from_string_kitten_cat_kitten_dog_kitten_zebra_kitten_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "kitten cat kitten dog kitten zebra kitten",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("kitten",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    ASSERT_EQ(4, octaspire_string_remove_all_substrings(str, substring));

    ASSERT_STR_EQ(
        " cat  dog  zebra ",
        octaspire_string_get_c_string(str));

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_insert_string_to_bc_into_index_1_of_ade_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_insert_string_to(strTarget, strAddition, 1));

    ASSERT_EQ(5, octaspire_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "abcde",
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_insert_string_to_bc_into_index_minus_1_of_ade_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_insert_string_to(strTarget, strAddition, -1));

    ASSERT_EQ(5, octaspire_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "adbce",
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_insert_string_to_bc_into_index_minus_3_of_ade_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_insert_string_to(strTarget, strAddition, -3));

    ASSERT_EQ(5, octaspire_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "bcade",
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_insert_string_to_bc_into_index_minus_4_of_ade_failure_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT_FALSE(octaspire_string_insert_string_to(strTarget, strAddition, -4));

    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "ade",
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_insert_string_to_bc_into_index_3_of_ade_failure_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT_FALSE(octaspire_string_insert_string_to(strTarget, strAddition, 3));

    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "ade",
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_insert_string_to_bc_into_index_0_of_ade_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_insert_string_to(strTarget, strAddition, 0));

    ASSERT_EQ(5, octaspire_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "bcade",
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_insert_string_to_bc_into_index_2_of_ade_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_insert_string_to(strTarget, strAddition, 2));

    ASSERT_EQ(5, octaspire_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "adbce",
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_overwrite_with_string_at_first_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "",
            octaspireContainerUtf8StringTestAllocator);

    char const * const expected =
        "abö";

    octaspire_string_t *strAddition =
        octaspire_string_new(expected,octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_overwrite_with_string_at(strTarget, strAddition, 0));
    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(strTarget));
    ASSERT_EQ(4, octaspire_string_get_length_in_octets(strTarget));
    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    strAddition = octaspire_string_new("q",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_overwrite_with_string_at(strTarget, strAddition, 1));
    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(strTarget));
    ASSERT_EQ(4, octaspire_string_get_length_in_octets(strTarget));

    char const * const expected2 =
        "aqö";

    ASSERT_STR_EQ(
        expected2,
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_overwrite_with_string_at_second_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "abc",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new(
            "ö",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_overwrite_with_string_at(strTarget, strAddition, 1));
    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(strTarget));
    ASSERT_EQ(4, octaspire_string_get_length_in_octets(strTarget));

    char const * const expected = "aöc";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_overwrite_with_string_at_called_with_negative_index_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "abc",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new(
            "ö",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_overwrite_with_string_at(
            strTarget,
            strAddition,
            -2));

    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(strTarget));
    ASSERT_EQ(4, octaspire_string_get_length_in_octets(strTarget));

    char const * const expected = "aöc";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_pop_front_ucs_character_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
        "abc",
        octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);
    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("abc", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_pop_front_ucs_character(str));
    ASSERT_EQ(2, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("bc", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_pop_front_ucs_character(str));
    ASSERT_EQ(1, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("c", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_pop_front_ucs_character(str));
    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    for (size_t i = 0; i < 10; ++i)
    {
        ASSERT_FALSE(octaspire_string_pop_front_ucs_character(str));
        ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));
        ASSERT_STR_EQ("", octaspire_string_get_c_string(str));
    }

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_pop_back_ucs_character_test(void)
{
    octaspire_string_t *str = octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);
    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("abc", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_pop_back_ucs_character(str));
    ASSERT_EQ(2, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("ab", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_pop_back_ucs_character(str));
    ASSERT_EQ(1, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("a", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_pop_back_ucs_character(str));
    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    for (size_t i = 0; i < 10; ++i)
    {
        ASSERT_FALSE(octaspire_string_pop_back_ucs_character(str));
        ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));
        ASSERT_STR_EQ("", octaspire_string_get_c_string(str));
    }

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_compare_with_two_empty_strings_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT_EQ(0, octaspire_string_compare(str1, str2));

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_compare_with_abc_and_empty_string_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT(octaspire_string_compare(str1, str2) > 0);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_compare_with_empty_string_and_abc_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT(octaspire_string_compare(str1, str2) < 0);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_compare_with_string_abc_and_abc_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT_EQ(0, octaspire_string_compare(str1, str2));

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_compare_with_string_abd_and_abc_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("abd", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT(octaspire_string_compare(str1, str2) > 0);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_compare_with_string_abca_and_abc_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("abca", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT(octaspire_string_compare(str1, str2) > 0);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_compare_with_string_abb_and_abc_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("abb", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT(octaspire_string_compare(str1, str2) < 0);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_compare_with_string_abc_and_abca_test(void)
{
    octaspire_string_t *str =
        octaspire_string_new(
            "",
            octaspireContainerUtf8StringTestAllocator);

    for (ptrdiff_t i = -64; i < 64; ++i)
    {
        ASSERT_FALSE(octaspire_string_is_index_valid(str, i));
    }

    octaspire_string_concatenate_c_string(str, "a");

    for (ptrdiff_t i = -64; i < 64; ++i)
    {
        ASSERT_EQ(
            i== -1 || i == 0,
            octaspire_string_is_index_valid(str, i));
    }

    octaspire_string_concatenate_c_string(str, "b");

    for (ptrdiff_t i = -64; i < 64; ++i)
    {
        ASSERT_EQ(
            i == -1 || i == -2 || i == 0 || i == 1,
            octaspire_string_is_index_valid(str, i));
    }

    ASSERT(str);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_abc_and_empty_string_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "abc",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(3, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_two_empty_strings_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(0, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_empty_string_and_abc_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "abc",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(3, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_abcdefghijklmnopqrstuvwxyz_and_abc_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "abcdefghijklmnopqrstuvwxyz",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "abc",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(23, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_a_and_b_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "a",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "b",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(1, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_kitten_and_sitting_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "kitten",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "sitting",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(3, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_flaw_and_lawn_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "flaw",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "lawn",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(2, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_jfpaasdasd2d_and_askdfsferrr4_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "jfpaasdasd2d",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "askdfsferrr4",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(11, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_rosettacode_and_raisethysword_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "rosettacode",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "raisethysword",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(8, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_two_longer_strings_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "CTAGGCTCGGACCAATCACCTAGGCCTCGGACCAACACCAACTACTCAAGAAGGGGTG",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "GACTTACTGGGACAAGTCTTGGACACATGGCAAACCAGTCCCGAACCAACAGCACATG",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(32, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_starts_with_c_string_test(void)
{
    octaspire_string_t *str =
        octaspire_string_new(
            "abcdefghij",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);
    ASSERT(octaspire_string_starts_with_c_string(str, "a"));
    ASSERT(octaspire_string_starts_with_c_string(str, "ab"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abc"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abcd"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abcde"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abcdef"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abcdefg"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abcdefgh"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abcdefghi"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abcdefghij"));

    ASSERT_FALSE(octaspire_string_starts_with_c_string(str, "abcdefghijk"));
    ASSERT_FALSE(octaspire_string_starts_with_c_string(str, "abcdefghix"));
    ASSERT_FALSE(octaspire_string_starts_with_c_string(str, "abcdefghxj"));
    ASSERT_FALSE(octaspire_string_starts_with_c_string(str, "abcdefgxij"));
    ASSERT_FALSE(octaspire_string_starts_with_c_string(str, "b"));

    ASSERT(octaspire_string_starts_with_c_string(str, ""));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_ends_with_c_string_test(void)
{
    octaspire_string_t *str =
        octaspire_string_new(
            "abcdefghij",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);
    ASSERT(octaspire_string_ends_with_c_string(str, "j"));
    ASSERT(octaspire_string_ends_with_c_string(str, "ij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "hij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "ghij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "fghij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "efghij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "defghij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "cdefghij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "bcdefghij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "abcdefghij"));

    ASSERT_FALSE(octaspire_string_ends_with_c_string(str, "abcdefghijk"));
    ASSERT_FALSE(octaspire_string_ends_with_c_string(str, "abcdefghix"));
    ASSERT_FALSE(octaspire_string_ends_with_c_string(str, "abcdefghxj"));
    ASSERT_FALSE(octaspire_string_ends_with_c_string(str, "abcdefgxij"));
    ASSERT_FALSE(octaspire_string_ends_with_c_string(str, "i"));

    ASSERT(octaspire_string_ends_with_c_string(str, ""));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_is_index_valid_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("abca", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT(octaspire_string_compare(str1, str2) < 0);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_set_from_c_string_test(void)
{
    octaspire_string_t *str1 = octaspire_string_new(
        "",
        octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 = octaspire_string_new(
        "ab",
        octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str3 = octaspire_string_new(
        "abc",
        octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT(str3);

    char const * const expected = "xy";

    ASSERT(octaspire_string_set_from_c_string(str1, expected));
    ASSERT(octaspire_string_set_from_c_string(str2, expected));
    ASSERT(octaspire_string_set_from_c_string(str3, expected));

    ASSERT(octaspire_string_compare_to_c_string(str1, expected) == 0);
    ASSERT(octaspire_string_compare_to_c_string(str2, expected) == 0);
    ASSERT(octaspire_string_compare_to_c_string(str3, expected) == 0);

    ASSERT_STR_EQ(expected, octaspire_string_get_c_string(str1));
    ASSERT_STR_EQ(expected, octaspire_string_get_c_string(str2));
    ASSERT_STR_EQ(expected, octaspire_string_get_c_string(str3));

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    octaspire_string_release(str3);
    str3 = 0;

    PASS();
}

TEST octaspire_string_set_from_c_string_allocation_failure_on_first_allocation_test(void)
{
    char const * const expected = "abc";

    octaspire_string_t *str = octaspire_string_new(
        expected,
        octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerUtf8StringTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerUtf8StringTestAllocator));

    ASSERT_FALSE(octaspire_string_set_from_c_string(str, "xy"));

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

GREATEST_SUITE(octaspire_string_suite)
{
    octaspireContainerUtf8StringTestAllocator = octaspire_allocator_new(0);

    assert(octaspireContainerUtf8StringTestAllocator);

    RUN_TEST(octaspire_string_new_called_with_null_argument_test);
    RUN_TEST(octaspire_string_new_with_simple_ascii_string_test);
    RUN_TEST(octaspire_string_new_with_some_multioctet_ucs_characters_test);
    RUN_TEST(octaspire_string_new_with_simple_ascii_string_with_error_test);
    RUN_TEST(octaspire_string_new_from_buffer_with_some_multioctet_ucs_characters_test);
    RUN_TEST(octaspire_string_new_from_buffer_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_string_new_from_buffer_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_string_new_from_buffer_allocation_failure_on_third_allocation_test);



    RUN_TEST(octaspire_string_new_from_buffer_allocation_failure_on_sixth_2_allocation_test);
    RUN_TEST(octaspire_string_new_format_with_string_test);
    RUN_TEST(octaspire_string_new_format_with_size_t_test);
    RUN_TEST(octaspire_string_new_format_with_doubles_test);
    RUN_TEST(octaspire_string_new_format_with_string_and_size_t_test);
    RUN_TEST(octaspire_string_new_format_with_string_and_size_t_on_otherwise_empty_format_string_test);
    RUN_TEST(octaspire_string_new_format_with_empty_format_string_test);
    RUN_TEST(octaspire_string_new_copy_test);
    RUN_TEST(octaspire_string_new_copy_failure_test);
    RUN_TEST(octaspire_string_get_length_in_ucs_characters_test);
    RUN_TEST(octaspire_string_get_length_in_ucs_characters_called_with_empty_string_test);
    RUN_TEST(octaspire_string_get_length_in_octets_test);
    RUN_TEST(octaspire_string_get_length_in_octets_called_with_empty_string_test);
    RUN_TEST(octaspire_string_get_ucs_character_at_index_test);
    RUN_TEST(octaspire_string_get_c_string_test);
    RUN_TEST(octaspire_string_get_c_string_called_with_empty_string_test);
    RUN_TEST(octaspire_string_is_error_false_case_test);
    RUN_TEST(octaspire_string_is_error_true_case_test);
    RUN_TEST(octaspire_string_get_error_position_in_octets_called_when_has_error_test);
    RUN_TEST(octaspire_string_get_error_position_in_octets_called_when_has_no_error_test);
    RUN_TEST(octaspire_string_reset_error_status_called_when_there_is_error_test);
    RUN_TEST(octaspire_string_reset_error_status_called_when_there_is_no_error_test);
    RUN_TEST(octaspire_string_concatenate_c_string_called_with_null_and_empty_string_arguments_test);
    RUN_TEST(octaspire_string_concatenate_c_string_test);
#ifndef _MSC_VER
    RUN_TEST(octaspire_string_concatenate_c_string_with_decode_error_test);
#endif
    RUN_TEST(octaspire_string_concatenate_c_string_allocation_failure_one_test);
    RUN_TEST(octaspire_string_concatenate_c_string_allocation_failure_two_test);
    RUN_TEST(octaspire_string_c_strings_end_always_in_null_byte_test);
    RUN_TEST(octaspire_string_new_format_numbers_into_vector_test);
    RUN_TEST(octaspire_string_new_format_number_test);
    RUN_TEST(octaspire_string_find_char_a_from_string_a123a56a89a_using_negative_indice_test);
    RUN_TEST(octaspire_string_find_char_a_from_string_a123a56a89a_using_index_zero_test);
    RUN_TEST(octaspire_string_find_char_q_from_string_a123a56q89q_using_index_one_test);
    RUN_TEST(octaspire_string_find_char_c_from_string_a123c56q89q_using_index_two_test);
    RUN_TEST(octaspire_string_find_char_c_from_string_a123y56q89q_using_index_two_failure_test);
    RUN_TEST(octaspire_string_find_string_Xcat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_minus_3_and_length_of_3_test);
    RUN_TEST(octaspire_string_find_string_cat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_zero_and_length_of_3_test);
    RUN_TEST(octaspire_string_find_string_cat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_one_and_length_of_3_test);
    RUN_TEST(octaspire_string_find_string_dog_from_string_dog_cat_zebra_using_index_zero_and_length_of_three_test);
    RUN_TEST(octaspire_string_find_string_dog_from_string_cat_zebra_dog_using_index_zero_and_length_of_three_test);
    RUN_TEST(octaspire_string_find_string_dog_from_string_cat_zebra_kitten_using_index_zero_and_length_of_three_test);
    RUN_TEST(octaspire_string_find_string_kitten_from_string_cat_using_index_zero_and_length_of_six_failure_test);
    RUN_TEST(octaspire_string_private_check_substring_match_at_middle_test);
    RUN_TEST(octaspire_string_private_check_substring_match_at_the_beginning_test);
    RUN_TEST(octaspire_string_private_check_substring_match_at_the_end_test);
    RUN_TEST(octaspire_string_find_first_substring_abc_from_123abc456abc_starting_from_index_0_test);
    RUN_TEST(octaspire_string_find_first_substring_abc_from_123abc456abc_starting_from_index_minus_three_test);
    RUN_TEST(octaspire_string_find_first_substring_abc_from_123abc456abc_starting_from_index_4_test);
    RUN_TEST(octaspire_string_find_first_substring_abcd_from_123abc456abc_starting_from_index_0_failure_test);
    RUN_TEST(octaspire_string_remove_character_at_test);
    RUN_TEST(octaspire_string_remove_character_at_called_on_string_with_two_os_with_diaeresis_test);
    RUN_TEST(octaspire_string_remove_characters_at_test);
    RUN_TEST(octaspire_string_remove_all_substrings_kitten_from_string_kitten_cat_kitten_dog_kitten_zebra_kitten_test);
    RUN_TEST(octaspire_string_insert_string_to_bc_into_index_1_of_ade_test);
    RUN_TEST(octaspire_string_insert_string_to_bc_into_index_minus_1_of_ade_test);
    RUN_TEST(octaspire_string_insert_string_to_bc_into_index_minus_3_of_ade_test);
    RUN_TEST(octaspire_string_insert_string_to_bc_into_index_minus_4_of_ade_failure_test);
    RUN_TEST(octaspire_string_insert_string_to_bc_into_index_3_of_ade_failure_test);
    RUN_TEST(octaspire_string_insert_string_to_bc_into_index_0_of_ade_test);
    RUN_TEST(octaspire_string_insert_string_to_bc_into_index_2_of_ade_test);

    RUN_TEST(octaspire_string_overwrite_with_string_at_first_test);
    RUN_TEST(octaspire_string_overwrite_with_string_at_second_test);
    RUN_TEST(octaspire_string_overwrite_with_string_at_called_with_negative_index_test);

    RUN_TEST(octaspire_string_pop_front_ucs_character_test);
    RUN_TEST(octaspire_string_pop_back_ucs_character_test);

    RUN_TEST(octaspire_string_compare_with_two_empty_strings_test);
    RUN_TEST(octaspire_string_compare_with_abc_and_empty_string_test);
    RUN_TEST(octaspire_string_compare_with_empty_string_and_abc_test);
    RUN_TEST(octaspire_string_compare_with_string_abc_and_abc_test);
    RUN_TEST(octaspire_string_compare_with_string_abd_and_abc_test);
    RUN_TEST(octaspire_string_compare_with_string_abca_and_abc_test);
    RUN_TEST(octaspire_string_compare_with_string_abb_and_abc_test);
    RUN_TEST(octaspire_string_compare_with_string_abc_and_abca_test);

    RUN_TEST(octaspire_string_levenshtein_distance_called_with_abc_and_empty_string_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_two_empty_strings_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_empty_string_and_abc_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_abcdefghijklmnopqrstuvwxyz_and_abc_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_a_and_b_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_kitten_and_sitting_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_flaw_and_lawn_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_jfpaasdasd2d_and_askdfsferrr4_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_rosettacode_and_raisethysword_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_two_longer_strings_test);

    RUN_TEST(octaspire_string_starts_with_c_string_test);
    RUN_TEST(octaspire_string_ends_with_c_string_test);

    RUN_TEST(octaspire_string_is_index_valid_test);

    RUN_TEST(octaspire_string_set_from_c_string_test);
    RUN_TEST(octaspire_string_set_from_c_string_allocation_failure_on_first_allocation_test);

    octaspire_allocator_release(octaspireContainerUtf8StringTestAllocator);
    octaspireContainerUtf8StringTestAllocator = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/test/test_string.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/test/test_pair.c
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

static octaspire_allocator_t *octaspireContainerPairTestAllocator = 0;

TEST octaspire_pair_new_short_and_long_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
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
    octaspire_pair_set(p, &expectedFirst, &expectedSecond);

    ASSERT_EQ(expectedFirst,  *(short const *)p->first);
    ASSERT_EQ(expectedSecond, *(long const *) p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_new_long_and_short_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
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
    octaspire_pair_set(p, &expectedFirst, &expectedSecond);

    ASSERT_EQ(expectedFirst,  *(long const*) p->first);
    ASSERT_EQ(expectedSecond, *(short const*)p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_new_uint32_t_and_double_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
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
    octaspire_pair_set(p, &expectedFirst, &expectedSecond);

    ASSERT_EQ(expectedFirst,  *(uint32_t const*)p->first);
    ASSERT_IN_RANGE(expectedSecond, *(double const*)p->second, 0.000001);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_new_allocation_failure_on_first_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_new_allocation_failure_on_second_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        2,
        0x01);

    ASSERT_EQ(
        2,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_new_allocation_failure_on_third_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        3,
        0x03);

    ASSERT_EQ(
        3,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_new_shallow_copy_uint32_t_and_double_test(void)
{
    octaspire_pair_t *expected = octaspire_pair_new(
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
    octaspire_pair_set(expected, &expectedFirst, &expectedSecond);

    octaspire_pair_t *p = octaspire_pair_new_shallow_copy(
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

    octaspire_pair_release(p);
    p = 0;

    octaspire_pair_release(expected);
    expected = 0;

    PASS();
}

TEST octaspire_pair_new_shallow_copy_failure_on_first_allocation_test(void)
{
    octaspire_pair_t *expected = octaspire_pair_new(
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
    octaspire_pair_set(expected, &expectedFirst, &expectedSecond);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_pair_t *p = octaspire_pair_new_shallow_copy(
        expected,
        octaspireContainerPairTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_pair_release(p);
    p = 0;

    octaspire_pair_release(expected);
    expected = 0;

    PASS();
}

TEST octaspire_pair_new_shallow_copy_failure_on_second_allocation_test(void)
{
    octaspire_pair_t *expected = octaspire_pair_new(
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
    octaspire_pair_set(expected, &expectedFirst, &expectedSecond);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        2,
        0x1);

    ASSERT_EQ(
        2,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_pair_t *p = octaspire_pair_new_shallow_copy(
        expected,
        octaspireContainerPairTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_pair_release(p);
    p = 0;

    octaspire_pair_release(expected);
    expected = 0;

    PASS();
}

TEST octaspire_pair_new_shallow_copy_failure_on_third_allocation_test(void)
{
    octaspire_pair_t *expected = octaspire_pair_new(
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
    octaspire_pair_set(expected, &expectedFirst, &expectedSecond);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        3,
        0x3);

    ASSERT_EQ(
        3,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_pair_t *p = octaspire_pair_new_shallow_copy(
        expected,
        octaspireContainerPairTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_pair_release(p);
    p = 0;

    octaspire_pair_release(expected);
    expected = 0;

    PASS();
}

static size_t octaspire_pair_release_test_private_release_callback_for_first_callcount = 0;

static void octaspire_pair_release_test_private_release_callback_for_first(void *element)
{
    OCTASPIRE_HELPERS_UNUSED_PARAMETER(element);
    ++octaspire_pair_release_test_private_release_callback_for_first_callcount;
}

static size_t octaspire_pair_release_test_private_release_callback_for_second_callcount = 0;

static void octaspire_pair_release_test_private_release_callback_for_second(void *element)
{
    OCTASPIRE_HELPERS_UNUSED_PARAMETER(element);
    ++octaspire_pair_release_test_private_release_callback_for_second_callcount;
}

TEST octaspire_pair_release_test(void)
{
    octaspire_pair_release_test_private_release_callback_for_first_callcount  = 0;
    octaspire_pair_release_test_private_release_callback_for_second_callcount = 0;

    octaspire_string_t *second = octaspire_string_new(
        "second element of the pair in octaspire_pair_release_test",
        octaspireContainerPairTestAllocator);

    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(size_t),
        false,
        sizeof(octaspire_string_t*),
        true,
        octaspire_pair_release_test_private_release_callback_for_first,
        octaspire_pair_release_test_private_release_callback_for_second,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    size_t const first  = 11;
    octaspire_pair_set(p, &first, &second);

    ASSERT_EQ(first,  *(size_t const *)p->first);
    ASSERT_EQ(second, *(octaspire_string_t **)p->second);

    octaspire_pair_release(p);
    p = 0;

    octaspire_string_release(second);
    second = 0;

    ASSERT_EQ(1, octaspire_pair_release_test_private_release_callback_for_first_callcount);
    ASSERT_EQ(1, octaspire_pair_release_test_private_release_callback_for_second_callcount);

    PASS();
}

TEST octaspire_pair_get_first_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
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
    octaspire_pair_set(p, &expectedFirst, &second);

    ASSERT_EQ(expectedFirst, *(long const*)octaspire_pair_get_first(p));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_get_first_const_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
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
    octaspire_pair_set(p, &expectedFirst, &second);

    ASSERT_EQ(expectedFirst, *(long const*)octaspire_pair_get_first_const(p));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_get_second_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
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
    octaspire_pair_set(p, &first, &expectedSecond);

    ASSERT_EQ(expectedSecond, *(short const*)octaspire_pair_get_second(p));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_get_second_const_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
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
    octaspire_pair_set(p, &first, &expectedSecond);

    ASSERT_EQ(expectedSecond, *(short const*)octaspire_pair_get_second_const(p));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_get_size_of_first_element_in_octets_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    ASSERT_EQ(sizeof(long), octaspire_pair_get_size_of_first_element_in_octets(p));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_get_size_of_second_element_in_octets_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    ASSERT_EQ(sizeof(short), octaspire_pair_get_size_of_second_element_in_octets(p));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_set_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
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
    octaspire_pair_set(p, &expectedFirst, &expectedSecond);

    ASSERT_EQ(expectedFirst,  *(short const *)p->first);
    ASSERT_EQ(expectedSecond, *(long const *) p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_set_first_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
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
    octaspire_pair_set_first(p, &expectedFirst);

    ASSERT_EQ(expectedFirst,  *(short const *)p->first);
    ASSERT_EQ(expectedSecond, *(long const *) p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_set_second_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
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
    octaspire_pair_set_second(p, &expectedSecond);

    ASSERT_EQ(expectedFirst,  *(short const *)p->first);
    ASSERT_EQ(expectedSecond, *(long const *) p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_set_first_to_void_pointer_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
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
    ASSERT(octaspire_pair_set_first_to_void_pointer(p, expectedFirst));

    ASSERT_EQ(expectedFirst,  *(void **)p->first);
    ASSERT_EQ(expectedSecond, *(long const *)p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_set_first_to_void_pointer_failure_on_element_size_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(char),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    void *ptr = 0;
    ASSERT_FALSE(octaspire_pair_set_first_to_void_pointer(p, ptr));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_set_second_to_void_pointer_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
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
    ASSERT(octaspire_pair_set_second_to_void_pointer(p, expectedSecond));

    ASSERT_EQ(expectedFirst,  *(long const *)p->first);
    ASSERT_EQ(expectedSecond, *(void const **)p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_set_second_to_void_pointer_failure_on_element_size_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(long),
        false,
        sizeof(char),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    void *ptr = 0;
    ASSERT_FALSE(octaspire_pair_set_second_to_void_pointer(p, ptr));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_clear_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
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
    octaspire_pair_set(p, &expectedFirst, &expectedSecond);

    ASSERT_EQ(11, *(short const*)p->first);
    ASSERT_EQ(12, *(long const*)p->second);

    octaspire_pair_clear(p);

    ASSERT_EQ(0, *(short const*)p->first);
    ASSERT_EQ(0, *(long const*)p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

GREATEST_SUITE(octaspire_pair_suite)
{
    octaspireContainerPairTestAllocator = octaspire_allocator_new(0);
    assert(octaspireContainerPairTestAllocator);

    RUN_TEST(octaspire_pair_new_short_and_long_test);
    RUN_TEST(octaspire_pair_new_long_and_short_test);
    RUN_TEST(octaspire_pair_new_uint32_t_and_double_test);
    RUN_TEST(octaspire_pair_new_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_pair_new_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_pair_new_allocation_failure_on_third_allocation_test);
    RUN_TEST(octaspire_pair_new_shallow_copy_uint32_t_and_double_test);
    RUN_TEST(octaspire_pair_new_shallow_copy_failure_on_first_allocation_test);
    RUN_TEST(octaspire_pair_new_shallow_copy_failure_on_second_allocation_test);
    RUN_TEST(octaspire_pair_new_shallow_copy_failure_on_third_allocation_test);
    RUN_TEST(octaspire_pair_release_test);
    RUN_TEST(octaspire_pair_get_first_test);
    RUN_TEST(octaspire_pair_get_first_const_test);
    RUN_TEST(octaspire_pair_get_second_test);
    RUN_TEST(octaspire_pair_get_second_const_test);
    RUN_TEST(octaspire_pair_get_size_of_first_element_in_octets_test);
    RUN_TEST(octaspire_pair_get_size_of_second_element_in_octets_test);
    RUN_TEST(octaspire_pair_set_test);
    RUN_TEST(octaspire_pair_set_first_test);
    RUN_TEST(octaspire_pair_set_second_test);
    RUN_TEST(octaspire_pair_set_first_to_void_pointer_test);
    RUN_TEST(octaspire_pair_set_first_to_void_pointer_failure_on_element_size_test);
    RUN_TEST(octaspire_pair_set_second_to_void_pointer_test);
    RUN_TEST(octaspire_pair_set_second_to_void_pointer_failure_on_element_size_test);
    RUN_TEST(octaspire_pair_clear_test);

    octaspire_allocator_release(octaspireContainerPairTestAllocator);
    octaspireContainerPairTestAllocator = 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/test/test_pair.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/test/test_map.c
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

static octaspire_allocator_t *octaspireContainerHashMapTestAllocator = 0;



TEST octaspire_map_element_new_allocation_failure_on_first_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    size_t const value = 0;
    octaspire_map_element_t *element = octaspire_map_element_new(
        0,
        sizeof(value),
        false,
        &value,
        sizeof(value),
        false,
        &value,
        octaspireContainerHashMapTestAllocator);

    ASSERT_FALSE(element);
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_map_element_release(element);
    element = 0;

    PASS();
}

TEST octaspire_map_element_new_allocation_failure_on_second_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 2, 0x01);
    ASSERT_EQ(2, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    size_t const value = 0;
    octaspire_map_element_t *element = octaspire_map_element_new(
        0,
        sizeof(value),
        false,
        &value,
        sizeof(value),
        false,
        &value,
        octaspireContainerHashMapTestAllocator);

    ASSERT_FALSE(element);
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_map_element_release(element);
    element = 0;

    PASS();
}

TEST octaspire_map_element_new_allocation_failure_on_third_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 3, 0x03);
    ASSERT_EQ(3, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    size_t const value = 0;
    octaspire_map_element_t *element = octaspire_map_element_new(
        0,
        sizeof(value),
        false,
        &value,
        sizeof(value),
        false,
        &value,
        octaspireContainerHashMapTestAllocator);

    ASSERT_FALSE(element);
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_map_element_release(element);
    element = 0;

    PASS();
}

static bool octaspire_map_new_test_key_compare_function_for_size_t_keys(
    void const * const key1,
    void const * const key2);

static uint32_t octaspire_map_new_test_key_hash_function_for_size_t_keys(
    void const * const key);

static bool octaspire_map_new_test_key_compare_function_for_size_t_keys(
    void const * const key1,
    void const * const key2)
{
    return *(size_t const * const)key1 == *(size_t const * const)key2;
}

static uint32_t octaspire_map_new_test_key_hash_function_for_size_t_keys(
    void const * const key)
{
    size_t const value = *(size_t const * const)key;
    return (uint32_t)value;
}

TEST octaspire_map_private_rehash_allocation_failure_on_first_allocation_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 1, 0x00);
    ASSERT_EQ(1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    ASSERT_FALSE(octaspire_map_private_rehash(hashMap));
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_new_keys_uint32_t_and_values_size_t_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        uint32_t hash = (uint32_t)i;

        octaspire_map_put(hashMap, hash, &i, &i);
    }

    ASSERT_EQ(numElements, octaspire_map_get_number_of_elements(hashMap));

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_map_element_t *element =
            octaspire_map_get(hashMap, (uint32_t)i, &i);

        ASSERT_EQ(i,   octaspire_map_element_get_hash(element));
        ASSERT_EQ(i,   *(size_t*)octaspire_map_element_get_key(element));
        ASSERT_EQ(i,   *(size_t*)octaspire_map_element_get_value(element));
    }

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_add_same_key_many_times_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    size_t const key = 1024;

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT(octaspire_map_put(
            hashMap,
            octaspire_helpers_calculate_hash_for_size_t_argument(key),
            &key,
            &i));

        octaspire_map_element_t * const element = octaspire_map_get(
            hashMap,
            octaspire_helpers_calculate_hash_for_size_t_argument(key),
            &key);

        ASSERT(element);

        ASSERT_EQ(key, *(size_t*)octaspire_map_element_get_key(element));

        octaspire_vector_t * const values =
            octaspire_map_element_get_values(element);

        ASSERT_EQ(i + 1,   octaspire_vector_get_length(values));

        for (size_t j = 0; j < octaspire_vector_get_length(values) ; ++j)
        {
            ASSERT_EQ(
                j,
                *(size_t*)octaspire_vector_get_element_at(
                    values,
                    (ptrdiff_t)j));
        }
    }

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_new_allocation_failure_on_first_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT_FALSE(hashMap);
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_new_allocation_failure_on_second_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 2, 0x01);
    ASSERT_EQ(2, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT_FALSE(hashMap);
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

static bool octaspire_map_new_test_key_compare_function_for_ostring_t_keys(
    void const * const key1,
    void const * const key2);

static uint32_t octaspire_map_new_test_key_hash_function_for_ostring_t_keys(
    void const * const key);

static bool octaspire_map_new_test_key_compare_function_for_ostring_t_keys(
    void const * const key1,
    void const * const key2)
{
    assert(key1);
    assert(key2);

    return octaspire_string_is_equal(
        (octaspire_string_t const * const)key1,
        (octaspire_string_t const * const)key2);
}

static uint32_t octaspire_map_new_test_key_hash_function_for_ostring_t_keys(
    void const * const key)
{
    assert(key);
    return octaspire_string_get_hash((octaspire_string_t const * const)key);
}

TEST octaspire_map_new_keys_ostring_t_and_values_ostring_t_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(octaspire_string_t *),
        true,
        sizeof(octaspire_string_t *),
        true,
        octaspire_map_new_test_key_compare_function_for_ostring_t_keys,
        octaspire_map_new_test_key_hash_function_for_ostring_t_keys,
        (octaspire_map_element_callback_t)octaspire_string_release,
        (octaspire_map_element_callback_t)octaspire_string_release,
        octaspireContainerHashMapTestAllocator);

    size_t const numElements = 32;

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t const hash = octaspire_string_get_hash(str);

        octaspire_string_t *cpyStr = octaspire_string_new_copy(str, octaspireContainerHashMapTestAllocator);
        ASSERT(octaspire_string_is_equal(str, cpyStr));
        octaspire_map_put(hashMap, hash, &cpyStr, &str);

        ASSERT_EQ(i+1, octaspire_map_get_number_of_elements(hashMap));
    }

    ASSERT_EQ(numElements, octaspire_map_get_number_of_elements(hashMap));

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t hash = octaspire_string_get_hash(str);

        octaspire_map_element_t *element =
            octaspire_map_get(hashMap, hash, &str);

        ASSERT(element);

        ASSERT_EQ(hash, octaspire_map_element_get_hash(element));

        ASSERT(octaspire_string_is_equal(str, (octaspire_string_t*)octaspire_map_element_get_key(element)));

        ASSERT(octaspire_string_is_equal(str, (octaspire_string_t*)octaspire_map_element_get_value(element)));

        octaspire_string_release(str);
        str = 0;
    }

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_new_with_octaspire_string_keys_test(void)
{
    octaspire_map_t *hashMap =
        octaspire_map_new_with_octaspire_string_keys(
            sizeof(octaspire_string_t *),
            true,
            (octaspire_map_element_callback_t)
                octaspire_string_release,
            octaspireContainerHashMapTestAllocator);

    size_t const numElements = 32;

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t const hash = octaspire_string_get_hash(str);

        octaspire_string_t *cpyStr = octaspire_string_new_copy(str, octaspireContainerHashMapTestAllocator);
        ASSERT(octaspire_string_is_equal(str, cpyStr));
        octaspire_map_put(hashMap, hash, &cpyStr, &str);

        ASSERT_EQ(i+1, octaspire_map_get_number_of_elements(hashMap));
    }

    ASSERT_EQ(numElements, octaspire_map_get_number_of_elements(hashMap));

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t hash = octaspire_string_get_hash(str);

        octaspire_map_element_t *element =
            octaspire_map_get(hashMap, hash, &str);

        ASSERT(element);

        ASSERT_EQ(hash, octaspire_map_element_get_hash(element));

        ASSERT(octaspire_string_is_equal(str, (octaspire_string_t*)octaspire_map_element_get_key(element)));

        ASSERT(octaspire_string_is_equal(str, (octaspire_string_t*)octaspire_map_element_get_value(element)));

        octaspire_string_release(str);
        str = 0;
    }

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_new_with_size_t_keys_test(void)
{
    octaspire_map_t *hashMap =
        octaspire_map_new_with_size_t_keys(
            sizeof(octaspire_string_t *),
            true,
            (octaspire_map_element_callback_t)
                octaspire_string_release,
            octaspireContainerHashMapTestAllocator);

    size_t const numElements = 32;

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t const hash = octaspire_map_helper_size_t_get_hash(i);

        ASSERT(octaspire_map_put(hashMap, hash, &i, &str));

        ASSERT_EQ(i+1, octaspire_map_get_number_of_elements(hashMap));
    }

    ASSERT_EQ(numElements, octaspire_map_get_number_of_elements(hashMap));

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t const hash = octaspire_map_helper_size_t_get_hash(i);

        octaspire_map_element_t *element =
            octaspire_map_get(hashMap, hash, &i);

        ASSERT(element);

        ASSERT_EQ(hash, octaspire_map_element_get_hash(element));

        ASSERT_EQ(i, *(size_t const * const)octaspire_map_element_get_key(element));

        ASSERT(octaspire_string_is_equal(str, (octaspire_string_t*)octaspire_map_element_get_value(element)));

        octaspire_string_release(str);
        str = 0;
    }

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_element_iterator_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    octaspire_map_element_iterator_t iterator =
        octaspire_map_element_iterator_init(hashMap);

    ASSERT_EQ(hashMap, iterator.hashMap);
    ASSERT_EQ(0,       iterator.element);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(octaspire_map_element_iterator_next(&iterator));

        ASSERT_EQ(hashMap, iterator.hashMap);
        ASSERT_EQ(0,       iterator.element);
    }

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        uint32_t hash = (uint32_t)i;

        octaspire_map_put(hashMap, hash, &i, &i);
    }

    ASSERT_EQ(numElements, octaspire_map_get_number_of_elements(hashMap));

    iterator =
        octaspire_map_element_iterator_init(hashMap);

    ASSERT_EQ(hashMap, iterator.hashMap);

    size_t counter = 0;
    while (iterator.element)
    {
        ASSERT_EQ(hashMap, iterator.hashMap);
        ASSERT_EQ(counter, octaspire_map_element_get_hash(iterator.element));
        ASSERT_EQ(counter, *(size_t*)octaspire_map_element_get_key(iterator.element));
        ASSERT_EQ(counter, *(size_t*)octaspire_map_element_get_value(iterator.element));

        ++counter;
        octaspire_map_element_iterator_next(&iterator);
    }

    ASSERT_EQ(numElements, counter);

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_element_const_iterator_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    octaspire_map_element_const_iterator_t iterator =
        octaspire_map_element_const_iterator_init(hashMap);

    ASSERT_EQ(hashMap, iterator.hashMap);
    ASSERT_EQ(0,       iterator.element);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(octaspire_map_element_const_iterator_next(&iterator));

        ASSERT_EQ(hashMap, iterator.hashMap);
        ASSERT_EQ(0,       iterator.element);
    }

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        uint32_t hash = (uint32_t)i;

        octaspire_map_put(hashMap, hash, &i, &i);
    }

    ASSERT_EQ(numElements, octaspire_map_get_number_of_elements(hashMap));

    iterator =
        octaspire_map_element_const_iterator_init(hashMap);

    ASSERT_EQ(hashMap, iterator.hashMap);

    size_t counter = 0;
    while (iterator.element)
    {
        ASSERT_EQ(hashMap, iterator.hashMap);
        ASSERT_EQ(counter, octaspire_map_element_get_hash(iterator.element));
        ASSERT_EQ(counter, *(size_t const*)octaspire_map_element_get_key_const(iterator.element));
        ASSERT_EQ(counter, *(size_t const*)octaspire_map_element_get_value_const(iterator.element));

        ++counter;
        octaspire_map_element_const_iterator_next(&iterator);
    }

    ASSERT_EQ(numElements, counter);

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_get_at_index_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    size_t const numElements = 3;

    for (size_t i = 0; i < numElements; ++i)
    {
        uint32_t hash = (uint32_t)i;
        octaspire_map_put(hashMap, hash, &i, &i);
    }

    ASSERT_EQ(numElements, octaspire_map_get_number_of_elements(hashMap));

    // Test failures
    octaspire_map_element_t *element =
        octaspire_map_get_at_index(hashMap, 3);

    ASSERT_FALSE(element);

    element =
        octaspire_map_get_at_index(hashMap, -4);

    ASSERT_FALSE(element);

    // Test success with positive and negative indices
    element =
        octaspire_map_get_at_index(hashMap, 1);

    ASSERT(element);

    ASSERT_EQ(
        1,
        *(size_t const * const)octaspire_map_element_get_value(element));

    element =
        octaspire_map_get_at_index(hashMap, -2);

    ASSERT(element);

    ASSERT_EQ(
        1,
        *(size_t const * const)octaspire_map_element_get_value(element));

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_is_empty_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    ASSERT(octaspire_map_is_empty(hashMap));

    size_t const numElements = 3;

    for (size_t i = 0; i < numElements; ++i)
    {
        uint32_t hash = (uint32_t)i;
        octaspire_map_put(hashMap, hash, &i, &i);
        ASSERT_FALSE(octaspire_map_is_empty(hashMap));
    }

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

GREATEST_SUITE(octaspire_map_suite)
{
    octaspireContainerHashMapTestAllocator = octaspire_allocator_new(0);

    assert(octaspireContainerHashMapTestAllocator);

    RUN_TEST(octaspire_map_element_new_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_map_element_new_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_map_element_new_allocation_failure_on_third_allocation_test);
    RUN_TEST(octaspire_map_private_rehash_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_map_new_keys_uint32_t_and_values_size_t_test);
    RUN_TEST(octaspire_map_add_same_key_many_times_test);
    RUN_TEST(octaspire_map_new_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_map_new_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_map_new_keys_ostring_t_and_values_ostring_t_test);
    RUN_TEST(octaspire_map_new_with_octaspire_string_keys_test);
    RUN_TEST(octaspire_map_new_with_size_t_keys_test);
    RUN_TEST(octaspire_map_element_iterator_test);
    RUN_TEST(octaspire_map_element_const_iterator_test);

    RUN_TEST(octaspire_map_get_at_index_test);
    RUN_TEST(octaspire_map_is_empty_test);

    octaspire_allocator_release(octaspireContainerHashMapTestAllocator);
    octaspireContainerHashMapTestAllocator = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/test/test_map.c
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        dev/test/test_semver.c
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

static octaspire_allocator_t *octaspireSemverTestAllocator = 0;

TEST octaspire_semver_pre_release_elem_type_accessors_called_on_lexical_type_test(void)
{
    char const * const expected = "qwerty";

    octaspire_semver_pre_release_elem_t * elem =
        octaspire_semver_pre_release_elem_new_from_c_string(
            expected,
            octaspireSemverTestAllocator);

    ASSERT(elem);

    ASSERT_EQ(
        OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL,
        octaspire_semver_pre_release_elem_get_type(elem));

    ASSERT_STR_EQ(
        expected,
        octaspire_semver_pre_release_elem_get_lexical_value_as_c_string(elem));

    ASSERT_FALSE(octaspire_semver_pre_release_elem_is_numerical_type(elem));
    ASSERT(octaspire_semver_pre_release_elem_is_lexical_type(elem));

    octaspire_semver_pre_release_elem_release(elem);
    elem = 0;

    PASS();
}

TEST octaspire_semver_pre_release_elem_type_accessors_called_on_numerical_type_test(void)
{
    size_t const expected = 123;

    octaspire_semver_pre_release_elem_t * elem =
        octaspire_semver_pre_release_elem_numerical_new(
            expected,
            octaspireSemverTestAllocator);

    ASSERT(elem);

    ASSERT_EQ(
        OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL,
        octaspire_semver_pre_release_elem_get_type(elem));

    ASSERT_EQ(
        expected,
        octaspire_semver_pre_release_elem_get_numerical_value(elem));

    ASSERT(octaspire_semver_pre_release_elem_is_numerical_type(elem));
    ASSERT_FALSE(octaspire_semver_pre_release_elem_is_lexical_type(elem));

    octaspire_semver_pre_release_elem_release(elem);
    elem = 0;

    PASS();
}

TEST octaspire_semver_pre_release_elem_new_copy_called_with_numerical_type_test(void)
{
    size_t const expected = 321;

    octaspire_semver_pre_release_elem_t * elem1 =
        octaspire_semver_pre_release_elem_numerical_new(
            expected,
            octaspireSemverTestAllocator);

    ASSERT(elem1);

    octaspire_semver_pre_release_elem_t * elem2 =
        octaspire_semver_pre_release_elem_new_copy(
            elem1,
            octaspireSemverTestAllocator);

    ASSERT(elem2);

    ASSERT_EQ(
        OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL,
        octaspire_semver_pre_release_elem_get_type(elem2));

    ASSERT_EQ(
        expected,
        octaspire_semver_pre_release_elem_get_numerical_value(elem2));

    octaspire_semver_pre_release_elem_release(elem1);
    elem1 = 0;

    octaspire_semver_pre_release_elem_release(elem2);
    elem2 = 0;

    PASS();
}

TEST octaspire_semver_pre_release_elem_new_copy_called_with_lexcal_type_test(void)
{
     char const * const expected = "ytrewq";

    octaspire_semver_pre_release_elem_t * elem1 =
        octaspire_semver_pre_release_elem_new_from_c_string(
            expected,
            octaspireSemverTestAllocator);

    ASSERT(elem1);

    octaspire_semver_pre_release_elem_t * elem2 =
        octaspire_semver_pre_release_elem_new_copy(
            elem1,
            octaspireSemverTestAllocator);

    ASSERT(elem2);

    ASSERT_EQ(
        OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL,
        octaspire_semver_pre_release_elem_get_type(elem2));

    ASSERT_STR_EQ(
        expected,
        octaspire_semver_pre_release_elem_get_lexical_value_as_c_string(elem2));

    octaspire_semver_pre_release_elem_release(elem1);
    elem1 = 0;

    octaspire_semver_pre_release_elem_release(elem2);
    elem2 = 0;

    PASS();
}

TEST octaspire_semver_pre_release_elem_make_numerical_and_lexical_test(void)
{
    octaspire_semver_pre_release_elem_t * elem =
        octaspire_semver_pre_release_elem_new_from_c_string(
            "qwerty",
            octaspireSemverTestAllocator);

    ASSERT(elem);

    size_t const expectedNum = 123;

    octaspire_semver_pre_release_elem_make_numerical(elem, expectedNum);

    ASSERT_EQ(
        OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL,
        octaspire_semver_pre_release_elem_get_type(elem));

    ASSERT_EQ(expectedNum, octaspire_semver_pre_release_elem_get_numerical_value(elem));

    char const * const expectedStr = "abc";

    ASSERT(octaspire_semver_pre_release_elem_make_lexical(elem, expectedStr));

    ASSERT_EQ(
        OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL,
        octaspire_semver_pre_release_elem_get_type(elem));

    ASSERT_STR_EQ(
        expectedStr,
        octaspire_semver_pre_release_elem_get_lexical_value_as_c_string(elem));

    octaspire_semver_pre_release_elem_release(elem);
    elem = 0;

    PASS();
}


TEST octaspire_semver_new_called_with_null_allocator_test(void)
{
    octaspire_vector_t * preRelease =
        octaspire_vector_new(
            sizeof(octaspire_string_t*),
            true,
            (octaspire_vector_element_callback_t)octaspire_string_release,
            octaspireSemverTestAllocator);

    ASSERT(preRelease);

    octaspire_vector_t * buildMetadata =
        octaspire_vector_new(
            sizeof(octaspire_string_t*),
            true,
            (octaspire_vector_element_callback_t)octaspire_string_release,
            octaspireSemverTestAllocator);

    ASSERT(buildMetadata);

    octaspire_semver_t * semver =
        octaspire_semver_new(
            0,
            0,
            0,
            preRelease,
            buildMetadata,
            0);

    ASSERT_EQ(semver, 0);

    octaspire_vector_release(preRelease);
    preRelease = 0;

    octaspire_vector_release(buildMetadata);
    buildMetadata = 0;

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}

TEST octaspire_semver_new_prerelease_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver);

    octaspire_string_t * str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-alpha.3"));
    octaspire_string_release(str);
    str = 0;

    ASSERT(octaspire_semver_add_buildmetadata(semver, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver, "5214f"));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-alpha.3+sha.5214f"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}

TEST octaspire_semver_new_copy_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);

    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    octaspire_semver_t * semver2 = octaspire_semver_new_copy(
        semver1,
        octaspireSemverTestAllocator);

    ASSERT(semver2);
    ASSERT(octaspire_semver_is_equal_to(semver1, semver2));

    octaspire_string_t * str1 = octaspire_semver_to_string(semver1);
    ASSERT(str1);
    ASSERT(octaspire_string_is_equal_to_c_string(str1, "0.1.2-alpha.3+sha.5214f"));

    octaspire_string_t * str2 = octaspire_semver_to_string(semver2);
    ASSERT(str2);
    ASSERT(octaspire_string_is_equal(str1, str2));

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;

    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_get_build_metadata_at_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver);

    ASSERT(octaspire_semver_add_buildmetadata(semver, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver, "5214f"));

    ASSERT_EQ(0,           octaspire_semver_get_build_metadata_at(semver, 3));
    ASSERT_EQ(0,           octaspire_semver_get_build_metadata_at(semver, 2));
    ASSERT_STR_EQ("5214f", octaspire_semver_get_build_metadata_at(semver, 1));
    ASSERT_STR_EQ("sha",   octaspire_semver_get_build_metadata_at(semver, 0));

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}

TEST octaspire_semver_get_prerelease_at_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver);

    ASSERT(octaspire_semver_add_buildmetadata(semver, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver, "5214f"));

    size_t       numerical = 0;
    char const * lexical   = 0;

    octaspire_semver_pre_release_elem_type_t elemType =
        octaspire_semver_get_prerelease_at(semver, 0, &numerical, &lexical);

    ASSERT_EQ(OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL, elemType);
    ASSERT(lexical);
    ASSERT_EQ(0, numerical);
    ASSERT_STR_EQ("alpha", lexical);

    numerical = 0;
    lexical   = 0;

    elemType =
        octaspire_semver_get_prerelease_at(semver, 1, &numerical, &lexical);

    ASSERT_EQ(OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL, elemType);
    ASSERT_EQ(0, lexical);
    ASSERT_EQ(3, numerical);

    numerical = 0;
    lexical   = 0;

    elemType =
        octaspire_semver_get_prerelease_at(semver, 2, &numerical, &lexical);

    ASSERT_EQ(OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_UNKNOWN, elemType);
    ASSERT_EQ(0, lexical);
    ASSERT_EQ(0, numerical);

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}

TEST octaspire_semver_get_length_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver);

    ASSERT(octaspire_semver_add_buildmetadata(semver, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver, "5214f"));

    ASSERT_EQ(7, octaspire_semver_get_length(semver));

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}

TEST octaspire_semver_get_major_minor_patch_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver);

    ASSERT(octaspire_semver_add_buildmetadata(semver, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver, "5214f"));

    ASSERT_EQ(0, octaspire_semver_get_major(semver));
    ASSERT_EQ(1, octaspire_semver_get_minor(semver));
    ASSERT_EQ(2, octaspire_semver_get_patch(semver));

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_3_metadata_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ(0, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ(0, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214g_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214g"));

    ASSERT_EQ(0, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ(0, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_2_alpha_4_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "4",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ(-1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ( 1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_4_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "4",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ( 1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ(-1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alphb_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alphb",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ( 1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ(-1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_2_alphb_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alphb",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ(-1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ( 1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_3_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            3,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ( 1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ(-1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_3_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            3,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ(-1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ( 1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_2_2_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            2,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ( 1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ(-1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_2_2_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            2,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ(-1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ( 1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_1_1_2_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ( 1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ(-1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_1_1_2_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            1,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ(-1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ( 1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_0_0_alpha_and_1_0_0_alpha_1_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "alpha",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "alpha",
            "1",
            "");

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_0_0_alpha_1_and_1_0_0_alpha_beta_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "alpha",
            "1",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "alpha",
            "beta",
            "");

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_0_0_alpha_beta_and_1_0_0_beta_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "alpha",
            "beta",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "beta",
            "");

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_0_0_beta_and_1_0_0_beta_2_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "beta",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "beta",
            "2",
            "");

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_0_0_beta_2_and_1_0_0_beta_11_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "beta",
            "2",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "beta",
            "11",
            "");

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_0_0_beta_11_and_1_0_0_rc_1_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "beta",
            "11",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_0_0_rc_1_and_1_0_0_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            1,
            0,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_3_0_1_rc_1_and_3_0_1_rc_1_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            3,
            0,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            3,
            0,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver2);

    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_9_0_and_1_10_0_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new(
            1,
            9,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            1,
            10,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_is_equal_to_c_string_called_with_1_9_0_and_same_and_five_different_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new(
            1,
            9,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver1);

    ASSERT(octaspire_semver_is_equal_to_c_string(semver1, "1.9.0"));
    ASSERT_FALSE(octaspire_semver_is_equal_to_c_string(semver1, "1.9.1"));
    ASSERT_FALSE(octaspire_semver_is_equal_to_c_string(semver1, "1.10.0"));
    ASSERT_FALSE(octaspire_semver_is_equal_to_c_string(semver1, "2.9.0"));
    ASSERT_FALSE(octaspire_semver_is_equal_to_c_string(semver1, "1.9.0-rc"));
    ASSERT_FALSE(octaspire_semver_is_equal_to_c_string(semver1, "1.9.0-rc.1"));

    octaspire_semver_release(semver1);
    semver1 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_0_0_rc_1_and_0_0_1_and_true_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            0,
            0,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.0.1-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_0_1_rc_1_and_0_1_0_and_true_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            0,
            1,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.0-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_1_0_0_and_true_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            1,
            0,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "2.0.0-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_and_0_0_0_rc_1_and_true_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new(
            1,
            1,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            0,
            0,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");


    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_and_1_1_1_and_true_failure_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new(
            1,
            1,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            1,
            1,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT_FALSE(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_and_1_1_0_and_true_failure_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new(
            1,
            1,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            1,
            1,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT_FALSE(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_and_1_0_1_and_true_failure_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new(
            1,
            1,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            1,
            0,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT_FALSE(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_and_0_1_1_and_true_failure_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new(
            1,
            1,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            0,
            1,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT_FALSE(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_0_0_rc_1_and_0_0_1_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            0,
            0,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT_FALSE(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.0.0-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_0_1_rc_1_and_0_0_1_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            0,
            0,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.0.0-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_1_0_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            0,
            1,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.0.1-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_1_0_0_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            1,
            0,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.1-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_rc_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            0,
            0,
            octaspireSemverTestAllocator,
            "rc",
            "");


    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1-1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_1_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            0,
            0,
            octaspireSemverTestAllocator,
            "1",
            "");


    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1-rc"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_rc_1_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            0,
            0,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");


    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_ra_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            0,
            0,
            octaspireSemverTestAllocator,
            "ra",
            "");


    ASSERT(semver2);

    // Add.
    ASSERT_FALSE(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_2_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            0,
            0,
            octaspireSemverTestAllocator,
            "2",
            "");


    ASSERT(semver2);

    // Add.
    ASSERT_FALSE(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_pop_back_called_on_prerelease_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver);

    ASSERT(octaspire_semver_add_buildmetadata(semver, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver, "5214f"));

    ASSERT(octaspire_semver_pop_back(semver));

    octaspire_string_t * str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-alpha.3+sha"));
    octaspire_string_release(str);
    str = 0;

    ASSERT(octaspire_semver_pop_back(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-alpha.3"));
    octaspire_string_release(str);
    str = 0;

    ASSERT(octaspire_semver_pop_back(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-alpha"));
    octaspire_string_release(str);
    str = 0;

    ASSERT(octaspire_semver_pop_back(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2"));
    octaspire_string_release(str);
    str = 0;

    // This should not have any effect anymore.
    ASSERT(octaspire_semver_pop_back(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}

TEST octaspire_semver_pop_front_called_on_prerelease_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver);

    ASSERT(octaspire_semver_add_buildmetadata(semver, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver, "5214f"));

    ASSERT(octaspire_semver_pop_front(semver));

    octaspire_string_t * str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-alpha.3+5214f"));
    octaspire_string_release(str);
    str = 0;

    ASSERT(octaspire_semver_pop_front(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-alpha.3"));
    octaspire_string_release(str);
    str = 0;

    ASSERT(octaspire_semver_pop_front(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-3"));
    octaspire_string_release(str);
    str = 0;

    ASSERT(octaspire_semver_pop_front(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2"));
    octaspire_string_release(str);
    str = 0;

    // This should not have any effect anymore.
    ASSERT(octaspire_semver_pop_front(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}


GREATEST_SUITE(octaspire_semver_suite)
{
    octaspireSemverTestAllocator = octaspire_allocator_new(0);

    assert(octaspireSemverTestAllocator);

    // Pre release element
    RUN_TEST(octaspire_semver_pre_release_elem_type_accessors_called_on_lexical_type_test);
    RUN_TEST(octaspire_semver_pre_release_elem_type_accessors_called_on_numerical_type_test);
    RUN_TEST(octaspire_semver_pre_release_elem_new_copy_called_with_numerical_type_test);
    RUN_TEST(octaspire_semver_pre_release_elem_new_copy_called_with_lexcal_type_test);
    RUN_TEST(octaspire_semver_pre_release_elem_make_numerical_and_lexical_test);

    // Semantic version number
    RUN_TEST(octaspire_semver_new_called_with_null_allocator_test);
    RUN_TEST(octaspire_semver_new_prerelease_0_1_2_alpha_3_and_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_new_copy_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_get_build_metadata_at_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_get_prerelease_at_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_get_length_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_get_major_minor_patch_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_3_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214g_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_2_alpha_4_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_4_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alphb_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_2_alphb_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_3_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_3_alpha_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_2_2_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_2_2_alpha_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_1_1_2_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_1_1_2_alpha_3_sha_5214f_test);

    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_0_0_alpha_and_1_0_0_alpha_1_test);
    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_0_0_alpha_1_and_1_0_0_alpha_beta_test);
    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_0_0_alpha_beta_and_1_0_0_beta_test);
    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_0_0_beta_and_1_0_0_beta_2_test);
    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_0_0_beta_2_and_1_0_0_beta_11_test);
    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_0_0_beta_11_and_1_0_0_rc_1_test);
    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_0_0_rc_1_and_1_0_0_test);

    RUN_TEST(octaspire_semver_comparison_operators_called_with_3_0_1_rc_1_and_3_0_1_rc_1_test);
    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_9_0_and_1_10_0_test);

    RUN_TEST(octaspire_semver_is_equal_to_c_string_called_with_1_9_0_and_same_and_five_different_test);

    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_0_0_rc_1_and_0_0_1_and_true_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_0_1_rc_1_and_0_1_0_and_true_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_1_0_0_and_true_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_and_0_0_0_rc_1_and_true_test);

    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_and_1_1_1_and_true_failure_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_and_1_1_0_and_true_failure_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_and_1_0_1_and_true_failure_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_and_0_1_1_and_true_failure_test);

    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_0_0_rc_1_and_0_0_1_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_0_1_rc_1_and_0_0_1_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_1_0_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_1_0_0_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_rc_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_1_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_rc_1_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_ra_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_2_and_false_test);

    RUN_TEST(octaspire_semver_pop_back_called_on_prerelease_0_1_2_alpha_3_and_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_pop_front_called_on_prerelease_0_1_2_alpha_3_and_metadata_sha_5214f_test);

    octaspire_allocator_release(octaspireSemverTestAllocator);
    octaspireSemverTestAllocator = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          dev/test/test_semver.c
//////////////////////////////////////////////////////////////////////////////////////////////////
void octaspire_core_amalgamated_write_test_file(
    char const * const name,
    unsigned char const * const buffer,
    size_t const bufferSize)
{
#ifdef _MSC_VER
    FILE *stream = 0;
    errno_t const err = fopen_s(&stream, name, "wb");

    if(err)
    {
        abort();
    }
#else
    FILE *stream = fopen(name, "wb");
#endif

    if (!stream)
    {
        abort();
    }

    if (!buffer || !bufferSize)
    {
        if (fclose(stream) != 0)
        {
            abort();
        }

        stream = 0;

        printf("  Wrote empty file '%s'\n", name);

        return;
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

    int c = 0;

    if (argc >= 2)
    {
        if (strcmp(argv[1], "--write-test-files") == 0)
        {
            --argc;
            ++argv;
            c = (int)'a';
        }
        else
        {
            printf("Unknown option '%s'\n", argv[1]);
            return EXIT_FAILURE;
        }
        printf("Option '%c' given with command line argument.\n", (char)c);
    }
    else
    {
        c = getchar();
    }

    switch (c)
    {
        case 'a':
        {
            printf("Writing test files to current working directory...\n");

            octaspire_core_amalgamated_write_test_file(
                "octaspire_helpers_path_to_buffer_failure_on_empty_file_test", 0, 0);



            unsigned char const octaspire_helpers_path_to_buffer_test[] = {
                0xc2, 0xa9, 0xe2, 0x89, 0xa0, 0xf0, 0x90, 0x80, 0x80
            };
            size_t const octaspire_helpers_path_to_buffer_test_len = 9;

            octaspire_core_amalgamated_write_test_file(
                "octaspire_helpers_path_to_buffer_test",
                octaspire_helpers_path_to_buffer_test,
                octaspire_helpers_path_to_buffer_test_len);


            unsigned char const octaspire_input_new_from_path_test[] = {
              0x61, 0x62, 0x63, 0xc2, 0xa9, 0xe2, 0x89, 0xa0, 0xf0, 0x90, 0x80, 0x80
            };
            size_t const octaspire_input_new_from_path_test_len = 12;

            octaspire_core_amalgamated_write_test_file(
                "octaspire_input_new_from_path_test",
                octaspire_input_new_from_path_test,
                octaspire_input_new_from_path_test_len);



            unsigned char const octaspire_stdio_fread_test[] = {
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
    RUN_SUITE(octaspire_stdio_suite);
    RUN_SUITE(octaspire_input_suite);
    RUN_SUITE(octaspire_vector_suite);
    RUN_SUITE(octaspire_list_suite);
    RUN_SUITE(octaspire_queue_suite);
    RUN_SUITE(octaspire_string_suite);
    RUN_SUITE(octaspire_semver_suite);
    RUN_SUITE(octaspire_pair_suite);
    RUN_SUITE(octaspire_map_suite);
    GREATEST_MAIN_END();
}


#endif  // OCTASPIRE_CORE_AMALGAMATED_UNIT_TEST_IMPLEMENTATION
#endif  // OCTASPIRE_CORE_AMALGAMATED_H
