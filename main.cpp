#include "ft_vector.h"
#include "test_runner.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <list>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <vector>
//#include "list.hpp"
//#include "map.hpp"
//#include "queue.hpp"
//#include "priority_queue.hpp"

//#include "stack.hpp"
#include <cstdlib>
#include <ctime>
#include <iomanip>

#define    CLR_GOOD    "\033[1;32m"
#define    CLR_ERROR    "\033[41;30m"
#define    CLR_WARN    "\033[48;5;202m\033[38;5;0m"
#define    CLR_RESET    "\033[0m"
#define STR_FAIL    std::string(CLR_ERROR) + "failed test" + CLR_RESET
/*	**************************************************	*/
/*	this *MAY* decrease the exection time of the tests	*/
/*	by simply detaching c/cpp streams and cin/cout		*/
/*	NOTICE: this DOES NOT increase the performance		*/
/*	this code is just for me to note and remember		*/
/*	**************************************************	*/
void iostreamhack() {
//	detaches cstdio and iostream (this is ok if i don't use C streams with C++ streams)
//	this also creates still reachable leaks at exit because it allocates different buffers
    std::ios_base::sync_with_stdio(false);
//	unties cin and cout meaning that if i used cin i would need to manually flush cout
    std::cin.tie(NULL);
}

void error_exception(const std::string &hint = "") {
    std::string msg(CLR_ERROR);
    msg     = msg + "failed test" + CLR_RESET;
    if (!hint.empty())
        msg = msg + ":\n" + CLR_ERROR + hint + CLR_RESET;
    throw std::runtime_error(msg);
}

template<class T>
std::string ft_tostring(T val) {
    std::ostringstream oss;
    oss << val;
    return (oss.str());
}
bool intpredicate(int x) { return (x >= 666); }
bool sizetpredicate(int x) { return (x >= 666 && x <= 66666); }
bool binpredicate(int &x, int &y) { return (x == 420 || y == 420 || x == 666 || y == 666); }
bool doublecomp(double first, double second) { return (int(first) < int(second)); }
bool reversecomp(const std::string &first, const std::string &second) { return (first > second); }

template<class Container1, class Container2>
void printrelationaloperators(const Container1 &scont0, const Container1 &scont1,
                              const Container2 &fcont0, const Container2 &fcont1) {
    std::cout << "relational ops" << std::endl;
    bool e0, e1, ne0, ne1, l0, l1, le0, le1, g0, g1, ge0, ge1;
    e0  = (scont0 == scont1);
    e1  = (fcont0 == fcont1);
    ne0 = (scont0 != scont1);
    ne1 = (fcont0 != fcont1);
    l0  = (scont0 < scont1);
    l1  = (fcont0 < fcont1);
    le0 = (scont0 <= scont1);
    le1 = (fcont0 <= fcont1);
    g0  = (scont0 > scont1);
    g1  = (fcont0 > fcont1);
    ge0 = (scont0 >= scont1);
    ge1 = (fcont0 >= fcont1);
    if (e0 != e1 || ne0 != ne1 || l0 != l1 || le0 != le1 || g0 != g1 || ge0 != ge1)
        error_exception("relational operators");
    std::cout << "== " << e0 << e1 << std::endl;
    std::cout << "!= " << ne0 << ne1 << std::endl;
    std::cout << "<  " << l0 << l1 << std::endl;
    std::cout << "<= " << le0 << le1 << std::endl;
    std::cout << ">  " << g0 << g1 << std::endl;
    std::cout << ">= " << ge0 << ge1 << std::endl;
}

template<class Container>
void printcontainer(const std::string &containername, const Container &container) {
    std::cout << containername << " contains:";
    for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << std::endl;
}

template<class Container>
void printmap(const std::string &containername, const Container &container) {
    std::cout << containername << " contains:\n";
    for (typename Container::const_iterator it = container.begin(); it != container.end(); ++it)
        std::cout << it->first << " => " << it->second << std::endl;
}

template<class Container1, class Container2>
void are_equal_print(const Container1 &scont, const Container2 &fcont, size_t i = 0) {
    if (scont.size() == fcont.size() &&
        std::equal(scont.begin(), scont.end(), fcont.begin()) &&
        std::equal(fcont.begin(), fcont.end(), scont.begin())) {
        std::cout << CLR_GOOD << "containers are equal" << CLR_RESET;
        if (!i)
            std::cout << std::endl;
        else
            std::cout << CLR_GOOD << " x" << i << CLR_RESET << "\r";
    } else {
        std::cerr << CLR_ERROR << "containers are not equal" << CLR_RESET << std::endl;
        if (scont.size() != fcont.size())
            std::cerr << CLR_ERROR << "wrong size" << CLR_RESET << std::endl;
        error_exception();
    }
}
#include "test_runner.h"

