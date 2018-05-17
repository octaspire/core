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
#include <octaspire/core/octaspire_queue.h>
#include <octaspire/core/octaspire_list.h>
#include <octaspire/core/octaspire_memory.h>
#include <octaspire/core/octaspire_helpers.h>

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

