#pragma once

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

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

namespace ft {
template
    <class T,
     class Allocator = std::allocator<T> >
class vector {

 public:
    typedef T                                      value_type;
    typedef Allocator                              allocator_type;
    typedef typename allocator_type::reference     reference;
    typedef typename allocator_type::reference     const_reference;
    typedef typename allocator_type::pointer       pointer;
    typedef typename allocator_type::const_pointer const_pointer;


    class iterator {
     public:
        typedef int      difference_type;
        typedef iterator self_type;
        iterator():ptr_(NULL) {}
        iterator(pointer ptr) : ptr_(ptr) {}
        self_type operator++() {
            self_type i = *this;
            ptr_++;
            return i;
        }
        self_type operator++(int junk) {
            ptr_--;
            return *this;
        }
        self_type operator--() {
            self_type i = *this;
            ptr_--;
            return i;
        }
        self_type operator--(int junk) {
            ptr_--;
            return *this;
        }
        const self_type &operator+=(difference_type n) {
            ptr_ += n;
            return *this;
        }
        const self_type &operator-=(difference_type n) {
            ptr_ -= n;
            return *this;
        }
        const self_type &operator+(difference_type n) {
            self_type tmp = *this;
            return tmp += n;
        }

        friend const self_type& operator+(difference_type rhs, const self_type& lhs) {
            self_type tmp = lhs;
            return lhs += rhs;
        }

        const self_type &operator-(difference_type n) {
            self_type tmp = *this;
            return tmp -= n;
        }
        difference_type operator-(self_type rhs) { return this->ptr_ - rhs->ptr_; } // TODO :: test?
        const value_type &operator[](difference_type n) { return *(*this + n); };
        value_type &operator[](difference_type n) const { return *(*this + n); };

        reference operator*() { return *ptr_; }
        pointer operator->() { return ptr_; }

        bool operator==(const self_type &rhs) { return ptr_ == rhs.ptr_; }
        bool operator!=(const self_type &rhs) { return ptr_ != rhs.ptr_; }
        bool operator<(const self_type &rhs) const { return ptr_ < rhs.ptr_; }
        bool operator>(const self_type &rhs) const { return rhs < *this; }
        bool operator<=(const self_type &rhs) const { return !(rhs < *this); }
        bool operator>=(const self_type &rhs) const { return !(*this < rhs); }
     private:
        pointer ptr_;
    };
    class const_iterator {
     public:
        typedef int            difference_type;
        typedef const_iterator self_type;

        const_iterator():ptr_(NULL) {}
        const_iterator(pointer ptr) : ptr_(ptr) {}
        self_type operator++() {
            self_type i = *this;
            ptr_++;
            return i;
        }
        self_type operator++(int junk) {
            ptr_--;
            return *this;
        }
        self_type operator--() {
            self_type i = *this;
            ptr_--;
            return i;
        }
        self_type operator--(int junk) {
            ptr_--;
            return *this;
        }
        const self_type &operator+=(difference_type n) {
            ptr_ += n;
            return *this;
        }
        const self_type &operator-=(difference_type n) {
            ptr_ -= n;
            return *this;
        }
        const self_type &operator+(difference_type n) {
            self_type tmp = *this;
            return tmp += n;
        }
        const self_type &operator-(difference_type n) {
            self_type tmp = *this;
            return tmp -= n;
        }

        friend const self_type& operator+(difference_type rhs, const self_type& lhs) {
            self_type tmp = lhs;
            return rhs += rhs;
        }

        difference_type operator-(self_type rhs) { return this->ptr_ - rhs->ptr_; } // TODO :: test?
        const value_type &operator[](difference_type n) { return *(*this + n); };
        const value_type &operator[](difference_type n) const { return *(*this + n); };

        const_reference operator*() { return *ptr_; }
        const_pointer operator->() { return ptr_; }

