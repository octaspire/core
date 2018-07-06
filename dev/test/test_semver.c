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
#include <assert.h>
#include "../src/octaspire_semver.c"
#include "external/greatest.h"
#include "octaspire/core/octaspire_memory.h"
#include "octaspire/core/octaspire_semver.h"
#include "octaspire/core/octaspire_core_config.h"

static octaspire_allocator_t *octaspireSemverTestAllocator = 0;

TEST octaspire_semver_pre_release_elem_type_accessors_called_on_lexical_type_test(void)
{
    char const * const expected = "qwerty";

    octaspire_semver_pre_release_elem_t * elem =
        octaspire_semver_pre_release_elem_new_from_c_string(
            expected,
            octaspireSemverTestAllocator);

    ASSERT(elem);

    ASSERT_EQ(
        OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL,
        octaspire_semver_pre_release_elem_get_type(elem));

    ASSERT_STR_EQ(
        expected,
        octaspire_semver_pre_release_elem_get_lexical_value_as_c_string(elem));

    ASSERT_FALSE(octaspire_semver_pre_release_elem_is_numerical_type(elem));
    ASSERT(octaspire_semver_pre_release_elem_is_lexical_type(elem));

    octaspire_semver_pre_release_elem_release(elem);
    elem = 0;

    PASS();
}

TEST octaspire_semver_pre_release_elem_type_accessors_called_on_numerical_type_test(void)
{
    size_t const expected = 123;

    octaspire_semver_pre_release_elem_t * elem =
        octaspire_semver_pre_release_elem_numerical_new(
            expected,
            octaspireSemverTestAllocator);

    ASSERT(elem);

    ASSERT_EQ(
        OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL,
        octaspire_semver_pre_release_elem_get_type(elem));

    ASSERT_EQ(
        expected,
        octaspire_semver_pre_release_elem_get_numerical_value(elem));

    ASSERT(octaspire_semver_pre_release_elem_is_numerical_type(elem));
    ASSERT_FALSE(octaspire_semver_pre_release_elem_is_lexical_type(elem));

    octaspire_semver_pre_release_elem_release(elem);
    elem = 0;

    PASS();
}

TEST octaspire_semver_pre_release_elem_new_copy_called_with_numerical_type_test(void)
{
    size_t const expected = 321;

    octaspire_semver_pre_release_elem_t * elem1 =
        octaspire_semver_pre_release_elem_numerical_new(
            expected,
            octaspireSemverTestAllocator);

    ASSERT(elem1);

    octaspire_semver_pre_release_elem_t * elem2 =
        octaspire_semver_pre_release_elem_new_copy(
            elem1,
            octaspireSemverTestAllocator);

    ASSERT(elem2);

    ASSERT_EQ(
        OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL,
        octaspire_semver_pre_release_elem_get_type(elem2));

    ASSERT_EQ(
        expected,
        octaspire_semver_pre_release_elem_get_numerical_value(elem2));

    octaspire_semver_pre_release_elem_release(elem1);
    elem1 = 0;

    octaspire_semver_pre_release_elem_release(elem2);
    elem2 = 0;

    PASS();
}

TEST octaspire_semver_pre_release_elem_new_copy_called_with_lexcal_type_test(void)
{
     char const * const expected = "ytrewq";

    octaspire_semver_pre_release_elem_t * elem1 =
        octaspire_semver_pre_release_elem_new_from_c_string(
            expected,
            octaspireSemverTestAllocator);

    ASSERT(elem1);

    octaspire_semver_pre_release_elem_t * elem2 =
        octaspire_semver_pre_release_elem_new_copy(
            elem1,
            octaspireSemverTestAllocator);

    ASSERT(elem2);

    ASSERT_EQ(
        OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL,
        octaspire_semver_pre_release_elem_get_type(elem2));

    ASSERT_STR_EQ(
        expected,
        octaspire_semver_pre_release_elem_get_lexical_value_as_c_string(elem2));

    octaspire_semver_pre_release_elem_release(elem1);
    elem1 = 0;

    octaspire_semver_pre_release_elem_release(elem2);
    elem2 = 0;

    PASS();
}

