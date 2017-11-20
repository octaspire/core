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

TEST octaspire_helpers_is_even_size_t_test(void)
{
    ASSERT(octaspire_helpers_is_even_size_t(0));

    for (size_t i = 2; i < 1024; i += 2)
    {
        ASSERT(octaspire_helpers_is_even_size_t(i));
    }

    ASSERT_FALSE(octaspire_helpers_is_even_size_t(1));

    for (size_t i = 3; i < 1024; i += 2)
    {
        ASSERT_FALSE(octaspire_helpers_is_even_size_t(i));
    }

    PASS();
}

TEST octaspire_helpers_is_odd_size_t_test(void)
{
    ASSERT_FALSE(octaspire_helpers_is_odd_size_t(0));

    for (size_t i = 1; i < 1024; i += 2)
    {
        ASSERT(octaspire_helpers_is_odd_size_t(i));
    }

    ASSERT_FALSE(octaspire_helpers_is_odd_size_t(2));

    for (size_t i = 4; i < 1024; i += 2)
    {
        ASSERT_FALSE(octaspire_helpers_is_odd_size_t(i));
    }

    PASS();
}

TEST octaspire_helpers_calculate_hash_for_memory_buffer_argument_test(void)
{
    char const buffer[] = {'a', 'b', 'c'};

    ASSERT_EQ(
        3977453403,
        octaspire_helpers_calculate_hash_for_memory_buffer_argument(
            buffer,
            sizeof(buffer)));

    char const * const buffer2 = "123456789=?qwertyuiop#_.:,!++?";

    ASSERT_EQ(
        3026418028,
        octaspire_helpers_calculate_hash_for_memory_buffer_argument(
            buffer2,
            strlen(buffer2)));

    PASS();
}

