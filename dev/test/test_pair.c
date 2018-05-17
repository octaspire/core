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
#include "../src/octaspire_pair.c"
#include <assert.h>
#include "external/greatest.h"
#include "octaspire/core/octaspire_string.h"
#include "octaspire/core/octaspire_helpers.h"
#include "octaspire/core/octaspire_memory.h"
#include "octaspire/core/octaspire_core_config.h"

static octaspire_allocator_t *octaspireContainerPairTestAllocator = 0;

TEST octaspire_pair_new_short_and_long_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    ASSERT(p->first);
    ASSERT(p->second);

    ASSERT_EQ(0, *(short const*)p->first);
    ASSERT_EQ(0, *(long const*)p->second);

    ASSERT_EQ(sizeof(short), p->firstSize);
    ASSERT_EQ(sizeof(long),  p->secondSize);
    ASSERT_EQ(0,             p->firstReleaseCallback);
    ASSERT_EQ(0,             p->secondReleaseCallback);
    ASSERT_EQ(octaspireContainerPairTestAllocator,     p->allocator);

    short const expectedFirst  = 11;
    long  const expectedSecond = 12;
    octaspire_pair_set(p, &expectedFirst, &expectedSecond);

    ASSERT_EQ(expectedFirst,  *(short const *)p->first);
    ASSERT_EQ(expectedSecond, *(long const *) p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_new_long_and_short_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    ASSERT(p->first);
    ASSERT(p->second);

    ASSERT_EQ(0, *(long const*)p->first);
    ASSERT_EQ(0, *(short const*)p->second);

    ASSERT_EQ(sizeof(long), p->firstSize);
    ASSERT_EQ(sizeof(short),  p->secondSize);
    ASSERT_EQ(0,             p->firstReleaseCallback);
    ASSERT_EQ(0,             p->secondReleaseCallback);
    ASSERT_EQ(octaspireContainerPairTestAllocator,     p->allocator);

    long  const expectedFirst  = 11;
    short const expectedSecond = 12;
    octaspire_pair_set(p, &expectedFirst, &expectedSecond);

    ASSERT_EQ(expectedFirst,  *(long const*) p->first);
    ASSERT_EQ(expectedSecond, *(short const*)p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_new_uint32_t_and_double_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(uint32_t),
        false,
        sizeof(double),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    ASSERT(p->first);
    ASSERT(p->second);

    ASSERT_IN_RANGE(0, *(uint32_t*)p->first, 0.000001);
    ASSERT_IN_RANGE(0, *(double*)p->second,  0.000001);

    ASSERT_EQ(sizeof(uint32_t), p->firstSize);
    ASSERT_EQ(sizeof(double),   p->secondSize);
    ASSERT_EQ(0,                p->firstReleaseCallback);
    ASSERT_EQ(0,                p->secondReleaseCallback);
    ASSERT_EQ(octaspireContainerPairTestAllocator,        p->allocator);

    uint32_t  const expectedFirst  = 11;
    double    const expectedSecond = 12.12;
    octaspire_pair_set(p, &expectedFirst, &expectedSecond);

    ASSERT_EQ(expectedFirst,  *(uint32_t const*)p->first);
    ASSERT_IN_RANGE(expectedSecond, *(double const*)p->second, 0.000001);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_new_allocation_failure_on_first_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_new_allocation_failure_on_second_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        2,
        0x01);

    ASSERT_EQ(
        2,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_new_allocation_failure_on_third_allocation_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        3,
        0x03);

    ASSERT_EQ(
        3,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_new_shallow_copy_uint32_t_and_double_test(void)
{
    octaspire_pair_t *expected = octaspire_pair_new(
        sizeof(uint32_t),
        false,
        sizeof(double),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(expected);

    uint32_t  const expectedFirst  = 11;
    double    const expectedSecond = 12.12;
    octaspire_pair_set(expected, &expectedFirst, &expectedSecond);

    octaspire_pair_t *p = octaspire_pair_new_shallow_copy(
        expected,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    ASSERT(p->first);
    ASSERT(p->second);

    ASSERT_EQ(*(uint32_t const*)expected->first,  *(uint32_t const*)p->first);
    ASSERT_IN_RANGE(*(double const*)expected->second, *(double const*)p->second, 0.000001);

    ASSERT_EQ(sizeof(uint32_t), p->firstSize);
    ASSERT_EQ(sizeof(double),   p->secondSize);
    ASSERT_EQ(0,                p->firstReleaseCallback);
    ASSERT_EQ(0,                p->secondReleaseCallback);
    ASSERT_EQ(octaspireContainerPairTestAllocator,        p->allocator);

    octaspire_pair_release(p);
    p = 0;

    octaspire_pair_release(expected);
    expected = 0;

    PASS();
}

TEST octaspire_pair_new_shallow_copy_failure_on_first_allocation_test(void)
{
    octaspire_pair_t *expected = octaspire_pair_new(
        sizeof(uint32_t),
        false,
        sizeof(double),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(expected);

    uint32_t  const expectedFirst  = 11;
    double    const expectedSecond = 12.12;
    octaspire_pair_set(expected, &expectedFirst, &expectedSecond);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_pair_t *p = octaspire_pair_new_shallow_copy(
        expected,
        octaspireContainerPairTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_pair_release(p);
    p = 0;

    octaspire_pair_release(expected);
    expected = 0;

    PASS();
}

TEST octaspire_pair_new_shallow_copy_failure_on_second_allocation_test(void)
{
    octaspire_pair_t *expected = octaspire_pair_new(
        sizeof(uint32_t),
        false,
        sizeof(double),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(expected);

    uint32_t  const expectedFirst  = 11;
    double    const expectedSecond = 12.12;
    octaspire_pair_set(expected, &expectedFirst, &expectedSecond);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        2,
        0x1);

    ASSERT_EQ(
        2,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_pair_t *p = octaspire_pair_new_shallow_copy(
        expected,
        octaspireContainerPairTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_pair_release(p);
    p = 0;

    octaspire_pair_release(expected);
    expected = 0;

    PASS();
}

TEST octaspire_pair_new_shallow_copy_failure_on_third_allocation_test(void)
{
    octaspire_pair_t *expected = octaspire_pair_new(
        sizeof(uint32_t),
        false,
        sizeof(double),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(expected);

    uint32_t  const expectedFirst  = 11;
    double    const expectedSecond = 12.12;
    octaspire_pair_set(expected, &expectedFirst, &expectedSecond);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireContainerPairTestAllocator,
        3,
        0x3);

    ASSERT_EQ(
        3,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
            octaspireContainerPairTestAllocator));

    octaspire_pair_t *p = octaspire_pair_new_shallow_copy(
        expected,
        octaspireContainerPairTestAllocator);

    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(octaspireContainerPairTestAllocator, 0, 0x00);

    ASSERT_FALSE(p);

    octaspire_pair_release(p);
    p = 0;

    octaspire_pair_release(expected);
    expected = 0;

    PASS();
}

static size_t octaspire_pair_release_test_private_release_callback_for_first_callcount = 0;

static void octaspire_pair_release_test_private_release_callback_for_first(void *element)
{
    OCTASPIRE_HELPERS_UNUSED_PARAMETER(element);
    ++octaspire_pair_release_test_private_release_callback_for_first_callcount;
}

static size_t octaspire_pair_release_test_private_release_callback_for_second_callcount = 0;

static void octaspire_pair_release_test_private_release_callback_for_second(void *element)
{
    OCTASPIRE_HELPERS_UNUSED_PARAMETER(element);
    ++octaspire_pair_release_test_private_release_callback_for_second_callcount;
}

TEST octaspire_pair_release_test(void)
{
    octaspire_pair_release_test_private_release_callback_for_first_callcount  = 0;
    octaspire_pair_release_test_private_release_callback_for_second_callcount = 0;

    octaspire_string_t *second = octaspire_string_new(
        "second element of the pair in octaspire_pair_release_test",
        octaspireContainerPairTestAllocator);

    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(size_t),
        false,
        sizeof(octaspire_string_t*),
        true,
        octaspire_pair_release_test_private_release_callback_for_first,
        octaspire_pair_release_test_private_release_callback_for_second,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    size_t const first  = 11;
    octaspire_pair_set(p, &first, &second);

    ASSERT_EQ(first,  *(size_t const *)p->first);
    ASSERT_EQ(second, *(octaspire_string_t **)p->second);

    octaspire_pair_release(p);
    p = 0;

    octaspire_string_release(second);
    second = 0;

    ASSERT_EQ(1, octaspire_pair_release_test_private_release_callback_for_first_callcount);
    ASSERT_EQ(1, octaspire_pair_release_test_private_release_callback_for_second_callcount);

    PASS();
}

TEST octaspire_pair_get_first_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    long  const expectedFirst = -11;
    short const second        =  12;
    octaspire_pair_set(p, &expectedFirst, &second);

    ASSERT_EQ(expectedFirst, *(long const*)octaspire_pair_get_first(p));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_get_first_const_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    long  const expectedFirst = -11;
    short const second        =  12;
    octaspire_pair_set(p, &expectedFirst, &second);

    ASSERT_EQ(expectedFirst, *(long const*)octaspire_pair_get_first_const(p));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_get_second_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    long  const first           =  11;
    short const expectedSecond  = -12;
    octaspire_pair_set(p, &first, &expectedSecond);

    ASSERT_EQ(expectedSecond, *(short const*)octaspire_pair_get_second(p));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_get_second_const_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    long  const first           =  11;
    short const expectedSecond  = -12;
    octaspire_pair_set(p, &first, &expectedSecond);

    ASSERT_EQ(expectedSecond, *(short const*)octaspire_pair_get_second_const(p));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_get_size_of_first_element_in_octets_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    ASSERT_EQ(sizeof(long), octaspire_pair_get_size_of_first_element_in_octets(p));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_get_size_of_second_element_in_octets_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(long),
        false,
        sizeof(short),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    ASSERT_EQ(sizeof(short), octaspire_pair_get_size_of_second_element_in_octets(p));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_set_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    short const expectedFirst  = 11;
    long  const expectedSecond = 12;
    octaspire_pair_set(p, &expectedFirst, &expectedSecond);

    ASSERT_EQ(expectedFirst,  *(short const *)p->first);
    ASSERT_EQ(expectedSecond, *(long const *) p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_set_first_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    short const expectedFirst  = 11;
    long  const expectedSecond = 0;
    octaspire_pair_set_first(p, &expectedFirst);

    ASSERT_EQ(expectedFirst,  *(short const *)p->first);
    ASSERT_EQ(expectedSecond, *(long const *) p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_set_second_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    short const expectedFirst  = 0;
    long  const expectedSecond = 11;
    octaspire_pair_set_second(p, &expectedSecond);

    ASSERT_EQ(expectedFirst,  *(short const *)p->first);
    ASSERT_EQ(expectedSecond, *(long const *) p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_set_first_to_void_pointer_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(void*),
        true,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    void *expectedFirst = p;
    long  const expectedSecond = 0;
    ASSERT(octaspire_pair_set_first_to_void_pointer(p, expectedFirst));

    ASSERT_EQ(expectedFirst,  *(void **)p->first);
    ASSERT_EQ(expectedSecond, *(long const *)p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_set_first_to_void_pointer_failure_on_element_size_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(char),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    void *ptr = 0;
    ASSERT_FALSE(octaspire_pair_set_first_to_void_pointer(p, ptr));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_set_second_to_void_pointer_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(long),
        false,
        sizeof(void*),
        true,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    void *expectedSecond = p;
    long  const expectedFirst = 0;
    ASSERT(octaspire_pair_set_second_to_void_pointer(p, expectedSecond));

    ASSERT_EQ(expectedFirst,  *(long const *)p->first);
    ASSERT_EQ(expectedSecond, *(void const **)p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_set_second_to_void_pointer_failure_on_element_size_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(long),
        false,
        sizeof(char),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    void *ptr = 0;
    ASSERT_FALSE(octaspire_pair_set_second_to_void_pointer(p, ptr));

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

TEST octaspire_pair_clear_test(void)
{
    octaspire_pair_t *p = octaspire_pair_new(
        sizeof(short),
        false,
        sizeof(long),
        false,
        0,
        0,
        octaspireContainerPairTestAllocator);

    ASSERT(p);

    short const expectedFirst  = 11;
    long  const expectedSecond = 12;
    octaspire_pair_set(p, &expectedFirst, &expectedSecond);

    ASSERT_EQ(11, *(short const*)p->first);
    ASSERT_EQ(12, *(long const*)p->second);

    octaspire_pair_clear(p);

    ASSERT_EQ(0, *(short const*)p->first);
    ASSERT_EQ(0, *(long const*)p->second);

    octaspire_pair_release(p);
    p = 0;

    PASS();
}

GREATEST_SUITE(octaspire_pair_suite)
{
    octaspireContainerPairTestAllocator = octaspire_allocator_new(0);
    assert(octaspireContainerPairTestAllocator);

    RUN_TEST(octaspire_pair_new_short_and_long_test);
    RUN_TEST(octaspire_pair_new_long_and_short_test);
    RUN_TEST(octaspire_pair_new_uint32_t_and_double_test);
    RUN_TEST(octaspire_pair_new_allocation_failure_on_first_allocation_test);
    RUN_TEST(octaspire_pair_new_allocation_failure_on_second_allocation_test);
    RUN_TEST(octaspire_pair_new_allocation_failure_on_third_allocation_test);
    RUN_TEST(octaspire_pair_new_shallow_copy_uint32_t_and_double_test);
    RUN_TEST(octaspire_pair_new_shallow_copy_failure_on_first_allocation_test);
    RUN_TEST(octaspire_pair_new_shallow_copy_failure_on_second_allocation_test);
    RUN_TEST(octaspire_pair_new_shallow_copy_failure_on_third_allocation_test);
    RUN_TEST(octaspire_pair_release_test);
    RUN_TEST(octaspire_pair_get_first_test);
    RUN_TEST(octaspire_pair_get_first_const_test);
    RUN_TEST(octaspire_pair_get_second_test);
    RUN_TEST(octaspire_pair_get_second_const_test);
    RUN_TEST(octaspire_pair_get_size_of_first_element_in_octets_test);
    RUN_TEST(octaspire_pair_get_size_of_second_element_in_octets_test);
    RUN_TEST(octaspire_pair_set_test);
    RUN_TEST(octaspire_pair_set_first_test);
    RUN_TEST(octaspire_pair_set_second_test);
    RUN_TEST(octaspire_pair_set_first_to_void_pointer_test);
    RUN_TEST(octaspire_pair_set_first_to_void_pointer_failure_on_element_size_test);
    RUN_TEST(octaspire_pair_set_second_to_void_pointer_test);
    RUN_TEST(octaspire_pair_set_second_to_void_pointer_failure_on_element_size_test);
    RUN_TEST(octaspire_pair_clear_test);

    octaspire_allocator_release(octaspireContainerPairTestAllocator);
    octaspireContainerPairTestAllocator = 0;
}
