/***************************************************
 To compile this file from the 'examples' directory:
 c99 -Wall -Wextra -pedantic              \
     -I ../../include/ vector-example.c   \
     -lm -L ../../build/ -loctaspire-core \
     -o vector-example
***************************************************/
#include <stdio.h>
#define OCTASPIRE_CORE_AMALGAMATED_IMPLEMENTATION
#include "octaspire-core-amalgamated.c"

int main(void)
{
    octaspire_memory_allocator_t *allocator =
        octaspire_memory_allocator_new(0);

    octaspire_container_vector_t *v =
        octaspire_container_vector_new(
            sizeof(octaspire_container_utf8_string_t*),
            true,
            (octaspire_container_vector_element_callback_t)
                octaspire_container_utf8_string_release,
            allocator);

    for (size_t i = 0; i < 10; ++i)
    {
        octaspire_container_utf8_string_t *s =
            octaspire_container_utf8_string_new_format(
                allocator,
                "Hello %zu world!",
                i);

        if (!octaspire_container_vector_push_back_element(
                v,
                &s))
        {
            printf("Cannot insert string to vector\n");
        }
    }

    for (size_t i = 0;
         i < octaspire_container_vector_get_length(v);
         ++i)
    {
        octaspire_container_utf8_string_t const * const s =
            octaspire_container_vector_get_element_at_const(
                v,
                i);

        printf(
            "String %zu. is: %s\n",
            i,
            octaspire_container_utf8_string_get_c_string(
                s));
    }

    octaspire_container_vector_release(v);
    v = 0;

    octaspire_memory_allocator_release(allocator);
    allocator = 0;

    return 0;
}

