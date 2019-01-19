void octaspire_core_amalgamated_write_test_file(
    char const * const name,
    unsigned char const * const buffer,
    size_t const bufferSize)
{
#ifdef _MSC_VER
    FILE *stream = 0;
    errno_t const err = fopen_s(&stream, name, "wb");

    if(err)
    {
        abort();
    }
#else
    FILE *stream = fopen(name, "wb");
#endif

    if (!stream)
    {
        abort();
    }

    if (!buffer || !bufferSize)
    {
        if (fclose(stream) != 0)
        {
            abort();
        }

        stream = 0;

        printf("  Wrote empty file '%s'\n", name);

        return;
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

    int c = 0;

    if (argc >= 2)
    {
        if (strcmp(argv[1], "--write-test-files") == 0)
        {
            --argc;
            ++argv;
            c = (int)'a';
        }
        else
        {
            printf("Unknown option '%s'\n", argv[1]);
            return EXIT_FAILURE;
        }
        printf("Option '%c' given with command line argument.\n", (char)c);
    }
    else
    {
        c = getchar();
    }

    switch (c)
    {
        case 'a':
        {
            printf("Writing test files to current working directory...\n");

            octaspire_core_amalgamated_write_test_file(
                "octaspire_helpers_path_to_buffer_failure_on_empty_file_test", 0, 0);



            unsigned char const octaspire_helpers_path_to_buffer_test[] = {
                0xc2, 0xa9, 0xe2, 0x89, 0xa0, 0xf0, 0x90, 0x80, 0x80
            };
            size_t const octaspire_helpers_path_to_buffer_test_len = 9;

            octaspire_core_amalgamated_write_test_file(
                "octaspire_helpers_path_to_buffer_test",
                octaspire_helpers_path_to_buffer_test,
                octaspire_helpers_path_to_buffer_test_len);


            unsigned char const octaspire_input_new_from_path_test[] = {
              0x61, 0x62, 0x63, 0xc2, 0xa9, 0xe2, 0x89, 0xa0, 0xf0, 0x90, 0x80, 0x80
            };
            size_t const octaspire_input_new_from_path_test_len = 12;

            octaspire_core_amalgamated_write_test_file(
                "octaspire_input_new_from_path_test",
                octaspire_input_new_from_path_test,
                octaspire_input_new_from_path_test_len);



            unsigned char const octaspire_stdio_fread_test[] = {
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
    RUN_SUITE(octaspire_vector_suite);
    RUN_SUITE(octaspire_list_suite);
    RUN_SUITE(octaspire_queue_suite);
    RUN_SUITE(octaspire_string_suite);
    RUN_SUITE(octaspire_semver_suite);
    RUN_SUITE(octaspire_pair_suite);
    RUN_SUITE(octaspire_map_suite);
    GREATEST_MAIN_END();
}


#endif  // OCTASPIRE_CORE_AMALGAMATED_UNIT_TEST_IMPLEMENTATION
#endif  // OCTASPIRE_CORE_AMALGAMATED_H
