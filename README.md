[![Build Status](https://travis-ci.org/octaspire/core.svg?branch=master)](https://travis-ci.org/octaspire/core) [![Coverage Status](https://codecov.io/gh/octaspire/core/coverage.svg?branch=master)](https://codecov.io/gh/octaspire/core/coverage.svg?branch=master)

Containers and other utility libraries in standard C99

To build on Raspberry Pi, Debian or Ubuntu (16.04 LTS) system:

```shell
sudo apt-get install cmake git
git clone https://github.com/octaspire/core.git
cd core/build
cmake ..
make
```

To run the unit tests:

```shell
test/octaspire-core-test-runner
```
