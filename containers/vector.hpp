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
	public: //typedefs
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
	private: //variables
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
		//When we say that a constructor is explicit, we're saying that the compiler will use the
		//constructor only in contexts in which the user expressly invokes the constructor, and not otherwise:
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

		iterator begin() {return _data_start;};
		const_iterator begin() const {return _data_start;};
		iterator end() {return _data_end;};
		const_iterator end() const {return _data_end;};

	    // const iterator cbegin() const;
		//
	    // const iterator cend() const;

	    /*----------------------------*/

	    /* -------- CAPACITY -------- */

		bool empty() const
		{
			return !(_data_end - _data_start);
		};
		size_type size() const
		{
			return _data_end - _data_start;
		};

	    // Returns size of allocated storage capacity
		size_type capacity() const
		{
			return _data_max - _data_start;
		}


	    // Requests a change in capacity
	    // reserve() will never decrase the capacity.
	    // void reserve(int newmalloc)
		// {
		//
		// }

	    // Changes the vector's size.
	    // If the newsize is smaller, the last elements will be lost.
	    // Has a default value param for custom values when resizing.
	    // void resize(int newsize, T val = T())
		// {
		//
		// }

		// Returns the size of the vector (number of elements).


	    // Returns the maximum number of elements the vector can hold
		size_type max_size(void) const
		{
			return allocator_type().max_size();
		};

	    // Reduces capcity to fit the size
	    // void shrink_to_fit()
		// {
		//
		// }


	    // deconstuct all elements from the vector
	    // Capacity is not changed.
		void clear()
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
	    // // Inserts element at the back
	    // void push_back(const T &d)
		// {
		//
		// }
		//
	    // // Removes the last element from the vector
		void pop_back()
		{
			if (_data_end)
			{
				_alloc.destroy(_data_end - 1);
				if (_data_end - 1 != _data_start)
					_data_end--;
				else _data_end = _data_start = 0;
			}
		}

	    /*----------------------------*/

	    /* ----- ELEMENT ACCESS ----- */



		reference &operator[](size_type i)
		{
			return _data_start[i];
		};

		const_reference &operator[](size_type i) const
		{
			return _data_start[i];
		};

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
		//
	    // // Access elements, no bounds checking
	    // const T &operator[](int i) const
		// {
		// 	return _data[i];
		// }
		//
	    // // Returns a reference to the first element
	    // T &front()
		// {
		// 	return iterator(&_data);
		// }
	    // // Returns a reference to the first element
	    // const T &front() const
		// {
		// 	return iterator(&_data);
		// }
		//
	    // // Returns a reference to the last element
	    // T &back();
		//
	    // // Returns a reference to the last element
	    // const T &back() const;

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
