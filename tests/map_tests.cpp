#include "map_tests.h"
bool fncomp(char lhs, char rhs) { return lhs < rhs; }

void rand_fill_maps(ft::map<int, int> &ft_, std::map<int, int> &st, int n) {

    for (int i = 0; i < n; i++) {
        int first  = rand() % 1000;
        int second = rand() % 1000;
        ft_[first] = second;
        st[first]  = second;
    }
}

struct classcomp {
    bool operator()(const char &lhs, const char &rhs) const { return lhs < rhs; }
};

void all_map_tests(TestRunner &tr) {
    std::cerr << "============ map ================" << std::endl;
    RUN_TEST(tr, map_constructor_tests);
    RUN_TEST(tr, map_iterator_test);
    RUN_TEST(tr, map_simple_bounds_test);
    RUN_TEST(tr, map_erase_test);
    std::cerr << "========== map end ===============" << std::endl;
}

template<class T>
void is_empty(const T &mp) {
    std::cout << "is_empty: " << mp.empty() << std::endl;
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
void map_simple_bounds_test() {
    {
        std::map<char, int>           mymap;
        std::map<char, int>::iterator itlow, itup;

        mymap['b'] = 40;
        mymap['d'] = 80;
        mymap['a'] = 20;
        mymap['e'] = 100;
        mymap['c'] = 60;

        itlow = mymap.lower_bound('b');
        itup  = mymap.upper_bound('d');

        ft::map<char, int>           fmymap;
        ft::map<char, int>::iterator fitlow, fitup;

        fmymap['b'] = 40;
        fmymap['d'] = 80;
        fmymap['a'] = 20;
        fmymap['e'] = 100;
        fmymap['c'] = 60;
        ASSERT_EQUAL(fmymap, mymap)

        fitlow = fmymap.lower_bound('b');
        fitup  = fmymap.upper_bound('d');
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
void map_iterator_test() {
    {
        std::map<std::string, int> map1;
        map1["something"]  = 69;
        map1["anything"]   = 199;
        map1["that thing"] = 50;

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
        while (fit != fmap1.begin()) {
            ASSERT_EQUAL(*(--fit), *(--it))
        }
    }
    {
        std::map<std::string, int> map1;
        map1["something"]  = 69;
        map1["anything"]   = 199;
        map1["that thing"] = 50;

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
void map_constructor_tests() {
    {
        using std::endl;
        using std::cout;

        // (1) Default constructor
        std::map<std::string, int> map1;
        map1["something"]  = 69;
        map1["anything"]   = 199;
        map1["that thing"] = 50;

        ft::map<std::string, int> fmap1;
        fmap1["something"]  = 69;
        fmap1["anything"]   = 199;
        fmap1["that thing"] = 50;
        ASSERT_EQUAL(fmap1, map1);

        std::map<std::string, int> iter(map1.find("anything"), map1.end());
        ft::map<std::string, int>  fiter(fmap1.find("anything"), fmap1.end());

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

ostream &operator<<(ostream &os, const Point &point) {
    os << "x: " << point.x << " y: " << point.y;
    return os;
}
