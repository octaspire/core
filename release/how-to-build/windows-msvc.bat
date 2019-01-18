@ECHO OFF

@ECHO -----------------------------------------------------------------
@ECHO stand alone unit test runner:
@ECHO -----------------------------------------------------------------
cl /nologo /W3 /DOCTASPIRE_CORE_AMALGAMATED_UNIT_TEST_IMPLEMENTATION octaspire-core-amalgamated.c /link /out:octaspire-core-unit-test-runner.exe
@ECHO.
@ECHO RUN WITH:
@ECHO octaspire-core-unit-test-runner.exe
@ECHO.
@ECHO BUILD WITH:
@ECHO cl /W3 /DOCTASPIRE_CORE_AMALGAMATED_UNIT_TEST_IMPLEMENTATION octaspire-core-amalgamated.c /link /out:octaspire-core-unit-test-runner.exe

@ECHO.
@ECHO -----------------------------------------------------------------
@ECHO example program:
@ECHO -----------------------------------------------------------------
cl /nologo /W3 /I. examples/example.c /link /out:example.exe
@ECHO.
@ECHO RUN WITH:
@ECHO example.exe
@ECHO.
@ECHO BUILD WITH:
@ECHO cl /W3 /I. examples/example.c /link /out:example.exe
