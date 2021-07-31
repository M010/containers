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
		typedef pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef rbIterator<value_type> iterator;
		typedef rbIterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef Node<value_type> node_type;
		class value_compare
		{
			bool operator()(const value_type& lhs, const value_type& rhs){
				return Compare(lhs.first, rhs.first);
			}
		};
	public:


	private:
		key_compare _key_comp;
		allocator_type _alloc;
		value_compare _v_cmp;
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
		/*
		 * Constructors
		 */


		iterator _insert(const value_type& val) {
		}

		//TODO: delete it

		node_type* _find_node(const key_type& key, node_type* start = NULL) const
		{

			if(start == NULL)
				start = _root;
			if(start->isNull() || start->val().second == key)
				return start;

			if(_key_comp(start->val().second, key))
				return _find_node(key, start->right);
			else
				return _find_node(key, start->left);
		}

		node_type* _lower_bound(const value_type& val, node_type* start = NULL) const
		{

			if(start == NULL)
				start = _root;
			if(start->isNull() || start->val() == val)
				return start;

			if(start->val() < val)
			{
				if(start->right->isNull())
					return start;
				return _lower_bound(val, start->right);
			}
			else {
				if(start->left->isNull())
					return increment(start);
				return _lower_bound(val, start->left);
			}
		}

		ft::pair<node_type*, node_type*> _equal_range(const value_type& val){
			node_type* node = _lower_bound(val);
			if(node->notNull() && node->val() == val)
				return make_pair(node, increment(node));
			return make_pair(node, node);
		};



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
		/*
		 * Construct and destructors
		 */


		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type())
		: _size(0), _root(NULL), _key_comp(comp), _alloc(alloc) {_Leaf = node_type(true);}

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) :
				_size(0), _root(NULL), _key_comp(comp), _alloc(alloc){
			_Leaf = node_type(true);
			this->insert(first, last);
		}

		map(const map& other) :
		_size(0), _root(NULL), _key_comp(other._key_comp), _alloc(other._alloc){
			_Leaf = node_type(true);
			*this = other;
		}

		map& operator=(const map& other) {
			if(&other == this)
				return *this;
			this->clear();
			this->insert(other.begin(), other.end());
			return *this;
		}

		~map() {
			this->clear();
		}

		/*
		 * Iterator funcs
		 */

		iterator begin()
		{
			return iterator(_most_left);
		}

		iterator end() {
			return iterator(&_Leaf);
		}


		const_iterator begin() const{
			return const_iterator(_most_left);
		}

		const_iterator end() const
		{
			return const_iterator(&_Leaf);
		}


		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}

		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		const_reverse_iterator rbegin() const{
			return const_reverse_iterator(end());
		}

		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}

		/*
		 * Acsess
		 */

		mapped_type& operator[] (const key_type& k)
		{
			node_type* node = _find_node(k);
			if(node->isNull())
				return insert(make_pair(k, mapped_type())).second;
			return node->val().second;
		}



		/*
		 * Capacity
		 */

		size_type size() const
		{
			return _size;
		}

		bool empty() const {
			return !size();
		}

		size_type max_size() const {
			return 42; //TODO
		}

		/*
		 * Modifiers
		 */
		//TODO:: add swap
		void clear()
		{
			erase(begin(), end());
		}

		ft::pair<iterator, bool> insert(const value_type& val)
		{
			ft::pair<iterator, bool> ret = _put(val, _root);
			_update_Leaf();
			return _put(val, _root);
		}

		iterator insert(iterator hint, const value_type& value )
		{
		    node_type* hint_node = hint.GetNode();
		    if(_cmp(*hint < value) && value < *ft::next(hint)) //TODO:hard_test
                return iterator(_put(value, hint_node).first);
            return iterator(insert(value).first);
		}

		template< class InputIt >
		void insert(InputIt first, InputIt last )
		{
            while (first != last)
                insert(*(first++));
		}

		void erase (iterator position){
			_delete_elem(*position);
		}

		size_type erase (const key_type& k) {
			return _delete_elem(k);
		}

		void erase (iterator first, iterator last) {
			while (first != last)
				erase(first++);
		}

		/*
		 * Lookup
		 */

		size_type count( const key_type & key ) const {
			return find(key) != end();
		}

		iterator find(const key_type& key ) {
			return iterator(_find_node(key));
		}
		const_iterator find(const key_type& key ) const{
			return const_iterator(_find_node(key));
		}

		iterator lower_bound (const key_type& k){
			return iterator(_lower_bound(k));
		}

		const_iterator lower_bound (const key_type& k) const{
			return const_iterator(_lower_bound(k));
		}

		iterator upper_bound (const key_type& k){
			return iterator(_equal_range(k).second);
		}

		const_iterator upper_bound (const key_type& k) const{
			return const_iterator(_equal_range(k).second);
		}


		pair<iterator,iterator>    equal_range (const key_type& k) {
			ft::pair<node_type*, node_type*> range = _equal_range(k);
			return make_pair(iterator(range.first), iterator(range.second));
		}

		pair<const_iterator,const_iterator>    equal_range (const key_type& k) const {
			ft::pair<node_type*, node_type*> range = _equal_range(k);
			return make_pair(const_iterator(range.first), const_iterator(range.second));
		}

	};
}