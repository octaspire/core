pkgman install gcc_x86
git clone https://github.com/octaspire/core.git
cd core
make submodules-init
CC=gcc-x86 make
