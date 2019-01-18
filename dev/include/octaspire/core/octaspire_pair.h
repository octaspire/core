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

#include <stdbool.h>
#include <stddef.h>
#include "octaspire_memory.h"

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

