#include "pair.h"
#include "map.hpp"
#include "vector.hpp"
#include "test_runner.h"
#include "vector_tests.h"
#include "stack_test.h"
#include <iostream>
#include <map>
#include <vector>
#include <list>

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp {
    bool operator()(const char &lhs, const char &rhs) const { return lhs < rhs; }
};

struct Point {
    Point(double x, double y) : x(x), y(y) {}

    friend ostream &operator<<(ostream &os, const Point &point) {
        os << "x: " << point.x << " y: " << point.y;
        return os;
    }

    double x, y;
};

struct PointCmp {
    bool operator()(const Point &lhs, const Point &rhs) const {
        return lhs.x < rhs.x; // NB. intentionally ignores y
    }
};

void map_constructor_tests() {
    {
        using std::endl;
        using std::cout;

        // (1) Default constructor
        std::map<std::string, int> map1;
        map1["something"]  = 69;
        map1["anything"]   = 199;
        map1["that thing"] = 50;
        std::cout << "map1 = " << map1 << endl;

        ft::map<std::string, int> fmap1;
        fmap1["something"]  = 69;
        fmap1["anything"]   = 199;
        fmap1["that thing"] = 50;
        ASSERT_EQUAL(fmap1, map1);
        std::cout << "map1 = " << fmap1 << std::endl;

        // (2) Range constructor
        std::map<std::string, int> iter(map1.find("anything"), map1.end());
        ft::map<std::string, int>  fiter(fmap1.find("anything"), fmap1.end());

        // (2) Range constructor
        std::map<std::string, int> niter(map1.find("something"), map1.end());
        ft::map<std::string, int>  nfiter(fmap1.find("something"), fmap1.end());

        ASSERT_EQUAL(niter, nfiter);


        // (3) Copy constructor
        std::map<std::string, int> copied(map1);
        ft::map<std::string, int>  fcopied(fmap1);
        ASSERT_EQUAL(map1, fmap1);

        std::map<Point, double, PointCmp> mag;

        mag[Point(5, -12)]  = 13;
        mag[Point(3, 4)]    = 5;
        mag[Point(-8, -15)] = 17;

        ft::map<Point, double, PointCmp> fmag;

        fmag[Point(5, -12)]  = 13;
        fmag[Point(3, 4)]    = 5;
        fmag[Point(-8, -15)] = 17;
        ASSERT_EQUAL(fmag, mag);
    }
}

void rand_fill_maps(ft::map<int, int> &ft_, std::map<int, int> &st, int n) {

    for (int i = 0; i < n; i++) {
        int first  = rand() % 1000;
        int second = rand() % 1000;
        ft_[first] = second;
        st[first]  = second;
    }
}

void map_iterator_test() {
    {

    }

    {
        std::map<std::string, int> map1;
        map1["something"]  = 69;
        map1["anything"]   = 199;
        map1["that thing"] = 50;
        std::cout << "map1 = " << map1 << endl;

        ft::map<std::string, int> fmap1;
        fmap1["something"]  = 69;
        fmap1["anything"]   = 199;
        fmap1["that thing"] = 50;

        ft::map<std::string, int>::iterator  fit = fmap1.begin();
        std::map<std::string, int>::iterator it  = map1.begin();
        while (fit != fmap1.end()) {
            ASSERT_EQUAL(*(fit++), *(it++))
        }

        fit = fmap1.end();
        it  = map1.end();
        fmap1.print_map();
        while (fit != fmap1.begin()) {
            ASSERT_EQUAL(*(--fit), *(--it))
        }
    }
    {
        std::map<std::string, int> map1;
        map1["something"]  = 69;
        map1["anything"]   = 199;
        map1["that thing"] = 50;
        std::cout << "map1 = " << map1 << endl;

        ft::map<std::string, int> fmap1;
        fmap1["something"]  = 69;
        fmap1["anything"]   = 199;
        fmap1["that thing"] = 50;

        ft::map<std::string, int>::reverse_iterator  fit = fmap1.rbegin();
        std::map<std::string, int>::reverse_iterator it  = map1.rbegin();
        while (fit != fmap1.rend()) {
            ASSERT_EQUAL(*(fit++), *(it++))
        }

        fit = fmap1.rend();
        it  = map1.rend();

        while (fit != fmap1.rbegin()) {
            ASSERT_EQUAL(*(--fit), *(--it))
        }

    }

}

