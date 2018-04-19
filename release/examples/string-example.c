/****************************************************
 To compile this file from the 'examples' directory:
 c99 -Wall -Wextra -pedantic -I ../../include/ \
     string-example.c -lm -L ../../build/      \
     -loctaspire-core -o string-example
****************************************************/
#include <stdio.h>
#define OCTASPIRE_CORE_AMALGAMATED_IMPLEMENTATION
#include "octaspire-core-amalgamated.c"

int main(void)
{
    octaspire_allocator_t *allocator =
        octaspire_allocator_new(0);

    octaspire_string_t *myStr =
        octaspire_string_new(
            "Hello world!",
            allocator);

    printf(
        "String is \"%s\"\n",
        octaspire_string_get_c_string(
            myStr));

    octaspire_string_release(myStr);
    myStr = 0;

    octaspire_allocator_release(allocator);
    allocator = 0;

    return 0;
}

