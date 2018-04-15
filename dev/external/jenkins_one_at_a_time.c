// Based on public domain code from:
// burtleburtle.net/bob/hash/doobs.html

#include "jenkins_one_at_a_time.h"

uint32_t jenkins_one_at_a_time_hash(void const * const data, size_t const lengthInOctets)
{
    uint32_t hash = 0;

    for (size_t i = 0; i < lengthInOctets; ++i)
    {
        hash += ((uint8_t const * const)data)[i];
        hash += (hash << 10);
        hash ^= (hash >>  6);
    }

    hash += (hash <<  3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

