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
#include "../src/octaspire_vector.c"
#include <stdint.h>
#include "external/greatest.h"
#include "octaspire/core/octaspire_vector.h"
#include "octaspire/core/octaspire_helpers.h"
#include "octaspire/core/octaspire_core_config.h"

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
