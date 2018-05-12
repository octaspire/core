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
#include "octaspire/core/octaspire_utf8.h"
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <string.h>
#include "octaspire/core/octaspire_helpers.h"

typedef enum octaspire_utf8_character_range_t
{
    OCTASPIRE_UTF8_CHARACTER_RANGE_FIRST,
    OCTASPIRE_UTF8_CHARACTER_RANGE_SECOND,
    OCTASPIRE_UTF8_CHARACTER_RANGE_THIRD,
    OCTASPIRE_UTF8_CHARACTER_RANGE_FOURTH,
    OCTASPIRE_UTF8_CHARACTER_RANGE_ILLEGAL
}
octaspire_utf8_character_range_t;

static octaspire_utf8_character_range_t octaspire_utf8_private_rangeof(uint32_t const character);
static uint32_t octaspire_utf8_private_high_order_bits  (octaspire_utf8_character_range_t const range);
static void     octaspire_utf8_private_set_bit          (uint32_t *bitset, size_t const index, bool const on);

static void octaspire_utf8_private_set_bit_of_char(unsigned char *bitset, size_t const index, bool const on);

static bool     octaspire_utf8_private_get_bit          (uint32_t const bitset, size_t const index);
static bool     octaspire_utf8_private_get_bit_of_uint8 (char const bitset, size_t const index);

static int octaspire_utf8_private_octets_in_next(char const * const text, size_t const textLengthInOctets);

static int octaspire_utf8_private_octets_in_next_from_buffer(
    char const * const buffer,
    size_t const lengthInOctets,
    size_t const currentIndex);

octaspire_utf8_decode_status_t octaspire_utf8_private_decode_helper(
    char const * const buffer,
    size_t const numOctetsNeeded,
    size_t const numOctetsAvailable,
    uint32_t * const result);

static uint32_t const octaspire_utf8_private_range1_end   = ((uint32_t)0x007F);

static uint32_t const octaspire_utf8_private_range2_start = ((uint32_t)0x0080);
static uint32_t const octaspire_utf8_private_range2_end   = ((uint32_t)0x07FF);

static uint32_t const octaspire_utf8_private_range3_start = ((uint32_t)0x0800);
static uint32_t const octaspire_utf8_private_range3_end   = ((uint32_t)0xFFFF);

static uint32_t const octaspire_utf8_private_range4_start = ((uint32_t)0x00010000);
static uint32_t const octaspire_utf8_private_range4_end   = ((uint32_t)0x0010FFFF);

static octaspire_utf8_character_range_t octaspire_utf8_private_rangeof(uint32_t const character)
{
    if (character <= octaspire_utf8_private_range1_end)
        return OCTASPIRE_UTF8_CHARACTER_RANGE_FIRST;

    if (character >= octaspire_utf8_private_range2_start && character <= octaspire_utf8_private_range2_end)
        return OCTASPIRE_UTF8_CHARACTER_RANGE_SECOND;

    if (character >= octaspire_utf8_private_range3_start && character <= octaspire_utf8_private_range3_end)
        return OCTASPIRE_UTF8_CHARACTER_RANGE_THIRD;

    if (character >= octaspire_utf8_private_range4_start && character <= octaspire_utf8_private_range4_end)
        return OCTASPIRE_UTF8_CHARACTER_RANGE_FOURTH;

    return OCTASPIRE_UTF8_CHARACTER_RANGE_ILLEGAL;
}

static uint32_t octaspire_utf8_private_high_order_bits(octaspire_utf8_character_range_t const range)
{
    if (range == OCTASPIRE_UTF8_CHARACTER_RANGE_FIRST)
        return 0;

    if (range == OCTASPIRE_UTF8_CHARACTER_RANGE_SECOND)
        return 0xC080;

    if (range == OCTASPIRE_UTF8_CHARACTER_RANGE_THIRD)
        return 0xE08080;

    if (range == OCTASPIRE_UTF8_CHARACTER_RANGE_FOURTH)
        return 0xF0808080;

    // Error, illegal range. Should there be another/better way of reporting it?
    return ((uint32_t)0xFFFFFFFF);
}

static void octaspire_utf8_private_set_bit(uint32_t *bitset, size_t const index, bool const on)
{
    assert(index < 32);

    // INVALID_READ_OF_1
    if (on)
    {
        (*bitset) |= (uint32_t)1 << index;
    }
    else
    {
        (*bitset) &= ~((uint32_t)1 << index);
    }
}

