#include <iostream>
#include "ft_vector.h"
#include <vector>
#include "test_runner.h"


int constr_test()
{
    ft::vector<int>     ft_vec(1, 10);
    std::vector<int>    std_vec(1, 10);
    ASSERT_EQUAL(ft_vec.front(), std_vec.front())
    ASSERT_EQUAL(std_vec.size(), ft_vec.size());
};


int TestAll()
{
    TestRunner tr;
    RUN_TEST(tr, constr_test);
}

struct Scream
{
    static int counter;

   Scream(){
      std::cerr << "Hello, world "  << counter++  << std::endl;
   }
   ~Scream(){
       std::cerr << "GOODBYE, world! "  <<  --counter << std::endl;
   }
    Scream(const Scream& other)
    {
        std::cerr << "Copy, world "  << counter++  << std::endl;
    }
};
int Scream::counter = 0;

int main()
{
    //TestAll();
    ft::vector<Scream> test(1);
   // test.resize(3);
    //std::cerr << "end of func" << std::endl;
}
