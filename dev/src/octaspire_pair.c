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
#include "octaspire/core/octaspire_pair.h"
#include <string.h>
#include <stdlib.h>
#include "octaspire/core/octaspire_memory.h"
#include "octaspire/core/octaspire_helpers.h"

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