template<class Container1, class Container2>
void printbothdirs(const Container1 &scont, const Container2 &fcont) {
    std::cout << "forward:" << std::endl;
    {
        typename Container1::const_iterator sit = scont.begin();
        typename Container2::const_iterator fit = fcont.begin();
        std::cout << "scont contains: ";
        while (sit != scont.end())
            std::cout << " " << *sit++;

        std::cout << std::endl << "fcont contains: ";
        while (fit != fcont.end())
		{
//        	std::cerr << "dist" << std::distance(fit, fcont.end()) << std::endl;
			std::cout << " " << *(fit++);// << std::endl;
		}
        std::cout << std::endl;
    }
    std::cout << "reverse:" << std::endl;
    {
        typename Container1::const_reverse_iterator sit = scont.rbegin();
        typename Container2::const_reverse_iterator fit = fcont.rbegin();
        std::cout << "scont contains: ";
        while (sit != scont.rend())
            std::cout << " " << *sit++;

        while (fit != fcont.rend())
            std::cerr << " " << *(fit++); //TODO: test
        std::cout << std::endl;
    }
}
//
//template <class Key, class T>
//void		printbothdirsmap(const std::map<Key, T>& scont, const ft::map<Key, T>& fcont)
//{
//	std::cout << "forward:" << std::endl;
//	{
//		typename std::map<Key, T>::const_iterator	sit = scont.begin();
//		typename ft::map<Key, T>::const_iterator	fit = fcont.begin();
//		std::cout << "smap contains: ";
//		while (sit != scont.end())
//		{
//			std::cout << " " << sit->first << "->" << sit->second;
//			++sit;
//		}
//		std::cout << std::endl << "fmap contains: ";
//		while (fit != fcont.end())
//		{
//			std::cout << " " << fit->first << "->" << fit->second;
//			++fit;
//		}
//		std::cout << std::endl;
//	}
//	std::cout << "reverse:" << std::endl;
//	{
//		typename std::map<Key, T>::const_reverse_iterator	sit = scont.rbegin();
//		typename ft::map<Key, T>::const_reverse_iterator	fit = fcont.rbegin();
//		std::cout << "smap contains: ";
//		while (sit != scont.rend())
//		{
//			std::cout << " " << sit->first << "->" << sit->second;
//			++sit;
//		}
//		std::cout << std::endl << "fmap contains: ";
//		while (fit != fcont.rend())
//		{
//			std::cout << " " << fit->first << "->" << fit->second;
//			++fit;
//		}
//		std::cout << std::endl << std::endl;
//	}
//}
//
//void		ft_list_tests(int ac, char **av)
//{
//	std::cout << CLR_WARN << "LIST TESTS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET << std::endl;
//	{
//		std::list<std::string>	slist;
//		ft::list<std::string>	flist;
//	}
//
//	{
//		std::list<std::string>	slist(av, av + ac);
//		ft::list<std::string>	flist(av, av + ac);
//		std::list<int>	slistint;
//		ft::list<int>	flistint;
//
//		std::cout << "Test " << slist.max_size() << "\t" << flist.max_size() << std::endl;
//		std::cout << "Test " << slistint.max_size() << "\t" << flistint.max_size() << std::endl;
//
//		printcontainer("slist", slist);
//		printcontainer("flist", flist);
//
//		std::cout << slist.size() << std::endl;
//		std::cout << flist.size() << std::endl;
//
//	}
//
//	std::list<std::string>	slist2(5, "hello");
//	ft::list<std::string>	flist2(5, "hello");
//
//	int	i = 0;
//	for (std::list<std::string>::iterator it = slist2.begin(); it != slist2.end(); it++)
//	{
//		i++;
//		(*it) += ft_tostring(i);
//	}
//
//	i = 0;
//	for (ft::list<std::string>::iterator it = flist2.begin(); it != flist2.end(); it++)
//	{
//		i++;
//		(*it) += ft_tostring(i);
//	}
//
//	printbothdirs(slist2, flist2);
//
//	std::list<std::string>	slist3(slist2);
//	ft::list<std::string>	flist3(flist2);
//
//	printbothdirs(slist3, flist3);
//
//	slist3 = slist2;
//	flist3 = flist2;
//
//	slist3.front() = "front1";
//	slist3.back() = "back5";
//	flist3.front() = "front1";
//	flist3.back() = "back5";
//
//	std::cout << "std\tfront: " << slist3.front() << " back: " << slist3.back() << std::endl;
//	std::cout << "ft\tfront: " << flist3.front() << " back: " << flist3.back() << std::endl;
//	slist3.push_front("hello0");
//	slist3.push_back("hello6");
//	flist3.push_front("hello0");
//	flist3.push_back("hello6");
//
//	{
//		printcontainer("slist3", slist3);
//		printcontainer("flist3", flist3);
//		std::cout << slist3.size() << "\t" << std::distance(slist3.rbegin(), slist3.rend()) << std::endl;
//		std::cout << flist3.size() << "\t" << std::distance(flist3.rbegin(), flist3.rend()) << std::endl;
//	}
//
//	{
//		std::cout << "-------------" << std::endl;
//		std::list<std::string>::iterator sit = slist3.begin();
//		ft::list<std::string>::iterator fit = flist3.begin();
//
//		while (sit != slist3.end() && fit != flist3.end())
//		{
//			std::ptrdiff_t	sdist = std::distance(sit, slist3.begin());
//			std::ptrdiff_t	fdist = std::distance(fit, flist3.begin());
//			std::cout << sdist << "\t" << fdist << std::endl;
//			++sit;
//			++fit;
//		}
//	}
//	{
//		std::cout << "-------------" << std::endl;
//		std::list<std::string>::reverse_iterator sit = slist3.rbegin();
//		ft::list<std::string>::reverse_iterator fit = flist3.rbegin();
//
//		while (sit != slist3.rend() && fit != flist3.rend())
//		{
//			std::ptrdiff_t	sdist = std::distance(sit, slist3.rbegin());
//			std::ptrdiff_t	fdist = std::distance(fit, flist3.rbegin());
//			std::cout << sdist << "\t" << fdist << std::endl;
//			++sit;
//			++fit;
//		}
//	}
//
//	std::cout << "std::distance slist3: " << std::distance(slist3.begin(), slist3.end()) << std::endl;
//	std::cout << "std::distance flist3: " << std::distance(flist3.begin(), flist3.end()) << std::endl;
//	std::cout << "ft::distance slist3: " << ft::distance(slist3.begin(), slist3.end()) << std::endl;
//	std::cout << "ft::distance flist3: " << ft::distance(flist3.begin(), flist3.end()) << std::endl;
//
//	{
//		std::list<std::string>	slist0(flist2.begin(), flist2.end());
//		ft::list<std::string>	flist0(flist2.begin(), flist2.end());
//
//		std::list<std::string>	slist1(flist3.begin(), flist3.end());
//		ft::list<std::string>	flist1(flist3.begin(), flist3.end());
//
//		printrelationaloperators(slist0, slist1, flist0, flist1);
//
//		slist0.clear();
//		flist0.clear();
//
//		slist1.assign(10, "mda");
//		flist1.assign(10, "mda");
//		slist0.assign(slist1.begin(), slist1.end());
//		flist0.assign(flist1.begin(), flist1.end());
//
//		std::cout << "after assign:" << std::endl;
//		printrelationaloperators(slist0, slist1, flist0, flist1);
//		are_equal_print(slist0, flist0);
//		are_equal_print(slist1, flist1);
//
//		slist0.clear();
//		slist1.clear();
//		flist0.clear();
//		flist1.clear();
//		std::cout << "after clear:" << std::endl;
//		printrelationaloperators(slist0, slist1, flist0, flist1);
//
//		slist0.resize(1, "first");
//		flist0.resize(1, "first");
//
//		std::cout << "empty?:\t\t" << slist0.empty() << " " << flist0.empty() << std::endl;
//		slist0.resize(10, "lmao");
//		flist0.resize(10, "lmao");
//		std::cout << "resize(10):\t" << slist0.size() << " " << flist0.size() << std::endl;
//		std::cout << "empty?:\t\t" << slist0.empty() << " " << flist0.empty() << std::endl;
//		printbothdirs(slist0, flist0);
//		are_equal_print(slist0, flist0);
//
//		slist0.resize(1);
//		flist0.resize(1);
//		std::cout << "resize(1):\t" << slist0.size() << " " << flist0.size() << std::endl;
//		std::cout << "empty?:\t\t" << slist0.empty() << " " << flist0.empty() << std::endl;
//		printbothdirs(slist0, flist0);
//		are_equal_print(slist0, flist0);
//
//		slist0.resize(0);
//		flist0.resize(0);
//		std::cout << "resize(0):\t" << slist0.size() << " " << flist0.size() << std::endl;
//		std::cout << "empty?:\t\t" << slist0.empty() << " " << flist0.empty() << std::endl;
//		printbothdirs(slist0, flist0);
//		are_equal_print(slist0, flist0);
//
//		{
//			std::cout << "list of lists test" << std::endl;
//
//			std::list< std::list<std::string> >	sll;
//			ft::list< ft::list<std::string> >	fll;
//
//			sll.push_back(slist0);		fll.push_back(flist0);
//			sll.push_back(slist1);		fll.push_back(flist1);
//			sll.push_back(slist2);		fll.push_back(flist2);
//			sll.push_back(slist3);		fll.push_back(flist3);
//
//			sll.insert(sll.begin(), sll.begin(), sll.end());
//			fll.insert(fll.begin(), fll.begin(), fll.end());
//			sll.insert(++(sll.begin()), sll.begin(), sll.end());
//			fll.insert(++(fll.begin()), fll.begin(), fll.end());
//			sll.insert(--(sll.end()), sll.begin(), sll.end());
//			fll.insert(--(fll.end()), fll.begin(), fll.end());
//			sll.insert(sll.end(), sll.begin(), sll.end());
//			fll.insert(fll.end(), fll.begin(), fll.end());
//
//			if (sll.size() != fll.size())
//				error_exception();
//			std::list< std::list<std::string> >::const_iterator	scit = sll.begin();
//			ft::list< ft::list<std::string> >::const_iterator	fcit = fll.begin();
//			size_t	cnt(0);
//			while (scit != sll.end())
//				are_equal_print(*scit++, *fcit++, ++cnt);
//			std::cout << std::endl;
//		}
//
//	}
//
//	std::cout << "---------------------------" << std::endl;
//	printcontainer("slist2", slist2);
//	printcontainer("flist2", flist2);
//	are_equal_print(slist2, flist2);
//	printcontainer("slist3", slist3);
//	printcontainer("flist3", flist3);
//	are_equal_print(slist3, flist3);
//
//	slist3.swap(slist3);
//	flist3.swap(flist3);
//
//	std::cout << "\nafter swap:" << std::endl;
//	slist3.swap(slist2);
//	flist3.swap(flist2);
//
//	printcontainer("slist2", slist2);
//	printcontainer("flist2", flist2);
//	are_equal_print(slist2, flist2);
//	printcontainer("slist3", slist3);
//	printcontainer("flist3", flist3);
//	are_equal_print(slist3, flist3);
//
//	std::cout << "\nafter std::swap back:" << std::endl;
//	swap(slist2, slist3);
//	swap(flist2, flist3);
//	printcontainer("slist2", slist2);
//	printcontainer("flist2", flist2);
//	are_equal_print(slist2, flist2);
//	printcontainer("slist3", slist3);
//	printcontainer("flist3", flist3);
//	are_equal_print(slist3, flist3);
//
//	std::cout << "\nafter insert0:" << std::endl;
//	slist2.insert(slist2.begin(), "insert0");
//	flist2.insert(flist2.begin(), "insert0");
//	printcontainer("slist2", slist2);
//	printcontainer("flist2", flist2);
//	are_equal_print(slist2, flist2);
//
//	std::cout << "\nafter insert1:" << std::endl;
//	slist2.insert(++(++slist2.begin()), "insert1");
//	flist2.insert(++(++flist2.begin()), "insert1");
//	printcontainer("slist2", slist2);
//	printcontainer("flist2", flist2);
//	are_equal_print(slist2, flist2);
//
//	std::cout << "\nafter insend:" << std::endl;
//	slist2.insert(slist2.end(), "insend");
//	flist2.insert(flist2.end(), "insend");
//	printcontainer("slist2", slist2);
//	printcontainer("flist2", flist2);
//	are_equal_print(slist2, flist2);
//
//	{
//		std::cout << "---------------------------" << std::endl;
//		std::list<int>				slist;
//		ft::list<int>				flist;
//		std::list<int>::iterator	sit, sit2;
//		ft::list<int>::iterator		fit, fit2;
//
//		// set some initial values:
//		for (int i = 1; i <= 5; ++i)
//			slist.push_back(i);		// 1 2 3 4 5
//		for (int i = 1; i <= 5; ++i)
//			flist.push_back(i);		// 1 2 3 4 5
//
//		sit = slist.begin();
//		fit = flist.begin();
//		++sit;
//		++fit;
//		if (*sit == *fit && *sit == 2 && std::distance(slist.begin(), sit) == std::distance(flist.begin(), fit))
//			std::cout << "both now point to number 2" << std::endl;
//
//		sit2 = slist.insert(sit, 10);						// 1 10 2 3 4 5
//		fit2 = flist.insert(fit, 10);						// 1 10 2 3 4 5
//		// "sit" still points to number 2							^
//		// "fit" still points to number 2							^
//		if (*sit2 != *fit2)
//			error_exception();
//
//		if (*sit == *fit && *sit == 2 && std::distance(slist.begin(), sit) == std::distance(flist.begin(), fit))
//			std::cout << "both still point to number 2" << std::endl;
//
//		slist.insert(sit, 2, 20);					//	1 10 20 20 2 3 4 5
//		flist.insert(fit, 2, 20);					//	1 10 20 20 2 3 4 5
//		--sit;		// it points now to the second 20			^
//		--fit;		// it points now to the second 20			^
//		if (*sit == *fit && *sit == 20 && std::distance(slist.begin(), sit) == std::distance(flist.begin(), fit))
//			std::cout << "both now point to second 20" << std::endl;
//
//		std::vector<int>	myvector(2, 30);
//		slist.insert(sit, myvector.begin(), myvector.end());
//		flist.insert(fit, myvector.begin(), myvector.end());
//													// 1 10 20 30 30 20 2 3 4 5
//													//				 ^
//		if (*sit == *fit && *sit == 20 && std::distance(slist.begin(), sit) == std::distance(flist.begin(), fit))
//			std::cout << "both still point to second 20" << std::endl;
//
//		sit = slist.erase(sit);
//		fit = flist.erase(fit);
//		if (*sit != *fit)
//			error_exception();
//		printcontainer("slist", slist);
//		printcontainer("flist", flist);
//		printbothdirs(slist, flist);
//	}
//
//	{
//		std::cout << "---------------------------" << std::endl;
//		std::list<int>	slist;
//		ft::list<int>	flist;
//
//		slist.insert(slist.begin(), 666, 6);
//		flist.insert(flist.begin(), 666, 6);
//		printcontainer("slist", slist);
//		printcontainer("flist", flist);
//
//		are_equal_print(slist, flist);
//
//		slist.erase(slist.begin(), --(slist.end()));
//		flist.erase(flist.begin(), --(flist.end()));
//		printcontainer("slist", slist);
//		printcontainer("flist", flist);
//
//		are_equal_print(slist, flist);
//		slist.erase(slist.begin());
//		flist.erase(flist.begin());
//		printcontainer("slist", slist);
//		printcontainer("flist", flist);
//
//		are_equal_print(slist, flist);
//
//		slist.erase(slist.begin(), slist.end());
//		flist.erase(flist.begin(), flist.end());
//		printcontainer("slist", slist);
//		printcontainer("flist", flist);
//
//		are_equal_print(slist, flist);
//	}
//
//	{
//		std::cout << "---------------------------" << std::endl;
//		std::list<int>	slist(666, 666);
//		ft::list<int>	flist(666, 666);
//
//		are_equal_print(slist, flist);
//		slist.remove(666);
//		flist.remove(666);
//		printcontainer("slist", slist);
//		printcontainer("flist", flist);
//
//		are_equal_print(slist, flist);
//
//		slist.insert(slist.begin(), 666, 666);
//		slist.insert(slist.begin(), 420, 420);
//		flist.insert(flist.begin(), 666, 666);
//		flist.insert(flist.begin(), 420, 420);
//
//		slist.reverse();
//		flist.reverse();
//		printcontainer("slist", slist);
//		printcontainer("flist", flist);
//		are_equal_print(slist, flist);
//
//		slist.remove_if(intpredicate);
//		flist.remove_if(intpredicate);
//		printcontainer("slist", slist);
//		printcontainer("flist", flist);
//		are_equal_print(slist, flist);
//	}
//
//	{
//		std::cout << "---------------------------" << std::endl;
//		printcontainer("slist3", slist3);
//		printcontainer("flist3", flist3);
//		printbothdirs(slist3, flist3);
//		are_equal_print(slist3, flist3);
//
//		slist3.reverse();
//		flist3.reverse();
//
//		printcontainer("slist3 after reverse", slist3);
//		printcontainer("flist3 after reverse", flist3);
//		printbothdirs(slist3, flist3);
//		are_equal_print(slist3, flist3);
//
//		slist3.reverse();
//		flist3.reverse();
//
//		printcontainer("slist3 after reverse", slist3);
//		printcontainer("flist3 after reverse", flist3);
//		printbothdirs(slist3, flist3);
//		are_equal_print(slist3, flist3);
//	}
//
//	{
//		std::cout << "---------------------------" << std::endl;
//		std::list<int>	slist(666, 666);
//		ft::list<int>	flist(666, 666);
//		slist.insert(slist.begin(), 420, 420);
//		flist.insert(flist.begin(), 420, 420);
//
//		slist.unique();
//		flist.unique();
//		printcontainer("slist after unique", slist);
//		printcontainer("flist after unique", flist);
//		are_equal_print(slist, flist);
//
//		slist.unique(binpredicate);
//		flist.unique(binpredicate);
//		printcontainer("slist after unique(binpredicate)", slist);
//		printcontainer("flist after unique(binpredicate)", flist);
//		are_equal_print(slist, flist);
//
//		std::cout << "---------------------------" << std::endl;
//		std::cout << "assignster" << std::endl;
//		std::list<int>	sbar(4, 200);
//		ft::list<int>	fbar(4, 200);
//		slist.assign(200, 666);
//		flist.assign(200, 666);
//		are_equal_print(slist, flist);
//
//		slist.assign(sbar.begin(), sbar.end());
//		flist.assign(fbar.begin(), fbar.end());
//		are_equal_print(slist, flist);
//
//		sbar.assign(400, 666);
//		fbar.assign(400, 666);
//		are_equal_print(sbar, fbar);
//		slist.assign(sbar.begin(), sbar.end());
//		flist.assign(fbar.begin(), fbar.end());
//		are_equal_print(slist, flist);
//	}
//
//	{
//		std::cout << "---------------------------" << std::endl;
//		std::list<int>				mylist1, mylist2;
//		ft::list<int>				ftlist1, ftlist2;
//		std::list<int>::iterator	it;
//		ft::list<int>::iterator		ft;
//
//		// set some initial values:
//		for (int i = 1; i <= 4; ++i)
//			mylist1.push_back(i);		// mylist1: 1 2 3 4
//		for (int i = 1; i <= 4; ++i)
//			ftlist1.push_back(i);		// ftlist1: 1 2 3 4
//
//		for (int i = 1; i <= 3; ++i)
//			mylist2.push_back(i * 10);	// mylist2: 10 20 30
//		for (int i = 1; i <= 3; ++i)
//			ftlist2.push_back(i * 10);	// ftlist2: 10 20 30
//
//		it = mylist1.begin();
//		ft = ftlist1.begin();
//		++it;							// points to 2
//		++ft;							// points to 2
//
//		mylist1.splice(it, mylist2);	// mylist1: 1 10 20 30 2 3 4
//										// mylist2 (empty)
//										// "it" still points to 2 (the 5th element)
//		ftlist1.splice(ft, ftlist2);	// ftlist1: 1 10 20 30 2 3 4
//										// ftlist2 (empty)
//										// "it" still points to 2 (the 5th element)
//		printcontainer("mylist1.splice(it, mylist2)", mylist1);
//		printcontainer("ftlist1.splice(ft, ftlist2)", ftlist1);
//		printcontainer("mylist2 after splice above", mylist2);
//		printcontainer("ftlist2 after splice above", ftlist2);
//		std::cout << "---------------------------" << std::endl;
//
//		mylist2.splice(mylist2.begin(), mylist1, it);
//										// "it" is now invalid.
//										// mylist1: 1 10 20 30 3 4
//										// mylist2: 2
//		ftlist2.splice(ftlist2.begin(), ftlist1, ft);
//										// "it" is now invalid.
//										// mylist1: 1 10 20 30 3 4
//										// mylist2: 2
//		printcontainer("mylist2.splice(mylist2.begin(), mylist1, it)", mylist2);
//		printcontainer("ftlist2.splice(ftlist2.begin(), ftlist1, ft)", ftlist2);
//		printcontainer("mylist1 after splice above", mylist1);
//		printcontainer("ftlist1 after splice above", ftlist1);
//		std::cout << "---------------------------" << std::endl;
//
//		it = mylist1.begin();
//		std::advance(it, 3);			// "it" points now to 30
//		ft = ftlist1.begin();
//		std::advance(ft, 3);			// "ft" points now to 30
//
//		mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
//										// mylist1: 30 3 4 1 10 20
//		ftlist1.splice(ftlist1.begin(), ftlist1, ft, ftlist1.end());
//										// ftlist1: 30 3 4 1 10 20
//
//		printcontainer("mylist1", mylist1);
//		printcontainer("mylist2", mylist2);
//		printcontainer("ftlist1", ftlist1);
//		printcontainer("ftlist2", ftlist2);
//
//		mylist2.splice(mylist2.end(), mylist1, mylist1.begin(), mylist1.end());
//										// mylist2: 2 30 3 4 1 10 20
//		ftlist2.splice(ftlist2.end(), ftlist1, ftlist1.begin(), ftlist1.end());
//										// mylist2: 2 30 3 4 1 10 20
//
//		printcontainer("mylist1", mylist1);
//		printcontainer("mylist2", mylist2);
//		printcontainer("ftlist1", ftlist1);
//		printcontainer("ftlist2", ftlist2);
//	}
//
//
//	{
//		std::cout << "---------------------------" << std::endl;
//		std::list<double>	sfirst, ssecond;
//		ft::list<double>	ffirst, fsecond;
//		sfirst.push_back(3.1);		ffirst.push_back(3.1);
//		sfirst.push_back(2.2);		ffirst.push_back(2.2);
//		sfirst.push_back(2.9);		ffirst.push_back(2.9);
//
//		ssecond.push_back(3.7);		fsecond.push_back(3.7);
//		ssecond.push_back(7.1);		fsecond.push_back(7.1);
//		ssecond.push_back(1.4);		fsecond.push_back(1.4);
//
//		printcontainer("sfirst before sort", sfirst);
//		printcontainer("ffirst before sort", ffirst);
//		printcontainer("ssecond before sort", ssecond);
//		printcontainer("fsecond before sort", fsecond);
//		sfirst.sort();				ffirst.sort();
//		ssecond.sort();				fsecond.sort();
//		printcontainer("sfirst after sort", sfirst);
//		printcontainer("ffirst after sort", ffirst);
//		printcontainer("ssecond after sort", ssecond);
//		printcontainer("fsecond after sort", fsecond);
//		are_equal_print(sfirst, ffirst);
//
//		std::cout << "merging ------------------" << std::endl;
//		sfirst.merge(ssecond);
//		ffirst.merge(fsecond);
//		printcontainer("sfirst after merge", sfirst);
//		printcontainer("ffirst after merge", ffirst);
//		are_equal_print(sfirst, ffirst);
//
//		// (second is now empty)
//
//		ssecond.push_back(2.1);		fsecond.push_back(2.1);
//
//		std::cout << "merging2 -----------------" << std::endl;
//		sfirst.merge(ssecond, doublecomp);
//		ffirst.merge(fsecond, doublecomp);
//
//		printcontainer("sfirst after merge", sfirst);
//		printcontainer("ffirst after merge", ffirst);
//		are_equal_print(sfirst, ffirst);
//	}
//
//
//	{
//		std::cout << "---------------------------" << std::endl;
//		std::list<std::string>::iterator	sit = slist3.begin();
//		ft::list<std::string>::iterator		fit = flist3.begin();
//		printcontainer("slist3 before sort", slist3);
//		printcontainer("flist3 before sort", flist3);
//		std::cout << "sit before sort: " << *sit << std::endl;
//		std::cout << "fit before sort: " << *fit << std::endl;
//		are_equal_print(slist3, flist3);
//		slist3.sort();
//		flist3.sort();
//		printcontainer("slist3 after sort", slist3);
//		printcontainer("flist3 after sort", flist3);
//		std::cout << "sit after sort: " << *sit << std::endl;
//		std::cout << "fit after sort: " << *fit << std::endl;
//		are_equal_print(slist3, flist3);
//	}
//
//	{
//		std::cout << "---------------------------" << std::endl;
//		std::list<std::string>::iterator	sit = slist3.begin();
//		ft::list<std::string>::iterator		fit = flist3.begin();
//		printcontainer("slist3 before backwardsort", slist3);
//		printcontainer("flist3 before backwardsort", flist3);
//		std::cout << "sit before sort: " << *sit << std::endl;
//		std::cout << "fit before sort: " << *fit << std::endl;
//		are_equal_print(slist3, flist3);
//		slist3.sort(reversecomp);
//		flist3.sort(reversecomp);
//		printcontainer("slist3 after backwardsort", slist3);
//		printcontainer("flist3 after backwardsort", flist3);
//		std::cout << "sit after sort: " << *sit << std::endl;
//		std::cout << "fit after sort: " << *fit << std::endl;
//		are_equal_print(slist3, flist3);
//	}
//
//	std::cout << CLR_GOOD << "list tests passed" << CLR_RESET << std::endl << std::endl;
//}

