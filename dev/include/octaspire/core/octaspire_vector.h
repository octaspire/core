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

#include <stdbool.h>
#include <stddef.h>
//#include <stdio.h>
#include "octaspire_memory.h"

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

