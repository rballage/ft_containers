// 1	Input Iterator				Can scan the container forward only once, can't change the value it points to (read-only);
// 2	Output Iterator				Can scan the container forward only once, can't read the value it points to (write-only);
// 3	Forward Iterator			Can scan the container forward multiple times, can read and write the value it points to;
// 4	Bidirectional Iterator		Same as previous one but can scan the container back and forth;
// 5	Random Access Iterator		Same as previous one but can access the container also non-sequentially (i.e. by jumping around);


namespace ft
{
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
	};
	template <class T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
	};
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef const T* pointer;
		typedef const T& reference;
	};

	template <class cat, class T, class dist = std::ptrdiff_t, class ptr = T*, class ref = T&>
	struct iterator
	{
		typedef T value_type;
		typedef ptr pointer;
		typedef ref reference;
		typedef cat iterator_category;
		typedef dist difference_type;
	};

	template <class T>
	class bidirectional_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
	private:
		typename ft::iterator< ft::random_access_iterator_tag, T >::pointer _current;
	public:
		typedef typename ft::iterator< ft::bidirectional_iterator_tag, T >::iterator_category iterator_category;
		typedef typename ft::iterator< ft::bidirectional_iterator_tag, T >::value_type value_type;
		typedef typename ft::iterator< ft::bidirectional_iterator_tag, T >::difference_type difference_type;
		typedef typename ft::iterator< ft::bidirectional_iterator_tag, T >::pointer pointer;
		typedef typename ft::iterator< ft::bidirectional_iterator_tag, T >::reference reference;
		bidirectional_iterator(pointer ptr = 0) : _current(ptr){};
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
		bool operator==(const bidirectional_iterator< T >& other) {return (_current == other._current);};
		bool operator!=(const bidirectional_iterator< T >& other) {return (_current != other._current);};
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
		typename ft::iterator< ft::random_access_iterator_tag, T >::pointer _current;
	public:
		typedef typename ft::iterator< ft::forward_iterator_tag, T >::iterator_category iterator_category;
		typedef typename ft::iterator< ft::forward_iterator_tag, T >::value_type value_type;
		typedef typename ft::iterator< ft::forward_iterator_tag, T >::difference_type difference_type;
		typedef typename ft::iterator< ft::forward_iterator_tag, T >::pointer pointer;
		typedef typename ft::iterator< ft::forward_iterator_tag, T >::reference reference;
		forward_iterator(pointer ptr = 0) : _current(ptr){};
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
		bool operator==(const forward_iterator< T >& other) {return (_current == other._current);};
		bool operator!=(const forward_iterator< T >& other) {return (_current != other._current);};
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
		typename ft::iterator< ft::random_access_iterator_tag, T >::pointer _current;
	public:
		random_access_iterator(pointer ptr = 0) : _current(ptr){};
		random_access_iterator(const random_access_iterator< T >& it) : _current(it._current){};
		operator random_access_iterator<const T>() const { return _current; }
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
		random_access_iterator operator+(difference_type i) const { return random_access_iterator(_current + i);};
		random_access_iterator operator-(difference_type i) const { return random_access_iterator(_current - i);};
		random_access_iterator& operator+=(difference_type i)
		{
			_current += i;
			return *this;
		};
		random_access_iterator& operator-=(difference_type i)
		{
			_current -= i;
			return *this;
		};
		reference operator[](difference_type i) const { return (_current[i]); };
		pointer const& base() const { return _current; };
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
	random_access_iterator<Iterator> operator+(typename random_access_iterator<Iterator>::difference_type diff, const random_access_iterator< Iterator >& n) {return diff + n;};
	template <class T1, class T2>
	typename random_access_iterator< T1 >::difference_type operator-(const random_access_iterator< T2 >& lhs, const random_access_iterator< T1 >& rhs) {return lhs.base() - rhs.base();};



	template <class T>
	class reverse_iterator
	{
	public:
		typedef typename ft::iterator_traits<T>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<T>::value_type value_type;
		typedef typename ft::iterator_traits<T>::difference_type difference_type;
		typedef typename ft::iterator_traits<T>::pointer pointer;
		typedef typename ft::iterator_traits<T>::reference reference;
	private:
		typedef T iterator_type;
		iterator_type _current;
	public:
		reverse_iterator() : _current(0){};
		explicit reverse_iterator(iterator_type it) : _current(it){};
		template <class Iterator>
		reverse_iterator(const reverse_iterator< Iterator>& it) : _current(it.base()){};
		template<class Iterator >
		reverse_iterator& operator=(const reverse_iterator<Iterator>& other)
		{
			_current = other.base();
			return *this;
		};
		virtual ~reverse_iterator(){};
		operator reverse_iterator<const T>() const { return _current; }
		reference operator*() const
		{
			iterator_type tmp = _current;
			return *(--tmp);
		};
		reverse_iterator& operator++()
		{
			--_current;
			return *this;
		};
		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			--_current;
			return tmp;
		};
		pointer operator->() const { return &(operator*()); };
		reverse_iterator& operator--()
		{
			++_current;
			return *this;
		};
		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			++_current;
			return tmp;
		};
		reverse_iterator operator+(difference_type i) const {return reverse_iterator(base()-i);};
		reverse_iterator operator-(difference_type i) const {return reverse_iterator(base()+i);};
		reverse_iterator& operator+=(difference_type i)
		{
			_current -= i;
			return *this;
		};
		reverse_iterator& operator-=(difference_type i)
		{
			_current += i;
			return *this;
		};
		reference operator[](difference_type i) const { return (_current[-i - 1]); };
		iterator_type const& base() const { return _current; };
	};

	template <class T1, class T2>
	bool operator==(const reverse_iterator<T1>& lhs, const reverse_iterator<T2>& rhs) {return (lhs.base() == rhs.base());};
	template <class T1, class T2>
	bool operator!=(const reverse_iterator< T1 >& lhs, const reverse_iterator< T2 >& rhs) {return (lhs.base() != rhs.base());};
	template <class T1, class T2>
	bool operator<(const reverse_iterator< T1 > lhs, const reverse_iterator< T2 >& rhs){return (lhs.base() > rhs.base());};
	template <class T1, class T2>
	bool operator<=(const reverse_iterator< T1 >& lhs, const reverse_iterator< T2 >& rhs) {return (lhs.base() >= rhs.base());};
	template <class T1, class T2>
	bool operator>(const reverse_iterator< T1 > lhs, const reverse_iterator< T2 >& rhs) {return (lhs.base() < rhs.base());};
	template <class T1, class T2>
	bool operator>=(const reverse_iterator< T1 >& lhs, const reverse_iterator< T2 >& rhs) {return (lhs.base() <= rhs.base());};
	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type diff, const reverse_iterator< Iterator >& it) {return reverse_iterator<Iterator>(it + diff);};
	// template <class Iterator>
	// reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type diff, const reverse_iterator< Iterator >& it) {return reverse_iterator<Iterator>(it.base() + diff);};
	template <class T1, class T2>
	typename reverse_iterator< T1 >::difference_type operator-(const reverse_iterator< T2 >& lhs, const reverse_iterator< T1 >& rhs) {return rhs.base() - lhs.base();};
}
