#pragma once

#include "pair.h"
#include "Node.h"
#include "mapIterator.h"
#include "reverse_iterator.h"
#include "utils.h"
#include <functional>
#include <memory>
#include <cstddef>
#include <iostream>
#include <iomanip>

namespace ft {
template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<ft::pair<const Key, T> >
>
class map {

 public:
    typedef map<Key, T, Compare, Allocator>          self_type;
    typedef Key                                      key_type;
    typedef T                                        mapped_type;
    typedef ft::pair<const key_type, mapped_type>    value_type;
    typedef Compare                                  key_compare;
    typedef Allocator                                allocator_type;
    typedef typename allocator_type::reference       reference;
    typedef typename allocator_type::const_reference const_reference;
    typedef typename allocator_type::pointer         pointer;
    typedef typename allocator_type::const_pointer   const_pointer;
    typedef mapIterator<value_type>                  iterator;
    typedef mapIterator<const value_type>            const_iterator;
    typedef ft::reverse_iterator<iterator>           reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;
    typedef ptrdiff_t                                difference_type;
    typedef size_t                                   size_type;
    typedef Node<value_type>                         node_type;
 private:

    key_compare     _key_cmp;
    struct ValComp {
        ValComp(key_compare key_cmp) : _key_cmp(key_cmp) {}
        bool operator()(const value_type &lhs, const value_type &rhs) const {
            return _key_cmp(lhs.first, rhs.first);
        }
     private:
        key_compare _key_cmp;
    };
    typedef ValComp value_compare;
    value_compare   _v_cmp_less;

    allocator_type                                                _alloc;
    node_type                                                     *_root;
    node_type                                                     *_Leaf;
    node_type                                                     *_most_left;
    node_type                                                     *_most_right;
    typedef typename Allocator::template rebind<node_type>::other node_allocator;
    node_allocator                                                _node_alloc;

    node_type *_alloc_node() {
        node_type *allocated = _node_alloc.allocate(1);
        _node_alloc.construct(allocated, node_type());
        return allocated;
    }

    node_type *_alloc_node(const value_type &val, node_type *leaf, node_type *parent = NULL) {
        node_type  *allocated = _node_alloc.allocate(1);
        value_type *p_val     = _alloc.allocate(1);
        _alloc.construct(p_val, value_type(val));
        _node_alloc.construct(allocated, node_type(p_val, leaf, parent));
        return allocated;
    }

    void _dealloc_node(node_type *node) {
        if (node->data) {
            _alloc.destroy(node->data);
            _alloc.deallocate(node->data, 1);
        }
        _node_alloc.destroy(node);
        _node_alloc.deallocate(node, 1);
    }

    bool _v_cmp(const value_type &lhs, const value_type &rhs) const {
        return !(_v_cmp_less(lhs, rhs) || _v_cmp_less(rhs, lhs));
    }

    void _update_Leaf() {
        _most_left  = GetMin(_root);
        _most_right = GetMax(_root);
        _Leaf->parent = _most_right;
    }

    static value_type make_val(const key_type &k) {
        return value_type(k, mapped_type());
    }

    ft::pair<node_type *, bool> _put(const value_type &val, node_type *&curr, node_type *parent = NULL) {
        if (curr == NULL || curr->isNull()) {
            curr = _alloc_node(val, _Leaf, parent);
            return ft::make_pair(curr, true);
        }

        ft::pair<node_type *, bool> ret = ft::make_pair(curr, false);
        if (rand() % (curr->size + 1) == 0)
            ret = insert_root(val, curr, curr->parent);
        else if (_v_cmp_less(curr->val(), val))
            ret = _put(val, curr->right, curr);
        else if (_v_cmp_less(val, curr->val()))
            ret = _put(val, curr->left, curr);
        curr->update_size();
        return ret;
    }

    void rotate_right(node_type *p) {
        node_type *q      = p->left;
        bool      is_root = p == _root;

        if (!q || q->isNull()) {
            return;
        }

        if (p->parent && p->parent->notNull()) {
            p->ParentBranch() = q;
        }
        q->parent = p->parent;
        p->assign_node(LEFT_BRANCH, q->right);
        q->assign_node(RIGHT_BRANCH, p);

        if (is_root)
            _root = q;
        p->update_size();
        q->update_size();
    }

