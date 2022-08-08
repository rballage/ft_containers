

# include <memory>
# include "iterator_map.hpp"

namespace ft
{

	enum color_node_map
	{
		BLACK_MAP,
		RED_MAP
	};

	template<typename Key, typename T>
	struct rbt_node_map
	{
		typedef ft::pair<Key, T>	value_type;

		value_type			content;
		rbt_node_map*		parent;
		rbt_node_map*		left;
		rbt_node_map*		right;
		color_node_map		color;

		rbt_node_map( value_type content ) : content(content)
		{
			return ;
		}
	}; // struct rbt_node_map

	template<typename Key, typename T, typename Compare = ft::less<Key>,
		typename Alloc = std::allocator<ft::pair<const Key, T> > >
	class RBTreeMap
	{

	public:
		typedef Key										key_type;
		typedef T										mapped_type;
		typedef Compare									key_compare;
		typedef rbt_node_map<key_type, mapped_type>		node_type;
		typedef ft::RBTreeIterator<node_type>			iterator;
		typedef ft::RBTreeIterator<const node_type>		const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef node_type*								pointer;
		typedef const node_type*						const_pointer;
		typedef node_type&								reference;
		typedef const node_type&						const_reference;
		typedef ft::pair<const Key, T>					value_type;
		typedef typename Alloc::template rebind
			<rbt_node_map<key_type, mapped_type> >::other	allocator_type;
		typedef size_t									size_type;

		/*
		** Constructs an empty red_MAPblack_MAP tree, with no elements.
		*/

