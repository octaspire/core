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
#ifndef OCTASPIRE_INPUT_H
#define OCTASPIRE_INPUT_H

#include <stdbool.h>
#include "octaspire_memory.h"
#include "octaspire_stdio.h"

#ifdef __cplusplus
extern "C"       {
#endif

typedef struct octaspire_input_t octaspire_input_t;

octaspire_input_t *octaspire_input_new_from_c_string(
    char const * const str,
    octaspire_allocator_t *allocator);

octaspire_input_t *octaspire_input_new_from_buffer(
    char const * const buffer,
    size_t const lengthInOctets,
    octaspire_allocator_t *allocator);

octaspire_input_t *octaspire_input_new_from_path(
    char const * const path,
    octaspire_allocator_t *octaspireAllocator,
    octaspire_stdio_t *octaspireStdio);

void octaspire_input_release(octaspire_input_t *self);

size_t octaspire_input_get_length_in_ucs_characters(octaspire_input_t const * const self);

void   octaspire_input_clear(octaspire_input_t *self);

void   octaspire_input_rewind(octaspire_input_t *self);

uint32_t octaspire_input_peek_next_ucs_character(octaspire_input_t *self);
uint32_t octaspire_input_peek_next_next_ucs_character(octaspire_input_t *self);

bool octaspire_input_pop_next_ucs_character(octaspire_input_t *self);

bool octaspire_input_is_good(octaspire_input_t const * const self);

bool octaspire_input_push_back_from_string(
    octaspire_input_t * const self,
    octaspire_string_t const * const str);

bool octaspire_input_push_back_from_c_string(octaspire_input_t * const self, char const * const str);

size_t octaspire_input_get_line_number(octaspire_input_t const * const self);
size_t octaspire_input_get_column_number(octaspire_input_t const * const self);
size_t octaspire_input_get_ucs_character_index(octaspire_input_t const * const self);

void octaspire_input_print(octaspire_input_t const * const self);

#ifdef __cplusplus
/* extern "C" */ }
#endif

#endif