void ft_vector_tests() {
    std::cout << CLR_WARN << "VECTOR TESTS <<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET
              << std::endl;
    {
        std::vector<std::string> svect;
        ft::vector<std::string>  fvect;
        std::cout << svect.size() << " = " << fvect.size() << std::endl;
        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
        std::cout << svect.max_size() << " = " << fvect.max_size() << std::endl;

        std::vector<int> svectint;
        ft::vector<int>  fvectint;
        std::cout << svectint.size() << " = " << fvectint.size() << std::endl;
        std::cout << svectint.capacity() << " = " << fvectint.capacity() << std::endl;
        std::cout << svectint.max_size() << " = " << fvectint.max_size() << std::endl;

    }


    {
        std::cout << "-------------" << std::endl;
        std::vector<std::string> svect(7, "hello");
        ft::vector<std::string>  fvect(7, "hello");
        std::cout << svect.size() << " = " << fvect.size() << std::endl;
        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
        std::cout << svect.max_size() << " = " << fvect.max_size() << std::endl;

        {
            std::vector<std::string> svect2(svect);
            ft::vector<std::string>  fvect2(fvect);
            std::cout << svect2.size() << " = " << fvect2.size() << std::endl;
            std::cout << svect2.capacity() << " = " << fvect2.capacity() << std::endl;
            std::cout << svect2.max_size() << " = " << fvect2.max_size() << std::endl;
            ASSERT_EQUAL(svect2, fvect2);
            svect2.clear();
            fvect2.clear();
            std::cout << svect2.size() << " = " << fvect2.size() << std::endl;
            std::cout << svect2.capacity() << " = " << fvect2.capacity() << std::endl;
            std::cout << svect2.max_size() << " = " << fvect2.max_size() << std::endl;
            ASSERT_EQUAL(svect2, fvect2);

            std::vector<std::string> svect3(7, "hello");
            ft::vector<std::string>  fvect3(7, "hello");
            svect2 = svect3;
            fvect2 = fvect3;
            std::cout << svect2.size() << " = " << fvect2.size() << std::endl;
            std::cout << svect2.capacity() << " = " << fvect2.capacity() << std::endl;
            std::cout << svect2.max_size() << " = " << fvect2.max_size() << std::endl;
            ASSERT_EQUAL(svect2, fvect2);

            svect2.reserve(100);
            fvect2.reserve(100);
            std::cout << svect2.size() << " = " << fvect2.size() << std::endl;
            std::cout << svect2.capacity() << " = " << fvect2.capacity() << std::endl;
            std::cout << svect2.max_size() << " = " << fvect2.max_size() << std::endl;
            ASSERT_EQUAL(svect2, fvect2);
        }

        printbothdirs(svect, fvect);

        std::cout << "front and back change" << std::endl;
        svect.front() = "front";
        svect.back()  = "back";
        fvect.front() = "front";
        fvect.back()  = "back";

        std::vector<std::string>::iterator sit = svect.begin();
        ft::vector<std::string>::iterator  fit = fvect.begin();

        for (size_t i = 1; sit != svect.end() && fit != fvect.end(); ++i) {
            *sit++ += ft_tostring(i);
            *fit++ += ft_tostring(i);
        }

        printbothdirs(svect, fvect);

        sit = svect.begin();
        fit = fvect.begin();

        while (sit != svect.end() && fit != fvect.end()) {
            std::ptrdiff_t sdist = std::distance(sit, svect.begin());
            std::ptrdiff_t fdist = std::distance(fit, fvect.begin());
            std::cout << sdist << "\t" << fdist << std::endl;
            sit = 1 + sit;
            fit = 1 + fit;
            sit = sit - 1;
            fit = fit - 1;
            sit = sit + 1;
            fit = fit + 1;
        }
    }

//    {
//        /*		this block is full of crap			*/
//        std::cout << "-------------" << std::endl;
//        std::vector<std::string>	svect(7, "hello");
//        ft::vector<std::string>		fvect(7, "hello");
//        std::vector<std::string>::reverse_iterator	sit = svect.rbegin();
//        ft::vector<std::string>::reverse_iterator	fit = fvect.rbegin();
//
//        std::vector<std::string>::const_reverse_iterator	sit2 = sit;
//        ft::vector<std::string>::const_reverse_iterator		fit2 = fit;
//
//        /*		this it the most painfull part		*/
//        std::cout << sit2 - sit << fit2 - fit;
//        if (sit <= sit2)
//            std::cout << "allo";
//        if (fit <= fit2)
//            std::cout << "allo\n";
//
//        while (sit != svect.rend() && fit != fvect.rend())
//        {
//            std::ptrdiff_t	sdist = std::distance(sit, svect.rbegin());
//            std::ptrdiff_t	fdist = std::distance(fit, fvect.rbegin());
//            std::cout << sdist << "\t" << fdist << std::endl;
//            ++sit;
//            fit = 1 + fit;
//        }
//        /*		i hate this part really much		*/
//    }

    {
        std::cout << "-------------" << std::endl;
        std::cout << "swapster" << std::endl;
        std::vector<int> sfoo(2, 100);   // two ints with a value of 100
        ft::vector<int>  ffoo(2, 100);   // two ints with a value of 100
        std::vector<int> sbar(4, 200);   // four ints with a value of 200
        ft::vector<int>  fbar(4, 200);   // four ints with a value of 200

        printcontainer("sfoo", sfoo);
        printcontainer("ffoo", ffoo);
        printcontainer("sbar", sbar);
        printcontainer("fbar", fbar);
        ASSERT_EQUAL(sfoo, ffoo);
        ASSERT_EQUAL(sbar, fbar);

        std::vector<int>::iterator sit1 = sfoo.begin();
        ft::vector<int>::iterator  fit1 = ffoo.begin();
        std::vector<int>::iterator sit2 = sbar.begin();
        ft::vector<int>::iterator  fit2 = fbar.begin();
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        std::cout << sbar.capacity() << " = " << fbar.capacity() << std::endl;
        std::cout << *sit1 << " " << *sit2 << std::endl;
        std::cout << *fit1 << " " << *fit2 << std::endl;

        sfoo.swap(sbar);
        ffoo.swap(fbar);

        printcontainer("sfoo", sfoo);
        printcontainer("ffoo", ffoo);
        printcontainer("sbar", sbar);
        printcontainer("fbar", fbar);
        ASSERT_EQUAL(sfoo, ffoo);
        ASSERT_EQUAL(sbar, fbar);

        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        std::cout << sbar.capacity() << " = " << fbar.capacity() << std::endl;

        std::cout << *sit1 << " " << *sit2 << std::endl;
        std::cout << *fit1 << " " << *fit2 << std::endl;

        try { sfoo.at(2378); }
        catch (const std::exception &e) { std::cerr << e.what() << std::endl; }
        try { ffoo.at(2378); }
        catch (const std::exception &e) { std::cerr << e.what() << std::endl; }
        try { sfoo.resize(sfoo.max_size() + 1); }
        catch (const std::exception &e) { std::cerr << e.what() << std::endl; }
        try { ffoo.resize(ffoo.max_size() + 1); }
        catch (const std::exception &e) { std::cerr << e.what() << std::endl; }
        ASSERT_EQUAL(sfoo, ffoo);
        ASSERT_EQUAL(sbar, fbar);

        std::cout << "-------------" << std::endl;
        std::cout << "assignster" << std::endl;
        sfoo.assign(200, 666);
        ffoo.assign(200, 666);
        std::cout << sfoo.size() << " = " << ffoo.size() << std::endl;
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sfoo.assign(sbar.begin(), sbar.end());
        ffoo.assign(fbar.begin(), fbar.end());
        std::cout << sfoo.size() << " = " << ffoo.size() << std::endl;
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sbar.assign(400, 666);
        fbar.assign(400, 666);
        sfoo.assign(sbar.begin(), sbar.end());
        ffoo.assign(fbar.begin(), fbar.end());
        std::cout << sfoo.size() << " = " << ffoo.size() << std::endl;
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);
    }

    {
        std::cout << "-------------" << std::endl;
        std::vector<int>::size_type ssz;
        std::vector<int>            sfoo;
        ft::vector<int>::size_type  fsz;
        ft::vector<int>             ffoo;
        ssz = sfoo.capacity();
        fsz = ffoo.capacity();
        std::cout << "making foo grow:\n";

        for (int i = 0; i < 100; ++i) {
            sfoo.push_back(i);
            ffoo.push_back(i);
            if (ssz != sfoo.capacity() || fsz != ffoo.capacity()) {
                ssz = sfoo.capacity();
                fsz = ffoo.capacity();
                std::cout << "capacity changed: " << ssz << "\t" << fsz << '\n';
            }
        }
        ASSERT_EQUAL(sfoo, ffoo);

        std::cout << "making foo smaller:\n";
        for (int i = 0; i < 64; ++i) {
            sfoo.pop_back();
            ffoo.pop_back();
            if (ssz != sfoo.capacity() || fsz != ffoo.capacity()) {
                ssz = sfoo.capacity();
                fsz = ffoo.capacity();
                std::cout << "capacity changed: " << ssz << "\t" << fsz << '\n';
            }
        }
        std::cout << "sizes changed: " << sfoo.size() << "\t" << ffoo.size() << '\n';
        ASSERT_EQUAL(sfoo, ffoo);
    }

    {
        std::cout << "-------------" << std::endl;
        std::vector<int> sfoo;
        ft::vector<int>  ffoo;

        // set some initial content:
        for (int i = 1; i < 10; i++) {
            sfoo.push_back(i);
            ffoo.push_back(i);
        }

        sfoo.resize(5);
        ffoo.resize(5);
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sfoo.resize(8, 100);
        ffoo.resize(8, 100);
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sfoo.resize(12);
        ffoo.resize(12);
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sfoo.resize(0);
        ffoo.resize(0);
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sfoo.resize(20, 6);
        ffoo.resize(20, 6);
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sfoo.resize(666, 666);
        ffoo.resize(666, 666);
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        sfoo.resize(6, 6626);
        ffoo.resize(6, 6626);
        std::cout << sfoo.capacity() << " = " << ffoo.capacity() << std::endl;
        ASSERT_EQUAL(sfoo, ffoo);

        printcontainer("sfoo", sfoo);
        printcontainer("ffoo", ffoo);
    }

