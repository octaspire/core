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
#include "../src/octaspire_stdio.c"
#include <assert.h>
#include "external/greatest.h"
#include "octaspire/core/octaspire_stdio.h"
#include "octaspire/core/octaspire_core_config.h"

static octaspire_allocator_t *octaspireStdioTestAllocator = 0;

TEST octaspire_stdio_new_test(void)
{
    octaspire_stdio_t *stdio = octaspire_stdio_new(octaspireStdioTestAllocator);

    ASSERT(stdio);

    ASSERT_EQ(0, stdio->numberOfFutureReadsToBeRigged);
    ASSERT_EQ(0, stdio->bitIndex);
    ASSERT_EQ(0, stdio->bitQueue);
    ASSERT_EQ(octaspireStdioTestAllocator, stdio->allocator);

    octaspire_stdio_release(stdio);
    stdio = 0;

    PASS();
}

TEST octaspire_stdio_new_allocation_failure_test(void)
{
    octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
        octaspireStdioTestAllocator,
        1,
        0);

    ASSERT_EQ(
        1,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireStdioTestAllocator));

    octaspire_stdio_t *stdio = octaspire_stdio_new(octaspireStdioTestAllocator);

    ASSERT_FALSE(stdio);

    ASSERT_EQ(
        0,
        octaspire_allocator_get_number_of_future_allocations_to_be_rigged(octaspireStdioTestAllocator));

    octaspire_stdio_release(stdio);
    stdio = 0;

    PASS();
}

TEST octaspire_stdio_fread_test(void)
{
    octaspire_stdio_t *stdio = octaspire_stdio_new(octaspireStdioTestAllocator);

    ASSERT(stdio);

#ifdef _MSC_VER
    FILE *f = 0;
    errno_t const err =
        fopen_s(&f, OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_stdio_fread_test", "rb");
    ASSERT(!err);
#else
    FILE *f = fopen(OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_stdio_fread_test", "rb");
#endif

    ASSERT(f);

    char octet = 0;
    char const * const expected = "0123456789qwertyuiop";

    for (size_t i = 0; i < strlen(expected); ++i)
    {
        ASSERT_EQ(1, octaspire_stdio_fread(stdio, &octet, sizeof(octet), 1, f));
        ASSERT_EQ(expected[i], octet);
    }

    fclose(f);
    f = 0;

    octaspire_stdio_release(stdio);
    stdio = 0;

    PASS();
}

TEST octaspire_stdio_fread_rigging_and_failure_test(void)
{
    octaspire_stdio_t *stdio = octaspire_stdio_new(octaspireStdioTestAllocator);

    ASSERT(stdio);

#ifdef _MSC_VER
    FILE *f = 0;
    errno_t const err =
        fopen_s(&f, OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_stdio_fread_test", "rb");
    ASSERT(!err);
#else
    FILE *f = fopen(OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "octaspire_stdio_fread_test", "rb");
#endif

    ASSERT(f);

    char octet = 0;
    char const * const expected = "0123456789qwertyuiop";

    // 0101 0101 0101 0101 0101
    //    5    5    5    5    5
    octaspire_stdio_set_number_and_type_of_future_reads_to_be_rigged(stdio, 20, 0x55555);

    ASSERT_EQ(20, octaspire_stdio_get_number_of_future_reads_to_be_rigged(stdio));

    size_t index = 0;
    for (size_t i = 0; i < strlen(expected); ++i)
    {
        if (i % 2)
        {
            ASSERT_EQ(0, octaspire_stdio_fread(stdio, &octet, sizeof(octet), 1, f));
        }
        else
        {
            ASSERT_EQ(1, octaspire_stdio_fread(stdio, &octet, sizeof(octet), 1, f));
            ASSERT_EQ(expected[index], octet);
            ++index;
        }
    }

    ASSERT_EQ(0, octaspire_stdio_get_number_of_future_reads_to_be_rigged(stdio));

    fclose(f);
    f = 0;

    octaspire_stdio_release(stdio);
    stdio = 0;

    PASS();
}

GREATEST_SUITE(octaspire_stdio_suite)
{
    octaspireStdioTestAllocator = octaspire_allocator_new(0);

    assert(octaspireStdioTestAllocator);

    RUN_TEST(octaspire_stdio_new_test);
    RUN_TEST(octaspire_stdio_new_allocation_failure_test);
    RUN_TEST(octaspire_stdio_fread_test);
    RUN_TEST(octaspire_stdio_fread_rigging_and_failure_test);

    octaspire_allocator_release(octaspireStdioTestAllocator);
    octaspireStdioTestAllocator = 0;
}

