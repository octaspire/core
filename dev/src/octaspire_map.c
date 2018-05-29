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
#include "octaspire/core/octaspire_map.h"
#include "external/jenkins_one_at_a_time.h"
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include "octaspire/core/octaspire_string.h"
#include "octaspire/core/octaspire_vector.h"
#include "octaspire/core/octaspire_pair.h"

#include <stdio.h>


struct octaspire_map_element_t
{
    size_t                        keySizeInOctets;
    void                         *key;
    size_t                        valueSizeInOctets;
    octaspire_vector_t *values;
    octaspire_allocator_t        *allocator;
    uint32_t                      hash;
    bool                          keyIsPointer;
    bool                          valueIsPointer;
    char                          padding[2];
};

octaspire_map_element_t *octaspire_map_element_new(
    uint32_t const hash,
    size_t const keySizeInOctets,
    bool const keyIsPointer,
    void const * const key,
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    void const * const value,
    octaspire_allocator_t * const allocator)
{
    octaspire_map_element_t *self = octaspire_allocator_malloc(
        allocator,
        sizeof(octaspire_map_element_t));

    if (!self)
    {
        return self;
    }

    self->allocator = allocator;
    self->hash = hash;
    self->keySizeInOctets = keySizeInOctets;
    self->keyIsPointer    = keyIsPointer;
    self->key = octaspire_allocator_malloc(self->allocator, self->keySizeInOctets);

    if (!self->key)
    {
        octaspire_map_element_release(self);
        self = 0;
        return 0;
    }

    if (self->key != memcpy(self->key, key, self->keySizeInOctets))
    {
        abort();
    }

    self->valueSizeInOctets = valueSizeInOctets;
    self->valueIsPointer    = valueIsPointer;
    //self->value = octaspire_allocator_malloc(self->allocator, self->valueSizeInOctets);

    self->values = octaspire_vector_new(
        valueSizeInOctets,
        valueIsPointer,
        0,
        allocator);

    if (!self->values)
    {
        octaspire_map_element_release(self);
        self = 0;
        return 0;
    }

    if (!octaspire_vector_push_back_element(self->values, value))
    {
        abort();
    }

    return self;
}

void octaspire_map_element_release(octaspire_map_element_t *self)
{
    if (!self)
    {
        return;
    }

    octaspire_allocator_free(self->allocator, self->key);
    self->key = 0;

    //octaspire_allocator_free(self->allocator, self->value);
    //self->value= 0;

    octaspire_vector_release(self->values);
    self->values = 0;

    octaspire_allocator_free(self->allocator, self);
}

uint32_t octaspire_map_element_get_hash(
    octaspire_map_element_t const * const self)
{
    assert(self);
    return self->hash;
}

void *octaspire_map_element_get_key(
    octaspire_map_element_t const * const self)
{
    assert(self);
    return self->keyIsPointer ? (*(void**)self->key) : self->key;
}

octaspire_vector_t *octaspire_map_element_get_values(
    octaspire_map_element_t * const self)
{
    return self->values;
}

void *octaspire_map_element_get_value(
    octaspire_map_element_t const * const self)
{
    assert(self);
    assert(octaspire_vector_get_length(self->values) < 2);
    return octaspire_vector_get_element_at(self->values, 0);
    //return self->valueIsPointer ? (*(void**)self->value) : self->value;
}

void const *octaspire_map_element_get_key_const(
    octaspire_map_element_t const * const self)
{
    assert(self);
    return self->keyIsPointer ? (*(void const**)self->key) : self->key;
}

void const *octaspire_map_element_get_value_const(
    octaspire_map_element_t const * const self)
{
    assert(self);
    assert(octaspire_vector_get_length(self->values) < 2);
    return octaspire_vector_get_element_at_const(self->values, 0);
}