//    {
//        std::cout << "-------------\ninsertster (capacities may differ depending on platform)" << std::endl;
//        std::vector<int>           svect(3, 100);
//        ft::vector<int>            fvect(3, 100);
//        std::vector<int>::iterator sit;
//        ft::vector<int>::iterator  fit;
//        printcontainer("svect", svect);
//        printcontainer("fvect", fvect);
//        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//        ASSERT_EQUAL(svect, fvect);
//
//        sit = svect.begin();
//        fit = fvect.begin();
//        sit = svect.insert(sit, 200);
//        fit = fvect.insert(fit, 200);
//        printcontainer("svect", svect);
//        printcontainer("fvect", fvect);
//        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//        ASSERT_EQUAL(svect, fvect);
//
//        svect.insert(sit, 1, 300);
//        fvect.insert(fit, 1, 300);
//        printcontainer("svect", svect);
//        printcontainer("fvect", fvect);
//        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//        ASSERT_EQUAL(svect, fvect);
//
//        // "it" no longer valid, get a new one:
//        sit = svect.begin();
//        fit = fvect.begin();
//
//        std::vector<int> svect2(4, 400);
//        ft::vector<int>  fvect2(4, 400);
////        svect.insert(sit + 2, svect2.begin(), svect2.end());
////        fvect.insert(fit + 2, fvect2.begin(), fvect2.end());
////        printcontainer("svect", svect);
////        printcontainer("fvect", fvect);
////        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
////        ASSERT_EQUAL(svect, fvect);
//
//        int myarray[] = {501, 502, 503};
//        svect.insert(svect.begin(), myarray, myarray + 3);
//        fvect.insert(fvect.begin(), myarray, myarray + 3);
//        printcontainer("svect", svect);
//        printcontainer("fvect", fvect);
//        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
//        ASSERT_EQUAL(svect, fvect);
//
////        svect.insert(svect.begin(), svect.begin(), svect.end());
////        fvect.insert(fvect.begin(), fvect.begin(), fvect.end());
////        printcontainer("svect", svect);
////        printcontainer("fvect", fvect);
////        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
////        ASSERT_EQUAL(svect, fvect);
//
////        svect.insert(svect.end(), svect.begin(), svect.end());
////        fvect.insert(fvect.end(), fvect.begin(), fvect.end());
////        printcontainer("svect", svect);
////        printcontainer("fvect", fvect);
////        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
////        ASSERT_EQUAL(svect, fvect);
//
//        std::cout << "vector of vectors inserts" << std::endl;
//        std::vector<std::vector<int> > svv;
//        ft::vector<ft::vector<int> >   fvv;
//        svv.push_back(svect);
//        fvv.push_back(fvect);
//        svv.push_back(svect2);
//        fvv.push_back(fvect2);
//
//        svv.insert(svv.begin(), svv.begin(), svv.end());
//        fvv.insert(fvv.begin(), fvv.begin(), fvv.end());
//#if (__cplusplus < 201103L)    //	tests below fail on linux with c++11 std
//        svv.insert(svv.end() - 1, svv.begin(), svv.end());
//        fvv.insert(fvv.end() - 1, fvv.begin(), fvv.end());
//        svv.insert(svv.end(), svv.begin(), svv.end());
//        fvv.insert(fvv.end(), fvv.begin(), fvv.end());
//#endif
//        svv.erase(svv.begin() + 1, svv.end() - 3);
//        fvv.erase(fvv.begin() + 1, fvv.end() - 3);
//
//        if (svv.size() != fvv.size())
//            error_exception();
//        size_t      cnt(0);
//        for (size_t i = 0; i < svv.size(); i++)
//            ASSERT_EQUAL(svv.at(i), fvv.at(i));
//        std::cout << std::endl;
//    }

    {
        std::cout << "-------------" << std::endl;
        std::vector<int>           svect;
        ft::vector<int>            fvect;
        std::vector<int>::iterator sit;
        ft::vector<int>::iterator  fit;

        // set some values (from 1 to 10)
        for (int i = 1; i <= 10; i++) {
            svect.push_back(i);
            fvect.push_back(i);
        }
        printcontainer("svect", svect);
        printcontainer("fvect", fvect);
        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
        ASSERT_EQUAL(svect, fvect);

        // erase the 6th element
        ASSERT_EQUAL(svect, fvect);
        sit = svect.erase(svect.begin() + 5);
        fit = fvect.erase(fvect.begin() + 5);
        //error
        ASSERT_EQUAL(*sit, *fit);
        ASSERT_EQUAL(svect, fvect);

        // erase the first 3 elements:
        svect.erase(svect.begin(), svect.begin() + 3);
        fvect.erase(fvect.begin(), fvect.begin() + 3);
        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
        ASSERT_EQUAL(svect, fvect);

        svect.erase(svect.end() - 4, svect.end() - 1);
        fvect.erase(fvect.end() - 4, fvect.end() - 1);
        ASSERT_EQUAL(svect, fvect);

        svect.erase(svect.begin(), svect.end());
        fvect.erase(fvect.begin(), fvect.end());
        std::cout << svect.capacity() << " = " << fvect.capacity() << std::endl;
        ASSERT_EQUAL(svect, fvect);
    }

    {
        std::cout << "--------------" << std::endl;
        std::vector<std::string> svect0;
        ft::vector<std::string>  fvect0;
        std::vector<std::string> svect1;
        ft::vector<std::string>  fvect1;
        printrelationaloperators(svect0, svect1, fvect0, fvect1);

        svect0.push_back("vector");
        fvect0.push_back("vector");
        printrelationaloperators(svect0, svect1, fvect0, fvect1);
        ASSERT_EQUAL(svect0, fvect0);

        svect1.push_back("vector");
        fvect1.push_back("vector");
        printrelationaloperators(svect0, svect1, fvect0, fvect1);
        ASSERT_EQUAL(svect1, fvect1);

        svect0.push_back("vector2");
        fvect0.push_back("vector2");
        printrelationaloperators(svect0, svect1, fvect0, fvect1);
        ASSERT_EQUAL(svect0, fvect0);

        svect1.push_back("vector5");
        fvect1.push_back("vector5");
        printrelationaloperators(svect0, svect1, fvect0, fvect1);
        ASSERT_EQUAL(svect1, fvect1);

        std::cout << "member swap:" << std::endl;
        svect0.swap(svect1);
        fvect0.swap(fvect1);
        printrelationaloperators(svect0, svect1, fvect0, fvect1);
        ASSERT_EQUAL(svect0, fvect0);
        ASSERT_EQUAL(svect1, fvect1);

        std::cout << "nonmember swap:" << std::endl;
        swap(svect0, svect1);
        swap(fvect0, fvect1);
        printrelationaloperators(svect0, svect1, fvect0, fvect1);
        ASSERT_EQUAL(svect0, fvect0);
        ASSERT_EQUAL(svect1, fvect1);
    }

    {
        std::cout << "-------------" << std::endl << "vector of vectors" << std::endl;
        std::vector<std::vector<size_t> > svect;
        ft::vector<ft::vector<size_t> >   fvect;

        while (svect.size() < 20) {
            bool a(rand() % 10000000);
            svect.push_back(std::vector<size_t>(20, a));
            fvect.push_back(ft::vector<size_t>(20, a));
        }

        svect.erase(svect.begin() + 6, svect.end() - 8);
        fvect.erase(fvect.begin() + 6, fvect.end() - 8);

        if (svect.size() != fvect.size())
            error_exception();

        size_t      cnt(0);
        for (size_t i = 0; i < svect.size(); i++)
            ASSERT_EQUAL(svect[i], fvect[i]);
        std::cout << std::endl;
    }

    std::cout << CLR_GOOD << "vector tests passed" << CLR_RESET << std::endl << std::endl;
}

//void		ft_vectorbool_tests()
//{
//	std::cout << CLR_WARN << "VECTOR<bool> TESTS <<<<<<<<<<<<<<<<<<<<<<<<<<<                        " << CLR_RESET << std::endl;
//	{
//		std::vector<bool>	svect;		ft::vector<bool>	fvect;
//
//		svect.assign(20, false);					fvect.assign(20, false);
//		printrelationaloperators(svect, std::vector<bool>(20, false), fvect, ft::vector<bool>(20, false));
//
//		printcontainer("svect", svect);				printcontainer("fvect", fvect);
//		ASSERT_EQUAL(svect, fvect);
//
//		svect.flip();								fvect.flip();
//		printcontainer("svect", svect);				printcontainer("fvect", fvect);
//		ASSERT_EQUAL(svect, fvect);
//
//		svect.flip();								fvect.flip();
//		svect.front().flip();						fvect.front().flip();
//		svect.back().flip();						fvect.back().flip();
//		printcontainer("svect", svect);				printcontainer("fvect", fvect);
//		are_equal_print(svect, fvect);
//
//		svect.back().flip();						fvect.back().flip();
//		printcontainer("svect", svect);				printcontainer("fvect", fvect);
//		svect.swap(svect.front(), svect.back());	fvect.swap(fvect.front(), fvect.back());
//		printcontainer("svect", svect);				printcontainer("fvect", fvect);
//		are_equal_print(svect, fvect);
//
//		svect.flip();								fvect.flip();
//		printcontainer("svect", svect);				printcontainer("fvect", fvect);
//		are_equal_print(svect, fvect);
//	}
//
//	{
//		std::cout << "-------------" << std::endl << "vector of vectors" << std::endl;
//		std::vector< std::vector<bool> >	svect;		ft::vector< ft::vector<bool> >	fvect;
//
//		while (svect.size() < 20)
//		{
//			bool	a(rand() % 2);
//			svect.push_back(std::vector<bool>(20, a));	fvect.push_back(ft::vector<bool>(20, a));
//		}
//
//		svect.erase(svect.begin() + 6, svect.end() - 8);
//		fvect.erase(fvect.begin() + 6, fvect.end() - 8);
//
//		if (svect.size() != fvect.size())
//			error_exception();
//
//		size_t	cnt(0);
//		for (size_t i = 0; i < svect.size(); i++)
//			are_equal_print(svect[i], fvect[i], ++cnt);
//		std::cout << std::endl;
//	}
//
//	std::cout << CLR_GOOD << "vector<bool> tests passed" << CLR_RESET << std::endl << std::endl;
//}

