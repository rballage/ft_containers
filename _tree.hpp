

# include <memory>
# include "iterator_map.hpp"

namespace ft
{
	template<typename Key, typename T, typename Compare = ft::less<Key>, typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class Tree
	{
		enum color
		{
			BLACK,
			RED
		};

		template<typename Key, typename T>
		class node
		{
			typedef ft::pair<Key, T>	value_type;

			node*		parent;
			node*		left;
			node*		right;
			color		color;
			value_type	data;
			node**					_end;
			node**					_root;

			node(value_type content, node* root, node* end) : data(content), _root(&root), _end(&end) {};

			node* operator++()
			{
				if (*this != *_end)
					*this = _successor(*this);
				return *this;
			};
			node* operator--()
			{
				if (*this == *_end)
					*this = _max(*_root);
				else
					*this = _predecessor(*this);
				return *this;
			};
			node* operator++(int)
			{
				node tmp = *this;
				++(*this);
				return tmp;
			};
			node* operator--(int)
			{
				node tmp = *this;
				--(*this);
				return tmp;
			};
		private:
			node* _max(node* n)
			{
				while (n->right != *_end)
					n = n->right;
				return n;
			};

			node* _min(node* n)
			{
				while (n->left != *_end && n != *_end)
					n = n->left;
				return n;
			};

			node* _predecessor(node* n)
			{
				node* predecessor;

				if (n->left != *_end)
					return _max(n->left);
				predecessor = n->parent;
				while (n->parent != 0 && n == predecessor->left)
				{
					n = predecessor;
					predecessor = predecessor->parent;
				}
				if (!predecessor)
					return *_end;
				else
					return predecessor;
			};

			node* _successor(node* n)
			{
				node* successor;

				if (n == *_end)
					return (*_end);
				if (n->right != *_end)
					return _get_min(n->right);
				successor = n->parent;
				while (n->parent != *_end && n == successor->right)
				{
					n = successor;
					successor = successor->parent;
				}
				if (!successor)
					return *_end;
				else
					return successor;
			};
		};
	public:
		typedef Key																		key_type;
		typedef T																		mapped_type;
		typedef Compare																	key_compare;
		typedef node<key_type, mapped_type>												node_type; //might need to change that
		typedef ft::bidirectional_iterator<node_type>									iterator;
		typedef ft::bidirectional_iterator<const node_type>								const_iterator;
		typedef ft::reverse_iterator<iterator>											reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>									const_reverse_iterator;
		typedef node_type*																pointer;
		typedef const node_type*														const_pointer;
		typedef node_type&																reference;
		typedef const node_type&														const_reference;
		typedef ft::pair<const Key, T>													value_type;
		typedef typename Alloc::template rebind<node<key_type, mapped_type> >::other	allocator_type;
		typedef typename allocator_type::size_type										size_type;

		explicit Tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _root(0), _end(0), _alloc(alloc), _compare(comp), _size(0)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, node_type(value_type()));
			_root = _end;
			_end->color = BLACK;
		};

		template<typename InputIterator>
		Tree(InputIterator first, InputIterator last, key_compare const& comp = key_compare(), allocator_type const& alloc = allocator_type(),
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
				: _root(0), _end(0), _alloc(alloc), _compare(comp), _size(0)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, node_type(value_type()));
			_end->color = BLACK;
			_root = _end;
			insert(first, last);
		};

		Tree(const Tree& src)
			: _root(0), _end(0), _alloc(src._alloc), _compare(src._compare), _size(0)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, node_type(value_type()));
			_end->color = BLACK;
			_root = _end;
			*this = src;
		};

		virtual	~Tree(void)
		{
			clear();
			_alloc.destroy(_end);
			_alloc.deallocate(_end, 1);
		};

		Tree&	operator=(Tree const &rhs)
		{
			if (this != &rhs)
			{
				clear();
				_alloc = rhs._alloc;
				_compare = rhs._compare;
				insert(rhs.begin(), rhs.end());
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

		mapped_type&	operator[](const key_type& key)
		{
			iterator it = _find(key, _root);

			if (it == end())
			{
				ft::pair<iterator, bool>	p;
				p = insert(ft::make_pair(key, mapped_type()));
				return p.first.base()->data.second;
			}
			return it.base()->data.second;
		};

		ft::pair<iterator, bool>	insert(const value_type& val)
		{
			iterator it = find(val.first);

			if (it != end())
				return ft::make_pair(it, false);
			pointer node = _alloc.allocate(1);
			_alloc.construct(node, node_type(val));
			pointer new_node = _insert(node, _root);
			it = iterator(new_node, _root, _end);
			_size++;
			return ft::make_pair(it, true);
		};

		iterator	insert(iterator pos, const value_type& val)
		{
			pointer succ = pos.successor(pos.base());

			if (_compare(pos->first, val.first) && _compare(val.first, succ->data.first))
			{
				pointer node = _alloc.allocate(1);
				_alloc.construct(node, node_type(val));
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
			if (pos == end())
				return;
			_delete_node(pos.base());
			_size--;
		};

		size_type	erase(const key_type& key)
		{
			iterator it = find(key);
			if (it == end())
				return (0);
			erase(it);
			return (1);
		};

		void	erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		};

		void	clear(void) {_clear(_root); _root = _end;};
		key_compare	key_comp(void) const {return key_compare();};
		iterator	find(const key_type& key) {return iterator(_find(key, _root));};
		const_iterator	find(const key_type& key) const {return const_iterator(_find(key, _root));};
		size_type	count(const key_type& key) const {return (find(key) != end()) ? 1 : 0;};

		iterator	lower_bound(const key_type& key)
		{
			for (iterator it = begin(); it != end(); it++)
				if (!(_compare(it.base()->data.first, key)))
					return it;
			return (end());
		};

		const_iterator	lower_bound(const key_type& key) const
		{
			for (const_iterator it = begin(); it != end(); it++)
				if (!(_compare(it.base()->data.first, key)))
					return it;
			return (end());
		};

		iterator	upper_bound(const key_type& key)
		{
			for (iterator it = begin(); it != end(); it++)
				if (_compare(key, it.base()->data.first))
					return it;
			return (end());
		};

		const_iterator	upper_bound(const key_type& key) const
		{
			for (const_iterator it = begin(); it != end(); it++)
				if (_compare(key, it.base()->data.first))
					return it;
			return (end());
		};

		ft::pair<iterator,iterator>	equal_range(const key_type& key) {return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));};
		ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {return ft::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));};

	private:

		pointer			_root;
		pointer			_end;
		allocator_type	_alloc;
		key_compare		_compare;
		size_type		_size;

		pointer	_insert(pointer new_node, pointer from)
		{
			pointer y = _end;
			pointer x = from;

			while (x != _end)
			{
				y = x;
				if (_compare(new_node->data.first, x->data.first))
					x = x->left;
				else
					x = x->right;
			}
			new_node->parent = y;
			if (y == _end)
				_root = new_node;
			else if (_compare(new_node->data.first, y->data.first))
				y->left = new_node;
			else
				y->right = new_node;
			new_node->left = _end;
			new_node->right = _end;
			new_node->color = RED; // needs to be RED by default for the fix
			_insert_fix(new_node);
			return (new_node);
		};

		void	_insert_fix(pointer node)
		{
			pointer uncle;

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

		void	_rotate_left(pointer x)
		{
			pointer y = x->right;

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

		void	_rotate_right(pointer y)
		{
			pointer x = y->left;

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

		pointer	_min(pointer node)
		{
			while (node->left != _end && node != _end)
				node = node->left;
			return node;
		};

		pointer	_min(pointer node) const
		{
			while (node->left != _end)
				node = node->left;
			return node;
		};

		void _clear(pointer node)
		{
			if (node == _end)
				return ;
			_clear(node->left);
			_clear(node->right);
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
			_size--;
		};

		iterator	_find(const key_type& key, const pointer& node) const
		{
			if (node == _end)
				return iterator(_end, _root, _end);
			else if (node->data.first == key)
				return iterator(node, _root, _end);
			if (_compare(node->data.first, key))
				return _find(key, node->right);
			else
				return _find(key, node->left);
		};

		void	_delete_node(pointer z)
		{
			pointer x = 0;
			pointer y = z;
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
			_delete_node(z);
		};

		void	_delete_fix(pointer x)
		{
			pointer w;

			while (x != _root && x->color == BLACK)
			{
				if (x == x->parent->left)
				{
					w = x->parent->right;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->parent->color = RED;
						_rotate_left(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == BLACK && w->right->color == BLACK)
					{
						w->color = RED;
						x = x->parent;
					}
					else if (w->right->color == BLACK)
					{
						w->left->color = BLACK;
						w->color = RED;
						_rotate_right(w);
						w = x->parent->right;
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->right->color = BLACK;
						_rotate_left(x->parent);
						x = _root;
					}
					else
					{
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->right->color = BLACK;
						_rotate_left(x->parent);
						x = _root;
					}
				}
				else
				{
					w = x->parent->left;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->parent->color = RED;
						_rotate_right(x->parent);
						w = x->parent->left;
					}
					if (w->right->color == BLACK && w->left->color == BLACK)
					{
						w->color = RED;
						x = x->parent;
					}
					else if (w->left->color == BLACK)
					{
						w->right->color = BLACK;
						w->color = RED;
						_rotate_left(w);
						w = x->parent->left;
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->left->color = BLACK;
						_rotate_right(x->parent);
						x = _root;
					}
					else
					{
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->left->color = BLACK;
						_rotate_right(x->parent);
						x = _root;
					}
				}
				x->color = BLACK;
			}
		};

		void	_move_subtree(pointer u, pointer v)
		{
			if (u->parent == _end)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		};

		void	_delete_node(pointer node)
		{
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
		};
	};
} // namespace ft

