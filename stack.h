#pragma once

#include "vector.hpp"
namespace ft {
template<
    class T,
    class Container = ft::vector<T>
>
class stack {
 protected:
    Container _container;
 public:
    typedef Container                           container_type;
    typedef typename Container::value_type      value_type;
    typedef typename Container::size_type       size_type;
    typedef typename Container::reference       reference;
    typedef typename Container::const_reference const_reference;

    explicit stack(const container_type &ctnr = container_type()) : _container(ctnr) {}
    size_type size() const { return _container.size(); }
    bool empty() const { return _container.size() == 0; }
    value_type &top() { return _container.back(); }
    const value_type &top() const { return _container.back(); }
    void push(const value_type &val) { _container.push_back(val); }
    void pop() { _container.pop_back(); }
    friend bool operator==(const stack &lhs, const stack &rhs) {
        return lhs._container == rhs._container;
    }
    friend bool operator!=(const stack &lhs, const stack &rhs) {
        return rhs != lhs;
    }
    friend bool operator<(const stack &lhs, const stack &rhs) {
        return lhs._container < rhs._container;
    }
    friend bool operator>(const stack &lhs, const stack &rhs) {
        return lhs > rhs;
    }
    friend bool operator<=(const stack &lhs, const stack &rhs) {
        return rhs <= lhs;
    }
    friend bool operator>=(const stack &lhs, const stack &rhs) {
        return lhs >= rhs;
    }
};
}