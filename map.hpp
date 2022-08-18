#ifndef MAP_H
# define MAP_H

// # include "utils.hpp"
# include "_tree.hpp"
// # include "iterators.hpp"

namespace ft
{

	template<typename Key, typename T, typename Compare = std::less<Key>, typename Alloc = std::allocator<ft::pair<Key const, T> > >
	class map
	{
	public:

		typedef Key										key_type;
		typedef T										mapped_type;
		typedef ft::pair<const key_type, mapped_type>	value_type;
		typedef	Compare									key_compare;
		typedef Alloc																			allocator_type;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
		protected:
			Compare comp;
		public:
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;
			value_compare(Compare c): comp(c) {};
			bool operator()(const value_type& lhs, const value_type& rhs) const {return (comp(lhs.first, rhs.first));};
		};
	private:
		typedef typename ft::Tree<Key, T, key_compare, allocator_type> t_tree;
	public:
		typedef value_type&																		reference;
		typedef const value_type&																const_reference;
		typedef value_type*																		pointer;
		typedef const value_type*																const_pointer;
		typedef typename t_tree::iterator				iterator;
		typedef typename t_tree::const_iterator			const_iterator;
		typedef typename t_tree::reverse_iterator		reverse_iterator;
		typedef typename t_tree::const_reverse_iterator	const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator >::difference_type							difference_type;
		typedef typename allocator_type::size_type												size_type;

		explicit map(const Compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, allocator_type(alloc)) {};

		template<typename InputIterator>
		map(InputIterator first, InputIterator last, const Compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, allocator_type(alloc)) {_tree.insert(first, last);};

		map(const map& src) : _tree(src._tree) {};

		map	&operator=(const map& rhs) {_tree = rhs._tree; return (*this);};

		virtual ~map(void) {};

		iterator begin(void) {return (_tree.begin());};
		const_iterator begin(void) const {return (const_iterator(_tree.begin()));};
		iterator end(void) {return (_tree.end());};
		const_iterator end(void) const {return (_tree.end());};
		reverse_iterator rbegin(void) {return (_tree.rbegin());};
		const_reverse_iterator rbegin(void) const {return (_tree.rbegin());};
		reverse_iterator rend(void) {return (_tree.rend());};
		const_reverse_iterator rend(void) const {return (_tree.rend());};

		allocator_type get_allocator(void) const {return (allocator_type(_tree.get_allocator()));};

		bool empty(void) const {return (_tree.empty());};
		size_type size(void) const {return (_tree.size());};
		size_type max_size(void) const {return (_tree.max_size());};
		mapped_type &operator[](const key_type& key) {return (_tree[key]);};
		mapped_type& at(const key_type& key) {return _tree.at(key);};
		const mapped_type& at(const key_type& key) const {return _tree.at(key);};

		ft::pair<iterator, bool> insert(const value_type& val) {return (_tree.insert(val));};
		iterator insert(iterator position, const value_type& val) {return (_tree.insert(position, val));};
		template<typename InputIterator>
		void insert(InputIterator first, InputIterator last) {_tree.insert(first, last);};

		void erase(iterator position) {_tree.erase(position);};
		size_type erase(const key_type& key) {return (_tree.erase(key));};
		void erase(iterator first, iterator last) {_tree.erase(first, last);};
		void clear(void) {_tree.clear();};

		void swap(map& other)
		{
			if (this == &other)
				return;
			_tree.swap(other._tree);
		};

		key_compare key_comp(void) const {return (_tree.key_comp());};
		value_compare value_comp(void) const {return (value_compare(key_compare()));};

		iterator find(const key_type& key) {return (_tree.find(key));};
		const_iterator find(const key_type& key) const {return (_tree.find(key));};
		size_type count(const key_type& key) const {return (_tree.count(key));};

		iterator lower_bound(const key_type& key) {return (_tree.lower_bound(key));};
		const_iterator lower_bound(const key_type& key) const {return (_tree.lower_bound(key));};
		iterator upper_bound(const key_type& key) {return (_tree.upper_bound(key));};
		const_iterator upper_bound(const key_type& key) const {return (_tree.upper_bound(key));};