void map_simple_bounds_test() {
    {
        std::map<char, int>           mymap;
        std::map<char, int>::iterator itlow, itup;

        mymap['b'] = 40;
        mymap['d'] = 80;
        mymap['a'] = 20;
        mymap['e'] = 100;
        mymap['c'] = 60;

        itlow = mymap.lower_bound('b');  // itlow points to b
        itup  = mymap.upper_bound('d');   // itup points to e (not d!)

        ft::map<char, int>           fmymap;
        ft::map<char, int>::iterator fitlow, fitup;

        fmymap['b'] = 40;
        fmymap['d'] = 80;
        fmymap['a'] = 20;
        fmymap['e'] = 100;
        fmymap['c'] = 60;
        ASSERT_EQUAL(fmymap, mymap)

        fitlow = fmymap.lower_bound('b');  // itlow points to b
        fitup  = fmymap.upper_bound('d');   // itup points to e (not d!)
        ASSERT_EQUAL(*fitlow, *itlow);
        ASSERT_EQUAL(*fitup, *itup);

        mymap.erase(itlow, itup);        // erases [itlow,itup)
        fmymap.erase(fitlow, fitup);        // erases [itlow,itup)

        ASSERT_EQUAL(mymap, fmymap);
    }

    {
        std::map<char, int>           mymap;
        std::map<char, int>::iterator itlow, itup;

        mymap['d'] = 80;
        mymap['e'] = 100;
        mymap['b'] = 40;
        mymap['c'] = 60;

        itlow = mymap.lower_bound('a');  // itlow points to b
        itup  = mymap.upper_bound('a');   // itup points to e (not d!)

        ft::map<char, int>           fmymap;
        ft::map<char, int>::iterator fitlow, fitup;

        fmymap['b'] = 40;
        fmymap['e'] = 100;
        fmymap['d'] = 80;
        fmymap['c'] = 60;
        ASSERT_EQUAL(fmymap, mymap)

        fmymap.print_map();
        fitlow = fmymap.lower_bound('a');  // itlow points to b
        fitup  = fmymap.upper_bound('a');   // itup points to e (not d!)
        ASSERT_EQUAL(*fitlow, *itlow);
        ASSERT_EQUAL(*fitup, *itup);

        mymap.erase(itlow, itup);        // erases [itlow,itup)
        fmymap.erase(fitlow, fitup);        // erases [itlow,itup)

        ASSERT_EQUAL(mymap, fmymap);
    }

    {
        for (int i = 0; i < 1000; i++) {
            std::map<int, int> smap;
            ft::map<int, int>  fmap;

            rand_fill_maps(fmap, smap, 500);
            int                          f   = rand() % 1500;
            ft::map<int, int>::iterator  fit = fmap.lower_bound(f);
            std::map<int, int>::iterator sit = smap.lower_bound(f);

            if (fit == fmap.end() || sit == smap.end()) {
                ASSERT(fit == fmap.end() && sit == smap.end());
            } else ASSERT_EQUAL(*fit, *sit);

            f   = rand() % 1500;
            fit = fmap.upper_bound(f);
            sit = smap.upper_bound(f);
            if (fit == fmap.end() || sit == smap.end()) {
                ASSERT(fit == fmap.end() && sit == smap.end());
            } else {
                ASSERT_EQUAL(*fit, *sit);
            }

            f   = rand() % 1500;
            fit = fmap.find(f);
            sit = smap.find(f);
            if (fit == fmap.end() || sit == smap.end()) {
                ASSERT(fit == fmap.end() && sit == smap.end());
            } else {
                ASSERT_EQUAL(*fit, *sit);
            }

            for (int z = 0; z < 1000; z++) {
                int k = rand() % 1000;
                ASSERT_EQUAL(smap.count(k), fmap.count(k));
            }
        }
    }
}

