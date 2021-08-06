//
// Created by Santiago Bashir on 8/6/21.
//

#include "vector.hpp"
#include <vector>

#define NAMESP std

static void time() {
    for (int i = 0; i < 100; i++) {
        NAMESP::vector<int> sample;
        for (int            j = 0; j < 1000; j++)
            sample.push_back(j);

        NAMESP::vector<int> isample(sample);
        for (int            j = 0; j < 1000; j++)
            sample.pop_back();
        sample.assign(isample.begin(), isample.end());
        for (int j = 0; j < 1000; j++) {
            sample.erase(isample.begin(), isample.end());
        }

        for (int j = 0; j < 1000; j++) {
            isample.resize(j);
            isample.reserve(43);
        }

        NAMESP::vector<int> ksample(1000);
        for (int j = 0; j < 10; j++) {
            isample.insert(isample.begin(), ksample.begin(), ksample.end());
        }

    }
}

int main() {
    time();
    return 0;
}
