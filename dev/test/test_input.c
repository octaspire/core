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
#include "../src/octaspire_input.c"
#include "external/greatest.h"
#include "octaspire/core/octaspire_input.h"
#include "octaspire/core/octaspire_core_config.h"

static octaspire_allocator_t *octaspireInputTestAllocator = 0;
static octaspire_stdio_t     *octaspireInputTestStdio = 0;

TEST octaspire_input_new_from_c_string_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    ASSERT(input->text);

    size_t const numUcsChars =
        octaspire_string_get_length_in_ucs_characters(input->text);

    ASSERT_EQ(6, numUcsChars);

    ASSERT_EQ(0x61,    octaspire_string_get_ucs_character_at_index(input->text, 0));
    ASSERT_EQ(0x62,    octaspire_string_get_ucs_character_at_index(input->text, 1));
    ASSERT_EQ(0x63,    octaspire_string_get_ucs_character_at_index(input->text, 2));
    ASSERT_EQ(0xa9,    octaspire_string_get_ucs_character_at_index(input->text, 3));
    ASSERT_EQ(0x2260,  octaspire_string_get_ucs_character_at_index(input->text, 4));
    ASSERT_EQ(0x10000, octaspire_string_get_ucs_character_at_index(input->text, 5));

    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);

    ASSERT_EQ(6, octaspire_input_get_length_in_ucs_characters(input));

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_c_string_called_with_null_string_test(void)
{
    octaspire_input_t *input = octaspire_input_new_from_c_string(0, octaspireInputTestAllocator);

    ASSERT(input);

    ASSERT(input->text);

    ASSERT_EQ(0,         octaspire_string_get_length_in_ucs_characters(input->text));
    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);

    ASSERT_EQ(0, octaspire_input_get_length_in_ucs_characters(input));

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_c_string_with_allocation_failure_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireInputTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    ASSERT_FALSE(input);

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_buffer_test(void)
{
    char const buffer[] =
    {
        'a',
        'b',
        'c',
        '\xC2',
        '\xA9',
        '\xE2',
        '\x89',
        '\xA0',
        '\xF0',
        '\x90',
        '\x80',
        '\x80'
    };

    octaspire_input_t *input = octaspire_input_new_from_buffer(
        buffer, sizeof(buffer) / sizeof(buffer[0]),
        octaspireInputTestAllocator);

    ASSERT(input);

    ASSERT(input->text);

    size_t const numUcsChars =
        octaspire_string_get_length_in_ucs_characters(input->text);

    ASSERT_EQ(6, numUcsChars);

    ASSERT_EQ(0x61,    octaspire_string_get_ucs_character_at_index(input->text, 0));
    ASSERT_EQ(0x62,    octaspire_string_get_ucs_character_at_index(input->text, 1));
    ASSERT_EQ(0x63,    octaspire_string_get_ucs_character_at_index(input->text, 2));
    ASSERT_EQ(0xa9,    octaspire_string_get_ucs_character_at_index(input->text, 3));
    ASSERT_EQ(0x2260,  octaspire_string_get_ucs_character_at_index(input->text, 4));
    ASSERT_EQ(0x10000, octaspire_string_get_ucs_character_at_index(input->text, 5));

    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);

    ASSERT_EQ(6, octaspire_input_get_length_in_ucs_characters(input));

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_buffer_with_allocation_failure_0x00_test(void)
{
    char const buffer[] =
    {
        'a',
        'b',
        'c',
        '\xC2',
        '\xA9',
        '\xE2',
        '\x89',
        '\xA0',
        '\xF0',
        '\x90',
        '\x80',
        '\x80'
    };

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireInputTestAllocator,
        1,
        0x00);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    octaspire_input_t *input = octaspire_input_new_from_buffer(
        buffer, sizeof(buffer) / sizeof(buffer[0]),
        octaspireInputTestAllocator);

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    ASSERT_FALSE(input);

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_buffer_with_allocation_failure_0x01_test(void)
{
    char const buffer[] =
    {
        'a',
        'b',
        'c',
        '\xC2',
        '\xA9',
        '\xE2',
        '\x89',
        '\xA0',
        '\xF0',
        '\x90',
        '\x80',
        '\x80'
    };

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireInputTestAllocator,
        2,
        0x01);

    ASSERT_EQ(
        2,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    octaspire_input_t *input = octaspire_input_new_from_buffer(
        buffer, sizeof(buffer) / sizeof(buffer[0]),
        octaspireInputTestAllocator);

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    ASSERT_FALSE(input);

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_path_test(void)
{
    octaspire_input_t *input = octaspire_input_new_from_path(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_input_new_from_path_test",
        octaspireInputTestAllocator,
        octaspireInputTestStdio);

    ASSERT(input);

    ASSERT(input->text);

    size_t const numUcsChars =
        octaspire_string_get_length_in_ucs_characters(input->text);

    ASSERT_EQ(6, numUcsChars);

    ASSERT_EQ(0x61,    octaspire_string_get_ucs_character_at_index(input->text, 0));
    ASSERT_EQ(0x62,    octaspire_string_get_ucs_character_at_index(input->text, 1));
    ASSERT_EQ(0x63,    octaspire_string_get_ucs_character_at_index(input->text, 2));
    ASSERT_EQ(0xa9,    octaspire_string_get_ucs_character_at_index(input->text, 3));
    ASSERT_EQ(0x2260,  octaspire_string_get_ucs_character_at_index(input->text, 4));
    ASSERT_EQ(0x10000, octaspire_string_get_ucs_character_at_index(input->text, 5));

    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);

    ASSERT_EQ(6, octaspire_input_get_length_in_ucs_characters(input));

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_path_failure_on_nonexisting_file_test(void)
{
    octaspire_input_t *input = octaspire_input_new_from_path(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_input_new_from_path_failure_on_nonexisting_file_test",
        octaspireInputTestAllocator,
        octaspireInputTestStdio);

    ASSERT_FALSE(input);

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_new_from_path_allocation_failure_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireInputTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    octaspire_input_t *input = octaspire_input_new_from_path(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_input_new_from_path_test",
        octaspireInputTestAllocator,
        octaspireInputTestStdio);

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireInputTestAllocator));

    ASSERT_FALSE(input);

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_get_length_in_ucs_characters_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    ASSERT_EQ(6, octaspire_input_get_length_in_ucs_characters(input));

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_clear_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    ASSERT(input->text);

    size_t const numUcsChars =
        octaspire_string_get_length_in_ucs_characters(input->text);

    ASSERT_EQ(6, numUcsChars);

    ASSERT_EQ(0x61,    octaspire_string_get_ucs_character_at_index(input->text, 0));
    ASSERT_EQ(0x62,    octaspire_string_get_ucs_character_at_index(input->text, 1));
    ASSERT_EQ(0x63,    octaspire_string_get_ucs_character_at_index(input->text, 2));
    ASSERT_EQ(0xa9,    octaspire_string_get_ucs_character_at_index(input->text, 3));
    ASSERT_EQ(0x2260,  octaspire_string_get_ucs_character_at_index(input->text, 4));
    ASSERT_EQ(0x10000, octaspire_string_get_ucs_character_at_index(input->text, 5));

    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);

    ASSERT_EQ(6, octaspire_input_get_length_in_ucs_characters(input));

    octaspire_input_clear(input);

    ASSERT(input->text);

    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(input->text));

    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);

    ASSERT_EQ(0, octaspire_input_get_length_in_ucs_characters(input));

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_rewind_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);

    ASSERT_EQ(6, octaspire_input_get_length_in_ucs_characters(input));

    while (octaspire_input_is_good(input))
    {
        ASSERT(octaspire_input_pop_next_ucs_character(input));
    }

    ASSERT_FALSE(octaspire_input_is_good(input));

    octaspire_input_rewind(input);
    ASSERT_EQ(0,         input->index);
    ASSERT_EQ(1,         input->line);
    ASSERT_EQ(1,         input->column);
    ASSERT_EQ(octaspireInputTestAllocator, input->allocator);
    ASSERT(octaspire_input_is_good(input));

    uint32_t expected[] = {0x61, 0x62, 0x63, 0xa9, 0x2260, 0x10000};

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT(octaspire_input_is_good(input));
        ASSERT_EQ(expected[i], octaspire_input_peek_next_ucs_character(input));
        ASSERT(octaspire_input_pop_next_ucs_character(input));
    }

    ASSERT_FALSE(octaspire_input_is_good(input));

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_peek_next_ucs_character_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    uint32_t expected[] = {0x61, 0x62, 0x63, 0xa9, 0x2260, 0x10000};

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT(octaspire_input_is_good(input));
        ASSERT_EQ(expected[i], octaspire_input_peek_next_ucs_character(input));
        ASSERT(octaspire_input_pop_next_ucs_character(input));
    }

    ASSERT_FALSE(octaspire_input_is_good(input));

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_FALSE(octaspire_input_is_good(input));
        ASSERT_EQ(0, octaspire_input_peek_next_ucs_character(input));
    }

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_pop_next_ucs_character_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    uint32_t expected[] = {0x61, 0x62, 0x63, 0xa9, 0x2260, 0x10000};

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT(octaspire_input_is_good(input));
        ASSERT_EQ(expected[i], octaspire_input_peek_next_ucs_character(input));
        ASSERT(octaspire_input_pop_next_ucs_character(input));
    }

    ASSERT_FALSE(octaspire_input_is_good(input));

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_FALSE(octaspire_input_is_good(input));
        ASSERT_EQ(0, octaspire_input_peek_next_ucs_character(input));
        ASSERT_FALSE(octaspire_input_pop_next_ucs_character(input));
    }

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_pop_next_ucs_character_current_line_and_column_are_calculated_correctly_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80\ndef\nghi";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    size_t expected_line[]   = {1, 1, 1, 1, 1, 1, 1,      2, 2, 2, 2,    3, 3, 3};
    size_t expected_column[] = {1, 2, 3, 4, 5, 6, 7,      1, 2, 3, 4,    1, 2, 3};

    ASSERT_EQ(
        sizeof(expected_line) / sizeof(expected_line[0]),
        octaspire_input_get_length_in_ucs_characters(input));

    ASSERT_EQ(
        sizeof(expected_column) / sizeof(expected_column[0]),
        octaspire_input_get_length_in_ucs_characters(input));

    for (size_t i = 0; i < octaspire_input_get_length_in_ucs_characters(input); ++i)
    {
        ASSERT(octaspire_input_is_good(input));

        ASSERT_EQ(expected_line[i],   input->line);
        ASSERT_EQ(expected_column[i], input->column);

        ASSERT(octaspire_input_pop_next_ucs_character(input));
    }

    ASSERT_FALSE(octaspire_input_is_good(input));

    size_t const lastIndex = octaspire_input_get_length_in_ucs_characters(input) - 1;

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQ(expected_column[lastIndex], input->column);
        ASSERT_FALSE(octaspire_input_is_good(input));
        ASSERT_EQ(expected_line[lastIndex],   input->line);
        ASSERT_EQ(expected_column[lastIndex], input->column);
        ASSERT_FALSE(octaspire_input_pop_next_ucs_character(input));
    }

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_is_good_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT(octaspire_input_is_good(input));
        ASSERT(octaspire_input_pop_next_ucs_character(input));
    }

    ASSERT_FALSE(octaspire_input_is_good(input));

    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_FALSE(octaspire_input_is_good(input));
        ASSERT_FALSE(octaspire_input_pop_next_ucs_character(input));
    }

    octaspire_input_release(input);
    input = 0;

    PASS();
}

