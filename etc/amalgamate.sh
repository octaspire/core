#!/usr/bin/env sh

FILE=octaspire_core_amalgamated.c

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

  This file is amalgamated version of the header files of Octaspire Core.
  It is created automatically by a script.

                            DO NOT EDIT MANUALLY!

  Edit the separate header files and then let the script create this file.

******************************************************************************/
#ifndef OCTASPIRE_CORE_AMALGAMATED_H
#define OCTASPIRE_CORE_AMALGAMATED_H

EnDoFmEsSaGe


# Write system includes
cat >> $FILE << EnDoFmEsSaGe
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


concat_file "../external/murmur3.h"
concat_file "../build/include/octaspire/core/octaspire_core_config.h"
concat_file "../include/octaspire/core/octaspire_utf8.h"
concat_file "../include/octaspire/core/octaspire_memory.h"
concat_file "../include/octaspire/core/octaspire_region.h"
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




concat_file "../external/murmur3.c"
concat_file "../src/octaspire_region.c"
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
concat_file "../test/test_region.c"
concat_file "../test/test_stdio.c"
concat_file "../test/test_input.c"
concat_file "../test/test_container_vector.c"
concat_file "../test/test_container_utf8_string.c"
concat_file "../test/test_container_pair.c"
concat_file "../test/test_container_hash_map.c"


cat >> $FILE << EnDoFmEsSaGe

GREATEST_MAIN_DEFS();

int main(int argc, char **argv)
{
    GREATEST_MAIN_BEGIN();
    RUN_SUITE(octaspire_helpers_suite);
    RUN_SUITE(octaspire_utf8_suite);
    RUN_SUITE(octaspire_memory_suite);
    RUN_SUITE(octaspire_region_suite);
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