static void octaspire_utf8_private_set_bit_of_char(unsigned char *bitset, size_t const index, bool const on)
{
    assert(index < CHAR_BIT);

    if (on)
    {
        (*bitset) |= (unsigned char)(1 << index);
    }
    else
    {
        (*bitset) &= (unsigned char)(~(1 << index));
    }
}

static bool octaspire_utf8_private_get_bit(uint32_t const bitset, size_t const index)
{
    assert(index < 32);
    return (bitset >> index) & 1;
}

static bool octaspire_utf8_private_get_bit_of_uint8(char const bitset, size_t const index)
{
    assert(index < 8);
    return (((uint8_t)bitset) >> index) & 1;
}

octaspire_utf8_encode_status_t octaspire_utf8_encode_character(
    uint32_t const character,
    octaspire_utf8_character_t * const result)
{
    memset(result->octets, 0, 4);
    result->numoctets = 0;

    // TODO XXX are the upper and lower bounds inclusive or not?
    // Check that and remove the equality operator part if necessary.
    if (character >= 0xD800 && character <= 0xDFFF)
    {
        return OCTASPIRE_UTF8_ENCODE_STATUS_ILLEGAL_CHARACTER_NUMBER;
    }

    octaspire_utf8_character_range_t const range = octaspire_utf8_private_rangeof(character);

    uint32_t bitset = octaspire_utf8_private_high_order_bits(range);

    switch (range)
    {
        case OCTASPIRE_UTF8_CHARACTER_RANGE_FIRST:
        {
            uint32_t const mask = 0x7F;       // Least significant 7 bits on
            bitset |= ((bitset & ~mask) | (character & mask));

            result->numoctets = 1;
        }
        break;

        case OCTASPIRE_UTF8_CHARACTER_RANGE_SECOND:
        {
            uint32_t const mask = 0x3F;     // Least significant 6 bits on
            bitset |= ((bitset & ~mask) | (character & mask));

            uint32_t const bitsetMask = 0x1F00; // Least significant bits 8,9,10,11,12 on
            uint32_t const charMask   = 0x7C0;  // Least significant bits 6,7, 8, 9,10 on
            bitset |= ((bitset & ~bitsetMask) | (((character & charMask) << 2) & bitsetMask));

            result->numoctets = 2;
        }
        break;

        case OCTASPIRE_UTF8_CHARACTER_RANGE_THIRD:
        {
            uint32_t mask = 0x3F;       // Least significant 6 bits on
            bitset |= ((bitset & ~mask) | (character & mask));

            uint32_t bitsetMask = 0x3F00; // Least significant bits 8,9,10,11,12,13 on
            uint32_t charMask   = 0xFC0;  // Least significant bits 6,7, 8, 9,10,11 on
            bitset |= ((bitset & ~bitsetMask) | (((character & charMask) << 2) & bitsetMask));

            bitsetMask = 0xF0000; // Least significant bits 16,17,18,19 on
            charMask   = 0xF000;  // Least significant bits 12,13,14,15 on
            bitset |= ((bitset & ~bitsetMask) | (((character & charMask) << 4) & bitsetMask));

            result->numoctets = 3;
        }
        break;

        case OCTASPIRE_UTF8_CHARACTER_RANGE_FOURTH:
        {
            uint32_t mask = 0x3F;       // Least significant 6 bits on
            bitset |= ((bitset & ~mask) | (character & mask));

            uint32_t bitsetMask = 0x3F00; // Least significant bits 8,9,10,11,12,13 on
            uint32_t charMask   = 0xFC0;  // Least significant bits 6,7, 8, 9,10,11 on
            bitset |= ((bitset & ~bitsetMask) | (((character & charMask) << 2) & bitsetMask));

            bitsetMask = 0x3F0000; // Least significant bits 16,17,18,19,20,21 on
            charMask   = 0x3F000; // Least significant bits 12,13,14,15,16,17 on
            bitset |= ((bitset & ~bitsetMask) | (((character & charMask) << 4) & bitsetMask));

            bitsetMask = 0x7000000; // Least significant bits 24,25,26 on
            charMask   = 0x1C0000;  // Most significant bits 18,19,20 on
            bitset |= ((bitset & ~bitsetMask) | (((character & charMask) << 6) & bitsetMask));

            result->numoctets = 4;
        }
        break;

        case OCTASPIRE_UTF8_CHARACTER_RANGE_ILLEGAL:
        {
            return OCTASPIRE_UTF8_ENCODE_STATUS_ILLEGAL_CHARACTER_NUMBER;
        }
    }

    uint8_t const resultMask = 0xFF; // First 8 bits on
    uint32_t      inputMask  = 0xFF; // Least significant 8 bits on
    result->octets[3] = ((result->octets[3] & ~resultMask) | (bitset & inputMask));

    inputMask  = 0x0000FF00; // Lest significant 8 bits off then 8 bits on
    result->octets[2] = ((result->octets[2] & ~resultMask) | ((bitset & inputMask) >> 8));

    inputMask  = 0x00FF0000; // Least significant 16 bits off then 8 bits on
    result->octets[1] = ((result->octets[1] & ~resultMask) | ((bitset & inputMask) >> 16));

    inputMask  = 0xFF000000; // Least significant 24 bits off then 8 bits on
    result->octets[0] = ((result->octets[0] & ~resultMask) | ((bitset & inputMask) >> 24));

    return OCTASPIRE_UTF8_ENCODE_STATUS_OK;
}

