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
#include "../src/octaspire_list.c"
#include <assert.h>
#include <stdint.h>
#include "external/greatest.h"
#include "octaspire/core/octaspire_list.h"
#include "octaspire/core/octaspire_helpers.h"
#include "octaspire/core/octaspire_core_config.h"

static octaspire_allocator_t *octaspireContainerListTestAllocator = 0;

TEST octaspire_list_new_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_new_allocation_failure_on_first_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerListTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerListTestAllocator));

    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT_EQ(0, list);

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerListTestAllocator));

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_release_called_with_null_pointer_test(void)
{
    octaspire_list_release(0);

    PASS();
}

TEST octaspire_list_get_front_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    ASSERT_EQ(0, octaspire_list_get_front(list));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_front(list, &i));

        octaspire_list_node_t const * const front =
            octaspire_list_get_front(list);

        ASSERT_EQ(i, *((size_t const * const)octaspire_list_node_get_element_const(front)));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_get_front_const_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    ASSERT_EQ(0, octaspire_list_get_front_const(list));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_front(list, &i));

        octaspire_list_node_t const * const front =
            octaspire_list_get_front_const(list);

        ASSERT_EQ(i, *((size_t const * const)octaspire_list_node_get_element_const(front)));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_get_back_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    ASSERT_EQ(0, octaspire_list_get_back(list));

    size_t const numElements = 10;

    octaspire_list_node_t const *first = 0;
    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));

        octaspire_list_node_t const * const back =
            octaspire_list_get_back(list);

        if (i == 0)
        {
            first = back;
        }

        ASSERT_EQ(first, octaspire_list_get_front(list));
        ASSERT_EQ(i, *((size_t const * const)octaspire_list_node_get_element_const(back)));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_get_back_const_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    ASSERT_EQ(0, octaspire_list_get_back_const(list));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));

        octaspire_list_node_t const * const back =
            octaspire_list_get_back_const(list);

        ASSERT_EQ(i, *((size_t const * const)octaspire_list_node_get_element_const(back)));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_clear_called_on_empty_list_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
            sizeof(size_t),
            false,
            0,
            octaspireContainerListTestAllocator);

    ASSERT(list);

    ASSERT_EQ(0, octaspire_list_get_length(list));

    ASSERT(octaspire_list_clear(list));

    ASSERT_EQ(0, octaspire_list_get_length(list));

    ASSERT_EQ(0, list->numElements);

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_clear_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));
    }

    ASSERT_EQ(numElements, list->numElements);

    ASSERT(octaspire_list_clear(list));

    ASSERT_EQ(0, octaspire_list_get_length(list));
    ASSERT_EQ(0, list->numElements);

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_push_back_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    ASSERT_EQ(0, octaspire_list_get_length(list));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));

        ASSERT_EQ(i + 1, octaspire_list_get_length(list));
        octaspire_list_node_t const * front = octaspire_list_get_front(list);
        octaspire_list_node_t const * back  = octaspire_list_get_back(list);

        ASSERT_EQ(0,     *((size_t const * const)octaspire_list_node_get_element_const(front)));
        ASSERT_EQ(i,     *((size_t const * const)octaspire_list_node_get_element_const(back)));
    }

    ASSERT_EQ(numElements, list->numElements);

    octaspire_list_node_t const * node = octaspire_list_get_front(list);

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(node);
        ASSERT_EQ(i, *((size_t const * const)octaspire_list_node_get_element_const(node)));
        node = octaspire_list_node_get_next_const(node);
    }

    ASSERT(node == 0);

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_push_front_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    ASSERT_EQ(0, octaspire_list_get_length(list));

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_front(list, &i));

        ASSERT_EQ(i + 1, octaspire_list_get_length(list));
        octaspire_list_node_t const * front = octaspire_list_get_front(list);
        octaspire_list_node_t const * back  = octaspire_list_get_back(list);

        ASSERT_EQ(i,     *((size_t const * const)octaspire_list_node_get_element_const(front)));
        ASSERT_EQ(0,     *((size_t const * const)octaspire_list_node_get_element_const(back)));
    }

    ASSERT_EQ(numElements, list->numElements);

    octaspire_list_node_t const * node = octaspire_list_get_front(list);

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(node);
        ASSERT_EQ(numElements - 1 - i, *((size_t const * const)octaspire_list_node_get_element_const(node)));
        node = octaspire_list_node_get_next_const(node);
    }

    ASSERT(node == 0);

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_pop_front_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));
    }

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_list_node_t const * node = octaspire_list_get_front(list);
        ASSERT(node);
        ASSERT_EQ(i, *((size_t const * const)octaspire_list_node_get_element_const(node)));

        ASSERT(octaspire_list_pop_front(list));
    }

    ASSERT_EQ(0, octaspire_list_get_length(list));
    ASSERT_EQ(0, octaspire_list_get_front(list));
    ASSERT_EQ(0, octaspire_list_get_back(list));

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_pop_back_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));
    }

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_list_node_t const * const first1 =
            octaspire_list_get_front_const(list);

        ASSERT(first1);
        ASSERT_EQ(0, *((size_t const * const)octaspire_list_node_get_element_const(first1)));

        ASSERT(octaspire_list_pop_back(list));

        if (i < (numElements - 1))
        {
            // Make sure that front doesn't change
            octaspire_list_node_t const * const first2 =
                octaspire_list_get_front_const(list);

            ASSERT(first2);
            ASSERT_EQ(first1, first2);

            // Check back
            octaspire_list_node_t const * const last =
                octaspire_list_get_back_const(list);

            ASSERT(last);

            ASSERT_EQ(
                numElements - 2 - i,
                *((size_t const * const)octaspire_list_node_get_element_const(last)));
        }
    }

    ASSERT_EQ(0, octaspire_list_get_length(list));
    ASSERT_EQ(0, octaspire_list_get_front(list));
    ASSERT_EQ(0, octaspire_list_get_back(list));

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_remove_middle_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    size_t const numElements = 10;

    octaspire_list_node_t * node = 0;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));

        if (i == 5)
        {
            node = octaspire_list_get_back(list);
        }
    }

    ASSERT(node);
    ASSERT(octaspire_list_remove(list, node));

    ASSERT_EQ(numElements - 1, octaspire_list_get_length(list));

    for (size_t i = 0; i < (numElements - 1); ++i)
    {
        node = octaspire_list_get_at(list, (ptrdiff_t)i);

        ASSERT(node);

        if (i < 5)
        {
            ASSERT_EQ(
                i < 5 ? i : (i + 1),
                *((size_t const * const)octaspire_list_node_get_element_const(node)));
        }
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_remove_first_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    size_t const numElements = 10;

    octaspire_list_node_t * node = 0;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));

        if (i == 0)
        {
            node = octaspire_list_get_back(list);
        }
    }

    ASSERT(node);
    ASSERT(octaspire_list_remove(list, node));

    ASSERT_EQ(numElements - 1, octaspire_list_get_length(list));

    for (size_t i = 0; i < (numElements - 1); ++i)
    {
        node = octaspire_list_get_at(list, (ptrdiff_t)i);

        ASSERT(node);

        ASSERT_EQ(
            (i + 1),
            *((size_t const * const)octaspire_list_node_get_element_const(node)));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_remove_last_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    size_t const numElements = 10;

    octaspire_list_node_t * node = 0;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));

        if (i == (numElements - 1))
        {
            node = octaspire_list_get_back(list);
        }
    }

    ASSERT(node);
    ASSERT(octaspire_list_remove(list, node));

    ASSERT_EQ(numElements - 1, octaspire_list_get_length(list));

    for (size_t i = 0; i < (numElements - 1); ++i)
    {
        node = octaspire_list_get_at(list, (ptrdiff_t)i);

        ASSERT(node);

        ASSERT_EQ(
            i,
            *((size_t const * const)octaspire_list_node_get_element_const(node)));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_remove_even_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    size_t const numElements = 10;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));
    }

    octaspire_list_node_t *node = octaspire_list_get_front(list);
    size_t index = 0;

    while (node)
    {
        octaspire_list_node_t * const next = octaspire_list_node_get_next(node);

        if (index % 2 == 0)
        {
            octaspire_list_remove(list, node);
            node = 0;
        }

        ++index;

        node = next;
    }

    ASSERT_EQ(5, octaspire_list_get_length(list));

    node = octaspire_list_get_front(list);
    index = 0;

    while (node)
    {
        octaspire_list_node_t * const next = octaspire_list_node_get_next(node);

        if (index % 2 == 0)
        {
            ++index;
        }

        ASSERT_EQ(
            index,
            *((size_t const * const)octaspire_list_node_get_element_const(node)));

        ++index;

        node = next;
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_get_at_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));
    }

    // Positive indices
    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_list_node_t const * const node =
            octaspire_list_get_at(list, (ptrdiff_t)i);

        ASSERT_EQ(
            i,
            *((size_t const * const)octaspire_list_node_get_element_const(node)));
    }

    // Negative indices
    for (size_t i = 0; i < numElements; ++i)
    {
        ptrdiff_t tmpIndex = -1 - (ptrdiff_t)i;
        octaspire_list_node_t const * const node =
            octaspire_list_get_at(list, tmpIndex);

        ASSERT_EQ(
            numElements - 1 - i,
            *((size_t const * const)octaspire_list_node_get_element_const(node)));
    }

    // Test failure
    ASSERT_FALSE(octaspire_list_get_at(list, numElements + 1));
    ASSERT_FALSE(octaspire_list_get_at(list, -((ptrdiff_t)(numElements + 2))));

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_get_at_const_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));
    }

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_list_node_t const * const node =
            octaspire_list_get_at_const(list, (ptrdiff_t)i);

        ASSERT_EQ(
            i,
            *((size_t const * const)octaspire_list_node_get_element_const(node)));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_node_iterator_called_on_empty_list_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    octaspire_list_node_iterator_t iter =
        octaspire_list_node_iterator_init(list);

    for (size_t i = 0; i < 10; ++i)
    {
        ASSERT_EQ(iter.list, list);
        ASSERT_FALSE(iter.currentNode);
        ASSERT_FALSE(octaspire_list_node_iterator_next(&iter));
    }

    octaspire_list_release(list);
    list = 0;

    PASS();
}