		explicit RBTreeMap( const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type() )
			: _root(0), _end(0), _alloc(alloc), _compare(comp), _size(0)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, node_type(value_type()));
			_end->color = BLACK_MAP;
			_root = _end;
		}

		/*
		** Constructs a red_MAPblack_MAP tree with as many elements as the range [first,last),
		** with each element constructed from its corresponding element in that range.
		*/

		template<typename InputIterator>
		RBTreeMap( InputIterator first, InputIterator last,
				key_compare const& comp = key_compare(),
				allocator_type const& alloc = allocator_type() )
				: _root(0), _end(0), _alloc(alloc),
				_compare(comp), _size(0)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, node_type(value_type()));
			_end->color = BLACK_MAP;
			_root = _end;
			insert(first, last);
		}

		/*
		** Constructs a red_MAPblack_MAP tree with a copy of each of the elements in src.
		*/

		RBTreeMap( const RBTreeMap& src )
			: _root(0), _end(0), _alloc(src._alloc),
			_compare(src._compare), _size(0)
		{
			_end = _alloc.allocate(1);
			_alloc.construct(_end, node_type(value_type()));
			_end->color = BLACK_MAP;
			_root = _end;
			*this = src;
		}

		/*
		** Destroys the tree object.
		*/

		virtual	~RBTreeMap( void )
		{
			clear();
			_alloc.destroy(_end);
			_alloc.deallocate(_end, 1);
		}

		/*
		** Assigns new contents to the tree, replacing its current content.
		*/

		RBTreeMap&	operator=( RBTreeMap const &rhs )
		{
			if (this != &rhs)
			{
				clear();
				_alloc = rhs._alloc;
				_compare = rhs._compare;
				insert(rhs.begin(), rhs.end());
			}
			return *this;
		}

		/*
		** Returns an iterator referring to the first element
		** in the tree. (miniumum value)
		*/

		iterator	begin( void)
		{
			return (iterator(_minimum(_root), _root, _end));
		}

		/*
		** Returns a const iterator referring to the first element
		** in the tree. (miniumum value)
		*/

		const_iterator	begin( void ) const
		{
			return (const_iterator(_minimum(_root), _root, _end));
		}

		/*
		** Returns an iterator referring to the past-the-end element
		** in the map container.
		*/

		iterator	end( void )
		{
			return (iterator(_end, _root, _end));
		}

		/*
		** Returns a const iterator referring to the past-the-end element
		** in the map container.
		*/

		const_iterator	end( void ) const
		{
			return (const_iterator(_end, _root, _end));
		}

		/*
		** Returns a reverse iterator pointing to the last element
		** in the container.
		*/

		reverse_iterator	rbegin( void )
		{
			return (reverse_iterator(end()));
		}

		/*
		** Returns a const reverse iterator pointing to the last element
		** in the container.
		*/

		const_reverse_iterator	rbegin() const
		{
			return (const_reverse_iterator(end()));
		}

		/*
		** Returns a reverse iterator pointing to the theoretical element
		** right before the first element in the map container.
		*/

		reverse_iterator	rend( void )
		{
			return (reverse_iterator(begin()));
		}

		/*
		** Returns a const reverse iterator pointing to the theoretical element
		** right before the first element in the map container.
		*/

		const_reverse_iterator	rend( void ) const
		{
			return (const_reverse_iterator(begin()));
		}

		/*
		** Returns whether the map container is empty.
		*/

		bool	empty( void ) const
		{
			if (_root == _end)
				return true;
			return false;
		}

		/*
		** Returns the number of elements in the map container.
		*/

		size_type	size( void ) const
		{
			return _size;
		}

		/*
		** Returns the maximum number of elements
		** that the map container can hold.
		*/


		size_type	max_size( void ) const
		{
			return _alloc.max_size();
		}

		/*
		** If key matches the key of an element in the container,
		** the function returns a reference to its mapped value.
		** If key does not match the key of any element in the container,
		** the function inserts a new element with that key and returns
		** a reference to its mapped value.
		*/

		mapped_type&	operator[]( const key_type& key )
		{
			iterator it = _find(key, _root);

			if (it == end())
			{
				ft::pair<iterator, bool>	p;
				p = insert(ft::make_pair(key, mapped_type()));
				return p.first.get_node()->content.second;
			}
			return it.get_node()->content.second;
		}

		/*
		** Extends the container by inserting one single element,
		** effectively increasing the container size by one.
		*/

		ft::pair<iterator, bool>	insert( const value_type& val )
      	{
			iterator it = find(val.first);

			if (it != end())
				return ft::make_pair(it, false);
			pointer node = _alloc.allocate(1);
			_alloc.construct(node, node_type(val));
			pointer node_inserted = _insertNode(node, _root);
			it = iterator(node_inserted, _root, _end);
			_size++;
			return ft::make_pair(it, true);
		}

		/*
		** Extends the container by inserting one single element at a given
		** position, effectively increasing the container size by one.
		** Position is an hint for the position where
		** the element can be inserted.
		*/

		iterator	insert( iterator position, const value_type& val )
      	{
			pointer succ = position.successor(position.get_node());

			if (_compare(position->first, val.first) &&
				_compare(val.first, succ->content.first))
			{
				pointer node = _alloc.allocate(1);
				_alloc.construct(node, node_type(val));
				pointer node_inserted = _insertNode(node, position.get_node());
				_size++;
				return iterator(node_inserted, _root, _end);
			}
			else
				return insert(val).first;
		}

		/*
		** Extends the container by inserting new elements,
		** effectively increasing the container size by
		** the number of elements inserted.
		*/

		template<typename InputIterator>
		void	insert( InputIterator first, InputIterator last )
		{
			while (first != last)
				insert(*first++);
		}

		/*
		** Removes from the map container a single element at a given position.
		** This effectively red_MAPuces the container size by the number
		** of elements removed, which are destroyed.
		*/

		void	erase( iterator position )
		{
			if (position == end())
				return;
			_eraseNode(position.get_node());
			_size--;
		}

		/*
		** Removes from the map container a single element
		** whose match with a given key.
		** This effectively red_MAPuces the container size by the number
		** of elements removed, which are destroyed.
		*/

		size_type	erase( const key_type& key )
		{
			iterator it = find(key);
			if (it == end())
				return (0);
			erase(it);
			return (1);
		}

		/*
		** Removes from the map container a range of elements.
		** This effectively red_MAPuces the container size by the number
		** of elements removed, which are destroyed.
		*/

		void	erase( iterator first, iterator last )
		{
			while (first != last)
				erase(first++);
		}

		/*
		** Removes all elements from the map container (which are destroyed),
		** leaving the container with a size of 0.
		*/

		void	clear( void )
		{
			_clear(_root);
			_root = _end;
		}

		/*
		** Returns a copy of the comparison object used
		** by the container to compare keys.
		*/

		key_compare	key_comp( void ) const
		{
			return key_compare();
		}

		/*
		** Searches the container for an element with a key equivalent to k
		** and returns an iterator to it if found,
		** otherwise it returns an iterator to map::end.
		*/

		iterator	find( const key_type& key )
		{
			iterator it = _find(key, _root);

			return it;
		}

		/*
		** Searches the container for an element with a key equivalent to k
		** and returns a constiterator to it if found,
		** otherwise it returns an iterator to map::end.
		*/

		const_iterator	find( const key_type& key ) const
		{
			const_iterator it = _find(key, _root);

			return it;
		}

		/*
		** Searches the container for elements with a key equivalent to k
		** and returns the number of matches.
		** 0 or 1 in the case of map.
		*/

		size_type	count( const key_type& key ) const
		{
			if (find(key) != end())
				return (1);
			return (0);
		}

		/*
		** Returns an iterator pointing to the first element
		** in the container whose key is not considered_MAP to go before key.
		*/

		iterator	lower_bound( const key_type& key )
		{
			for (iterator it = begin(); it != end(); it++)
			{
				if (!(_compare(it.get_node()->content.first, key)))
					return it;
			}
			return (end());
		}

		/*
		** Returns a const iterator pointing to the first element
		** in the container whose key is not considered_MAP to go before key.
		*/

		const_iterator	lower_bound( const key_type& key ) const
		{
			for (const_iterator it = begin(); it != end(); it++)
			{
				if (!(_compare(it.get_node()->content.first, key)))
					return it;
			}
			return (end());
		}

		/*
		** Returns an iterator pointing to the first element
		** in the container whose key is considered_MAP to go after key.
		*/

		iterator	upper_bound( const key_type& key )
		{
			for (iterator it = begin(); it != end(); it++)
			{
				if (_compare(key, it.get_node()->content.first))
					return it;
			}
			return (end());
		}

		/*
		** Returns a const iterator pointing to the first element
		** in the container whose key is considered_MAP to go after key.
		*/

		const_iterator	upper_bound( const key_type& key ) const
		{
			for (const_iterator it = begin(); it != end(); it++)
			{
				if (_compare(key, it.get_node()->content.first))
					return it;
			}
			return (end());
		}

		/*
		** Returns the bounds of a rang of iterators that includes all
		** the elements in the container which have a key equivalent to key.
		*/

		ft::pair<iterator,iterator>	equal_range( const key_type& key )
		{
			return ft::pair<iterator, iterator>(lower_bound(key),
				upper_bound(key));
		}

		/*
		** Returns the bounds of a rang of const iterators that includes all
		** the elements in the container which have a key equivalent to key.
		*/

		ft::pair<const_iterator, const_iterator>
			equal_range( const key_type& key ) const
		{
			return ft::pair<const_iterator, const_iterator>(lower_bound(key),
				upper_bound(key));
		}

		/*
		** Returns a copy of the allocator object associated with the map.
		*/

		Alloc	get_allocator( void ) const
		{
			return (Alloc(_alloc));
		}

	private:

		pointer			_root;
		pointer			_end;
		allocator_type	_alloc;
		key_compare		_compare;
		size_type		_size;

		/*
		** Inserts a new node at the right position in a leaf starting from
		** the pointer "from".
		** Then call insertFixUp in order to recolor and/or rotate nodes
		** to guarantee that the red_MAP-black_MAP properties are preserved.
		*/

		pointer	_insertNode( pointer new_node, pointer from )
		{
			pointer y = _end;
			pointer x = from;

			while (x != _end)
			{
				y = x;
				if (_compare(new_node->content.first, x->content.first))
					x = x->left;
				else
					x = x->right;
			}
			new_node->parent = y;
			if (y == _end)
				_root = new_node;
			else if (_compare(new_node->content.first, y->content.first))
				y->left = new_node;
			else
				y->right = new_node;
			new_node->left = _end;
			new_node->right = _end;
			new_node->color = RED_MAP;
			_insertFixUp(new_node);
			return (new_node);
		}

		/*
		** If the parent of the new node inserted is black_MAP, we're all set.
		** Else and until, node'sp parent is red_MAP :
		** We need to know if node's parent is at the left or the right
		** to node's grandparent.
		**
		** CASE 1 : node's parent is a left leaf.
		** 3 cases are possible :
		** 	Case 1, node's uncle is red_MAP :
		** 		Recolor and and check with node = node's grandparent.
		** 	Case 2, node is a right leaf :
		**		Execute a left rotation, recolor and right rotation.
		** 	Case 3, node is a left leaf :
		**		Recolor and execute a right rotation.
		**
		** CASE 2 :node's parent is a right leaf.
		** 3 cases are possible :
		** 	Case 1, node's uncle is red_MAP :
		** 		Recolor and and check with node = node's grandparent.
		** 	Case 2, node is a left leaf :
		**		Execute a right rotation, recolor and left rotation.
		** 	Case 3, node is a right leaf :
		**		Recolor and execute a left rotation.
		*/

		void	_insertFixUp( pointer node )
		{
			pointer uncle;

			while (node->parent->color == RED_MAP)
			{
				if (node->parent == node->parent->parent->left)
				{
					uncle = node->parent->parent->right;
					if (uncle->color == RED_MAP)
					{
						node->parent->color = BLACK_MAP;
						uncle->color = BLACK_MAP;
						node->parent->parent->color = RED_MAP;
						node = node->parent->parent;
					}
					else if(node == node->parent->right)
					{
						node = node->parent;
						_left_rotate(node);
						node->parent->color = BLACK_MAP;
						node->parent->parent->color = RED_MAP;
						_right_rotate(node->parent->parent);
					}
					else
					{
						node->parent->color = BLACK_MAP;
						node->parent->parent->color = RED_MAP;
						_right_rotate(node->parent->parent);
					}
				}
				else
				{
					uncle = node->parent->parent->left;
					if (uncle->color == RED_MAP)
					{
						node->parent->color = BLACK_MAP;
						uncle->color = BLACK_MAP;
						node->parent->parent->color = RED_MAP;
						node = node->parent->parent;
					}
					else if(node == node->parent->left)
					{
						node = node->parent;
						_right_rotate(node);
						node->parent->color = BLACK_MAP;
						node->parent->parent->color = RED_MAP;
						_left_rotate(node->parent->parent);
					}
					else
					{
						node->parent->color = BLACK_MAP;
						node->parent->parent->color = RED_MAP;
						_left_rotate(node->parent->parent);
					}
				}
			}
			_root->color = BLACK_MAP;
		}

		/*
		** Rotate to the left making Y the new parent of X.
		**
		**		 |		<-----------      |
		**      (Y)	    left rotate	     (X)
		**	    /\                       /\
		**    (X) c                     a (Y)
		**    /\        right rotate       /\
		**   a  b       ----------->      b  c
		*/


		void	_left_rotate( pointer x )
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
		}

		/*
		** Rotate to the right making X the new parent of Y.
		**
		**		 |		<-----------      |
		**      (Y)	    left rotate	     (X)
		**	    /\                       /\
		**    (X) c                     a (Y)
		**    /\        right rotate       /\
		**   a  b       ----------->      b  c
		*/

		void	_right_rotate( pointer y )
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
		}

		/*
		** Returns the minimum value found in a leaf starting from node.
		*/

		pointer	_minimum( pointer node )
		{
			while (node->left != _end && node != _end)
				node = node->left;
			return node;
		}

		pointer	_minimum( pointer node ) const
		{
			while (node->left != _end)
				node = node->left;
			return node;
		}

		/*
		** Destroy all the node starting from node in a recursive way.
		*/

		void _clear( pointer node )
		{
			if (node == _end)
				return ;
			_clear(node->left);
			_clear(node->right);
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
			_size--;
		}

		/*
		** Returns an iterators corresponding to the key in a leaf
		** starting from node, in a recursive way.
		*/

		iterator	_find( const key_type& key, const pointer& node ) const
		{
			if (node == _end)
				return iterator(_end, _root, _end);
			else if (node->content.first == key )
				return iterator(node, _root, _end);
			if (_compare(node->content.first, key))
				return _find(key, node->right);
			else
				return _find(key, node->left);
		}

		/*
		** Because deleted a node is over complicated,
		** we instead swap the wanted deleted node with a nil node.
		** We keep track of the original color of z node to see if we need
		** to fix up the tree in order to guarantee that the red_MAP-black_MAP
		** properties are preserved.
		** 3 cases are possible :
		** Case 1 : node's left == end
		**	Replacement is the right node.
		** Case 2 : node's right == end
		** 	Replacement is the left node.
		** Case 3 : node's left and node's right != end
		** 	Replacement is the minimum value in node's right leaf
		*/

		void	_eraseNode( pointer z )
		{
			pointer x = 0;
			pointer y = z;
			color_node_map y_orginal_color = y->color;

			if (z->left == _end)
			{
				x = z->right;
				_transplant(z, z->right);
			}
			else if (z->right == _end)
			{
				x = z->left;
				_transplant(z, z->left);
			}
			else
			{
				y = _minimum(z->right);
				y_orginal_color = y->color;
				x = y->right;
				if (y->parent == z)
					x->parent = y;
				else
				{
					_transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				_transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			if (y_orginal_color == BLACK_MAP)
				_deleteFixUp(x);
			_destroyNode(z);
		}

		/*
		** Until x != root and x is black_MAP, we need to operate few operation in
		** order to restablish the red_MAP black_MAP properties.
		**
		** First, we need to know if node' is at the left or the right
		** to node's parent.
		**
		** CASE 1 : node's parent is a left leaf.
		** 4 cases are possible :
		** 	Case 1, node's uncle's right (w) is red_MAP :
		** 		Recolor node's uncle and node's parent and
		**      operate a left rotation.
		**		We transformed a case 1 in a case 2, 3 or 4.
		** 	Case 2, node’s sibling w is black_MAP,
		**	and both of w’s children are black_MAP :
		**		Simply recolor node's sibling ans set node to his parent.
		** 	Case 3, node’s sibling w is black_MAP, w’s left child is red_MAP,
		**	and w’s right child is black_MAP :
		**		Recolor w's left in black_MAP, w in red_MAP
		**		and execute a right rotation.
		**		We set w to node's parent's right.
		**		We now transform case 3 in case 4.
		**	Case 4, node’s sibling w is black_MAP, and w’s right child is red_MAP :
		**		We perform a recolor and a left rotation.
		**		Then we set node to root causes the loop to terminate
		**		when it reaches this condition.
		**
		** CASE 2 :node's parent is a right leaf.
		** 4 cases are possible :
		** 	Case 1, node's uncle's left (w) is red_MAP :
		** 		Recolor node's uncle and node's parent and
		**      operate a right rotation.
		**		We transformed a case 1 in a case 2, 3 or 4.
		** 	Case 2, node’s sibling w is black_MAP,
		**	and both of w’s children are black_MAP :
		**		Simply recolor node's sibling ans set node to his parent.
		** 	Case 3, node’s sibling w is black_MAP, w’s right child is red_MAP,
		**	and w’s left child is black_MAP :
		**		Recolor w's right in black_MAP, w in red_MAP
		**		and execute a left rotation.
		**		We set w to node's parent's left.
		**		We now transform case 3 in case 4.
		**	Case 4, node’s sibling w is black_MAP, and w’s left child is red_MAP :
		**		We perform a recolor and a right rotation.
		**		Then we set node to root causes the loop to terminate
		**		when it reaches this condition.
		*/

		void	_deleteFixUp( pointer x )
		{
			pointer w;

			while (x != _root && x->color == BLACK_MAP)
			{
				if (x == x->parent->left)
				{
					w = x->parent->right;
					if (w->color == RED_MAP)
					{
						w->color = BLACK_MAP;
						x->parent->color = RED_MAP;
						_left_rotate(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == BLACK_MAP && w->right->color == BLACK_MAP)
					{
						w->color = RED_MAP;
						x = x->parent;
					}
					else if (w->right->color == BLACK_MAP)
					{
						w->left->color = BLACK_MAP;
						w->color = RED_MAP;
						_right_rotate(w);
						w = x->parent->right;
						w->color = x->parent->color;
						x->parent->color = BLACK_MAP;
						w->right->color = BLACK_MAP;
						_left_rotate(x->parent);
						x = _root;
					}
					else
					{
						w->color = x->parent->color;
						x->parent->color = BLACK_MAP;
						w->right->color = BLACK_MAP;
						_left_rotate(x->parent);
						x = _root;
					}
				}
				else
				{
					w = x->parent->left;
					if (w->color == RED_MAP)
					{
						w->color = BLACK_MAP;
						x->parent->color = RED_MAP;
						_right_rotate(x->parent);
						w = x->parent->left;
					}
					if (w->right->color == BLACK_MAP && w->left->color == BLACK_MAP)
					{
						w->color = RED_MAP;
						x = x->parent;
					}
					else if (w->left->color == BLACK_MAP)
					{
						w->right->color = BLACK_MAP;
						w->color = RED_MAP;
						_left_rotate(w);
						w = x->parent->left;
						w->color = x->parent->color;
						x->parent->color = BLACK_MAP;
						w->left->color = BLACK_MAP;
						_right_rotate(x->parent);
						x = _root;
					}
					else
					{
						w->color = x->parent->color;
						x->parent->color = BLACK_MAP;
						w->left->color = BLACK_MAP;
						_right_rotate(x->parent);
						x = _root;
					}
				}
				x->color = BLACK_MAP;
			}
		}

		/*
		** Replaces one subtree as a child of its parent with another subtree.
		*/

		void	_transplant( pointer u, pointer v )
		{
			if (u->parent == _end)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		/*
		** Destroy a single node.
		*/

		void	_destroyNode( pointer node )
		{
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
		}

	};

} // namespace ft
