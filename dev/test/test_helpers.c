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

static octaspire_allocator_t *octaspireHelpersTestAllocator = 0;
static octaspire_stdio_t     *octaspireHelpersTestStdio = 0;

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

    octaspire_allocator_free(octaspireHelpersTestAllocator, buffer);
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

    octaspire_allocator_free(octaspireHelpersTestAllocator, buffer);
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

    octaspire_allocator_free(octaspireHelpersTestAllocator, buffer);
    buffer = 0;

    PASS();
}

TEST octaspire_helpers_path_to_buffer_allocation_failure_test(void)
{
    size_t octetsAllocated = 0;

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireHelpersTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireHelpersTestAllocator));

    char * buffer = octaspire_helpers_path_to_buffer(
        OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_helpers_path_to_buffer_test",
        &octetsAllocated,
        octaspireHelpersTestAllocator,
        octaspireHelpersTestStdio);

    ASSERT_EQ(0, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireHelpersTestAllocator));

    ASSERT_FALSE(buffer);
    ASSERT_EQ(0, octetsAllocated);

    octaspire_allocator_free(octaspireHelpersTestAllocator, buffer);
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

    octaspire_allocator_free(octaspireHelpersTestAllocator, buffer);
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

TEST octaspire_helpers_base64_encode_qwerty1_line_len_0_test(void)
{
    char const * const input = "qwerty1";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        0,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ("cXdlcnR5MQ==", octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_qwerty1_line_len_10_test(void)
{
    char const * const input = "qwerty1";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        10,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ("cXdlcnR5MQ\n==", octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_qwerty1_test(void)
{
    char const * const input = "cXdlcnR5MQ==";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected = "qwerty1";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_qwerty1_with_embedded_whitespace_test(void)
{
    char const * const input = "\ncX\nd l\ncnR5\nM Q= \n= \n ";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected = "qwerty1";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_a_line_len_0_test(void)
{
    char const * const input = "a";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        0,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ("YQ==", octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_a_line_len_1_test(void)
{
    char const * const input = "a";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        1,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ("Y\nQ\n=\n=", octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_a_test(void)
{
    char const * const input = "YQ==";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected = "a";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_a_with_embedded_whitespace_test(void)
{
    char const * const input = " Y\t \t \t\t Q  = =  \t \n";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected = "a";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_empty_string_line_length_0_test(void)
{
    char const * const input = "";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        0,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ("", octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_empty_string_line_length_20_test(void)
{
    char const * const input = "";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        20,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ("", octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_empty_string_test(void)
{
    char const * const input = "";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT_EQ(0, decoded);

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_empty_string_with_whitespace_test(void)
{
    char const * const input = " \t \n ";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT_EQ(0, decoded);

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_base64_characters_line_length_0_test(void)
{
    char const * const input =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        0,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ(
        "QUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVphYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5e"
        "jAxMjM0NTY3ODkrLw==",
        octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_base64_characters_line_length_64_test(void)
{
    char const * const input =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        64,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ(
        "QUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVphYmNkZWZnaGlqa2xtbm9wcXJzdHV2\nd3h5e"
        "jAxMjM0NTY3ODkrLw==",
        octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_base64_characters_test(void)
{
    char const * const input =
        "QUJDREVGR0hJSktMTU5PUFFSU1RVVldYWVphYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5e"
        "jAxMjM0NTY3ODkrLw==";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_base64_characters_with_whitespace_test(void)
{
    char const * const input =
        " QU JD   RE\tVGR0hJ\nSktMTU5PUFFSU\n1RVVl  dYW VphYmNkZWZna\tGlqa2xtbm9wcXJzdHV2d 3h5e"
        "jAx M j M 0NTY\t\t\n 3ODkr Lw= =";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_printable_ascii_characters_line_len_0_test(void)
{
    char const * const input =
        " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abc"
        "defghijklmnopqrstuvwxyz{|}~";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        0,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ(
        "ICEiIyQlJicoKSorLC0uLzAxMjM0NTY3ODk6Ozw9Pj9AQUJDREVGR0hJSktMTU5PUFFSU1R"
        "VVldYWVpbXF1eX2BhYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5ent8fX4=",
        octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_printable_ascii_characters_line_len_10_test(void)
{
    char const * const input =
        " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abc"
        "defghijklmnopqrstuvwxyz{|}~";

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        input,
        strlen(input),
        10,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    ASSERT_STR_EQ(
        "ICEiIyQlJi\ncoKSorLC0u\nLzAxMjM0NT\nY3ODk6Ozw9\nPj9AQUJDRE\nVGR0hJSktM\nTU5PUFFSU1\nR"
        "VVldYWVpb\nXF1eX2BhYm\nNkZWZnaGlq\na2xtbm9wcX\nJzdHV2d3h5\nent8fX4=",
        octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_printable_ascii_characters_test(void)
{
    char const * const input =
        "ICEiIyQlJicoKSorLC0uLzAxMjM0NTY3ODk6Ozw9Pj9AQUJDREVGR0hJSktMTU5PUFFSU1R"
        "VVldYWVpbXF1eX2BhYmNkZWZnaGlqa2xtbm9wcXJzdHV2d3h5ent8fX4=";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected =
        " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abc"
        "defghijklmnopqrstuvwxyz{|}~";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_decode_encoded_printable_ascii_characters_with_whitespace_test(void)
{
    char const * const input =
        " I C EiI yQ  lJ  icoK\tSorLC0uLzAx\n\nMjM0NTY3O Dk6Ozw9Pj9AQUJDREVGR0hJSktMTU5PUFFSU1R"
        " V V l  d  Y  W    Vpb\nXF1eX\n\t 2B hYmN k  ZWZnaGlqa2xtbm9wcXJzdHV2d3 h 5ent8fX4=  ";

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        input,
        (int32_t)strlen(input),
        octaspireHelpersTestAllocator);

    ASSERT(decoded);

    char const * const expected =
        " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abc"
        "defghijklmnopqrstuvwxyz{|}~";

    ASSERT_EQ(strlen(expected), octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(
            expected[i],
            *(char const * const)octaspire_vector_get_element_at_const(
                decoded,
                (ptrdiff_t)i));
    }

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_all_octets_one_by_one_line_len_0_test(void)
{
    unsigned char input[0xFF + 1];

    for (size_t i = 0; i <= 0xFF; ++i)
        input[i] = (unsigned char)i;

    char const * const expected[] =
    {
        "AA==","AQ==","Ag==","Aw==","BA==","BQ==","Bg==","Bw==","CA==","CQ==",
        "Cg==","Cw==","DA==","DQ==","Dg==","Dw==","EA==","EQ==","Eg==","Ew==",
        "FA==","FQ==","Fg==","Fw==","GA==","GQ==","Gg==","Gw==","HA==","HQ==",
        "Hg==","Hw==","IA==","IQ==","Ig==","Iw==","JA==","JQ==","Jg==","Jw==",
        "KA==","KQ==","Kg==","Kw==","LA==","LQ==","Lg==","Lw==","MA==","MQ==",
        "Mg==","Mw==","NA==","NQ==","Ng==","Nw==","OA==","OQ==","Og==","Ow==",
        "PA==","PQ==","Pg==","Pw==","QA==","QQ==","Qg==","Qw==","RA==","RQ==",
        "Rg==","Rw==","SA==","SQ==","Sg==","Sw==","TA==","TQ==","Tg==","Tw==",
        "UA==","UQ==","Ug==","Uw==","VA==","VQ==","Vg==","Vw==","WA==","WQ==",
        "Wg==","Ww==","XA==","XQ==","Xg==","Xw==","YA==","YQ==","Yg==","Yw==",
        "ZA==","ZQ==","Zg==","Zw==","aA==","aQ==","ag==","aw==","bA==","bQ==",
        "bg==","bw==","cA==","cQ==","cg==","cw==","dA==","dQ==","dg==","dw==",
        "eA==","eQ==","eg==","ew==","fA==","fQ==","fg==","fw==","gA==","gQ==",
        "gg==","gw==","hA==","hQ==","hg==","hw==","iA==","iQ==","ig==","iw==",
        "jA==","jQ==","jg==","jw==","kA==","kQ==","kg==","kw==","lA==","lQ==",
        "lg==","lw==","mA==","mQ==","mg==","mw==","nA==","nQ==","ng==","nw==",
        "oA==","oQ==","og==","ow==","pA==","pQ==","pg==","pw==","qA==","qQ==",
        "qg==","qw==","rA==","rQ==","rg==","rw==","sA==","sQ==","sg==","sw==",
        "tA==","tQ==","tg==","tw==","uA==","uQ==","ug==","uw==","vA==","vQ==",
        "vg==","vw==","wA==","wQ==","wg==","ww==","xA==","xQ==","xg==","xw==",
        "yA==","yQ==","yg==","yw==","zA==","zQ==","zg==","zw==","0A==","0Q==",
        "0g==","0w==","1A==","1Q==","1g==","1w==","2A==","2Q==","2g==","2w==",
        "3A==","3Q==","3g==","3w==","4A==","4Q==","4g==","4w==","5A==","5Q==",
        "5g==","5w==","6A==","6Q==","6g==","6w==","7A==","7Q==","7g==","7w==",
        "8A==","8Q==","8g==","8w==","9A==","9Q==","9g==","9w==","+A==","+Q==",
        "+g==","+w==","/A==","/Q==","/g==","/w==",
    };

    size_t const inputLen = sizeof(input) / sizeof(input[0]);
    ASSERT_EQ(inputLen, sizeof(expected) / sizeof(expected[0]));

    for (size_t i = 0; i < inputLen; ++i)
    {
        octaspire_string_t * encoded = octaspire_helpers_base64_encode(
            (char const * const)(input + i),
            1,
            0,
            octaspireHelpersTestAllocator);

        ASSERT(encoded);

        ASSERT_STR_EQ(
            expected[i],
            octaspire_string_get_c_string(encoded));

        octaspire_string_release(encoded);
        encoded = 0;
    }

    PASS();
}

TEST octaspire_helpers_base64_encode_all_octets_line_len_0_test(void)
{
    unsigned char input[0xFF + 1];

    for (size_t i = 0; i <= 0xFF; ++i)
        input[i] = (unsigned char)i;

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        (char const * const)input,
        sizeof(input) / sizeof(input[0]),
        0,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    char const * const expected =
        "AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4vMDEyM"
        "zQ1Njc4OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5fYGFiY2RlZm"
        "doaWprbG1ub3BxcnN0dXZ3eHl6e3x9fn+AgYKDhIWGh4iJiouMjY6PkJGSk5SVlpeYmZq"
        "bnJ2en6ChoqOkpaanqKmqq6ytrq+wsbKztLW2t7i5uru8vb6/wMHCw8TFxsfIycrLzM3O"
        "z9DR0tPU1dbX2Nna29zd3t/g4eLj5OXm5+jp6uvs7e7v8PHy8/T19vf4+fr7/P3+/w==";

    ASSERT_EQ(strlen(expected), octaspire_string_get_length_in_octets(encoded));

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_all_octets_line_len_69_test(void)
{
    unsigned char input[0xFF + 1];

    for (size_t i = 0; i <= 0xFF; ++i)
        input[i] = (unsigned char)i;

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        (char const * const)input,
        sizeof(input) / sizeof(input[0]),
        69,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    char const * const expected =
        "AAECAwQFBgcICQoLDA0ODxAREhMUFRYXGBkaGxwdHh8gISIjJCUmJygpKissLS4vMDEyM\n"
        "zQ1Njc4OTo7PD0+P0BBQkNERUZHSElKS0xNTk9QUVJTVFVWV1hZWltcXV5fYGFiY2RlZm\n"
        "doaWprbG1ub3BxcnN0dXZ3eHl6e3x9fn+AgYKDhIWGh4iJiouMjY6PkJGSk5SVlpeYmZq\n"
        "bnJ2en6ChoqOkpaanqKmqq6ytrq+wsbKztLW2t7i5uru8vb6/wMHCw8TFxsfIycrLzM3O\n"
        "z9DR0tPU1dbX2Nna29zd3t/g4eLj5OXm5+jp6uvs7e7v8PHy8/T19vf4+fr7/P3+/w==";

    ASSERT_EQ(strlen(expected), octaspire_string_get_length_in_octets(encoded));

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(encoded));

    octaspire_string_release(encoded);
    encoded = 0;

    PASS();
}

TEST octaspire_helpers_base64_encode_and_then_decode_all_octets_line_len_69_test(void)
{
    unsigned char input[0xFF + 1];

    for (size_t i = 0; i <= 0xFF; ++i)
        input[i] = (unsigned char)i;

    octaspire_string_t * encoded = octaspire_helpers_base64_encode(
        (char const * const)input,
        sizeof(input) / sizeof(input[0]),
        69,
        octaspireHelpersTestAllocator);

    ASSERT(encoded);

    octaspire_vector_t * decoded = octaspire_helpers_base64_decode(
        octaspire_string_get_c_string(encoded),
        (int32_t)octaspire_string_get_length_in_octets(encoded),
        octaspireHelpersTestAllocator);

    ASSERT_EQ(0xFF + 1, octaspire_vector_get_length(decoded));

    for (size_t i = 0; i < octaspire_vector_get_length(decoded); ++i)
    {
        ASSERT_EQ(
            input[i],
            *(unsigned char const * const)
                octaspire_vector_get_element_at_const(decoded, (ptrdiff_t)i));
    }

    octaspire_string_release(encoded);
    encoded = 0;

    octaspire_vector_release(decoded);
    decoded = 0;

    PASS();
}

GREATEST_SUITE(octaspire_helpers_suite)
{
    octaspireHelpersTestAllocator = octaspire_allocator_new(0);
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

    RUN_TEST(octaspire_helpers_base64_encode_qwerty1_line_len_0_test);
    RUN_TEST(octaspire_helpers_base64_encode_qwerty1_line_len_10_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_qwerty1_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_qwerty1_with_embedded_whitespace_test);
    RUN_TEST(octaspire_helpers_base64_encode_a_line_len_0_test);
    RUN_TEST(octaspire_helpers_base64_encode_a_line_len_1_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_a_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_a_with_embedded_whitespace_test);
    RUN_TEST(octaspire_helpers_base64_encode_empty_string_line_length_0_test);
    RUN_TEST(octaspire_helpers_base64_encode_empty_string_line_length_20_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_empty_string_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_empty_string_with_whitespace_test);
    RUN_TEST(octaspire_helpers_base64_encode_base64_characters_line_length_0_test);
    RUN_TEST(octaspire_helpers_base64_encode_base64_characters_line_length_64_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_base64_characters_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_base64_characters_with_whitespace_test);
    RUN_TEST(octaspire_helpers_base64_encode_printable_ascii_characters_line_len_0_test);
    RUN_TEST(octaspire_helpers_base64_encode_printable_ascii_characters_line_len_10_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_printable_ascii_characters_test);
    RUN_TEST(octaspire_helpers_base64_decode_encoded_printable_ascii_characters_with_whitespace_test);
    RUN_TEST(octaspire_helpers_base64_encode_all_octets_one_by_one_line_len_0_test);
    RUN_TEST(octaspire_helpers_base64_encode_all_octets_line_len_0_test);
    RUN_TEST(octaspire_helpers_base64_encode_all_octets_line_len_69_test);
    RUN_TEST(octaspire_helpers_base64_encode_and_then_decode_all_octets_line_len_69_test);

    octaspire_stdio_release(octaspireHelpersTestStdio);
    octaspireHelpersTestStdio = 0;

    octaspire_allocator_release(octaspireHelpersTestAllocator);
    octaspireHelpersTestAllocator = 0;
}

