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
#include "octaspire/core/octaspire_input.h"
#include <assert.h>
#include <string.h>
#include "octaspire/core/octaspire_string.h"
#include "octaspire/core/octaspire_helpers.h"

struct octaspire_input_t
{
    octaspire_string_t *text;
    size_t                             index;
    size_t                             line;
    size_t                             column;
    octaspire_allocator_t             *allocator;
};

bool octaspire_input_private_is_ucs_character_index_valid(
    octaspire_input_t const * const self,
    size_t index);

octaspire_input_t *octaspire_input_new_from_c_string(
    char const * const str,
    octaspire_allocator_t *allocator)
{
    return octaspire_input_new_from_buffer(str, str ? strlen(str) : 0, allocator);
}

octaspire_input_t *octaspire_input_new_from_buffer(
    char const * const buffer,
    size_t const lengthInOctets,
    octaspire_allocator_t *allocator)
{
    octaspire_input_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_input_t));

    if (!self)
    {
        return self;
    }

    self->allocator = allocator;

    self->index  = 0;
    self->line   = 1;
    self->column = 1;

    self->text   = octaspire_string_new_from_buffer(buffer, lengthInOctets, self->allocator);

    if (!self->text)
    {
        octaspire_input_release(self);
        self = 0;
        return 0;
    }

    return self;
}

octaspire_input_t *octaspire_input_new_from_path(
    char const * const path,
    octaspire_allocator_t *octaspireAllocator,
    octaspire_stdio_t *octaspireStdio)
{
    size_t octetsAllocated = 0;

    char *buffer = octaspire_helpers_path_to_buffer(
        path,
        &octetsAllocated,
        octaspireAllocator,
        octaspireStdio);

    if (!buffer)
    {
        return 0;
    }

    octaspire_input_t *self = octaspire_input_new_from_buffer(buffer, octetsAllocated, octaspireAllocator);

    octaspire_allocator_free(octaspireAllocator, buffer);
    buffer = 0;

    return self;
}

void octaspire_input_release(octaspire_input_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_string_release(self->text);
    octaspire_allocator_free(self->allocator, self);
}

size_t octaspire_input_get_length_in_ucs_characters(octaspire_input_t const * const self)
{
    return octaspire_string_get_length_in_ucs_characters(self->text);
}

void   octaspire_input_clear(octaspire_input_t *self)
{
    octaspire_string_clear(self->text);
    self->index  = 0;
    self->line   = 1;
    self->column = 1;
}

void   octaspire_input_rewind(octaspire_input_t *self)
{
    self->index  = 0;
    self->line   = 1;
    self->column = 1;
}

uint32_t octaspire_input_peek_next_ucs_character(octaspire_input_t *self)
{
    if (self->index >= octaspire_string_get_length_in_ucs_characters(self->text))
    {
        return 0;
    }

    return octaspire_string_get_ucs_character_at_index(
        self->text,
        (ptrdiff_t)(self->index));
}

uint32_t octaspire_input_peek_next_next_ucs_character(octaspire_input_t *self)
{
    if ((self->index + 1) >= octaspire_string_get_length_in_ucs_characters(self->text))
    {
        return 0;
    }

    return octaspire_string_get_ucs_character_at_index(
        self->text,
        (ptrdiff_t)(self->index + 1));
}

bool octaspire_input_pop_next_ucs_character(octaspire_input_t *self)
{
    if (!octaspire_input_private_is_ucs_character_index_valid(self, self->index))
    {
        return false;
    }

    uint32_t const result =
        octaspire_string_get_ucs_character_at_index(
            self->text,
            (ptrdiff_t)(self->index));

    ++(self->index);

    if (octaspire_input_private_is_ucs_character_index_valid(self, self->index))
    {
        if (result == '\n')
        {
            self->column = 1;
            ++(self->line);
        }
        else
        {
            ++(self->column);
        }
    }

    return true;
}

bool octaspire_input_is_good(octaspire_input_t const * const self)
{
    return self->index < octaspire_string_get_length_in_ucs_characters(self->text);
}

bool octaspire_input_private_is_ucs_character_index_valid(
    octaspire_input_t const * const self,
    size_t index)
{
    return index < octaspire_string_get_length_in_ucs_characters(self->text);
}

bool octaspire_input_push_back_from_string(
    octaspire_input_t * const self,
    octaspire_string_t const * const str)
{
    return octaspire_input_push_back_from_c_string(
        self,
        octaspire_string_get_c_string(str));
}

bool octaspire_input_push_back_from_c_string(octaspire_input_t * const self, char const * const str)
{
    assert(self);
    return octaspire_string_concatenate_c_string(self->text, str);
}

size_t octaspire_input_get_line_number(octaspire_input_t const * const self)
{
    return self->line;
}

size_t octaspire_input_get_column_number(octaspire_input_t const * const self)
{
    return self->column;
}

size_t octaspire_input_get_ucs_character_index(octaspire_input_t const * const self)
{
    return self->index;
}

void octaspire_input_print(octaspire_input_t const * const self)
{
    printf("\n-------------------------- octaspire input --------------------------\n");
    printf("%s", octaspire_string_get_c_string(self->text));
    printf("---------------------------------------------------------------------\n");
}


