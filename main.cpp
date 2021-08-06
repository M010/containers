#include "pair.h"
#include "map.hpp"
#include "vector.hpp"
#include "tests/test_runner.h"
#include "tests/vector_tests.h"
#include "tests/stack_test.h"
#include "tests/map_tests.h"
#include <iostream>
#include <map>
#include <vector>
#include <list>


void test_all() {
    TestRunner tr;
    all_stack_test(tr);
    all_vector_tests(tr);
    all_map_tests(tr);
}

int main() {
    std::srand(1);
    test_all();


    ft::map<int, int> k;
    return (0);
}
