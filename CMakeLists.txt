cmake_minimum_required(VERSION 3.17)
project(containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wreturn-type")

add_executable(containers main.cpp ft_vector.h test_runner.h utils.h
        ft_map.cpp ft_map.h pair.cpp pair.h rbIterator.cpp rbIterator.h Node.cpp Node.h reverse_iterator.h vector_tests.h)