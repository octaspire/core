#/******************************************************************************
# Octaspire Core - Containers and other utility libraries in standard C99
# Copyright 2017 www.octaspire.com
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#******************************************************************************/
cmake_minimum_required(VERSION 2.8.12)
project(octaspire-core C)

set(OCTASPIRE_CORE_CONFIG_VERSION_MAJOR 0)
set(OCTASPIRE_CORE_CONFIG_VERSION_MINOR 25)
set(OCTASPIRE_CORE_CONFIG_VERSION_PATCH 0)

message("== Building ${PROJECT_NAME} ${OCTASPIRE_CORE_CONFIG_VERSION_MAJOR}.${OCTASPIRE_CORE_CONFIG_VERSION_MINOR}.${OCTASPIRE_CORE_CONFIG_VERSION_PATCH}")

set(OCTASPIRE_CORE_CONFIG_TEST_RES_PATH "${CMAKE_CURRENT_SOURCE_DIR}/test/resource/")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/octaspire/core/octaspire_core_config.h.in"
    "${CMAKE_BINARY_DIR}/include/octaspire/core/octaspire_core_config.h")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
        "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel. " FORCE)
endif(NOT CMAKE_BUILD_TYPE)

message("== Build type of ${PROJECT_NAME} is ${CMAKE_BUILD_TYPE}")
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB EXTERNAL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/external/*.c")
file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/octaspire/core/*.h")
file(GLOB MANUAL3 "${CMAKE_CURRENT_SOURCE_DIR}/doc/man/man3/octaspire-core.3")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("${CMAKE_BINARY_DIR}/include")
add_library(octaspire-core STATIC  ${SOURCES} ${EXTERNAL_SOURCES})
set_property(TARGET octaspire-core PROPERTY C_STANDARD 99)
set_property(TARGET octaspire-core PROPERTY C_EXTENSIONS OFF)

if(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID MATCHES "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -pedantic")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=c99 -fno-omit-frame-pointer -Wall -Wextra -pedantic -Werror")
endif(CMAKE_C_COMPILER_ID MATCHES "Clang" OR CMAKE_C_COMPILER_ID MATCHES "GNU")

if(CMAKE_C_COMPILER_ID MATCHES "Clang")

    if(CMAKE_BUILD_TYPE MATCHES "Debug")
        target_compile_definitions(octaspire-core PRIVATE OCTASPIRE_CLANG_PRAGMAS_ENABLED=1)
        message("== Enabling clang pragmas for ${PROJECT_NAME}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Weverything")
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Weverything")
    endif(CMAKE_BUILD_TYPE MATCHES "Debug")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
    #set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fcolor-diagnostics -fsanitize=undefined,address")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fcolor-diagnostics")
endif(CMAKE_C_COMPILER_ID MATCHES "Clang")

option(OCTASPIRE_CORE_COVERAGE  "OCTASPIRE_CORE_COVERAGE"  OFF)
option(OCTASPIRE_CORE_UNIT_TEST "OCTASPIRE_CORE_UNIT_TEST" ON)

if(OCTASPIRE_CORE_COVERAGE)
    message("== Code coverage enabled for ${PROJECT_NAME}")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage")
endif(OCTASPIRE_CORE_COVERAGE)

if(OCTASPIRE_CORE_UNIT_TEST)
    message("== Unit testing enabled for ${PROJECT_NAME}")
else()
    message("== Unit testing disabled for ${PROJECT_NAME}")
endif(OCTASPIRE_CORE_UNIT_TEST)

target_link_libraries(octaspire-core m)
install(TARGETS octaspire-core DESTINATION lib)
install(FILES ${HEADERS} DESTINATION "include/octaspire/core")
install(FILES "${CMAKE_BINARY_DIR}/include/octaspire/core/octaspire_core_config.h" DESTINATION "include/octaspire/core")
install(FILES ${MANUAL3} DESTINATION "man/man3")
add_custom_target(
    cppcheck-core
    COMMAND cppcheck --std=c99 -I "${CMAKE_CURRENT_SOURCE_DIR}/include"
            --enable=warning,performance,portability
            --verbose --quiet ${SOURCES} ${HEADERS})

add_custom_target(
    vera-core
    COMMAND vera++ --error ${SOURCES} ${HEADERS})

add_custom_target(
    book-core
    COMMAND asciidoctor -a source-highlighter=pygments -a max-width=55em --backend=html5 "${CMAKE_CURRENT_SOURCE_DIR}/doc/book/Octaspire_Core_Manual.adoc")

if(NOT TARGET octaspire-core-test-runner AND OCTASPIRE_CORE_UNIT_TEST)
    message("== Building of unit tests enabled for ${PROJECT_NAME}")
    enable_testing()
    include(CTest)
    add_subdirectory(test)
endif(NOT TARGET octaspire-core-test-runner AND OCTASPIRE_CORE_UNIT_TEST)

