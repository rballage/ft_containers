#ifndef _TREE_SET_HPP
# define _TREE_SET_HPP

# include "utils.hpp"
# include "_tree_iterators.hpp"

namespace ft
{
	template<typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
	class TreeSet
	{
	private:
		enum color
		{
			BLACK,
			RED
		};

		template<typename TYPE>
		class node
		{
		public:
			typedef TYPE	value_type;
			node*		parent;
			node*		left;
			node*		right;
			color		color;
			value_type	data;
			node(value_type content) : data(content) {};
			~node(void) {};
		};

		typedef node<const T>													t_node; //might need to change that
	public:
		typedef const T																	key_type;
		typedef const T																	mapped_type;
		typedef Compare																key_compare;
		typedef typename node<const T>::value_type															value_type;
		typedef typename  ft::tree_iterator<t_node>									iterator;
		typedef typename  ft::const_tree_iterator< t_node >							const_iterator; // need const expr ?
		typedef typename ft::reverse_iterator<iterator>										reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>								const_reverse_iterator;
		typedef t_node*																pointer;
		typedef const t_node*														const_pointer;
		typedef t_node&																reference;
		typedef const t_node&														const_reference;
		typedef typename Alloc::template rebind<t_node>::other	allocator_type;
		typedef typename allocator_type::size_type										size_type;

		explicit TreeSet(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			:  _alloc(alloc), _compare(comp), _size(0)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, t_node(value_type()));
			_root = _end;
			_end->color = BLACK;
		};