    void rotate_left(node_type *p) {
        node_type *q      = p->right;
        bool      is_root = p == _root;

        if (!q || q->isNull()) {
            if (is_root)
                _root = p;
            return;
        }

        if (p->parent && p->parent->notNull()) {
            p->ParentBranch() = q;
        }
        q->parent = p->parent;
        p->assign_node(RIGHT_BRANCH, q->left);
        q->assign_node(LEFT_BRANCH, p);

        if (is_root)
            _root = q;

        p->update_size();
        q->update_size();
    }

    node_type *join(node_type *left, node_type *right) // объединение двух деревьев
    {
        if (!left || left->isNull()) return right;
        if (!right || right->isNull()) return left;

        if (right->size > left->size) {
            left->assign_node(RIGHT_BRANCH, join(left->right, right));
            left->update_size();
            return left;
        } else {
            right->assign_node(LEFT_BRANCH, join(left, right->left));
            right->update_size();
            return right;
        }
    }

    ft::pair<node_type *, bool> insert_root(const value_type &val, node_type *&curr, node_type *parent = NULL) {
        if (curr == NULL || curr->isNull()) {
            curr = _alloc_node(val, _Leaf, parent);
            return ft::make_pair(curr, true);
        }
        ft::pair<node_type *, bool> ret = ft::make_pair(curr, false);
        if (_v_cmp_less(curr->val(), val)) {
            ret = insert_root(val, curr->right, curr);
            rotate_left(curr);
        } else if (_v_cmp_less(val, curr->val())) {
            ret = insert_root(val, curr->left, curr);
            rotate_right(curr);
        }
        return ret;
    }

    node_type *_find_node(const value_type &val, node_type *start = NULL) const {

        start = start ? start : _root;
        if (start->isNull() || _v_cmp(start->val(), val))
            return start;

        if (_v_cmp_less(start->val(), val))
            return _find_node(val, start->right);
        else
            return _find_node(val, start->left);
    }

    node_type *_lower_bound(const value_type &val, node_type *start = NULL) const {

        if (start == NULL)
            start = _root;
        if (start->isNull() || _v_cmp(start->val(), val))
            return start;

        if (_v_cmp_less(start->val(), val)) {
            if (start->right->isNull())
                return increment(start);
            return _lower_bound(val, start->right);
        } else {
            if (start->left->isNull())
                return start;
            return _lower_bound(val, start->left);
        }
    }

    ft::pair<node_type *, node_type *> _equal_range(const value_type &val) const {
        node_type *node = _lower_bound(val);
        if (node->notNull() && _v_cmp(node->val(), val))
            return ft::make_pair(node, increment(node));
        return ft::make_pair(node, node);
    };

    size_t _delete_random_node(const value_type &val, node_type *&curr) {
        if (curr == NULL || curr->isNull()) {
            return 0;
        }

        size_t    ret          = 0;
        node_type *copy_curr   = curr;
        node_type *parent_curr = curr->parent;

        if (_v_cmp(curr->val(), val)) {
            curr = join(curr->left, curr->right);
            if (!curr || curr->notNull()) {
                curr->parent = parent_curr;
                curr->update_size();
            }
            _dealloc_node(copy_curr);
            return 1;
        }

        if (_v_cmp_less(curr->val(), val)) {
            ret = _delete_random_node(val, curr->right);
        } else if (_v_cmp_less(val, curr->val()))
            ret = _delete_random_node(val, curr->left);
        curr->update_size();
        return ret;
    }

 public:
    /*
     * Construct and destructors
     */


    explicit map(const key_compare &comp = key_compare(),
                 const allocator_type &alloc = allocator_type())
        : _key_cmp(comp), _v_cmp_less(comp), _alloc(alloc), _root(_alloc_node()), _Leaf(_root) {
        _update_Leaf();
    }

    template<class InputIterator>
    map(InputIterator
        first, InputIterator
        last,
        const key_compare &comp = key_compare(),
        const allocator_type &alloc = allocator_type(),
        typename enable_if<!is_integral<InputIterator>::value>::type * = 0) :
        _key_cmp(comp), _v_cmp_less(comp), _alloc(alloc), _root(_alloc_node()), _Leaf(_root) {
        _update_Leaf();
        this->insert(first, last);
    }

    map(
        const map &other) :
        _key_cmp(other._key_cmp), _v_cmp_less(_key_cmp), _alloc(other._alloc),
        _root(_alloc_node()), _Leaf(_root) {
        _update_Leaf();
        *this = other;
    }

