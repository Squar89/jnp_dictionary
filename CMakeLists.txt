cmake_minimum_required(VERSION 3.8)
project(jnp_dictionary)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_FLAGS_RELEASE -DNDEBUG)

set(SOURCE_FILES dict.cc dict.h dictglobal.cpp dictglobal.h)
set(TEST_FILES tests.cpp dict.cc dict.h dictglobal.cpp dictglobal.h)
add_executable(jnp_dictionary ${SOURCE_FILES})
add_executable(tests ${TEST_FILES})