struct octaspire_map_t
{
    size_t                                                   keySizeInOctets;
    size_t                                                   valueSizeInOctets;
    octaspire_allocator_t                                   *allocator;
    octaspire_vector_t                            *buckets;
    octaspire_map_key_compare_function_t      keyCompareFunction;
    octaspire_map_key_hash_function_t         keyHashFunction;
    octaspire_map_element_callback_t     keyReleaseCallback;
    octaspire_map_element_callback_t     valueReleaseCallback;
    size_t                                                   numBucketsInUse;
    size_t                                                   numElements;
    bool                                                     keyIsPointer;
    bool                                                     valueIsPointer;
    char                                                     padding[6];
};

static size_t const OCTASPIRE_MAP_SMALLEST_SIZE   = 128;
static float  const OCTASPIRE_MAP_MAX_LOAD_FACTOR = 0.75f;

// Prototypes for static functions
static octaspire_vector_t *octaspire_map_private_build_new_buckets(
    octaspire_map_t *self,
    size_t const numBuckets,
    octaspire_allocator_t *allocator);

static float octaspire_map_private_get_load_factor(
    octaspire_map_t const * const self);

static bool octaspire_map_private_rehash(
    octaspire_map_t * const self);

static void octaspire_map_private_release_given_buckets(
    octaspire_map_t *self,
    octaspire_vector_t **bucketsPtr);


static bool octaspire_map_private_rehash(
    octaspire_map_t * const self)
{
    assert(self);

    size_t const oldBucketCount = octaspire_vector_get_length(self->buckets);
    size_t const newBucketCount = oldBucketCount * 2;

    assert(oldBucketCount && newBucketCount);

    octaspire_vector_t *newBuckets =
        octaspire_map_private_build_new_buckets(self, newBucketCount, self->allocator);

    self->numBucketsInUse = 0;
    self->numElements     = 0;

    if (!newBuckets)
    {
        return false;
    }

    for (size_t i = 0; i < oldBucketCount; ++i)
    {
        octaspire_vector_t *oldBucket =
            (octaspire_vector_t*)octaspire_vector_get_element_at(
                self->buckets,
                (ptrdiff_t)i);

        for (size_t j = 0; j < octaspire_vector_get_length(oldBucket); ++j)
        {
            octaspire_map_element_t *element =
                (octaspire_map_element_t*)octaspire_vector_get_element_at(
                    oldBucket,
                    (ptrdiff_t)j);

            uint32_t hash = octaspire_map_element_get_hash(element);

            size_t const bucketIndex = hash % newBucketCount;

            octaspire_vector_t *bucket =
                (octaspire_vector_t*)octaspire_vector_get_element_at(
                    newBuckets,
                    (ptrdiff_t)bucketIndex);

            assert(bucket);

            if (octaspire_vector_is_empty(bucket))
            {
                ++(self->numBucketsInUse);
            }

            if (!octaspire_vector_push_back_element(bucket, &element))
            {
                return false;
            }

            ++(self->numElements);
        }

        octaspire_vector_release(oldBucket);
        oldBucket = 0;
    }

    octaspire_vector_release(self->buckets);
    self->buckets = 0;

    self->buckets = newBuckets;

    assert(octaspire_map_private_get_load_factor(self) <
        OCTASPIRE_MAP_MAX_LOAD_FACTOR);

    return true;
}

static float octaspire_map_private_get_load_factor(
    octaspire_map_t const * const self)
{
    return (float)self->numBucketsInUse / octaspire_vector_get_length(self->buckets);
}