//void		ft_map_tests()
//{
//	std::cout << CLR_WARN << "MAP TESTS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET << std::endl;
//	{
//		std::map<std::string, std::string>	smap;
//		ft::map<std::string, std::string>	fmap;
//
//		std::cout << smap.max_size() << " " << fmap.max_size() << std::endl;
//
//		std::cout << "key and value _comp methods check: " <<
//			smap.key_comp()("key1", "key2") << fmap.key_comp()("key1", "key2") <<
//			smap.value_comp()(std::make_pair("key1", "val2"), std::make_pair("key2", "val1")) <<
//			fmap.value_comp()(std::make_pair("key1", "val2"), std::make_pair("key2", "val1")) <<
//			std::endl;
//
//		smap.insert(std::pair<std::string, std::string>("key1", "val1"));
//		fmap.insert(std::pair<std::string, std::string>("key1", "val1"));
//		are_equal_print(smap, fmap);
//
//		smap.insert(std::pair<std::string, std::string>("key1", "key1"));
//		fmap.insert(std::pair<std::string, std::string>("key1", "key1"));
//
//		smap.insert(std::pair<std::string, std::string>("key2", "val2"));
//		fmap.insert(std::pair<std::string, std::string>("key2", "val2"));
//		smap.insert(std::pair<std::string, std::string>("key3", "val3"));
//		fmap.insert(std::pair<std::string, std::string>("key3", "val3"));
//		smap.insert(std::pair<std::string, std::string>("key7", "val7"));
//		fmap.insert(std::pair<std::string, std::string>("key7", "val7"));
//		smap.insert(std::pair<std::string, std::string>("key4", "val4"));
//		fmap.insert(std::pair<std::string, std::string>("key4", "val4"));
//		smap.insert(std::pair<std::string, std::string>("key5", "val5"));
//		fmap.insert(std::pair<std::string, std::string>("key5", "val5"));
//		smap.insert(std::pair<std::string, std::string>("key6", "val6"));
//		fmap.insert(std::pair<std::string, std::string>("key6", "val6"));
//		smap.insert(std::pair<std::string, std::string>("key8", "val8"));
//		fmap.insert(std::pair<std::string, std::string>("key8", "val8"));
//		smap.insert(std::pair<std::string, std::string>("key9", "val9"));
//		fmap.insert(std::pair<std::string, std::string>("key9", "val9"));
//		are_equal_print(smap, fmap);
//
//		smap["allo"] = "da";
//		fmap["allo"] = "da";
//		are_equal_print(smap, fmap);
//
//		smap["allo"] = "mda";
//		fmap["allo"] = "mda";
//
//		for (std::map<std::string, std::string>::iterator it = smap.begin(); it != smap.end(); it++)
//			std::cout << it->second << " ";
//		std::cout << std::endl;
//		for (ft::map<std::string, std::string>::iterator it = fmap.begin(); it != fmap.end(); it++)
//			std::cout << it->second << " ";
//		std::cout << std::endl;
//
//		for (std::map<std::string, std::string>::reverse_iterator it = smap.rbegin(); it != smap.rend(); it++)
//			std::cout << it->second << " ";
//		std::cout << std::endl;
//		for (ft::map<std::string, std::string>::reverse_iterator it = fmap.rbegin(); it != fmap.rend(); it++)
//			std::cout << it->second << " ";
//		std::cout << std::endl;
//		are_equal_print(smap, fmap);
//
//		smap.erase("key4");
//		fmap.erase("key4");
//		smap.erase("key9");
//		fmap.erase("key9");
//		smap.erase("key1");
//		fmap.erase("key1");
//		smap.erase("key6");
//		fmap.erase("key6");
//
//		for (std::map<std::string, std::string>::const_iterator it = smap.begin(); it != smap.end(); it++)
//			std::cout << it->second << " ";
//		std::cout << std::endl;
//		for (ft::map<std::string, std::string>::const_iterator it = fmap.begin(); it != fmap.end(); it++)
//			std::cout << it->second << " ";
//		std::cout << std::endl;
//
//		for (std::map<std::string, std::string>::const_reverse_iterator it = smap.rbegin(); it != smap.rend(); it++)
//			std::cout << it->second << " ";
//		std::cout << std::endl;
//		for (ft::map<std::string, std::string>::const_reverse_iterator it = fmap.rbegin(); it != fmap.rend(); it++)
//			std::cout << it->second << " ";
//		std::cout << std::endl;
//		are_equal_print(smap, fmap);
//
//		std::map<std::string, std::string>	smap2(smap);
//		ft::map<std::string, std::string>	fmap2(fmap);
//		are_equal_print(smap2, fmap2);
//
//		std::map<std::string, std::string>	smap3(++(smap2.begin()), --(smap2.end()));
//		ft::map<std::string, std::string>	fmap3(++(fmap2.begin()), --(fmap2.end()));
//		are_equal_print(smap3, fmap3);
//
//		smap2 = smap3;	fmap2 = fmap3;
//		are_equal_print(smap2, fmap2);
//
//		smap2 = smap;	fmap2 = fmap;
//		are_equal_print(smap2, fmap2);
//
//		smap.clear();	fmap.clear();
//		are_equal_print(smap, fmap);
//
//		smap2 = smap;	fmap2 = fmap;
//		are_equal_print(smap2, fmap2);
//
//		smap = smap3;	fmap = fmap3;
//		are_equal_print(smap, fmap);
//	}
//
//	{
//		std::cout << "-------------" << std::endl;
//		std::map<char,int>	smap;							ft::map<char,int>	fmap;
//		// first insert function version (single parameter):
//		smap.insert(std::pair<char,int>('a', 100));			fmap.insert(std::pair<char,int>('a', 100));
//		smap.insert(std::pair<char,int>('z', 200));			fmap.insert(std::pair<char,int>('z', 200));
//		smap.insert(std::pair<char,int>('s', 100));			fmap.insert(std::pair<char,int>('s', 100));
//		smap.insert(std::pair<char,int>('e', 200));			fmap.insert(std::pair<char,int>('e', 200));
//		smap.insert(std::pair<char,int>('g', 100));			fmap.insert(std::pair<char,int>('g', 100));
//		smap.insert(std::pair<char,int>('j', 200));			fmap.insert(std::pair<char,int>('j', 200));
//		smap.insert(std::pair<char,int>('w', 100));			fmap.insert(std::pair<char,int>('w', 100));
//		smap.insert(std::pair<char,int>('z', 200));			fmap.insert(std::pair<char,int>('z', 200));
//		are_equal_print(smap, fmap);
//
//		std::pair<std::map<char,int>::iterator, bool> sret;	std::pair<ft::map<char,int>::iterator, bool> fret;
//		sret = smap.insert(std::pair<char,int>('z', 500));	fret = fmap.insert(std::pair<char,int>('z', 500));
//		are_equal_print(smap, fmap);
//
//		if (sret.second == false)
//		{
//			std::cout << "element 'z' already existed";
//			std::cout << " with a value of " << sret.first->second << '\n';
//		}
//		if (fret.second == false)
//		{
//			std::cout << "element 'z' already existed";
//			std::cout << " with a value of " << sret.first->second << '\n';
//		}
//		are_equal_print(smap, fmap);
//
//		// second insert function version (with hint position):
//		std::map<char,int>::iterator sit = smap.begin();	ft::map<char,int>::iterator fit = fmap.begin();
//		smap.insert(sit, std::pair<char,int>('b',300));
//		fmap.insert(fit, std::pair<char,int>('b',300));
//		smap.insert(sit, std::pair<char,int>('b',300));
//		fmap.insert(fit, std::pair<char,int>('b',300));
//		sit = smap.insert(smap.find('w'), std::pair<char,int>('y',300));
//		fit = fmap.insert(fmap.find('w'), std::pair<char,int>('y',300));
//		if (*sit != *fit)
//			error_exception();
//		sit = smap.insert(smap.find('s'), std::pair<char,int>('t',300));
//		fit = fmap.insert(fmap.find('s'), std::pair<char,int>('t',300));
//		if (*sit != *fit)
//			error_exception();
//		sit = smap.insert(smap.find('z'), std::pair<char,int>('}',300));
//		fit = fmap.insert(fmap.find('z'), std::pair<char,int>('}',300));
//		if (*sit != *fit)
//			error_exception();
//		sit = smap.insert(smap.find('g'), std::pair<char,int>('i',300));
//		fit = fmap.insert(fmap.find('g'), std::pair<char,int>('i',300));
//		if (*sit != *fit)
//			error_exception();
//		sit = smap.insert(smap.find('t'), std::pair<char,int>('u',300));
//		fit = fmap.insert(fmap.find('t'), std::pair<char,int>('u',300));
//		if (*sit != *fit)
//			error_exception();
//		sit = smap.insert(smap.end(), std::pair<char,int>('~',300));
//		fit = fmap.insert(fmap.end(), std::pair<char,int>('~',300));
//		if (*sit != *fit)
//			error_exception();
//		are_equal_print(smap, fmap);
//		smap.insert(sit, std::pair<char,int>('c',400));
//		fmap.insert(fit, std::pair<char,int>('c',400));
//		smap.insert(sit, std::pair<char,int>('c',400));
//		fmap.insert(fit, std::pair<char,int>('c',400));
//		are_equal_print(smap, fmap);
//
//		// third insert function version (range insertion):
//		std::map<char, int> anothersmap;					ft::map<char,int> anotherfmap;
//		anothersmap.insert(smap.begin(), smap.find('c'));	anotherfmap.insert(fmap.begin(), fmap.find('c'));
//
//		// showing contents:
//		printmap("smap", smap);
//		printmap("fmap", fmap);
//		printmap("anothersmap", anothersmap);
//		printmap("anotherfmap", anotherfmap);
//		are_equal_print(anothersmap, anotherfmap);
//
//		anothersmap.insert(++smap.begin(), --smap.end());	anotherfmap.insert(++fmap.begin(), --fmap.end());
//		are_equal_print(anothersmap, anotherfmap);
//		smap.erase(++smap.begin(), --smap.end());			fmap.erase(++fmap.begin(), --fmap.end());
//		are_equal_print(smap, fmap);
//
//		std::cout << "------------- MAPS IN MAP" << std::endl;
//		std::map<int, std::map<char, int> >	mapsmap;
//		ft::map<int, ft::map<char, int> >	mapfmap;
//		mapsmap.insert(std::make_pair(1, smap));			mapfmap.insert(std::make_pair(1, fmap));
//		mapsmap.insert(std::make_pair(2, anothersmap));		mapfmap.insert(std::make_pair(2, anotherfmap));
//
//		printmap("mapsmap[1]", mapsmap[1]);
//		printmap("mapfmap[1]", mapfmap[1]);
//		printmap("mapsmap[2]", mapsmap[2]);
//		printmap("mapfmap[2]", mapfmap[2]);
//		are_equal_print(mapsmap[1], mapfmap[1]);
//		are_equal_print(mapsmap[2], mapfmap[2]);
//	}
//
//	{
//		std::cout << "-------------" << std::endl;
//		std::map<char,int>				smap;	ft::map<char,int>				fmap;
//		std::map<char,int>::iterator	sit;	ft::map<char,int>::iterator		fit;
//
//		// insert some values:
//		smap['a'] = 10;					fmap['a'] = 10;
//		smap['b'] = 20;					fmap['b'] = 20;
//		smap['c'] = 30;					fmap['c'] = 30;
//		smap['d'] = 40;					fmap['d'] = 40;
//		smap['e'] = 50;					fmap['e'] = 50;
//		smap['f'] = 60;					fmap['f'] = 60;
//
//		sit = smap.find('b');			fit = fmap.find('b');
//		smap.erase(sit);				fmap.erase(fit);				// erasing by iterator
//
//		smap.erase('c');				fmap.erase('c');				// erasing by key
//
//		sit = smap.find('e');			fit = fmap.find('e');
//		smap.erase(sit, smap.end());	fmap.erase(fit, fmap.end());	// erasing by range
//
//		// show content:
//		printmap("smap", smap);			printmap("fmap", fmap);
//		are_equal_print(smap, fmap);
//	}
//
//	{
//		std::cout << "-------------" << std::endl;
//		std::map<char,int>				smap;			ft::map<char,int>				fmap;
//		std::map<char,int>::iterator	sitlow, situp;	ft::map<char,int>::iterator		fitlow, fitup;
//
//		smap['a'] = 20;						fmap['a'] = 20;
//		smap['b'] = 40;						fmap['b'] = 40;
//		smap['c'] = 60;						fmap['c'] = 60;
//		smap['d'] = 80;						fmap['d'] = 80;
//		smap['e'] = 100;					fmap['e'] = 100;
//
//		sitlow = smap.lower_bound('b');		fitlow = fmap.lower_bound('b');		// itlow points to b
//		situp = smap.upper_bound('d');		fitup = fmap.upper_bound('d');		// itup points to e (not d!)
//
//		smap.erase(sitlow, situp);			fmap.erase(fitlow, fitup);			// erases [itlow,itup)
//
//		// show content:
//		printmap("smap", smap);				printmap("fmap", fmap);
//		are_equal_print(smap, fmap);
//	}
//
//	{
//		std::cout << "-------------" << std::endl;
//		std::map<char,int>	smap;	ft::map<char,int>	fmap;
//
//		smap['a'] = 10;				fmap['a'] = 10;
//		smap['b'] = 20;				fmap['b'] = 20;
//		smap['c'] = 30;				fmap['c'] = 30;
//
//		std::pair<std::map<char,int>::iterator, std::map<char,int>::iterator>	sret;
//		std::pair< ft::map<char,int>::iterator,  ft::map<char,int>::iterator>	fret;
//		sret = smap.equal_range('b');	fret = fmap.equal_range('b');
//
//		std::cout << "std lower bound points to: ";
//		std::cout << sret.first->first << " => " << sret.first->second << '\n';
//		std::cout << "ft  lower bound points to: ";
//		std::cout << fret.first->first << " => " << fret.first->second << '\n';
//
//		std::cout << "std upper bound points to: ";
//		std::cout << sret.second->first << " => " << sret.second->second << '\n';
//		std::cout << "ft  upper bound points to: ";
//		std::cout << fret.second->first << " => " << fret.second->second << '\n';
//		are_equal_print(smap, fmap);
//	}
//
//	#if 0	//	does not working with real std::map
//	{
//		std::map<int, std::string>	smap;	ft::map<int, std::string>	fmap;
//
//		for (int i = 1; i <= 7; i++) { smap[i] = ft_tostring(i); fmap[i] = ft_tostring(i);	}
//		{
//
//			std::cout << "-------------" << std::endl;
//			ft::map<int, std::string>::iterator fit = fmap.begin();
//
//			while (fit != fmap.end())
//			{
//				std::ptrdiff_t	fdist = std::distance(fit, fmap.begin());
//				std::cout << fdist << std::endl;
//				++fit;
//			}
//		}
//		{
//			std::cout << "-------------" << std::endl;
//			ft::map<int, std::string>::reverse_iterator fit = fmap.rbegin();
//
//			while (fit != fmap.rend())
//			{
//				std::ptrdiff_t	fdist = std::distance(fit, fmap.rbegin());
//				std::cout << fdist << std::endl;
//				++fit;
//			}
//		}
//	}
//	#endif
//
//	{
//		std::cout << "--------------" << std::endl;
//		std::map<int, std::string>	smap0;	ft::map<int, std::string>	fmap0;
//		std::map<int, std::string>	smap1;	ft::map<int, std::string>	fmap1;
//		printrelationaloperators(smap0, smap1, fmap0, fmap1);
//
//		smap0[6] = "map";	fmap0[6] = "map";
//		printrelationaloperators(smap0, smap1, fmap0, fmap1);
//		are_equal_print(smap0, fmap0);
//
//		smap1[5] = "map";	fmap1[5] = "map";
//		printrelationaloperators(smap0, smap1, fmap0, fmap1);
//		are_equal_print(smap1, fmap1);
//
//		smap1[7] = "map";	fmap1[7] = "map";
//		printrelationaloperators(smap0, smap1, fmap0, fmap1);
//		are_equal_print(smap1, fmap1);
//
//		smap0[5] = "map";	fmap0[5] = "map";
//		printrelationaloperators(smap0, smap1, fmap0, fmap1);
//		are_equal_print(smap0, fmap0);
//
//		std::cout << "member swap:" << std::endl;
//		smap0.swap(smap1);	fmap0.swap(fmap1);
//		printrelationaloperators(smap0, smap1, fmap0, fmap1);
//		are_equal_print(smap0, fmap0);
//		are_equal_print(smap1, fmap1);
//
//		std::cout << "std::swap:" << std::endl;
//		swap(smap0, smap1);	swap(fmap0, fmap1);
//		printrelationaloperators(smap0, smap1, fmap0, fmap1);
//		are_equal_print(smap0, fmap0);
//		are_equal_print(smap1, fmap1);
//		printbothdirsmap(smap0, fmap0);
//		printbothdirsmap(smap1, fmap1);
//	}
//
//	std::cout << CLR_GOOD << "map tests passed" << CLR_RESET << std::endl << std::endl;
//}

//void		ft_stack_tests()
//{
//	std::cout << CLR_WARN << "STACK TESTS <<<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET << std::endl;
//	{
//		std::stack<int>	sstack;		ft::stack<int>	fstack;
//		int				ssum(0);	int				fsum(0);
//
//		for (int i = 1; i <= 10; i++)
//		{	sstack.push(i);			fstack.push(i);	}
//
//		std::cout << "size: " << sstack.size() << " = " << fstack.size() << '\n';
//		while (!sstack.empty())
//		{
//			ssum += sstack.top();	fsum += fstack.top();
//			sstack.pop();			fstack.pop();
//		}
//		std::cout << "total: " << ssum << " = " << fsum << '\n';
//		std::cout << CLR_GOOD << "containers are equal" << CLR_RESET << std::endl;
//	}
//
//	{
//		std::cout << "--------------" << std::endl;
//		std::stack<std::string>	sstack0;	ft::stack<std::string>	fstack0;
//		std::stack<std::string>	sstack1;	ft::stack<std::string>	fstack1;
//		printrelationaloperators(sstack0, sstack1, fstack0, fstack1);
//
//		sstack0.push("stack");	fstack0.push("stack");
//		printrelationaloperators(sstack0, sstack1, fstack0, fstack1);
//
//		sstack1.push("stack");	fstack1.push("stack");
//		printrelationaloperators(sstack0, sstack1, fstack0, fstack1);
//
//		sstack0.push("stack2");	fstack0.push("stack2");
//		printrelationaloperators(sstack0, sstack1, fstack0, fstack1);
//
//		sstack1.push("stack5");	fstack1.push("stack5");
//		printrelationaloperators(sstack0, sstack1, fstack0, fstack1);
//
//		sstack0 = sstack1;		fstack0 = fstack1;
//		printrelationaloperators(sstack0, sstack1, fstack0, fstack1);
//	}
//
//	{
//		std::cout << "--------------" << std::endl;
//		std::list<int>	slist;	ft::list<int>	flist;
//
//		while (slist.size() < 1000)
//		{
//			int		tmp(rand());
//			if (slist.size() % 2)
//			{	slist.push_back(tmp);		flist.push_back(tmp);	}
//			else
//			{	slist.push_front(tmp);		flist.push_front(tmp);	}
//		}
//
//		std::stack< int, std::list<int> >	sstack(slist);
//		ft::stack< int, ft::list<int> >		fstack(flist);
//
//		std::cout << sstack.size() << " = " << fstack.size() << std::endl;
//
//		while (!sstack.empty() && !fstack.empty())
//		{
//			if (sstack.top() != fstack.top())
//				error_exception();
//			sstack.pop();		fstack.pop();
//		}
//		if (!sstack.empty() || !fstack.empty())
//			error_exception();
//		std::cout << CLR_GOOD << "containers are equal" << CLR_RESET << std::endl;
//	}
//
//	std::cout << CLR_GOOD << "stack tests passed" << CLR_RESET << std::endl << std::endl;
//}

//void		ft_queue_tests()
//{
//	std::cout << CLR_WARN << "QUEUE TESTS <<<<<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET << std::endl;
//	{
//		std::queue<int>	squeue;		ft::queue<int>	fqueue;
//		int				ssum(0);	int				fsum(0);
//
//		for (int i = 1; i <= 10; i++)
//		{	squeue.push(i);			fqueue.push(i);	}
//
//		std::cout << "size: " << squeue.size() << " = " << fqueue.size() << '\n';
//		while (!squeue.empty())
//		{
//			ssum += squeue.front();	fsum += fqueue.front();
//			squeue.pop();			fqueue.pop();
//		}
//		std::cout << "total: " << ssum << " = " << fsum << '\n';
//		std::cout << CLR_GOOD << "containers are equal" << CLR_RESET << std::endl;
//	}
//
//	{
//		std::cout << "--------------" << std::endl;
//		std::queue<std::string>	squeue0;	ft::queue<std::string>	fqueue0;
//		std::queue<std::string>	squeue1;	ft::queue<std::string>	fqueue1;
//		printrelationaloperators(squeue0, squeue1, fqueue0, fqueue1);
//
//		squeue0.push("queue");	fqueue0.push("queue");
//		printrelationaloperators(squeue0, squeue1, fqueue0, fqueue1);
//
//		squeue1.push("queue");	fqueue1.push("queue");
//		printrelationaloperators(squeue0, squeue1, fqueue0, fqueue1);
//
//		squeue0.push("queue2");	fqueue0.push("queue2");
//		printrelationaloperators(squeue0, squeue1, fqueue0, fqueue1);
//
//		squeue1.push("queue5");	fqueue1.push("queue5");
//		printrelationaloperators(squeue0, squeue1, fqueue0, fqueue1);
//
//		squeue0 = squeue1;		fqueue0 = fqueue1;
//		printrelationaloperators(squeue0, squeue1, fqueue0, fqueue1);
//	}
//
//	{
//		std::cout << "--------------" << std::endl;
//		std::list<int>	slist;				ft::list<int>	flist;
//
//		while (slist.size() < 1000)
//		{
//			int		tmp(rand());
//			if (slist.size() % 2)
//			{	slist.push_back(tmp);		flist.push_back(tmp);	}
//			else
//			{	slist.push_front(tmp);		flist.push_front(tmp);	}
//		}
//
//		std::queue< int, std::list<int> >	squeue(slist);
//		ft::queue< int, ft::list<int> >		fqueue(flist);
//
//		std::cout << squeue.size() << " = " << fqueue.size() << std::endl;
//
//		squeue.front() -= squeue.back();		fqueue.front() -= fqueue.back();
//		std::cout << squeue.front() << " = " << fqueue.front() << std::endl;
//
//		squeue.back() -= squeue.front();		fqueue.back() -= fqueue.front();
//		std::cout << squeue.back() << " = " << fqueue.back() << std::endl;
//
//		while (!squeue.empty() && !fqueue.empty())
//		{
//			if (squeue.front() != fqueue.front() || squeue.back() != fqueue.back())
//				error_exception();
//			squeue.pop();		fqueue.pop();
//		}
//		if (!squeue.empty() || !fqueue.empty())
//			error_exception();
//		std::cout << CLR_GOOD << "containers are equal" << CLR_RESET << std::endl;
//	}
//
//	std::cout << CLR_GOOD << "queue tests passed" << CLR_RESET << std::endl << std::endl;
//}

