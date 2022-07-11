#pragma once
#include <memory>
#include <exception>
#include "utils.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <exception>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		// class rev_iterator
		// {
		// private:
		// 	T* _current;
		// public:
		// 	rev_iterator(const T* ptr) : _current(ptr) {};
		// }
		typedef Alloc										allocator_type;
		typedef T											value_type;
		typedef std::ptrdiff_t								diff;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef pointer										iterator;
		typedef const_pointer 								const_iterator;
		typedef pointer										reverse_iterator;
		typedef const_pointer 								reverse_const_iterator;

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
				_data_start = _alloc.allocate(s);
				_data_max = _data_end = _data_start + s;
				std::uninitialized_fill(_data_start, _data_end, value);
			}
			else
			{
				_data_max = _data_end = _data_start = 0;
			}
		};

		vector(const vector &v, const allocator_type &newAllocator = allocator_type()) :
		_alloc(newAllocator)
		{
			_data_start = _alloc.allocate(v.end() - v.begin());
			_data_max = _data_end = std::uninitialized_copy(static_cast<const_pointer>(v.begin()), static_cast<const_pointer>(v.end()), _data_start);
		};

		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& newAllocator = allocator_type(), typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) :
		_alloc(newAllocator)
		{
			_data_start = _alloc.allocate(last - first);
			_data_max = _data_end = std::uninitialized_copy(static_cast<const_iterator>(first), static_cast<const_iterator>(last), _data_start);
		};

		vector &operator=(const vector& x)
		{
			// if (x == *this)
			// 	return (*this);
			_delete();
			if (x.size())
			{
				_data_start = _alloc.allocate(x.size());
				std::uninitialized_copy(static_cast<const_pointer>(x.begin()), static_cast<const_pointer>(x.end()), _data_start);
				_data_max = _data_end = _data_start + x.size();
			}
			else _data_max = _data_end = _data_start = 0;
			return (*this);
		}

		~vector() {
			_delete();
		};

		T *data(void) {return static_cast<T*>(_data_start);};
		const T *data(void) const {return static_cast<T*>(_data_start);};

		iterator begin() {return _data_start;};
		const_iterator begin() const {return _data_start;};
		iterator end() {return _data_end;};
		const_iterator end() const {return _data_end;};
		iterator rend() {return _data_start - 1;};
		const_iterator rend() const {return _data_start - 1;};
		iterator rbegin() {return _data_end - 1;};
		const_iterator rbegin() const {return _data_end - 1;};

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
			pointer new_data_end = std::uninitialized_copy(static_cast<const_pointer>(begin()), static_cast<const_pointer>(end()), new_data_start);
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
				reserve(n);
				std::uninitialized_fill(static_cast<pointer>(end()), _data_max, val);
				_data_end = _data_max = _data_start + n;
			}
		};

	    // Reduces capcity to fit the size
		void shrink_to_fit(void)
		{
			_alloc.deallocate(_data_end, _data_max - _data_end);
			_data_max = _data_end;
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
			if (pos == _data_end || _data_start == _data_end)
				return end();
			_alloc.destroy(pos);
			iterator ret = pos++;
			while (pos != _data_end)
			{
				std::uninitialized_copy(pos, pos+1, pos - 1);
				_alloc.destroy(pos++);
			}
			_data_end = pos - 1;
			return ret;
		};

		iterator erase(iterator first, iterator last)
		{
			iterator pos = first;
			std::ptrdiff_t distance = last - first;
			while (pos < last)
				_alloc.destroy(pos++);
			while (pos < _data_end)
			{
				std::uninitialized_copy(pos, pos+1, pos - distance);
				_alloc.destroy(pos);
				pos++;
			}
			_data_end = pos - distance;
			return first;
		};

		void assign(size_type n, const value_type& value)
		{
			clear();
			if (!n)
				return;
			if (size() >= n)
			{
				const_pointer end = _data_start + n;
				pointer it = _data_start;
				while (it != end)
					_alloc.destroy(it++);
				std::uninitialized_fill_n(_data_start, n, value);
			}
			else if (size() < n)
			{
				reserve(n);
				pointer it = _data_start;
				while (it != _data_start + n)
					_alloc.destroy(it++);
				std::uninitialized_fill_n(_data_start, n, value);
				_data_end = _data_start + n;
			}
		};

		template<class InputIterator>
		void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			const size_type n = last - first;
			clear();
			if (!n)
				return;
			if (size() >= n)
			{
				pointer it = _data_start;
				while (it != _data_start + n)
					_alloc.destroy(it++);
				std::uninitialized_copy(first, last, _data_start);
			}
			else if (size() < n)
			{
				reserve(n);
				pointer it = _data_start;
				while (it != _data_start + n)
					_alloc.destroy(it++);
				std::uninitialized_copy(first, last, _data_start);
				_data_end = _data_start + n;
			}
		};

		iterator insert(iterator pos, const value_type& value)
		{
			const size_type distance = pos - _data_start; // necessary when reallocating is necessary
			insert(pos, 1, value);
			return _data_start + distance;
		};

		void insert(iterator pos, size_type count, const value_type& value)
		{
			if (count && size() && size() + count <= capacity()) // if the container has enough space for insertion
			{
				// if (!(_data_start == _data_end))
				// {
					pointer end = _data_end;
					while (end-- >= pos) // make place
					{
						std::uninitialized_fill_n((end + count), 1, *end);
						_alloc.destroy(end);
					}
				// }
				std::uninitialized_fill_n(pos , count, value);
				_data_end += count;
			}
			else if (count && size() && size() + count > capacity())
			{
				// if (!(_data_start == _data_end))
				// {
					const size_type total_size = ((count + size() > size() * 2) ? count + size() : size() * 2);
					pointer new_data_start = _alloc.allocate(total_size);
					pointer new_data_end = std::uninitialized_copy(begin(), pos, new_data_start) + count;
					std::uninitialized_fill_n(new_data_start + (pos - _data_start), count, value);
					new_data_end = std::uninitialized_copy(pos, _data_end, new_data_end);
					_delete();
					_data_start = new_data_start;
					_data_end = new_data_end;
					_data_max = new_data_start + total_size;
				// }
			}
			else if (count && size() == 0)
			{
				(void)pos;
				if (count > capacity())
					reserve(count);
				std::uninitialized_fill_n(_data_start, count, value);
				_data_end = _data_start + count;
			}
		};


		template<class InputIterator>
		void insert(iterator pos, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
		{
			const size_type count = last - first;
			if (count && size() && size() + count <= capacity()) // if the container has enough space for insertion
			{
				// if (!(_data_start == _data_end)
				// {
					pointer end = _data_end;
					while (end-- >= pos) // make place
					{
						std::uninitialized_fill_n((end + count), 1, *end);
						_alloc.destroy(end);
					}
				// }
				std::uninitialized_copy(first , last, pos);
				_data_end += count;
			}
			else if (count && size() && size() + count > capacity())
			{
				// if (!(_data_start == _data_end)
				// {
					const size_type total_size = ((count + size() > size() * 2) ? count + size() : size() * 2);
					pointer new_data_start = _alloc.allocate(total_size);
					pointer new_data_end = std::uninitialized_copy(begin(), pos, new_data_start) + count;
					std::uninitialized_copy(first , last, new_data_start + (pos - _data_start));
					new_data_end = std::uninitialized_copy(pos, _data_end, new_data_end);
					_delete();
					_data_start = new_data_start;
					_data_end = new_data_end;
					_data_max = new_data_start + total_size;
				// }
			}
			else if (count && size() == 0)
			{
				if (count > capacity())
					reserve(count);
				std::uninitialized_copy(first, last, _data_start);
				_data_end = _data_start + count;
			}
		};
		// template<class InputIt>
		// void insert(iterator pos, InputIt first, InputIt last);
		// Inserts element at the back
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
		}

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
	return (false);
	typename ft::vector<T>::const_iterator first1 = lhs.begin();
	typename ft::vector<T>::const_iterator first2 = rhs.begin();
	while (first1 != lhs.end())
	{
		if (first2 == rhs.end() || *first1 != *first2)
			return (false);
		++first1;
		++first2;
	}
	return (true);
};

