// 1	Input Iterator				Can scan the container forward only once, can't change the value it points to (read-only);
// 2	Output Iterator				Can scan the container forward only once, can't read the value it points to (write-only);
// 3	Forward Iterator			Can scan the container forward multiple times, can read and write the value it points to;
// 4	Bidirectional Iterator		Same as previous one but can scan the container back and forth;
// 5	Random Access Iterator		Same as previous one but can access the container also non-sequentially (i.e. by jumping around);

#include "map.hpp"
namespace ft
{
	// struct input_iterator_tag {};
	// struct output_iterator_tag {};
	// struct forward_iterator_tag : public input_iterator_tag {};
	// struct bidirectional_iterator_tag : public forward_iterator_tag {};
	// struct random_access_iterator_tag : public bidirectional_iterator_tag {};

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
		typedef std::random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
	};
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef std::random_access_iterator_tag iterator_category;
		typedef const T value_type;
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
	class bidirectional_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
	{
	private:
		typename ft::iterator< std::bidirectional_iterator_tag, T >::pointer _current;
	public:
		typedef typename ft::iterator< std::bidirectional_iterator_tag, T >::iterator_category iterator_category;
		typedef typename ft::iterator< std::bidirectional_iterator_tag, T >::value_type value_type;
		typedef typename ft::iterator< std::bidirectional_iterator_tag, T >::difference_type difference_type;
		typedef typename ft::iterator< std::bidirectional_iterator_tag, T >::pointer pointer;
		typedef typename ft::iterator< std::bidirectional_iterator_tag, T >::reference reference;
		bidirectional_iterator(pointer ptr = 0) : _current(ptr){};
		bidirectional_iterator(const bidirectional_iterator& other) : _current(other._current){};
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
	class input_iterator : public ft::iterator<std::input_iterator_tag, T>
	{
	private:
		typename ft::iterator< std::input_iterator_tag, T >::pointer _current;
	public:
		typedef typename ft::iterator< std::input_iterator_tag, T >::iterator_category iterator_category;
		typedef typename ft::iterator< std::input_iterator_tag, T >::value_type value_type;
		typedef typename ft::iterator< std::input_iterator_tag, T >::difference_type difference_type;
		typedef typename ft::iterator< std::input_iterator_tag, T >::pointer pointer;
		typedef typename ft::iterator< std::input_iterator_tag, T >::reference reference;
		input_iterator(pointer ptr = 0) : _current(ptr){};
		input_iterator(const input_iterator& other) : _current(other.ptr){};
		template <class diff>
		input_iterator(const input_iterator< diff >& it) : _current(it.base()) {};

		input_iterator& operator++()
		{
			++_current;
			return *this;
		};
		input_iterator operator++(int)
		{
			input_iterator tmp = *this;
			++(*this);
			return tmp;
		};
		bool operator==(const input_iterator< T >& other) {return (_current == other._current);};
		bool operator!=(const input_iterator< T >& other) {return (_current != other._current);};
		reference operator*() const {return *_current;};
		pointer operator->() const {return &(operator*());};
		pointer const& base() const {return _current;}
	};

	template <class T>
	class forward_iterator : public ft::iterator<std::forward_iterator_tag, T>
	{
	private:
		typename ft::iterator< std::forward_iterator_tag, T >::pointer _current;
	public:
		typedef typename ft::iterator< std::forward_iterator_tag, T >::iterator_category iterator_category;
		typedef typename ft::iterator< std::forward_iterator_tag, T >::value_type value_type;
		typedef typename ft::iterator< std::forward_iterator_tag, T >::difference_type difference_type;
		typedef typename ft::iterator< std::forward_iterator_tag, T >::pointer pointer;
		typedef typename ft::iterator< std::forward_iterator_tag, T >::reference reference;
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
	class random_access_iterator: public ft::iterator< std::random_access_iterator_tag, T >
	{
	public:
		typedef typename ft::iterator< std::random_access_iterator_tag, T >::iterator_category iterator_category;
		typedef typename ft::iterator< std::random_access_iterator_tag, T >::value_type value_type;
		typedef typename ft::iterator< std::random_access_iterator_tag, T >::difference_type difference_type;
		typedef typename ft::iterator< std::random_access_iterator_tag, T >::pointer pointer;
		typedef typename ft::iterator< std::random_access_iterator_tag, T >::reference reference;
	private:
		typename ft::iterator< std::random_access_iterator_tag, T >::pointer _current;
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
		reverse_iterator() : _current(){};
		 reverse_iterator(iterator_type it) : _current(it){};
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

	template <typename T>
	class const_tree_iterator;

	template <typename T>
	class tree_iterator : public ft::iterator< std::bidirectional_iterator_tag, T >
	{
	public:
		typedef typename T::value_type    value_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::pointer   pointer;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, value_type>::reference reference;
	protected:
		T*	_current;
		T*	_root;
		T*	_end;
	public:
		friend class const_tree_iterator<T>;
		tree_iterator(void): _current(0), _root(0), _end(0) {};
		explicit tree_iterator(T* ptr, T* root, T* end) : _current(ptr), _root(root), _end(end) {};
		// tree_iterator(const tree_iterator& src) : _current(src._current), _root(src._root), _end(src._end) {};
		tree_iterator(const tree_iterator& src) : _current(src._current), _root(src._root), _end(src._end) {};
		tree_iterator(const const_tree_iterator<T>& src) : _current(src._current), _root(src._root), _end(src._end) {};

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
		value_type& operator*(void) const {return _current->data;};
		// const_reference operator*(void) const {return _current->data;};
		// pointer operator->(void) const {return &_current->data;};
		value_type* operator->(void) const {return &_current->data;};
		// const_pointer operator->(void) const {return &(operator*());};
		// pointer base(void) {return _current->data;};
		T * base() const {return (_current);}
		// value_type* successor(value_type* node) {return _get_successor(node);};
	private:
		T* _get_max(T* node) const
		{
			while (node->right && node->right != _end)
				node = node->right;
			return node;
		};
		T* _get_min(T* node) const
		{
			while (node->left && node->left != _end && node != _end)
				node = node->left;
			return node;
		};
		T* _get_predecessor(T* node) const
		{
			T* predecessor;

			if (node->left && node->left != _end)
				return _get_max(node->left);
			predecessor = node->parent;
			while (node->parent && node == predecessor->left)
			{
				node = predecessor;
				predecessor = predecessor->parent;
			}
			if (!predecessor)
				return _end;
			else
				return predecessor;
		};
		T* _get_successor(T* node) const
		{
			T* successor;

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
	template <typename T>
	class const_tree_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
	{
	public:
		typedef typename T::value_type    value_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, const value_type>::iterator_category iterator_category;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, const value_type>::difference_type   difference_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag,  const value_type>::pointer   pointer;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, const value_type>::reference reference;
	protected:
		T*	_current;
		T*	_root;
		T*	_end;
	public:
		friend class tree_iterator<T>;

		const_tree_iterator(void): _current(0), _root(0), _end(0) {};
		explicit const_tree_iterator(T* ptr, T* root, T* end) : _current(ptr), _root(root), _end(end) {};
		// const_tree_iterator(T* ptr, T* root, T* end) : _current(ptr), _root(root), _end(end) {};
		const_tree_iterator(const const_tree_iterator& src) : _current(src._current), _root(src._root), _end(src._end) {};
		const_tree_iterator(const tree_iterator<T>& src) : _current(src._current), _root(src._root), _end(src._end) {};

		virtual ~const_tree_iterator(void) {};

		const_tree_iterator &operator=(const const_tree_iterator& rhs)
		{
			if (this != &rhs)
			{
				_current = rhs._current;
				_root = rhs._root;
				_end = rhs._end;
			}
			return *this;
		};
		const_tree_iterator &operator=(const tree_iterator<T>& rhs)
		{
			_current = rhs._current;
			_root = rhs._root;
			_end = rhs._end;
			return *this;
		};
		bool operator==(const const_tree_iterator& rhs) const {return (_current == rhs._current);};
		bool operator!=(const const_tree_iterator& rhs) const {return (_current != rhs._current);};
		const_tree_iterator& operator++(void)
		{
			if (_current != _end)
				_current = _get_successor(_current);
			return *this;
		};
		const_tree_iterator operator++(int)
		{
			const_tree_iterator tmp(*this);
			operator++();
			return tmp;
		};
		const_tree_iterator& operator--(void)
		{
			if (_current == _end)
				_current = _get_max(_root);
			else
				_current = _get_predecessor(_current);
			return *this;
		};
		const_tree_iterator operator--(int)
		{
			const_tree_iterator tmp(*this);
			operator--();
			return tmp;
		};
		const value_type& operator*(void) const {return _current->data;};
		// const_reference operator*(void) const {return _current->data;};
		// pointer operator->(void) const {return &_current->data;};
		const value_type* operator->(void) const {return &_current->data;};
		// const_pointer operator->(void) const {return &(operator*());};
		// pointer base(void) {return _current->data;};
		const T * base() const {return (_current);}
		// value_type* successor(value_type* node) {return _get_successor(node);};
	private:
		T* _get_max(T* node) const
		{
			while (node->right && node->right != _end)
				node = node->right;
			return node;
		};
		T* _get_min(T* node) const
		{
			while (node->left && node->left != _end && node != _end)
				node = node->left;
			return node;
		};
		T* _get_predecessor(T* node) const
		{
			T* predecessor;

			if (node->left && node->left != _end)
				return _get_max(node->left);
			predecessor = node->parent;
			while (node->parent && node == predecessor->left)
			{
				node = predecessor;
				predecessor = predecessor->parent;
			}
			if (!predecessor)
				return _end;
			else
				return predecessor;
		};
		T* _get_successor(T* node) const
		{
			T* successor;

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
