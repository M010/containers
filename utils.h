#pragma once

namespace ft {
template<class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
    while (first1 != last1) {
        if (!(*first1 == *first2))   // or: if (!pred(*first1,*first2)), for version 2
            return false;
        ++first1;
        ++first2;
    }
    return true;
}

template<class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                             InputIterator2 first2, InputIterator2 last2) {
    while (first1 != last1) {
        if (first2 == last2 || *first2 < *first1) return false;
        else if (*first1 < *first2) return true;
        ++first1;
        ++first2;
    }
    return (first2 != last2);
}

	template<class iterator>
	iterator ft_prev(iterator it) {
		return --it;
	}

	template<class iterator>
	iterator next(iterator it) {
		return ++it;
	}
}

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

