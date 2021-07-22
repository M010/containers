#pragma once

#include <cstdio>

namespace ft
{
	enum tree_branch{
		LEFT_BRANCH,
		RIGHT_BRANCH
	};

	template<class V>
	struct Node
	{

		typedef ft::Node<V> self_type;
		typedef V value_type;
		explicit Node(value_type value, self_type* parent = NULL)
		: left(NULL), right(NULL), parent(parent), data(value)
		{}
		self_type* GetNode(tree_branch branch)
		{
			return branch == LEFT_BRANCH ? this->left : this->right;
		}
		self_type* left;
		self_type* right;
		self_type* parent;
		value_type data;
	};


	template <class T>
	Node<T>* GetMinMaxAlgo(Node<T> *node, bool min){
		enum tree_branch branch = min ? LEFT_BRANCH : RIGHT_BRANCH;
		while (node && node->GetNode(branch))
			node = node->GetNode(branch);
		return node;
	}

	template<class T>
	Node<T>* GetMin(Node<T> *node){
		return GetMinMaxAlgo(node, true);
	}

	template<class T>
	Node<T>* GetMax(Node<T> *node){
		return GetMinMaxAlgo(node, false);
	}



	template <class T>
	Node<T>* inc_dec_algo(Node<T> *node, bool inc){
		enum tree_branch branch = !inc ? LEFT_BRANCH : RIGHT_BRANCH;
		if(node->GetNode(branch))
			return GetMinMaxAlgo(node->GetNode(branch), inc);

		Node<T>* parent_node = node->parent;
		while (parent_node && parent_node->GetNode(branch) == node)
		{
			node = parent_node;
			parent_node = parent_node->parent;
		}
		return parent_node;
	}

	template<class T>
	Node<T> * decrement(Node<T> *node)
	{
		return inc_dec_algo(node, false);
	}

	template<class T>
	Node<T> * increment(Node<T> *node)
	{
		return inc_dec_algo(node, true);
	}

}




