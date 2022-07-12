// 1	Input Iterator				Can scan the container forward only once, can't change the value it points to (read-only);
// 2	Output Iterator				Can scan the container forward only once, can't read the value it points to (write-only);
// 3	Forward Iterator			Can scan the container forward multiple times, can read and write the value it points to;
// 4	Bidirectional Iterator		Same as previous one but can scan the container back and forth;
// 5	Random Access Iterator		Same as previous one but can access the container also non-sequentially (i.e. by jumping around);
// 6								Contiguous Iterator	Same as previous one, with the addition that logically adjacent elements are also physically adjacent in memory.


namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class it>
	struct iterator_traits
	{
		typedef typename it::iterator_category iterator_category;
		typedef typename it::value_type value_type;
		typedef typename it::difference_type difference_type;
		typedef typename it::pointer pointer;
		typedef typename it::reference reference;
	};
	template <class T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
	};
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef const T* pointer;
		typedef const T& reference;
	};

	template <class cat, class T, class dist = std::ptrdiff_t, class ptr = T*, class ref = T&>
	class iterator
	{
	public:

		typedef typename cat iterator_category;
		typedef typename T value_type;
		typedef typename dist difference_type;
		typedef typename ptr pointer;
		typedef typename ref reference;

		iterator();
		iterator(const iterator&);
		~iterator();

		iterator& operator=(const iterator&);
		bool operator==(const iterator&) const;
		bool operator!=(const iterator&) const;
		bool operator<(const iterator&) const; //optional
		bool operator>(const iterator&) const; //optional
		bool operator<=(const iterator&) const; //optional
		bool operator>=(const iterator&) const; //optional

		iterator& operator++();
		iterator operator++(int); //optional
		iterator& operator--(); //optional
		iterator operator--(int); //optional
		iterator& operator+=(size_type); //optional
		iterator operator+(size_type) const; //optional
		friend iterator operator+(size_type, const iterator&); //optional
		friend iterator operator-(size_type, const iterator&); //optional
		iterator& operator-=(size_type); //optional
		iterator operator-(size_type) const; //optional
		difference_type operator-(iterator) const; //optional

		reference operator*() const;
		pointer operator->() const;
		reference operator[](size_type) const; //optional
	};

	template <class T>
	class bidirectional_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
	private:
		pointer _current;
	public:
		typedef typename ft::iterator< ft::bidirectional_iterator_tag, T >::iterator_category iterator_category;
		typedef typename ft::iterator< ft::bidirectional_iterator_tag, T >::value_type value_type;
		typedef typename ft::iterator< ft::bidirectional_iterator_tag, T >::difference_type difference_type;
		typedef typename ft::iterator< ft::bidirectional_iterator_tag, T >::pointer pointer;
		typedef typename ft::iterator< ft::bidirectional_iterator_tag, T >::reference reference;
		bidirectional_iterator(pointer ptr = ft::u_nullptr) : _current(ptr){};
		bidirectional_iterator(const bidirectional_iterator& other) : _current(other.ptr){};
		template <class diff>
		bidirectional_iterator(const bidirectional_iterator< diff >& it) : _current(it.base()) {};

		bidirectional_iterator& operator++()
		{
			++_current;
			return *this;
		};
		bidirectional_iterator operator++(int)
		{
			bidirectional_iterator tmp = *this;
			++(*this);
			return tmp;
		};
		bool operator==(const bidirectional_iterator< T >& other) {return (this->_current == other._current);};
		bool operator!=(const bidirectional_iterator< T >& other) {return (this->_current != other._current);};
		reference operator*() const {return *_current;};
		pointer operator->() const {return &(operator*());};
		bidirectional_iterator& operator--()
		{
			--_current;
			return *this;
		};
		bidirectional_iterator operator--(int)
		{
			bidirectional_iterator tmp = *this;
			--(*this);
			return tmp;
		};
		pointer const& base() const {return _current;}
	};


	template <class T>
	class forward_iterator : public ft::iterator<ft::forward_iterator_tag, T>
	{
	private:
		pointer _current;
	public:
		typedef typename ft::iterator< ft::forward_iterator_tag, T >::iterator_category iterator_category;
		typedef typename ft::iterator< ft::forward_iterator_tag, T >::value_type value_type;
		typedef typename ft::iterator< ft::forward_iterator_tag, T >::difference_type difference_type;
		typedef typename ft::iterator< ft::forward_iterator_tag, T >::pointer pointer;
		typedef typename ft::iterator< ft::forward_iterator_tag, T >::reference reference;
		forward_iterator(pointer ptr = ft::u_nullptr) : _current(ptr){};
		forward_iterator(const forward_iterator& other) : _current(other.ptr){};
		template <class diff>
		forward_iterator(const forward_iterator< diff >& it) : _current(it.base()) {};

		forward_iterator& operator++()
		{
			++_current;
			return *this;
		};
		forward_iterator operator++(int)
		{
			forward_iterator tmp = *this;
			++(*this);
			return tmp;
		};
		bool operator==(const forward_iterator< T >& other) {return (this->_current == other._current);};
		bool operator!=(const forward_iterator< T >& other) {return (this->_current != other._current);};
		reference operator*() const {return *_current;};
		pointer operator->() const {return &(operator*());};
		forward_iterator& operator--()
		{
			--_current;
			return *this;
		};
		forward_iterator operator--(int)
		{
			forward_iterator tmp = *this;
			--(*this);
			return tmp;
		};
		pointer const& base() const {return _current;}
	};




	template <class T>
	class random_access_iterator: public ft::iterator< ft::random_access_iterator_tag, T >
	{
	public:
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::iterator_category iterator_category;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::value_type value_type;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::difference_type difference_type;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::pointer pointer;
		typedef typename ft::iterator< ft::random_access_iterator_tag, T >::reference reference;
	private:
		pointer _current;
	public:
		random_access_iterator(pointer ptr = ft::u_nullptr) : _current(ptr){};
		random_access_iterator(const random_access_iterator< T >& it) : _current(it._current){};
		operator random_access_iterator<const T>() const { return this->_current; }
		random_access_iterator& operator++()
		{
			++_current;
			return *this;
		};
		random_access_iterator operator++(int)
		{
			random_access_iterator tmp = *this;
			++(*this);
			return tmp;
		};
		reference operator*() const { return *_current; };
		pointer operator->() const { return &(operator*()); };
		random_access_iterator& operator--()
		{
			--_current;
			return *this;
		};
		random_access_iterator operator--(int)
		{
			random_access_iterator tmp = *this;
			--(*this);
			return tmp;
		};
		random_access_iterator operator+(difference_type i) const { return random_access_iterator(this->_current + i);};
		random_access_iterator operator-(difference_type i) const { return random_access_iterator(this->_current - i);};
		random_access_iterator& operator+=(difference_type i)
		{
			this->_current += i;
			return *this;
		};
		random_access_iterator& operator-=(difference_type i)
		{
			this->_current -= i;
			return *this;
		};
		reference operator[](difference_type i) const { return (this->_current[i]); };
		pointer const& base() const { return this->_current; };
	};

	template <class T1, class T2>
	bool operator==(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs) {return (lhs.base() == rhs.base());};
	template <class T1, class T2>
	bool operator!=(const random_access_iterator< T1 >& lhs, const random_access_iterator< T2 >& rhs) {return (lhs.base() != rhs.base());};
	template <class T1, class T2>
	bool operator<(const random_access_iterator< T1 > lhs, const random_access_iterator< T2 >& rhs){return (lhs.base() < rhs.base());};
	template <class T1, class T2>
	bool operator<=(const random_access_iterator< T1 >& lhs, const random_access_iterator< T2 >& rhs) {return (lhs.base() <= rhs.base());};
	template <class T1, class T2>
	bool operator>(const random_access_iterator< T1 > lhs, const random_access_iterator< T2 >& rhs) {return (lhs.base() > rhs.base());};
	template <class T1, class T2>
	bool operator>=(const random_access_iterator< T1 >& lhs, const random_access_iterator< T2 >& rhs) {return (lhs.base() >= rhs.base());};
	template <class Iterator>
	random_access_iterator<Iterator> operator+(typename random_access_iterator<Iterator>::difference_type diff, const random_access_iterator< Iterator >& iter) {return diff + n;};
	template <class T1, class T2>
	typename random_access_iterator< T1 >::difference_type operator-(const random_access_iterator< T2 >& lhs, const random_access_iterator< T1 >& rhs) {return lhs.base() - rhs.base();};
}
