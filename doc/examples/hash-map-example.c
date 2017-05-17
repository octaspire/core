/***********************************************************************
 * To compile this file from the 'examples' directory:
 * c99 -Wall -Wextra -pedantic -I ../../include/ hash-map-example.c
 *     -lm -L ../../build/ -loctaspire-core -o hash-map-example
 **********************************************************************/
#include <stdio.h>
#include <octaspire/core/octaspire_container_utf8_string.h>
#include <octaspire/core/octaspire_container_hash_map.h>

int main(void)
{
    octaspire_memory_allocator_t *allocator =
        octaspire_memory_allocator_new(0);

    octaspire_container_hash_map_t * h =
        octaspire_container_hash_map_new_with_octaspire_container_utf8_string_keys(
            sizeof(float),
            false,
            (octaspire_container_hash_map_element_callback_function_t)0,
            allocator);


    for (size_t i = 0; i < 10; ++i)
    {
        octaspire_container_utf8_string_t *s =
            octaspire_container_utf8_string_new_format(allocator, "Item %zu!", i);

        float const value = i * 3.14;

        if (!octaspire_container_hash_map_put(
            h,
            octaspire_container_utf8_string_get_hash(s),
            &s,
            &value))
        {
            printf("Cannot insert element to hash map\n");
        }
    }

    for (size_t i = 0; i < octaspire_container_hash_map_get_number_of_elements(h); ++i)
    {
        octaspire_container_utf8_string_t *s =
            octaspire_container_utf8_string_new_format(allocator, "Item %zu!", i);

        octaspire_container_hash_map_element_t const * const element =
            octaspire_container_hash_map_get_const(
                h,
                octaspire_container_utf8_string_get_hash(s),
                &s);

        float const value =
            *(float const * const)octaspire_container_hash_map_element_get_value(element);

        printf(
            "%s -> %f\n",
            octaspire_container_utf8_string_get_c_string(s),
            value);

        octaspire_container_utf8_string_release(s);
        s = 0;
    }

    octaspire_container_hash_map_release(h);
    h = 0;

    octaspire_memory_allocator_release(allocator);
    allocator = 0;

    return 0;
}

