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
#ifndef OCTASPIRE_MEMORY_H
#define OCTASPIRE_MEMORY_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct octaspire_region_t;
typedef struct octaspire_memory_allocator_t octaspire_memory_allocator_t;

octaspire_memory_allocator_t *octaspire_memory_allocator_new_create_region(size_t const minBlockSizeInOctets);
octaspire_memory_allocator_t *octaspire_memory_allocator_new(struct octaspire_region_t *region);

void octaspire_memory_allocator_release(octaspire_memory_allocator_t *self);

void *octaspire_memory_allocator_malloc(
    octaspire_memory_allocator_t *self,
    size_t const size);

void *octaspire_memory_allocator_realloc(
    octaspire_memory_allocator_t *self,
    void *ptr, size_t const size);

void octaspire_memory_allocator_free(
    octaspire_memory_allocator_t *self,
    void *ptr);

void octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged(
    octaspire_memory_allocator_t *self,
    size_t const count,
    uint32_t const bitQueue0);

void octaspire_memory_allocator_set_number_and_type_of_future_allocations_to_be_rigged_when_larger_than_32(
    octaspire_memory_allocator_t *self,
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
    uint32_t const bitQueue19);

size_t octaspire_memory_allocator_get_number_of_future_allocations_to_be_rigged(
    octaspire_memory_allocator_t const * const self);

#ifdef __cplusplus
}
#endif

#endif

