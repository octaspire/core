#!/usr/bin/env sh

YELLOW='\033[1;33m'
GREEN='\033[1;32m'
NOCOLOR='\033[0m'

echoAndRun() { echo "$@" ; "$@" ; }
echoToDefs() { printf "$NOCOLOR\n" ; }

CC=gcc

printf "$YELLOW\n"
cat << EnDoFmEsSaGe
1. Building stand alone unit test runner to test the release
-------------------------------------------------------------------------------
EnDoFmEsSaGe
echoToDefs
echoAndRun $CC -O2 -std=c99 -Wall -Wextra                 \
    -DOCTASPIRE_CORE_AMALGAMATED_UNIT_TEST_IMPLEMENTATION \
    -DGREATEST_ENABLE_ANSI_COLORS                         \
-I . octaspire-core-amalgamated.c -lm                     \
-o octaspire-core-unit-test-runner



printf "$YELLOW\n"
cat << EnDoFmEsSaGe
2. Building the hash map example
-------------------------------------------------------------------------------
EnDoFmEsSaGe
echoToDefs
echoAndRun $CC -O2 -std=c99 -Wall -Wextra                 \
-I . examples/hash-map-example.c -lm                      \
-o hash-map-example



printf "$YELLOW\n"
cat << EnDoFmEsSaGe
3. Building the string example
-------------------------------------------------------------------------------
EnDoFmEsSaGe
echoToDefs
echoAndRun $CC -O2 -std=c99 -Wall -Wextra                 \
-I . examples/string-example.c -lm                        \
-o string-example



printf "$YELLOW\n"
cat << EnDoFmEsSaGe
4. Building the vector example
-------------------------------------------------------------------------------
EnDoFmEsSaGe
echoToDefs
echoAndRun $CC -O2 -std=c99 -Wall -Wextra                 \
-I . examples/vector-example.c -lm                        \
-o vector-example



printf "\nDone.\n$GREEN"
echo   "=================================================================="
echo   "Run programs and examples like this:"
echo   "=================================================================="
printf "%b1)%b ./octaspire-core-unit-test-runner\n" $YELLOW $GREEN
printf "%b2)%b ./hash-map-example\n" $YELLOW $GREEN
printf "%b3)%b ./string-example\n" $YELLOW $GREEN
printf "%b4)%b ./vector-example\n" $YELLOW $GREEN
echo "=================================================================="
echoToDefs