TEST octaspire_list_node_iterator_test(void)
{
    octaspire_list_t *list = octaspire_list_new(
        sizeof(size_t),
        false,
        0,
        octaspireContainerListTestAllocator);

    ASSERT(list);

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(octaspire_list_push_back(list, &i));
    }

    octaspire_list_node_iterator_t iter =
        octaspire_list_node_iterator_init(list);

    for (size_t i = 0; i < numElements; ++i)
    {
        ASSERT(iter.currentNode);

        size_t const fromIter =
            *(size_t const * const)octaspire_list_node_get_element_const(
                iter.currentNode);

        ASSERT_EQ(iter.list, list);
        ASSERT_EQ(i, fromIter);

        if ((i + 1) < numElements)
        {
            ASSERT(octaspire_list_node_iterator_next(&iter));
        }
    }

    ASSERT_FALSE(octaspire_list_node_iterator_next(&iter));
    ASSERT_FALSE(iter.currentNode);

    octaspire_list_release(list);
    list = 0;

    PASS();
}

GREATEST_SUITE(octaspire_list_suite)
{
    octaspireContainerListTestAllocator = octaspire_allocator_new(0);
    assert(octaspireContainerListTestAllocator);

    RUN_TEST(octaspire_list_new_test);
    RUN_TEST(octaspire_list_new_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_list_release_called_with_null_pointer_test);
    RUN_TEST(octaspire_list_get_front_test);
    RUN_TEST(octaspire_list_get_front_const_test);
    RUN_TEST(octaspire_list_get_back_test);
    RUN_TEST(octaspire_list_get_back_const_test);
    RUN_TEST(octaspire_list_clear_called_on_empty_list_test);
    RUN_TEST(octaspire_list_clear_test);
    RUN_TEST(octaspire_list_push_back_test);
    RUN_TEST(octaspire_list_push_front_test);
    RUN_TEST(octaspire_list_pop_front_test);
    RUN_TEST(octaspire_list_pop_back_test);
    RUN_TEST(octaspire_list_remove_middle_test);
    RUN_TEST(octaspire_list_remove_first_test);
    RUN_TEST(octaspire_list_remove_last_test);
    RUN_TEST(octaspire_list_remove_even_test);
    RUN_TEST(octaspire_list_get_at_test);
    RUN_TEST(octaspire_list_get_at_const_test);
    RUN_TEST(octaspire_list_node_iterator_called_on_empty_list_test);
    RUN_TEST(octaspire_list_node_iterator_test);

    octaspire_allocator_release(octaspireContainerListTestAllocator);
    octaspireContainerListTestAllocator = 0;
}