    map &operator=(const map &other) {
        if (&other == this)
            return *this;
        this->clear();
        this->insert(other.begin(), other.end());
        return *this;
    }

    ~map() {
        this->clear();
        _dealloc_node(_Leaf);
    }

    /*
     * Iterator funcs
     */

    iterator begin() {
        return iterator(_most_left);
    }

    iterator end() {
        return iterator(_Leaf);
    }

    const_iterator begin() const {
        return const_iterator(_most_left);
    }

    const_iterator end() const {
        return const_iterator(_Leaf);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(end());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(begin());
    }

    /*
     * Acsess
     */

    mapped_type &operator[](const key_type &k) {
        node_type *nodeType = insert(ft::make_pair(k, mapped_type())).first.GetNode();
        return nodeType->ref_val().second;
    }

    /*
     * Capacity
     */

    size_type size() const {
        return _root->size;
    }

    bool empty() const {
        return !size();
    }

    size_type max_size() const {
        return _alloc.max_size();
    }

    /*
     * Modifiers
     */

    void swap(map &x) {
        std::swap(_alloc, x._alloc);
        std::swap(_root, x._root);
        std::swap(_Leaf, x._Leaf);
        std::swap(_most_left, x._most_left);
        std::swap(_most_right, x._most_right);
    }

    void clear() {
        erase(begin(), end());
    }

    ft::pair<iterator, bool> insert(const value_type &val) {
        ft::pair<iterator, bool> ret = _put(val, _root);
        _update_Leaf();
        return ret;
    }

    iterator insert(iterator hint, const value_type &value) {
        (void) hint;
        return iterator(insert(value).first);
    }

    template<class InputIt>
    void insert(InputIt first, InputIt last) {
        while (first != last)
            insert(*(first++));
    }

    void erase(iterator position) {
        _delete_random_node(*position, _root);
        _update_Leaf();
    }

    size_type erase(const key_type &k) {
        size_type ret = _delete_random_node(make_val(k), _root);
        _update_Leaf();
        return ret;
    }

    void erase(iterator first, iterator last) {
        while (first != last) {
            erase(first++);
        }
    }

    key_compare key_comp() const {
        return _key_cmp;
    }

    value_compare value_comp() const {
        return _v_cmp_less;
    }

    /*
     * Lookup
     */

    size_type count(const key_type &key) const {
        return find(key) != end();
    }

    iterator find(const key_type &key) {
        node_type *node = _find_node(ft::make_pair(key, mapped_type()));
        return iterator(node);
    }

    const_iterator find(const key_type &key) const {
        node_type *node = _find_node(ft::make_pair(key, mapped_type()));
        return const_iterator(node);
    }

    iterator lower_bound(const key_type &k) {
        return iterator(_lower_bound(make_val(k)));
    }

    const_iterator lower_bound(const key_type &k) const {
        return const_iterator(_lower_bound(make_val(k)));
    }

    iterator upper_bound(const key_type &k) {
        return iterator(_equal_range(make_val(k)).second);
    }

    const_iterator upper_bound(const key_type &k) const {
        return const_iterator(_equal_range(make_val(k)).second);
    }

    ft::pair<iterator, iterator> equal_range(const key_type &k) {
        ft::pair<node_type *, node_type *> range = _equal_range(make_val(k));
        return ft::make_pair(iterator(range.first), iterator(range.second));
    }

    ft::pair<const_iterator, const_iterator> equal_range(const key_type &k) const {
        ft::pair<node_type *, node_type *> range = _equal_range(make_val(k));
        return ft::make_pair(const_iterator(range.first), const_iterator(range.second));
    }
    friend bool operator==(const map &lhs, const map &rhs) {
        if (lhs.size() != rhs.size())
            return false;
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    friend bool operator!=(const map &lhs, const map &rhs) {
        return !(rhs == lhs);
    }

    friend bool operator<(const map &lhs, const map &rhs) {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    friend bool operator>(const map &lhs, const map &rhs) {
        return rhs < lhs;
    }
    friend bool operator<=(const map &lhs, const map &rhs) {
        return !(rhs < lhs);
    }
    friend bool operator>=(const map &lhs, const map &rhs) {
        return !(lhs < rhs);
    }
};
}