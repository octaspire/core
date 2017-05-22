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
#include "../src/octaspire_helpers.c"
#include "external/greatest.h"
#include "octaspire/core/octaspire_stdio.h"
#include "octaspire/core/octaspire_core_config.h"

static octaspire_memory_allocator_t *octaspireHelpersTestAllocator = 0;
static octaspire_stdio_t            *octaspireHelpersTestStdio = 0;

TEST octaspire_helpers_test_bit_when_only_highest_order_bit_is_set_test(void)
{
    uint32_t const bitSet = 0x80000000;

    for (size_t i = 0; i < 31; ++i)
    {
        ASSERT_FALSE(octaspire_helpers_test_bit(bitSet, i));
    }

    ASSERT(octaspire_helpers_test_bit(bitSet, 31));

    PASS();
}

TEST octaspire_helpers_test_bit_when_only_lowest_order_bit_is_set_test(void)
{
    uint32_t const bitSet = 0x00000001;

    ASSERT(octaspire_helpers_test_bit(bitSet, 0));

    for (size_t i = 1; i < 32; ++i)
    {
        ASSERT_FALSE(octaspire_helpers_test_bit(bitSet, i));
    }

    PASS();
}

TEST octaspire_helpers_test_bit_when_all_bits_are_set_test(void)
{
    uint32_t const bitSet = 0xFFFFFFFF;

    for (size_t i = 0; i < 32; ++i)
    {
        ASSERT(octaspire_helpers_test_bit(bitSet, i));
    }

    PASS();
}

TEST octaspire_helpers_test_bit_when_no_bits_are_set_test(void)
{
    uint32_t const bitSet = 0x00000000;

    for (size_t i = 0; i < 32; ++i)
    {
        ASSERT_FALSE(octaspire_helpers_test_bit(bitSet, i));
    }

    PASS();
}

TEST octaspire_helpers_test_bit_when_every_bit_at_even_index_is_set_test(void)
{
    uint32_t const bitSet = 0x55555555;

    for (size_t i = 0; i < 32; ++i)
    {
        if (i % 2 == 0)
        {
            ASSERT(octaspire_helpers_test_bit(bitSet, i));
        }
        else
        {
            ASSERT_FALSE(octaspire_helpers_test_bit(bitSet, i));
        }
    }

    PASS();
}

TEST octaspire_helpers_test_bit_when_every_bit_at_odd_index_is_set_test(void)
{
    uint32_t const bitSet = 0xAAAAAAAA;

    for (size_t i = 0; i < 32; ++i)
    {
        if (i % 2 != 0)
        {
            ASSERT(octaspire_helpers_test_bit(bitSet, i));
        }
        else
        {
            ASSERT_FALSE(octaspire_helpers_test_bit(bitSet, i));
        }
    }

    PASS();
}

TEST octaspire_helpers_path_to_buffer_test(void)
{
    size_t octetsAllocated = 0;

    char * buffer = octaspire_helpers_path_to_buffer(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_helpers_path_to_buffer_test",
        &octetsAllocated,
        octaspireHelpersTestAllocator,
        octaspireHelpersTestStdio);

    ASSERT(buffer);
    ASSERT_EQ(2 + 3 + 4, octetsAllocated);

    // Copyright sign 0xa9               2 octet
    // Equal sign     0x2260             3 octets
    // Linear b syllable b008 a 0x10000  4 octets
    char const * const expected = "\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    ASSERT_EQ(octetsAllocated, strlen(expected));

    ASSERT_MEM_EQ(expected, buffer, octetsAllocated);

    octaspire_memory_allocator_free(octaspireHelpersTestAllocator, buffer);
    buffer = 0;

    PASS();
}

TEST octaspire_helpers_path_to_buffer_failure_on_nonexisting_file_test(void)
{
    size_t octetsAllocated = 0;

    char * buffer = octaspire_helpers_path_to_buffer(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_helpers_path_to_buffer_failure_on_nonexisting_file_test",
        &octetsAllocated,
        octaspireHelpersTestAllocator,
        octaspireHelpersTestStdio);

    ASSERT_FALSE(buffer);
    ASSERT_EQ(0, octetsAllocated);

    octaspire_memory_allocator_free(octaspireHelpersTestAllocator, buffer);
    buffer = 0;

    PASS();
}

