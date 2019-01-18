#include <stdio.h>
#define OCTASPIRE_CORE_AMALGAMATED_IMPLEMENTATION
#include "octaspire-core-amalgamated.c"

void map_example()
{
    octaspire_allocator_t *allocator = octaspire_allocator_new(0);

    octaspire_map_t * h = octaspire_map_new_with_octaspire_string_keys(
        sizeof(float),
        false,
        (octaspire_map_element_callback_t)0,
        allocator);

    for (size_t i = 0; i < 10; ++i)
    {
        octaspire_string_t *s = octaspire_string_new_format(
            allocator,
            "Item %zu!",
            i);

        float const value = i * 3.14f;

        if (!octaspire_map_put(h, octaspire_string_get_hash(s), &s, &value))
        {
            printf("Cannot insert element to hash map\n");
        }
    }

    for (size_t i = 0; i < octaspire_map_get_number_of_elements(h); ++i)
    {
        octaspire_string_t *s = octaspire_string_new_format(
            allocator,
            "Item %zu!",
            i);

        octaspire_map_element_t const * const element =
            octaspire_map_get_const(
                h,
                octaspire_string_get_hash(s),
                &s);

        float const value =
            *(float const * const)octaspire_map_element_get_value(element);

        printf(
            "%s -> %f\n",
            octaspire_string_get_c_string(s),
            value);

        octaspire_string_release(s);
        s = 0;
    }

    octaspire_map_release(h);
    h = 0;

    octaspire_allocator_release(allocator);
    allocator = 0;
}

int main(void)
{
    map_example();
    return 0;
}