void map_erase_test() {
    {
        std::map<char, int>           mymap;
        std::map<char, int>::iterator it;

        // insert some values:
        mymap['a'] = 10;
        mymap['e'] = 50;
        mymap['f'] = 60;
        mymap['b'] = 20;
        mymap['c'] = 30;
        mymap['d'] = 40;

        std::map<char, int>           fmymap;
        std::map<char, int>::iterator fit;

        // insert some values:
        fmymap['a'] = 10;
        fmymap['e'] = 50;
        fmymap['f'] = 60;
        fmymap['b'] = 20;
        fmymap['c'] = 30;
        fmymap['d'] = 40;

        ASSERT_EQUAL(mymap, fmymap);

        it  = mymap.find('b');
        fit = fmymap.find('b');
        ASSERT_EQUAL(*fit, *it);
        mymap.erase(it);                   // erasing by iterator
        fmymap.erase(fit);                   // erasing by iterator

        ASSERT_EQUAL(mymap, fmymap);

        mymap.erase('c');                  // erasing by key
        fmymap.erase('c');                  // erasing by key

        ASSERT_EQUAL(mymap, fmymap);

        it  = mymap.find('e');
        fit = fmymap.find('e');

        ASSERT_EQUAL(*fit, *it);
        mymap.erase(it, mymap.end());    // erasing by range
        fmymap.erase(fit, fmymap.end());    // erasing by range

        ASSERT_EQUAL(mymap, fmymap);
    }

    {
        for (int i = 0; i < 1000; i++) {
            std::map<int, int> smap;
            ft::map<int, int>  fmap;

            rand_fill_maps(fmap, smap, 500);
            ASSERT_EQUAL(fmap, smap);
            for (int k = 0; k < 10; k++) {
                int f = rand() % 1300;
                fmap.erase(fmap.lower_bound(f), fmap.upper_bound(f + 50));
                smap.erase(smap.lower_bound(f), smap.upper_bound(f + 50));
                ASSERT_EQUAL(fmap, smap);
            }
        }
    }

    {
        for (int i = 0; i < 100; i++) {
            std::map<int, int> smap;
            ft::map<int, int>  fmap;

            rand_fill_maps(fmap, smap, 1000);
            ASSERT_EQUAL(fmap, smap);
            for (int k = 0; k < 100; k++) {
                int f = rand() % 1300;
                if (smap.lower_bound(f) != smap.end()) {
                    fmap.erase(fmap.lower_bound(f));
                    smap.erase(smap.lower_bound(f));
                }
                ASSERT_EQUAL(fmap, smap);
            }
        }
    }

    {
        for (int i = 0; i < 100; i++) {
            std::map<int, int> smap;
            ft::map<int, int>  fmap;

            rand_fill_maps(fmap, smap, 1000);
            ASSERT_EQUAL(fmap, smap);
            for (int k = 0; k < 10; k++) {
                int f = rand() % 1300;
                if (smap.lower_bound(f) != smap.end()) {
                    fmap.erase(fmap.lower_bound(f), fmap.lower_bound(f + 100));
                    smap.erase(smap.lower_bound(f), smap.lower_bound(f + 100));
                }
                ASSERT_EQUAL(fmap, smap);
            }
        }
    }

    {
        for (int i = 0; i < 100; i++) {
            std::map<int, int> smap;
            ft::map<int, int>  fmap;

            rand_fill_maps(fmap, smap, 1000);
            ASSERT_EQUAL(fmap, smap);
            for (int k = 0; k < 100; k++) {
                int f = rand() % 1300;
                fmap.erase(f);
                smap.erase(f);
                ASSERT_EQUAL(fmap, smap);
            }
        }
    }
}

#define T1 int
#define T2 std::string
typedef ft::pair<const T1, T2> T3;

static int iter = 0;

template<typename MAP, typename U>
MAP ft_erase(MAP &mp, U param) {
    std::cout << "\t-- [" << iter++ << "] --" << std::endl;
    mp.erase(param);
    return mp;
}

template<typename MAP, typename U, typename V>
MAP ft_erase(MAP &mp, U param, V param2) {
    std::cout << "\t-- [" << iter++ << "] --" << std::endl;
    mp.erase(param, param2);
    return mp;
}

void sample_erase_test(void) {
    std::list<T3>     lst;
    unsigned int      lst_size = 10;
    for (unsigned int i        = 0; i < lst_size; ++i)
        lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
    ft::map<T1, T2>   mp(lst.begin(), lst.end());

    ft_erase(mp, ++mp.begin());

    ft_erase(mp, mp.begin());
    ft_erase(mp, --mp.end());

    ft_erase(mp, mp.begin(), ++(++(++mp.begin())));
    mp.print_map();
    ft::map<T1, T2>::iterator mit = mp.end();
    mit--;
    mit--;
    mit--;
    ft_erase(mp, --(--(--mp.end())), --mp.end());

    mp[10] = "Hello";
    mp[11] = "Hi there";
    ft_erase(mp, --(--(--mp.end())), mp.end());

    mp[12] = "ONE";
    mp[13] = "TWO";
    mp[14] = "THREE";
    mp[15] = "FOUR";
    ft_erase(mp, mp.begin(), mp.end());
}


