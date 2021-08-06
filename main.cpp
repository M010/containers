#include "pair.h"
#include "map.hpp"
#include "vector.hpp"
#include "test_runner.h"
#include "vector_tests.h"
#include "stack_test.h"
#include "map_tests.h"
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


    return (0);
}
