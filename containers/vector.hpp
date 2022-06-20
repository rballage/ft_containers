#pragma once
// https://tfetimes.com/wp-content/uploads/2015/11/Accelerated_C-_Practical_Programming_by_Example_-_Andrew_Koenig_Barbara_E._Moo_-_Addison-Wesley_-_2000.pdf
namespace ft
{
	template <class T, class Allocator = std::allocator<T> >
	class Vector
	{
	public: //typedefs
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t diff;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef T* iterator;
		typedef const T* const_iterator;
	private: //variables
		size_type _occupied_size;
		size_type _max_capacity;

		iterator _data; // first element in the Vec
		iterator _availaible; // (one past) the last element in the Vec
		iterator _limit; // (one past) the allocated memory
		allocator_type _alloc;

		void _create(void)
		{
			data = avail = limit = 0;
		};
		void _create(size_type size, const T &value)
		{
			_data = _alloc.allocate(size);
			_limit = _last = _data + size;
			uninitialized_fill(_data, _limit, value);
		};
		void _create(const_iterator first, const_iterator last)
		{
			_data = _alloc.allocate(last - first);
			_limit = _last = uninitialized_copy(start, end, _data);
		};
		void _delete(void)
		{
			if (_data)
			{
				iterator it = _availabale;
				while (it != _data)
					_alloc.destroy(--it); // might leek ?
				_alloc.deallocate(_data, _limit - _data);
			}
			_data = _limit = _avail = 0;
		};

	public:
		Vector(void) {_create();};
		//When we say that a constructor is explicit, we're saying that the compiler will use the
		//constructor only in contexts in which the user expressly invokes the constructor, and not otherwise:
		explicit Vector(size_type s)
		{

		};
		Vector(const Vector &arg)
		{

		};
		Vector<T> &operator=(const Vector<T> &arg)
		{

		};
		~Vector() {_delete();};

		iterator begin() {return _data;};
		const_iterator begin() const {return _data;};
		iterator end() {return _last;};
		const_iterator end() const {return _last;};

	    // const iterator cbegin() const;
		//
	    // const iterator cend() const;

	    /*----------------------------*/

	    /* -------- CAPACITY -------- */

	    bool empty() const
		{

		};

	    // Returns size of allocated storage capacity
		// size_t capacity() const
		// {
		//
		// }

	    // Requests a change in capacity
	    // reserve() will never decrase the capacity.
	    // void reserve(int newmalloc)
		// {
		//
		// }

	    // Changes the Vector's size.
	    // If the newsize is smaller, the last elements will be lost.
	    // Has a default value param for custom values when resizing.
	    // void resize(int newsize, T val = T())
		// {
		//
		// }

		// Returns the size of the Vector (number of elements).


	    // Returns the maximum number of elements the Vector can hold
		// size_t max_size() const
		// {
		// 	_limit - _data;
		// };

	    // Reduces capcity to fit the size
	    // void shrink_to_fit()
		// {
		//
		// }

	    /*----------------------------*/

	    /* -------- MODIFIERS --------*/

	    // Removes all elements from the Vector
	    // Capacity is not changed.
	    // void clear()
		// {
		//
		// }
		//
	    // // Inserts element at the back
	    // void push_back(const T &d)
		// {
		//
		// }
		//
	    // // Removes the last element from the Vector
	    // void pop_back()
		// {
		//
		// }

	    /*----------------------------*/

	    /* ----- ELEMENT ACCESS ----- */

	    // // Access elements with bounds checking
	    // T &at(int n);
		//
	    // // Access elements with bounds checking for constant Vectors.
	    // const T &at(int n) const;
		//
	    // // Access elements, no bounds checking
	    // T &operator[](int i)
		// {
		// 	return _data[i];
		// }
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
	// class Vector<T>::iterator
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
