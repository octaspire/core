/******************************************************************************
Octaspire Core - Containers and other utility libraries in standard C99
Copyright 2017 - 2019 www.octaspire.com

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
#include "../src/octaspire_string.c"
#include <wchar.h> // For WEOF
#include "external/greatest.h"
#include "octaspire/core/octaspire_string.h"
#include "octaspire/core/octaspire_core_config.h"

static octaspire_allocator_t *octaspireContainerUtf8StringTestAllocator = 0;

TEST octaspire_string_new_called_with_null_argument_test(void)
{
    octaspire_string_t *str =
        octaspire_string_new(0, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_with_simple_ascii_string_test(void)
{
    char const * const expected = "Hello World!";
    octaspire_string_t *str =
        octaspire_string_new(expected, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(strlen((char const * const)expected), octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(strlen((char const * const)expected), octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ(expected, octaspire_string_get_c_string(str));

    for (size_t i = 0; i < octaspire_string_get_length_in_ucs_characters(str); ++i)
    {
        ASSERT_EQ(
            (uint32_t)(expected[i]),
            octaspire_string_get_ucs_character_at_index(
                str,
                (ptrdiff_t)i));
    }

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_with_some_multioctet_ucs_characters_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_with_simple_ascii_string_with_error_test(void)
{
    char const * const input    = "Hello World\xC0\xB3";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_DECODING_ERROR, str->errorStatus);
    ASSERT_EQ(11,                                                          str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                                   str->allocator);

    ASSERT(octaspire_string_is_error(str));
    ASSERT_EQ(11, octaspire_string_get_error_position_in_octets(str));

    char const * const expected = "Hello World";

    ASSERT_EQ(strlen((char const * const)expected), octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(strlen((char const * const)expected), octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ(expected, octaspire_string_get_c_string(str));

    for (size_t i = 0;
         i < octaspire_string_get_length_in_ucs_characters(str);
         ++i)
    {
        ASSERT_EQ(
            (uint32_t)(expected[i]),
            octaspire_string_get_ucs_character_at_index(
                str,
                (ptrdiff_t)i));
    }

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_from_buffer_with_some_multioctet_ucs_characters_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    size_t const       lengthInOctets      = strlen(input);
    octaspire_string_t *str =
        octaspire_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_from_buffer_allocation_failure_on_first_allocation_test(void)
{
#ifdef _MSC_VER
    char const * const input = u8"©Hello World! © ≠𐀀How are you?";
#else
    char const * const input = "©Hello World! © ≠𐀀How are you?";
#endif

    size_t const       lengthInOctets      = strlen(input);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    octaspire_string_t *str =
        octaspire_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    ASSERT_FALSE(str);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_from_buffer_allocation_failure_on_second_allocation_test(void)
{
#ifdef _MSC_VER
    char const * const input = u8"©Hello World! © ≠𐀀How are you?";
#else
    char const * const input = "©Hello World! © ≠𐀀How are you?";
#endif

    size_t const       lengthInOctets      = strlen(input);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 2, 0x01);
    ASSERT_EQ(2, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    octaspire_string_t *str =
        octaspire_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    ASSERT_FALSE(str);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_from_buffer_allocation_failure_on_third_allocation_test(void)
{
#ifdef _MSC_VER
    char const * const input = u8"©Hello World! © ≠𐀀How are you?";
#else
    char const * const input = "©Hello World! © ≠𐀀How are you?";
#endif

    size_t const       lengthInOctets      = strlen(input);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 3, 0x03);
    ASSERT_EQ(3, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    octaspire_string_t *str =
        octaspire_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    ASSERT_FALSE(str);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_from_buffer_allocation_failure_on_sixth_2_allocation_test(void)
{
#ifdef _MSC_VER
    char const * const input = u8"©Hello World! © ≠𐀀How are you?";
#else
    char const * const input = "©Hello World! © ≠𐀀How are you?";
#endif

    size_t const       lengthInOctets      = strlen(input);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 6, 0x1F);
    ASSERT_EQ(6, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    octaspire_string_t *str =
        octaspire_string_new_from_buffer(input, lengthInOctets, octaspireContainerUtf8StringTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    ASSERT_FALSE(str);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_format_with_string_test(void)
{
    char const * const name  = "Mike";
    char const * const input = "Hello! My name is %s. What's yours?";
    octaspire_string_t *str =
        octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, input, name);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(37, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "Hello! My name is Mike. What's yours?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_format_with_size_t_test(void)
{
    size_t const value = 62039;

    char const * const input = "©Hello World! © ≠𐀀How are you? My age is %zu. What's yours?";

    octaspire_string_t *str =
        octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, input, value);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(68, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(61, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you? My age is 62039. What's yours?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_format_with_doubles_test(void)
{
    double const value1 = 12.001;
    double const value2 = 2015.12;
    double const value3 = 4.9;
    char const * const input = "The doubles are %g, %g and %g\n";
    octaspire_string_t *str =
        octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, input, value1, value2, value3);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(40, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(40, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = "The doubles are 12.001, 2015.12 and 4.9\n";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_format_with_string_and_size_t_test(void)
{
    size_t const value = 62039;

    char const * const name  = "©Hello";

    char const * const input =
        "©Hello World! © ≠𐀀How are you? My name is \"%s\" and my age is %zu. What's yours?";

    octaspire_string_t *str =
        octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, input, name, value);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(93, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(85, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you? My name is \"\xC2\xA9Hello\" and my age is 62039. What's yours?";

    ASSERT_MEM_EQ(
        expected,
        octaspire_string_get_c_string(str),
        octaspire_string_get_length_in_octets(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_format_with_string_and_size_t_on_otherwise_empty_format_string_test(void)
{
    size_t const value = 62039;
    char const * const name  = "Hello";
    char const * const input = "%s%zu";
    octaspire_string_t *str =
        octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, input, name, value);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(10, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(10, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "Hello62039";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_format_with_empty_format_string_test(void)
{
    char const * const input = "";
    octaspire_string_t *str =
        octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, input);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_copy_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_t *cpy =
        octaspire_string_new_copy(str, octaspireContainerUtf8StringTestAllocator);

    ASSERT_EQ(
        octaspire_string_get_length_in_octets(str),
        octaspire_string_get_length_in_octets(cpy));

    ASSERT_MEM_EQ(
        octaspire_vector_get_element_at_const(str->octets, 0),
        octaspire_vector_get_element_at_const(cpy->octets, 0),
        octaspire_string_get_length_in_octets(str));

    ASSERT_EQ(
        octaspire_vector_get_length_in_octets(str->ucsCharacters),
        octaspire_vector_get_length_in_octets(cpy->ucsCharacters));

    ASSERT_MEM_EQ(
        octaspire_vector_get_element_at_const(str->ucsCharacters, 0),
        octaspire_vector_get_element_at_const(cpy->ucsCharacters, 0),
        octaspire_vector_get_length_in_octets(str->ucsCharacters));

    ASSERT_EQ(str->errorStatus,  cpy->errorStatus);
    ASSERT_EQ(str->errorAtOctet, cpy->errorAtOctet);

    ASSERT_EQ(cpy->allocator,     octaspireContainerUtf8StringTestAllocator);

    octaspire_string_release(str);
    str = 0;

    octaspire_string_release(cpy);
    cpy = 0;

    PASS();
}

TEST octaspire_string_new_copy_failure_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(str->octets);
    ASSERT(str->ucsCharacters);
    ASSERT_EQ(OCTASPIRE_STRING_ERROR_STATUS_OK, str->errorStatus);
    ASSERT_EQ(0,                                               str->errorAtOctet);
    ASSERT_EQ(octaspireContainerUtf8StringTestAllocator,                                       str->allocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 1, 0);
    ASSERT_EQ(1, octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator));

    ASSERT_FALSE(octaspire_string_new_copy(str, octaspireContainerUtf8StringTestAllocator));

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_length_in_ucs_characters_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    //ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_length_in_ucs_characters_called_with_empty_string_test(void)
{
    char const * const input = "";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_length_in_octets_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_length_in_octets_called_with_empty_string_test(void)
{
    char const * const input = "";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_string_get_length_in_octets(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_ucs_character_at_index_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

#define EXPECTED_LENGTH 30

    ASSERT_EQ(EXPECTED_LENGTH, octaspire_string_get_length_in_ucs_characters(str));

    uint32_t expected[EXPECTED_LENGTH] =
    {
        0xA9,    // Copyright symbol
        0x48,    // H
        0x65,    // e
        0x6C,    // l
        0x6C,    // l
        0x6F,    // o
        0x20,    // SPACE
        0x57,    // W
        0x6F,    // o
        0x72,    // r
        0x6C,    // l
        0x64,    // d
        0x21,    // !
        0x20,    // SPACE
        0xA9,    // Copyright symbol
        0x20,    // SPACE
        0x2260,  // NOT EQUAL SIGN
        0x10000, // LINEAR B SYLLABLE B008 A
        0x48,    // H
        0x6F,    // o
        0x77,    // w
        0x20,    // SPACE
        0x61,    // a
        0x72,    // r
        0x65,    // e
        0x20,    // SPACE
        0x79,    // y
        0x6F,    // o
        0x75,    // u
        0x3F,    // ?
    };

    for (size_t i = 0; i < EXPECTED_LENGTH; ++i)
    {
        ASSERT_EQ(
            expected[i],
            octaspire_string_get_ucs_character_at_index(
                str,
                (ptrdiff_t)i));
    }

    for (size_t i = 0; i < EXPECTED_LENGTH; ++i)
    {
        ptrdiff_t const index = -((ptrdiff_t)(i + 1));
        ASSERT_EQ(
            expected[EXPECTED_LENGTH - 1 - i],
            octaspire_string_get_ucs_character_at_index(str, index));
    }

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_c_string_test(void)
{
    char const * const input    = "Hello World! ©";
    char const * const expected = "Hello World! \xc2\xa9";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(15, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(14, octaspire_string_get_length_in_ucs_characters(str));

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_c_string_called_with_empty_string_test(void)
{
    char const * const input    = "";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(0, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));

    ASSERT_EQ('\0', *octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_is_error_false_case_test(void)
{
    char const * const input    = "Hello World";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_is_error_true_case_test(void)
{
    char const * const input    = "Hello World\xC0\xB3";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(octaspire_string_is_error(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_error_position_in_octets_called_when_has_error_test(void)
{
    char const * const input    = "Hello World\xC0\xB3";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_EQ(11, octaspire_string_get_error_position_in_octets(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_get_error_position_in_octets_called_when_has_no_error_test(void)
{
    char const * const input    = "Hello World";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_reset_error_status_called_when_there_is_error_test(void)
{
    char const * const input    = "Hello World\xC0\xB3";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT(octaspire_string_is_error(str));
    ASSERT_EQ(11, octaspire_string_get_error_position_in_octets(str));

    octaspire_string_reset_error_status(str);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_reset_error_status_called_when_there_is_no_error_test(void)
{
    char const * const input    = "Hello World";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    octaspire_string_reset_error_status(str);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_concatenate_c_string_called_with_null_and_empty_string_arguments_test(void)
{
    char const * const input = "©Hello World! © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_string_concatenate_c_string(str, 0);
    octaspire_string_concatenate_c_string(str, "");

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

// TODO XXX Add test cases for allocation failures in concatenate_c_string...

TEST octaspire_string_concatenate_c_string_test(void)
{
    char const * const input  = "©Hello World!";
    char const * const input2 = " © ≠𐀀How are you?";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_string_concatenate_c_string(str, input2);

    ASSERT_FALSE(octaspire_string_is_error(str));
    ASSERT_EQ(0, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

#ifndef _MSC_VER
TEST octaspire_string_concatenate_c_string_with_decode_error_test(void)
{
    char const * const input  = "©Hello World!";
    char const * const input2 = " © ≠𐀀How are you?\xC0\xB3";

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_string_concatenate_c_string(str, input2);

    ASSERT(octaspire_string_is_error(str));
    ASSERT_EQ(23, octaspire_string_get_error_position_in_octets(str));

    ASSERT_EQ(37, octaspire_string_get_length_in_octets(str));
    ASSERT_EQ(30, octaspire_string_get_length_in_ucs_characters(str));

    char const * const expected = 
        "\xC2\xA9Hello World! \xC2\xA9 \xE2\x89\xA0\xF0\x90\x80\x80How are you?";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}
#endif

TEST octaspire_string_concatenate_c_string_allocation_failure_one_test(void)
{
#ifdef _MSC_VER
    char const * const input  = u8"©Hello World!";
    char const * const input2 = u8" © ≠𐀀How are you?";
#else
    char const * const input  = "©Hello World!";
    char const * const input2 = " © ≠𐀀How are you?";
#endif

    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 1, 0);

    ASSERT_FALSE(octaspire_string_concatenate_c_string(str, input2));

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_concatenate_c_string_allocation_failure_two_test(void)
{
    char const * const input  = "a";
    char const * const input2 = "bcd";
    octaspire_string_t *str =
        octaspire_string_new(input, octaspireContainerUtf8StringTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerUtf8StringTestAllocator,
        2, 0x00000002);

    ASSERT_FALSE(octaspire_string_concatenate_c_string(str, input2));

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_c_strings_end_always_in_null_byte_test(void)
{
    octaspire_string_t *str = octaspire_string_new("", octaspireContainerUtf8StringTestAllocator);
    ASSERT(octaspire_vector_is_empty(str->octets));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    str = octaspire_string_new("a", octaspireContainerUtf8StringTestAllocator);
    ASSERT(octaspire_vector_is_empty(str->octets));
    ASSERT_STR_EQ("a", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;


    str = octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, "");
    ASSERT(octaspire_vector_is_empty(str->octets));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;


    size_t const size = 112;
    str = octaspire_string_new_format(octaspireContainerUtf8StringTestAllocator, "%zu", size);
    ASSERT(octaspire_vector_is_empty(str->octets));
    ASSERT_STR_EQ("112", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_new_format_numbers_into_vector_test(void)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(octaspire_string_t*),
        true,
        (octaspire_vector_element_callback_t)octaspire_string_release,
        octaspireContainerUtf8StringTestAllocator);

    size_t const numElements = 256;

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerUtf8StringTestAllocator,
            "%zu",
            i);

        octaspire_vector_push_back_element(vec, &str);

    }

    for (size_t i = 0; i < numElements; ++i)
    {
        octaspire_string_t const * const str =
            octaspire_vector_get_element_at_const(vec, (ptrdiff_t)i);

        ASSERT_EQ(i, (size_t)atoi(octaspire_string_get_c_string(str)));
    }

    octaspire_vector_release(vec);
    vec = 0;

    PASS();
}

TEST octaspire_string_new_format_number_test(void)
{
    size_t const i = 2000;
    octaspire_string_t *str = octaspire_string_new_format(
            octaspireContainerUtf8StringTestAllocator,
            "%zu",
            i);

    ASSERT_EQ(i, (size_t)atoi(octaspire_string_get_c_string(str)));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_char_a_from_string_a123a56a89a_using_negative_indice_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "a123a56a89a",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *character =
        octaspire_string_new("a123",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && character);

    // Test failure first
    octaspire_vector_t *indices = octaspire_string_find_char(
        str,
        character,
        -5);

    ASSERT_FALSE(indices);

    // Test success
    indices = octaspire_string_find_char(
        str,
        character,
        -4);

    ASSERT(indices);

    ASSERT_EQ(4, octaspire_vector_get_length(indices));

    ASSERT_EQ(0,  *(size_t*)octaspire_vector_get_element_at(indices, 0));
    ASSERT_EQ(4,  *(size_t*)octaspire_vector_get_element_at(indices, 1));
    ASSERT_EQ(7,  *(size_t*)octaspire_vector_get_element_at(indices, 2));
    ASSERT_EQ(10, *(size_t*)octaspire_vector_get_element_at(indices, 3));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(character);
    character = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_char_a_from_string_a123a56a89a_using_index_zero_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "a123a56a89a",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *character =
        octaspire_string_new("a123",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && character);

    octaspire_vector_t *indices = octaspire_string_find_char(
        str,
        character,
        0);

    ASSERT(indices);

    ASSERT_EQ(4, octaspire_vector_get_length(indices));

    ASSERT_EQ(0,  *(size_t*)octaspire_vector_get_element_at(indices, 0));
    ASSERT_EQ(4,  *(size_t*)octaspire_vector_get_element_at(indices, 1));
    ASSERT_EQ(7,  *(size_t*)octaspire_vector_get_element_at(indices, 2));
    ASSERT_EQ(10, *(size_t*)octaspire_vector_get_element_at(indices, 3));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(character);
    character = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_char_q_from_string_a123a56q89q_using_index_one_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "a123a56q89q",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *character =
        octaspire_string_new("aq123",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && character);

    octaspire_vector_t *indices = octaspire_string_find_char(
        str,
        character,
        1);

    ASSERT(indices);

    ASSERT_EQ(2, octaspire_vector_get_length(indices));

    ASSERT_EQ(7,  *(size_t*)octaspire_vector_get_element_at(indices, 0));
    ASSERT_EQ(10, *(size_t*)octaspire_vector_get_element_at(indices, 1));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(character);
    character = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_char_c_from_string_a123c56q89q_using_index_two_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "a123c56q89q",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *character =
        octaspire_string_new("aqc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && character);

    octaspire_vector_t *indices = octaspire_string_find_char(
        str,
        character,
        2);

    ASSERT(indices);

    ASSERT_EQ(1, octaspire_vector_get_length(indices));

    ASSERT_EQ(4, *(size_t*)octaspire_vector_get_element_at(indices, 0));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(character);
    character = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_char_c_from_string_a123y56q89q_using_index_two_failure_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "a123y56q89q",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *character =
        octaspire_string_new("aqc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && character);

    octaspire_vector_t *indices = octaspire_string_find_char(
        str,
        character,
        2);

    ASSERT(indices);

    ASSERT_EQ(0, octaspire_vector_get_length(indices));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(character);
    character = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_string_Xcat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_minus_3_and_length_of_3_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "cat dog cat zebra car kitten cat",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *lookFor =
        octaspire_string_new("Xcat",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_vector_t *indices = octaspire_string_find_string(
        str,
        lookFor,
        -3,
        3);

    ASSERT(indices);

    ASSERT_EQ(3, octaspire_vector_get_length(indices));

    ASSERT_EQ(0,   *(size_t*)octaspire_vector_get_element_at(indices, 0));
    ASSERT_EQ(8,   *(size_t*)octaspire_vector_get_element_at(indices, 1));
    ASSERT_EQ(29,  *(size_t*)octaspire_vector_get_element_at(indices, 2));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(lookFor);
    lookFor = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_string_cat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_zero_and_length_of_3_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "cat dog cat zebra car kitten cat",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *lookFor =
        octaspire_string_new("cat",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_vector_t *indices = octaspire_string_find_string(
        str,
        lookFor,
        0,
        3);

    ASSERT(indices);

    ASSERT_EQ(3, octaspire_vector_get_length(indices));

    ASSERT_EQ(0,   *(size_t*)octaspire_vector_get_element_at(indices, 0));
    ASSERT_EQ(8,   *(size_t*)octaspire_vector_get_element_at(indices, 1));
    ASSERT_EQ(29,  *(size_t*)octaspire_vector_get_element_at(indices, 2));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(lookFor);
    lookFor = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_string_cat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_one_and_length_of_3_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "cat dog cat zebra car kitten cat",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *lookFor =
        octaspire_string_new(">cat<",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_vector_t *indices = octaspire_string_find_string(
        str,
        lookFor,
        1,
        3);

    ASSERT(indices);

    ASSERT_EQ(3, octaspire_vector_get_length(indices));

    ASSERT_EQ(0,   *(size_t*)octaspire_vector_get_element_at(indices, 0));
    ASSERT_EQ(8,   *(size_t*)octaspire_vector_get_element_at(indices, 1));
    ASSERT_EQ(29,  *(size_t*)octaspire_vector_get_element_at(indices, 2));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(lookFor);
    lookFor = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_string_dog_from_string_dog_cat_zebra_using_index_zero_and_length_of_three_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "dog cat zebra",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *lookFor =
        octaspire_string_new("dog",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_vector_t *indices = octaspire_string_find_string(
        str,
        lookFor,
        0,
        3);

    ASSERT(indices);

    ASSERT_EQ(1, octaspire_vector_get_length(indices));

    ASSERT_EQ(0,   *(size_t*)octaspire_vector_get_element_at(indices, 0));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(lookFor);
    lookFor = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_string_dog_from_string_cat_zebra_dog_using_index_zero_and_length_of_three_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "cat zebra dog",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *lookFor =
        octaspire_string_new("dog",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_vector_t *indices = octaspire_string_find_string(
        str,
        lookFor,
        0,
        3);

    ASSERT(indices);

    ASSERT_EQ(1, octaspire_vector_get_length(indices));

    ASSERT_EQ(10,   *(size_t*)octaspire_vector_get_element_at(indices, 0));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(lookFor);
    lookFor = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_string_dog_from_string_cat_zebra_kitten_using_index_zero_and_length_of_three_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "cat zebra kitten",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *lookFor =
        octaspire_string_new("dog",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_vector_t *indices = octaspire_string_find_string(
        str,
        lookFor,
        0,
        3);

    ASSERT(indices);

    ASSERT_EQ(0, octaspire_vector_get_length(indices));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(lookFor);
    lookFor = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_string_kitten_from_string_cat_using_index_zero_and_length_of_six_failure_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "cat",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *lookFor =
        octaspire_string_new("kitten",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && lookFor);

    octaspire_vector_t *indices = octaspire_string_find_string(
        str,
        lookFor,
        0,
        6);

    ASSERT(indices);

    ASSERT_EQ(0, octaspire_vector_get_length(indices));

    octaspire_vector_release(indices);
    indices = 0;

    octaspire_string_release(lookFor);
    lookFor = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_private_check_substring_match_at_middle_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "123kitten456",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("kitten",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    for (size_t i = 0; i < octaspire_string_get_length_in_ucs_characters(str); ++i)
    {
        ASSERT_EQ(i == 3 ? true : false,
            octaspire_string_private_check_substring_match_at(
                str,
                i,
                substring));
    }

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_private_check_substring_match_at_the_beginning_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "kitten456",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("kitten",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    for (size_t i = 0; i < octaspire_string_get_length_in_ucs_characters(str); ++i)
    {
        ASSERT_EQ(i == 0 ? true : false,
            octaspire_string_private_check_substring_match_at(
                str,
                i,
                substring));
    }

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_private_check_substring_match_at_the_end_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "123kitten",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("kitten",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    for (size_t i = 0; i < octaspire_string_get_length_in_ucs_characters(str); ++i)
    {
        ASSERT_EQ(i == 3 ? true : false,
            octaspire_string_private_check_substring_match_at(
                str,
                i,
                substring));
    }

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_first_substring_abc_from_123abc456abc_starting_from_index_0_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "123abc456abc",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("abc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    ASSERT_EQ(
        3,
        octaspire_string_find_first_substring(
            str,
            0,
            substring));

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_first_substring_abc_from_123abc456abc_starting_from_index_minus_three_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "123abc456abc",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("abc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    ASSERT_EQ(
        9,
        octaspire_string_find_first_substring(
            str,
            -3,
            substring));

    ASSERT_EQ(
        9,
        octaspire_string_find_first_substring(
            str,
            -4,
            substring));

    ASSERT_EQ(
        3,
        octaspire_string_find_first_substring(
            str,
            -9,
            substring));

    ASSERT_EQ(
        3,
        octaspire_string_find_first_substring(
            str,
            -12,
            substring));

    // Not found
    ASSERT_EQ(
        -1,
        octaspire_string_find_first_substring(
            str,
            -2,
            substring));

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_first_substring_abc_from_123abc456abc_starting_from_index_4_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "123abc456abc",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("abc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    ASSERT_EQ(
        9,
        octaspire_string_find_first_substring(
            str,
            4,
            substring));

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_find_first_substring_abcd_from_123abc456abc_starting_from_index_0_failure_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "123abc456abc",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("abcd",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    ASSERT_EQ(
        -1,
        octaspire_string_find_first_substring(
            str,
            0,
            substring));

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_remove_character_at_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "0123456789",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT(octaspire_string_remove_character_at(str, 1));
    ASSERT_STR_EQ("023456789", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, 0));
    ASSERT_STR_EQ("23456789", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, 7));
    ASSERT_STR_EQ("2345678", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, -1));
    ASSERT_STR_EQ("234567", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, -1));
    ASSERT_STR_EQ("23456", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, -5));
    ASSERT_STR_EQ("3456", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, -4));
    ASSERT_STR_EQ("456", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, -2));
    ASSERT_STR_EQ("46", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_remove_character_at_called_on_string_with_two_os_with_diaeresis_test(void)
{
    char const * const expected =
        "öö";

    char const * const expected2 =
        "ö";

    octaspire_string_t *str = octaspire_string_new(
        expected,
        octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);
    ASSERT_EQ(2, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ(expected, octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, 1));
    ASSERT_EQ(1, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ(expected2, octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_remove_character_at(str, 0));
    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_remove_characters_at_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
        "0123456789",
        octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    ASSERT_EQ(3, octaspire_string_remove_characters_at(str, 7, 3));
    ASSERT_STR_EQ("0123456", octaspire_string_get_c_string(str));

    ASSERT_EQ(3, octaspire_string_remove_characters_at(str, 2, 3));
    ASSERT_STR_EQ("0156", octaspire_string_get_c_string(str));

    ASSERT_EQ(3, octaspire_string_remove_characters_at(str, 0, 3));
    ASSERT_STR_EQ("6", octaspire_string_get_c_string(str));

    ASSERT_EQ(1, octaspire_string_remove_characters_at(str, 0, 1));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    // Using negative indices
    str = octaspire_string_new(
        "0123456789",
        octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    // Failures
    ASSERT_EQ(0, octaspire_string_remove_characters_at(str, -11, 3));
    ASSERT_STR_EQ("0123456789", octaspire_string_get_c_string(str));

    ASSERT_EQ(0, octaspire_string_remove_characters_at(str, -12, 3));
    ASSERT_STR_EQ("0123456789", octaspire_string_get_c_string(str));

    // Success
    ASSERT_EQ(3, octaspire_string_remove_characters_at(str, -3, 3));
    ASSERT_STR_EQ("0123456", octaspire_string_get_c_string(str));

    ASSERT_EQ(3, octaspire_string_remove_characters_at(str, -5, 3));
    ASSERT_STR_EQ("0156", octaspire_string_get_c_string(str));

    ASSERT_EQ(3, octaspire_string_remove_characters_at(str, -4, 3));
    ASSERT_STR_EQ("6", octaspire_string_get_c_string(str));

    ASSERT_EQ(1, octaspire_string_remove_characters_at(str, -1, 1));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_remove_all_substrings_kitten_from_string_kitten_cat_kitten_dog_kitten_zebra_kitten_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
            "kitten cat kitten dog kitten zebra kitten",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *substring =
        octaspire_string_new("kitten",octaspireContainerUtf8StringTestAllocator);

    ASSERT(str && substring);

    ASSERT_EQ(4, octaspire_string_remove_all_substrings(str, substring));

    ASSERT_STR_EQ(
        " cat  dog  zebra ",
        octaspire_string_get_c_string(str));

    octaspire_string_release(substring);
    substring = 0;

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_insert_string_to_bc_into_index_1_of_ade_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_insert_string_to(strTarget, strAddition, 1));

    ASSERT_EQ(5, octaspire_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "abcde",
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_insert_string_to_bc_into_index_minus_1_of_ade_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_insert_string_to(strTarget, strAddition, -1));

    ASSERT_EQ(5, octaspire_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "adbce",
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_insert_string_to_bc_into_index_minus_3_of_ade_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_insert_string_to(strTarget, strAddition, -3));

    ASSERT_EQ(5, octaspire_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "bcade",
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_insert_string_to_bc_into_index_minus_4_of_ade_failure_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT_FALSE(octaspire_string_insert_string_to(strTarget, strAddition, -4));

    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "ade",
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_insert_string_to_bc_into_index_3_of_ade_failure_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT_FALSE(octaspire_string_insert_string_to(strTarget, strAddition, 3));

    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "ade",
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_insert_string_to_bc_into_index_0_of_ade_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_insert_string_to(strTarget, strAddition, 0));

    ASSERT_EQ(5, octaspire_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "bcade",
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_insert_string_to_bc_into_index_2_of_ade_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "ade",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new("bc",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_insert_string_to(strTarget, strAddition, 2));

    ASSERT_EQ(5, octaspire_string_get_length_in_ucs_characters(strTarget));

    ASSERT_STR_EQ(
        "adbce",
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_overwrite_with_string_at_first_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "",
            octaspireContainerUtf8StringTestAllocator);

    char const * const expected =
        "abö";

    octaspire_string_t *strAddition =
        octaspire_string_new(expected,octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_overwrite_with_string_at(strTarget, strAddition, 0));
    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(strTarget));
    ASSERT_EQ(4, octaspire_string_get_length_in_octets(strTarget));
    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    strAddition = octaspire_string_new("q",octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_overwrite_with_string_at(strTarget, strAddition, 1));
    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(strTarget));
    ASSERT_EQ(4, octaspire_string_get_length_in_octets(strTarget));

    char const * const expected2 =
        "aqö";

    ASSERT_STR_EQ(
        expected2,
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_overwrite_with_string_at_second_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "abc",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new(
            "ö",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_overwrite_with_string_at(strTarget, strAddition, 1));
    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(strTarget));
    ASSERT_EQ(4, octaspire_string_get_length_in_octets(strTarget));

    char const * const expected = "aöc";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_overwrite_with_string_at_called_with_negative_index_test(void)
{
    octaspire_string_t *strTarget = octaspire_string_new(
            "abc",
            octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *strAddition =
        octaspire_string_new(
            "ö",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(strTarget && strAddition);

    ASSERT(octaspire_string_overwrite_with_string_at(
            strTarget,
            strAddition,
            -2));

    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(strTarget));
    ASSERT_EQ(4, octaspire_string_get_length_in_octets(strTarget));

    char const * const expected = "aöc";

    ASSERT_STR_EQ(
        expected,
        octaspire_string_get_c_string(strTarget));

    octaspire_string_release(strAddition);
    strAddition = 0;

    octaspire_string_release(strTarget);
    strTarget = 0;

    PASS();
}

TEST octaspire_string_pop_front_ucs_character_test(void)
{
    octaspire_string_t *str = octaspire_string_new(
        "abc",
        octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);
    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("abc", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_pop_front_ucs_character(str));
    ASSERT_EQ(2, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("bc", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_pop_front_ucs_character(str));
    ASSERT_EQ(1, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("c", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_pop_front_ucs_character(str));
    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    for (size_t i = 0; i < 10; ++i)
    {
        ASSERT_FALSE(octaspire_string_pop_front_ucs_character(str));
        ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));
        ASSERT_STR_EQ("", octaspire_string_get_c_string(str));
    }

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_pop_back_ucs_character_test(void)
{
    octaspire_string_t *str = octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);
    ASSERT_EQ(3, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("abc", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_pop_back_ucs_character(str));
    ASSERT_EQ(2, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("ab", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_pop_back_ucs_character(str));
    ASSERT_EQ(1, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("a", octaspire_string_get_c_string(str));

    ASSERT(octaspire_string_pop_back_ucs_character(str));
    ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));
    ASSERT_STR_EQ("", octaspire_string_get_c_string(str));

    for (size_t i = 0; i < 10; ++i)
    {
        ASSERT_FALSE(octaspire_string_pop_back_ucs_character(str));
        ASSERT_EQ(0, octaspire_string_get_length_in_ucs_characters(str));
        ASSERT_STR_EQ("", octaspire_string_get_c_string(str));
    }

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_compare_with_two_empty_strings_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT_EQ(0, octaspire_string_compare(str1, str2));

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_compare_with_abc_and_empty_string_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT(octaspire_string_compare(str1, str2) > 0);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_compare_with_empty_string_and_abc_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT(octaspire_string_compare(str1, str2) < 0);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_compare_with_string_abc_and_abc_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT_EQ(0, octaspire_string_compare(str1, str2));

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_compare_with_string_abd_and_abc_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("abd", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT(octaspire_string_compare(str1, str2) > 0);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_compare_with_string_abca_and_abc_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("abca", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT(octaspire_string_compare(str1, str2) > 0);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_compare_with_string_abb_and_abc_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("abb", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT(octaspire_string_compare(str1, str2) < 0);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_compare_with_string_abc_and_abca_test(void)
{
    octaspire_string_t *str =
        octaspire_string_new(
            "",
            octaspireContainerUtf8StringTestAllocator);

    for (ptrdiff_t i = -64; i < 64; ++i)
    {
        ASSERT_FALSE(octaspire_string_is_index_valid(str, i));
    }

    octaspire_string_concatenate_c_string(str, "a");

    for (ptrdiff_t i = -64; i < 64; ++i)
    {
        ASSERT_EQ(
            i== -1 || i == 0,
            octaspire_string_is_index_valid(str, i));
    }

    octaspire_string_concatenate_c_string(str, "b");

    for (ptrdiff_t i = -64; i < 64; ++i)
    {
        ASSERT_EQ(
            i == -1 || i == -2 || i == 0 || i == 1,
            octaspire_string_is_index_valid(str, i));
    }

    ASSERT(str);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_abc_and_empty_string_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "abc",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(3, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_two_empty_strings_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(0, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_empty_string_and_abc_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "abc",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(3, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_abcdefghijklmnopqrstuvwxyz_and_abc_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "abcdefghijklmnopqrstuvwxyz",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "abc",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(23, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_a_and_b_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "a",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "b",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(1, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_kitten_and_sitting_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "kitten",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "sitting",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(3, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_flaw_and_lawn_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "flaw",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "lawn",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(2, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_jfpaasdasd2d_and_askdfsferrr4_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "jfpaasdasd2d",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "askdfsferrr4",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(11, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_rosettacode_and_raisethysword_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "rosettacode",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "raisethysword",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(8, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_levenshtein_distance_called_with_two_longer_strings_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new(
            "CTAGGCTCGGACCAATCACCTAGGCCTCGGACCAACACCAACTACTCAAGAAGGGGTG",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);

    octaspire_string_t *str2 =
        octaspire_string_new(
            "GACTTACTGGGACAAGTCTTGGACACATGGCAAACCAGTCCCGAACCAACAGCACATG",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str2);

    size_t const result =
        octaspire_string_levenshtein_distance(str1, str2);

    ASSERT_EQ(32, result);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_starts_with_c_string_test(void)
{
    octaspire_string_t *str =
        octaspire_string_new(
            "abcdefghij",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);
    ASSERT(octaspire_string_starts_with_c_string(str, "a"));
    ASSERT(octaspire_string_starts_with_c_string(str, "ab"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abc"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abcd"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abcde"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abcdef"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abcdefg"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abcdefgh"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abcdefghi"));
    ASSERT(octaspire_string_starts_with_c_string(str, "abcdefghij"));

    ASSERT_FALSE(octaspire_string_starts_with_c_string(str, "abcdefghijk"));
    ASSERT_FALSE(octaspire_string_starts_with_c_string(str, "abcdefghix"));
    ASSERT_FALSE(octaspire_string_starts_with_c_string(str, "abcdefghxj"));
    ASSERT_FALSE(octaspire_string_starts_with_c_string(str, "abcdefgxij"));
    ASSERT_FALSE(octaspire_string_starts_with_c_string(str, "b"));

    ASSERT(octaspire_string_starts_with_c_string(str, ""));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_ends_with_c_string_test(void)
{
    octaspire_string_t *str =
        octaspire_string_new(
            "abcdefghij",
            octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);
    ASSERT(octaspire_string_ends_with_c_string(str, "j"));
    ASSERT(octaspire_string_ends_with_c_string(str, "ij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "hij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "ghij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "fghij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "efghij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "defghij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "cdefghij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "bcdefghij"));
    ASSERT(octaspire_string_ends_with_c_string(str, "abcdefghij"));

    ASSERT_FALSE(octaspire_string_ends_with_c_string(str, "abcdefghijk"));
    ASSERT_FALSE(octaspire_string_ends_with_c_string(str, "abcdefghix"));
    ASSERT_FALSE(octaspire_string_ends_with_c_string(str, "abcdefghxj"));
    ASSERT_FALSE(octaspire_string_ends_with_c_string(str, "abcdefgxij"));
    ASSERT_FALSE(octaspire_string_ends_with_c_string(str, "i"));

    ASSERT(octaspire_string_ends_with_c_string(str, ""));

    octaspire_string_release(str);
    str = 0;

    PASS();
}

TEST octaspire_string_is_index_valid_test(void)
{
    octaspire_string_t *str1 =
        octaspire_string_new("abc", octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 =
        octaspire_string_new("abca", octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT(octaspire_string_compare(str1, str2) < 0);

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    PASS();
}

TEST octaspire_string_set_from_c_string_test(void)
{
    octaspire_string_t *str1 = octaspire_string_new(
        "",
        octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str2 = octaspire_string_new(
        "ab",
        octaspireContainerUtf8StringTestAllocator);

    octaspire_string_t *str3 = octaspire_string_new(
        "abc",
        octaspireContainerUtf8StringTestAllocator);

    ASSERT(str1);
    ASSERT(str2);
    ASSERT(str3);

    char const * const expected = "xy";

    ASSERT(octaspire_string_set_from_c_string(str1, expected));
    ASSERT(octaspire_string_set_from_c_string(str2, expected));
    ASSERT(octaspire_string_set_from_c_string(str3, expected));

    ASSERT(octaspire_string_compare_to_c_string(str1, expected) == 0);
    ASSERT(octaspire_string_compare_to_c_string(str2, expected) == 0);
    ASSERT(octaspire_string_compare_to_c_string(str3, expected) == 0);

    ASSERT_STR_EQ(expected, octaspire_string_get_c_string(str1));
    ASSERT_STR_EQ(expected, octaspire_string_get_c_string(str2));
    ASSERT_STR_EQ(expected, octaspire_string_get_c_string(str3));

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    octaspire_string_release(str3);
    str3 = 0;

    PASS();
}

TEST octaspire_string_set_from_c_string_allocation_failure_on_first_allocation_test(void)
{
    char const * const expected = "abc";

    octaspire_string_t *str = octaspire_string_new(
        expected,
        octaspireContainerUtf8StringTestAllocator);

    ASSERT(str);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerUtf8StringTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerUtf8StringTestAllocator));

    ASSERT_FALSE(octaspire_string_set_from_c_string(str, "xy"));

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerUtf8StringTestAllocator, 0, 0x00);

    octaspire_string_release(str);
    str = 0;

    PASS();
}

GREATEST_SUITE(octaspire_string_suite)
{
    octaspireContainerUtf8StringTestAllocator = octaspire_allocator_new(0);

    assert(octaspireContainerUtf8StringTestAllocator);

    RUN_TEST(octaspire_string_new_called_with_null_argument_test);
    RUN_TEST(octaspire_string_new_with_simple_ascii_string_test);
    RUN_TEST(octaspire_string_new_with_some_multioctet_ucs_characters_test);
    RUN_TEST(octaspire_string_new_with_simple_ascii_string_with_error_test);
    RUN_TEST(octaspire_string_new_from_buffer_with_some_multioctet_ucs_characters_test);
    RUN_TEST(octaspire_string_new_from_buffer_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_string_new_from_buffer_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_string_new_from_buffer_allocation_failure_on_third_allocation_test);



    RUN_TEST(octaspire_string_new_from_buffer_allocation_failure_on_sixth_2_allocation_test);
    RUN_TEST(octaspire_string_new_format_with_string_test);
    RUN_TEST(octaspire_string_new_format_with_size_t_test);
    RUN_TEST(octaspire_string_new_format_with_doubles_test);
    RUN_TEST(octaspire_string_new_format_with_string_and_size_t_test);
    RUN_TEST(octaspire_string_new_format_with_string_and_size_t_on_otherwise_empty_format_string_test);
    RUN_TEST(octaspire_string_new_format_with_empty_format_string_test);
    RUN_TEST(octaspire_string_new_copy_test);
    RUN_TEST(octaspire_string_new_copy_failure_test);
    RUN_TEST(octaspire_string_get_length_in_ucs_characters_test);
    RUN_TEST(octaspire_string_get_length_in_ucs_characters_called_with_empty_string_test);
    RUN_TEST(octaspire_string_get_length_in_octets_test);
    RUN_TEST(octaspire_string_get_length_in_octets_called_with_empty_string_test);
    RUN_TEST(octaspire_string_get_ucs_character_at_index_test);
    RUN_TEST(octaspire_string_get_c_string_test);
    RUN_TEST(octaspire_string_get_c_string_called_with_empty_string_test);
    RUN_TEST(octaspire_string_is_error_false_case_test);
    RUN_TEST(octaspire_string_is_error_true_case_test);
    RUN_TEST(octaspire_string_get_error_position_in_octets_called_when_has_error_test);
    RUN_TEST(octaspire_string_get_error_position_in_octets_called_when_has_no_error_test);
    RUN_TEST(octaspire_string_reset_error_status_called_when_there_is_error_test);
    RUN_TEST(octaspire_string_reset_error_status_called_when_there_is_no_error_test);
    RUN_TEST(octaspire_string_concatenate_c_string_called_with_null_and_empty_string_arguments_test);
    RUN_TEST(octaspire_string_concatenate_c_string_test);
#ifndef _MSC_VER
    RUN_TEST(octaspire_string_concatenate_c_string_with_decode_error_test);
#endif
    RUN_TEST(octaspire_string_concatenate_c_string_allocation_failure_one_test);
    RUN_TEST(octaspire_string_concatenate_c_string_allocation_failure_two_test);
    RUN_TEST(octaspire_string_c_strings_end_always_in_null_byte_test);
    RUN_TEST(octaspire_string_new_format_numbers_into_vector_test);
    RUN_TEST(octaspire_string_new_format_number_test);
    RUN_TEST(octaspire_string_find_char_a_from_string_a123a56a89a_using_negative_indice_test);
    RUN_TEST(octaspire_string_find_char_a_from_string_a123a56a89a_using_index_zero_test);
    RUN_TEST(octaspire_string_find_char_q_from_string_a123a56q89q_using_index_one_test);
    RUN_TEST(octaspire_string_find_char_c_from_string_a123c56q89q_using_index_two_test);
    RUN_TEST(octaspire_string_find_char_c_from_string_a123y56q89q_using_index_two_failure_test);
    RUN_TEST(octaspire_string_find_string_Xcat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_minus_3_and_length_of_3_test);
    RUN_TEST(octaspire_string_find_string_cat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_zero_and_length_of_3_test);
    RUN_TEST(octaspire_string_find_string_cat_from_string_cat_dog_cat_zebra_car_kitten_cat_using_index_one_and_length_of_3_test);
    RUN_TEST(octaspire_string_find_string_dog_from_string_dog_cat_zebra_using_index_zero_and_length_of_three_test);
    RUN_TEST(octaspire_string_find_string_dog_from_string_cat_zebra_dog_using_index_zero_and_length_of_three_test);
    RUN_TEST(octaspire_string_find_string_dog_from_string_cat_zebra_kitten_using_index_zero_and_length_of_three_test);
    RUN_TEST(octaspire_string_find_string_kitten_from_string_cat_using_index_zero_and_length_of_six_failure_test);
    RUN_TEST(octaspire_string_private_check_substring_match_at_middle_test);
    RUN_TEST(octaspire_string_private_check_substring_match_at_the_beginning_test);
    RUN_TEST(octaspire_string_private_check_substring_match_at_the_end_test);
    RUN_TEST(octaspire_string_find_first_substring_abc_from_123abc456abc_starting_from_index_0_test);
    RUN_TEST(octaspire_string_find_first_substring_abc_from_123abc456abc_starting_from_index_minus_three_test);
    RUN_TEST(octaspire_string_find_first_substring_abc_from_123abc456abc_starting_from_index_4_test);
    RUN_TEST(octaspire_string_find_first_substring_abcd_from_123abc456abc_starting_from_index_0_failure_test);
    RUN_TEST(octaspire_string_remove_character_at_test);
    RUN_TEST(octaspire_string_remove_character_at_called_on_string_with_two_os_with_diaeresis_test);
    RUN_TEST(octaspire_string_remove_characters_at_test);
    RUN_TEST(octaspire_string_remove_all_substrings_kitten_from_string_kitten_cat_kitten_dog_kitten_zebra_kitten_test);
    RUN_TEST(octaspire_string_insert_string_to_bc_into_index_1_of_ade_test);
    RUN_TEST(octaspire_string_insert_string_to_bc_into_index_minus_1_of_ade_test);
    RUN_TEST(octaspire_string_insert_string_to_bc_into_index_minus_3_of_ade_test);
    RUN_TEST(octaspire_string_insert_string_to_bc_into_index_minus_4_of_ade_failure_test);
    RUN_TEST(octaspire_string_insert_string_to_bc_into_index_3_of_ade_failure_test);
    RUN_TEST(octaspire_string_insert_string_to_bc_into_index_0_of_ade_test);
    RUN_TEST(octaspire_string_insert_string_to_bc_into_index_2_of_ade_test);

    RUN_TEST(octaspire_string_overwrite_with_string_at_first_test);
    RUN_TEST(octaspire_string_overwrite_with_string_at_second_test);
    RUN_TEST(octaspire_string_overwrite_with_string_at_called_with_negative_index_test);

    RUN_TEST(octaspire_string_pop_front_ucs_character_test);
    RUN_TEST(octaspire_string_pop_back_ucs_character_test);

    RUN_TEST(octaspire_string_compare_with_two_empty_strings_test);
    RUN_TEST(octaspire_string_compare_with_abc_and_empty_string_test);
    RUN_TEST(octaspire_string_compare_with_empty_string_and_abc_test);
    RUN_TEST(octaspire_string_compare_with_string_abc_and_abc_test);
    RUN_TEST(octaspire_string_compare_with_string_abd_and_abc_test);
    RUN_TEST(octaspire_string_compare_with_string_abca_and_abc_test);
    RUN_TEST(octaspire_string_compare_with_string_abb_and_abc_test);
    RUN_TEST(octaspire_string_compare_with_string_abc_and_abca_test);

    RUN_TEST(octaspire_string_levenshtein_distance_called_with_abc_and_empty_string_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_two_empty_strings_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_empty_string_and_abc_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_abcdefghijklmnopqrstuvwxyz_and_abc_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_a_and_b_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_kitten_and_sitting_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_flaw_and_lawn_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_jfpaasdasd2d_and_askdfsferrr4_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_rosettacode_and_raisethysword_test);
    RUN_TEST(octaspire_string_levenshtein_distance_called_with_two_longer_strings_test);

    RUN_TEST(octaspire_string_starts_with_c_string_test);
    RUN_TEST(octaspire_string_ends_with_c_string_test);

    RUN_TEST(octaspire_string_is_index_valid_test);

    RUN_TEST(octaspire_string_set_from_c_string_test);
    RUN_TEST(octaspire_string_set_from_c_string_allocation_failure_on_first_allocation_test);

    octaspire_allocator_release(octaspireContainerUtf8StringTestAllocator);
    octaspireContainerUtf8StringTestAllocator = 0;
}

