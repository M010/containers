#pragma once

#include "pair.h"
#include "Node.h"
#include "rbIterator.h"
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
    typedef rbIterator<value_type>                   iterator;
    typedef rbIterator<const value_type>             const_iterator;
    typedef ft::reverse_iterator<iterator>           reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;
    typedef ptrdiff_t                                difference_type;
    typedef size_t                                   size_type;
    typedef Node<value_type>                         node_type;

 private:
    key_compare _key_cmp;

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

//		bool _v_cmp_less(const value_type &lhs, const value_type &rhs) const
//		{
//			return _key_cmp(lhs.first, rhs.first);
//		}

    bool _v_cmp(const value_type &lhs, const value_type &rhs) const {
        return !(_v_cmp_less(lhs, rhs) || _v_cmp_less(rhs, lhs));
    }

    allocator_type _alloc;
    size_type      _size;
    node_type      *_root;
    node_type      *_Leaf;
    node_type      *_most_left;
    node_type      *_most_right;

    void _update_Leaf() {
        _most_left  = GetMin(_root);
        _most_right = GetMax(_root);
        _Leaf->parent = _most_right;
    }

    void _print(node_type *p, int indent) {
        if (p != NULL && p->notNull()) {
            if (p->right->notNull()) {
                _print(p->right, indent + 4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (p->right->notNull()) std::cout << " /\n" << std::setw(indent) << ' ';
            std::cout << p->val() << "\n ";
            if (p->left->notNull()) {
                std::cout << std::setw(indent) << ' ' << " \\\n";
                _print(p->left, indent + 4);
            }
        }
    }

    static value_type make_val(const key_type &k) {
        return value_type(k, mapped_type());
    }

    ft::pair<node_type *, bool> _put(const value_type &val, node_type *&curr, node_type *parent = NULL) {
        //TODO: parrent is Tnull?
        if (curr == NULL || curr->isNull()) {
            //			bool first_insert = !_root || _root->isNull();
            curr = new node_type(val, _Leaf, parent);
//				if (first_insert)
//				{
//				//	_most_left = curr;
//				//	_most_right = curr;
//				} else if (_v_cmp_less(curr->val(), _most_left->val()))
//				{
//					_most_left = curr;
//				} else if (_v_cmp_less(_most_right->val(), curr->val()))
//				{
//					_most_right = curr;
//				}
            //_Leaf->parent = _most_right; //TODO:
            _size++;
            return ft::make_pair(curr, true);
        }

        if (_v_cmp_less(curr->val(), val))
            return _put(val, curr->right, curr);
        else if (_v_cmp_less(val, curr->val()))
            return _put(val, curr->left, curr);
        return ft::make_pair(curr, false);
    }

 public:

    //TODO: delete it

    node_type *_find_node(const value_type &val, node_type *start = NULL) const {

        if (start == NULL)
            start = _root;
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

    node_type *_exclude_node(node_type *node) {
        //TODO: check if node Is Tnull or null?
        if (node->left->isNull()) {
            if (node->parent->notNull()) {
                node->ParentBranch() = node->right;
            } else
                _root = node->right;
            if (node->right->notNull())
                node->right->parent = node->parent;
            node->right             = node->parent = node->left = _Leaf;
            return node;
        }

        if (node->right->isNull()) {
            if (node->parent->notNull())
                node->ParentBranch() = node->left;
            else
                _root = node->left;
            if (node->left->notNull())
                node->left->parent = node->parent;
            node->right            = node->parent = node->left = _Leaf;
            return node;
        }

        node_type *excluded = _exclude_node(GetMin(node->right));
        copy_links(node, excluded);
        if (node == _root)
            _root = excluded;
        node->right = node->parent = node->left = _Leaf;
        return node;
    };

    size_t _delete_elem(const value_type &val) {
        node_type *found_elem = _find_node(val);
        if (!found_elem || found_elem->isNull())
            return 0;
        _delete_elem(found_elem);
        return 1;
    }

    size_t _delete_elem(node_type *node) {
        delete _exclude_node(node);
        _update_Leaf();
        _size--;
        return 1;
    }

    void print_map() {
        _print(_root, 0);
    }

    void _raw_print(node_type *node) {
        if (node->notNull()) {
            _raw_print(node->left);
            std::cout << node->val() << " ";
            _raw_print(node->right);
        }
    }

    void raw_print() {
        _raw_print(_root);
    }

//TODO: delete it

 public:
    /*
     * Construct and destructors
     */


    explicit map(const key_compare &comp = key_compare(),
                 const allocator_type &alloc = allocator_type())
        : _key_cmp(comp), _v_cmp_less(comp), _alloc(alloc), _size(0), _root(NULL) {
        _root = _Leaf = new node_type();
        _update_Leaf();
    }

    template<class InputIterator>
    map(InputIterator first, InputIterator last,
        const key_compare &comp = key_compare(),
        const allocator_type &alloc = allocator_type(),
        typename enable_if<!is_integral<InputIterator>::value>::type * = 0) :
        _key_cmp(comp), _v_cmp_less(comp), _alloc(alloc), _size(0), _root(NULL) {
        _root = _Leaf = new node_type();
        _update_Leaf();
        this->insert(first, last);
    }

    map(const map &other) :
        _key_cmp(other._key_cmp), _v_cmp_less(_key_cmp), _alloc(other._alloc), _size(0), _root(NULL) {
        _root = _Leaf = new node_type();
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
        delete _Leaf;
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
        return _size;
    }

    bool empty() const {
        return !size();
    }

    size_type max_size() const {
        return 461168601842738790; //TODO::!!
    }

    /*
     * Modifiers
     */

    void swap(map &x) {
        std::swap(_alloc, x._alloc);
        std::swap(_size, x._size);
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
        //TODO:: void hint
        (void) hint;
        //node_type *hint_node = hint.GetNode();
//			if (_v_cmp_less(*hint, value) && _v_cmp_less(value, *ft::next(hint))) //TODO:hard_test
//				return iterator(_put(value, hint_node).first);
        return iterator(insert(value).first);
    }

    template<class InputIt>
    void insert(InputIt first, InputIt last) {
        while (first != last)
            insert(*(first++));
    }

    void erase(iterator position) {
        _delete_elem(position.GetNode()); // TODO: optimize
    }

    size_type erase(const key_type &k) {
        return _delete_elem(make_val(k));
    }

    void erase(iterator first, iterator last) {
        while (first != last)
            erase(first++);
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