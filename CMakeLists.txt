cmake_minimum_required(VERSION 3.5.1)
project(jnp_dictionary)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2 -std=c++17")
set(CMAKE_C_FLAGS "-Wall -Wextra -O2")

set(CMAKE_CXX_FLAGS_RELEASE -DNDEBUG)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE DEBUG)
endif ()

set(TEST1_FILES dict.cc dict.h dictglobal.cc dictglobal.h dict_test1.c)
set(TEST2A_FILES dict.cc dict.h dictglobal.cc dictglobal.h dict_test2a.cc)
set(TEST2B_FILES dict.cc dict.h dictglobal.cc dictglobal.h dict_test2b.cc)
set(TEST_FILES tests.cpp dict.cc dict.h dictglobal.cc dictglobal.h)
set(TEST3_FILES test3.cpp dict.cc dict.h dictglobal.cc dictglobal.h cdict cdictglobal)

add_executable(dict_test1 ${TEST1_FILES})
add_executable(dict_test2a ${TEST2A_FILES})
add_executable(dict_test2b ${TEST2B_FILES})
add_executable(tests ${TEST_FILES})
add_executable(test3 ${TEST3_FILES})

#g++ -c -Wall -Wextra -O2 -std=c++17 dict.cc -o dict.o
#g++ -c -Wall -Wextra -O2 -std=c++17 dictglobal.cc -o dictglobal.o
#gcc -c -Wall -Wextra -O2 dict_test1.c -o dict_test1.o
#g++ -c -Wall -Wextra -O2 -std=c++17 dict_test2a.cc -o dict_test2a.o
#g++ -c -Wall -Wextra -O2 -std=c++17 dict_test2b.cc -o dict_test2b.o
#g++ dict_test1.o dict.o dictglobal.o -o dict_test1
#g++ dict_test2a.o dict.o dictglobal.o -o dict_test2a
#g++ dict_test2b.o dict.o dictglobal.o -o dict_test2b