        bool operator==(const self_type &rhs) { return ptr_ == rhs.ptr_; }
        bool operator!=(const self_type &rhs) { return ptr_ != rhs.ptr_; }
        bool operator<(const self_type &rhs) const { return ptr_ < rhs.ptr_; }
        bool operator>(const self_type &rhs) const { return rhs < *this; }
        bool operator<=(const self_type &rhs) const { return !(rhs < *this); }
        bool operator>=(const self_type &rhs) const { return !(*this < rhs); }
     private:
        pointer ptr_;
    };

    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef size_t size_type;

 private:
    allocator_type      _allocator;
    pointer             data_;
    size_type           size_;
    size_type           capacity_;

 public:
/*
 * Constructors and destructors
 */

    //default (1)
    explicit vector(const Allocator &alloc = Allocator())
        : _allocator(alloc), size_(0), capacity_(0) {
        data_ = NULL;
    };
    //fill (2)
    explicit vector(size_type n, const value_type &val = value_type(),
                    const allocator_type &alloc = allocator_type())
        : size_(n), capacity_(n), _allocator(alloc), data_(NULL) {
        if (size_ == 0)
            return;
        data_ = _allocator.allocate(n);
        _construct_n(data_, n, val);
    }
    //range (3)
    template<class InputIterator>
    vector(InputIterator first, InputIterator last,
           const allocator_type &alloc = allocator_type()
           ,typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0
               )
           : _allocator(alloc), size_(0), capacity_(0), data_(NULL) {
        for (; first < last; first++)
            this->push_back(*first);
    }
    //copy (4)
    vector(const vector &x) {

    }

    ~vector() {
        if (empty())
            return;
        _destroy_n(data_, size());
        _allocator.deallocate(data_, size_);
    }

/*
 *  Modifiers
 */
    void clear() {
        _destroy_n(data_, size());
        size_ = 0;
    }

    void swap(vector &other) {
        std::swap(other.data_, data_);
        std::swap(other.size_, size_);
        std::swap(other.capacity_, capacity_);
    }

    void push_back(const T &value) {
        if (size_ >= capacity_) { // ?
            size_type new_capacity = capacity() == 0 ? 1 : capacity() * 2;
            this->reserve(new_capacity);
        }
        data_[size_] = value;
        size_++;
    }

    void pop_back() {
        if (this->empty())
            return;
        _destroy_one(&(data_[--size_]));
    }

    template<class InputIterator>
    void assign(InputIterator first, InputIterator last,
    typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0) {
        *this = vector<T, Allocator>(first, last);
    }

    void assign(size_type n, const value_type &val) {
        *this= vector<T, Allocator>(n, val);
    }

    iterator erase(iterator position) {
        pointer pos = &(*position);
        _destroy_one(pos);
        _move_in_place(pos, pos + 1, &(*(this->end())));
    }

    iterator erase(iterator first, iterator last) {
        _destroy_array(&(*first), &(*last));
        pointer pos = &(*last);
        _move_in_place(pos, pos + 1, &(*(this->end())));
        return &(*first);
    }

    //single element (1)
    iterator insert(iterator position, const value_type &val) {
        this->reserve(size() + 1);
        pointer pos = &(*position);
        _move_in_place(pos, pos + 1, data_ + size());
        _construct_one(pos, val);
        return pos;
    }

    //fill (2)
    void insert(iterator position, size_type n, const value_type &val) {
        this->reserve(size() + n);
        pointer start_position = &(*position);
        _move_in_place(start_position + n, start_position, &(*end()));
        _construct_n(start_position, n, val);
    }
    //range (3)
    template<class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last) {
        return; // TODO:
    }

/*
 * Element access
 */

    reference operator[](size_t index) {
        return data_[index];
    }

    const_reference operator[](size_t index) const {
        return data_[index];
    }

    reference at(size_type n) {
        if (n >= this->size())
            throw std::out_of_range("vector");
        return (*this)[n];
    }

    const_reference at(size_type n) const {
        if (n >= this->size())
            throw std::out_of_range("vector");
        return (*this)[n];
    }

