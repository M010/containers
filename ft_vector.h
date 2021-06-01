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
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef typename allocator_type::reference reference;
    typedef typename allocator_type::reference const_reference;
    typedef typename allocator_type::pointer pointer;
    typedef typename allocator_type::const_pointer const_pointer;

    typedef T *iterator;
    typedef const T *const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    typedef size_t size_type;

    explicit vector(const Allocator &alloc = Allocator())
        : _allocator(alloc), size_(0), capacity_(0) {
        vect_ = _allocator.allocate(0);
    };

    explicit vector(size_type n, const value_type &val = value_type(),
                    const allocator_type &alloc = allocator_type())
        : size_(n), capacity_(n), _allocator(alloc), vect_(_allocator.allocate(n)) {
        for (size_type i; i < n; i++)
            _allocator.construct(vect_ + i, val);
    }
//template <class InputIterator>
//vector (InputIterator first, InputIterator last,
//const allocator_type& alloc = allocator_type());
//vector (const vector& x);
//

    ~vector() {
        for (size_t arr_shift = 0; arr_shift < size_; arr_shift++)
            test.destroy(vect_ + arr_shift);
        _allocator.deallocate(vect_, size_);
    }

/*
 *  Constructors
 */

    void push_back(T value) {
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
 * Element access
 */

    reference operator[](size_t index) {
        return vect_[index];
    }

    const_reference operator[](size_t index) const {
        return vect_[index];
    }

    reference at (size_type n){
       if (n >= this->size())
           throw std::out_of_range("vector");
        return this[n];
    }

    const_reference at (size_type n) const {
        if (n >= this->size())
            throw std::out_of_range("vector");
        return this[n];

    }
/*
 *  Capacity
 */

    size_type size() const {
        return size_;
    }

    size_type max_size() const
    {
        return test.max_size(); //TODO: maybe we need size_t limit?
    }

    size_type capacity() const {
        return capacity_;
    }

    bool empty() const
    {
       return size_ == 0;
    }

/*
 * iterator functions section
 */
    iterator begin() {
        return vect_;
    }

    iterator end() {
        return vect_ + size_;
    }

    const_iterator begin() const {
        return vect_;
    }

    const_iterator end() const {
        return vect_ + size_;
    }

    iterator rbegin() {
        return std::reverse_iterator<iterator>(begin());
    }

    iterator rend() {
        return std::reverse_iterator<iterator>(end());
    }

    const_iterator rbegin() const {
        return std::reverse_iterator<iterator>(begin());
    }

    const_iterator rend() const {
        return std::reverse_iterator<iterator>(end());
    }

/*
 * iterator functions section END
 */

//   template<typename T, class Allocator>
//    vector(const vector &other):
//            capacity_(other.size_), vector_size_(other.vector_size_) {
//        vect_ = new T[size_];
//        copy(other.begin(), other.end(), begin());
//    }

    vector<T, Allocator> & operator=(const vector &other) {
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
 private:

};
}