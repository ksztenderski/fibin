cmake_minimum_required(VERSION 3.15)
project(Fibin)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -std=c++17 -O2 -lstdc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

add_executable(Fibin fibin_example.cc fibin_test.cc)