/*
** Until x != root and x is BLACK, we need to operate few operation in
** order to restablish the RED BLACK properties.
**
** First, we need to know if node' is at the left or the right
** to node's parent.
**
** CASE 1 : node's parent is a left leaf.
** 4 cases are possible :
** 	Case 1, node's uncle's right (w) is RED :
** 		Recolor node's uncle and node's parent and
**      operate a left rotation.
**		We transformed a case 1 in a case 2, 3 or 4.
** 	Case 2, node’s sibling w is BLACK,
**	and both of w’s children are BLACK :
**		Simply recolor node's sibling ans set node to his parent.
** 	Case 3, node’s sibling w is BLACK, w’s left child is RED,
**	and w’s right child is BLACK :
**		Recolor w's left in BLACK, w in RED
**		and execute a right rotation.
**		We set w to node's parent's right.
**		We now transform case 3 in case 4.
**	Case 4, node’s sibling w is BLACK, and w’s right child is RED :
**		We perform a recolor and a left rotation.
**		Then we set node to root causes the loop to terminate
**		when it reaches this condition.
**
** CASE 2 :node's parent is a right leaf.
** 4 cases are possible :
** 	Case 1, node's uncle's left (w) is RED :
** 		Recolor node's uncle and node's parent and
**      operate a right rotation.
**		We transformed a case 1 in a case 2, 3 or 4.
** 	Case 2, node’s sibling w is BLACK,
**	and both of w’s children are BLACK :
**		Simply recolor node's sibling ans set node to his parent.
** 	Case 3, node’s sibling w is BLACK, w’s right child is RED,
**	and w’s left child is BLACK :
**		Recolor w's right in BLACK, w in RED
**		and execute a left rotation.
**		We set w to node's parent's left.
**		We now transform case 3 in case 4.
**	Case 4, node’s sibling w is BLACK, and w’s left child is RED :
**		We perform a recolor and a right rotation.
**		Then we set node to root causes the loop to terminate
**		when it reaches this condition.
*/


		/*
		** If the parent of the new node inserted is BLACK, we're all set.
		** Else and until, node'sp parent is RED :
		** We need to know if node's parent is at the left or the right
		** to node's grandparent.
		**
		** CASE 1 : node's parent is a left leaf.
		** 3 cases are possible :
		** 	Case 1, node's uncle is RED :
		** 		Recolor and and check with node = node's grandparent.
		** 	Case 2, node is a right leaf :
		**		Execute a left rotation, recolor and right rotation.
		** 	Case 3, node is a left leaf :
		**		Recolor and execute a right rotation.
		**
		** CASE 2 :node's parent is a right leaf.
		** 3 cases are possible :
		** 	Case 1, node's uncle is RED :
		** 		Recolor and and check with node = node's grandparent.
		** 	Case 2, node is a left leaf :
		**		Execute a right rotation, recolor and left rotation.
		** 	Case 3, node is a right leaf :
		**		Recolor and execute a left rotation.
		*/
