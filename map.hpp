#pragma once

#include "utils.hpp"
// https://github.com/pmouhali/ft_containers/blob/main/map.hpp
namespace ft
{
	template <class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<pair<const Key,T> >
	class map
	{
	public:
		typedef typename Key								key_type;
		typedef typename T									mapped_type;
		typedef typename pair<const key_type, mapped_type>	value_type;
	private:
		typedef enum		_node_color
		{
			black, red;
		}					_color;
		typedef struct		_node
		{
			value_type		data;
			struct _node	*parent;
			struct _node	*left;
			struct _node	*right;
			enum _color		color;
		}					node;

	public:
		typedef typename Alloc::template rebind<node>::other	allocator_type;
		typedef typename Compare							key_compare;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename ft::bidirectional_iterator<value_type>				iterator;
		typedef typename ft::bidirectional_iterator<const value_type> 		const_iterator;
		typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> 				const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type			difference_type;

	private:

		allocator_type _allocator;
		key_compare _comparator;
		node *_nil;
		node *_root;
		// node *_left_most;
		// node *_right_most;

		const std::string _range_err_message(size_type val) const
		{
			std::string message;
			std::ostringstream out;
			out << "map::_M_range_check: __n (which is " << val << ") >= this->size() (which is " << size() << ")";
			message = out.str();
			return message;
		};
		node *_new_node(node *ref)
		{
			node *ptr;
			_allocator.construct(ptr = _allocator(1), *ref);
			*ptr = (const node)0;
			ptr->parent = _nil;
			ptr->left = _nil;
			ptr->right = _nil;
			return ptr;
		};
		void _insert(reference data)
		{
			if (!_root)
			{
				_root = _new_node(0);
				_root->data = data;
			}
			else
			{

			}
		};
		node *_search(key_type &key, node *n)
		{
			if (!n || !_comparator(key, n->data->key) && !_comparator(n->data->key, key))
				return n;
			if (_comparator(key, n->data->key))
				return _search(key, n->left);
			return _search(key, n->right);
		};
	public:
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
		_comparator(comp), _allocator(Alloc), _root(0){
			_nil = _new_node((const node)0);
		};
		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		map(const map& x);



		~map() {
			// _delete();
		};

		// iterator begin() {return iterator(_data_start);};
		// const_iterator begin() const {return iterator(_data_start);};
		// iterator end() {return iterator(_data_end);};
		// const_iterator end() const {return iterator(_data_end);};
		// reverse_iterator rend() {return reverse_iterator(_data_start);};
		// const_reverse_iterator rend() const {return const_reverse_iterator(_data_start);};
		// reverse_iterator rbegin() {return reverse_iterator(_data_end);};
		// const_reverse_iterator rbegin() const {return const_reverse_iterator(_data_end);};

		// bool empty() const {return !(_data_end - _data_start);};
		// size_type size() const {return _data_end - _data_start;};
		size_type max_size(void) const {return allocator_type().max_size();};

