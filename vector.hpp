#ifndef VECTOR_HPP
# define  VECTOR_HPP
# include "utils.hpp"
// https://github.com/pmouhali/ft_containers/blob/main/vector.hpp
namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef Alloc										allocator_type;
		typedef T											value_type;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename ft::random_access_iterator<value_type>				iterator;
		typedef typename ft::random_access_iterator<const value_type> 		const_iterator;
		typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> 				const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type		difference_type;

	private:
		pointer _data_start, _data_max, _data_end;
		allocator_type _alloc;

		void _delete(void)
		{
			if (_data_start != _data_end)
			{
				pointer it = _data_start;
				while (it != _data_end)
					_alloc.destroy(it++);
			}
			if (_data_max - _data_start)
				_alloc.deallocate(_data_start, _data_max - _data_start);
			_data_start = _data_max = _data_end = 0;
		};

		const std::string _range_err_message(size_type val) const
		{
			std::string message;
			std::ostringstream out;
			out << "vector::_M_range_check: __n (which is " << val << ") >= this->size() (which is " << size() << ")";
			message = out.str();
			return message;
		};
		template<class Iterator>
		size_type _distance(Iterator first, Iterator last) const
		{
			size_type len = 0;
			while (first != last)
			{
				first++;
				len++;
			}
			return len;
		};
		template <class InputIterator>
		pointer _construct_copy(InputIterator first, InputIterator last, pointer pos, typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			while (first != last)
			{
				_alloc.construct(pos++, *first++);
			}
			return &(*pos);
		};
		template <class ForwardIt>
		void _construct_fill_n(ForwardIt pos, size_type count, const T& value, typename enable_if<!ft::is_integral<ForwardIt>::value, ForwardIt>::type* = 0)
		{
			while (count--)
			{
				_alloc.construct(pos++, value);
			}
		};
		template <class ForwardIt>
		void _construct_fill(ForwardIt pos, ForwardIt end, const T& value, typename enable_if<!ft::is_integral<ForwardIt>::value, ForwardIt>::type* = 0)
		{
			while (pos != end)
			{
				_alloc.construct(pos++, value);
			}
		};
		template<class InputIterator>
		vector _temp_copy(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			vector temp;
			// temp.reserve(128);
			while (first != last)
				temp.push_back(*first++);
			return temp;
		};

	public:
		explicit vector(const allocator_type &newAllocator = allocator_type()) :
		_alloc(newAllocator)
		{
			_data_start = _data_end = _data_max = 0;
		};

		explicit vector(size_type s, const value_type &value = value_type(), const allocator_type &newAllocator = allocator_type()) :
		_alloc(newAllocator)
		{
			if (s)
			{
				if (s > max_size())
					throw(std::length_error("vector::reserve"));
				_data_start = _alloc.allocate(s);
				_data_max = _data_end = _data_start + s;
				_construct_fill(_data_start, _data_end, value);
			}
			else
				_data_max = _data_end = _data_start = 0;
		};

		vector(const vector &v, const allocator_type &newAllocator = allocator_type()) :
		_alloc(newAllocator)
		{
			if (v.empty())
			{
				_data_max = _data_end = _data_start = 0;
				return;
			}
			_data_start = _alloc.allocate(v.end() - v.begin());
			_data_max = _data_end = _construct_copy(v.begin(), v.end(), _data_start);
		};

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& newAllocator = allocator_type(), typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) :
		_alloc(newAllocator)
		{
			vector temp = _temp_copy(first, last);
			if (temp.size() > max_size())
				throw(std::length_error("vector::reserve"));
			_data_max = _data_end = _data_start = 0;
			if (temp.size())
			{
				_data_start = _data_end = _alloc.allocate(temp.size());
				_data_max = _data_start + temp.size();
				// _data_max = _data_end = _construct_copy(first, last, _data_start);
				// reserve(temp.size());
				_construct_copy(temp.begin(), temp.end(), _data_start);
				_data_end = _data_start + temp.size();
				// *this = temp;
			}
			// *this = temp;
		};

		vector &operator=(const vector& x)
		{
			size_type new_capacity;
			bool realloc = false;
			if (capacity() >= x.capacity())
			{
				new_capacity = capacity();
				clear();
			}
			else
			{
				realloc = true;
				new_capacity = x.capacity();
				_delete();
			}
			if (x.size())
			{
				if (realloc)
				{
					_data_start = _alloc.allocate(new_capacity);
					_data_max = _data_start + new_capacity;
				}
				_construct_copy(x.begin(), x.end(), _data_start);
				_data_end = _data_start + x.size();
			}
			return (*this);
		}

		~vector() {
			_delete();
		};

		T *data(void) {return static_cast<T*>(_data_start);};
		const T *data(void) const {return static_cast<T*>(_data_start);};

		iterator begin() {return iterator(_data_start);};
		const_iterator begin() const {return iterator(_data_start);};
		iterator end() {return iterator(_data_end);};
		const_iterator end() const {return iterator(_data_end);};
		reverse_iterator rend() {return reverse_iterator(_data_start);};
		const_reverse_iterator rend() const {return const_reverse_iterator(_data_start);};
		reverse_iterator rbegin() {return reverse_iterator(_data_end);};
		const_reverse_iterator rbegin() const {return const_reverse_iterator(_data_end);};

		bool empty() const {return !(_data_end - _data_start);};
		size_type size() const {return _data_end - _data_start;};
		size_type capacity() const {return _data_max - _data_start;}
		size_type max_size(void) const {return allocator_type().max_size();};

		// Requests a change in capacity
		// reserve() will never decrase the capacity.
		void reserve(size_type i)
		{
			if (!i)
				i = 1;
			if (i <= capacity())
				return;
			if (i > max_size())
				throw(std::length_error("vector::reserve"));

			pointer new_data_start = _alloc.allocate(i);
			pointer new_data_end = _construct_copy(begin(), end(), new_data_start);
			pointer new_data_max = new_data_start + i;
			_delete();
			_data_start = new_data_start;
			_data_end = new_data_end;
			_data_max = new_data_max;
		};

		// Changes the vector's size.
		// If the newsize is smaller, the last elements will be lost.
		// Has a default value param for custom values when resizing.
		void resize(size_type n, value_type val = value_type())
		{
			if (size() > n)
			{
				pointer it = _data_start + n;
				while (it != _data_end)
					_alloc.destroy(it++);
				_data_end = _data_start + n;
			}
			else if (size() < n)
			{
				if (size() *2 < n)
					reserve(n);
				else // need to do stuff with capacity ?
					reserve(size() * 2);
				_construct_fill(_data_end, _data_start + n, val);
				_data_end = _data_start + n;
			}
		};

		// deconstuct all elements from the vector
		// Capacity is not changed.
		void clear(void)
		{
			if (_data_start != _data_end)
			{
				pointer it = _data_end;
				while (it != _data_start)
					_alloc.destroy(--it);
			}
			_data_end = _data_start;
		};

		iterator erase(iterator pos)
		{
			if (&(*pos) == _data_end || _data_start == _data_end)
				return end();
			_alloc.destroy(&(*pos));
			iterator ret = pos++;
			while (&(*pos) != _data_end)
			{
				_construct_copy(&(*pos), &(*(pos+1)), &(*(pos-1)));
				_alloc.destroy(&(*pos));
				pos++;
			}
			_data_end = &(*(pos-1));
			return ret;
		};

		iterator erase(iterator first, iterator last)
		{
			if (first == last)
				return first;
			iterator pos = first;
			std::ptrdiff_t distance = last - first;
			while (pos < last)
			{
				_alloc.destroy(&(*pos));
				pos++;
			}
			while (&(*pos) < _data_end)
			{
				_construct_copy(pos, pos+1, (pos - distance).base());
				_alloc.destroy(&(*pos));
				pos++;
			}
			_data_end = &(*(pos - distance));
			return first;
		};

		void assign(size_type n, const value_type& value)
		{
			clear();
			if (!n)
				return;
			if (size() < n)
				reserve(n);
			_construct_fill_n(_data_start, n, value);
			_data_end = _data_start + n;
		};

		template<class InputIterator>
		void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			vector temp = _temp_copy(first, last);
			const size_type n = temp.size();
			clear();
			if (!n)
				return;
			if (size() < n)
				reserve(n);
			_construct_copy(temp.begin(), temp.end(), _data_start);
			_data_end = _data_start + n;
		};

		iterator insert(iterator pos, const value_type& value)
		{
			const size_type distance = &(*pos) - _data_start; // necessary when reallocating is necessary
			insert(pos, 1, value);
			return _data_start + distance;
		};

		void insert(iterator pos, size_type count, const value_type& value)
		{
			if (!count)
				return;
			if (count > max_size())
				throw(std::length_error("vector::reserve"));
			if (empty())
			{
				(void)pos;
				if (count > capacity())
					reserve(count);
				_construct_fill_n(_data_start, count, value);
				_data_end = _data_start + count;
				return ;
			}
			size_type total_size;
			if (size() + count <= capacity()) // if the container has enough space for insertion
				total_size = (capacity());
			else total_size = ((count + size() > size() * 2) ? count + size() : size() * 2);
			pointer new_data_start = _alloc.allocate(total_size);
			pointer new_data_end = _construct_copy(begin(), pos, new_data_start);
			_construct_fill_n(new_data_end, count, value);
			new_data_end = _construct_copy(&(*pos), _data_end, new_data_end + count);
			_delete();
			_data_start = new_data_start;
			_data_end = new_data_end;
			_data_max = new_data_start + total_size;
		};


		template<class InputIterator>
		void insert(iterator pos, InputIterator p, InputIterator l, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			vector temp = _temp_copy(p, l);
			iterator first = (temp.begin());
			iterator last = (temp.end());
			const size_type count = temp.size();
			if (!count)
				return;
			if (count + size() > max_size())
				throw(std::length_error("vector::reserve"));
			if (count && empty())
			{
				if (count > capacity())
					reserve(count);
				_construct_copy(first, last, _data_start);
				_data_end = _data_start + count;
				return ;
			}
			size_type total_size = 0;
			if (count && !empty() && size() + count <= capacity()) // if the container has enough space for insertion
				total_size = capacity();
			else
				total_size = ((count + size() > size() * 2) ? count + size() : size() * 2);
			pointer new_data_start = _alloc.allocate(total_size);
			pointer new_data_end = _construct_copy(begin(), pos, new_data_start); // copy first part of original vector until pos (not included)
			new_data_end = _construct_copy(first , last, new_data_end); // insertion
			new_data_end = _construct_copy(&(*pos), _data_end, new_data_end); // copy last part
			_delete();
			_data_start = new_data_start;
			_data_end = new_data_end;
			_data_max = new_data_start + total_size;
		};

		void push_back(const_reference val)
		{
			if (_data_end == _data_max)
				reserve(capacity() ? capacity() * 2 : 1);
			_alloc.construct(_data_end, val);
			_data_end++;
		};
		//
		void pop_back(void)
		{
			if (_data_end != _data_start)
			{
				_alloc.destroy(_data_end - 1);
				if (_data_end - 1 != _data_start)
					_data_end--;
				else _data_end = _data_start;
			}
		};

		reference operator[](size_type i) {return _data_start[i];};
		const_reference operator[](size_type i) const {return _data_start[i];};
		reference front() { return (*_data_start); };
		const_reference front() const { return (*_data_start); };
		reference back() { return (*(_data_end - 1)); };
		const_reference back() const { return (*(_data_end - 1)); };

		reference at(size_type i)
		{
			if (i >= static_cast<size_type>(_data_end - _data_start))
				throw std::out_of_range(_range_err_message(i));
			return _data_start[i];
		};
		const_reference at(size_type i) const
		{
			if (i >= static_cast<size_type>(_data_end - _data_start))
				throw std::out_of_range(_range_err_message(i));
			return _data_start[i];
		};
		allocator_type get_allocator() const
		{
			return allocator_type();
		};
		void swap(vector &other)
		{
			ft::swap(_alloc, other._alloc);
			ft::swap(_data_start, other._data_start);
			ft::swap(_data_end, other._data_end);
			ft::swap(_data_max, other._data_max);
		};
	};

template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	if (lhs.empty() && rhs.empty())
		return true;
	typename ft::vector<T>::const_iterator first1 = lhs.begin();
	typename ft::vector<T>::const_iterator first2 = rhs.begin();
	while (first1 != lhs.end())
	{
		if (first2 == rhs.end() || *first1 != *first2)
			return (false);
		++first1;
		++first2;
	}
	return true;
};

template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (!(lhs == rhs));
};

template <class T, class Alloc>
bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	if ((lhs.empty() && !rhs.empty()))
		return true;
	if ((lhs.empty() && rhs.empty()))
		return false;
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
};

template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	if ((lhs.empty() && !rhs.empty()))
		return true;
	return ( ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || lhs == rhs);
};

template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	if ((!lhs.empty() && rhs.empty()))
		return true;
	if ((lhs.empty() && rhs.empty()))
		return false;
	return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
};

template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	if ((!lhs.empty() && rhs.empty()))
		return true;
	return ( ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()) || lhs == rhs);
};

template <class T, class Alloc>
void swap (vector<T,Alloc> &x, vector<T,Alloc> &y)
{
	x.swap(y);
};
}

#endif