static void octaspire_map_private_release_given_buckets(
    octaspire_map_t *self,
    octaspire_vector_t **bucketsPtr)
{
    assert(self && bucketsPtr && *bucketsPtr);

    octaspire_vector_t *buckets = *bucketsPtr;

    size_t const numBuckets = octaspire_vector_get_length(buckets);

    for (size_t i = 0; i < numBuckets; ++i)
    {
        octaspire_vector_t *bucket =
            (octaspire_vector_t*)octaspire_vector_get_element_at(
                buckets,
                (ptrdiff_t)i);

        assert(bucket);

        for (size_t j = 0; j < octaspire_vector_get_length(bucket); ++j)
        {
            octaspire_map_element_t *element = (octaspire_map_element_t*)
                octaspire_vector_get_element_at(bucket, (ptrdiff_t)j);

            if (self->valueReleaseCallback)
            {
                for (size_t k = 0; k < octaspire_vector_get_length(element->values); ++k)
                {
                    //self->valueReleaseCallback(*(void**)element->value);
                    self->valueReleaseCallback(
                        octaspire_vector_get_element_at(
                            element->values,
                            (ptrdiff_t)k));
                }
            }

            if (self->keyReleaseCallback)
            {
                if (element->keyIsPointer)
                {
                    self->keyReleaseCallback(*(void**)element->key);
                }
                else
                {
                    self->keyReleaseCallback(element->key);
                }
            }

            octaspire_map_element_release(element);
        }

        //octaspire_vector_clear(bucket);
        octaspire_vector_release(bucket);
        bucket = 0;

    }

    octaspire_vector_release(buckets);
    *bucketsPtr = 0;
}

static octaspire_vector_t *octaspire_map_private_build_new_buckets(
    octaspire_map_t *self,
    size_t const numBuckets,
    octaspire_allocator_t *allocator)
{
    octaspire_vector_t *buckets = octaspire_vector_new_with_preallocated_elements(
        sizeof(octaspire_vector_t*),
        true,
        numBuckets,
        0, //(octaspire_vector_element_callback_t)octaspire_vector_release,
        allocator);

    if (!buckets)
    {
        return 0;
    }

    for (size_t i = 0; i < numBuckets; ++i)
    {
        octaspire_vector_t *bucket = octaspire_vector_new(
            sizeof(octaspire_map_element_t *),
            true,
            0, // (octaspire_vector_element_callback_t)octaspire_map_element_release,
            allocator);

        if (!bucket)
        {
            octaspire_map_private_release_given_buckets(self, &buckets);
            assert(!buckets);
            return 0;
        }

        if (!octaspire_vector_push_back_element(buckets, &bucket))
        {
            // This should never happen, because numBuckets buckets are
            // preallocated on the vector. So assert could be
            // used here, but maybe this is still safer?
            octaspire_map_private_release_given_buckets(self, &buckets);
            assert(!buckets);
            return 0;
        }
    }

    assert(octaspire_vector_get_length(buckets) == numBuckets);

    return buckets;
}

octaspire_map_t *octaspire_map_new(
    size_t const keySizeInOctets,
    bool const keyIsPointer,
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    octaspire_map_key_compare_function_t keyCompareFunction,
    octaspire_map_key_hash_function_t keyHashFunction,
    octaspire_map_element_callback_t keyReleaseCallback,
    octaspire_map_element_callback_t valueReleaseCallback,
    octaspire_allocator_t *allocator)
{
    octaspire_map_t *self =
        octaspire_allocator_malloc(allocator, sizeof(octaspire_map_t));

    if (!self)
    {
        return self;
    }

    self->keySizeInOctets      = keySizeInOctets;
    self->keyIsPointer         = keyIsPointer;
    self->valueSizeInOctets    = valueSizeInOctets;
    self->valueIsPointer       = valueIsPointer;
    self->allocator            = allocator;
    self->keyCompareFunction   = keyCompareFunction;
    self->keyHashFunction      = keyHashFunction;
    self->keyReleaseCallback   = keyReleaseCallback;
    self->valueReleaseCallback = valueReleaseCallback;
    self->numBucketsInUse      = 0;
    self->numElements          = 0;

    self->buckets = octaspire_map_private_build_new_buckets(
        self,
        OCTASPIRE_MAP_SMALLEST_SIZE,
        self->allocator);

    if (!self->buckets)
    {
        octaspire_map_release(self);
        self = 0;
        return 0;
    }

    return self;
}

