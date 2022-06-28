#pragma once
#include <memory>
#include <exception>
#include "utils.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <exception>

// https://tfetimes.com/wp-content/uploads/2015/11/Accelerated_C-_Practical_Programming_by_Example_-_Andrew_Koenig_Barbara_E._Moo_-_Addison-Wesley_-_2000.pdf
namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
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
	private:
		size_type _occupied_size;
		size_type _max_capacity;

		pointer _data_start; // first element in the Vec
		pointer _data_max; // end of the allocated memory
		pointer _data_end; // end of the constructed memory
		allocator_type _alloc;

		void _delete(void) {
			if (_data_start)
			{
				pointer it = _data_max;
				while (it != _data_start)
					_alloc.destroy(--it); // might leek ?
				_alloc.deallocate(_data_start, _data_max - _data_start);
			}
			_data_start = _data_max = _data_end = 0;
		};
		std::string _range_err_message(size_type val)
		{
			std::string message;
			std::ostringstream out;
			out << "vector::_M_range_check: __n (which is " << val << ") >= this->size() (which is " << size() << ")";
			message = out.str();
			return message;
		}

	public:
		explicit vector(const allocator_type &newAllocator = allocator_type()) :
		_alloc(newAllocator)
		{
			_data_start = _data_end = _data_max = 0;
		};

		explicit vector(size_type s, const value_type &value = value_type(), const allocator_type &newAllocator = allocator_type()) :
		_alloc(newAllocator)
		{
			_data_start = _alloc.allocate(s);
			_data_max = _data_end = _data_start + s;
			std::uninitialized_fill(_data_start, _data_max, value);
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

		vector &operator=(const value_type &v) {
			if (v == *this)
				return *this;
			_delete();
			_data_start = _alloc.allocate(v.end() - v.begin());
			_data_max = _data_end = std::uninitialized_copy(v.begin(), v.end(), _data_start);
			return *this;
		};

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
			if (i <= capacity())
				return;
			if (i > max_size())
				throw(std::length_error(""));
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
				_data_end = _data_start + n;
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
			if (_data_start)
			{
				pointer it = _data_end;
				while (it != _data_start)
					_alloc.destroy(--it);
			}
			_data_end = _data_start;
		};
		//
		iterator insert(iterator pos, const T& value)
		{
			if (size() + 1 <= capacity()) // if the container has enough space for insertion
			{
				if (static_cast<pointer>(pos) == _data_end)
				{
					push_back(value);
					return _data_end;
				}
				pointer end = _data_end - 1;
				while (end >= pos)
				{
					std::uninitialized_fill(static_cast<const_pointer>(end + 1), 1, *end);
					_alloc.destroy(end--);
				}
				_data_end++;
				
			}
		};
		void insert(iterator pos, size_type count, const T& value);
		template<class InputIt>
		void insert(iterator pos, InputIt first, InputIt last);
		// Inserts element at the back
		void push_back(const_reference val)
		{
			if (_data_end == _data_max)
				reserve(capacity() * 2);
			_alloc.construct(_data_end, val);
			_data_end++;
		};
		//
		void pop_back(void)
		{
			if (_data_end)
			{
				_alloc.destroy(_data_end - 1);
				if (_data_end - 1 != _data_start)
					_data_end--;
				else _data_end = _data_start = 0;
			}
		}

		reference &operator[](size_type i) {return _data_start[i];};
		const_reference &operator[](size_type i) const {return _data_start[i];};
		reference front() { return &(*_data_start); };
		const_reference front() const { return &(*_data_start); };
		reference back() { return &(*(_data_end - 1)); };
		const_reference back() const { return &(*(_data_end - 1)); };

		reference &at(size_type i)
		{
			if (i >= static_cast<size_type>(_data_end - _data_start))
				throw std::out_of_range(_range_err_message(i));
			return _data_start[i];
		};
		const_reference &at(size_type i) const
		{
			if (i >= static_cast<size_type>(_data_end - _data_start))
				throw std::out_of_range(_range_err_message(i));
			return _data_start[i];
		};
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

}
