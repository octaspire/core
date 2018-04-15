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

#include <stdbool.h>
#include <stddef.h>
#include "octaspire_memory.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct octaspire_container_list_node_t octaspire_container_list_node_t;

typedef void (*octaspire_container_list_element_callback_t)(void *element);

octaspire_container_list_node_t *octaspire_container_list_node_new(
    octaspire_container_list_node_t * const previous,
    octaspire_container_list_node_t * const next,
    size_t const elementSize,
    bool const elementIsPointer,
    octaspire_container_list_element_callback_t const elementReleaseCallback,
    void const * const element,
    octaspire_memory_allocator_t * const allocator);

void octaspire_container_list_node_release(octaspire_container_list_node_t *self);

void *octaspire_container_list_node_get_element(octaspire_container_list_node_t *self);

void const *octaspire_container_list_node_get_element_const(
    octaspire_container_list_node_t const * const self);

size_t octaspire_container_list_node_get_size_of_element_in_octets(
    octaspire_container_list_node_t const * const self);

void octaspire_container_list_node_set_next(
    octaspire_container_list_node_t * const self,
    octaspire_container_list_node_t * const next);

octaspire_container_list_node_t *octaspire_container_list_node_get_next(
    octaspire_container_list_node_t * const self);

octaspire_container_list_node_t const *octaspire_container_list_node_get_next_const(
    octaspire_container_list_node_t const * const self);

void octaspire_container_list_node_set_previous(
    octaspire_container_list_node_t * const self,
    octaspire_container_list_node_t * const previous);

octaspire_container_list_node_t *octaspire_container_list_node_get_previous(
    octaspire_container_list_node_t * const self);

octaspire_container_list_node_t const *octaspire_container_list_node_get_previous_const(
    octaspire_container_list_node_t const * const self);



typedef struct octaspire_container_list_t octaspire_container_list_t;

octaspire_container_list_t *octaspire_container_list_new(
    size_t const elementSize,
    bool const elementIsPointer,
    octaspire_container_list_element_callback_t const elementReleaseCallback,
    octaspire_memory_allocator_t *allocator);

void octaspire_container_list_release(octaspire_container_list_t *self);

octaspire_container_list_node_t *octaspire_container_list_get_front(
    octaspire_container_list_t *self);

octaspire_container_list_node_t const *octaspire_container_list_get_front_const(
    octaspire_container_list_t const * const self);

octaspire_container_list_node_t *octaspire_container_list_get_back(
    octaspire_container_list_t *self);

octaspire_container_list_node_t const *octaspire_container_list_get_back_const(
    octaspire_container_list_t const * const self);

bool octaspire_container_list_push_front(
    octaspire_container_list_t *self,
    void const * const element);

bool octaspire_container_list_push_back(
    octaspire_container_list_t *self,
    void const * const element);

bool octaspire_container_list_pop_front(
    octaspire_container_list_t * const self);

bool octaspire_container_list_pop_back(
    octaspire_container_list_t * const self);

bool octaspire_container_list_remove(
    octaspire_container_list_t * const self,
    octaspire_container_list_node_t * const node);

bool octaspire_container_list_clear(
    octaspire_container_list_t * const self);

size_t octaspire_container_list_get_length(
    octaspire_container_list_t const * const self);

bool octaspire_container_list_is_empty(
    octaspire_container_list_t const * const self);

octaspire_container_list_node_t *octaspire_container_list_get_at(
    octaspire_container_list_t * const self,
    ptrdiff_t const possiblyNegativeIndex);

octaspire_container_list_node_t const *octaspire_container_list_get_at_const(
    octaspire_container_list_t const * const self,
    ptrdiff_t const possiblyNegativeIndex);


typedef struct octaspire_container_list_node_iterator_t
{
    octaspire_container_list_t      *list;
    octaspire_container_list_node_t *currentNode;
}
octaspire_container_list_node_iterator_t;

octaspire_container_list_node_iterator_t octaspire_container_list_node_iterator_init(
    octaspire_container_list_t * const self);

bool octaspire_container_list_node_iterator_next(
    octaspire_container_list_node_iterator_t * const self);

#ifdef __cplusplus
}
#endif

#endif

