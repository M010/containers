#pragma once

#include  "../map.hpp"
#include <map>
#include <string>
#include "map_tests.h"
#include "test_runner.h"
#include "../utils.h"

struct Point {
    Point(double x, double y) : x(x), y(y) {}
    friend ostream &operator<<(ostream &os, const Point &point);
    double x, y;
};

struct PointCmp {
    bool operator()(const Point &lhs, const Point &rhs) const {
        return lhs.x < rhs.x; // NB. intentionally ignores y
    }
};

void map_constructor_tests();
void map_iterator_test();
void map_simple_bounds_test();
void map_erase_test();
void all_map_tests(TestRunner &tr);