//void		ft_priority_queue_tests()
//{
//	std::cout << CLR_WARN << "PRIORITY QUEUE TESTS <<<<<<<<<<<<<<<<<<<<<<<<<<<<                     " << CLR_RESET << std::endl;
//	{
//		std::priority_queue<int>	squeue;		ft::priority_queue<int>	fqueue;
//		int				ssum(0);				int				fsum(0);
//
//		for (int i = 1; i <= 10; i++)
//		{	squeue.push(i);			fqueue.push(i);	}
//
//		std::cout << "size: " << squeue.size() << " = " << fqueue.size() << '\n';
//		while (!squeue.empty())
//		{
//			ssum += squeue.top();	fsum += fqueue.top();
//			std::cout << squeue.top() << " = " << fqueue.top() << std::endl;
//			squeue.pop();			fqueue.pop();
//		}
//		std::cout << "total: " << ssum << " = " << fsum << '\n';
//		std::cout << CLR_GOOD << "containers are equal" << CLR_RESET << std::endl;
//	}
//
//	{
//		std::cout << "--------------" << std::endl;
//		std::priority_queue<int>	squeue;		ft::priority_queue<int>	fqueue;
//		int				ssum(0);				int				fsum(0);
//
//		while (squeue.size() < 10) {
//			int		i(rand() % 100);
//			squeue.push(i);			fqueue.push(i);
//		}
//
//		std::cout << "size: " << squeue.size() << " = " << fqueue.size() << '\n';
//		while (!squeue.empty())
//		{
//			ssum += squeue.top();	fsum += fqueue.top();
//			std::cout << squeue.top() << " = " << fqueue.top() << std::endl;
//			if (squeue.top() != fqueue.top())
//				error_exception();
//			squeue.pop();			fqueue.pop();
//		}
//		if (!squeue.empty() || !fqueue.empty())
//			error_exception();
//		std::cout << "total: " << ssum << " = " << fsum << '\n';
//		std::cout << CLR_GOOD << "containers are equal" << CLR_RESET << std::endl;
//	}
//
//	{
//		std::cout << "--------------" << std::endl;
//		std::list<int>	slist;				ft::list<int>	flist;
//
//		while (slist.size() < 1000)
//		{
//			int		tmp(rand());
//			slist.push_back(tmp);	flist.push_back(tmp);
//		}
//
//		std::priority_queue<int>	squeue(slist.begin(), slist.end());
//		ft::priority_queue<int>		fqueue(flist.begin(), flist.end());
//
//		std::cout << squeue.size() << " = " << fqueue.size() << std::endl;
//
//		while (!squeue.empty() && !fqueue.empty())
//		{
//			if (squeue.top() != fqueue.top())
//				error_exception();
//			squeue.pop();		fqueue.pop();
//		}
//		if (!squeue.empty() || !fqueue.empty())
//			error_exception();
//		std::cout << CLR_GOOD << "containers are equal" << CLR_RESET << std::endl;
//	}
//
//	{
//		std::cout << "--------------" << std::endl;
//		std::list<int>	slist;				ft::list<int>	flist;
//
//		while (slist.size() < 1000)
//		{
//			int		tmp(rand());
//			slist.push_back(tmp);	flist.push_back(tmp);
//		}
//
//		std::priority_queue< int, std::vector<int>, std::greater<int> >	squeue(slist.begin(), slist.end());
//		ft::priority_queue< int, ft::vector<int>, ft::greater<int> >	fqueue(flist.begin(), flist.end());
//
//		std::cout << squeue.size() << " = " << fqueue.size() << std::endl;
//
//		while (!squeue.empty() && !fqueue.empty())
//		{
//			if (squeue.top() != fqueue.top())
//				error_exception();
//			squeue.pop();		fqueue.pop();
//		}
//		if (!squeue.empty() || !fqueue.empty())
//			error_exception();
//		std::cout << CLR_GOOD << "containers are equal" << CLR_RESET << std::endl;
//	}
//
//	std::cout << CLR_GOOD << "priority_queue tests passed" << CLR_RESET << std::endl << std::endl;
//}

struct mapdata {
    bool               _b;
    char               _c;
    signed char        _sc;
    unsigned char      _uc;
    wchar_t            _wc;
    short              _s;
    unsigned short     _us;
    int                _i;
    unsigned int       _ui;
    long               _l;
    unsigned long      _ul;
    long long          _ll;
    unsigned long long _ull;
    std::string        _str;
    std::wstring       _wstr;
    std::string genstr() {
        std::string res = "";
        while (res.length() < 20)
            res += char(97 + (std::rand() % 26));
        return (res);
    }
    std::wstring genwstr() {
        std::wstring res;
        while (res.length() < 20)
            res += wchar_t(97 + (std::rand() % 26));
        return (res);
    }
    mapdata() : _b(rand()), _c(rand()), _sc(rand()), _uc(rand()), _wc(rand()), _s(rand()),
                _us(rand()), _i(rand()), _ui(rand()), _l(rand()), _ul(rand()), _ll(rand()), _ull(rand()),
                _str(genstr()), _wstr(genwstr()) {}
    friend
    bool operator==(const mapdata &x, const mapdata &y) {
        return (x._b == y._b && x._c == y._c && x._sc == y._sc &&
            x._uc == y._uc && x._wc == y._wc && x._s == y._s &&
            x._us == y._us && x._i == y._i && x._ui == y._ui &&
            x._l == y._l && x._ul == y._ul && x._ll == y._ll &&
            x._ull == y._ull && x._str == y._str && x._wstr == y._wstr);
    }
    friend
    bool operator!=(const mapdata &x, const mapdata &y) { return (!(x == y)); }
};

double gets(const timespec &start) {
    timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    double nsec = double((now.tv_nsec - start.tv_nsec) / 1000000) / 1000.0;
    return (double(now.tv_sec - start.tv_sec) + nsec);
}

/*	100 thousand uses about 80 Mb of RAM. 320+ Mb with valgrind and 640+ Mb with asan.	**
**	don't set this value higher than 1 million (1+ Gb ram usage)						**
**	with valgrind don't set this higher than 200 thousand (x4 ram usage and x30 time)	**
**	same recommendation for asan (x8 ram usage but much less impact on time) 			*/

#define INSANITYSIZE    100000

//void		checkconstmapmeths(const std::map<size_t, mapdata>& smap,
//							const ft::map<size_t, mapdata>& fmap)
//{
//	timespec	start;	size_t	count = INSANITYSIZE / 1000 * 2;
//	clock_gettime(CLOCK_REALTIME, &start);
//	for (size_t i = 0; i < count; i++)
//	{
//		size_t		find = size_t(rand()) % INSANITYSIZE;
//		if (*(smap.lower_bound(find)) != *(fmap.lower_bound(find)) ||
//			*(smap.upper_bound(find)) != *(fmap.upper_bound(find)) ||
//			*(smap.equal_range(find).first) != *(fmap.equal_range(find).first) ||
//			*(smap.equal_range(find).second) != *(fmap.equal_range(find).second))
//			error_exception();
//		if (smap.count(find) != fmap.count(find) ||
//			(smap.find(find) == smap.end() && fmap.find(find) != fmap.end()) ||
//			(smap.find(find) != smap.end() && *(smap.find(find)) != *(fmap.find(find))))
//			error_exception();
//	}
//	std::cout << "checked " << count << " elements in " << gets(start) << "s" << std::endl;
//	are_equal_print(smap, fmap);
//}