static int octaspire_utf8_private_octets_in_next(char const * const text, size_t const textLengthInOctets)
{
    size_t lengthInOctets = 0;

    if (!text || textLengthInOctets == 0 || text[0] == '\0')
    {
        return 0;
    }

    for (size_t i = 0; i < octaspire_helpers_min_size_t(4, textLengthInOctets); ++i)
    {
        if (text[i] == '\0')
        {
            break;
        }
        else
        {
            ++lengthInOctets;
        }
    }

    return octaspire_utf8_private_octets_in_next_from_buffer(text, lengthInOctets, 0);
}

static int octaspire_utf8_private_octets_in_next_from_buffer(
    char const * const buffer,
    size_t const lengthInOctets,
    size_t const currentIndex)
{
    if (!buffer || currentIndex >= lengthInOctets)
        return 0;

    size_t const octetsAvailable = lengthInOctets - currentIndex;

    if (!octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 7))
    {
        return 1;
    }

    if ( octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 7) &&
         octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 6) &&
        !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 5))
    {
        if (octetsAvailable < 2)
        {
            return -1;
        }

        if ( octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 1], 7) &&
            !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 1], 6))
        {
            return 2;
        }

        return -1;
    }

    if ( octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 7) &&
         octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 6) &&
         octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 5) &&
        !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 4))
    {
        if (octetsAvailable < 3)
        {
            return -1;
        }

        if ( octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 1], 7) &&
            !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 1], 6) &&
             octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 2], 7) &&
            !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 2], 6))
        {
            return 3;
        }

        return -1;
    }

    if ( octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 7) &&
         octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 6) &&
         octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 5) &&
         octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 4) &&
        !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 0], 3))
    {
        if (octetsAvailable < 4)
        {
            return -1;
        }

        if ( octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 1], 7) &&
            !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 1], 6) &&
             octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 2], 7) &&
            !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 2], 6) &&
             octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 3], 7) &&
            !octaspire_utf8_private_get_bit_of_uint8(buffer[currentIndex + 3], 6))
        {
            return 4;
        }

        return -1;
    }

    return -1;
}

