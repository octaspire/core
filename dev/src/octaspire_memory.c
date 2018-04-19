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
#include "octaspire/core/octaspire_memory.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "octaspire/core/octaspire_helpers.h"

#include <stdio.h> // REMOVE

struct octaspire_allocator_t
{
    size_t                                               numberOfFutureAllocationsToBeRigged;
    size_t                                               bitIndex;
    uint32_t                                             bitQueue[20];
    octaspire_allocator_custom_malloc_function_t  customMallocFunction;
    octaspire_allocator_custom_free_function_t    customFreeFunction;
    octaspire_allocator_custom_realloc_function_t customReallocFunction;
};

octaspire_allocator_config_t octaspire_allocator_config_default(void)
{
    octaspire_allocator_config_t result =
    {
        .customMallocFunction  = 0,
        .customFreeFunction    = 0,
        .customReallocFunction = 0
    };

    return result;
}

octaspire_allocator_t *octaspire_allocator_new(
    octaspire_allocator_config_t const * config)
{
    octaspire_allocator_config_t defaultConfig = octaspire_allocator_config_default();

    if (!config)
    {
        config = &defaultConfig;
    }

    size_t const size = sizeof(octaspire_allocator_t);

    octaspire_allocator_t *self = malloc(size);

    if (!self)
    {
        return self;
    }

    memset(self, 0, size);

    self->numberOfFutureAllocationsToBeRigged = 0;
    self->bitIndex = 0;

    if (self->bitQueue != memset(self->bitQueue, 0, sizeof(self->bitQueue)))
    {
        abort();
    }

    self->customMallocFunction  = config->customMallocFunction;
    self->customFreeFunction    = config->customFreeFunction;
    self->customReallocFunction = config->customReallocFunction;

    return self;
}

void octaspire_allocator_release(octaspire_allocator_t *self)
{
    if (!self)
    {
        return;
    }

    free(self);
}

bool octaspire_allocator_private_test_bit(octaspire_allocator_t const * const self);

bool octaspire_allocator_private_test_bit(octaspire_allocator_t const * const self)
{
    size_t const arrayIndex = (size_t)((float)self->bitIndex / 32.0f);
    size_t const bitIndex   = self->bitIndex % 8;
    assert(bitIndex < 32);
    assert(arrayIndex < (sizeof(self->bitQueue) / sizeof(self->bitQueue[0])));
    return octaspire_helpers_test_bit(self->bitQueue[arrayIndex], bitIndex);
}

void *octaspire_allocator_malloc(
    octaspire_allocator_t *self,
    size_t const size)
{
    if (self->numberOfFutureAllocationsToBeRigged)
    {
        --(self->numberOfFutureAllocationsToBeRigged);

        if (!octaspire_allocator_private_test_bit(self))
        {
            ++(self->bitIndex);
            return 0;
        }

        ++(self->bitIndex);
    }

    assert(size);

    void * const result =
        self->customMallocFunction ? self->customMallocFunction(size) : malloc(size);

    if (!result)
    {
        return result;
    }

    if (!self->customMallocFunction)
    {
        if (result != memset(result, 0, size))
        {
            abort();
        }
    }

    return result;
}

void *octaspire_allocator_realloc(
    octaspire_allocator_t *self,
    void *ptr, size_t const size)
{
    if (self->numberOfFutureAllocationsToBeRigged)
    {
        --(self->numberOfFutureAllocationsToBeRigged);

        if (!octaspire_allocator_private_test_bit(self))
        {
            ++(self->bitIndex);
            return 0;
        }

        ++(self->bitIndex);
    }

    return self->customReallocFunction ? self->customReallocFunction(ptr, size) : realloc(ptr, size);
}

void octaspire_allocator_free(
    octaspire_allocator_t *self,
    void *ptr)
{
    assert(self);

    self->customFreeFunction ? self->customFreeFunction(ptr) : free(ptr);
}

void octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
    octaspire_allocator_t *self,
    size_t const count,
    uint32_t const bitQueue0)
{
    assert(count <= 32);
    self->numberOfFutureAllocationsToBeRigged = count;
    self->bitIndex  = 0;

    if (self->bitQueue != memset(self->bitQueue, 0, sizeof(self->bitQueue)))
    {
        abort();
    }

    self->bitQueue[0] = bitQueue0;
}

void octaspire_allocator_set_number_and_type_of_future_allocations_to_be_rigged_when_larger_than_32(
    octaspire_allocator_t *self,
    size_t const count,
    uint32_t const bitQueue0,
    uint32_t const bitQueue1,
    uint32_t const bitQueue2,
    uint32_t const bitQueue3,
    uint32_t const bitQueue4,
    uint32_t const bitQueue5,
    uint32_t const bitQueue6,
    uint32_t const bitQueue7,
    uint32_t const bitQueue8,
    uint32_t const bitQueue9,
    uint32_t const bitQueue10,
    uint32_t const bitQueue11,
    uint32_t const bitQueue12,
    uint32_t const bitQueue13,
    uint32_t const bitQueue14,
    uint32_t const bitQueue15,
    uint32_t const bitQueue16,
    uint32_t const bitQueue17,
    uint32_t const bitQueue18,
    uint32_t const bitQueue19)
{
    assert(count <= 640);
    self->numberOfFutureAllocationsToBeRigged = count;
    self->bitIndex = 0;

    if (self->bitQueue != memset(self->bitQueue, 0, sizeof(self->bitQueue)))
    {
        abort();
    }

    self->bitQueue[0]  = bitQueue0;
    self->bitQueue[1]  = bitQueue1;
    self->bitQueue[2]  = bitQueue2;
    self->bitQueue[3]  = bitQueue3;
    self->bitQueue[4]  = bitQueue4;
    self->bitQueue[5]  = bitQueue5;
    self->bitQueue[6]  = bitQueue6;
    self->bitQueue[7]  = bitQueue7;
    self->bitQueue[8]  = bitQueue8;
    self->bitQueue[9]  = bitQueue9;
    self->bitQueue[10] = bitQueue10;
    self->bitQueue[11] = bitQueue11;
    self->bitQueue[12] = bitQueue12;
    self->bitQueue[13] = bitQueue13;
    self->bitQueue[14] = bitQueue14;
    self->bitQueue[15] = bitQueue15;
    self->bitQueue[16] = bitQueue16;
    self->bitQueue[17] = bitQueue17;
    self->bitQueue[18] = bitQueue18;
    self->bitQueue[19] = bitQueue19;
}

size_t octaspire_allocator_get_number_of_future_allocations_to_be_rigged(
    octaspire_allocator_t const * const self)
{
    return self->numberOfFutureAllocationsToBeRigged;
}