		// // Capacity is not changed.
		// void clear(void)
		// {
		// 	if (_data_start != _data_end)
		// 	{
		// 		pointer it = _data_end;
		// 		while (it != _data_start)
		// 			_alloc.destroy(--it);
		// 	}
		// 	_data_end = _data_start;
		// };
		//
		// iterator erase(iterator pos)
		// {
		// 	if (&(*pos) == _data_end || _data_start == _data_end)
		// 		return end();
		// 	_alloc.destroy(&(*pos));
		// 	iterator ret = pos++;
		// 	while (&(*pos) != _data_end)
		// 	{
		// 		std::uninitialized_copy(&(*pos), &(*(pos+1)), &(*(pos-1)));
		// 		_alloc.destroy(&(*pos));
		// 		pos++;
		// 	}
		// 	_data_end = &(*(pos-1));
		// 	return ret;
		// };
		//
		// iterator erase(iterator first, iterator last)
		// {
		// 	iterator pos = first;
		// 	std::ptrdiff_t distance = last - first;
		// 	while (pos < last)
		// 	{
		// 		_alloc.destroy(&(*pos));
		// 		pos++;
		// 	}
		// 	while (&(*pos) < _data_end)
		// 	{
		// 		std::uninitialized_copy(pos, pos+1, pos - distance);
		// 		_alloc.destroy(&(*pos));
		// 		pos++;
		// 	}
		// 	_data_end = &(*(pos - distance));
		// 	return first;
		// };
		//
		// iterator insert(iterator pos, const value_type& value)
		// {
		// 	const size_type distance = &(*pos) - _data_start; // necessary when reallocating is necessary
		// 	insert(pos, 1, value);
		// 	return _data_start + distance;
		// };
		//
		// void insert(iterator pos, size_type count, const value_type& value)
		// {
		// 	if (count && !empty() && size() + count <= capacity()) // if the container has enough space for insertion
		// 	{
		// 		iterator end = _data_end;
		// 		while (end-- >= pos) // make place
		// 		{
		// 			std::uninitialized_fill_n(&(*(end + count)), 1, *end);
		// 			_alloc.destroy(&(*end));
		// 		}
		// 		std::uninitialized_fill_n(&(*pos) , count, value);
		// 		_data_end += count;
		// 	}
		// 	else if (count && !empty() && size() + count > capacity()) // if it doesnt but not emppty
		// 	{
		// 		const size_type total_size = ((count + size() > size() * 2) ? count + size() : size() * 2);
		// 		pointer new_data_start = _alloc.allocate(total_size);
		// 		pointer new_data_end = std::uninitialized_copy(begin(), pos, new_data_start) + count;
		// 		std::uninitialized_fill_n(new_data_start + (&(*pos) - _data_start), count, value);
		// 		new_data_end = std::uninitialized_copy(&(*pos), _data_end, new_data_end);
		// 		_delete();
		// 		_data_start = new_data_start;
		// 		_data_end = new_data_end;
		// 		_data_max = new_data_start + total_size;
		// 	}
		// 	else if (count && empty())
		// 	{
		// 		(void)pos;
		// 		if (count > capacity())
		// 			reserve(count);
		// 		std::uninitialized_fill_n(_data_start, count, value);
		// 		_data_end = _data_start + count;
		// 	}
		// };
		//
		// template<class InputIterator>
		// void insert(iterator pos, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		// {
		// 	const size_type count = _distance(first, last);
		// 	if (count && !empty() && size() + count <= capacity()) // if the container has enough space for insertion
		// 	{
		// 		pointer end = _data_end;
		// 		while (end-- >= &(*pos)) // make place
		// 		{
		// 			std::uninitialized_fill_n((end + count), 1, *end);
		// 			_alloc.destroy(end);
		// 		}
		// 		std::uninitialized_copy(first , last, pos);
		// 		_data_end += count;
		// 	}
		// 	else if (count && !empty() && size() + count > capacity())
		// 	{
		// 		const size_type total_size = ((count + size() > size() * 2) ? count + size() : size() * 2);
		// 		pointer new_data_start = _alloc.allocate(total_size);
		// 		pointer new_data_end = std::uninitialized_copy(begin(), pos, new_data_start) + count;
		// 		std::uninitialized_copy(first , last, new_data_start + (&(*pos) - _data_start));
		// 		new_data_end = std::uninitialized_copy(&(*pos), _data_end, new_data_end);
		// 		_delete();
		// 		_data_start = new_data_start;
		// 		_data_end = new_data_end;
		// 		_data_max = new_data_start + total_size;
		// 	}
		// 	else if (count && empty())
		// 	{
		// 		if (count > capacity())
		// 			reserve(count);
		// 		std::uninitialized_copy(first, last, _data_start);
		// 		_data_end = _data_start + count;
		// 	}
		// };
		//
		// reference operator[](size_type i) {return _data_start[i];};
		// const_reference operator[](size_type i) const {return _data_start[i];};
		// reference front() { return (*_data_start); };
		// const_reference front() const { return (*_data_start); };
		// reference back() { return (*(_data_end - 1)); };
		// const_reference back() const { return (*(_data_end - 1)); };
		//
		// reference at(size_type i)
		// {
		// 	if (i >= static_cast<size_type>(_data_end - _data_start))
		// 		throw std::out_of_range(_range_err_message(i));
		// 	return _data_start[i];
		// };
		// const_reference at(size_type i) const
		// {
		// 	if (i >= static_cast<size_type>(_data_end - _data_start))
		// 		throw std::out_of_range(_range_err_message(i));
		// 	return _data_start[i];
		// };
		// allocator_type get_allocator() const
		// {
		// 	return allocator_type();
		// };
		// void swap(map &other)
		// {
		// 	ft::swap(_allocator, other._allocator);
		// 	ft::swap(_comparator, other._comparator);
		// 	ft::swap(_root, other._root);
		// 	ft::swap(_nil, other._nil);
		// 	ft::swap(_left_most, other._left_most);
		// 	ft::swap(_right_most, other._right_most);
		// };
		//
		// size_type count( const Key& key ) const;
		// iterator find(const Key& key);
		//
		// const_iterator find( const Key& key ) const;
		// iterator lower_bound( const Key& key );
		// const_iterator lower_bound( const Key& key ) const;
		// iterator upper_bound( const Key& key );
		// const_iterator upper_bound( const Key& key ) const;
	};

// template <class T, class Alloc>
// bool operator== (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
// {
// 	if (lhs.size() != rhs.size())
// 	return (false);
// 	typename ft::map<T>::const_iterator first1 = lhs.begin();
// 	typename ft::map<T>::const_iterator first2 = rhs.begin();
// 	while (first1 != lhs.end())
// 	{
// 		if (first2 == rhs.end() || *first1 != *first2)
// 			return (false);
// 		++first1;
// 		++first2;
// 	}
// 	return (true);
// };
//
// template <class T, class Alloc>
// bool operator!= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
// {
// 	return (!(lhs == rhs));
// };
//
// template <class T, class Alloc>
// bool operator<  (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
// {
// 	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
// };
//
// template <class T, class Alloc>
// bool operator<= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
// {
// 	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || std::equal(lhs.begin(), lhs.end(), rhs.begin()));
// };
//
// template <class T, class Alloc>
// bool operator>  (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
// {
// 	return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
// };
//
// template <class T, class Alloc>
// bool operator>= (const map<T,Alloc>& lhs, const map<T,Alloc>& rhs)
// {
// 	return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()) || std::equal(rhs.begin(), rhs.end(), lhs.begin()));
// };
//
//
// template <class T, class Alloc>
// void swap (map<T,Alloc> &x, map<T,Alloc> &y)
// {
// 	x.swap(y);
// };
}
