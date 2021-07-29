#pragma once
#include <iterator>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <cstddef>
#include "utils.h"

namespace ft {
template<class T,
         class Allocator = std::allocator<T> >
class vector {

 public:
    typedef T                                      value_type;
    typedef Allocator                              allocator_type;
    typedef typename allocator_type::reference     reference;
    typedef typename allocator_type::reference     const_reference;
    typedef typename allocator_type::pointer       pointer;
    typedef typename allocator_type::const_pointer const_pointer;

    class iterator :
        public std::iterator<std::random_access_iterator_tag,
                             value_type,
                             ptrdiff_t,
                             pointer,
                             reference> {
     public:
        typedef int      difference_type;
        typedef iterator self_type;
        iterator() : ptr_(NULL) {}
        iterator(pointer ptr) : ptr_(ptr) {}
        self_type& operator++() {
			ptr_++;
			return *this;
		}
		self_type operator++(int) {
			self_type i = *this;
			ptr_++;
			return i;
		}
		self_type operator--() {
			ptr_--;
			return *this;
		}
		self_type operator--(int) {
			self_type i = *this;
			ptr_--;
			return i;
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
        friend const self_type &operator+(difference_type rhs, const self_type &lhs) {
            self_type tmp = lhs;
            return tmp += rhs;
        }
        const self_type &operator-(difference_type n) {
            self_type tmp = *this;
            return tmp -= n;
        }
        difference_type operator-(self_type rhs) { return this->ptr_ - rhs.ptr_; } // TODO :: test?
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
    class const_iterator : public std::iterator<std::random_access_iterator_tag,
                                                value_type,
                                                ptrdiff_t,
                                                pointer,
                                                reference> {
     public:
        typedef int            difference_type;
        typedef const_iterator self_type;

        const_iterator() : ptr_(NULL) {}
        const_iterator(pointer ptr) : ptr_(ptr) {}

		self_type& operator++() { ptr_++; return *this;}
		self_type operator++(int) {
			self_type i = *this;
			ptr_++;
			return i;
		}
		self_type& operator--() {
			ptr_--;
			return *this;
		}
		self_type operator--(int) {
			self_type i = *this;
			ptr_--;
			return i;
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

        friend const self_type &operator+(difference_type rhs, const self_type &lhs) {
            self_type tmp = lhs;
            return rhs += rhs;
        }

        difference_type operator-(self_type rhs) { return this->ptr_ - rhs.ptr_; } // TODO :: test?
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
    typedef size_t                                size_type;

 private:
    allocator_type _allocator;
    pointer        data_;
    size_type      size_;
    size_type      capacity_;

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
    vector(InputIterator first,
           InputIterator last,
           const allocator_type &alloc = allocator_type(),
           typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0
    )
        : _allocator(alloc), size_(0), capacity_(0), data_(NULL) {
        int i = 10;
        for (; first != last; first++) {
            this->push_back(*first);
        }
    }
    //copy (4)
    vector(const vector &x)
        : _allocator(x._allocator), size_(0), capacity_(0), data_(NULL) {
        *this = x;
    }

    vector<T, Allocator> &operator=(const vector &other) {
        vector<T, Allocator> tmp(other.begin(), other.end(), other._allocator);
        std::swap(tmp.data_, data_);
        std::swap(tmp.size_, size_);
        std::swap(tmp.capacity_, capacity_);
        return *this;
    }

    ~vector() {
        if (empty())
            return;
        _destroy_n(data_, size());
        _allocator.deallocate(data_, capacity_);
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
        _construct_one(&data_[size()], value);
        size_++;
    }

    void pop_back() {
        if (this->empty())
            return;

        _destroy_one(&(data_[size_]));
        size_--;
    }

    template<class InputIterator>
    void assign(InputIterator first, InputIterator last,
                typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0) {
        *this = vector<T, Allocator>(first, last);
    }

    void assign(size_type n, const value_type &val) {
        *this = vector<T, Allocator>(n, val);
    }

    iterator erase(iterator position) {
        pointer pos = &(*position);
        _destroy_one(pos);
        _move_in_place(pos, pos + 1, &(*(this->end())));
        size_--;
        return pos;
    }

    iterator erase(iterator first, iterator last) {
        ptrdiff_t n = last - first;
        _destroy_array(&(*first), &(*last));
        _move_in_place(&(*first), &(*last), &(*(end())));
        size_ -= n;
        return &(*first);
    }

    //single element (1)
    iterator insert(iterator position, const value_type &val) {
    	ptrdiff_t element_index = position - begin();
        this->reserve(size() + 1);
        pointer pos = data_ + element_index ;
        _move_in_place(pos + 1, pos, data_ + size());
        _construct_one(pos, val);
        size_++;
        return pos;
    }

    //fill (2)
    void insert(iterator position, size_type n, const value_type &val) {
		ptrdiff_t element_index =  position - begin();
		this->reserve(size() + n);
        pointer start_position = data_ + element_index;
        _move_in_place(start_position + n, start_position, &(*end()));
        _construct_n(start_position, n, val);
        size_ += n;
    }
    //range (3)
    template<class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last,
				typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0) {
    	ptrdiff_t n = std::distance(first, last);
		ptrdiff_t element_index =  position - begin();
		this->reserve(size() + n);
		pointer start_position = data_ + element_index;
		_move_in_place(start_position + n, start_position, &(*end()));
		for(pointer walker = start_position; first != last; walker++ ,first++)
			_construct_one(walker, *first);
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
//TODO: maybe front is not in container
    reference front() {
        return *begin();
    }

    const_reference front() const {
        return *begin();
    }

    reference back() {
        return *(rend());
    }

    const_reference back() const {
        return *(rend());
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
        if (this->size() != 0)
            _move(data_, old_vector, &old_vector[size()]);
        if (this->capacity() != 0)
            _allocator.deallocate(old_vector, capacity());
        capacity_ = n;
    }

    void resize(size_type n, value_type val = value_type()) {
        this->reserve(n);
        _construct_array(&data_[size_], &data_[n], val);
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
        return std::reverse_iterator<iterator>(end());
    }

    reverse_iterator rend() {
        return std::reverse_iterator<iterator>(begin());
    }

    const_reverse_iterator rbegin() const {
        return std::reverse_iterator<const_iterator>(end());
    }

    const_reverse_iterator rend() const {
        return std::reverse_iterator<const_iterator>(begin());
    }

/*
 * iterator functions section END
 */


/*
 *  Compare
 */

    friend bool operator==(const vector &lhs, const vector &rhs) {
        if (lhs.size() != rhs.size())
            return false;
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    friend bool operator<(const vector &lhs, const vector &rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
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

    void _construct_n(pointer dst, size_type n, const value_type &val = value_type()) {
        for (size_type i = 0; i < n; i++)
            _construct_one(dst + i, val);
    }

    void _construct_array(pointer begin, pointer end, const value_type &val = value_type()) {
        for (pointer elem = begin; elem < end; elem++)
            _construct_one(elem, val);
    }
    void _destroy_one(pointer elem) {
        _allocator.destroy(elem);
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
        if (end <= start)
            return;
        for (pointer walker = start; walker < end; walker++, dst++) {
            _construct_one(dst, *walker);
            _destroy_one(walker);
        }
    }

    void _move_in_place(pointer dst, pointer start, pointer end) {
        if (end <= start)
            return;
        if (dst < start) {
            _move(dst, start, end);
            return;
        }
        for (ptrdiff_t dist = end - start - 1; dist >= 0; dist--) {
            _construct_one(&(dst[dist]), start[dist]);
            _destroy_one(&(start[dist]));
        }
    }
};
}