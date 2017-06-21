#!/usr/bin/env sh

FILE="$1/octaspire_core_amalgamated.c"

# Remove old file, if created
rm -rf $FILE

# Write license and the top-part of the include guards
cat >> $FILE << EnDoFmEsSaGe
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
*******************************************************************************

  This file is amalgamated version of the header files, implementation files
  and unit tests of Octaspire Core. It is created automatically by a script.

                            DO NOT EDIT MANUALLY!

  Edit the separate .h and .c files in the source distribution and then let
  the script create this file again with the modifications.

******************************************************************************/
#ifndef OCTASPIRE_CORE_AMALGAMATED_H
#define OCTASPIRE_CORE_AMALGAMATED_H

EnDoFmEsSaGe


# Write system includes
cat >> $FILE << EnDoFmEsSaGe

#ifdef OCTASPIRE_PLAN9_IMPLEMENTATION

#include <u.h>
#include <libc.h>
#include <mp.h>
#include <stdio.h>
#include <ctype.h>

typedef long               int32_t;
typedef unsigned long      uint32_t;
typedef char               bool;
typedef char               int8_t;
typedef unsigned char      uint8_t;
typedef long               ptrdiff_t;
typedef unsigned long      size_t;
typedef unsigned long long uintmax_t;

#define true 1
#define false 0

#define CHAR_BIT 8
#define INT32_MAX 2147483647
#define UINTMAX_MAX 0xFFFFFFFF
#define va_copy(x,y) (x) = (y)
#define PRId32 "ld"
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#else

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <assert.h>
#include <limits.h>
#include <inttypes.h>
#include <math.h>
#include <wchar.h>

#endif



#define OCTASPIRE_CORE_CONFIG_TEST_RES_PATH ""


EnDoFmEsSaGe



concat_file() {
INFILE=$1
cat >> $FILE << EnDoFmEsSaGe
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        $INFILE
//////////////////////////////////////////////////////////////////////////////////////////////////
EnDoFmEsSaGe
sed -n '/#include/!p' $INFILE >> $FILE
cat >> $FILE << EnDoFmEsSaGe
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          $INFILE
//////////////////////////////////////////////////////////////////////////////////////////////////



EnDoFmEsSaGe
}



concat_config_file() {
INFILE=$1
cat >> $FILE << EnDoFmEsSaGe
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        $INFILE
//////////////////////////////////////////////////////////////////////////////////////////////////
EnDoFmEsSaGe
sed -n '/#define OCTASPIRE_CORE_CONFIG_TEST_RES_PATH/!p' $INFILE >> $FILE
cat >> $FILE << EnDoFmEsSaGe
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          $INFILE
//////////////////////////////////////////////////////////////////////////////////////////////////



EnDoFmEsSaGe
}




concat_file_literally() {
INFILE=$1
cat >> $FILE << EnDoFmEsSaGe
//////////////////////////////////////////////////////////////////////////////////////////////////
// START OF        $INFILE
//////////////////////////////////////////////////////////////////////////////////////////////////
EnDoFmEsSaGe
cat $INFILE >> $FILE
cat >> $FILE << EnDoFmEsSaGe
//////////////////////////////////////////////////////////////////////////////////////////////////
// END OF          $INFILE
//////////////////////////////////////////////////////////////////////////////////////////////////



EnDoFmEsSaGe
}

cat >> $FILE << EnDoFmEsSaGe
#ifdef OCTASPIRE_CORE_AMALGAMATED_UNIT_TEST_IMPLEMENTATION
#define OCTASPIRE_CORE_AMALGAMATED_IMPLEMENTATION 1
#endif
EnDoFmEsSaGe


concat_file "../external/jenkins_one_at_a_time.h"
concat_config_file "../build/include/octaspire/core/octaspire_core_config.h"
concat_file "../include/octaspire/core/octaspire_utf8.h"
concat_file "../include/octaspire/core/octaspire_memory.h"
concat_file "../include/octaspire/core/octaspire_container_vector.h"
concat_file "../include/octaspire/core/octaspire_container_utf8_string.h"
concat_file "../include/octaspire/core/octaspire_container_pair.h"
concat_file "../include/octaspire/core/octaspire_stdio.h"
concat_file "../include/octaspire/core/octaspire_input.h"
concat_file "../include/octaspire/core/octaspire_container_hash_map.h"
concat_file "../include/octaspire/core/octaspire_helpers.h"










cat >> $FILE << EnDoFmEsSaGe
#ifdef __cplusplus
extern "C" {
#endif

EnDoFmEsSaGe



# Write the bottom-part of the include guards
cat >> $FILE << EnDoFmEsSaGe
#ifdef __cplusplus
}
#endif

#endif

EnDoFmEsSaGe













# Write implementations
cat >> $FILE << EnDoFmEsSaGe







#ifdef OCTASPIRE_CORE_AMALGAMATED_IMPLEMENTATION

