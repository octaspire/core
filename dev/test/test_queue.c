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
#include "../src/octaspire_queue.c"
#include <assert.h>
#include <stdint.h>
#include "external/greatest.h"
#include "octaspire/core/octaspire_queue.h"
#include "octaspire/core/octaspire_helpers.h"
#include "octaspire/core/octaspire_core_config.h"

static octaspire_allocator_t *octaspireContainerQueueTestAllocator = 0;

TEST octaspire_queue_new_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);
    ASSERT_EQ(0, octaspire_queue_get_max_length(queue));
    ASSERT_FALSE(octaspire_queue_has_max_length(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_new_allocation_failure_on_first_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerQueueTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerQueueTestAllocator));

    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT_EQ(0, queue);

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerQueueTestAllocator));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_new_with_max_length_of_56_with_size_t_elements_test(void)
{
    size_t const maxLength = 56;

    octaspire_queue_t *queue = octaspire_queue_new_with_max_length(
        maxLength,
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);
    ASSERT_EQ(maxLength, octaspire_queue_get_max_length(queue));
    ASSERT(octaspire_queue_has_max_length(queue));

    for (size_t i = 0; i < (3 * maxLength); ++i)
    {
        octaspire_queue_push(queue, &i);

        ASSERT(octaspire_queue_get_length(queue) <= maxLength);

        ASSERT_EQ(
            i < maxLength ? 0 : (i + 1 - maxLength),
            *(size_t const * const)octaspire_queue_peek(queue));

        size_t firstExpectedNumber = 0;

        if (i >= (maxLength-1))
        {
            firstExpectedNumber += (i - (maxLength - 1));
        }

        for (size_t j = 0; j < octaspire_queue_get_length(queue); ++j)
        {
            size_t const storedNum =
                *(size_t const * const)octaspire_queue_get_at_const(
                    queue,
                    (ptrdiff_t)j);

            size_t const expectedNum = firstExpectedNumber + j;

            ASSERT_EQ(expectedNum, storedNum);
        }
    }

    ASSERT_EQ(maxLength, octaspire_queue_get_length(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_new_with_max_length_of_10_with_ostring_ptr_elements_test(void)
{
    size_t const maxLength = 10;

    octaspire_queue_t *queue = octaspire_queue_new_with_max_length(
        maxLength,
        sizeof(octaspire_string_t*),
        true,
        (octaspire_queue_element_callback_t)octaspire_string_release,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);
    ASSERT_EQ(maxLength, octaspire_queue_get_max_length(queue));
    ASSERT(octaspire_queue_has_max_length(queue));

    for (size_t i = 0; i < (3 * maxLength); ++i)
    {
        octaspire_string_t * const str = octaspire_string_new_format(
            octaspireContainerQueueTestAllocator,
            "This is string %zu.",
            i);

        octaspire_queue_push(queue, &str);

        ASSERT(octaspire_queue_get_length(queue) <= maxLength);

        size_t firstExpectedNumber = 0;

        if (i >= maxLength)
        {
            firstExpectedNumber += (i - (maxLength - 1));
        }

        for (size_t j = 0; j < octaspire_queue_get_length(queue); ++j)
        {
            octaspire_string_t const * const storedStr =
                octaspire_queue_get_at_const(
                    queue,
                    (ptrdiff_t)j);

            octaspire_string_t * expectedStr =
                octaspire_string_new_format(
                    octaspireContainerQueueTestAllocator,
                    "This is string %zu.",
                    firstExpectedNumber + j);

            ASSERT(octaspire_string_is_equal(expectedStr, storedStr));

            octaspire_string_release(expectedStr);
            expectedStr = 0;
        }
    }

    ASSERT_EQ(maxLength, octaspire_queue_get_length(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_release_called_with_null_pointer_test(void)
{
    octaspire_queue_release(0);

    PASS();
}

TEST octaspire_queue_peek_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    ASSERT_EQ(0, octaspire_queue_peek(queue));

    size_t const expected = 123;
    ASSERT(octaspire_queue_push(queue, &expected));
    ASSERT_EQ(expected, *(size_t const * const)octaspire_queue_peek(queue));

    size_t const next = 9876;
    ASSERT(octaspire_queue_push(queue, &next));
    ASSERT_EQ(expected, *(size_t const * const)octaspire_queue_peek(queue));

    ASSERT(octaspire_queue_pop(queue));
    ASSERT_EQ(next, *(size_t const * const)octaspire_queue_peek(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_peek_const_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    ASSERT_EQ(0, octaspire_queue_peek_const(queue));

    size_t const expected = 123;
    ASSERT(octaspire_queue_push(queue, &expected));
    ASSERT_EQ(expected, *(size_t const * const)octaspire_queue_peek_const(queue));

    size_t const next = 9876;
    ASSERT(octaspire_queue_push(queue, &next));
    ASSERT_EQ(expected, *(size_t const * const)octaspire_queue_peek_const(queue));

    ASSERT(octaspire_queue_pop(queue));
    ASSERT_EQ(next, *(size_t const * const)octaspire_queue_peek_const(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_pop_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    size_t const numElements = 100;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));
    }

    ASSERT_EQ(numElements, octaspire_queue_get_length(queue));

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_pop(queue));
        size_t const * const ptr = (size_t const * const)octaspire_queue_peek(queue);

        if (i != (numElements -1))
        {
            ASSERT(ptr);
            ASSERT_EQ(i + 1, *ptr);
        }
        else
        {
            ASSERT_FALSE(ptr);
        }
    }

    ASSERT_EQ(0, octaspire_queue_get_length(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_push_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    size_t const numElements = 100;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT_EQ(i, octaspire_queue_get_length(queue));
        ASSERT(octaspire_queue_push(queue, &i));
        ASSERT_EQ(i + 1, octaspire_queue_get_length(queue));
        size_t const * const ptr = (size_t const * const)octaspire_queue_peek(queue);
        ASSERT_EQ(0, *ptr);

        for (size_t j = 0; j < octaspire_queue_get_length(queue); ++j)
        {
            size_t const * const jth =
                (size_t const * const)octaspire_queue_get_at(
                    queue,
                    (ptrdiff_t)j);

            ASSERT_EQ(j, *jth);
        }
    }

    ASSERT_EQ(numElements, octaspire_queue_get_length(queue));

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_pop(queue));
        size_t const * const ptr = (size_t const * const)octaspire_queue_peek(queue);

        if (i != (numElements -1))
        {
            ASSERT(ptr);
            ASSERT_EQ(i + 1, *ptr);
        }
        else
        {
            ASSERT_FALSE(ptr);
        }
    }

    ASSERT_EQ(0, octaspire_queue_get_length(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_clear_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    ASSERT(octaspire_queue_clear(queue));
    ASSERT(octaspire_queue_is_empty(queue));
    ASSERT_EQ(0, octaspire_queue_get_length(queue));
    ASSERT_FALSE(octaspire_queue_peek(queue));

    size_t const value = 10;
    ASSERT(octaspire_queue_push(queue, &value));

    ASSERT(octaspire_queue_clear(queue));
    ASSERT(octaspire_queue_is_empty(queue));
    ASSERT_EQ(0, octaspire_queue_get_length(queue));
    ASSERT_FALSE(octaspire_queue_peek(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_get_length_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    ASSERT_EQ(0, octaspire_queue_get_length(queue));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));
        ASSERT_EQ(i + 1, octaspire_queue_get_length(queue));
    }

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_pop(queue));
        ASSERT_EQ(numElements - 1 - i, octaspire_queue_get_length(queue));
    }

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_is_empty_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    ASSERT(octaspire_queue_is_empty(queue));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));
        ASSERT_FALSE(octaspire_queue_is_empty(queue));
    }

    for (size_t i = 0; i < (numElements - 1); ++i)
    {
        ASSERT(octaspire_queue_pop(queue));
        ASSERT_FALSE(octaspire_queue_is_empty(queue));
    }

    ASSERT(octaspire_queue_pop(queue));
    ASSERT(octaspire_queue_is_empty(queue));

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_get_at_failure_on_too_large_index_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    ASSERT_FALSE(octaspire_queue_get_at(queue, 0));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));

        size_t j;
        for (j = 0; j < i; ++j)
        {
            ASSERT(octaspire_queue_get_at(queue, (ptrdiff_t)j));
        }

        ++j;
        ASSERT_FALSE(octaspire_queue_get_at(queue, (ptrdiff_t)j));
    }

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_get_at_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    size_t const numElements = 100;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));

        for (size_t j = 0; j < i; ++j)
        {
            size_t const * const ptr =
                octaspire_queue_get_at(queue, (ptrdiff_t)j);

            ASSERT(ptr);
            ASSERT_EQ(j, *ptr);
        }

        // Negative index
        size_t * const ptr =
            octaspire_queue_get_at(queue, -1);

        ASSERT(ptr);
        ASSERT_EQ(i, *ptr);

        // Failure test
        ASSERT_FALSE(octaspire_queue_get_at(
            queue,
            -((ptrdiff_t)(i + 2))));

        ASSERT_FALSE(octaspire_queue_get_at(
            queue,
            (ptrdiff_t)(i + 1)));
    }

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_get_at_const_failure_on_too_large_index_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    ASSERT_FALSE(octaspire_queue_get_at_const(queue, 0));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));

        size_t j;
        for (j = 0; j < i; ++j)
        {
            ASSERT(octaspire_queue_get_at_const(queue, (ptrdiff_t)j));
        }

        ++j;
        ASSERT_FALSE(octaspire_queue_get_at_const(queue, (ptrdiff_t)j));
    }

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_get_at_const_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    size_t const numElements = 100;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));

        for (size_t j = 0; j < i; ++j)
        {
            size_t const * const ptr =
                octaspire_queue_get_at_const(
                    queue,
                    (ptrdiff_t)j);
            ASSERT(ptr);
            ASSERT_EQ(j, *ptr);
        }

        // Negative index
        size_t const * const ptr =
            octaspire_queue_get_at_const(queue, -1);

        ASSERT(ptr);
        ASSERT_EQ(i, *ptr);

        // Failure test
        ASSERT_FALSE(octaspire_queue_get_at_const(
            queue,
            -((ptrdiff_t)(i + 2))));

        ASSERT_FALSE(octaspire_queue_get_at_const(
            queue,
            (ptrdiff_t)(i + 1)));
    }

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_get_set_has_max_length_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT_EQ(0, octaspire_queue_get_max_length(queue));
    ASSERT_FALSE(octaspire_queue_has_max_length(queue));

    size_t const value = 100;

    for (size_t i = 0; i < value; ++i)
    {
        ASSERT(octaspire_queue_set_max_length(queue, i));
        ASSERT_EQ(i, octaspire_queue_get_max_length(queue));
        ASSERT_EQ(0, octaspire_queue_get_length(queue));
    }

    size_t const numElements = 256;
    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));
    }

    ASSERT_EQ(numElements, octaspire_queue_get_length(queue));
    ASSERT_FALSE(octaspire_queue_has_max_length(queue));

    for (size_t i = value; i > 0; --i)
    {
        ASSERT(octaspire_queue_set_max_length(queue, i));
        ASSERT(octaspire_queue_set_has_max_length(queue, true));
        ASSERT(octaspire_queue_has_max_length(queue));
        ASSERT_EQ(i, octaspire_queue_get_max_length(queue));
        ASSERT_EQ(i, octaspire_queue_get_length(queue));
    }

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_iterator_called_on_empty_queue_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    octaspire_queue_iterator_t iter =
        octaspire_queue_iterator_init(queue);

    for (size_t i = 0; i < 10; ++i)
    {
        ASSERT_EQ(iter.queue, queue);
        ASSERT_FALSE(iter.iterator.currentNode);
        ASSERT_FALSE(octaspire_queue_iterator_next(&iter));
    }

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

