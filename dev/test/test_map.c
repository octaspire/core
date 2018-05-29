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
#include "../src/octaspire_map.c"
#include <assert.h>
#include <inttypes.h>
#include "external/greatest.h"
#include "octaspire/core/octaspire_map.h"
#include "octaspire/core/octaspire_memory.h"
#include "octaspire/core/octaspire_string.h"
#include "octaspire/core/octaspire_helpers.h"
#include "octaspire/core/octaspire_core_config.h"

static octaspire_allocator_t *octaspireContainerHashMapTestAllocator = 0;



TEST octaspire_map_element_new_allocation_failure_on_first_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    size_t const value = 0;
    octaspire_map_element_t *element = octaspire_map_element_new(
        0,
        sizeof(value),
        false,
        &value,
        sizeof(value),
        false,
        &value,
        octaspireContainerHashMapTestAllocator);

    ASSERT_FALSE(element);
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_map_element_release(element);
    element = 0;

    PASS();
}

TEST octaspire_map_element_new_allocation_failure_on_second_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 2, 0x01);
    ASSERT_EQ(2, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    size_t const value = 0;
    octaspire_map_element_t *element = octaspire_map_element_new(
        0,
        sizeof(value),
        false,
        &value,
        sizeof(value),
        false,
        &value,
        octaspireContainerHashMapTestAllocator);

    ASSERT_FALSE(element);
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_map_element_release(element);
    element = 0;

    PASS();
}

TEST octaspire_map_element_new_allocation_failure_on_third_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 3, 0x03);
    ASSERT_EQ(3, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    size_t const value = 0;
    octaspire_map_element_t *element = octaspire_map_element_new(
        0,
        sizeof(value),
        false,
        &value,
        sizeof(value),
        false,
        &value,
        octaspireContainerHashMapTestAllocator);

    ASSERT_FALSE(element);
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_map_element_release(element);
    element = 0;

    PASS();
}

static bool octaspire_map_new_test_key_compare_function_for_size_t_keys(
    void const * const key1,
    void const * const key2);

static uint32_t octaspire_map_new_test_key_hash_function_for_size_t_keys(
    void const * const key);

static bool octaspire_map_new_test_key_compare_function_for_size_t_keys(
    void const * const key1,
    void const * const key2)
{
    return *(size_t const * const)key1 == *(size_t const * const)key2;
}

static uint32_t octaspire_map_new_test_key_hash_function_for_size_t_keys(
    void const * const key)
{
    size_t const value = *(size_t const * const)key;
    return (uint32_t)value;
}

TEST octaspire_map_private_rehash_allocation_failure_on_first_allocation_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 1, 0x00);
    ASSERT_EQ(1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    ASSERT_FALSE(octaspire_map_private_rehash(hashMap));
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_new_keys_uint32_t_and_values_size_t_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        uint32_t hash = (uint32_t)i;

        octaspire_map_put(hashMap, hash, &i, &i);
    }

    ASSERT_EQ(numElements, octaspire_map_get_number_of_elements(hashMap));

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_map_element_t *element =
            octaspire_map_get(hashMap, (uint32_t)i, &i);

        ASSERT_EQ(i,   octaspire_map_element_get_hash(element));
        ASSERT_EQ(i,   *(size_t*)octaspire_map_element_get_key(element));
        ASSERT_EQ(i,   *(size_t*)octaspire_map_element_get_value(element));
    }

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_add_same_key_many_times_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    size_t const key = 1024;

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT(octaspire_map_put(
            hashMap,
            octaspire_helpers_calculate_hash_for_size_t_argument(key),
            &key,
            &i));

        octaspire_map_element_t * const element = octaspire_map_get(
            hashMap,
            octaspire_helpers_calculate_hash_for_size_t_argument(key),
            &key);

        ASSERT(element);

        ASSERT_EQ(key, *(size_t*)octaspire_map_element_get_key(element));

        octaspire_vector_t * const values =
            octaspire_map_element_get_values(element);

        ASSERT_EQ(i + 1,   octaspire_vector_get_length(values));

        for (size_t j = 0; j < octaspire_vector_get_length(values) ; ++j)
        {
            ASSERT_EQ(
                j,
                *(size_t*)octaspire_vector_get_element_at(
                    values,
                    (ptrdiff_t)j));
        }
    }

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_new_allocation_failure_on_first_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT_FALSE(hashMap);
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_new_allocation_failure_on_second_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 2, 0x01);
    ASSERT_EQ(2, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator));

    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT_FALSE(hashMap);
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerHashMapTestAllocator, 0, 0x00);

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

