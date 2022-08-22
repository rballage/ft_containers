#ifndef _TREE_ITERATOR_HPP
# define _TREE_ITERATOR_HPP

namespace ft
{
	template <typename T>
	class tree_iterator;
	template <typename T>
	class tree_iterator_set;
	template <typename T>
	class const_tree_iterator;

	template <typename T>
	class tree_iterator : public ft::iterator< std::bidirectional_iterator_tag, T >
	{
	public:
		typedef typename T::value_type    value_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::pointer   pointer;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::reference reference;
	protected:
		T*	_current;
		T*	_root;
		T*	_end;
	public:
		friend class const_tree_iterator<T>;
		tree_iterator(void): _current(0), _root(0), _end(0) {};
		explicit tree_iterator(T* ptr, T* root, T* end) : _current(ptr), _root(root), _end(end) {};
		tree_iterator(const tree_iterator& src) : _current(src._current), _root(src._root), _end(src._end) {};
		// tree_iterator(const const_tree_iterator<T>& src) : _current(src._current), _root(src._root), _end(src._end) {};
		virtual ~tree_iterator(void) {};
		tree_iterator &operator=(const tree_iterator& rhs)
		{
			if (this != &rhs)
			{
				_current = rhs._current;
				_root = rhs._root;
				_end = rhs._end;
			}
			return *this;
		};
		bool operator==(const tree_iterator& rhs) const {return (_current == rhs._current);};
		bool operator!=(const tree_iterator& rhs) const {return (_current != rhs._current);};
		bool operator==(const ft::const_tree_iterator<T>& rhs) const {return (_current == rhs._current);};
		bool operator!=(const ft::const_tree_iterator<T>& rhs) const {return (_current != rhs._current);};
		tree_iterator& operator++(void)
		{
			if (_current != _end)
				_current = _get_successor(_current);
			return *this;
		};
		tree_iterator operator++(int)
		{
			tree_iterator tmp(*this);
			operator++();
			return tmp;
		};
		tree_iterator& operator--(void)
		{
			if (_current == _end)
				_current = _get_max(_root);
			else
				_current = _get_predecessor(_current);
			return *this;
		};
		tree_iterator operator--(int)
		{
			tree_iterator tmp(*this);
			operator--();
			return tmp;
		};
		value_type& operator*(void) const {return _current->data;};
		value_type* operator->(void) const {return &_current->data;};
		T * base() const {return (_current);}
	private:
		T* _get_max(T* node) const
		{
			while (node->right != _end)
				node = node->right;
			return node;
		};
		T* _get_min(T* node) const
		{
			while (node->left != _end)
				node = node->left;
			return node;
		};
		T* _get_predecessor(T* node) const
		{
			T* predecessor;

			if (node->left != _end)
				return _get_max(node->left);
			predecessor = node->parent;
			while (node->parent && node == predecessor->left)
			{
				node = predecessor;
				predecessor = predecessor->parent;
			}
			return predecessor;
		};
		T* _get_successor(T* node) const
		{
			T* successor;

			if (node == _end)
				return (_end);
			if (node->right != _end)
				return _get_min(node->right);
			successor = node->parent;
			while (node->parent != _end && node == successor->right)
			{
				node = successor;
				successor = successor->parent;
			}
			return successor;
		};
	};
	template <typename T>
	class tree_iterator_set : public ft::iterator< std::bidirectional_iterator_tag, T >
	{
	public:
		typedef typename T::value_type    value_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::pointer   pointer;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::reference reference;
	protected:
		T*	_current;
		T*	_root;
		T*	_end;
	public:
		friend class const_tree_iterator<T>;
		tree_iterator_set(void): _current(0), _root(0), _end(0) {};
		explicit tree_iterator_set(T* ptr, T* root, T* end) : _current(ptr), _root(root), _end(end) {};
		tree_iterator_set(const tree_iterator_set& src) : _current(src._current), _root(src._root), _end(src._end) {};
		tree_iterator_set(const const_tree_iterator<T>& src) : _current(src._current), _root(src._root), _end(src._end) {};
		virtual ~tree_iterator_set(void) {};
		tree_iterator_set &operator=(const tree_iterator_set& rhs)
		{
			if (this != &rhs)
			{
				_current = rhs._current;
				_root = rhs._root;
				_end = rhs._end;
			}
			return *this;
		};
		bool operator==(const tree_iterator_set& rhs) const {return (_current == rhs._current);};
		bool operator!=(const tree_iterator_set& rhs) const {return (_current != rhs._current);};
		tree_iterator_set& operator++(void)
		{
			if (_current != _end)
				_current = _get_successor(_current);
			return *this;
		};
		tree_iterator_set operator++(int)
		{
			tree_iterator_set tmp(*this);
			operator++();
			return tmp;
		};
		tree_iterator_set& operator--(void)
		{
			if (_current == _end)
				_current = _get_max(_root);
			else
				_current = _get_predecessor(_current);
			return *this;
		};
		tree_iterator_set operator--(int)
		{
			tree_iterator_set tmp(*this);
			operator--();
			return tmp;
		};
		value_type& operator*(void) const {return _current->data;};
		value_type* operator->(void) const {return &_current->data;};
		T * base() const {return (_current);}
	private:
		T* _get_max(T* node) const
		{
			while (node->right != _end)
				node = node->right;
			return node;
		};
		T* _get_min(T* node) const
		{
			while (node->left != _end)
				node = node->left;
			return node;
		};
		T* _get_predecessor(T* node) const
		{
			T* predecessor;

			if (node->left != _end)
				return _get_max(node->left);
			predecessor = node->parent;
			while (node->parent && node == predecessor->left)
			{
				node = predecessor;
				predecessor = predecessor->parent;
			}
			return predecessor;
		};
		T* _get_successor(T* node) const
		{
			T* successor;

			if (node == _end)
				return (_end);
			if (node->right != _end)
				return _get_min(node->right);
			successor = node->parent;
			while (node->parent != _end && node == successor->right)
			{
				node = successor;
				successor = successor->parent;
			}
			return successor;
		};
	};
	template <typename T>
	class const_tree_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		typedef typename T::value_type    value_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, const value_type>::iterator_category iterator_category;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, const value_type>::difference_type   difference_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag,  const value_type>::pointer   pointer;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, const value_type>::reference reference;
	protected:
		T*	_current;
		T*	_root;
		T*	_end;
	public:
		friend class tree_iterator<T>;
		friend class tree_iterator_set<T>;
		const_tree_iterator(void): _current(0), _root(0), _end(0) {};
		explicit const_tree_iterator(T* ptr, T* root, T* end) : _current(ptr), _root(root), _end(end) {};
		const_tree_iterator(const const_tree_iterator& src) : _current(src._current), _root(src._root), _end(src._end) {};
		const_tree_iterator(const tree_iterator<T>& src) : _current(src._current), _root(src._root), _end(src._end) {};
		const_tree_iterator(const tree_iterator_set<T>& src) : _current(src._current), _root(src._root), _end(src._end) {};
		virtual ~const_tree_iterator(void) {};
		const_tree_iterator &operator=(const const_tree_iterator& rhs)
		{
			if (this != &rhs)
			{
				_current = rhs._current;
				_root = rhs._root;
				_end = rhs._end;
			}
			return *this;
		};
		const_tree_iterator &operator=(const tree_iterator<T>& rhs)
		{
			_current = rhs._current;
			_root = rhs._root;
			_end = rhs._end;
			return *this;
		};
		bool operator==(const const_tree_iterator& rhs) const {return (_current == rhs._current);};
		bool operator!=(const const_tree_iterator& rhs) const {return (_current != rhs._current);};
		const_tree_iterator& operator++(void)
		{
			if (_current != _end)
				_current = _get_successor(_current);
			return *this;
		};
		const_tree_iterator operator++(int)
		{
			const_tree_iterator tmp(*this);
			operator++();
			return tmp;
		};
		const_tree_iterator& operator--(void)
		{
			if (_current == _end)
				_current = _get_max(_root);
			else
				_current = _get_predecessor(_current);
			return *this;
		};
		const_tree_iterator operator--(int)
		{
			const_tree_iterator tmp(*this);
			operator--();
			return tmp;
		};
		const value_type& operator*(void) const {return _current->data;};
		const value_type* operator->(void) const {return &_current->data;};
		const T * base() const {return (_current);}
	private:
		T* _get_max(T* node) const
		{
			while (node->right != _end)
				node = node->right;
			return node;
		};
		T* _get_min(T* node) const
		{
			while (node->left != _end)
				node = node->left;
			return node;
		};
		T* _get_predecessor(T* node) const
		{
			T* predecessor;

			if (node->left != _end)
				return _get_max(node->left);
			predecessor = node->parent;
			while (node->parent && node == predecessor->left)
			{
				node = predecessor;
				predecessor = predecessor->parent;
			}
			return predecessor;
		};
		T* _get_successor(T* node) const
		{
			T* successor;

			if (node == _end)
				return (_end);
			if (node->right != _end)
				return _get_min(node->right);
			successor = node->parent;
			while (node->parent != _end && node == successor->right)
			{
				node = successor;
				successor = successor->parent;
			}
			return successor;
		};
	};
}

#endif
