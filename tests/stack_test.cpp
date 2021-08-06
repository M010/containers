#include "stack_test.h"

void stack_top_pop_test() {
    {
        std::stack<int> s;
        ft::stack<int>  fs;

        s.push(2);
        s.push(6);
        s.push(51);

        fs.push(2);
        fs.push(6);
        fs.push(51);

        while (!s.empty()) {
            ASSERT_EQUAL(s.size(), fs.size())
            ASSERT_EQUAL(s.top(), fs.top())
            s.pop();
            fs.pop();
        }
    }

    {
        std::stack<std::string> s;
        ft::stack<std::string>  fs;

        s.push(ft_tostring(2));
        s.push(ft_tostring(6));
        s.push(ft_tostring(51));

        fs.push(ft_tostring(2));
        fs.push(ft_tostring(6));
        fs.push(ft_tostring(51));

        while (!s.empty()) {
            ASSERT_EQUAL(s.size(), fs.size())
            ASSERT_EQUAL(s.top(), fs.top())
            s.pop();
            fs.pop();
        }

    }
    {
        std::stack<int, std::list<int> > s;
        ft::stack<int, std::list<int> >  fs;

        s.push(2);
        s.push(6);
        s.push(51);

        fs.push(2);
        fs.push(6);
        fs.push(51);

        while (!s.empty()) {
            ASSERT_EQUAL(s.size(), fs.size())
            ASSERT_EQUAL(s.top(), fs.top())
            s.pop();
            fs.pop();
        }
    }
}

void stack_top_pop_random_test() {
    {
        std::stack<int> s;
        ft::stack<int>  fs;

        for (int i = 0; i < 100; i++) {
            int k = rand() % 500;
            s.push(k);
            fs.push(k);
            ASSERT_EQUAL(s.size(), fs.size())
            ASSERT_EQUAL(s.top(), fs.top())
        }

        while (!s.empty()) {
            ASSERT_EQUAL(s.size(), fs.size())
            ASSERT_EQUAL(s.top(), fs.top())
            s.pop();
            fs.pop();
        }
    }

    {
        std::stack<std::string> s;
        ft::stack<std::string>  fs;

        for (int i = 0; i < 100; i++) {
            int k = rand() % 500;
            s.push(ft_tostring(k));
            fs.push(ft_tostring(k));
            ASSERT_EQUAL(s.size(), fs.size())
            ASSERT_EQUAL(s.top(), fs.top())
        }

        while (!s.empty()) {
            ASSERT_EQUAL(s.size(), fs.size())
            ASSERT_EQUAL(s.top(), fs.top())
            s.pop();
            fs.pop();
        }
    }

    {
        std::stack<int, std::list<int> > s;
        ft::stack<int, std::list<int> >  fs;

        for (int i = 0; i < 100; i++) {
            int k = rand() % 500;
            s.push(k);
            fs.push(k);
            ASSERT_EQUAL(s.size(), fs.size())
            ASSERT_EQUAL(s.top(), fs.top())
        }

        while (!s.empty()) {
            ASSERT_EQUAL(s.size(), fs.size())
            ASSERT_EQUAL(s.top(), fs.top())
            s.pop();
            fs.pop();
        }
    }
}

void all_stack_test(TestRunner &tr) {
    RUN_TEST(tr, stack_top_pop_test);
    RUN_TEST(tr, stack_top_pop_random_test);
}
