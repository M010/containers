#pragma once
#include "Node.h"
#include <iterator>
#include <cassert>
#include "utils.h"


namespace ft
{
	template<class T>
	class rbIterator
	{
	public:
		typedef std::bidirectional_iterator_tag  iterator_category;
		typedef T        value_type;
		typedef std::ptrdiff_t difference_type;
		typedef value_type*  pointer;
		typedef value_type& reference;
		typedef rbIterator<T> 	self_type;
		typedef Node<typename remove_const<value_type>::type> node_type;
		rbIterator(node_type* node = NULL): _node(node){};
	private:
		node_type *_node;
	public:
		template<class Some>
		rbIterator(rbIterator<Some> it){
			_node = it.GetNode();
		}

		node_type *GetNode() const {
			return _node;
		}

		bool operator==(const rbIterator &rhs) const
		{
			return _node == rhs._node;
		}

		bool operator!=(const rbIterator &rhs) const
		{
			return !(rhs == *this);
		}



		self_type& operator++() {
			_node = increment(_node);
			return *this;
		}

		self_type operator++(int) {
			self_type tmp = *this;
			this->_node = increment(this->_node);
			return tmp;
		}

		self_type& operator--() {
			_node = decrement(_node);
			return *this;
		}

		self_type operator--(int) {
			self_type tmp = *this;
			this->_node = decrement(this->_node);
			return tmp;
		}

		reference operator*() { return const_cast<reference>(_node->val()); }
		pointer operator->() { return &(_node->ref_val()); }
	};
}