octaspire_map_t *octaspire_map_new_with_octaspire_string_keys(
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    octaspire_map_element_callback_t valueReleaseCallback,
    octaspire_allocator_t *allocator)
{
    return octaspire_map_new(
        sizeof(octaspire_string_t*),
        true,
        valueSizeInOctets,
        valueIsPointer,
        (octaspire_map_key_compare_function_t)octaspire_string_is_equal,
        (octaspire_map_key_hash_function_t)octaspire_string_get_hash,
        (octaspire_map_element_callback_t)octaspire_string_release,
        valueReleaseCallback,
        allocator);
}

static bool octaspire_map_helper_private_size_t_is_equal(
    size_t const * const first,
    size_t const * const second)
{
    return *first == *second;
}

uint32_t octaspire_map_helper_size_t_get_hash(
    size_t const value)
{
    return jenkins_one_at_a_time_hash(&value, sizeof(value));
}

octaspire_map_t *octaspire_map_new_with_size_t_keys(
    size_t const valueSizeInOctets,
    bool const valueIsPointer,
    octaspire_map_element_callback_t valueReleaseCallback,
    octaspire_allocator_t *allocator)
{
    return octaspire_map_new(
        sizeof(size_t),
        false,
        valueSizeInOctets,
        valueIsPointer,
        (octaspire_map_key_compare_function_t)
            octaspire_map_helper_private_size_t_is_equal,
        (octaspire_map_key_hash_function_t)octaspire_map_helper_size_t_get_hash,
        (octaspire_map_element_callback_t)0,
        valueReleaseCallback,
        allocator);
}

void octaspire_map_release(octaspire_map_t *self)
{
    if (!self)
    {
        return;
    }

    if (self->buckets)
    {
        octaspire_map_private_release_given_buckets(self, &(self->buckets));
        assert(!(self->buckets));
    }

    self->buckets = 0;

    octaspire_allocator_free(self->allocator, self);
}

