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
#include "octaspire/core/octaspire_list.h"
#include <string.h>
#include "octaspire/core/octaspire_pair.h"
#include "octaspire/core/octaspire_memory.h"
#include "octaspire/core/octaspire_helpers.h"

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

