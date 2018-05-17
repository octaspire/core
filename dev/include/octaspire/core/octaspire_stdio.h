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
#ifndef OCTASPIRE_STDIO_H
#define OCTASPIRE_STDIO_H

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include "octaspire_memory.h"
#include "octaspire_string.h"

#ifdef __cplusplus
extern "C"       {
#endif

typedef struct octaspire_stdio_t octaspire_stdio_t;

octaspire_stdio_t *octaspire_stdio_new(octaspire_allocator_t *allocator);

void octaspire_stdio_release(octaspire_stdio_t *self);

size_t octaspire_stdio_fread(
    octaspire_stdio_t *self,
    void *ptr,
    size_t const size,
    size_t const nmemb,
    FILE *stream);

void octaspire_stdio_set_number_and_type_of_future_reads_to_be_rigged(
    octaspire_stdio_t *self,
    size_t const count,
    uint32_t const bitQueue);

size_t octaspire_stdio_get_number_of_future_reads_to_be_rigged(
    octaspire_stdio_t const * const self);

octaspire_string_t *octaspire_stdio_read_line(octaspire_stdio_t *self, FILE *stream);

#ifdef __cplusplus
/* extern "C" */ }
#endif

#endif

