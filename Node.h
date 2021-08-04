#pragma once
#include <cstdio>
#include <cassert>

namespace ft {
enum tree_branch {
    LEFT_BRANCH,
    RIGHT_BRANCH
};

template<class V>
struct Node {
    typedef ft::Node<V> self_type;
    typedef V           value_type;

    explicit Node(const value_type &value, self_type *Tnull, self_type *parent = NULL)
        : left(Tnull), right(Tnull), parent(parent ? parent : Tnull), data(new value_type(value)) {}

    Node(const Node &node) : data(NULL) {
        this = node;
    }

    Node &operator=(const Node &node) {
        delete data;
        data = new Node(node.data);
    }

    ~Node() {
        delete data;
    }

    self_type *GetNode(tree_branch branch) {
        return branch == LEFT_BRANCH ? this->left : this->right;
    }

    bool notNull() const { return right; }
    bool isNull() const { return !notNull(); }

    self_type *left;
    self_type *right;
    self_type *parent;
    const value_type &val() const {
        return *data;
    }

    value_type &ref_val() {
        return *data;
    }
    void val(const value_type &val) const {
        if (data)
            *data = val;
        else
            data = new value_type(val);
    }

    Node() : left(NULL), right(NULL), parent(NULL), data(NULL) {}
    Node *&ParentBranch() {
        assert(notNull());
        return (parent->left == this) ? parent->left : parent->right;
    }

 private:
    value_type *data;
};

template<class T>
Node<T> *GetMinMaxAlgo(Node<T> *node, bool min) {
    enum tree_branch branch = min ? LEFT_BRANCH : RIGHT_BRANCH;
    while (node->notNull() && node->GetNode(branch)->notNull())
        node = node->GetNode(branch);
    return node;
}

template<class T>
Node<T> *GetMin(Node<T> *node) {
    return GetMinMaxAlgo(node, true);
}

template<class T>
void copy_links(Node<T> *from, Node<T> *to) {
    to->parent = from->parent;
    to->left   = from->left;
    to->right  = from->right;
    if (from->parent->notNull())
        from->ParentBranch() = to;
    if (to->left->notNull())
        to->left->parent  = to;
    if (to->right->notNull())
        to->right->parent = to;
}

template<class T>
Node<T> *GetMax(Node<T> *node) {
    return GetMinMaxAlgo(node, false);
}

template<class T>
Node<T> *inc_dec_algo(Node<T> *node, bool inc) {
    enum tree_branch branch       = !inc ? LEFT_BRANCH : RIGHT_BRANCH;
    Node<T>          *branch_node = node->GetNode(branch);

    if (branch_node && branch_node->notNull())
        return GetMinMaxAlgo(node->GetNode(branch), inc);

    Node<T> *parent_node = node->parent;
    while (node->notNull() &&
        parent_node->notNull() &&
        (parent_node->GetNode(branch) == node)) {

        node        = parent_node;
        parent_node = parent_node->parent;
    }
    return parent_node;
}

template<class T>
Node<T> *decrement(Node<T> *node) {
    return inc_dec_algo(node, false);
}

template<class T>
Node<T> *increment(Node<T> *node) {
    return inc_dec_algo(node, true);
}
}