TEST octaspire_input_private_is_ucs_character_index_valid_test(void)
{
    char const * const cstr = "abc\xC2\xA9\xE2\x89\xA0\xF0\x90\x80\x80";

    octaspire_input_t *input = octaspire_input_new_from_c_string(cstr, octaspireInputTestAllocator);

    ASSERT(input);

    for (size_t i = 0; i < 1024; ++i)
    {
        bool const valid = octaspire_input_private_is_ucs_character_index_valid(input, i);
        if (i < octaspire_input_get_length_in_ucs_characters(input))
        {
            ASSERT(valid);
        }
        else
        {
            ASSERT_FALSE(valid);
        }
    }

    octaspire_input_release(input);
    input = 0;

    PASS();
}

GREATEST_SUITE(octaspire_input_suite)
{
    octaspireInputTestAllocator = octaspire_allocator_new(0);
    octaspireInputTestStdio     = octaspire_stdio_new(octaspireInputTestAllocator);

    assert(octaspireInputTestAllocator);
    assert(octaspireInputTestStdio);

    RUN_TEST(octaspire_input_new_from_c_string_test);
    RUN_TEST(octaspire_input_new_from_c_string_called_with_null_string_test);
    RUN_TEST(octaspire_input_new_from_c_string_with_allocation_failure_test);
    RUN_TEST(octaspire_input_new_from_buffer_test);
    RUN_TEST(octaspire_input_new_from_buffer_with_allocation_failure_0x00_test);
    RUN_TEST(octaspire_input_new_from_buffer_with_allocation_failure_0x01_test);
    RUN_TEST(octaspire_input_new_from_path_test);
    RUN_TEST(octaspire_input_new_from_path_failure_on_nonexisting_file_test);
    RUN_TEST(octaspire_input_new_from_path_allocation_failure_test);
    RUN_TEST(octaspire_input_get_length_in_ucs_characters_test);
    RUN_TEST(octaspire_input_clear_test);
    RUN_TEST(octaspire_input_rewind_test);
    RUN_TEST(octaspire_input_peek_next_ucs_character_test);
    RUN_TEST(octaspire_input_pop_next_ucs_character_test);
    RUN_TEST(octaspire_input_pop_next_ucs_character_current_line_and_column_are_calculated_correctly_test);
    RUN_TEST(octaspire_input_is_good_test);
    RUN_TEST(octaspire_input_private_is_ucs_character_index_valid_test);

    octaspire_stdio_release(octaspireInputTestStdio);
    octaspireInputTestStdio = 0;

    octaspire_allocator_release(octaspireInputTestAllocator);
    octaspireInputTestAllocator = 0;
}

