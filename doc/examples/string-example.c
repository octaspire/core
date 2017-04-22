/***********************************************************************
 * To compile this file from the 'examples' directory:
 * c99 -Wall -Wextra -pedantic -I ../../include/ string-example.c
 *     -lm -L ../../build/ -loctaspire_core -o string-example
 **********************************************************************/
#include <stdio.h>
#include <octaspire/core/octaspire_container_utf8_string.h>

int main(void)
{
    octaspire_memory_allocator_t *allocator =
        octaspire_memory_allocator_new(0);

    octaspire_container_utf8_string_t *myStr =
        octaspire_container_utf8_string_new("Hello world!", allocator);

    printf(
        "String is \"%s\"\n",
        octaspire_container_utf8_string_get_c_string(myStr));

    octaspire_container_utf8_string_release(myStr);
    myStr = 0;

    octaspire_memory_allocator_release(allocator);
    allocator = 0;

    return 0;
}

