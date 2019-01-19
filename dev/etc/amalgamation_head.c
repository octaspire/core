/******************************************************************************
Octaspire Core - Containers and other utility libraries in standard C99
Copyright 2017 - 2019 www.octaspire.com

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
#define INT_MAX 2147483647
#define INT32_MAX 2147483647
#define UINTMAX_MAX 0xFFFFFFFF
#define va_copy(x,y) (x) = (y)
#define PRId32 "ld"
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void exit(int32_t const status)
{
    exits(status == 0 ? "" : "error");
}

int isnan(double const x)
{
    return x != x;
}

#else

#include <ctype.h>
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

#undef OCTASPIRE_CORE_CONFIG_TEST_RES_PATH
#define OCTASPIRE_CORE_CONFIG_TEST_RES_PATH ""

#ifdef OCTASPIRE_CORE_AMALGAMATED_UNIT_TEST_IMPLEMENTATION
#define OCTASPIRE_CORE_AMALGAMATED_IMPLEMENTATION 1
#endif

#ifdef __cplusplus
extern "C" {
#endif

