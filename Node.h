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

    explicit Node(value_type *value, self_type *Tnull, self_type *parent = NULL)
        : left(Tnull), right(Tnull), parent(parent ? parent : Tnull), data(NULL), size(1) {
        data = value;
    }

    Node(const Node &node)
        : data(NULL), size(0) {
        *this = node;
    }

    void assign_node(tree_branch branch, Node *node) {
        this->GetNode(branch) = node;
        if (!node || node->notNull())
            node->parent = this;
    }

    void update_size()
    {
        size = get_size(left) + get_size(right) + 1;
    }

    Node &operator=(const Node &node) {
        if (this == &node)
            return *this;
        data   = node.data;
        size   = node.size;
        left   = node.left;
        right  = node.right;
        parent = node.parent;
        return *this;
    }

    self_type *GetNode(tree_branch branch) const {
        return branch == LEFT_BRANCH ? this->left : this->right;
    }

    self_type *&GetNode(tree_branch branch) {
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

    Node() : left(NULL), right(NULL), parent(NULL), data(NULL), size(0) {}
    Node *&ParentBranch() {
        assert(notNull());
        return (parent->left == this) ? parent->left : parent->right;
    }

    value_type *data;
    size_t     size;
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

template<class T>
size_t get_size(Node<T> *node) {
    if (node)
        return node->size;
    return 0;
}

}
