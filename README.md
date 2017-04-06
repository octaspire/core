[![Build Status](https://travis-ci.org/octaspire/core.svg?branch=master)](https://travis-ci.org/octaspire/core)

Containers and other utility libraries in standard C99

To build on Raspberry Pi and Debian system:

```shell
sudo apt-get install cmake git
git clone https://gitlab.com/octaspire/core.git
cd core
mkdir build
cd build
cmake ..
make
```

To run the unit tests:

```shell
test/octaspire-core-test-runner
```