		ft::pair<iterator, iterator> equal_range(const key_type& key) {return (_tree.equal_range(key));};
		ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {return (_tree.equal_range(key));};

	protected:
		ft::Tree<Key, T, key_compare, allocator_type>	_tree;
	};//map

	template<typename Key, typename T, typename Compare, typename Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		if (lhs.empty() && rhs.empty())
			return true;
		typename ft::map<Key, T, Compare, Alloc>::const_iterator first1 = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator first2 = rhs.begin();
		while (first1 != lhs.end())
		{
			if (first2 == rhs.end() || *first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return true;
	};
	template<typename Key, typename T, typename Compare, typename Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {return (!(lhs == rhs));};
	template<typename Key, typename T, typename Compare, typename Alloc>
	bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if ((lhs.empty() && !rhs.empty()))
			return true;
		if ((lhs.empty() && rhs.empty()))
			return false;
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};
	template<typename Key, typename T, typename Compare, typename Alloc>
	bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if ((!lhs.empty() && rhs.empty()))
			return true;
		if ((lhs.empty() && rhs.empty()))
			return false;
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	};
	template<typename Key, typename T, typename Compare, typename Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if ((lhs.empty() && !rhs.empty()))
			return true;
		return ( ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || lhs == rhs);
	};
	template<typename Key, typename T, typename Compare, typename Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if ((!lhs.empty() && rhs.empty()))
			return true;
		return ( ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()) || lhs == rhs);
	};
	template<typename Key, typename T, typename Compare, typename Alloc>
	void swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs) {lhs.swap(rhs);};
	//
	// template<typename Key, typename T, typename Compare, typename Alloc>
	// ft::pair<Key, T>&	ft::map<Key, T, Compare, Alloc>::iterator::operator*(void) {return *_current.data;};


} // namespace ft

#endif