TEST octaspire_queue_iterator_test(void)
{
    octaspire_queue_t *queue = octaspire_queue_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerQueueTestAllocator);

    ASSERT(queue);

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_queue_push(queue, &i));
    }

    octaspire_queue_iterator_t iter =
        octaspire_queue_iterator_init(queue);

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(iter.iterator.currentNode);

        size_t const fromIter =
            *(size_t const * const)octaspire_list_node_get_element_const(
                iter.iterator.currentNode);

        ASSERT_EQ(iter.queue, queue);
        ASSERT_EQ(i, fromIter);

        if ((i + 1) < numElements)
        {
            ASSERT(octaspire_queue_iterator_next(&iter));
        }
    }

    ASSERT_FALSE(octaspire_queue_iterator_next(&iter));
    ASSERT_FALSE(iter.iterator.currentNode);

    octaspire_queue_release(queue);
    queue = 0;

    PASS();
}

GREATEST_SUITE(octaspire_queue_suite)
{
    octaspireContainerQueueTestAllocator = octaspire_allocator_new(0);
    assert(octaspireContainerQueueTestAllocator);

    RUN_TEST(octaspire_queue_new_test);
    RUN_TEST(octaspire_queue_new_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_queue_new_with_max_length_of_56_with_size_t_elements_test);
    RUN_TEST(octaspire_queue_new_with_max_length_of_10_with_ostring_ptr_elements_test);
    RUN_TEST(octaspire_queue_release_called_with_null_pointer_test);
    RUN_TEST(octaspire_queue_peek_test);
    RUN_TEST(octaspire_queue_peek_const_test);
    RUN_TEST(octaspire_queue_pop_test);
    RUN_TEST(octaspire_queue_push_test);
    RUN_TEST(octaspire_queue_clear_test);
    RUN_TEST(octaspire_queue_get_length_test);
    RUN_TEST(octaspire_queue_is_empty_test);
    RUN_TEST(octaspire_queue_get_at_failure_on_too_large_index_test);
    RUN_TEST(octaspire_queue_get_at_test);
    RUN_TEST(octaspire_queue_get_at_const_failure_on_too_large_index_test);
    RUN_TEST(octaspire_queue_get_at_const_test);
    RUN_TEST(octaspire_queue_get_set_has_max_length_test);
    RUN_TEST(octaspire_queue_iterator_called_on_empty_queue_test);
    RUN_TEST(octaspire_queue_iterator_test);

    octaspire_allocator_release(octaspireContainerQueueTestAllocator);
    octaspireContainerQueueTestAllocator = 0;
}