TEST octaspire_semver_pre_release_elem_make_numerical_and_lexical_test(void)
{
    octaspire_semver_pre_release_elem_t * elem =
        octaspire_semver_pre_release_elem_new_from_c_string(
            "qwerty",
            octaspireSemverTestAllocator);

    ASSERT(elem);

    size_t const expectedNum = 123;

    octaspire_semver_pre_release_elem_make_numerical(elem, expectedNum);

    ASSERT_EQ(
        OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL,
        octaspire_semver_pre_release_elem_get_type(elem));

    ASSERT_EQ(expectedNum, octaspire_semver_pre_release_elem_get_numerical_value(elem));

    char const * const expectedStr = "abc";

    ASSERT(octaspire_semver_pre_release_elem_make_lexical(elem, expectedStr));

    ASSERT_EQ(
        OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL,
        octaspire_semver_pre_release_elem_get_type(elem));

    ASSERT_STR_EQ(
        expectedStr,
        octaspire_semver_pre_release_elem_get_lexical_value_as_c_string(elem));

    octaspire_semver_pre_release_elem_release(elem);
    elem = 0;

    PASS();
}


TEST octaspire_semver_new_called_with_null_allocator_test(void)
{
    octaspire_vector_t * preRelease =
        octaspire_vector_new(
            sizeof(octaspire_string_t*),
            true,
            (octaspire_vector_element_callback_t)octaspire_string_release,
            octaspireSemverTestAllocator);

    ASSERT(preRelease);

    octaspire_vector_t * buildMetadata =
        octaspire_vector_new(
            sizeof(octaspire_string_t*),
            true,
            (octaspire_vector_element_callback_t)octaspire_string_release,
            octaspireSemverTestAllocator);

    ASSERT(buildMetadata);

    octaspire_semver_t * semver =
        octaspire_semver_new(
            0,
            0,
            0,
            preRelease,
            buildMetadata,
            0);

    ASSERT_EQ(semver, 0);

    octaspire_vector_release(preRelease);
    preRelease = 0;

    octaspire_vector_release(buildMetadata);
    buildMetadata = 0;

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}

TEST octaspire_semver_new_prerelease_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver);

    octaspire_string_t * str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-alpha.3"));
    octaspire_string_release(str);
    str = 0;

    ASSERT(octaspire_semver_add_buildmetadata(semver, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver, "5214f"));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-alpha.3+sha.5214f"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}

TEST octaspire_semver_new_copy_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);

    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    octaspire_semver_t * semver2 = octaspire_semver_new_copy(
        semver1,
        octaspireSemverTestAllocator);

    ASSERT(semver2);
    ASSERT(octaspire_semver_is_equal_to(semver1, semver2));

    octaspire_string_t * str1 = octaspire_semver_to_string(semver1);
    ASSERT(str1);
    ASSERT(octaspire_string_is_equal_to_c_string(str1, "0.1.2-alpha.3+sha.5214f"));

    octaspire_string_t * str2 = octaspire_semver_to_string(semver2);
    ASSERT(str2);
    ASSERT(octaspire_string_is_equal(str1, str2));

    octaspire_string_release(str1);
    str1 = 0;

    octaspire_string_release(str2);
    str2 = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;

    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_get_build_metadata_at_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver);

    ASSERT(octaspire_semver_add_buildmetadata(semver, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver, "5214f"));

    ASSERT_EQ(0,           octaspire_semver_get_build_metadata_at(semver, 3));
    ASSERT_EQ(0,           octaspire_semver_get_build_metadata_at(semver, 2));
    ASSERT_STR_EQ("5214f", octaspire_semver_get_build_metadata_at(semver, 1));
    ASSERT_STR_EQ("sha",   octaspire_semver_get_build_metadata_at(semver, 0));

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}

TEST octaspire_semver_get_prerelease_at_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver);

    ASSERT(octaspire_semver_add_buildmetadata(semver, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver, "5214f"));

    size_t       numerical = 0;
    char const * lexical   = 0;

    octaspire_semver_pre_release_elem_type_t elemType =
        octaspire_semver_get_prerelease_at(semver, 0, &numerical, &lexical);

    ASSERT_EQ(OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_LEXICAL, elemType);
    ASSERT(lexical);
    ASSERT_EQ(0, numerical);
    ASSERT_STR_EQ("alpha", lexical);

    numerical = 0;
    lexical   = 0;

    elemType =
        octaspire_semver_get_prerelease_at(semver, 1, &numerical, &lexical);

    ASSERT_EQ(OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_NUMERICAL, elemType);
    ASSERT_EQ(0, lexical);
    ASSERT_EQ(3, numerical);

    numerical = 0;
    lexical   = 0;

    elemType =
        octaspire_semver_get_prerelease_at(semver, 2, &numerical, &lexical);

    ASSERT_EQ(OCTASPIRE_SEMVER_PRE_RELEASE_ELEM_TYPE_UNKNOWN, elemType);
    ASSERT_EQ(0, lexical);
    ASSERT_EQ(0, numerical);

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}

