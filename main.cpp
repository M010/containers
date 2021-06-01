#include <iostream>
#include "ft_vector.h"
#include <vector>
#include "test_runner.h"


int constr_test()
{
    ft::vector<int>     ft_vec(1);
    std::vector<int>    std_vec(1);
    try {
        std_vec.at(100);
    } catch (std::out_of_range& ex)
    {
       std::cerr << ex.what() << std::endl;
    }
    std_vec.max_size();
    ASSERT_EQUAL(std_vec.size(), ft_vec.size());
};


int TestAll()
{
    TestRunner tr;
    RUN_TEST(tr, constr_test);

}

int main()
{
    TestAll();
}
