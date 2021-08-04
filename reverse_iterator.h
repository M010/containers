#pragma once

namespace ft {
template<typename Iter>
class reverse_iterator {
 protected:
    Iter current;

    typedef iterator_traits<Iter> trait;

 public:
    typedef Iter                              iterator_type;
    typedef typename trait::iterator_category iterator_category;
    typedef typename trait::value_type        value_type;
    typedef typename trait::difference_type   difference_type;
    typedef typename trait::pointer           pointer;
    typedef typename trait::reference         reference;

    reverse_iterator() : current() {}

    explicit
    reverse_iterator(iterator_type other) : current(other) {}

    reverse_iterator(const reverse_iterator &other)
        : current(other.current) {}

    template<typename nIter>
    reverse_iterator(const reverse_iterator<nIter> &other)
        : current(other.base()) {}

    iterator_type base() const { return current; }

    reference
    operator*() const {
        Iter tmp = current;
        return *--tmp;
    }

    pointer
    operator->() const {
        Iter tmp = current;
        --tmp;
        return &(*tmp);
    }

    reverse_iterator &
    operator++() {
        --current;
        return *this;
    }

    reverse_iterator
    operator++(int) {
        reverse_iterator tmp = *this;
        --current;
        return tmp;
    }

    reverse_iterator &
    operator--() {
        ++current;
        return *this;
    }

    reverse_iterator
    operator--(int) {
        reverse_iterator tmp = *this;
        ++current;
        return tmp;
    }

    reverse_iterator
    operator+(difference_type n) const { return reverse_iterator(current - n); }

    reverse_iterator &
    operator+=(difference_type n) {
        current -= n;
        return *this;
    }

    reverse_iterator
    operator-(difference_type n) const { return reverse_iterator(current + n); }

    reverse_iterator &
    operator-=(difference_type n) {
        current += n;
        return *this;
    }

    reference operator[](difference_type n) const { return *(*this + n); }
};

template<typename Iter>
bool
operator==(const reverse_iterator<Iter> &lhs,
           const reverse_iterator<Iter> &rhs) { return lhs.base() == rhs.base(); }

template<typename Iter>
bool
operator<(const reverse_iterator<Iter> &lhs,
          const reverse_iterator<Iter> &rhs) { return rhs.base() < lhs.base(); }

template<typename Iter>
bool
operator!=(const reverse_iterator<Iter> &lhs,
           const reverse_iterator<Iter> &rhs) { return !(lhs == rhs); }

template<typename Iter>
bool
operator>(const reverse_iterator<Iter> &lhs,
          const reverse_iterator<Iter> &rhs) { return rhs < lhs; }

template<typename Iter>
bool
operator<=(const reverse_iterator<Iter> &lhs,
           const reverse_iterator<Iter> &rhs) { return !(rhs < lhs); }

template<typename Iter>
bool
operator>=(const reverse_iterator<Iter> &lhs,
           const reverse_iterator<Iter> &rhs) { return !(lhs < rhs); }

template<typename IterL, typename IterR>
bool operator==(const reverse_iterator<IterL> &lhs,
           const reverse_iterator<IterR> &rhs) { return lhs.base() == rhs.base(); }

template<typename IterL, typename IterR>
inline bool
operator<(const reverse_iterator<IterL> &lhs,
          const reverse_iterator<IterR> &rhs) { return rhs.base() < lhs.base(); }

template<typename IterL, typename IterR>
inline bool
operator!=(const reverse_iterator<IterL> &lhs,
           const reverse_iterator<IterR> &rhs) { return !(lhs == rhs); }

template<typename IterL, typename IterR>
inline bool
operator>(const reverse_iterator<IterL> &lhs,
          const reverse_iterator<IterR> &rhs) { return rhs < lhs; }

template<typename IterL, typename IterR>
inline bool
operator<=(const reverse_iterator<IterL> &lhs,
           const reverse_iterator<IterR> &rhs) { return !(rhs < lhs); }

template<typename IterL, typename IterR>
inline bool
operator>=(const reverse_iterator<IterL> &lhs,
           const reverse_iterator<IterR> &rhs) { return !(lhs < rhs); }

template<typename Iter>
inline typename reverse_iterator<Iter>::difference_type
operator-(const reverse_iterator<Iter> &lhs,
          const reverse_iterator<Iter> &rhs) { return rhs.base() - lhs.base(); }

template<typename IterL, typename IterR>
inline typename reverse_iterator<IterL>::difference_type
operator-(const reverse_iterator<IterL> &lhs,
          const reverse_iterator<IterR> &rhs) { return rhs.base() - lhs.base(); }

template<typename Iter>
inline reverse_iterator<Iter>
operator+(typename reverse_iterator<Iter>::difference_type n,
          const reverse_iterator<Iter> &lhs) { return reverse_iterator<Iter>(lhs.base() - n); }
}