//void		ft_iwanttotorturemyram()
//{
//	std::cout << CLR_WARN << "INSANITY TESTS <<<<<<<<<<<<<<<<<<<<<<<<<                              " << CLR_RESET << std::endl;
//	std::cout << std::fixed << std::setprecision(3);
//	timespec	start;
//	typedef std::map<size_t, mapdata>::iterator	smapit;	typedef std::pair<smapit, bool>	sres_t;
//	typedef ft::map<size_t, mapdata>::iterator	fmapit;	typedef std::pair<fmapit, bool>	fres_t;
//	typedef std::list<size_t>::iterator		slistit;	typedef std::vector<size_t>::iterator	svectit;
//	typedef ft::list<size_t>::iterator		flistit;	typedef ft::vector<size_t>::iterator	fvectit;
//	std::map<size_t, mapdata>	smap;	ft::map<size_t, mapdata>	fmap;
//	std::list<size_t>			slist;	ft::list<size_t>			flist;
//	std::vector<size_t>			svect;	ft::vector<size_t>			fvect;
//	std::stack<size_t>			sstack;	ft::stack<size_t>			fstack;
//	std::queue<size_t>			squeue;	ft::queue<size_t>			fqueue;
//
//	clock_gettime(CLOCK_REALTIME, &start);
//	while ((smap.size() < INSANITYSIZE || fmap.size() < INSANITYSIZE) &&
//		slist.size() < INSANITYSIZE * 2 && flist.size() < INSANITYSIZE * 2)
//	{
//		std::pair<size_t, mapdata>	tmp(size_t(rand()) % INSANITYSIZE, mapdata());
//		if (slist.size() % 2)
//		{
//			sres_t	sres = smap.insert(tmp);
//			fres_t	fres = fmap.insert(tmp);
//			if (*(sres.first) != *(fres.first) || sres.second != fres.second)
//				error_exception();
//		}
//		else
//		{
//			smap[tmp.first] = tmp.second;
//			fmap[tmp.first] = tmp.second;
//		}
//		slist.push_back(tmp.first);	flist.push_back(tmp.first);
//		svect.push_back(tmp.first);	fvect.push_back(tmp.first);
//		sstack.push(tmp.first);		fstack.push(tmp.first);
//		squeue.push(tmp.first);		fqueue.push(tmp.first);
//	}
//	std::cout << "Added " << svect.size() << " elements (" << smap.size() <<
//		" unique) in " << gets(start) << "s" << std::endl;
//
//	std::cout << "maxsizes:" << std::endl;
//	std::cout << "map:\t" << smap.max_size() << "\t" << fmap.max_size() << std::endl;
//	std::cout << "list:\t" << slist.max_size() << "\t" << flist.max_size() << std::endl;
//	std::cout << "vect:\t" << svect.max_size() << "\t" << fvect.max_size() << std::endl;
//
//	std::cout << "sizes:" << std::endl;
//	std::cout << "map:\t" << smap.size() << "\t" << fmap.size() << std::endl;
//	std::cout << "list:\t" << slist.size() << "\t" << flist.size() << std::endl;
//	std::cout << "vect:\t" << svect.size() << "\t" << fvect.size() <<
//				"\tcapacities:\t" << svect.capacity() << "\t" << fvect.capacity() << std::endl;
//	std::cout << "stack:\t" << sstack.size() << "\t" << fstack.size() << std::endl;
//	std::cout << "queue:\t" << squeue.size() << "\t" << fqueue.size() << std::endl;
//
//	clock_gettime(CLOCK_REALTIME, &start);
//	slist.sort();
//	std::cout << "slist sorted in " << gets(start) << "s\t\t";
//	clock_gettime(CLOCK_REALTIME, &start);
//	flist.sort();
//	std::cout << "flist sorted in " << gets(start) << "s" << std::endl;
//
//	clock_gettime(CLOCK_REALTIME, &start);
//	std::sort(svect.begin(), svect.end());
//	std::cout << "svect sorted in " << gets(start) << "s\t\t";
//	clock_gettime(CLOCK_REALTIME, &start);
//	std::sort(fvect.begin(), fvect.end());
//	std::cout << "fvect sorted in " << gets(start) << "s" << std::endl;
//
//	clock_gettime(CLOCK_REALTIME, &start);
//	slist.unique();
//	std::cout << "slist uniqued in " << gets(start) << "s\t\t";
//	clock_gettime(CLOCK_REALTIME, &start);
//	flist.unique();
//	std::cout << "flist uniqued in " << gets(start) << "s" << std::endl;
//
//	{
//		svectit	sit;	fvectit	fit;
//		clock_gettime(CLOCK_REALTIME, &start);
//		sit = std::unique(svect.begin(), svect.end());
//		svect.resize(std::distance(svect.begin(), sit));
//		std::cout << "svect uniqued in " << gets(start) << "s\t\t";
//
//		clock_gettime(CLOCK_REALTIME, &start);
//		fit = std::unique(fvect.begin(), fvect.end());
//		fvect.resize(std::distance(fvect.begin(), fit));
//		std::cout << "fvect uniqued in " << gets(start) << "s" << std::endl;
//	}
//
//	are_equal_print(smap, fmap);
//	are_equal_print(slist, flist);
//	are_equal_print(svect, fvect);
//
//	{
//		size_t	prevsize = smap.size();
//		size_t	onethird = prevsize / 3;
//
//		smapit	smitb = smap.begin();	smapit	smite = smap.end();
//		fmapit	fmitb = fmap.begin();	fmapit	fmite = fmap.end();
//		slistit	slitb = slist.begin();	slistit	slite = slist.end();
//		flistit	flitb = flist.begin();	flistit	flite = flist.end();
//		svectit	svitb = svect.begin();	svectit	svite = svect.end();
//		fvectit	fvitb = fvect.begin();	fvectit	fvite = fvect.end();
//		svitb += onethird;				svite -= onethird;
//		fvitb += onethird;				fvite -= onethird;
//
//		for (size_t i = 0; i < onethird; i++)
//		{
//			++smitb;	--smite;	++fmitb;	--fmite;
//			++slitb;	--slite;	++flitb;	--flite;
//		}
//
//		clock_gettime(CLOCK_REALTIME, &start);
//		smap.erase(smitb, smite);
//		std::cout << "Erased smap's  " << (prevsize - smap.size()) << " elements in " <<
//			gets(start) << "s" << std::endl;
//
//		clock_gettime(CLOCK_REALTIME, &start);
//		fmap.erase(fmitb, fmite);
//		std::cout << "Erased fmap's  " << (prevsize - fmap.size()) << " elements in " <<
//			gets(start) << "s" << std::endl;
//
//		clock_gettime(CLOCK_REALTIME, &start);
//		slitb = slist.erase(slitb, slite);
//		std::cout << "Erased slist's " << (prevsize - slist.size()) << " elements in " <<
//			gets(start) << "s" << std::endl;
//
//		clock_gettime(CLOCK_REALTIME, &start);
//		flitb = flist.erase(flitb, flite);
//		std::cout << "Erased flist's " << (prevsize - flist.size()) << " elements in " <<
//			gets(start) << "s" << std::endl;
//
//		if ((slitb == slist.end() && flitb != flist.end()) ||
//			((slitb != slist.end() && flitb != flist.end()) && *slitb != *flitb))
//			error_exception();
//
//		clock_gettime(CLOCK_REALTIME, &start);
//		svitb = svect.erase(svitb, svite);
//		std::cout << "Erased svect's " << (prevsize - svect.size()) << " elements in " <<
//			gets(start) << "s" << std::endl;
//
//		clock_gettime(CLOCK_REALTIME, &start);
//		fvitb = fvect.erase(fvitb, fvite);
//		std::cout << "Erased fvect's " << (prevsize - fvect.size()) << " elements in " <<
//			gets(start) << "s" << std::endl;
//
//		if ((svitb == svect.end() && fvitb != fvect.end()) ||
//			((svitb != svect.end() && fvitb != fvect.end()) && *svitb != *fvitb))
//			error_exception();
//	}
//
//	are_equal_print(smap, fmap);
//	are_equal_print(slist, flist);
//	are_equal_print(svect, fvect);
//
//	smapit	smit = smap.begin();	fmapit	fmit = fmap.begin();
//	slistit	slit = slist.begin();	flistit	flit = flist.begin();
//	svectit	svit = svect.begin();	fvectit	fvit = fvect.begin();
//	while (smit != smap.end() && fmit != fmap.end() && slit != slist.end() &&
//		flit != flist.end() && svit != svect.end() && fvit != fvect.end())
//	{
//		if (smit->first != fmit->first || smit->first != *slit || smit->first != *flit ||
//			smit->first != *svit || smit->first != *fvit)
//			error_exception();
//		++smit; ++fmit; ++slit; ++flit; ++svit; ++fvit;
//	}
//	if (smit != smap.end() || fmit != fmap.end() || slit != slist.end() ||
//		flit != flist.end() || svit != svect.end() || fvit != fvect.end())
//		error_exception();
//
//	{
//		std::stack<size_t, std::list<size_t> >	tmpsstack;
//		ft::stack<size_t, ft::list<size_t> >	tmpfstack;
//		//	turn stacks over so we could
//		while (sstack.size() != 0)
//		{
//			tmpsstack.push(sstack.top());	tmpfstack.push(fstack.top());
//			sstack.pop();					fstack.pop();
//		}
//		//	now top and front of stack and queue are same
//		while (squeue.size() != 0)
//		{
//			if (tmpsstack.top() != tmpfstack.top() || tmpsstack.top() != squeue.front() ||
//				tmpfstack.top() != fqueue.front() || tmpsstack.top() != fqueue.front())
//				error_exception();
//			tmpsstack.pop();				tmpfstack.pop();
//			squeue.pop();					fqueue.pop();
//		}
//		if (squeue.size() != fqueue.size() || tmpsstack.size() != tmpfstack.size() ||
//			sstack.size() != fstack.size())
//			error_exception();
//	}
//
//	{
//		std::cout << "insanity reversers" << std::endl;
//		std::map<size_t, mapdata, std::greater<size_t> >	smapr(smap.rbegin(), smap.rend());
//		ft::map<size_t, mapdata, std::greater<size_t> >		fmapr(fmap.rbegin(), fmap.rend());
//								slist.reverse();						flist.reverse();
//		std::list<size_t>		slistr(slist);		ft::list<size_t>	flistr(flist);
//								slist.reverse();						flist.reverse();
//		std::vector<size_t>		svectr(svect.rbegin(), svect.rend());
//		ft::vector<size_t>		fvectr(svect.rbegin(), svect.rend());
//
//		while (smit != smap.end() && fmit != fmap.end() && slit != slist.end() &&
//			flit != flist.end() && svit != svect.end() && fvit != fvect.end())
//		{
//			if (smit->first != fmit->first || smit->first != *slit || smit->first != *flit ||
//				smit->first != *svit || smit->first != *fvit)
//				error_exception();
//			++smit; ++fmit; ++slit; ++flit; ++svit; ++fvit;
//		}
//
//		are_equal_print(smapr, fmapr);
//		are_equal_print(slistr, flistr);
//		are_equal_print(slistr, fvectr);
//		are_equal_print(svectr, flistr);
//	}
//
//	{
//		size_t	prevsize = smap.size();
//		clock_gettime(CLOCK_REALTIME, &start);
//		while (smap.size() < INSANITYSIZE)
//		{
//			std::pair<size_t, mapdata>	tmp(size_t(rand()) % (INSANITYSIZE * 10), mapdata());
//			smap[tmp.first] = tmp.second;
//			fmap[tmp.first] = tmp.second;
//		}
//		std::cout << "generated " << (smap.size() - prevsize) << " elements in " <<
//			gets(start) << "s" << std::endl;
//		are_equal_print(smap, fmap);
//	}
//
//	checkconstmapmeths(smap, fmap);
//
//	{
//		size_t	prevsize = svect.size();
//		clock_gettime(CLOCK_REALTIME, &start);
//		for (size_t i = 0; i < 100; i++)
//		{
//			size_t		tmp(size_t(rand()) % INSANITYSIZE);
//			slist.remove(tmp);				flist.remove(tmp);
//			svect.erase(std::remove(svect.begin(), svect.end(), tmp), svect.end());
//			fvect.erase(std::remove(fvect.begin(), fvect.end(), tmp), fvect.end());
//		}
//		std::cout << "removed random " << (prevsize - svect.size()) <<
//			" elements from list and vector " << gets(start) << "s" << std::endl;
//		are_equal_print(slist, flist);
//		are_equal_print(svect, fvect);
//		are_equal_print(slist, svect);
//		are_equal_print(flist, fvect);
//	}
//
//	{
//		size_t	prevsize = svect.size();
//		clock_gettime(CLOCK_REALTIME, &start);
//		for (size_t i = 0; i < 100; i++)
//		{
//			slist.remove_if(sizetpredicate);	flist.remove_if(sizetpredicate);
//			svect.erase(std::remove_if(svect.begin(), svect.end(), sizetpredicate), svect.end());
//			fvect.erase(std::remove_if(fvect.begin(), fvect.end(), sizetpredicate), fvect.end());
//		}
//		std::cout << "removed " << (prevsize - svect.size()) <<
//			" elements using predicate from list and vector " << gets(start) << "s" << std::endl;
//		are_equal_print(slist, flist);
//		are_equal_print(svect, fvect);
//		are_equal_print(slist, svect);
//		are_equal_print(flist, fvect);
//	}
//
//	{
//		size_t	prevsize = svect.size();
//		size_t	tmp(size_t(rand()) % INSANITYSIZE);
//		clock_gettime(CLOCK_REALTIME, &start);
//		slist.resize(66666, tmp);		flist.resize(66666, tmp);
//		svect.resize(66666, tmp);		fvect.resize(66666, tmp);
//		std::cout << "resized list and vector from " << (svect.size() - prevsize) <<
//			" to " << svect.size() << " elements in " << gets(start) << "s" << std::endl;
//		are_equal_print(slist, flist);
//		are_equal_print(svect, fvect);
//		are_equal_print(slist, svect);
//		are_equal_print(flist, fvect);
//
//		{
//			tmp = size_t(rand());
//			slist.front() = tmp;	flist.front() = tmp;
//			svect.front() = tmp;	fvect.front() = tmp;
//			tmp = size_t(rand());
//			slist.back() = tmp;		flist.back() = tmp;
//			svect.back() = tmp;		fvect.back() = tmp;
//			tmp = size_t(rand());
//
//			*(++(++(slist.begin()))) = tmp;			*(++(++(flist.begin()))) = tmp;
//			*((svect.begin() + 2)) = tmp;			*((fvect.begin() + 2)) = tmp;
//			tmp = size_t(rand());
//			*(--(--(slist.end()))) = tmp;			*(--(--(flist.end()))) = tmp;
//			*((svect.end() - 2)) = tmp;				*((fvect.end() - 2)) = tmp;
//
//			*(++(++(++(slist.rbegin())))) = tmp;	*(++(++(++(flist.rbegin())))) = tmp;
//			*((svect.rbegin() + 3)) = tmp;			*((fvect.rbegin() + 3)) = tmp;
//			tmp = size_t(rand());
//			*(--(--(--(--(slist.rend()))))) = tmp;	*(--(--(--(--(flist.rend()))))) = tmp;
//			*((svect.rend() - 4)) = tmp;			*((fvect.rend() - 4)) = tmp;
//			std::cout << "some changes by front/back and iterators" << std::endl;
//			are_equal_print(slist, flist);
//			are_equal_print(svect, fvect);
//			are_equal_print(slist, svect);
//			are_equal_print(flist, fvect);
//		}
//
//		prevsize = svect.size();
//		clock_gettime(CLOCK_REALTIME, &start);
//		slist.resize(666, tmp);			flist.resize(666, tmp);
//		svect.resize(666, tmp);			fvect.resize(666, tmp);
//		std::cout << "resized list and vector from " << prevsize <<
//			" to " << svect.size() << " elements in " << gets(start) << "s" << std::endl;
//		are_equal_print(slist, flist);
//		are_equal_print(svect, fvect);
//		are_equal_print(slist, svect);
//		are_equal_print(flist, fvect);
//	}
//
//	{
//		svect.resize(4242, 2121);	fvect.resize(4242, 2121);
//		size_t	prevsize = svect.size();
//		clock_gettime(CLOCK_REALTIME, &start);
//		for (size_t i = 0; i < svect.size(); i++)
//		{
//			size_t	tmp(size_t(rand()) % (svect.size() / 2));
//			if (svect.erase(svect.begin() + tmp) - svect.begin() !=
//				fvect.erase(fvect.begin() + tmp) - fvect.begin())
//				error_exception();
//		}
//		std::cout << "erased random " << (prevsize - svect.size()) <<
//			" vector elements by iterator in " << gets(start) << "s" << std::endl;
//		are_equal_print(svect, fvect);
//	}
//
//	{
//		size_t	prevsize = smap.size();
//		clock_gettime(CLOCK_REALTIME, &start);
//		for (size_t i = 0; i < INSANITYSIZE; i++)
//		{
//			size_t	tmp(size_t(rand()) % INSANITYSIZE);
//			if (smap.erase(tmp) != fmap.erase(tmp))
//				error_exception();
//		}
//		std::cout << "erased random " << (prevsize - smap.size()) <<
//			" map elements by key in " << gets(start) << "s" << std::endl;
//		are_equal_print(smap, fmap);
//	}
//
//	std::cout << CLR_GOOD << "insanity tests passed" << CLR_RESET << std::endl;
//}

//void		ft_reviter_tests()
//{
//	std::cout << CLR_WARN << "REVERSE ITERATOR TESTS <<<<<<<<<<<<<<<<<                              " << CLR_RESET << std::endl;
//	std::cout << "std::rit - std::crit - ft::rit - ft::crit" << std::endl;
//
//	std::list<size_t>			sl;				ft::list<size_t>		fl;
//	std::vector<size_t>			sv;				ft::vector<size_t>		fv;
//	std::map<size_t, size_t>	sm;				ft::map<size_t, size_t>	fm;
//
//	while (sl.size() < 10)
//	{	size_t	tmp(sl.size());
//		sl.push_back(tmp);						fl.push_back(tmp);
//		sv.push_back(tmp);						fv.push_back(tmp);
//		sm.insert(std::make_pair(tmp, tmp));	fm.insert(std::make_pair(tmp, tmp));
//	}
//
//	std::list<size_t>::reverse_iterator					slrit;
//	ft::list<size_t>::reverse_iterator					flrit;
//	std::vector<size_t>::reverse_iterator				svrit;
//	ft::vector<size_t>::reverse_iterator				fvrit;
//	std::map<size_t, size_t>::reverse_iterator			smrit;
//	ft::map<size_t, size_t>::reverse_iterator			fmrit;
//	std::list<size_t>::const_reverse_iterator			slcrit = sl.rbegin();
//	ft::list<size_t>::const_reverse_iterator			flcrit = fl.rbegin();
//	std::vector<size_t>::const_reverse_iterator			svcrit = sv.rbegin();
//	ft::vector<size_t>::const_reverse_iterator			fvcrit = fv.rbegin();
//	std::map<size_t, size_t>::const_reverse_iterator	smcrit = sm.rbegin();
//	ft::map<size_t, size_t>::const_reverse_iterator		fmcrit = fm.rbegin();
//
//	slrit = sl.rbegin();		flrit = fl.rbegin();
//	svrit = sv.rbegin();		fvrit = fv.rbegin();
//	smrit = sm.rbegin();		fmrit = fm.rbegin();
//
//	std::cout << "*l*rits: " << *slrit << " " << *slcrit << " " << *flrit << " " << *flcrit << std::endl;
//	std::cout << "*v*rits: " << *svrit << " " << *svcrit << " " << *fvrit << " " << *fvcrit << std::endl;
//	std::cout << "*m*rits: " << (*smrit).first << " " << (*smcrit).first << " " <<
//								(*fmrit).first << " " << (*fmcrit).first << std::endl;
//
//	++(++slrit);	++(++slcrit);	++(++flrit);	++(++flcrit);
//	++(++svrit);	++(++svcrit);	++(++fvrit);	++(++fvcrit);
//	++(++smrit);	++(++smcrit);	++(++fmrit);	++(++fmcrit);
//	std::cout << "*l*rits: " << *slrit << " " << *slcrit << " " << *flrit << " " << *flcrit << std::endl;
//	std::cout << "*v*rits: " << svrit[0] << " " << svcrit[0] << " " << fvrit[0] << " " << fvcrit[0] << std::endl;
//	std::cout << "*m*rits: " << smrit->first << " " << smcrit->first << " " <<
//								fmrit->first << " " << fmcrit->first << std::endl;
//
//	std::cout << "*l*rits: " << *(--slrit) << " " << *(--slcrit) << " " << *(--flrit) << " " << *(--flcrit) << std::endl;
//	std::cout << "*v*rits: " << svrit[-1] << " " << svcrit[-1] << " " << fvrit[-1] << " " << fvcrit[-1] << std::endl;
//	std::cout << "*m*rits: " << (--smrit)->first << " " << (--smcrit)->first << " " <<
//								(--fmrit)->first << " " << (--fmcrit)->first << std::endl;
//
//	std::cout << "--------------------" << std::endl;
//	std::cout << "rit - 2" << std::endl;
//	svrit = svrit - 2;	svcrit = svcrit - 2;	fvrit = fvrit - 2;	fvcrit = fvcrit - 2;
//	std::cout << "*v*rits: " << *svrit << " " << *svcrit << " " << *fvrit << " " << *fvcrit << std::endl;
//	std::cout << "rit + 1" << std::endl;
//	svrit = svrit + 1;	svcrit = svcrit + 1;	fvrit = fvrit + 1;	fvcrit = fvcrit + 1;
//	std::cout << "*v*rits: " << *svrit << " " << *svcrit << " " << *fvrit << " " << *fvcrit << std::endl;
//	std::cout << "6 + rit" << std::endl;
//	std::cout << "*v*rits: " << *(6 + svrit) << " " << *(6 + svcrit) << " " << *(6 + fvrit) << " " << *(6 + fvcrit) << std::endl;
//
//	std::cout << "rit += 7" << std::endl;
//	svrit += 7;		svcrit += 7;	fvrit += 7;		fvcrit += 7;
//	std::cout << "*v*rits: " << *svrit << " " << *svcrit << " " << *fvrit << " " << *fvcrit << std::endl;
//	std::cout << "rit -= 4" << std::endl;
//	svrit -= 4;		svcrit -= 4;	fvrit -= 4;		fvcrit -= 4;
//	std::cout << "*v*rits: " << *svrit << " " << *svcrit << " " << *fvrit << " " << *fvcrit << std::endl;
//
//	std::cout << "--------------------" << std::endl;
//	std::cout << "*v*rits cmp<: " << (svrit < sv.rbegin()) << " " << (svcrit < sv.rbegin()) << " " <<
//									 (fvrit < fv.rbegin()) << " " << (fvcrit < fv.rbegin()) << std::endl;
//	std::cout << "*v*rits cmp<: " << (svrit < sv.rend()) << " " << (svcrit < sv.rend()) << " " <<
//									 (fvrit < fv.rend()) << " " << (fvcrit < fv.rend()) << std::endl;
//	std::cout << "*v*rits cmp>: " << (svrit > sv.rbegin()) << " " << (svcrit > sv.rbegin()) << " " <<
//									 (fvrit > fv.rbegin()) << " " << (fvcrit > fv.rbegin()) << std::endl;
//	std::cout << "*v*rits cmp>: " << (svrit > sv.rend()) << " " << (svcrit > sv.rend()) << " " <<
//									 (fvrit > fv.rend()) << " " << (fvcrit > fv.rend()) << std::endl;
//	std::cout << "*v*rits diff: " << (svrit - sv.rbegin()) << " " << (svcrit - sv.rbegin()) << " " <<
//									 (fvrit - fv.rbegin()) << " " << (fvcrit - fv.rbegin()) << std::endl;
//	std::cout << "*v*rits diff: " << (svrit - sv.rend()) << " " << (svcrit - sv.rend()) << " " <<
//									 (fvrit - fv.rend()) << " " << (fvcrit - fv.rend()) << std::endl;
//
//	std::cout << "--------------------" << std::endl;
//	std::cout << "*l*rit base: " << *slrit.base() << " " << *slcrit.base() << " " << *flrit.base() << " " << *flcrit.base() << std::endl;
//	std::cout << "*v*rit base: " << svrit.base()[0] << " " << svcrit.base()[0] << " " << fvrit.base()[0] << " " << fvcrit.base()[0] << std::endl;
//	std::cout << "*m*rit base: " << smrit.base()->first << " " << smcrit.base()->first << " " <<
//									fmrit.base()->first << " " << fmcrit.base()->first << std::endl;
//	std::cout << std::endl;
//}