// #pragma once
//
// #include "utils.hpp"
// // https://github.com/pmouhali/ft_containers/blob/main/map.hpp
// namespace ft
// {
//
// 	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > >
// 	class map
// 	{
// 	public:
// 		typedef  Key								key_type;
// 		typedef  T									mapped_type;
// 		typedef typename std::pair<key_type, mapped_type>	value_type;
// 	private:
// 		typedef enum		_node_color
// 		{
// 			black, red
// 		}t_color;
// 		class		node
// 		{
// 		public:
// 			value_type		data;
// 			node	*parent;
// 			node	*left;
// 			node	*right;
// 			t_color		color;
// 			node(void) : data(0), parent(0), left(0), right(0), color(red) {};
// 			node(const value_type &d) : data(d), parent(0), left(0), right(0), color(red) {};
// 			node(const node &n) : data(n.data), parent(0), left(0), right(0), color(red) {};
// 			~node()
// 			{
// 				parent = left = right = 0;
//
// 			};
// 			node& operator=(const node& other)
// 			{
// 				(void)other;
// 			};
// 			node* _next(node *n)
// 			{
// 				if (n->right)
// 					return _min(n->right);
// 				while (n->parent && n->parent->left != n)
// 					n = n->parent;
// 				return n->parent ? n->parent : n;
// 			};
// 			node* _prev(node *n)
// 			{
// 				if (n->left)
// 					return _max(n->left);
// 				while (n->parent && n->parent->right != n)
// 					n = n->parent;
// 				return n->parent ? n->parent : n;
// 			};
// 			node* operator++()
// 			{
//
// 				return _next(&(*this));
// 			};
// 			node* operator++(int)
// 			{
// 				node tmp = *this;
// 				++(*this);
// 				return tmp;
// 			};
// 			bool operator==(const bidirectional_iterator< T >& other) {return (_current == other._current);};
// 			bool operator!=(const bidirectional_iterator< T >& other) {return (_current != other._current);};
// 			reference operator*() const {return *_current;};
// 			pointer operator->() const {return &(operator*());};
// 			node& operator--()
// 			{
// 				--_current;
// 				return *this;
// 			};
// 			node operator--(int)
// 			{
// 				node tmp = *this;
// 				--(*this);
// 				return tmp;
// 			};
// 		private:
//
// 		};
//
// 	public:
// 		typedef typename Alloc::template rebind<node>::other	allocator_type;
// 		typedef Compare							key_compare;
// 		typedef typename allocator_type::size_type			size_type;
// 		typedef typename allocator_type::reference			reference;
// 		typedef typename allocator_type::const_reference	const_reference;
// 		typedef typename allocator_type::pointer			pointer;
// 		typedef typename allocator_type::const_pointer		const_pointer;
// 		typedef typename ft::bidirectional_iterator<value_type>				iterator;
// 		typedef typename ft::bidirectional_iterator<const value_type> 		const_iterator;
// 		typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
// 		typedef typename ft::reverse_iterator<const_iterator> 				const_reverse_iterator;
// 		typedef typename iterator_traits<iterator>::difference_type			difference_type;
//
// 	private:
//
// 		key_compare _comparator;
// 		allocator_type _allocator;
// 		// node *_nil;
// 		node *_root;
// 		// node *_left_most;
// 		// node *_right_most;
//
// 		// const std::string _range_err_message(size_type val) const
// 		// {
// 		// 	std::string message;
// 		// 	std::ostringstream out;
// 		// 	out << "map::_M_range_check: __n (which is " << val << ") >= this->size() (which is " << size() << ")";
// 		// 	message = out.str();
// 		// 	return message;
// 		// };
// 		node *_new_node(const value_type &ref)
// 		{
// 			node *ptr;
// 			_allocator.construct(ptr = _allocator.allocate(1), node(ref));
// 			ptr->parent = 0;
// 			ptr->left = 0;
// 			ptr->right = 0;
// 			return ptr;
// 		};
// 		node *_insert_(node *n, const value_type &data)
// 		{
// 			if (!n)
// 			{
// 				n = _new_node(data);
// 				// n->data = data;
// 				if (!_root)
// 				_root = n;
// 				return n;
// 			}
// 			if (data.first < n->data.first)
// 			{
// 				n->left = _insert_(n->left, data);
// 				n->left->parent = n;
// 			}
// 			else if (data.first > n->data.first)
// 			{
// 				n->right = _insert_(n->right, data);
// 				n->right->parent = n;
// 			}
// 			return n;
// 		};
// 		node *_insert(const value_type &data)
// 		{
// 			if (!_root)
// 			{
// 				_root = _new_node(data);
// 				// _root->data = data;
// 				return _root;
// 			}
// 			return _insert_(_root, data);
// 		};
//
// 		node *_min(node* n)
// 		{
// 			if (n == NULL)
// 				return NULL;
// 			else if (n->left == NULL)
// 				return n;
// 			else
// 				return _min(n->left);
// 		};
// 		node *_max(node* n)
// 		{
// 			if (n == NULL)
// 				return NULL;
// 			else if (n->right == NULL)
// 				return n;
// 			else
// 				return _max(n->right);
// 		};
// 		void _delete(node n)
// 		{
// 			if (!n)
// 				return ;
// 			if (!n->left && !n->right)
// 			{
// 				if (n->parent)
// 				{
// 					if (n->parent->left == n)
// 						n->parent->left = NULL;
// 					else
// 						n->parent->right = NULL;
// 				}
// 				_allocator.destroy(n);
// 				_allocator.deallocate(n, 1);
// 				n = NULL;
// 			}
// 			if ((n->left && !n->right) || (!n->left && n->right))
// 			{
// 				node *child = n->left ? n->left : n->right;
// 				if (n->parent)
// 				{
// 					if (n->parent->left == n)
// 						n->parent->left = child;
// 					else
// 						n->parent->right = child;
// 					child->parent = n->parent;
// 				}
// 				_allocator.destroy(n);
// 				_allocator.deallocate(n, 1);
// 				n = NULL;
// 			}
// 			else
// 			{
// 				node *successor = _min(n->right);
// 				successor->left = n->left;
// 				successor->parent = n->parent;
// 				if (n->parent && n->parent->left == n)
// 					n->parent->left = successor;
// 				if (n->parent && n->parent->right == n)
// 					n->parent->right = successor;
// 				_allocator.destroy(n);
// 				_allocator.deallocate(n, 1);
// 				n = successor;
// 			}
// 		};
// 		void _delete(key_type &key)
// 		{
// 			node *n = _search(key, _root);
// 			if (!n)
// 				return ;
// 			_delete(n);
// 		};
// 		node *_search(key_type &key, node *n)
// 		{
// 			if (!n || (!_comparator(key, n->data.first) && !_comparator(n->data.first, key)))
// 				return n;
// 			if (_comparator(key, n->data.first))
// 				return _search(key, n->left);
// 			return _search(key, n->right);
// 		};
// 		void _print_inorder(node *n)
// 		{
// 			if (!n)
// 				return ;
// 			_print_inorder(n->left);
// 			std::cout << n->data.first << ": " << n->data.second << std::endl;
// 			_print_inorder(n->right);
// 		};
// 		size_type _size(node *n) const
// 		{
// 			if (!n)
// 				return 0;
// 			return 1 + _size(n->left) + _size(n->right);
// 		};
//
// 		void _delete_all(node *n) //must pass _root as it recursively erase all nodes
// 		{
// 			if (!n)
// 				return ;
// 			_delete_all(n->left);
// 			_delete_all(n->right);
// 			_allocator.destroy(n);
// 			_allocator.deallocate(n, 1);
// 			n = 0;
// 		};
// 		node *_deep_copy(node *n, node *parent)
// 		{
// 			if (!n)
// 				return n;
// 			node* copy = _new_node(n->data);
// 			copy->parent = parent;
// 			copy->left = _deep_copy(n->left, copy);
// 			copy->right = _deep_copy(n->right, copy);
// 			return copy;
// 		};
// 	public:
// 		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
// 		_comparator(comp), _allocator(alloc), _root(0) {};
// 		// template <class InputIterator>
// 		// map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
// 		map(const map& x) : _root(_deep_copy(x._root, NULL)) {};
//
// 		map& operator=(const map& other)
// 		{
// 			if ((*this)._root == other._root)
// 				return *this;
// 			clear();
// 			_root = _deep_copy(other._root, NULL);
// 			return *this;
// 		};
//
// 		~map()
// 		{
// 			_delete_all(_root);
// 		};
// 		void print()
// 		{
// 			_print_inorder(_root);
// 		};
// 		void clear()
// 		{
// 			_delete_all(_root);
// 			_root = 0;
// 		};
// 		size_type size(void) const
// 		{
// 			return _size(_root);
// 		};
// 		size_type count(const Key& key) const
// 		{
// 			if (!_root)
// 				return 0;
// 			return _search(key, _root) ? 1 : 0;
// 		};
// 		iterator find(const Key& key)
// 		{
// 			return _search(key, _root);
// 		};
// 		const_iterator find(const Key& key) const
// 		{
// 			return _search(key, _root);
// 		};
// 		// iterator begin() {return iterator(_data_start);};
// 		// const_iterator begin() const {return iterator(_data_start);};
// 		// iterator end() {return iterator(_data_end);};
// 		// const_iterator end() const {return iterator(_data_end);};
// 		// reverse_iterator rend() {return reverse_iterator(_data_start);};
// 		// const_reverse_iterator rend() const {return const_reverse_iterator(_data_start);};
// 		// reverse_iterator rbegin() {return reverse_iterator(_data_end);};
// 		// const_reverse_iterator rbegin() const {return const_reverse_iterator(_data_end);};
//
// 		// bool empty() const {return !(_data_end - _data_start);};
// 		// size_type size() const {return _data_end - _data_start;};
// 		size_type max_size(void) const {return allocator_type().max_size();};
//
// 		// // Capacity is not changed.
//
//
// 		// iterator erase(iterator pos)
// 		// {
// 		// 	if (&(*pos) == _data_end || _data_start == _data_end)
// 		// 		return end();
// 		// 	_alloc.destroy(&(*pos));
// 		// 	iterator ret = pos++;
// 		// 	while (&(*pos) != _data_end)
// 		// 	{
// 		// 		std::uninitialized_copy(&(*pos), &(*(pos+1)), &(*(pos-1)));
// 		// 		_alloc.destroy(&(*pos));
// 		// 		pos++;
// 		// 	}
// 		// 	_data_end = &(*(pos-1));
// 		// 	return ret;
// 		// };
// 		//
// 		// iterator erase(iterator first, iterator last)
// 		// {
// 		// 	iterator pos = first;
// 		// 	std::ptrdiff_t distance = last - first;
// 		// 	while (pos < last)
// 		// 	{
// 		// 		_alloc.destroy(&(*pos));
// 		// 		pos++;
// 		// 	}
// 		// 	while (&(*pos) < _data_end)
// 		// 	{
// 		// 		std::uninitialized_copy(pos, pos+1, pos - distance);
// 		// 		_alloc.destroy(&(*pos));
// 		// 		pos++;
// 		// 	}
// 		// 	_data_end = &(*(pos - distance));
// 		// 	return first;
// 		// };
// 		//
// 		void insert(const value_type &value)
// 		{
// 			// (void)pos;
// 			_insert_(_root, value);
// 		};
// 		//
// 		// void insert(iterator pos, size_type count, const value_type& value)
// 		// {
// 		// 	if (count && !empty() && size() + count <= capacity()) // if the container has enough space for insertion
// 		// 	{
// 		// 		iterator end = _data_end;
// 		// 		while (end-- >= pos) // make place
// 		// 		{
// 		// 			std::uninitialized_fill_n(&(*(end + count)), 1, *end);
// 		// 			_alloc.destroy(&(*end));
// 		// 		}
// 		// 		std::uninitialized_fill_n(&(*pos) , count, value);
// 		// 		_data_end += count;
// 		// 	}
// 		// 	else if (count && !empty() && size() + count > capacity()) // if it doesnt but not emppty
// 		// 	{
// 		// 		const size_type total_size = ((count + size() > size() * 2) ? count + size() : size() * 2);
// 		// 		pointer new_data_start = _alloc.allocate(total_size);
// 		// 		pointer new_data_end = std::uninitialized_copy(begin(), pos, new_data_start) + count;
// 		// 		std::uninitialized_fill_n(new_data_start + (&(*pos) - _data_start), count, value);
// 		// 		new_data_end = std::uninitialized_copy(&(*pos), _data_end, new_data_end);
// 		// 		_delete();
// 		// 		_data_start = new_data_start;
// 		// 		_data_end = new_data_end;
// 		// 		_data_max = new_data_start + total_size;
// 		// 	}
// 		// 	else if (count && empty())
// 		// 	{
// 		// 		(void)pos;
// 		// 		if (count > capacity())
// 		// 			reserve(count);
// 		// 		std::uninitialized_fill_n(_data_start, count, value);
// 		// 		_data_end = _data_start + count;
// 		// 	}
// 		// };
// 		//
// 		// template<class InputIterator>
// 		// void insert(iterator pos, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
// 		// {
// 		// 	const size_type count = _distance(first, last);
// 		// 	if (count && !empty() && size() + count <= capacity()) // if the container has enough space for insertion
// 		// 	{
// 		// 		pointer end = _data_end;
// 		// 		while (end-- >= &(*pos)) // make place
// 		// 		{
// 		// 			std::uninitialized_fill_n((end + count), 1, *end);
// 		// 			_alloc.destroy(end);
// 		// 		}
// 		// 		std::uninitialized_copy(first , last, pos);
// 		// 		_data_end += count;
// 		// 	}
// 		// 	else if (count && !empty() && size() + count > capacity())
// 		// 	{
// 		// 		const size_type total_size = ((count + size() > size() * 2) ? count + size() : size() * 2);
// 		// 		pointer new_data_start = _alloc.allocate(total_size);
// 		// 		pointer new_data_end = std::uninitialized_copy(begin(), pos, new_data_start) + count;
// 		// 		std::uninitialized_copy(first , last, new_data_start + (&(*pos) - _data_start));
// 		// 		new_data_end = std::uninitialized_copy(&(*pos), _data_end, new_data_end);
// 		// 		_delete();
// 		// 		_data_start = new_data_start;
// 		// 		_data_end = new_data_end;
// 		// 		_data_max = new_data_start + total_size;
// 		// 	}
// 		// 	else if (count && empty())
// 		// 	{
// 		// 		if (count > capacity())
// 		// 			reserve(count);
// 		// 		std::uninitialized_copy(first, last, _data_start);
// 		// 		_data_end = _data_start + count;
// 		// 	}
// 		// };
// 		//
// 		// reference operator[](size_type i) {return _data_start[i];};
// 		// const_reference operator[](size_type i) const {return _data_start[i];};
// 		// reference front() { return (*_data_start); };
// 		// const_reference front() const { return (*_data_start); };
// 		// reference back() { return (*(_data_end - 1)); };
// 		// const_reference back() const { return (*(_data_end - 1)); };
// 		//
// 		// reference at(size_type i)
// 		// {
// 		// 	if (i >= static_cast<size_type>(_data_end - _data_start))
// 		// 		throw std::out_of_range(_range_err_message(i));
// 		// 	return _data_start[i];
// 		// };
// 		// const_reference at(size_type i) const
// 		// {
// 		// 	if (i >= static_cast<size_type>(_data_end - _data_start))
// 		// 		throw std::out_of_range(_range_err_message(i));
// 		// 	return _data_start[i];
// 		// };
// 		// allocator_type get_allocator() const
// 		// {
// 		// 	return allocator_type();
// 		// };
// 		// void swap(map &other)
// 		// {
// 		// 	ft::swap(_allocator, other._allocator);
// 		// 	ft::swap(_comparator, other._comparator);
// 		// 	ft::swap(_root, other._root);
// 		// 	ft::swap(_nil, other._nil);
// 		// 	ft::swap(_left_most, other._left_most);
// 		// 	ft::swap(_right_most, other._right_most);
// 		// };
// 		//
// 		// size_type count(const Key& key) const;
// 		// iterator find(const Key& key);
// 		//
// 		// const_iterator find(const Key& key) const;
// 		// iterator lower_bound(const Key& key);
// 		// const_iterator lower_bound(const Key& key) const;
// 		// iterator upper_bound(const Key& key);
// 		// const_iterator upper_bound(const Key& key) const;
// 	};
//
// // template <class T, class Alloc>
// // bool operator== (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
// // {
// // 	if (lhs.size() != rhs.size())
// // 	return (false);
// // 	typename ft::map<T>::const_iterator first1 = lhs.begin();
// // 	typename ft::map<T>::const_iterator first2 = rhs.begin();
// // 	while (first1 != lhs.end())
// // 	{
// // 		if (first2 == rhs.end() || *first1 != *first2)
// // 			return (false);
// // 		++first1;
// // 		++first2;
// // 	}
// // 	return (true);
// // };
// //
// // template <class T, class Alloc>
// // bool operator!= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
// // {
// // 	return (!(lhs == rhs));
// // };
// //
// // template <class T, class Alloc>
// // bool operator<  (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
// // {
// // 	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
// // };
// //
// // template <class T, class Alloc>
// // bool operator<= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
// // {
// // 	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || std::equal(lhs.begin(), lhs.end(), rhs.begin()));
// // };
// //
// // template <class T, class Alloc>
// // bool operator>  (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
// // {
// // 	return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
// // };
// //
// // template <class T, class Alloc>
// // bool operator>= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
// // {
// // 	return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()) || std::equal(rhs.begin(), rhs.end(), lhs.begin()));
// // };
// //
// //
// // template <class T, class Alloc>
// // void swap (map<T,Alloc> &x, map<T,Alloc> &y)
// // {
// // 	x.swap(y);
// // };
// };
