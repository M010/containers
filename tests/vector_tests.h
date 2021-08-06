#include "../vector.hpp"
#include "test_runner.h"

void ft_vector_tests();

void reserve_test();

void push_back_test();

void constructor_test();

void iterator_test();

void reverse_iterator_test();

template<class Container, class Container1>
void n_fill(Container &container1, Container1 &container2);

template<class Container, class Container1>
void s_fill(Container &container1, Container1 &container2, int n = 10);

void insert_test();

void all_vector_tests(TestRunner &tr);