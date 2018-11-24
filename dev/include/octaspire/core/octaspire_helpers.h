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
#ifndef OCTASPIRE_HELPERS_H
#define OCTASPIRE_HELPERS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "octaspire_memory.h"
#include "octaspire_stdio.h"

#ifdef __cplusplus
extern "C"       {
#endif

#define OCTASPIRE_HELPERS_UNUSED_PARAMETER(x) (void)(x)

bool  octaspire_helpers_test_bit(uint32_t const bitSet, size_t const index);

char *octaspire_helpers_path_to_buffer(
    char const * const path,
    size_t *octetsAllocated,
    octaspire_allocator_t *allocator,
    octaspire_stdio_t *stdio);

uint32_t octaspire_helpers_calculate_hash_for_size_t_argument(size_t const value);
uint32_t octaspire_helpers_calculate_hash_for_bool_argument(bool const value);
uint32_t octaspire_helpers_calculate_hash_for_int32_t_argument(int32_t const value);
uint32_t octaspire_helpers_calculate_hash_for_double_argument(double const value);
uint32_t octaspire_helpers_calculate_hash_for_void_pointer_argument(void const * const value);

uint32_t octaspire_helpers_calculate_hash_for_memory_buffer_argument(
    void const * const value,
    size_t const lengthInOctets);

size_t octaspire_helpers_character_digit_to_number(uint32_t const c);

size_t octaspire_helpers_min_size_t(size_t const a, size_t const b);
int octaspire_helpers_min_int(int const a, int const b);

size_t octaspire_helpers_min3_size_t(
    size_t const a,
    size_t const b,
    size_t const c);

int octaspire_helpers_min3_int(
    int const a,
    int const b,
    int const c);

size_t octaspire_helpers_max_size_t(size_t const a, size_t const b);

void octaspire_helpers_verify_true(bool const condition);
void octaspire_helpers_verify_null(void const * const ptr);
void octaspire_helpers_verify_not_null(void const * const ptr);

void octaspire_helpers_verify_not_null_void_funptr_void_ptr_const(
        void (*ptr)(void * const));

float octaspire_helpers_maxf(float const a, float const b);
float octaspire_helpers_ceilf(float const value);

bool octaspire_helpers_is_even_size_t(size_t const value);
bool octaspire_helpers_is_odd_size_t( size_t const value);

uint8_t octaspire_helpers_get_char_or_default_from_buf(
    uint8_t const * const input,
    size_t const inLen,
    size_t const getAtIndex,
    uint8_t const defaultChar);

size_t octaspire_helpers_measure_length_of_last_line(
    octaspire_string_t const * const str);

octaspire_vector_t * octaspire_helpers_base64_decode(
    char const * const input,
    int32_t const inputLenOrNegativeToMeasure,
    octaspire_allocator_t * const allocator);

octaspire_string_t * octaspire_helpers_base64_encode(
    char const * const input,
    size_t const inLen,
    size_t const lineLen,
    octaspire_allocator_t * const allocator);

#ifdef __cplusplus
/* extern "C" */ }
#endif

#endif

