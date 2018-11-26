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
#include "octaspire/core/octaspire_vector.h"
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "octaspire/core/octaspire_memory.h"
#include "octaspire/core/octaspire_helpers.h"

#include <stdio.h>

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