TEST octaspire_semver_get_length_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver);

    ASSERT(octaspire_semver_add_buildmetadata(semver, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver, "5214f"));

    ASSERT_EQ(7, octaspire_semver_get_length(semver));

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}

TEST octaspire_semver_get_major_minor_patch_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver);

    ASSERT(octaspire_semver_add_buildmetadata(semver, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver, "5214f"));

    ASSERT_EQ(0, octaspire_semver_get_major(semver));
    ASSERT_EQ(1, octaspire_semver_get_minor(semver));
    ASSERT_EQ(2, octaspire_semver_get_patch(semver));

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_3_metadata_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ(0, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ(0, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214g_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214g"));

    ASSERT_EQ(0, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ(0, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_2_alpha_4_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "4",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ(-1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ( 1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_4_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "4",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ( 1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ(-1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alphb_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alphb",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ( 1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ(-1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_2_alphb_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alphb",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ(-1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ( 1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_3_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            3,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ( 1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ(-1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_3_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            3,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ(-1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ( 1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_2_2_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            2,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ( 1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ(-1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_2_2_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            2,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ(-1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ( 1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_1_1_2_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ( 1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ(-1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_1_1_2_alpha_3_sha_5214f_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver1);
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver1, "5214f"));

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            1,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver2);
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver2, "5214f"));

    ASSERT_EQ(-1, octaspire_semver_compare(semver1, semver2));
    ASSERT_EQ( 1, octaspire_semver_compare(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_0_0_alpha_and_1_0_0_alpha_1_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "alpha",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "alpha",
            "1",
            "");

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_0_0_alpha_1_and_1_0_0_alpha_beta_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "alpha",
            "1",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "alpha",
            "beta",
            "");

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_0_0_alpha_beta_and_1_0_0_beta_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "alpha",
            "beta",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "beta",
            "");

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_0_0_beta_and_1_0_0_beta_2_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "beta",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "beta",
            "2",
            "");

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_0_0_beta_2_and_1_0_0_beta_11_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "beta",
            "2",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "beta",
            "11",
            "");

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_0_0_beta_11_and_1_0_0_rc_1_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "beta",
            "11",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_0_0_rc_1_and_1_0_0_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            1,
            0,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_3_0_1_rc_1_and_3_0_1_rc_1_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            3,
            0,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            3,
            0,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver2);

    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_comparison_operators_called_with_1_9_0_and_1_10_0_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new(
            1,
            9,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver1);

    // Second
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            1,
            10,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Regular.
    ASSERT(octaspire_semver_is_smaller_than(semver1, semver2));
    ASSERT(octaspire_semver_is_smaller_or_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_than(semver1, semver2));
    ASSERT_FALSE(octaspire_semver_is_greater_or_equal_to(semver1, semver2));

    // Reverse order.
    ASSERT_FALSE(octaspire_semver_is_smaller_than(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_smaller_or_equal_to(semver2, semver1));
    ASSERT_FALSE(octaspire_semver_is_equal_to(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_than(semver2, semver1));
    ASSERT(octaspire_semver_is_greater_or_equal_to(semver2, semver1));

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_is_equal_to_c_string_called_with_1_9_0_and_same_and_five_different_test(void)
{
    // First
    octaspire_semver_t * semver1 =
        octaspire_semver_new(
            1,
            9,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver1);

    ASSERT(octaspire_semver_is_equal_to_c_string(semver1, "1.9.0"));
    ASSERT_FALSE(octaspire_semver_is_equal_to_c_string(semver1, "1.9.1"));
    ASSERT_FALSE(octaspire_semver_is_equal_to_c_string(semver1, "1.10.0"));
    ASSERT_FALSE(octaspire_semver_is_equal_to_c_string(semver1, "2.9.0"));
    ASSERT_FALSE(octaspire_semver_is_equal_to_c_string(semver1, "1.9.0-rc"));
    ASSERT_FALSE(octaspire_semver_is_equal_to_c_string(semver1, "1.9.0-rc.1"));

    octaspire_semver_release(semver1);
    semver1 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_0_0_rc_1_and_0_0_1_and_true_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            0,
            0,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.0.1-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_0_1_rc_1_and_0_1_0_and_true_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            0,
            1,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.0-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_1_0_0_and_true_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            1,
            0,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "2.0.0-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_and_0_0_0_rc_1_and_true_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new(
            1,
            1,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            0,
            0,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");


    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_and_1_1_1_and_true_failure_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new(
            1,
            1,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            1,
            1,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT_FALSE(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_and_1_1_0_and_true_failure_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new(
            1,
            1,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            1,
            1,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT_FALSE(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_and_1_0_1_and_true_failure_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new(
            1,
            1,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            1,
            0,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT_FALSE(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_and_0_1_1_and_true_failure_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new(
            1,
            1,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            0,
            1,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT_FALSE(octaspire_semver_add_or_subtract(semver1, semver2, true));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_0_0_rc_1_and_0_0_1_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            0,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            0,
            0,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT_FALSE(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.0.0-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_0_1_rc_1_and_0_0_1_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            0,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            0,
            0,
            1,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.0.0-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_1_0_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            0,
            1,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.0.1-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_1_0_0_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new(
            1,
            0,
            0,
            0,
            0,
            octaspireSemverTestAllocator);

    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.1-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_rc_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            0,
            0,
            octaspireSemverTestAllocator,
            "rc",
            "");


    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1-1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_1_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            0,
            0,
            octaspireSemverTestAllocator,
            "1",
            "");


    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1-rc"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_rc_1_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            0,
            0,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");


    ASSERT(semver2);

    // Add.
    ASSERT(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_ra_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            0,
            0,
            octaspireSemverTestAllocator,
            "ra",
            "");


    ASSERT(semver2);

    // Add.
    ASSERT_FALSE(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_2_and_false_test(void)
{
    // Target.
    octaspire_semver_t * semver1 =
        octaspire_semver_new_prerelease(
            1,
            1,
            1,
            octaspireSemverTestAllocator,
            "rc",
            "1",
            "");

    ASSERT(semver1);

    // To be added.
    octaspire_semver_t * semver2 =
        octaspire_semver_new_prerelease(
            0,
            0,
            0,
            octaspireSemverTestAllocator,
            "2",
            "");


    ASSERT(semver2);

    // Add.
    ASSERT_FALSE(octaspire_semver_add_or_subtract(semver1, semver2, false));

    // Check result of addition.
    octaspire_string_t * str = octaspire_semver_to_string(semver1);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "1.1.1-rc.1"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver1);
    semver1 = 0;
    octaspire_semver_release(semver2);
    semver2 = 0;

    PASS();
}

TEST octaspire_semver_pop_back_called_on_prerelease_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver);

    ASSERT(octaspire_semver_add_buildmetadata(semver, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver, "5214f"));

    ASSERT(octaspire_semver_pop_back(semver));

    octaspire_string_t * str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-alpha.3+sha"));
    octaspire_string_release(str);
    str = 0;

    ASSERT(octaspire_semver_pop_back(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-alpha.3"));
    octaspire_string_release(str);
    str = 0;

    ASSERT(octaspire_semver_pop_back(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-alpha"));
    octaspire_string_release(str);
    str = 0;

    ASSERT(octaspire_semver_pop_back(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2"));
    octaspire_string_release(str);
    str = 0;

    // This should not have any effect anymore.
    ASSERT(octaspire_semver_pop_back(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}

TEST octaspire_semver_pop_front_called_on_prerelease_0_1_2_alpha_3_and_metadata_sha_5214f_test(void)
{
    octaspire_semver_t * semver =
        octaspire_semver_new_prerelease(
            0,
            1,
            2,
            octaspireSemverTestAllocator,
            "alpha",
            "3",
            "");

    ASSERT(semver);

    ASSERT(octaspire_semver_add_buildmetadata(semver, "sha"));
    ASSERT(octaspire_semver_add_buildmetadata(semver, "5214f"));

    ASSERT(octaspire_semver_pop_front(semver));

    octaspire_string_t * str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-alpha.3+5214f"));
    octaspire_string_release(str);
    str = 0;

    ASSERT(octaspire_semver_pop_front(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-alpha.3"));
    octaspire_string_release(str);
    str = 0;

    ASSERT(octaspire_semver_pop_front(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2-3"));
    octaspire_string_release(str);
    str = 0;

    ASSERT(octaspire_semver_pop_front(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2"));
    octaspire_string_release(str);
    str = 0;

    // This should not have any effect anymore.
    ASSERT(octaspire_semver_pop_front(semver));

    str = octaspire_semver_to_string(semver);
    ASSERT(str);
    ASSERT(octaspire_string_is_equal_to_c_string(str, "0.1.2"));
    octaspire_string_release(str);
    str = 0;

    octaspire_semver_release(semver);
    semver = 0;

    PASS();
}


GREATEST_SUITE(octaspire_semver_suite)
{
    octaspireSemverTestAllocator = octaspire_allocator_new(0);

    assert(octaspireSemverTestAllocator);

    // Pre release element
    RUN_TEST(octaspire_semver_pre_release_elem_type_accessors_called_on_lexical_type_test);
    RUN_TEST(octaspire_semver_pre_release_elem_type_accessors_called_on_numerical_type_test);
    RUN_TEST(octaspire_semver_pre_release_elem_new_copy_called_with_numerical_type_test);
    RUN_TEST(octaspire_semver_pre_release_elem_new_copy_called_with_lexcal_type_test);
    RUN_TEST(octaspire_semver_pre_release_elem_make_numerical_and_lexical_test);

    // Semantic version number
    RUN_TEST(octaspire_semver_new_called_with_null_allocator_test);
    RUN_TEST(octaspire_semver_new_prerelease_0_1_2_alpha_3_and_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_new_copy_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_get_build_metadata_at_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_get_prerelease_at_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_get_length_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_get_major_minor_patch_called_with_0_1_2_alpha_3_and_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_3_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214g_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_2_alpha_4_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_4_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alphb_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_2_alphb_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_3_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_1_3_alpha_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_2_2_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_0_2_2_alpha_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_1_1_2_alpha_3_sha_5214f_and_0_1_2_alpha_3_sha_5214f_test);
    RUN_TEST(octaspire_semver_compare_0_1_2_alpha_3_sha_5214f_and_1_1_2_alpha_3_sha_5214f_test);

    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_0_0_alpha_and_1_0_0_alpha_1_test);
    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_0_0_alpha_1_and_1_0_0_alpha_beta_test);
    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_0_0_alpha_beta_and_1_0_0_beta_test);
    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_0_0_beta_and_1_0_0_beta_2_test);
    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_0_0_beta_2_and_1_0_0_beta_11_test);
    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_0_0_beta_11_and_1_0_0_rc_1_test);
    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_0_0_rc_1_and_1_0_0_test);

    RUN_TEST(octaspire_semver_comparison_operators_called_with_3_0_1_rc_1_and_3_0_1_rc_1_test);
    RUN_TEST(octaspire_semver_comparison_operators_called_with_1_9_0_and_1_10_0_test);

    RUN_TEST(octaspire_semver_is_equal_to_c_string_called_with_1_9_0_and_same_and_five_different_test);

    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_0_0_rc_1_and_0_0_1_and_true_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_0_1_rc_1_and_0_1_0_and_true_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_1_0_0_and_true_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_and_0_0_0_rc_1_and_true_test);

    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_and_1_1_1_and_true_failure_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_and_1_1_0_and_true_failure_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_and_1_0_1_and_true_failure_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_and_0_1_1_and_true_failure_test);

    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_0_0_rc_1_and_0_0_1_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_0_1_rc_1_and_0_0_1_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_1_0_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_1_0_0_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_rc_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_1_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_rc_1_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_ra_and_false_test);
    RUN_TEST(octaspire_semver_add_or_subtract_called_with_1_1_1_rc_1_and_0_0_0_2_and_false_test);

    RUN_TEST(octaspire_semver_pop_back_called_on_prerelease_0_1_2_alpha_3_and_metadata_sha_5214f_test);
    RUN_TEST(octaspire_semver_pop_front_called_on_prerelease_0_1_2_alpha_3_and_metadata_sha_5214f_test);

    octaspire_allocator_release(octaspireSemverTestAllocator);
    octaspireSemverTestAllocator = 0;
}