		template<typename InputIterator>
		TreeSet(InputIterator first, InputIterator last, key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type(),
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
				:  _alloc(alloc), _compare(comp), _size(0)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, t_node(value_type()));
			_end->color = BLACK;
			_root = _end;
			insert(first, last);
		};

		TreeSet(const TreeSet& src)
			:  _alloc(src._alloc), _compare(src._compare), _size(src.size())
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, t_node(value_type()));
			_end->color = BLACK;
			_root = _end;
			// *this = src;
			if (!src.empty())
				insert(src.begin(), src.end());
			_size = src.size();
		};

		virtual	~TreeSet(void)
		{
			if (!empty())
				clear();
			_alloc.destroy(_end);
			_alloc.deallocate(_end, 1);
		};

		TreeSet&	operator=(TreeSet const &rhs)
		{
			if (this != &rhs)
			{
				clear();
				_alloc.destroy(_end);
				_alloc.deallocate(_end, 1);
				_alloc = rhs._alloc;
				_compare = rhs._compare;
				_end = _alloc.allocate(1);
				_alloc.construct(_end, t_node(value_type()));
				_end->color = BLACK;
				_root = _end;
				if (!rhs.empty())
					insert(rhs.begin(), rhs.end());
				_size = rhs.size();
			}
			return *this;
		};

		iterator				begin(void) {return (iterator(_min(_root), _root, _end));};
		const_iterator			begin(void) const {return (const_iterator(_min(_root), _root, _end));};
		iterator				end(void) {return (iterator(_end, _root, _end));};
		const_iterator			end(void) const {return (const_iterator(_end, _root, _end));};
		reverse_iterator		rbegin(void) {return (reverse_iterator(end()));};
		const_reverse_iterator	rbegin() const {return (const_reverse_iterator(end()));};
		reverse_iterator		rend(void) {return (reverse_iterator(begin()));};
		const_reverse_iterator	rend(void) const {return (const_reverse_iterator(begin()));};
		size_type				size(void) const {return _size;};
		size_type				max_size(void) const {return _alloc.max_size();};
		Alloc					get_allocator(void) const {return (Alloc(_alloc));}; // returns the original allocator<ft::pair>
		bool					empty(void) const {return (_root == _end) ? true : false;};

		ft::pair<iterator, bool>	insert(const value_type& val)
		{
			iterator it = find(val);

			if (it != end())
				return ft::make_pair(it, false);
			pointer node = _alloc.allocate(1);
			_alloc.construct(node, t_node(val));
			pointer new_node = _insert(node, _root);
			it = iterator(new_node, _root, _end);
			_size++;
			return ft::make_pair(it, true);
		};

		iterator	insert(iterator pos, const T& val)
		{
			iterator pos2 = pos;
			pointer succ = (++pos2).base();

			if (_compare(pos.base()->data, val) && _compare(val, succ->data))
			{
				pointer node = _alloc.allocate(1);
				_alloc.construct(node, t_node(val));
				pointer new_node = _insert(node, pos.base());
				_size++;
				return iterator(new_node, _root, _end);
			}
			else
				return insert(val).first;
		};

		template<typename InputIterator>
		void	insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			while (first != last)
				insert(*first++);
		};

		void	erase(iterator pos)
		{
			if (_root == _end || pos == end())
			{
				(void)pos;
				return;
			}
			_delete_node(pos.base());
			_size--;
		};

		size_type	erase(const key_type& key)
		{
			if (_root == _end)
			{
				(void)key;
				return 0;
			}
			iterator it = find(key);
			if (it == end())
				return (0);
			erase(it);
			return (1);
		};

		void	erase(iterator first, iterator last)
		{
			if (_root == _end || first == last)
			{
				(void)first;
				(void)last;
				return;
			}
			while (first != last)
				erase(first++);
		};

		void	clear(void) {
			if (!_size)
				return;
			_clear(_root);
			_root = _end;
		};
		key_compare	key_comp(void) const {return key_compare();};
		iterator	find(const key_type& key) {return iterator(_find(key, _root));};
		const_iterator	find(const key_type& key) const {return const_iterator(_find(key, _root));};
		size_type	count(const key_type& key) const {return (find(key) != end()) ? 1 : 0;};

		iterator	lower_bound(const key_type& key)
		{
			iterator last = end();
			for (iterator it = begin(); it != last; it++)
				if (!(_compare(*it, key)))
					return it;
			return (last);
		};

		const_iterator	lower_bound(const key_type& key) const
		{
			const_iterator last = end();
			for (const_iterator it = begin(); it != last; it++)
				if (!(_compare(*it, key)))
					return it;
			return (last);
		};

		iterator	upper_bound(const key_type& key)
		{
			iterator last = end();
			for (iterator it = begin(); it != last; it++)
				if (_compare(key, *it))
					return it;
			return (last);
		};

		const_iterator	upper_bound(const key_type& key) const
		{
			const_iterator last = end();
			for (const_iterator it = begin(); it != last; it++)
				if (_compare(key, *it))
					return it;
			return (last);
		};

		ft::pair<iterator,iterator>	equal_range(const key_type& key) {return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));};
		ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));};
		void swap(TreeSet& other)
		{
			pointer tmp_root, tmp_end;
			size_type tmp_size = _size;
			tmp_root = _root;
			tmp_end = _end;
			_root = other._root;
			_end = other._end;
			_size = other._size;
			 other._root = tmp_root;
			other._end = tmp_end;
			other._size = tmp_size;
		};


	private:

		t_node*			_root;
		t_node*			_end;
		allocator_type	_alloc;
		key_compare		_compare;
		size_type		_size;

		t_node*	_insert(t_node* new_node, t_node* from)
		{
			t_node* y = _end;
			t_node* x = from;

			while (x != _end)
			{
				y = x;
				if (_compare(new_node->data, x->data))
					x = x->left;
				else
					x = x->right;
			}
			new_node->parent = y;
			if (y == _end)
				_root = new_node;
			else if (_compare(new_node->data, y->data))
				y->left = new_node;
			else
				y->right = new_node;
			new_node->left = _end;
			new_node->right = _end;
			new_node->color = RED; // needs to be RED by default for the fix
			_insert_fix(new_node);
			return (new_node);
		};

		void	_insert_fix(t_node* node)
		{
			t_node* uncle;

			while (node->parent->color == RED)
			{
				if (node->parent == node->parent->parent->left)
				{
					uncle = node->parent->parent->right;
					if (uncle->color == RED)
					{
						node->parent->color = BLACK;
						uncle->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else if(node == node->parent->right)
					{
						node = node->parent;
						_rotate_left(node);
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						_rotate_right(node->parent->parent);
					}
					else
					{
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						_rotate_right(node->parent->parent);
					}
				}
				else
				{
					uncle = node->parent->parent->left;
					if (uncle->color == RED)
					{
						node->parent->color = BLACK;
						uncle->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else if(node == node->parent->left)
					{
						node = node->parent;
						_rotate_right(node);
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						_rotate_left(node->parent->parent);
					}
					else
					{
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						_rotate_left(node->parent->parent);
					}
				}
			}
			_root->color = BLACK;
		};

		void	_rotate_left(t_node* x)
		{
			t_node* y = x->right;

			x->right = y->left;
			if (y->left != _end)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == _end)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		};

		void	_rotate_right(t_node* y)
		{
			t_node* x = y->left;

			y->left = x->right;
			if (x->right != _end)
				x->right->parent = y;
			x->parent = y->parent;
			if (y->parent == _end)
				_root = x;
			else if (y == y->parent->left)
				y->parent->left = x;
			else
				y->parent->right = x;
			x->right = y;
			y->parent = x;
		};

		t_node*	_min(t_node* node)
		{
			if (empty())
				return _end;
			if (!node)
				return node;
			while (node->left != _end && node != _end)
				node = node->left;
			return node;
		};

		t_node*	_min(t_node* node) const
		{
			if (empty())
				return _end;
			if (!node)
				return node;
			while (node->left != _end)
				node = node->left;
			return node;
		};

		void _clear(t_node* node)
		{
			if (node == _end)
				return ;
			_clear(node->left);
			_clear(node->right);
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
			_size--;
		};

		iterator	_find(const key_type& key,  t_node* node) const
		{
			if (node == _end)
				return iterator(_end, _root, _end);
			else if (!_compare(node->data, key) && !_compare(key, node->data))
				return iterator(node, _root, _end);
			if (_compare(node->data, key))
				return _find(key, node->right);
			else
				return _find(key, node->left);
		};

		void	_delete_node(t_node* z)
		{
			t_node* x = 0;
			t_node* y = z;
			color y_orginal_color = y->color;

			if (z->left == _end)
			{
				x = z->right;
				_move_subtree(z, z->right);
			}
			else if (z->right == _end)
			{
				x = z->left;
				_move_subtree(z, z->left);
			}
			else
			{
				y = _min(z->right);
				y_orginal_color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					_move_subtree(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				_move_subtree(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			if (y_orginal_color == BLACK)
				_delete_fix(x);
			_delete_one_node(z);
		};

		void	_delete_fix(t_node* x)
		{
			t_node* w;

			while (x != _root && x->color == BLACK)
			{
				if (x == x->parent->left) // if we're on the left
				{
					w = x->parent->right;
					if (w->color == RED) // case 1
					{
						w->color = BLACK;
						x->parent->color = RED;
						_rotate_left(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == BLACK && w->right->color == BLACK) // case 2
					{
						w->color = RED;
						x = x->parent;
					}
					else
					{
						if (w->right->color == BLACK) //case 3
						{
							w->left->color = BLACK;
							w->color = RED;
							_rotate_right(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->right->color = BLACK;
						_rotate_left(x->parent);
						x = _root;
					}
				}
				else// if we're on the right
				{
					w = x->parent->left;
					if (w->color == RED) //case 1
					{
						w->color = BLACK;
						x->parent->color = RED;
						_rotate_right(x->parent);
						w = x->parent->left;
					}
					if (w->right->color == BLACK && w->left->color == BLACK) //case 2
					{
						w->color = RED;
						x = x->parent;
					}
					else
					{
						if (w->left->color == BLACK)// case 3
						{
							w->right->color = BLACK;
							w->color = RED;
							_rotate_left(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->left->color = BLACK;
						_rotate_right(x->parent);
						x = _root;
					}
				}
			}
			x->color = BLACK;
		};

		void	_move_subtree(t_node* u, t_node* v)
		{
			if (u->parent == _end)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		};

		void	_delete_one_node(t_node* node)
		{
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
		};
	};
} // namespace ft
#endif
