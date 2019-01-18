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

#include "octaspire_vector.h"
#include "octaspire_memory.h"

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