octaspire_utf8_decode_status_t octaspire_utf8_private_decode_helper(
    char const * const buffer,
    size_t const numOctetsNeeded,
    size_t const numOctetsAvailable,
    uint32_t * const result)
{
    assert(numOctetsNeeded <= 4);

    if (numOctetsNeeded > numOctetsAvailable || !buffer)
    {
        return OCTASPIRE_UTF8_DECODE_STATUS_INPUT_NOT_ENOUGH_OCTETS_AVAILABLE;
    }

    switch (numOctetsNeeded)
    {
        case 1:
        {
            // 0xxxxxxx

            uint32_t const resultMask = 0x7F; // 7 least significant bits on
            uint8_t  const inputMask  = 0x7F; // 7 least significant bits on
            *result = 0;
            *result |= ((*result & ~resultMask) | (buffer[0] & inputMask));
        }
        break;

        case 2:
        {
            // 110xxxxx 10xxxxxx

            uint32_t resultMask = 0x7C0; // 6 least significant bits off, then 5 on
            uint8_t  inputMask  = 0x1F;  // 5 least significant bits on
            *result = 0;
            *result |= ((*result & ~resultMask) | ((buffer[0] & inputMask) << 6));

            resultMask = 0x3F; // 6 least significant bits on
            inputMask  = 0x3F; // 6 least significant bits on
            *result |= ((*result & ~resultMask) | (buffer[1] & inputMask));

            if (*result <= 0x7F)
            {
                return OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER;
            }
        }
        break;

        case 3:
        {
            // 1110xxxx 10xxxxxx 10xxxxxx

            uint32_t resultMask = 0xF000; // 12 least significant bits off, then 4 on
            uint8_t  inputMask  = 0xF;    // 4 least significant bits on
            *result = 0;
            *result |= ((*result & ~resultMask) | ((buffer[0] & inputMask) << 12));

            resultMask = 0xFC0; // 6 least significant bits off, then 6 on
            inputMask  = 0x3F;  // 6 least significant bits on
            *result |= ((*result & ~resultMask) | ((buffer[1] & inputMask) << 6));

            resultMask = 0x3F; // 6 least significant bits on
            inputMask  = 0x3F; // 6 least significant bits on
            *result |= ((*result & ~resultMask) | (buffer[2] & inputMask));

            if (*result <= 2047)
            {
                return OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER;
            }
        }
        break;

        case 4:
        {
            // 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

            uint32_t resultMask = 0x1C0000; // 18 least significant bits off, then 3 on
            uint8_t  inputMask  = 0x7;      // 3 least significant bits on
            *result = 0;
            *result |= ((*result & ~resultMask) | ((buffer[0] & inputMask) << 18));

            resultMask = 0x3F000; // 12 least significant bits off, then 6 on
            inputMask  = 0x3F;    // 6 least significant bits on
            *result |= ((*result & ~resultMask) | ((buffer[1] & inputMask) << 12));

            resultMask = 0xFC0; // 6 least significant bits off, then 6 on
            inputMask  = 0x3F;  // 6 least significant bits on
            *result |= ((*result & ~resultMask) | ((buffer[2] & inputMask) << 6));

            resultMask = 0x3F; // 6 least significant bits on
            inputMask  = 0x3F; // 6 least significant bits on
            *result |= ((*result & ~resultMask) | (buffer[3] & inputMask));

            if (*result <= 65535)
            {
                return OCTASPIRE_UTF8_DECODE_STATUS_OVERLONG_REPRESENTATION_OF_CHARACTER;
            }
        }
        break;
    }

    return OCTASPIRE_UTF8_DECODE_STATUS_OK;
}

octaspire_utf8_decode_status_t octaspire_utf8_decode_character(
    char const * const text,
    size_t const textLengthInOctets,
    uint32_t *result,
    int *numoctets)
{
    if (!text || textLengthInOctets == 0 || text[0] == '\0')
    {
        *result = 0;
        *numoctets = 0;
        return OCTASPIRE_UTF8_DECODE_STATUS_INPUT_IS_NULL;
    }

    *result = 0;
    *numoctets = octaspire_utf8_private_octets_in_next(text, textLengthInOctets);

    if (*numoctets <= 0 || *numoctets > 4)
    {
        return OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS;
    }

    if ((size_t)(*numoctets) > textLengthInOctets)
    {
        return OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS;
    }

    size_t numOctetsAvailable = 0;

    for (size_t i = 0; i < octaspire_helpers_min_size_t(4, textLengthInOctets); ++i)
    {
        if (text[i] == '\0')
        {
            break;
        }
        else
        {
            ++numOctetsAvailable;
        }
    }

    return octaspire_utf8_private_decode_helper(text, (size_t)*numoctets, numOctetsAvailable, result);
}

octaspire_utf8_decode_status_t octaspire_utf8_decode_character_from_buffer(
    char const * const buffer,
    size_t const bufferLengthInOctets,
    size_t const currentIndex,
    uint32_t *result,
    int *numoctets)
{
    if (!buffer)
    {
        *result = 0;
        *numoctets = 0;
        return OCTASPIRE_UTF8_DECODE_STATUS_INPUT_IS_NULL;
    }

    *result = 0;

    *numoctets =
        octaspire_utf8_private_octets_in_next_from_buffer(buffer, bufferLengthInOctets, currentIndex);

    if (*numoctets <= 0 || *numoctets > 4)
    {
        return OCTASPIRE_UTF8_DECODE_STATUS_ILLEGAL_NUMBER_OF_OCTETS;
    }

    size_t numOctetsAvailable = 0;

    if (bufferLengthInOctets > currentIndex)
    {
        numOctetsAvailable = bufferLengthInOctets - currentIndex;
    }

    return octaspire_utf8_private_decode_helper(buffer, (size_t)*numoctets, numOctetsAvailable, result);
}

