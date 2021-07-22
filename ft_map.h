#pragma once
#include "pair.h"
#include "Node.h"
#include "rbIterator.h"
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
		node_type* _head;
		void _print(node_type* p, int indent){
			if(p != NULL) {
				if(p->right) {
					_print(p->right, indent + 4);
				}
				if (indent) {
					std::cout << std::setw(indent) << ' ';
				}
				if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
				std::cout<< p->data << "\n ";
				if(p->left) {
					std::cout << std::setw(indent) << ' ' <<" \\\n";
					_print(p->left, indent + 4);
				}
			}
		}

		node_type* _put(const value_type& val, node_type*& node, node_type* parent = NULL){
			if(node == NULL){
				node = new node_type(val, parent);
				return node;
			}
			if(node->data == val) {
				node->data == val; //TODO: bullshit
				return node;
			}
			if(node->data < val)
				_put(val, node->right, node);
			else
				_put(val, node->left, node);
		}
	public:
		map() : _size(0), _head(NULL)
		{}
//TODO: delete it
		iterator insert(const value_type& val) {
			_put(val, _head);
		}
		void print_map() {
			_print(_head, 0);
		}
		void _raw_print(node_type* node){
			if(node != NULL)
			{
				_raw_print(node->left);
				std::cout << node->data << " ";
				_raw_print(node->right);
			}
		}
		void raw_print(){
			_raw_print(_head);
		}
//TODO: delete it

	public:
		//Modifiers
		//pair<iterator,bool> insert (const value_type& val);
		//with hint (2)
		//iterator insert (iterator position, const value_type& val);
		//range (3)
		//template <class InputIterator>
		//void insert (InputIterator first, InputIterator last);

	};
}