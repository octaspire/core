git clone https://github.com/octaspire/core.git
cd core
make submodules-init
make
make test
make codestyle
make cppcheck
make valgrind
make coverage
make coverage-show

make amalgamation

make clean

rm release/octaspire-core-amalgamated.c
make release/octaspire-core-amalgamated.c

rm release/documentation/core-manual.html
make release/documentation/core-manual.html
