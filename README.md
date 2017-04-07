[![Build Status](https://travis-ci.org/octaspire/core.svg?branch=master)](https://travis-ci.org/octaspire/core) [![Coverage Status](https://codecov.io/gh/octaspire/core/coverage.svg?branch=master)](https://codecov.io/gh/octaspire/core/coverage.svg?branch=master)

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
