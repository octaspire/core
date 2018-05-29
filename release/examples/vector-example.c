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
    octaspire_allocator_t *allocator =
        octaspire_allocator_new(0);

    octaspire_vector_t *v =
        octaspire_vector_new(
            sizeof(octaspire_string_t*),
            true,
            (octaspire_vector_element_callback_t)
                octaspire_string_release,
            allocator);

    for (size_t i = 0; i < 10; ++i)
    {
        octaspire_string_t *s =
            octaspire_string_new_format(
                allocator,
                "Hello %zu world!",
                i);

        if (!octaspire_vector_push_back_element(
                v,
                &s))
        {
            printf("Cannot insert string\n");
        }
    }

    for (size_t i = 0;
         i < octaspire_vector_get_length(v);
         ++i)
    {
        octaspire_string_t const * const s =
            octaspire_vector_get_element_at_const(
                v,
                i);

        printf(
            "String %zu. is: %s\n",
            i,
            octaspire_string_get_c_string(
                s));
    }

    octaspire_vector_release(v);
    v = 0;

    octaspire_allocator_release(allocator);
    allocator = 0;

    return 0;
}

