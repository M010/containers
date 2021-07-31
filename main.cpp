#include "ft_map.h"
#include "ft_vector.h"
#include "test_runner.h"
#include "vector_tests.h"
#include <iostream>
#include <map>
#include <vector>

bool fncomp(char lhs, char rhs)
{ return lhs < rhs; }

struct classcomp
{
	bool operator()(const char &lhs, const char &rhs) const
	{ return lhs < rhs; }
};

struct Point
{
	Point(double x, double y) : x(x), y(y)
	{}

	friend ostream &operator<<(ostream &os, const Point &point)
	{
		os << "x: " << point.x << " y: " << point.y;
		return os;
	}

	double x, y;
};

struct PointCmp
{
	bool operator()(const Point &lhs, const Point &rhs) const
	{
		return lhs.x < rhs.x; // NB. intentionally ignores y
	}
};

void map_constructor_tests()
{
	{
		using std::endl;
		using std::cout;
		// (1) Default constructor
		std::map<std::string, int> map1;
		map1["something"] = 69;
		map1["anything"] = 199;
		map1["that thing"] = 50;
		std::cout << "map1 = " << map1 << endl;

		ft::map<std::string, int> fmap1;
		fmap1["something"] = 69;
		fmap1["anything"] = 199;
		fmap1["that thing"] = 50;

		ASSERT_EQUAL(fmap1, map1);
		std::cout << "map1 = " << fmap1 << std::endl;
		fmap1.erase(fmap1.find("something"));

		// (2) Range constructor
		//std::map<std::string, int> iter(map1.find("anything"), map1.end());
		//std::cout << "\niter = " << (iter) << std::endl;
		//std::cout << "map1 = " << std::endl;

		//ft::map<std::string, int> fiter(fmap1.find("anything"), fmap1.end());
		//std::cout << "\niter = " << (fiter) << std::endl;
		//std::cout << "map1 = " << std::endl;


		// (3) Copy constructor
		std::map<std::string, int> copied(map1);
		std::cout << "\ncopied = " << copied << endl;
		std::cout << "map1 = " << map1 << endl;


		ft::map<std::string, int> fcopied(fmap1);
		std::cout << "\ncopied = " << fcopied << endl;
		std::cout << "map1 = " << fmap1 << endl;
		ASSERT_EQUAL(map1, fmap1);


		//TODO: add back
		//std::map<Point, double, PointCmp> mag;

		//mag[Point(5, -12)] = 13;
		//mag[Point(3, 4)] = 5;
		//mag[Point(-8, -15)] = 17;

		//ft::map<Point, double, PointCmp> fmag;

		//fmag[Point(5, -12)] = 13;
		//fmag[Point(3, 4)] = 5;
		//fmag[Point(-8, -15)] = 17;
		//ASSERT_EQUAL(fmag, mag);

	}
}


void all_map_tests(TestRunner &tr)
{
	RUN_TEST(tr, map_constructor_tests);
}


template<class T>
void foo(T t, typename ft::enable_if<ft::is_integral<T>::value, T>::type *v = 0)
{
	std::cout << "hello !!!!!!!!!!!!!!!!!!!" << t << std::endl;
}

template<class T>
void foo(T t, typename ft::enable_if<!ft::is_integral<T>::value, T>::type *v = 0)
{
	std::cout << "hi" << t << std::endl;
}

void type_traits_test()
{
	{
		foo(42);
		foo("str");

	}
}

void all_utils_test(TestRunner &tr)
{
	RUN_TEST(tr, type_traits_test);
}


void test_all()
{
	TestRunner tr;
	all_utils_test(tr);
	//all_vector_tests(tr);

}

struct Cry
{
	std::string name;

	Cry() : name("Empty")
	{ std::cerr << "cry " << name << std::endl; }

	Cry(const std::string &name) : name(name)
	{
		std::cerr << "cry name " << this->name << std::endl;
	}

	Cry(const Cry &cry)
	{
		this->name = "[" + cry.name + "]";
		std::cerr << "copy cry!" << this->name << std::endl;
	}

	void operator=(const Cry &cry)
	{ std::cerr << this->name << " = " << cry.name << std::endl; }

	~Cry()
	{ std::cerr << "~cry " << name << std::endl; }
};

int main(int ac, char **av)
{
	test_all();

	std::set<int> test_set;
	std::vector<int> test_vec;

	for (int i = 0; i < 10; i++)
		test_set.insert(i);
	test_set.max_size();
	std::set<int>::iterator iti = test_set.begin();
	//typedef ft::map<int, int>::iterator map_iter;
	//std::vector<map_iter> iters;
	//srand(time(0));
	//for(int i = 0; i < 10; i++)
	//{
	//	iters.push_back(test._insert(rand() % 100));
	//}
	//test.print_map();
	//std::cerr << "iter_test:" << endl;
	//for(map_iter it = test.begin(); it != test.end(); it++)
	//{
	//	std::cerr << *it << " " ;
	//}
	//std::cerr << endl << "iter_test:end" << endl;

	//ft::vector<std::string> tmp(3, "hi");
	//std::cout << tmp << std::endl;
	//	common stuff
	//	iostreamhack();
	// std::srand(std::time(NULL));
	// ft::vector<std::string> asdf(12, "asdf");
	// std::vector<std::string> sadf(12, "sdf");
	// const ft::vector<std::string> fcont(sadf.begin(), sadf.end());
	//    fcont.rend();
	//	a lot of data test: requires more than 320mb of ram with valgrind memcheck
	//	and more than 640mb of ram with -fsanitize=address (asan + lsan on linux)
	//	changing INSANITYSIZE changes ram usage accordingly

	std::pair<const int, int> p = std::pair<int, int>(42, 42);
	ft::pair<const int, int> d = ft::pair<int, int>(42, 42);
	return (0);
}
