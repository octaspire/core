[![Build Status](https://travis-ci.org/octaspire/core.svg?branch=master)](https://travis-ci.org/octaspire/core) [![Coverage Status](https://codecov.io/gh/octaspire/core/coverage.svg?branch=master)](https://codecov.io/gh/octaspire/core/coverage.svg?branch=master) [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)


Containers and other utility libraries in standard C99

[![asciicast](https://asciinema.org/a/129147.png)](https://asciinema.org/a/129147)

To build on Raspberry Pi, Debian or Ubuntu (16.04 LTS) system:

```shell
sudo apt-get install cmake git
git clone https://github.com/octaspire/core.git
cd core/build
cmake ..
make
```

To build on Arch Linux (Arch Linux ARM) system:

```shell
sudo pacman -S cmake git gcc make
git clone https://github.com/octaspire/core.git
cd core/build
cmake ..
make
```

To build on Haiku (Version Walter (Revision hrev51127) x86_gcc2):

```shell
pkgman install gcc_x86 cmake_x86
git clone https://github.com/octaspire/core.git
cd core/build
CC=gcc-x86 cmake ..
make
```

To build on FreeBSD (FreeBSD-11.0-RELEASE-arm-armv6-RPI2) system:

```shell
sudo pkg install git cmake
git clone https://github.com/octaspire/core.git
cd core/build
cmake ..
make
```

To build on MINIX 3 (minix_R3.3.0-588a35b) system:

```shell
su root
pkgin install cmake clang binutils git-base
exit
git clone git://github.com/octaspire/core
cd core/build
cmake ..
make
```

To run the unit tests:

```shell
test/octaspire-core-test-runner
```

Homepage for Octaspire Core can be found from here:
[http://www.octaspire.com/core](http://www.octaspire.com/core)

Other Octaspire projects using Octaspire Core can be seen here:
[Programming language Octaspire Dern](http://www.octaspire.com/dern), 
[Puzzle game Octaspire Maze](http://www.octaspire.com/maze) and 
[Puzzle game Octaspire Lightboard](http://www.octaspire.com/lightboard).