template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (!(lhs == rhs));
};

template <class T, class Alloc>
bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
};

template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || std::equal(lhs.begin(), lhs.end(), rhs.begin()));
};

template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
};

template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()) || std::equal(rhs.begin(), rhs.end(), lhs.begin()));
};


template <class T, class Alloc>
void swap (vector<T,Alloc> &x, vector<T,Alloc> &y)
{
	x.swap(y);
};
	// template <class T>
	// class vector<T>::iterator
	// {
	// private:
	// 	T *_curr;
	// public:
	// 	iterator(T *p) : _curr(p)
	// 	{
	// 	}
	//
	// 	iterator &operator++(void) // pre-incrementation
	// 	{
	// 		_curr++;
	// 		return *this;
	// 	}
	//
	// 	iterator &operator--(void) // pre-decrementation
	// 	{
	// 		_curr--;
	// 		return *this;
	// 	}
	// 	iterator &operator++(int)// post-incrementation
	// 	{
	// 		iterator tmp(&_curr);
	// 		_curr++;
	// 		return tmp;
	// 	}
	//
	// 	iterator &operator--(int)// post-decrementation
	// 	{
	// 		iterator tmp(&_curr);
	// 		_curr--;
	// 		return tmp;
	// 	}
	//
	// 	T &operator*()
	// 	{
	// 		return *_curr;
	// 	}
	//
	// 	bool operator==(const iterator &b) const
	// 	{
	// 		return *_curr == *b._curr;
	// 	}
	//
	// 	bool operator!=(const iterator &b) const
	// 	{
	// 		return *_curr != *b._curr;
	// 	}
	//
	//
	// };
	// template <class T, class Alloc>
	// 	bool operator== (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	// 	{
	// 		if (lhs.size() != rhs.size())
	// 			return (false);
	// 		typename ft::vector<T>::const_iterator first1 = lhs.begin();
	// 		typename ft::vector<T>::const_iterator first2 = rhs.begin();
	// 		while (first1 != lhs.end())
	// 		{
	// 			if (first2 == rhs.end() || *first1 != *first2)
	// 				return (false);
	// 			++first1;
	// 			++first2;
	// 		}
	// 		return (true);
	// 	}
}