EnDoFmEsSaGe




concat_file "../external/jenkins_one_at_a_time.c"
concat_file "../src/octaspire_memory.c"
concat_file "../src/octaspire_helpers.c"
concat_file "../src/octaspire_utf8.c"
concat_file "../src/octaspire_container_vector.c"
concat_file "../src/octaspire_container_utf8_string.c"
concat_file "../src/octaspire_container_pair.c"
concat_file "../src/octaspire_container_hash_map.c"
concat_file "../src/octaspire_input.c"
concat_file "../src/octaspire_stdio.c"




# Write implementations
cat >> $FILE << EnDoFmEsSaGe
#endif // OCTASPIRE_CORE_AMALGAMATED_IMPLEMENTATION

EnDoFmEsSaGe













# Write unit tests
cat >> $FILE << EnDoFmEsSaGe







#ifdef OCTASPIRE_CORE_AMALGAMATED_UNIT_TEST_IMPLEMENTATION

EnDoFmEsSaGe



concat_file_literally "../external/greatest.h"

concat_file "../test/test_helpers.c"
concat_file "../test/test_utf8.c"
concat_file "../test/test_memory.c"
concat_file "../test/test_stdio.c"
concat_file "../test/test_input.c"
concat_file "../test/test_container_vector.c"
concat_file "../test/test_container_utf8_string.c"
concat_file "../test/test_container_pair.c"
concat_file "../test/test_container_hash_map.c"


cat >> $FILE << EnDoFmEsSaGe


