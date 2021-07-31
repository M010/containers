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
	iterator prev(iterator it) {
		return --it;
	}

	template<class iterator>
	iterator next(iterator it) {
		return ++it;
	}

	template<class T>
	struct remove_const{
		typedef T type;
	};

	template<class T>
	struct remove_const<const T>{
		typedef T type;
	};

	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	template<typename Iter>
	struct iterator_traits
	{
		typedef typename Iter::iterator_category iterator_category;
		typedef typename Iter::value_type 		value_type;
		typedef typename Iter::difference_type 	difference_type;
		typedef typename Iter::pointer 			pointer;
		typedef typename Iter::reference 		reference;
	};


}