//void map_equal_range_test(){
//
//    std::map<int, const char*> u;
//    u[0] = "zero";
//    u[1] = "one";
//    u[2] = "two";
//    const std::map<int, const char*> m(u);
//
//    {
//        auto p = m.equal_range(1);
//        for (auto& q = p.first; q != p.second; ++q) {
//            std::cout << "m[" << q->first << "] = " << q->second << '\n';
//        }
//
//        if (p.second == m.find(2)) {
//            std::cout << "end of equal_range (p.second) is one-past p.first\n";
//        } else {
//            std::cout << "unexpected; p.second expected to be one-past p.first\n";
//        }
//    }
//
//    {
//        auto pp = m.equal_range(-1);
//        if (pp.first == m.begin()) {
//            std::cout << "pp.first is iterator to first not-less than -1\n";
//        } else {
//            std::cout << "unexpected pp.first\n";
//        }
//
//        if (pp.second == m.begin()) {
//            std::cout << "pp.second is iterator to first element greater-than -1\n";
//        } else {
//            std::cout << "unexpected pp.second\n";
//        }
//    }
//
//    {
//        auto ppp = m.equal_range(3);
//        if (ppp.first == m.end()) {
//            std::cout << "ppp.first is iterator to first not-less than 3\n";
//        } else {
//            std::cout << "unexpected ppp.first\n";
//        }
//
//        if (ppp.second == m.end()) {
//            std::cout << "ppp.second is iterator to first element greater-than 3\n";
//        } else {
//            std::cout << "unexpected ppp.second\n";
//        }
//    }
//}


template<class T>
void is_empty(T const &mp) {
    std::cout << "is_empty: " << mp.empty() << std::endl;
}

void all_map_tests(TestRunner &tr) {
    RUN_TEST(tr, map_constructor_tests);
    RUN_TEST(tr, map_iterator_test);
    RUN_TEST(tr, sample_erase_test);
    RUN_TEST(tr, map_simple_bounds_test);
    RUN_TEST(tr, map_erase_test);
}

template<class T>
void foo(T t, typename ft::enable_if<ft::is_integral<T>::value, T>::type * = 0) {
    std::cout << "hello !!!!!!!!!!!!!!!!!!!" << t << std::endl;
}

template<class T>
void foo(T t, typename ft::enable_if<!ft::is_integral<T>::value, T>::type * = 0) {
    std::cout << "hi" << t << std::endl;
}

void type_traits_test() {
    {
        foo(42);
        foo("str");
    }
}

void all_utils_test(TestRunner &tr) {
    RUN_TEST(tr, type_traits_test);
}

void test_all() {
    TestRunner tr;
    //all_stack_test(tr);
    //all_utils_test(tr);
    //all_vector_tests(tr);
    all_map_tests(tr);
}



struct Cry {
    std::string name;

    Cry() : name("Empty") { std::cerr << "cry " << name << std::endl; }

    Cry(const std::string &name) : name(name) {
        std::cerr << "cry name " << this->name << std::endl;
    }

    Cry(const Cry &cry) {
        this->name = "[" + cry.name + "]";
        std::cerr << "copy cry!" << this->name << std::endl;
    }

    void operator=(const Cry &cry) { std::cerr << this->name << " = " << cry.name << std::endl; }

    ~Cry() { std::cerr << "~cry " << name << std::endl; }
};

int main() {
    std::srand(time(0));
   // test_all();

    ft::map<int, int> k;
    k[8] = 0;
    k[3] = 0;
    k[10] = 0;
    k[1] = 0;
    k[6] = 0;
    k[14] = 0;
    k[4] = 0;
    k[7] = 0;
    k[13] = 0;

    k.print_map();
    std::cout << "-------------------------------" << std::endl;
    k.rotate_left_root();
    k.print_map();
    std::cout << "-------------------------------" << std::endl;
    k.rotate_right_root();
    k.print_map();
    std::cout << "-------------------------------" << std::endl;
    k.insert_root_test(ft::make_pair(5,0));
    k.print_map();
    return (0);
}
