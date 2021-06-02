#pragma once

namespace ft {
template
    <class T,
        class Allocator = std::allocator<T> >
class vector {
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


 private:
    allocator_type _allocator;
    pointer vect_;
    size_type size_;
    size_type capacity_;
    std::allocator<int> test;

 public:
    explicit vector(const Allocator &alloc = Allocator())
        : _allocator(alloc), size_(0), capacity_(0) {
        vect_ = NULL;
    };

    explicit vector(size_type n, const value_type &val = value_type(),
                    const allocator_type &alloc = allocator_type())
        : size_(n), capacity_(n), _allocator(alloc), vect_(NULL){
        if(size_ == 0)
            return;
        vect_ = _allocator.allocate(n);
        _construct(vect_, n, val);
    }
//template <class InputIterator>
//vector (InputIterator first, InputIterator last,
//const allocator_type& alloc = allocator_type());
//vector (const vector& x);
//

    ~vector() {
        if(empty())
            return;
        for (size_t arr_shift = 0; arr_shift < size_; arr_shift++)
            _destroy(vect_ + arr_shift);
        _allocator.deallocate(vect_, size_);
    }

/*
 *  Modifiers
 */
    void clear()
    {
        _destroy(vect_, size());
        size_ = 0;
    }

    void swap(vector& other ) {
        std::swap(other.vect_, vect_);
        std::swap(other.size_, size_);
        std::swap(other.capacity_, capacity_);
    }

    void push_back(T value) {
        if (size_ >= capacity_) { // ?
            size_type new_capacity = capacity() == 0 ? 1 : capacity() * 2;
            this->reserve(new_capacity);
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

    reference at(size_type n) {
        if (n >= this->size())
            throw std::out_of_range("vector");
        return this[n];
    }

    const_reference at(size_type n) const {
        if (n >= this->size())
            throw std::out_of_range("vector");
        return this[n];

    }

    reference front() {
       return *begin();
    }

    const_reference front() const {
       return *begin();
    }

    reference back()
    {
        return *prev(end());
    }

    const_reference back() const
    {
        return *prev(end());
    }

/*
 *  Capacity
 */

    size_type size() const {
        return size_;
    }

    size_type max_size() const {
        return test.max_size(); //TODO: maybe we need size_t limit?
    }

    size_type capacity() const {
        return capacity_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void reserve(size_type n) {
        if (n <= this->capacity())
            return;
        pointer old_vector = vect_;
        vect_ = _allocator.allocate(n);
        for (size_type i; i < size(); i++) {
            _construct(&(vect_[i]), old_vector[i]);
            _destroy(&old_vector[i]);
        }
        _allocator.deallocate(old_vector, capacity());
        capacity_ = n;
    }

    void resize(size_type n, value_type val = value_type()) {
        this->reserve(n);
        _construct(&vect_[size_], &vect_[n]);
        _destroy(&vect_[n], &vect_[size_]);
        size_ = n;
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

    reverse_iterator rbegin() {
        return std::reverse_iterator<iterator>(begin());
    }

    reverse_iterator rend() {
        return std::reverse_iterator<iterator>(end());
    }

    const_reverse_iterator rbegin() const {
        return std::reverse_iterator<iterator>(begin());
    }

    const_reverse_iterator rend() const {
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

    vector<T, Allocator> &operator=(const vector &other) {
        if (other.size_ <= capacity_) {
            copy(other.begin(), other.end(), begin()); // TODO: test it !!
            size_ = other.size_;
        } else {
            vector<T, Allocator> tmp(other);
            swap(other);
        }
    }

 private:
    void _construct(pointer elem, value_type val = value_type()) {
        _allocator.construct(elem, val);
    }

    void _construct(pointer p, size_type n, value_type val = value_type()) {
        for (size_type i = 0; i < n; i++)
            _construct(vect_ + i, val);
    }

    void _construct(pointer begin, pointer end, value_type val = value_type()) {
        for (pointer elem = begin; elem < end; elem++)
            _construct(elem, val);
    }

    void _destroy(pointer p) {
        _allocator.destroy(p);
    }

    void _destroy(pointer p, size_type n) {
        pointer end = p + n;
        for (; p < end; p++)
            _destroy(p);
    }

    void _destroy(pointer begin, pointer end) {
        for (pointer elem = begin; elem < end; elem++)
            _destroy(elem);
    }

};
}