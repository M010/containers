cmake_minimum_required(VERSION 3.17)
project(containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS  "-Wall -Wextra -Werror")

add_executable(containers main.cpp vector.hpp test_runner.h utils.h
        ft_map.cpp map.hpp pair.cpp pair.h rbIterator.cpp rbIterator.h Node.cpp Node.h reverse_iterator.h vector_tests.h)