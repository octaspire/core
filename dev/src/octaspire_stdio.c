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
#include "octaspire/core/octaspire_stdio.h"
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include "octaspire/core/octaspire_vector.h"
#include "octaspire/core/octaspire_helpers.h"

struct octaspire_stdio_t
{
    octaspire_allocator_t *allocator;
    size_t   numberOfFutureReadsToBeRigged;
    size_t   bitIndex;
    uint32_t bitQueue;
    char     padding[4];
};

octaspire_stdio_t *octaspire_stdio_new(octaspire_allocator_t *allocator)
{
    size_t const size = sizeof(octaspire_stdio_t);

    octaspire_stdio_t *self = octaspire_allocator_malloc(allocator, size);

    if (!self)
    {
        return self;
    }

    memset(self, 0, size);

    self->allocator = allocator;

    return self;
}

void octaspire_stdio_release(octaspire_stdio_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_allocator_free(self->allocator, self);
}

size_t octaspire_stdio_fread(
    octaspire_stdio_t *self,
    void *ptr,
    size_t const size,
    size_t const nmemb,
    FILE *stream)
{
    if (self->numberOfFutureReadsToBeRigged)
    {
        --(self->numberOfFutureReadsToBeRigged);

        if (!octaspire_helpers_test_bit(self->bitQueue, self->bitIndex))
        {
            ++(self->bitIndex);
            return 0;
        }

        ++(self->bitIndex);
    }

    return fread(ptr, size, nmemb, stream);
}

void octaspire_stdio_set_number_and_type_of_future_reads_to_be_rigged(
    octaspire_stdio_t *self,
    size_t const count,
    uint32_t const bitQueue)
{
    self->numberOfFutureReadsToBeRigged = count;
    self->bitIndex = 0;
    self->bitQueue = bitQueue;
}

size_t octaspire_stdio_get_number_of_future_reads_to_be_rigged(
    octaspire_stdio_t const * const self)
{
    return self->numberOfFutureReadsToBeRigged;
}

octaspire_string_t *octaspire_stdio_read_line(octaspire_stdio_t *self, FILE *stream)
{
    octaspire_vector_t *vec = octaspire_vector_new(
        sizeof(char),
        false,
        0,
        self->allocator);

    while (true)
    {
        int c = fgetc(stream);
        char const ch = (char)c;

        if (c == EOF)
        {
            octaspire_vector_release(vec);
            return 0;
        }
        else if (c == '\n')
        {
            octaspire_vector_push_back_element(vec, &ch);
            break;
        }

        octaspire_vector_push_back_element(vec, &ch);
    }

    octaspire_string_t* result = octaspire_string_new_from_buffer(
        octaspire_vector_get_element_at_const(vec, 0),
        octaspire_vector_get_length_in_octets(vec),
        self->allocator);

    octaspire_vector_release(vec);
    vec = 0;
    return result;
}


