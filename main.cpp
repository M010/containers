#include <iostream>
#include "ft_vector.h"
#include <vector>
#include "test_runner.h"


int constr_test()
{
    ft::vector<int> ft_vec(1);
    std::vector<int> std_vec(0);
    ASSERT_EQUAL(std_vec.size(), ft_vec.size());
};


int TestAll()
{
    TestRunner tr;
    RUN_TEST(tr, constr_test);
}

int main()
{

}
