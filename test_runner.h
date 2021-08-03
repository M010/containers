#pragma once

#include "utils.h"
#include "map.hpp"
#include "ft_vector.h"
#include "utils.h"
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using std::ostream;
using std::string;
using std::endl;
using std::cerr;

class ostringstream;
namespace test
{
	template<class T>
	std::string to_string(const T& val)
	{
		std::ostringstream stream;
		stream << val;
		return stream.str();
	}
}


template<class T>
bool operator==(const std::vector<T> lhs, const ft::vector<T> rhs){
    if(lhs.size() != rhs.size())
        return false;
    return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<class T>
bool operator==(const ft::vector<T> lhs, const std::vector<T> rhs){
    if(lhs.size() != rhs.size())
        return false;
    return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<class K, class V, class Cmp>
bool operator==(const ft::map<K, V, Cmp> lhs, const std::map<K, V, Cmp> rhs){
	if(lhs.size() != rhs.size())
		return false;
	typename std::map<K, V,Cmp>::const_iterator sit= rhs.begin();
	for(typename ft::map<K, V,Cmp>::const_iterator it = lhs.begin(); it!=lhs.end(); sit++, it++) {
		bool first_equal = (!rhs.key_comp()(it->first, sit->first) && !rhs.key_comp()(sit->first, it->first));
		if(!first_equal && !(it->second == sit->second))
			return false;
	}

	typename std::map<K, V,Cmp>::const_reverse_iterator rsit = rhs.rbegin();
	for(typename ft::map<K, V,Cmp>::const_reverse_iterator rit = lhs.rbegin(); rit!=lhs.rend(); rsit++, rit++) {
		bool first_equal = (!rhs.key_comp()(rit->first, rsit->first) && !rhs.key_comp()(rsit->first, rit->first));
		if(!first_equal && !(rit->second == rsit->second))
			return false;
	}
	return true;
}

template<class K, class V, class Cmp>
bool operator==(const std::map<K, V, Cmp> lhs, const ft::map<K, V, Cmp> rhs){
	return rhs == lhs;
}

template<class K, class V>
bool operator==(const ft::map<K, V> lhs, const std::map<K, V> rhs){
	if(lhs.size() != rhs.size())
		return false;
	typename std::map<K, V>::const_iterator sit= rhs.begin();
	for(typename ft::map<K, V>::const_iterator it = lhs.begin(); it!=lhs.end(); sit++, it++) {
		if(!(it->first == sit->first) && !(it->second == sit->second))
			return false;
	}

	typename std::map<K, V>::const_reverse_iterator rsit = rhs.rbegin();
	for(typename ft::map<K, V>::const_reverse_iterator rit = lhs.rbegin(); rit!=lhs.rend(); rsit++, rit++) {
		if(!(rit->first == rsit->first) && !(rit->second == rsit->second))
			return false;
	}

	return true;
}

template<class K, class V>
bool operator==(const std::map<K, V> lhs, const ft::map<K, V> rhs){
	return rhs == lhs;
}


template <class T>
ostream& operator << (ostream& os, const std::vector<T>& s) {
    os << "!size: " << s.size() << " capacity: "<< s.capacity() << "{";
    bool first = true;
    for (typename std::vector<T>::const_iterator x = s.begin(); x != s.end(); x++) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << *x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const ft::vector<T>& s) {
	os << "!size: " << s.size() << " capacity: "<< s.capacity() << "{";
	bool first = true;
	for (typename ft::vector<T>::const_iterator x = s.begin(); x != s.end(); x++) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << *x;
	}
	return os << "}";
}


template <class K, class V>
ostream& operator << (ostream& os, const ft::map<K, V>& m) {
	os << "{" << "size: " << m.size();
	bool first = true;
	for (typename ft::map<K, V>::const_iterator kv = m.begin(); kv != m.end(); kv++) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv->first << ": " << kv->second;
	}
	return os << "}";
}

template <class K, class V, class cmp>
ostream& operator << (ostream& os, const ft::map<K, V, cmp>& m) {
	os << "{" << "size: " << m.size();
	bool first = true;
	for (typename ft::map<K, V, cmp>::const_iterator kv = m.begin(); kv != m.end(); kv++) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv->first << ": " << kv->second;
	}
	return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const std::set<T>& s) {
    os << "{";
    bool first = true;
	for (typename std::set<T>::const_iteratror x = s.begin(); x != s.end(); x++) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << *x;
    }
    return os << "}";
}
template<class F, class S>
bool operator==(std::pair<F, S> lhs , ft::pair<F, S>rhs){
	return lhs == std::pair<F, S>(rhs.first, rhs.second);
}

template<class F, class S>
bool operator==(ft::pair<F, S> lhs , std::pair<F, S>rhs){
	return rhs == lhs;
}

template <class K, class V>
ostream& operator << (ostream& os, const std::map<K, V>& m) {
    os << "{";
    bool first = true;
	for (typename std::map<K, V>::const_iterator kv = m.begin(); kv != m.end(); kv++) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv->first << ": " << kv->second;
    }
    return os << "}";
}


template <class K, class V, class Cmp>
ostream& operator << (ostream& os, const std::map<K, V, Cmp>& m) {
	os << "{";
	bool first = true;
	for (typename std::map<K, V, Cmp>::const_iterator kv = m.begin(); kv != m.end(); kv++) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv->first << ": " << kv->second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = "") {
    if (!(t == u)) {
        std::ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw std::runtime_error(os.str());
    }
}

inline void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    	TestRunner():fail_count(0){};
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name)  {
        try {
            func();
            std::cerr << test_name << " OK" << std::endl;
        } catch (std::exception& e) {
            ++fail_count;
            std::cerr << test_name << " fail: " << e.what() << std::endl;
        } catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count;
};

template <class T>
std::string ft_tostring(T t){
	std::ostringstream ss;
	ss << t;
	return ss.str();
};
#define ASSERT_EQUAL(x, y) {            \
  std::ostringstream os;                \
  os << #x << " != " << #y << ", "      \
    << __FILE__ << ":" << __LINE__;     \
  AssertEqual(x, y, os.str());          \
}

#define ASSERT(x) {                     \
  std::ostringstream os;                     \
  os << #x << " is false, "             \
    << __FILE__ << ":" << __LINE__;     \
  Assert(x, os.str());                  \
}


#define RUN_TEST(tr, func) tr.RunTest(func, #func)