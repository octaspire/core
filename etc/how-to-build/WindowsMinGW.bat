echo off
set MINGW_PATH=C:\MinGW
echo =                                                             
echo ===============================================================
echo = This script expects that you have MinGW installed in %MINGW_PATH%
echo = and that %MINGW_PATH% and %MINGW_PATH%\bin are in the PATH.
echo = If you don't have MinGW installed, you can download it from:
echo =                                                             
echo =                     http://www.mingw.org/                   
echo =                                                             
echo = There are also installation instructions available for it.
echo ===============================================================
echo =
echo =
echo = 1. Building stand alone unit test runner to test the release 
echo ===============================================================

echo on
%MINGW_PATH%\bin\gcc.exe -O2 -std=c99 -Wall -Wextra -DOCTASPIRE_CORE_AMALGAMATED_UNIT_TEST_IMPLEMENTATION octaspire-core-amalgamated.c -lm -o octaspire-core-unit-test-runner

echo off
echo =
echo =
echo = 2. Building the hash map example                             
echo ===============================================================

echo on
%MINGW_PATH%\bin\gcc.exe -O2 -std=c99 -Wall -Wextra -I . examples/hash-map-example.c -lm -o hash-map-example

echo off
echo =
echo =
echo = 3. Building the string example                               
echo ===============================================================

echo on
%MINGW_PATH%\bin\gcc.exe -O2 -std=c99 -Wall -Wextra -I . examples/string-example.c -lm -o string-example

echo off
echo =
echo =
echo = 4. Building the vector example                               
echo ===============================================================

echo on
%MINGW_PATH%\bin\gcc.exe -O2 -std=c99 -Wall -Wextra -I . examples/vector-example.c -lm -o vector-example

echo off
echo =
echo =
echo ======================================
echo = Run programs and examples like this:
echo ======================================
echo = 1) octaspire-core-unit-test-runner  
echo = 2) hash-map-example                 
echo = 3) string-example                   
echo = 4) vector-example                   
echo ======================================
