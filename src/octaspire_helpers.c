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
#include "octaspire/core/octaspire_helpers.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "external/jenkins_one_at_a_time.h"

bool octaspire_helpers_test_bit(uint32_t const bitSet, size_t const index)
{
    assert(index < 32);
    return bitSet & ((uint32_t)0x01 << index);
}

char *octaspire_helpers_path_to_buffer(
    char const * const path,
    size_t *octetsAllocated,
    octaspire_memory_allocator_t *allocator,
    octaspire_stdio_t *stdio)
{
    *octetsAllocated = 0;
    FILE *f = fopen(path, "rb");

    if (!f)
    {
        return 0;
    }

    fseek(f, 0, SEEK_END);

    long const length = ftell(f);

    if (length <= 0)
    {
        fclose(f);
        f = 0;
        return 0;
    }

    fseek(f, 0, SEEK_SET);

    char *result = octaspire_memory_allocator_malloc(allocator, sizeof(char) * (size_t)length);

    if (!result)
    {
        fclose(f);
        f = 0;
        return 0;
    }

    *octetsAllocated = (size_t)length;

    if (*octetsAllocated != octaspire_stdio_fread(stdio, result, sizeof(char), *octetsAllocated, f))
    {
        fclose(f);
        f = 0;
        octaspire_memory_allocator_free(allocator, result);
        result = 0;
        *octetsAllocated = 0;
        return 0;
    }

    fclose(f);
    f = 0;

    return result;
}

uint32_t octaspire_helpers_calculate_hash_for_size_t_argument(size_t const value)
{
    return jenkins_one_at_a_time_hash(&value, sizeof(value));
}

uint32_t octaspire_helpers_calculate_hash_for_bool_argument(bool const value)
{
    return jenkins_one_at_a_time_hash(&value, sizeof(value));
}

uint32_t octaspire_helpers_calculate_hash_for_int32_t_argument(int32_t const value)
{
    return jenkins_one_at_a_time_hash(&value, sizeof(value));
}

uint32_t octaspire_helpers_calculate_hash_for_double_argument(double const value)
{
    return jenkins_one_at_a_time_hash(&value, sizeof(value));
}

uint32_t octaspire_helpers_calculate_hash_for_void_pointer_argument(void const * const value)
{
    return jenkins_one_at_a_time_hash(&value, sizeof(value));
}

size_t octaspire_helpers_character_digit_to_number(uint32_t const c)
{
    return c - '0';
}

size_t octaspire_helpers_min_size_t(size_t const a, size_t const b)
{
    if (a < b)
    {
        return a;
    }

    return b;
}

size_t octaspire_helpers_max_size_t(size_t const a, size_t const b)
{
    if (a > b)
    {
        return a;
    }

    return b;
}

void octaspire_helpers_verify_true(bool const condition)
{
    if (!condition)
    {
        abort();
    }
}

void octaspire_helpers_verify_null(void const * const ptr)
{
    if (ptr)
    {
        abort();
    }
}

void octaspire_helpers_verify_not_null(void const * const ptr)
{
    if (!ptr)
    {
        abort();
    }
}

float octaspire_helpers_maxf(float const a, float const b)
{
    if (a > b)
    {
        return a;
    }

    return b;
}

float octaspire_helpers_ceilf(float const value)
{
    return (float)ceil(value);
}

