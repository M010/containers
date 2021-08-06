#pragma once
#include <iterator>

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
struct remove_const {
    typedef T type;
};

template<class T>
struct remove_const<const T> {
    typedef T type;
};

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

template<typename Iter>
struct iterator_traits {
    typedef typename Iter::iterator_category iterator_category;
    typedef typename Iter::value_type        value_type;
    typedef typename Iter::difference_type   difference_type;
    typedef typename Iter::pointer           pointer;
    typedef typename Iter::reference         reference;
};

template<typename T>
struct iterator_traits<T *> {
    typedef ptrdiff_t                       difference_type;
    typedef typename remove_const<T>::type  value_type;
    typedef T                               *pointer;
    typedef T                               &reference;
    typedef std::random_access_iterator_tag iterator_category;
};

template<class T>
struct is_integral_helper {
    const static bool value = false;
};

template<>
struct is_integral_helper<bool> {
    const static bool value = true;
};

template<>
struct is_integral_helper<int> {
    const static bool value = true;
};

template<>
struct is_integral_helper<long> {
    const static bool value = true;
};

template<>
struct is_integral_helper<long long> {
    const static bool value = true;
};

template<>
struct is_integral_helper<char> {
    const static bool value = true;
};

template<>
struct is_integral_helper<short> {
    const static bool value = true;
};

template<>
struct is_integral_helper<unsigned int> {
    const static bool value = true;
};

template<>
struct is_integral_helper<unsigned long> {
    const static bool value = true;
};

template<>
struct is_integral_helper<unsigned long long> {
    const static bool value = true;
};

template<>
struct is_integral_helper<unsigned char> {
    const static bool value = true;
};

template<>
struct is_integral_helper<unsigned short> {
    const static bool value = true;
};

template<class T>
struct is_integral {
    const static bool value = is_integral_helper<typename remove_const<T>::type>::value;
};

template<typename T, typename U>
struct is_same {
    static const bool value = false;
};

template<typename T>
struct is_same<T, T> {
    static const bool value = true;
};

template<typename Iterator>
typename iterator_traits<Iterator>::difference_type
distance_helper(const Iterator &first, const Iterator &last, std::random_access_iterator_tag) {
    return last - first;
}

template<typename Iterator>
typename iterator_traits<Iterator>::difference_type
distance_helper(const Iterator &first, const Iterator &last, std::input_iterator_tag) {
    Iterator                                            it   = first;
    typename iterator_traits<Iterator>::difference_type size = 0;
    while (it++ != last)
        size++;
    return size;
}

template<typename Iterator>
ptrdiff_t distance(const Iterator &first, const Iterator &last) {
    return distance_helper(first, last, typename iterator_traits<Iterator>::iterator_category());
}

template<class T>
struct is_const {
    static const bool value = false;
};

template<class T>
struct is_const<const T> {
    static const bool value = true;
};

}
