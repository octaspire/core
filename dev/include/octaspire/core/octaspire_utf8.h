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
#ifndef OCTASPIRE_UTF8_H
#define OCTASPIRE_UTF8_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"       {
#endif

typedef enum octaspire_utf8_decode_status_t
{
    OCTASPIRE_UTF8_DECODE_STATUS_OK = 0,
    OCTASPIRE_UTF8_DECODE_STATUS_INPUT_IS_NULL,
    OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS,
    OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER,
    OCTASPIRE_UTF8_DECODE_STATUS_INPUT_NOT_ENOUGH_OCTETS_AVAILABLE
}
octaspire_utf8_decode_status_t;

typedef enum octaspire_utf8_encode_status_t
{
    OCTASPIRE_UTF8_ENCODE_STATUS_OK = 0,
    OCTASPIRE_UTF8_ENCODE_STATUS_ILLEGAL_CHARACTER_NUMBER
}
octaspire_utf8_encode_status_t;

typedef struct octaspire_utf8_character_t
{
    size_t        numoctets;
    unsigned char octets[4];
    char          padding[4];
}
octaspire_utf8_character_t;

octaspire_utf8_encode_status_t octaspire_utf8_encode_character(
    uint32_t const character,
    octaspire_utf8_character_t * const result);

octaspire_utf8_decode_status_t octaspire_utf8_decode_character(
    char const * const text,
    size_t const textLengthInOctets,
    uint32_t *result,
    int *numoctets);

octaspire_utf8_decode_status_t octaspire_utf8_decode_character_from_buffer(
    char const * const buffer,
    size_t const bufferLengthInOctets,
    size_t const currentIndex,
    uint32_t *result,
    int *numoctets);

#ifdef __cplusplus
/* extern "C" */ }
#endif

#endif

