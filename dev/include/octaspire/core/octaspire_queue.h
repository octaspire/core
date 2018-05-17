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

#include <stdbool.h>
#include <stddef.h>
#include "octaspire_memory.h"
#include "octaspire_list.h"

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