static bool octaspire_map_new_test_key_compare_function_for_ostring_t_keys(
    void const * const key1,
    void const * const key2);

static uint32_t octaspire_map_new_test_key_hash_function_for_ostring_t_keys(
    void const * const key);

static bool octaspire_map_new_test_key_compare_function_for_ostring_t_keys(
    void const * const key1,
    void const * const key2)
{
    assert(key1);
    assert(key2);

    return octaspire_string_is_equal(
        (octaspire_string_t const * const)key1,
        (octaspire_string_t const * const)key2);
}

static uint32_t octaspire_map_new_test_key_hash_function_for_ostring_t_keys(
    void const * const key)
{
    assert(key);
    return octaspire_string_get_hash((octaspire_string_t const * const)key);
}

TEST octaspire_map_new_keys_ostring_t_and_values_ostring_t_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(octaspire_string_t *),
        true,
        sizeof(octaspire_string_t *),
        true,
        octaspire_map_new_test_key_compare_function_for_ostring_t_keys,
        octaspire_map_new_test_key_hash_function_for_ostring_t_keys,
        (octaspire_map_element_callback_t)octaspire_string_release,
        (octaspire_map_element_callback_t)octaspire_string_release,
        octaspireContainerHashMapTestAllocator);

    size_t const numElements = 32;

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t const hash = octaspire_string_get_hash(str);

        octaspire_string_t *cpyStr = octaspire_string_new_copy(str, octaspireContainerHashMapTestAllocator);
        ASSERT(octaspire_string_is_equal(str, cpyStr));
        octaspire_map_put(hashMap, hash, &cpyStr, &str);

        ASSERT_EQ(i+1, octaspire_map_get_number_of_elements(hashMap));
    }

    ASSERT_EQ(numElements, octaspire_map_get_number_of_elements(hashMap));

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t hash = octaspire_string_get_hash(str);

        octaspire_map_element_t *element =
            octaspire_map_get(hashMap, hash, &str);

        ASSERT(element);

        ASSERT_EQ(hash, octaspire_map_element_get_hash(element));

        ASSERT(octaspire_string_is_equal(str, (octaspire_string_t*)octaspire_map_element_get_key(element)));

        ASSERT(octaspire_string_is_equal(str, (octaspire_string_t*)octaspire_map_element_get_value(element)));

        octaspire_string_release(str);
        str = 0;
    }

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_new_with_octaspire_string_keys_test(void)
{
    octaspire_map_t *hashMap =
        octaspire_map_new_with_octaspire_string_keys(
            sizeof(octaspire_string_t *),
            true,
            (octaspire_map_element_callback_t)
                octaspire_string_release,
            octaspireContainerHashMapTestAllocator);

    size_t const numElements = 32;

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t const hash = octaspire_string_get_hash(str);

        octaspire_string_t *cpyStr = octaspire_string_new_copy(str, octaspireContainerHashMapTestAllocator);
        ASSERT(octaspire_string_is_equal(str, cpyStr));
        octaspire_map_put(hashMap, hash, &cpyStr, &str);

        ASSERT_EQ(i+1, octaspire_map_get_number_of_elements(hashMap));
    }

    ASSERT_EQ(numElements, octaspire_map_get_number_of_elements(hashMap));

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t hash = octaspire_string_get_hash(str);

        octaspire_map_element_t *element =
            octaspire_map_get(hashMap, hash, &str);

        ASSERT(element);

        ASSERT_EQ(hash, octaspire_map_element_get_hash(element));

        ASSERT(octaspire_string_is_equal(str, (octaspire_string_t*)octaspire_map_element_get_key(element)));

        ASSERT(octaspire_string_is_equal(str, (octaspire_string_t*)octaspire_map_element_get_value(element)));

        octaspire_string_release(str);
        str = 0;
    }

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_new_with_size_t_keys_test(void)
{
    octaspire_map_t *hashMap =
        octaspire_map_new_with_size_t_keys(
            sizeof(octaspire_string_t *),
            true,
            (octaspire_map_element_callback_t)
                octaspire_string_release,
            octaspireContainerHashMapTestAllocator);

    size_t const numElements = 32;

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t const hash = octaspire_map_helper_size_t_get_hash(i);

        ASSERT(octaspire_map_put(hashMap, hash, &i, &str));

        ASSERT_EQ(i+1, octaspire_map_get_number_of_elements(hashMap));
    }

    ASSERT_EQ(numElements, octaspire_map_get_number_of_elements(hashMap));

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerHashMapTestAllocator,
            "%zu",
            i);

        uint32_t const hash = octaspire_map_helper_size_t_get_hash(i);

        octaspire_map_element_t *element =
            octaspire_map_get(hashMap, hash, &i);

        ASSERT(element);

        ASSERT_EQ(hash, octaspire_map_element_get_hash(element));

        ASSERT_EQ(i, *(size_t const * const)octaspire_map_element_get_key(element));

        ASSERT(octaspire_string_is_equal(str, (octaspire_string_t*)octaspire_map_element_get_value(element)));

        octaspire_string_release(str);
        str = 0;
    }

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_element_iterator_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    octaspire_map_element_iterator_t iterator =
        octaspire_map_element_iterator_init(hashMap);

    ASSERT_EQ(hashMap, iterator.hashMap);
    ASSERT_EQ(0,       iterator.element);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(octaspire_map_element_iterator_next(&iterator));

        ASSERT_EQ(hashMap, iterator.hashMap);
        ASSERT_EQ(0,       iterator.element);
    }

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        uint32_t hash = (uint32_t)i;

        octaspire_map_put(hashMap, hash, &i, &i);
    }

    ASSERT_EQ(numElements, octaspire_map_get_number_of_elements(hashMap));

    iterator =
        octaspire_map_element_iterator_init(hashMap);

    ASSERT_EQ(hashMap, iterator.hashMap);

    size_t counter = 0;
    while (iterator.element)
    {
        ASSERT_EQ(hashMap, iterator.hashMap);
        ASSERT_EQ(counter, octaspire_map_element_get_hash(iterator.element));
        ASSERT_EQ(counter, *(size_t*)octaspire_map_element_get_key(iterator.element));
        ASSERT_EQ(counter, *(size_t*)octaspire_map_element_get_value(iterator.element));

        ++counter;
        octaspire_map_element_iterator_next(&iterator);
    }

    ASSERT_EQ(numElements, counter);

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_element_const_iterator_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    octaspire_map_element_const_iterator_t iterator =
        octaspire_map_element_const_iterator_init(hashMap);

    ASSERT_EQ(hashMap, iterator.hashMap);
    ASSERT_EQ(0,       iterator.element);

    for (size_t i = 0; i < 100; ++i)
    {
        ASSERT_FALSE(octaspire_map_element_const_iterator_next(&iterator));

        ASSERT_EQ(hashMap, iterator.hashMap);
        ASSERT_EQ(0,       iterator.element);
    }

    size_t const numElements = 128;

    for (size_t i = 0; i < numElements; ++i)
    {
        uint32_t hash = (uint32_t)i;

        octaspire_map_put(hashMap, hash, &i, &i);
    }

    ASSERT_EQ(numElements, octaspire_map_get_number_of_elements(hashMap));

    iterator =
        octaspire_map_element_const_iterator_init(hashMap);

    ASSERT_EQ(hashMap, iterator.hashMap);

    size_t counter = 0;
    while (iterator.element)
    {
        ASSERT_EQ(hashMap, iterator.hashMap);
        ASSERT_EQ(counter, octaspire_map_element_get_hash(iterator.element));
        ASSERT_EQ(counter, *(size_t const*)octaspire_map_element_get_key_const(iterator.element));
        ASSERT_EQ(counter, *(size_t const*)octaspire_map_element_get_value_const(iterator.element));

        ++counter;
        octaspire_map_element_const_iterator_next(&iterator);
    }

    ASSERT_EQ(numElements, counter);

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_get_at_index_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    size_t const numElements = 3;

    for (size_t i = 0; i < numElements; ++i)
    {
        uint32_t hash = (uint32_t)i;
        octaspire_map_put(hashMap, hash, &i, &i);
    }

    ASSERT_EQ(numElements, octaspire_map_get_number_of_elements(hashMap));

    // Test failures
    octaspire_map_element_t *element =
        octaspire_map_get_at_index(hashMap, 3);

    ASSERT_FALSE(element);

    element =
        octaspire_map_get_at_index(hashMap, -4);

    ASSERT_FALSE(element);

    // Test success with positive and negative indices
    element =
        octaspire_map_get_at_index(hashMap, 1);

    ASSERT(element);

    ASSERT_EQ(
        1,
        *(size_t const * const)octaspire_map_element_get_value(element));

    element =
        octaspire_map_get_at_index(hashMap, -2);

    ASSERT(element);

    ASSERT_EQ(
        1,
        *(size_t const * const)octaspire_map_element_get_value(element));

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

