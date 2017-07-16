# Octaspire Core

[![Build Status](https://travis-ci.org/octaspire/core.svg?branch=master)](https://travis-ci.org/octaspire/core) [![Coverage Status](https://codecov.io/gh/octaspire/core/coverage.svg?branch=master)](https://codecov.io/gh/octaspire/core/coverage.svg?branch=master) [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)


Containers and other utility libraries in standard C99

[![asciicast](https://asciinema.org/a/129147.png)](https://asciinema.org/a/129147)


## Building the amalgamated source release

The amalgamated source release is the recommended way of using Core, if you don't need to
modify Core itself. To use the amalgamated release, you will need only a C compiler and
C standard library supporting C99.

Core should compile cleanly without any warnings using `-Wall -Wextra -pedantic`.
Currently it is tested with *gcc*, *clang*, *Tiny C Compiler (tcc)*, *Portable C compiler
(pcc)* and Plan 9's *8c* compiler.

Core is portable and is tested and known to run in Linux, FreeBSD, OpenBSD, NetBSD, OpenIndiana,
DragonFly BSD, MidnightBSD, MINIX 3, Haiku, Syllable Desktop and Windows.
The `how-to-build`-directory of the amalgamated source release contains build script for most tested
platforms. More platforms and build scripts will be added later.

### Linux, FreeBSD, OpenBSD, NetBSD, OpenIndiana, DragonFly BSD, MidnightBSD, MINIX 3, Haiku, Syllable Desktop

```shell
curl -O octaspire.com/core/release.tar.bz2
tar jxf release.tar.bz2
cd release/*
curl -O https://octaspire.github.io/core/checksums
sha512sum -c checksums
sh how-to-build/YOUR_PLATFORM_NAME_HERE.XX
```

replace **YOUR_PLATFORM_NAME_HERE.XX** with **FreeBSD.sh**, **NetBSD.sh**, **OpenBSD.sh**,
**OpenIndiana.sh**, **DragonFlyBSD.sh**, **MidnightBSD.sh**, **linux.sh**, **minix3.sh**,
**haiku.sh** or **SyllableDesktop.sh**. More scripts for different platforms will be added later.


### Windows using MinGW

1. Download and install **MinGW** from
[http://www.mingw.org](www.mingw.org) into directory `C:\MinGW`. Please note, that you might need
to add `C:\MinGW` and `C:\MinGW\bin` into the `PATH`.
If you cannot install into `C:\MinGW`, you can install MinGW to some other place.
Remember the installation path, because later you can write it into the
`WindowsMinGW.bat` file, so that the script finds MinGW.

2. Download and install **7-Zip** from
[http://www.7-zip.org](www.7-zip.org).

3. Download
[http://www.octaspire.com/core/release.tar.bz2](www.octaspire.com/core/release.tar.bz2) and
extract it with 7-Zip. You might need to extract it twice; first into file `release.tar`
and then again to get the directory.

4. Start **shell** and change directory to the extracted release directory
   and then into directory `version-x.y.z`, where x, y and z are some version
   numbers.

5. When you are in the directory `version-x.y.z` run command `how-to-build\WindowsMinGW.bat`


More scripts for different tools might be added later.


## Links

Homepage for Octaspire Core can be found from here:
[http://www.octaspire.com/core](http://www.octaspire.com/core)

Other Octaspire projects using Octaspire Core can be seen here:
[Programming language Octaspire Dern](http://www.octaspire.com/dern), 
[Puzzle game Octaspire Maze](http://www.octaspire.com/maze) and 
[Puzzle game Octaspire Lightboard](http://www.octaspire.com/lightboard).