void octaspire_core_amalgamated_write_test_file(
    char const * const name,
    char const * const buffer,
    size_t const bufferSize)
{
    FILE *stream = fopen(name, "wb");

    if (!stream)
    {
        abort();
    }

    if (!buffer || !bufferSize)
    {
        if (fwrite("", sizeof(char), 0, stream) != 0)
        {
            fclose(stream);
            stream = 0;
            abort();
        }
    }
    else
    {
        if (fwrite(buffer, sizeof(char), bufferSize, stream) != bufferSize)
        {
            fclose(stream);
            stream = 0;
            abort();
        }
    }

    if (fclose(stream) != 0)
    {
        abort();
    }

    printf("  Wrote file '%s'\n", name);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    // This banner is created with figlet using font 'small'
    unsigned char octaspire_core_amalgamated_version_banner[] = {
      0x20, 0x20, 0x5f, 0x5f, 0x5f, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5f, 0x20,
      0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
      0x20, 0x20, 0x20, 0x5f, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
      0x20, 0x20, 0x20, 0x20, 0x5f, 0x5f, 0x5f, 0x20, 0x20, 0x20, 0x20, 0x20,
      0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x0a, 0x20, 0x2f, 0x20,
      0x5f, 0x20, 0x5c, 0x20, 0x5f, 0x5f, 0x7c, 0x20, 0x7c, 0x5f, 0x20, 0x5f,
      0x5f, 0x20, 0x5f, 0x20, 0x5f, 0x5f, 0x5f, 0x5f, 0x20, 0x5f, 0x5f, 0x28,
      0x5f, 0x29, 0x5f, 0x20, 0x5f, 0x20, 0x5f, 0x5f, 0x5f, 0x20, 0x20, 0x20,
      0x2f, 0x20, 0x5f, 0x5f, 0x7c, 0x5f, 0x5f, 0x5f, 0x20, 0x5f, 0x20, 0x5f,
      0x20, 0x5f, 0x5f, 0x5f, 0x20, 0x0a, 0x7c, 0x20, 0x28, 0x5f, 0x29, 0x20,
      0x2f, 0x20, 0x5f, 0x7c, 0x20, 0x20, 0x5f, 0x2f, 0x20, 0x5f, 0x60, 0x20,
      0x28, 0x5f, 0x2d, 0x3c, 0x20, 0x27, 0x5f, 0x20, 0x5c, 0x20, 0x7c, 0x20,
      0x27, 0x5f, 0x2f, 0x20, 0x2d, 0x5f, 0x29, 0x20, 0x7c, 0x20, 0x28, 0x5f,
      0x5f, 0x2f, 0x20, 0x5f, 0x20, 0x5c, 0x20, 0x27, 0x5f, 0x2f, 0x20, 0x2d,
      0x5f, 0x29, 0x0a, 0x20, 0x5c, 0x5f, 0x5f, 0x5f, 0x2f, 0x5c, 0x5f, 0x5f,
      0x7c, 0x5c, 0x5f, 0x5f, 0x5c, 0x5f, 0x5f, 0x2c, 0x5f, 0x2f, 0x5f, 0x5f,
      0x2f, 0x20, 0x2e, 0x5f, 0x5f, 0x2f, 0x5f, 0x7c, 0x5f, 0x7c, 0x20, 0x5c,
      0x5f, 0x5f, 0x5f, 0x7c, 0x20, 0x20, 0x5c, 0x5f, 0x5f, 0x5f, 0x5c, 0x5f,
      0x5f, 0x5f, 0x2f, 0x5f, 0x7c, 0x20, 0x5c, 0x5f, 0x5f, 0x5f, 0x7c, 0x0a,
      0x20, 0x20, 0x41, 0x6d, 0x61, 0x6c, 0x67, 0x61, 0x6d, 0x61, 0x74, 0x65,
      0x64, 0x20, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f, 0x6e, 0x7c, 0x5f, 0x7c,
      0x73, 0x74, 0x61, 0x6e, 0x64, 0x2d, 0x61, 0x6c, 0x6f, 0x6e, 0x65, 0x20,
      0x75, 0x6e, 0x69, 0x74, 0x20, 0x74, 0x65, 0x73, 0x74, 0x20, 0x72, 0x75,
      0x6e, 0x6e, 0x65, 0x72, 0x20, 0x20, 0x20, 0x20, 0x0a, 0x0a, '\0'
    };

    printf(
        "%s  %s\n\n",
        octaspire_core_amalgamated_version_banner,
        OCTASPIRE_CORE_CONFIG_VERSION_STR);

    printf(
        "  This is stand-alone unit test runner for the amalgamated version of\n"
        "  Octaspire Core. Some of the unit tests test reading of files from\n"
        "  the filesystem. The full source distribution has these files in\n"
        "  the 'test/resource' directory. But because this amalgamated\n"
        "  distribution can have only one file, to be able to run all\n"
        "  the tests succesfully something must be done. What do you\n"
        "  want to do? Select 'a', 'b', 'c' or any other key:\n"
        "\n"
        "  a) Let this program to write those files to disk to the current working\n"
        "     directory. All existing files with the same name will be OVERWRITTEN.\n"
        "     The files to be written are of form 'octaspire_XYZ_test', where XYZ\n"
        "     is the name of the test.\n"
        "\n"
        "  b) Let those tests to fail on missing files, or succeed if the files are\n"
        "     already present in the current working directory.\n"
        "\n"
        "  c) Abort and quit this program.\n"
        "\n"
        "  > ");

    int const c = getchar();

    switch (c)
    {
        case 'a':
        {
            printf("Writing test files to current working directory...\n");

            octaspire_core_amalgamated_write_test_file(
                "octaspire_helpers_path_to_buffer_failure_on_empty_file_test", 0, 0);



            char const octaspire_helpers_path_to_buffer_test[] = {
                0xc2, 0xa9, 0xe2, 0x89, 0xa0, 0xf0, 0x90, 0x80, 0x80
            };
            size_t const octaspire_helpers_path_to_buffer_test_len = 9;

            octaspire_core_amalgamated_write_test_file(
                "octaspire_helpers_path_to_buffer_test",
                octaspire_helpers_path_to_buffer_test,
                octaspire_helpers_path_to_buffer_test_len);


            char const octaspire_input_new_from_path_test[] = {
              0x61, 0x62, 0x63, 0xc2, 0xa9, 0xe2, 0x89, 0xa0, 0xf0, 0x90, 0x80, 0x80
            };
            size_t const octaspire_input_new_from_path_test_len = 12;

            octaspire_core_amalgamated_write_test_file(
                "octaspire_input_new_from_path_test",
                octaspire_input_new_from_path_test,
                octaspire_input_new_from_path_test_len);



            char const octaspire_stdio_fread_test[] = {
              0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x71, 0x77,
              0x65, 0x72, 0x74, 0x79, 0x75, 0x69, 0x6f, 0x70, 0x0a
            };
            size_t const octaspire_stdio_fread_test_len = 21;

            octaspire_core_amalgamated_write_test_file(
                "octaspire_stdio_fread_test",
                octaspire_stdio_fread_test,
                octaspire_stdio_fread_test_len);




            printf("Done.\n");
        }
        break;

        case 'b':
        {
            printf("Tests reading files will fail, if the required files are not available.\n");
        }
        break;

        case 'c':
        default:
        {
            printf("Going to quit now, as requested\n");
            return EXIT_FAILURE;
        }
        break;
    }

    GREATEST_MAIN_BEGIN();
    RUN_SUITE(octaspire_helpers_suite);
    RUN_SUITE(octaspire_utf8_suite);
    RUN_SUITE(octaspire_memory_suite);
    RUN_SUITE(octaspire_stdio_suite);
    RUN_SUITE(octaspire_input_suite);
    RUN_SUITE(octaspire_container_vector_suite);
    RUN_SUITE(octaspire_container_utf8_string_suite);
    RUN_SUITE(octaspire_container_pair_suite);
    RUN_SUITE(octaspire_container_hash_map_suite);
    GREATEST_MAIN_END();
}


#endif // OCTASPIRE_CORE_AMALGAMATED_UNIT_TEST_IMPLEMENTATION

EnDoFmEsSaGe
