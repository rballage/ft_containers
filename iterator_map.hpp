

namespace ft
{

	template <typename T>
	class RBTreeIterator
	{

	public:

		typedef T										value_type;
		typedef value_type*								node_pointer;
		typedef typename T::value_type const			data_type;
		typedef data_type&								reference;
		typedef data_type const&						const_reference;
		typedef data_type*								pointer;
		typedef data_type const*						const_pointer;
		typedef typename std::ptrdiff_t					difference_type;
		typedef ft::bidirectional_iterator_tag			iterator_category;

	public:

		/*
		** Empty Constructor (Default constructor)
		** Constructs an empty iterator, points to NULL.
		*/

		RBTreeIterator( void ): _ptr(0), _root(0), _end(0)
		{
			return ;
		};

		/*
		** Constructor one element
		** Constructs an iterator, points to ptr.
		*/

		explicit RBTreeIterator( node_pointer ptr, node_pointer root,
			node_pointer end )
			: _ptr(ptr), _root(root), _end(end)
		{
			return ;
		};

		/*
		** Copy constructor
		** Constructs an iterator with a copy of each of the elements in src.
		*/

		RBTreeIterator( const RBTreeIterator& src )
			: _ptr(src._ptr), _root(src._root), _end(src._end)
		{
			return ;
		};

		/*
		** Destructor
		*/

		virtual ~RBTreeIterator( void )
		{
			return ;
		}

		/*
		** Assign content
		** Copies all the elements from rhs into the iterator..
		*/

		RBTreeIterator &operator=( const RBTreeIterator& rhs )
		{
			if (this != &rhs)
			{
				_ptr = rhs._ptr;
				_root = rhs._root;
				_end = rhs._end;
			}
			return *this;
		}

		/*
		** Allow a conversion from iterator to const_iterator.
		*/

		operator RBTreeIterator<value_type const>() const
		{
			return RBTreeIterator<value_type const>(_ptr, _root, _end);
		}

		/*
		** Returns a reference to the content of the element
		** pointed to by the iterator.
		*/

		reference operator*( void )
		{
			return _ptr->content;
		}

		/*
		** Returns a const reference to the content of the element
		** pointed to by the iterator.
		*/

		const_reference operator*( void ) const
		{
			return _ptr->content;
		}

		/*
		** Returns a pointer to the element pointed to by the iterator.
		*/

		pointer operator->( void )
		{
			return &(operator*());
		}

		/*
		** Performs the comparison == operation between the
		** pointer of this and pointer of rhs.
		*/

		bool operator==( const RBTreeIterator& rhs ) const
		{
			return (_ptr == rhs._ptr);
		}

		/*
		** Performs the comparison != operation between the
		** pointer of this and pointer of rhs.
		*/

		bool operator!=( const RBTreeIterator& rhs ) const
		{
			return (_ptr != rhs._ptr);
		}

		/*
		** Pre increment version
		** Returns an interator to the successor of _ptr.
		** Changing where _ptr points to.
		*/

		RBTreeIterator& operator++( void )
		{
			if (_ptr != _end)
				_ptr = _get_successor(_ptr);

			return *this;
		}

		/*
		** Post increment version
		** Returns an interator to the successor of _ptr.
		** Changing where _ptr points to.
		*/

		RBTreeIterator operator++( int )
		{
			RBTreeIterator tmp(*this);
			operator++();
			return tmp;
		}

		/*
		** Pre decrement version
		** Returns an interator to the predecessor of _ptr.
		** Changing where _ptr points to.
		*/

		RBTreeIterator& operator--( void)
		{
			if (_ptr == _end)
				_ptr = _maximum(_root);
			else
				_ptr = _get_predecessor(_ptr);
			return *this;
		}

		/*
		** Post decrement version
		** Returns an interator to the predecessor of _ptr.
		** Changing where _ptr points to.
		*/

		RBTreeIterator operator--( int )
		{
			RBTreeIterator tmp(*this);
			operator--();
			return tmp;
		}

		/*
		** Returns the pointer whose the iterator points to.
		*/

		node_pointer get_node( void )
		{
			return _ptr;
		}

		/*
		** Returns the sucessor of node.
		*/

		node_pointer successor( node_pointer node )
		{
			return _get_successor(node);
		}

	private:

		/*
		** Returns the maximum value in a leaf starting from node.
		*/

		node_pointer _maximum( node_pointer node )
		{
			while (node->right != _end)
				node = node->right;
			return node;
		}

		/*
		** Returns the minimum value in a leaf starting from node.
		*/

		node_pointer _minimum( node_pointer node )
		{
			while (node->left != _end && node != _end)
				node = node->left;
			return node;
		}

		/*
		** Returns the predecessor value in a leaf starting from node.
		*/

		node_pointer _get_predecessor( node_pointer node )
		{
			node_pointer predecessor;

			if (node->left != _end)
				return _maximum(node->left);
			predecessor = node->parent;
			while (node->parent != 0 && node == predecessor->left)
			{
				node = predecessor;
				predecessor = predecessor->parent;
			}
			if (!predecessor)
				return _end;
			else
				return predecessor;
		}

		/*
		** Returns the successor value in a leaf starting from node.
		*/

		node_pointer _get_successor( node_pointer node )
		{
			node_pointer successor;

			if (node == _end)
				return (_end);
			if (node->right != _end)
				return _minimum(node->right);
			successor = node->parent;
			while (node->parent != _end && node == successor->right)
			{
				node = successor;
				successor = successor->parent;
			}
			if (!successor)
				return _end;
			else
				return successor;
		}

	protected:

		node_pointer	_ptr;
		node_pointer	_root;
		node_pointer	_end;

	}; // class RBTreeIterator

} // namespace ft

#endif