//void		ft_sort_heap_test()
//{
//	std::cout << "additional sort_heap tests" << std::endl;
//	std::vector<int>	svect;	ft::vector<int>		fvect;
//	svect.reserve(1000);		fvect.reserve(1000);
//	while (svect.size() < 1000) {
//		int	tmp(rand());
//		svect.push_back(tmp);	fvect.push_back(tmp);
//	}
//	are_equal_print(svect, fvect);
//
//	std::make_heap(svect.begin(), svect.end());
//	ft::make_heap(fvect.begin(), fvect.end());
//	are_equal_print(svect, fvect);
//
//	std::sort_heap(svect.begin(), svect.end());
//	ft::sort_heap(fvect.begin(), fvect.end());
//	are_equal_print(svect, fvect);
//
//	std::make_heap(svect.begin(), svect.end(), std::greater<int>());
//	ft::make_heap(fvect.begin(), fvect.end(), ft::greater<int>());
//	are_equal_print(svect, fvect);
//
//	std::sort_heap(svect.begin(), svect.end(), std::greater<int>());
//	ft::sort_heap(fvect.begin(), fvect.end(), ft::greater<int>());
//	are_equal_print(svect, fvect);
//
//	std::cout << std::endl;
//}

void reserve_test() {
    {
        ft::vector<std::string>  fvect(2, "hi");
        std::vector<std::string> svect(2, "hi");

//        fvect.reserve(100);
//        svect.reserve(100);

        ASSERT_EQUAL(fvect, svect);
        ASSERT_EQUAL(fvect.capacity(), svect.capacity());

//        fvect.reserve(10);
//        svect.reserve(10);

        ASSERT_EQUAL(fvect, svect);
        ASSERT_EQUAL(fvect.capacity(), svect.capacity());
    }

//    {
//        ft::vector<std::string> fvect(10, "HI");
//        std::vector<std::string> svect(10, "HI");
//
//        fvect.reserve(100);
//        svect.reserve(100);
//
//        ASSERT_EQUAL(fvect, svect);
//        ASSERT_EQUAL(fvect.capacity(), svect.capacity());
//
//        fvect.reserve(10);
//        svect.reserve(10);
//
//        ASSERT_EQUAL(fvect, svect);
//        ASSERT_EQUAL(fvect.capacity(), svect.capacity());
//    }
}

void push_back_test() {

    {
        ft::vector<int>  vecy;
        std::vector<int> vecx;

        vecy.push_back(2);
        vecx.push_back(2);
        vecy.push_back(2);
        vecx.push_back(2);

        vecy.push_back(2);
        vecx.push_back(2);
        vecy.push_back(2);
        vecx.push_back(2);

        ft::vector<int>  vecy1 = vecy;
        std::vector<int> vecx1 = vecx;

        ASSERT_EQUAL(vecx, vecy);
        ASSERT_EQUAL(vecx1, vecy1);
    }
    {
        ft::vector<std::string>  vecy;
        std::vector<std::string> vecx;

        vecy.push_back("2");
        vecx.push_back("2");
        vecy.push_back("2");
        vecx.push_back("2");

        vecy.push_back("2");
        vecx.push_back("2");
        vecy.push_back("2");
        vecx.push_back("2");

        ft::vector<std::string>  vecy1 = vecy;
        std::vector<std::string> vecx1 = vecx;

        ASSERT_EQUAL(vecx1, vecy1);
    }

}

void constructor_test() {

    {
        ft::vector<std::string>  vecy;
        std::vector<std::string> vecx;
        ASSERT_EQUAL(vecx, vecy);
    }

    {
        ft::vector<std::string>  vecy(3);
        std::vector<std::string> vecx(3);

        ASSERT_EQUAL(vecx, vecy);
    }

    {
        ft::vector<std::string>  vecy(3, "Hello");
        std::vector<std::string> vecx(3, "Hello");
        ASSERT_EQUAL(vecx, vecy);
    }

    {
        ft::vector<std::string>  vecy(13, "ello");
        std::vector<std::string> vecx(13, "ello");

        ASSERT_EQUAL(vecx, vecy);
    }

    {
        std::vector<std::string> tmp;

        for (int                 i = 0; i < 100; i++)
            tmp.push_back(test::to_string(i));
        ft::vector<std::string>  vecy(tmp.begin(), tmp.end());
        std::vector<std::string> vecx(tmp.begin(), tmp.end());

        ASSERT_EQUAL(vecx, vecy);
    }

    {
        ft::vector<std::string> tmp;

        for (int                 i = 0; i < 100; i++)
            tmp.push_back(test::to_string(i));
        ft::vector<std::string>  vecy(tmp.begin(), tmp.end());
        std::vector<std::string> vecx(tmp.begin(), tmp.end());

        ASSERT_EQUAL(vecx, vecy);
    }

    {
        ft::vector<std::string> tmp;
        std::vector<std::string> stmp;

        for (int i = 0; i < 100; i++) {
            tmp.push_back(test::to_string(i));
            stmp.push_back(test::to_string(i));
        }
        ft::vector<std::string>  vecy(tmp.begin(), tmp.end());
        std::vector<std::string> vecx(tmp.begin(), tmp.end());

        ASSERT_EQUAL(vecx, vecy);
    }

    {
        ft::vector<int> tmp;

        for (int  i = 0; i < 100; i++) {
            tmp.push_back(i);
        }

        ft::vector<int>  vecy(tmp.begin(), tmp.end());
        std::vector<int> vecx(tmp.begin(), tmp.end());

        ASSERT_EQUAL(vecx, vecy);
    }
}

void iterator_test() {
    {
        ft::vector<int>  fvect;
        std::vector<int> svect;

        for (int i = 0; i < 10; i++) {
            fvect.push_back(i);
            svect.push_back(i);
        }

        ft::vector<int>::iterator  fit = fvect.begin();
        std::vector<int>::iterator sit = svect.begin();

        for (int i = 0; i < 10; i++) {
            ASSERT_EQUAL(*fit, *sit);
            fit++;
            sit++;
        }
    }

    {
        ft::vector<int>  fvect;
        std::vector<int> svect;

        for (int i = 0; i < 10; i++) {
            fvect.push_back(i);
            svect.push_back(i);
        }

        ft::vector<int>::iterator  fit = fvect.end();
        std::vector<int>::iterator sit = svect.end();

        for (int i = 0; i < 10; i++) {
            fit--;
            sit--;
            ASSERT_EQUAL(*fit, *sit);
        }
    }

    {
        ft::vector<int>  fvect;
        std::vector<int> svect;

        for (int i = 0; i < 1; i++) {
            fvect.push_back(i);
            svect.push_back(i);
        }

        ft::vector<int>::iterator  fit = fvect.begin();
        std::vector<int>::iterator sit = svect.begin();

        for (; fit != fvect.end(); fit++, sit++) {
            ASSERT_EQUAL(*fit, *sit);
        }
    }

    {
        ft::vector<std::string>  fvect;
        std::vector<std::string> svect;

        for (int i = 0; i < 1; i++) {
            fvect.push_back(test::to_string(i));
            svect.push_back(test::to_string(i));
        }

        ft::vector<std::string>::iterator  fit     = fvect.begin();
        std::vector<std::string>::iterator sit     = svect.begin();

        for (; sit != svect.end(); fit++, sit++) {
            ASSERT_EQUAL(*fit, *sit);
        }
    }
}


void reverse_iterator_test() {
    {
        ft::vector<int>  fvect;
        std::vector<int> svect;

        for (int i = 0; i < 10; i++) {
            fvect.push_back(i);
            svect.push_back(i);
        }

        ft::vector<int>::reverse_iterator fit = fvect.rbegin();
        std::vector<int>::reverse_iterator sit = svect.rbegin();

        for (int i = 0; i < 10; i++) {
            ASSERT_EQUAL(*fit, *sit);
            fit++;
            sit++;
        }
    }

    {
        ft::vector<int>  fvect;
        std::vector<int> svect;

        for (int i = 0; i < 10; i++) {
            fvect.push_back(i);
            svect.push_back(i);
        }

        ft::vector<int>::reverse_iterator  fit = fvect.rend();
        std::vector<int>::reverse_iterator sit = svect.rend();

        for (int i = 0; i < 10; i++) {
            fit--;
            sit--;
            ASSERT_EQUAL(*fit, *sit);
        }
    }

    {
        ft::vector<int>  fvect;
        std::vector<int> svect;

        for (int i = 0; i < 10; i++) {
            fvect.push_back(i);
            svect.push_back(i);
        }

        ft::vector<int>::reverse_iterator  fit = fvect.rbegin();
        std::vector<int>::reverse_iterator sit = svect.rbegin();

        for (; fit != fvect.rend(); fit++, sit++) {
            ASSERT_EQUAL(*fit, *sit);
        }
    }

    {
        ft::vector<std::string>  fvect;
        std::vector<std::string> svect;

        for (int i = 0; i < 10; i++) {
            fvect.push_back(test::to_string(i));
            svect.push_back(test::to_string(i));
        }

        ft::vector<std::string>::reverse_iterator  fit     = fvect.rbegin();
        std::vector<std::string>::reverse_iterator sit     = svect.rbegin();

        for (; sit != svect.rend(); fit++, sit++) {
            ASSERT_EQUAL(*fit, *sit);
        }
    }
}

template<class Container, class Container1>
void n_fill(Container& container1, Container1& container2, int n = 10)
{
	for (int i = 0; i < 10; ++i)
	{
		container1.push_back(i);
		container2.push_bask(i);
	}
}

template<class Container, class Container1>
void s_fill(Container& container1, Container1& container2, int n = 10)
{
	for (int i = 0; i < n; ++i)
	{
		container1.push_back(test::to_string(i));
		container2.push_back(test::to_string(i));
	}
}

void insert_test()
{
	{

		ft::vector<std::string> hi;
		ft::vector<std::string> ki;
		ft::vector<std::string> ti;

		hi.insert(hi.begin(), "begin");
		ki.insert(ki.end(), "begin");
		ti.push_back("begin");
		ASSERT_EQUAL(ki, ti);
		ASSERT_EQUAL(hi, ti);
	}
	{

		ft::vector<std::string> hi(10);
		ft::vector<std::string> ti(10);

		hi.insert(hi.end(), "begin");
		ti.push_back("begin");
		ASSERT_EQUAL(hi, ti);
	}

	{
		ft::vector<std::string> hi;
		std::vector<std::string> ti;
		s_fill(hi, ti);
		hi.insert(hi.begin(), 10, "loh");
		ti.insert(ti.begin(), 10, "loh");
		ASSERT_EQUAL(hi, ti);

		hi.insert(hi.end(), 10, "l9h");
		ti.insert(ti.end(), 10, "l9h");
		ASSERT_EQUAL(hi, ti);

		hi.insert(hi.begin() + 4, 10, "lh");
		ti.insert(ti.begin() + 4, 10, "lh");
		ASSERT_EQUAL(hi, ti);
	}
}

void test_all() {
    TestRunner tr;
    RUN_TEST(tr, iterator_test);
	RUN_TEST(tr, reverse_iterator_test);
	RUN_TEST(tr, reserve_test);
    RUN_TEST(tr, constructor_test);
    RUN_TEST(tr, push_back_test);
	RUN_TEST(tr, insert_test);
	RUN_TEST(tr, ft_vector_tests);
}

int main(int ac, char **av) {
	test_all();
    ft_vector_tests();

	ft::vector<std::string> f;
	std::vector<std::string> s;

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

    return (0);
}
