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
#ifndef OCTASPIRE_REGION_H
#define OCTASPIRE_REGION_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct octaspire_region_t octaspire_region_t;

octaspire_region_t *octaspire_region_new(size_t const minBlockSizeInOctets);

void octaspire_region_release(octaspire_region_t *self);

void *octaspire_region_malloc(
    octaspire_region_t *self,
    size_t const size);

void *octaspire_region_realloc(
    octaspire_region_t *self,
    void *ptr, size_t const size);

void octaspire_region_free(
    octaspire_region_t *self,
    void *ptr);

void octaspire_region_compact(octaspire_region_t *self);

void octaspire_region_print(octaspire_region_t const * const self);

#ifdef __cplusplus
}
#endif

#endif

