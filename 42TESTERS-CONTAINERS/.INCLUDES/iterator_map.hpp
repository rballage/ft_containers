#ifndef ITERATOR_MAP_HPP
# define ITERATOR_MAP_HPP
# include "iterators.hpp"
# include "utils.hpp"

namespace ft
{

	template <typename T>
	class tree_iterator
	{

	public:
		typedef T										value_type;
		typedef typename T::value_type const			data_type;
		typedef data_type&								reference;
		typedef data_type const&						const_reference;
		typedef data_type*								pointer;
		typedef data_type const*						const_pointer;
		typedef typename std::ptrdiff_t					difference_type;
		typedef ft::bidirectional_iterator_tag			iterator_category;
	protected:
		value_type*	_current;
		value_type*	_root;
		value_type*	_end;
	public:
		tree_iterator(void): _current(0), _root(0), _end(0) {};
		explicit tree_iterator(value_type* ptr, value_type* root, value_type* end) : _current(ptr), _root(root), _end(end) {};
		tree_iterator(const tree_iterator& src) : _current(src._current), _root(src._root), _end(src._end) {};

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

		operator tree_iterator<value_type const>() const {return tree_iterator<value_type const>(_current, _root, _end);};

		bool operator==(const tree_iterator& rhs) const {return (_current == rhs._current);};
		bool operator!=(const tree_iterator& rhs) const {return (_current != rhs._current);};

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
		reference operator*(void){return _current->data;};
		const_reference operator*(void) const {return _current->data;};
		pointer operator->(void) {return &(operator*());};
		value_type* base(void) {return _current;};

		// value_type* successor(value_type* node) {return _get_successor(node);};

	private:
		value_type* _get_max(value_type* node)
		{
			while (node->right != _end)
				node = node->right;
			return node;
		};

		value_type* _get_min(value_type* node)
		{
			while (node->left != _end && node != _end)
				node = node->left;
			return node;
		};

		value_type* _get_predecessor(value_type* node)
		{
			value_type* predecessor;

			if (node->left != _end)
				return _get_max(node->left);
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
		};

		value_type* _get_successor(value_type* node)
		{
			value_type* successor;

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
			if (!successor)
				return _end;
			else
				return successor;
		};
	};

}

#endif