bool octaspire_map_remove(
    octaspire_map_t *self,
    uint32_t const hash,
    void const * const key)
{
    size_t const bucketIndex = hash % octaspire_vector_get_length(self->buckets);

    octaspire_vector_t *bucket =
        (octaspire_vector_t*)octaspire_vector_get_element_at(
            self->buckets,
            (ptrdiff_t)bucketIndex);

    if (!bucket)
    {
        return false;
    }

    size_t const numElementsInBucket = octaspire_vector_get_length(bucket);

    for (size_t i = 0; i < numElementsInBucket; ++i)
    {
        octaspire_map_element_t *element =
            (octaspire_map_element_t*)octaspire_vector_get_element_at(
                bucket,
                (ptrdiff_t)i);

        assert(element);

        void const * key2 = octaspire_map_element_get_key(element);

        if (self->keyCompareFunction(element->keyIsPointer ? *(void const * const *)key : key, key2))
        {
            if (self->valueReleaseCallback)
            {
                for (size_t j = 0; j < octaspire_vector_get_length(element->values); ++j)
                {
                    //self->valueReleaseCallback(*(void**)element->value);
                    self->valueReleaseCallback(
                        octaspire_vector_get_element_at(
                            element->values,
                            (ptrdiff_t)j));
                }
            }

            if (self->keyReleaseCallback)
            {
                if (element->keyIsPointer)
                {
                    self->keyReleaseCallback(*(void**)element->key);
                }
                else
                {
                    self->keyReleaseCallback(element->key);
                }
            }

            octaspire_map_element_release(element);
            if (octaspire_vector_remove_element_at(bucket, (ptrdiff_t)i))
            {
                --(self->numElements);
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    return false;
}

bool octaspire_map_clear(
    octaspire_map_t * const self)
{
    // TODO XXX how to this in best way?

    octaspire_vector_t *buckets = octaspire_map_private_build_new_buckets(
        self,
        OCTASPIRE_MAP_SMALLEST_SIZE,
        self->allocator);

    if (!buckets)
    {
        return false;
    }

    if (self->buckets)
    {
        octaspire_map_private_release_given_buckets(self, &(self->buckets));
        assert(!(self->buckets));
    }

    self->buckets = buckets;

    self->numBucketsInUse = 0;
    self->numElements     = 0;

    return true;
}

bool octaspire_map_add_hash_map(
    octaspire_map_t * const self,
    octaspire_map_t * const other)
{
    bool result = true;

    for (size_t i = 0; i < octaspire_map_get_number_of_elements(other); ++i)
    {
        octaspire_map_element_t *otherElement =
            octaspire_map_get_at_index(other, (ptrdiff_t)i);

        for (size_t j = 0; j < octaspire_vector_get_length(otherElement->values); ++j)
        {
            void * const key   = otherElement->key;
            void * const value = octaspire_vector_get_element_at(
                otherElement->values,
                (ptrdiff_t)j);

            if (!octaspire_map_put(
                self,
                otherElement->hash,
                key,
                &value))
            {
                result = false;
            }
        }
    }

    return result;
}

bool octaspire_map_put(
    octaspire_map_t *self,
    uint32_t const hash,
    void const * const key,
    void const * const value)
{
    assert(self);
    assert(octaspire_vector_get_length(self->buckets));

    octaspire_map_element_t *element =
        octaspire_map_get(self, hash, key);

    if (element)
    {
        return octaspire_vector_push_back_element(element->values, value);
    }
    else
    {
        //octaspire_map_remove(self, hash, key);

        size_t const bucketIndex = hash % octaspire_vector_get_length(self->buckets);

        octaspire_vector_t *bucket =
            (octaspire_vector_t*)octaspire_vector_get_element_at(
                self->buckets,
                (ptrdiff_t)bucketIndex);

        assert(bucket);

        if (octaspire_vector_is_empty(bucket))
        {
            ++(self->numBucketsInUse);
        }

        element = octaspire_map_element_new(
            hash,
            self->keySizeInOctets,
            self->keyIsPointer,
            key,
            self->valueSizeInOctets,
            self->valueIsPointer,
            value,
            self->allocator);

        if (!octaspire_vector_push_back_element(bucket, &element))
        {
            return false;
        }

        ++(self->numElements);

        if (octaspire_map_private_get_load_factor(self) >=
                OCTASPIRE_MAP_MAX_LOAD_FACTOR)
        {
            if (!octaspire_map_private_rehash(self))
            {
                return false;
            }
        }

        return true;
    }
}

octaspire_map_element_t const * octaspire_map_get_const(
    octaspire_map_t const * const self,
    uint32_t const hash,
    void const * const key)
{
    size_t const bucketIndex = hash % octaspire_vector_get_length(self->buckets);

    octaspire_vector_t *bucket =
        (octaspire_vector_t*)octaspire_vector_get_element_at(
            self->buckets,
            (ptrdiff_t)bucketIndex);

    assert(bucket);

    size_t const numElementsInBucket = octaspire_vector_get_length(bucket);

    if (numElementsInBucket == 1)
    {
        octaspire_map_element_t *element = (octaspire_map_element_t*)
            octaspire_vector_peek_front_element(bucket);

        assert(element);

        void const * const key2 = octaspire_map_element_get_key(element);

        if (self->keyCompareFunction(element->keyIsPointer ? *(void const * const *)key : key, key2))
        {
            return element;
        }

        return 0;
    }

    for (size_t i = 0; i < numElementsInBucket; ++i)
    {
        octaspire_map_element_t *element =
            (octaspire_map_element_t*)octaspire_vector_get_element_at(
                bucket,
                (ptrdiff_t)i);

        assert(element);

        void const * const key2 = octaspire_map_element_get_key(element);

        if (self->keyCompareFunction(element->keyIsPointer ? *(void const * const *)key : key, key2))
        {
            return element;
        }
    }

    return 0;
}

octaspire_map_element_t *octaspire_map_get(
    octaspire_map_t *self, uint32_t const hash, void const * const key)
{
    size_t const bucketIndex = hash % octaspire_vector_get_length(self->buckets);

    octaspire_vector_t *bucket =
        (octaspire_vector_t*)octaspire_vector_get_element_at(
            self->buckets,
            (ptrdiff_t)bucketIndex);

    assert(bucket);

    size_t const numElementsInBucket = octaspire_vector_get_length(bucket);

    if (numElementsInBucket == 1)
    {
        octaspire_map_element_t *element = (octaspire_map_element_t*)
            octaspire_vector_peek_front_element(bucket);

        assert(element);

        void const * key2 = octaspire_map_element_get_key(element);

        if (self->keyCompareFunction(element->keyIsPointer ? *(void const * const *)key : key, key2))
        {
            return element;
        }

        return 0;
    }

    for (size_t i = 0; i < numElementsInBucket; ++i)
    {
        octaspire_map_element_t *element =
            (octaspire_map_element_t*)octaspire_vector_get_element_at(
                bucket,
                (ptrdiff_t)i);

        assert(element);

        void const * key2 = octaspire_map_element_get_key(element);

        if (self->keyCompareFunction(element->keyIsPointer ? *(void const * const *)key : key, key2))
        {
            return element;
        }
    }

    return 0;
}

bool octaspire_map_is_empty(octaspire_map_t const * const self)
{
    return (octaspire_map_get_number_of_elements(self) == 0);
}

size_t octaspire_map_get_number_of_elements(octaspire_map_t const * const self)
{
    assert(self);
    return self->numElements;
}

octaspire_map_element_t *octaspire_map_get_at_index(
    octaspire_map_t * const self,
    ptrdiff_t const possiblyNegativeIndex)
{
    if (possiblyNegativeIndex < 0)
    {
        if (octaspire_vector_is_empty(self->buckets))
        {
            return 0;
        }

        size_t index   = (size_t)(-(possiblyNegativeIndex+1));
        size_t counter = 0;
        for (ptrdiff_t i = (ptrdiff_t)octaspire_vector_get_length(self->buckets) - 1; i >= 0; --i)
        {
            octaspire_vector_t * const bucket = (octaspire_vector_t*)
                octaspire_vector_get_element_at(
                    self->buckets,
                    i);

            size_t const bucketSize = octaspire_vector_get_length(bucket);

            if (bucketSize)
            {
                if (index <= (counter + bucketSize - 1))
                {
                    return (octaspire_map_element_t*)
                        octaspire_vector_get_element_at(
                            bucket,
                            -((ptrdiff_t)(index - counter)));
                }

                counter += bucketSize;
            }
        }

        return 0;
    }
    else
    {
        size_t counter = 0;
        for (size_t i = 0; i < octaspire_vector_get_length(self->buckets); ++i)
        {
            octaspire_vector_t * const bucket = (octaspire_vector_t*)
                octaspire_vector_get_element_at(
                    self->buckets,
                    (ptrdiff_t)i);

            size_t const bucketSize = octaspire_vector_get_length(bucket);

            if (bucketSize)
            {
                if ((size_t)possiblyNegativeIndex <= (counter + bucketSize - 1))
                {
                    return (octaspire_map_element_t*)
                        octaspire_vector_get_element_at(
                            bucket,
                            possiblyNegativeIndex - (ptrdiff_t)counter);
                }

                counter += bucketSize;
            }
        }

        return 0;
    }
}

octaspire_map_element_iterator_t
octaspire_map_element_iterator_init(
    octaspire_map_t * const self)
{
    octaspire_map_element_iterator_t iterator;

    iterator.hashMap = self;
    iterator.bucketIndex = 0;
    iterator.elementInsideBucketIndex = 0;
    iterator.element = 0;

    while (!(iterator.element))
    {
        if (iterator.bucketIndex < octaspire_vector_get_length(self->buckets))
        {
            octaspire_vector_t * const bucket = (octaspire_vector_t*)
                octaspire_vector_get_element_at(
                    self->buckets,
                    (ptrdiff_t)(iterator.bucketIndex));

            size_t const bucketSize = octaspire_vector_get_length(bucket);

            for (; iterator.elementInsideBucketIndex < bucketSize; ++(iterator.elementInsideBucketIndex))
            {
                iterator.element = (octaspire_map_element_t*)
                    octaspire_vector_get_element_at(
                        bucket,
                        (ptrdiff_t)(iterator.elementInsideBucketIndex));

                if (iterator.element)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }

        if (iterator.element)
        {
            return iterator;
        }

        ++(iterator.bucketIndex);
        iterator.elementInsideBucketIndex = 0;
    }

    return iterator;
}

bool octaspire_map_element_iterator_next(
    octaspire_map_element_iterator_t * const self)
{
    self->element = 0;
    ++(self->elementInsideBucketIndex);

    while (!(self->element))
    {
        if (self->bucketIndex < octaspire_vector_get_length(self->hashMap->buckets))
        {
            octaspire_vector_t * const bucket = (octaspire_vector_t*)
                octaspire_vector_get_element_at(
                    self->hashMap->buckets,
                    (ptrdiff_t)(self->bucketIndex));

            size_t const bucketSize = octaspire_vector_get_length(bucket);

            for (; self->elementInsideBucketIndex < bucketSize; ++(self->elementInsideBucketIndex))
            {
                self->element = (octaspire_map_element_t*)
                    octaspire_vector_get_element_at(
                        bucket,
                        (ptrdiff_t)(self->elementInsideBucketIndex));

                if (self->element)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }

        if (self->element)
        {
            return self->element != 0;
        }

        ++(self->bucketIndex);
        self->elementInsideBucketIndex = 0;
    }

    return self->element != 0;
}


octaspire_map_element_const_iterator_t
octaspire_map_element_const_iterator_init(
    octaspire_map_t const * const self)
{
    octaspire_map_element_const_iterator_t iterator;

    iterator.hashMap = self;
    iterator.bucketIndex = 0;
    iterator.elementInsideBucketIndex = 0;
    iterator.element = 0;

    while (!(iterator.element))
    {
        if (iterator.bucketIndex < octaspire_vector_get_length(self->buckets))
        {
            octaspire_vector_t const * const bucket =
                (octaspire_vector_t const *)
                octaspire_vector_get_element_at_const(
                    self->buckets,
                    (ptrdiff_t)(iterator.bucketIndex));

            size_t const bucketSize = octaspire_vector_get_length(bucket);

            for (; iterator.elementInsideBucketIndex < bucketSize; ++(iterator.elementInsideBucketIndex))
            {
                iterator.element = (octaspire_map_element_t const *)
                    octaspire_vector_get_element_at_const(
                        bucket,
                        (ptrdiff_t)(iterator.elementInsideBucketIndex));

                if (iterator.element)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }

        if (iterator.element)
        {
            return iterator;
        }

        ++(iterator.bucketIndex);
        iterator.elementInsideBucketIndex = 0;
    }

    return iterator;
}

bool octaspire_map_element_const_iterator_next(
    octaspire_map_element_const_iterator_t * const self)
{
    self->element = 0;
    ++(self->elementInsideBucketIndex);

    while (!(self->element))
    {
        if (self->bucketIndex < octaspire_vector_get_length(self->hashMap->buckets))
        {
            octaspire_vector_t const * const bucket =
                (octaspire_vector_t const *)
                octaspire_vector_get_element_at_const(
                    self->hashMap->buckets,
                    (ptrdiff_t)(self->bucketIndex));

            size_t const bucketSize = octaspire_vector_get_length(bucket);

            for (; self->elementInsideBucketIndex < bucketSize; ++(self->elementInsideBucketIndex))
            {
                self->element = (octaspire_map_element_t const *)
                    octaspire_vector_get_element_at_const(
                        bucket,
                        (ptrdiff_t)(self->elementInsideBucketIndex));

                if (self->element)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }

        if (self->element)
        {
            return self->element != 0;
        }

        ++(self->bucketIndex);
        self->elementInsideBucketIndex = 0;
    }

    return self->element != 0;
}


