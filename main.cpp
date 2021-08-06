#include "tests/test_runner.h"
#include "tests/vector_tests.h"
#include "tests/stack_test.h"
#include "tests/map_tests.h"


void test_all() {
    TestRunner tr;
    all_stack_test(tr);
    all_vector_tests(tr);
    all_map_tests(tr);
}

int main() {
    std::srand(time(0));
    test_all();
    return (0);
}
