#!/usr/bin/env sh

PROJECT_PATH=$1

if test "$PROJECT_PATH" = ""; then echo "No PROJECT_PATH given"; exit 1; fi

rm -rf $1/build/octaspire_core_coverage
mkdir -p $1/build/octaspire_core_coverage
cp -r $1/release/* $1/build/octaspire_core_coverage
cd $1/build/octaspire_core_coverage
how-to-build/linux.sh gcc --coverage
./octaspire-core-unit-test-runner --write-test-files
lcov --no-external --capture --directory . --output-file $1/build/octaspire_core_coverage/coverage.info
genhtml $1/build/octaspire_core_coverage/coverage.info --output-directory $1/build/octaspire_core_coverage/out
xdg-open $1/build/octaspire_core_coverage/out/index.html &