    reference front() {
        return *begin();
    }

    const_reference front() const {
        return *begin();
    }

    reference back() {
        iterator it = end();
        return *(--it);
    }

    const_reference back() const {
        return *(end() - 1);
    }
/*
 *  Capacity
 */

    size_type size() const {
        return size_;
    }

    size_type max_size() const {
        return _allocator.max_size();
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
        pointer old_vector = data_;
        data_ = _allocator.allocate(n);
        if (!this->empty()) {
            _move(data_, old_vector, &old_vector[size()]);
            _allocator.deallocate(old_vector, capacity());
        }
        capacity_ = n;
    }

    void resize(size_type n, value_type val = value_type()) {
        this->reserve(n);
        _construct_array(&data_[size_], &data_[n]);
        _destroy_array(&data_[n], &data_[size_]);
        size_ = n;
    }

    /*
    * iterator functions section
    */
    iterator begin() {
        return data_;
    }

    iterator end() {
        return data_ + size_;
    }

    const_iterator begin() const {
        return data_;
    }

    const_iterator end() const {
        return data_ + size_;
    }

    reverse_iterator rbegin() {
        return std::reverse_iterator<iterator>(begin());
    }

    reverse_iterator rend() {
        return std::reverse_iterator<iterator>(end());
    }

    const_reverse_iterator rbegin() const {
        return std::reverse_iterator<const_iterator>(begin());
    }

    const_reverse_iterator rend() const {
        return std::reverse_iterator<const_iterator>(end());
    }

/*
 * iterator functions section END
 */

    vector<T, Allocator> &operator=(const vector &other) {
        vector<T, Allocator> tmp(other.begin(), other.end());
        std::swap(tmp.data_, data_);
        std::swap(tmp.size_, size_);
        std::swap(tmp.capacity_, capacity_);
        this->assign(other.begin(), other.end());
    }
/*
 *  Compare
 */

    friend bool operator==(const vector &lhs, const vector &rhs) {
        if (lhs.size() != rhs.size())
            return false;
        return equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    friend bool operator<(const vector &lhs, const vector &rhs) {
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    friend bool operator!=(const vector &lhs, const vector &rhs) {
        return !(lhs == rhs);
    }

    friend bool operator>(const vector &lhs, const vector &rhs) {
        return rhs < lhs;
    }
    friend bool operator<=(const vector &lhs, const vector &rhs) {
        return !(rhs < lhs);
    }
    friend bool operator>=(const vector &lhs, const vector &rhs) {
        return !(lhs < rhs);
    }

 private:

    void _construct_one(pointer elem, const value_type &val = value_type()) {
        _allocator.construct(elem, val);
    }

    void _construct_n(pointer p, size_type n, const value_type &val = value_type()) {
        for (size_type i = 0; i < n; i++)
            _construct_one(data_ + i, val);
    }

    void _construct_array(pointer begin, pointer end, const value_type &val = value_type()) {
        for (pointer elem = begin; elem < end; elem++)
            _construct_one(elem, val);
    }
    void _destroy_one(pointer p) {
        _allocator.destroy(p);
    }

    void _destroy_n(pointer p, size_type n) {
        pointer end = p + n;
        for (; p < end; p++)
            _destroy_one(p);
    }

    void _destroy_array(pointer begin, pointer end) {
        for (pointer elem = begin; elem < end; elem++)
            _destroy_one(elem);
    }

    void _move(pointer dst, pointer start, pointer end) {
        if (end < start)
            return;
        for (pointer walker = start; walker < end; walker++, dst++) {
            _construct_one(dst, *walker);
            _destroy_one(walker);
        }
    }

    void _move_in_place(pointer dst, pointer start, pointer end) {
        if (end < start)
            return;
        if (dst < start) {
            _move(dst, start, end);
        }
        for (size_type dist = end - start; dist >= 0; dist--) {
            _construct_one(&(dst[dist]), start[dist]);
            _destroy_one(&(start[dist]));
        }
    }
};
}