TEST octaspire_helpers_path_to_buffer_failure_on_empty_file_test(void)
{
    size_t octetsAllocated = 0;

    char * buffer = octaspire_helpers_path_to_buffer(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_helpers_path_to_buffer_failure_on_empty_file_test",
        &octetsAllocated,
        octaspireHelpersTestAllocator,
        octaspireHelpersTestStdio);

    ASSERT_FALSE(buffer);
    ASSERT_EQ(0, octetsAllocated);

    octaspire_memory_allocator_free(octaspireHelpersTestAllocator, buffer);
    buffer = 0;

    PASS();
}

TEST octaspire_helpers_path_to_buffer_allocation_failure_test(void)
{
    size_t octetsAllocated = 0;

    octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireHelpersTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireHelpersTestAllocator));

    char * buffer = octaspire_helpers_path_to_buffer(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_helpers_path_to_buffer_test",
        &octetsAllocated,
        octaspireHelpersTestAllocator,
        octaspireHelpersTestStdio);

    ASSERT_EQ(0, octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(octaspireHelpersTestAllocator));

    ASSERT_FALSE(buffer);
    ASSERT_EQ(0, octetsAllocated);

    octaspire_memory_allocator_free(octaspireHelpersTestAllocator, buffer);
    buffer = 0;

    PASS();
}

TEST octaspire_helpers_path_to_buffer_read_failure_test(void)
{
    size_t octetsAllocated = 0;

    octaspire_stdio_set_number_and_type_of_future_reads_to_be_rigged(octaspireHelpersTestStdio, 1, 0);
    ASSERT_EQ(1, octaspire_stdio_get_number_of_future_reads_to_be_rigged(octaspireHelpersTestStdio));

    char * buffer = octaspire_helpers_path_to_buffer(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_helpers_path_to_buffer_test",
        &octetsAllocated,
        octaspireHelpersTestAllocator,
        octaspireHelpersTestStdio);

    ASSERT_EQ(0, octaspire_stdio_get_number_of_future_reads_to_be_rigged(octaspireHelpersTestStdio));

    ASSERT_FALSE(buffer);
    ASSERT_EQ(0, octetsAllocated);

    octaspire_memory_allocator_free(octaspireHelpersTestAllocator, buffer);
    buffer = 0;

    PASS();
}

static size_t octaspireHelpersSuiteNumTimesRun = 0;

GREATEST_SUITE(octaspire_helpers_suite)
{
    octaspireHelpersSuiteNumTimesRun = 0;

    octaspireHelpersTestAllocator       = octaspire_memory_allocator_new_create_region(
        OCTASPIRE_CORE_CONFIG_MEMORY_ALLOCATOR_REGION_MIN_BLOCK_SIZE_IN_OCTETS);

    octaspireHelpersTestStdio  = octaspire_stdio_new(octaspireHelpersTestAllocator);

second_run:

    assert(octaspireHelpersTestAllocator);
    assert(octaspireHelpersTestStdio);

    RUN_TEST(octaspire_helpers_test_bit_when_only_highest_order_bit_is_set_test);
    RUN_TEST(octaspire_helpers_test_bit_when_only_lowest_order_bit_is_set_test);
    RUN_TEST(octaspire_helpers_test_bit_when_all_bits_are_set_test);
    RUN_TEST(octaspire_helpers_test_bit_when_no_bits_are_set_test);
    RUN_TEST(octaspire_helpers_test_bit_when_every_bit_at_even_index_is_set_test);
    RUN_TEST(octaspire_helpers_test_bit_when_every_bit_at_odd_index_is_set_test);
    RUN_TEST(octaspire_helpers_path_to_buffer_test);
    RUN_TEST(octaspire_helpers_path_to_buffer_failure_on_nonexisting_file_test);
    RUN_TEST(octaspire_helpers_path_to_buffer_failure_on_empty_file_test);
    RUN_TEST(octaspire_helpers_path_to_buffer_allocation_failure_test);
    RUN_TEST(octaspire_helpers_path_to_buffer_read_failure_test);

    octaspire_stdio_release(octaspireHelpersTestStdio);
    octaspireHelpersTestStdio = 0;

    octaspire_memory_allocator_release(octaspireHelpersTestAllocator);
    octaspireHelpersTestAllocator = 0;

    ++octaspireHelpersSuiteNumTimesRun;

    if (octaspireHelpersSuiteNumTimesRun < 2)
    {
        // Second run without region allocator

        octaspireHelpersTestAllocator      = octaspire_memory_allocator_new(0);
        octaspireHelpersTestStdio = octaspire_stdio_new(octaspireHelpersTestAllocator);

        goto second_run;
    }
}

