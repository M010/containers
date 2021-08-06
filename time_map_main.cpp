#include "map.hpp"
#include <map>

#define NAMESP ft

void rand_fill_maps(NAMESP::map<int, int> &ft_, int n) {

    for (int i = 0; i < n; i++) {
        int first  = rand() % 1000;
        ft_[first] = first;
    }
}

void time_test() {
    {
        for (int i = 0; i < 1000; i++) {
            NAMESP::map<int, int>  fmap;

            rand_fill_maps(fmap, 1000);
            for (int k = 0; k < 10; k++) {
                int f = rand() % 1300;
                fmap.erase(fmap.lower_bound(f), fmap.upper_bound(f + 50));
            }
        }
    }

    {
        for (int i = 0; i < 100; i++) {
            NAMESP::map<int, int>  fmap;

            rand_fill_maps(fmap, 1000);
            for (int k = 0; k < 100; k++) {
                int f = rand() % 1300;
                if (fmap.lower_bound(f) != fmap.end()) {
                    fmap.erase(fmap.lower_bound(f));
                }
            }
        }
    }

    {
        for (int i = 0; i < 100; i++) {
            NAMESP::map<int, int> smap;

            rand_fill_maps(smap, 1000);
            for (int k = 0; k < 1000; k++) {
                int f = rand() % 1300;
                if (smap.lower_bound(f) != smap.end()) {
                    smap.erase(smap.lower_bound(f), smap.lower_bound(f + 100));
                }
            }
        }
    }

    {
        for (int i = 0; i < 1000; i++) {
            NAMESP::map<int, int>  fmap;

            rand_fill_maps(fmap, 10000);
            for (int k = 0; k < 1000; k++) {
                int f = rand() % 1300;
                fmap.erase(f);
            }
        }
    }
}
int main()
{
    srand(time(0));
    time_test();
    return 0;
}