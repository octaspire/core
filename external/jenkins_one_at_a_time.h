// Based on public domain code from:
// burtleburtle.net/bob/hash/doobs.html
#ifndef OCTASPIRE_CORE_JENKINS_ONE_AT_A_TIME_H
#define OCTASPIRE_CORE_JENKINS_ONE_AT_A_TIME_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t jenkins_one_at_a_time_hash(void const * const data, size_t const lengthInOctets);

#ifdef __cplusplus
}
#endif

#endif