TEST octaspire_helpers_base64_encode_qwerty1_test(void)
{
    char const * const input = "qwerty1";

    octaspire_container_utf8_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ("cXdlcnR5MQ==", octaspire_container_utf8_string_get_c_string(encoded));

    octaspire_container_utf8_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_qwerty1_test(void)
{
    char const * const input = "cXdlcnR5MQ==";

    octaspire_container_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected = "qwerty1";

    ASSERT_EQ(strlen(expected), octaspire_container_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_container_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_container_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_qwerty1_with_embedded_whitespace_test(void)
{
    char const * const input = "\ncX\nd l\ncnR5\nM Q= \n= \n ";

    octaspire_container_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected = "qwerty1";

    ASSERT_EQ(strlen(expected), octaspire_container_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_container_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_container_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_a_test(void)
{
    char const * const input = "a";

    octaspire_container_utf8_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ("YQ==", octaspire_container_utf8_string_get_c_string(encoded));

    octaspire_container_utf8_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_a_test(void)
{
    char const * const input = "YQ==";

    octaspire_container_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected = "a";

    ASSERT_EQ(strlen(expected), octaspire_container_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_container_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_container_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_a_with_embedded_whitespace_test(void)
{
    char const * const input = " Y\t \t \t\t Q  = =  \t \n";

    octaspire_container_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected = "a";

    ASSERT_EQ(strlen(expected), octaspire_container_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_container_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_container_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_empty_string_test(void)
{
    char const * const input = "";

    octaspire_container_utf8_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ("", octaspire_container_utf8_string_get_c_string(encoded));

    octaspire_container_utf8_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_empty_string_test(void)
{
    char const * const input = "";

    octaspire_container_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT_EQ(0, decoded);

    octaspire_container_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_empty_string_with_whitespace_test(void)
{
    char const * const input = " \t \n ";

    octaspire_container_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT_EQ(0, decoded);

    octaspire_container_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_base64_characters_test(void)
{
    char const * const input =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    octaspire_container_utf8_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ(
        "QUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVphYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5e"
        "jAxMjM0NTY3ODkrLw==",
        octaspire_container_utf8_string_get_c_string(encoded));

    octaspire_container_utf8_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_base64_characters_test(void)
{
    char const * const input =
        "QUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVphYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5e"
        "jAxMjM0NTY3ODkrLw==";

    octaspire_container_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    ASSERT_EQ(strlen(expected), octaspire_container_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_container_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_container_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_base64_characters_with_whitespace_test(void)
{
    char const * const input =
        " QU JD   RE\tVGR0hJ\nSktMTU5PUFFSU\n1RVVl  dYW VphYmNkZWZna\tGlqa2xtbm9wcXJzdHV2d 3h5e"
        "jAx M j M 0NTY\t\t\n 3ODkr Lw= =";

    octaspire_container_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    ASSERT_EQ(strlen(expected), octaspire_container_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_container_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_container_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_printable_ascii_characters_test(void)
{
    char const * const input =
        " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abc"
        "defghijklmnopqrstuvwxyz{|}~";

    octaspire_container_utf8_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ(
        "ICEiIyQlJicoKSorLC0uLzAxMjM0NTY3ODk6Ozw9Pj9AQUJDREVGR0hJSktMTU5PUFFSU1R"
        "VVldYWVpbXF1eX2BhYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5ent8fX4=",
        octaspire_container_utf8_string_get_c_string(encoded));

    octaspire_container_utf8_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_printable_ascii_characters_test(void)
{
    char const * const input =
        "ICEiIyQlJicoKSorLC0uLzAxMjM0NTY3ODk6Ozw9Pj9AQUJDREVGR0hJSktMTU5PUFFSU1R"
        "VVldYWVpbXF1eX2BhYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5ent8fX4=";

    octaspire_container_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected =
        " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abc"
        "defghijklmnopqrstuvwxyz{|}~";

    ASSERT_EQ(strlen(expected), octaspire_container_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_container_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_container_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_printable_ascii_characters_with_whitespace_test(void)
{
    char const * const input =
        " I C EiI yQ  lJ  icoK\tSorLC0uLzAx\n\nMjM0NTY3O Dk6Ozw9Pj9AQUJDREVGR0hJSktMTU5PUFFSU1R"
        " V V l  d  Y  W    Vpb\nXF1eX\n\t 2B hYmN k  ZWZnaGlqa2xtbm9wcXJzdHV2d3 h 5ent8fX4=  ";

    octaspire_container_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected =
        " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abc"
        "defghijklmnopqrstuvwxyz{|}~";

    ASSERT_EQ(strlen(expected), octaspire_container_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_container_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_container_vector_release(decoded);
    decoded = 0;

    PASS();
}

GREATEST_SUITE(octaspire_helpers_suite)
{
    octaspireHelpersTestAllocator = octaspire_memory_allocator_new(0);
    octaspireHelpersTestStdio     = octaspire_stdio_new(octaspireHelpersTestAllocator);

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

    RUN_TEST(octaspire_helpers_is_even_size_t_test);
    RUN_TEST(octaspire_helpers_is_odd_size_t_test);

    RUN_TEST(octaspire_helpers_calculate_hash_for_memory_buffer_argument_test);

    RUN_TEST(octaspire_helpers_base64_encode_qwerty1_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_qwerty1_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_qwerty1_with_embedded_whitespace_test);
    RUN_TEST(octaspire_helpers_base64_encode_a_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_a_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_a_with_embedded_whitespace_test);
    RUN_TEST(octaspire_helpers_base64_encode_empty_string_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_empty_string_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_empty_string_with_whitespace_test);
    RUN_TEST(octaspire_helpers_base64_encode_base64_characters_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_base64_characters_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_base64_characters_with_whitespace_test);
    RUN_TEST(octaspire_helpers_base64_encode_printable_ascii_characters_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_printable_ascii_characters_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_printable_ascii_characters_with_whitespace_test);

    octaspire_stdio_release(octaspireHelpersTestStdio);
    octaspireHelpersTestStdio = 0;

    octaspire_memory_allocator_release(octaspireHelpersTestAllocator);
    octaspireHelpersTestAllocator = 0;
}

