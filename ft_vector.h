#pragma once

namespace ft {
template
    <class T,
    class Allocator = std::allocator<T> >
class vector {
 private:
    Allocator _allocator;
    T *vect_;
    size_t size_;
    size_t capacity_;
    std::allocator<int> test;
 public:
    typedef T         value_type;
    typedef Allocator                                   allocator_type;
    typedef typename allocator_type::reference          reference;
    typedef typename allocator_type::reference          const_reference;
    typedef typename allocator_type::pointer            pointer;
    typedef typename allocator_type::const_pointer      const_pointer;

    typedef T*                                          iterator;
    typedef const T*                                    const_iterator;
    typedef std::reverse_iterator<iterator>             reverse_iterator;
    typedef std::reverse_iterator<const_iterator>       const_reverse_iterator;

    typedef size_t                                      size_type;

    reference operator[](size_t index);
    const_reference operator[](size_t index) const;
    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
    size_t size() const;
    size_t capacity() const;
    void push_back(T value);
    vector &operator=(const vector &other);
    explicit vector(const Allocator &alloc = Allocator())
        : _allocator(alloc), size_(0) {
        vect_ = test.allocate(0);
    };

explicit vector (size_type n, const value_type& val = value_type(),
const allocator_type& alloc = allocator_type())
: size_(n), capacity_(n), _allocator(alloc), vect_(_allocator.allocate(n))
{
    for(size_type i; i < n; i++)
        test.construct(vect_ + i, val);
}
//template <class InputIterator>
//vector (InputIterator first, InputIterator last,
//const allocator_type& alloc = allocator_type());
//vector (const vector& x);
//

    ~vector() {
        for (size_t elem = 0; elem < size_; elem++)
            vect_[elem].~T();
        _allocator.deallocate(size_, vect_);
    }

};

/*
 *  Constructors
 */


template<typename T, class Allocator>
void vector<T, Allocator>::push_back(T value) {
    if (size_ < capacity_) {
        capacity_ = capacity_ == 0 ? 1 : capacity_ * 2;
        T *old_vect = vect_;
        vect_ = _allocator.allocate(capacity_);
        //TODO: может вызываться деструктор от копируемых обьектов утечка?)
        std::copy(old_vect, old_vect + size_, vect_);
        _allocator.deallocate(old_vect, size_);
    }
    vect_[size_] = value;
    size_++;
}

/*
 * Getters
 */

template<typename T, class Allocator>
typename vector<T, Allocator>::reference
vector<T, Allocator>::operator[](size_t index) {
    return vect_[index];
}

template<class T, class Allocator>
typename vector<T, Allocator>::const_reference
vector<T, Allocator>::operator[](size_t index) const {
    return vect_[index];
}

template<typename T, class Allocator>
size_t vector<T, Allocator>::size() const {
    return size_;
}

template<typename T, class Allocator>
size_t vector<T, Allocator>::capacity() const {
    return capacity_;
}

/*
 * iterator functions section
 */

template<typename T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::begin() {
    return vect_;
}

template<typename T, class Allocator>
typename vector<T, Allocator>::iterator vector<T, Allocator>::end() {
    return vect_ + size_;
}

template<typename T, class Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::begin() const {
    return vect_;
}

template<typename T, class Allocator>
typename vector<T, Allocator>::const_iterator vector<T, Allocator>::end() const {
    return vect_ + size_;
}

/*
 * iterator functions section END
 */

//   template<typename T, class Allocator>
//    vector<T, Allocator>::vector(const vector &other):
//            capacity_(other.size_), vector_size_(other.vector_size_) {
//        vect_ = new T[size_];
//        copy(other.begin(), other.end(), begin());
//    }

template<typename T, class Allocator>
vector<T, Allocator> &vector<T, Allocator>::operator=(const vector &other) {
    if (other.size_ <= capacity_) {
        copy(other.begin(), other.end(), begin());
        size_ = other.size_;
    } else {
        vector<T, Allocator> tmp(other);
        std::swap(tmp.vect_, vect_);
        std::swap(tmp.size_, size_);
        std::swap(tmp.capacity_, capacity_);
    }
}
}