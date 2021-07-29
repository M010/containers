#pragma once
#include "pair.h"
#include "Node.h"
#include "rbIterator.h"
#include "utils.h"
#include <functional>
#include <memory>
#include <cstddef>
#include <iostream>
#include <iomanip>

namespace ft
{
	template<
			class Key,
			class T,
			class Compare = std::less<Key>,
			class Allocator = std::allocator<ft::pair<const Key, T> >
	>
	class map
	{
	public:
		typedef map< Key, T, Compare, Allocator> self_type;
		typedef Key key_type;
		typedef T mapped_type;
		//typedef pair<const key_type, mapped_type> value_type;
		typedef Key value_type;
		typedef Compare key_compare;
		//typedef value_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef rbIterator<value_type> iterator;
		//typedef typename const_iterator const_iterator;
		//typedef typename reverse_iterator<iterator> reverse_iterator;
		//typedef typename reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef Node<value_type> node_type;

	private:
		size_type _size;
		node_type* _root;
		node_type _Leaf;
		node_type* _most_left;
		node_type* _most_right;

		void _update_Leaf()
		{
			_most_left = GetMin(_root);
			_most_right = GetMax(_root);
            _Leaf.parent = _most_right;
		}

		void _print(node_type* p, int indent){
			if(p != NULL && p->notNull()) {
				if(p->right->notNull()) {
					_print(p->right, indent + 4);
				}
				if (indent) {
					std::cout << std::setw(indent) << ' ';
				}
				if (p->right->notNull()) std::cout<<" /\n" << std::setw(indent) << ' ';
				std::cout<< p->val() << "\n ";
				if(p->left->notNull()) {
					std::cout << std::setw(indent) << ' ' <<" \\\n";
					_print(p->left, indent + 4);
				}
			}
		}

		ft::pair<node_type*, bool> _put(const value_type& val, node_type*& curr, node_type* parent = NULL){
		    //TODO: parrent is Tnull?
			if(curr == NULL || curr->isNull()){
				bool first_insert = !_root || _root->isNull();
                curr = new node_type(val, &_Leaf, parent);
				if(first_insert)
				{
					_most_left = curr;
					_most_right = curr;
				} else if(curr->val() < _most_left->val()) {
					_most_left = curr;
				} else if(curr->val() > _most_right->val()) {
					_most_right = curr;
				}
                _Leaf.left = _Leaf.parent = _most_right; //TODO:
				_size++;
				return make_pair(curr, true);
			}

			if(curr->val() < val)
                return _put(val, curr->right, curr);
			else if( val < curr->val() )
                return _put(val, curr->left, curr);
            return make_pair(curr, false);
		}

	public:
		map() : _size(0), _root(NULL)
		{
            _Leaf = node_type(true);
		}

		size_type size()
		{
            return _size;
		}
		/*
		 * Iteratror funcs
		 */
		iterator begin()
		{
			return iterator(_most_left);
		}
		iterator end() {
			return iterator(&_Leaf);
		}
		iterator _insert(const value_type& val) {
			iterator ret = iterator(_put(val, _root).first);
            _update_Leaf();
			return ret;
		}

		//TODO: delete it

		node_type* _find_node(const value_type& val, node_type* start = NULL)
		{

			if(start == NULL)
				start = _root;
			if(!start->notNull() || start->val() == val)
				return start;

			if(start->val() < val)
				return _find_node(val, start->right);
			else
				return _find_node(val, start->left);
		}

		node_type* _exclude_node (node_type * node)
		{
			//TODO: check if node Is Tnull or null?
			if(node->left->isNull())
			{
			    if(node->parent->notNull()) {
			        node->ParentBranch() = node->right;
			    } else
				    _root = node->right;
				if(node->right->notNull())
					node->right->parent = node->parent;
				node->right = node->parent = node->left = &_Leaf;
				return node;
			}

			if(node->right->isNull())
			{
				if(node->parent->notNull())
					node->ParentBranch() = node->left;
				else
				    _root = node->left;
				if(node->left->notNull())
					node->left->parent = node->parent;
				node->right = node->parent = node->left = &_Leaf;
				return node;
			}

			node_type * excluded = _exclude_node(GetMin(node->right));
			copy_links(node, excluded);
			if(node == _root)
				_root = excluded;
			node->right = node->parent = node->left = &_Leaf;
			return node;
		};

		size_t _delete_elem(const value_type& val){
			node_type* found_elem = _find_node(val);
			if(!found_elem || found_elem->isNull())
				return 0;
			delete _exclude_node(found_elem);
            _update_Leaf();
			_size--;
			return 1;
		}


		void print_map() {
			_print(_root, 0);
		}

		void _raw_print(node_type* node){
			if(node->notNull())
			{
				_raw_print(node->left);
				std::cout << node->val() << " ";
				_raw_print(node->right);
			}
		}
		void raw_print(){
			_raw_print(_root);
		}
//TODO: delete it

	public:
		//Modifiers
		//pair<iterator,bool> _insert (const value_type& val);
		//with hint (2)
		//iterator _insert (iterator position, const value_type& val);
		//range (3)
		//template <class InputIterator>
		//void _insert (InputIterator first, InputIterator last);


		/*
		 * Modifiers
		 */

		ft::pair<iterator, bool> insert(const value_type& val)
		{
            return _put(val, _root);
		}

		iterator insert(iterator hint, const value_type& value )
		{
		    node_type* hint_node = hint.GetNode();
		    if(*hint < value && value < *ft::next(hint)) //TODO:hard_test
                return iterator(_put(value, hint).first);
            return iterator(insert(value).first);
		}

		template< class InputIt >
		void insert(InputIt first, InputIt last )
		{
            while (first != last)
                insert(*(first++));
		}

    //    template<class >
	//	void erase (iterator position){
	//
	//	}
	//
	//	void erase (iterator position){
	//
	//	}
	//
	//	//(2)
	//	size_type erase (const key_type& k);
	//	//(3)
	//	void erase (iterator first, iterator last);
	};
}