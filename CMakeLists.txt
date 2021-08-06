cmake_minimum_required(VERSION 3.17)
project(containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS  "-Wall -Wextra -Werror")

add_executable(containers main.cpp vector.hpp tests/test_runner.h utils.h
        map.hpp pair.h rbIterator.h Node.h reverse_iterator.h tests/vector_tests.h stack.hpp tests/stack_test.cpp tests/stack_test.h tests/map_tests.cpp tests/map_tests.h)