TEST octaspire_map_is_empty_test(void)
{
    octaspire_map_t *hashMap = octaspire_map_new(
        sizeof(size_t),
        false,
        sizeof(size_t),
        false,
        octaspire_map_new_test_key_compare_function_for_size_t_keys,
        octaspire_map_new_test_key_hash_function_for_size_t_keys,
        0,
        0,
        octaspireContainerHashMapTestAllocator);

    ASSERT(hashMap);

    ASSERT(octaspire_map_is_empty(hashMap));

    size_t const numElements = 3;

    for (size_t i = 0; i < numElements; ++i)
    {
        uint32_t hash = (uint32_t)i;
        octaspire_map_put(hashMap, hash, &i, &i);
        ASSERT_FALSE(octaspire_map_is_empty(hashMap));
    }

    octaspire_map_release(hashMap);
    hashMap = 0;

    PASS();
}

GREATEST_SUITE(octaspire_map_suite)
{
    octaspireContainerHashMapTestAllocator = octaspire_allocator_new(0);

    assert(octaspireContainerHashMapTestAllocator);

    RUN_TEST(octaspire_map_element_new_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_map_element_new_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_map_element_new_allocation_failure_on_third_allocation_test);
    RUN_TEST(octaspire_map_private_rehash_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_map_new_keys_uint32_t_and_values_size_t_test);
    RUN_TEST(octaspire_map_add_same_key_many_times_test);
    RUN_TEST(octaspire_map_new_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_map_new_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_map_new_keys_ostring_t_and_values_ostring_t_test);
    RUN_TEST(octaspire_map_new_with_octaspire_string_keys_test);
    RUN_TEST(octaspire_map_new_with_size_t_keys_test);
    RUN_TEST(octaspire_map_element_iterator_test);
    RUN_TEST(octaspire_map_element_const_iterator_test);

    RUN_TEST(octaspire_map_get_at_index_test);
    RUN_TEST(octaspire_map_is_empty_test);

    octaspire_allocator_release(octaspireContainerHashMapTestAllocator);
    octaspireContainerHashMapTestAllocator = 0;
}

