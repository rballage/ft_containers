#ifndef SET_HPP
# define SET_HPP
# include "_tree_set.hpp"

namespace ft
{

	template<typename T, typename Compare = std::less<T>, typename Alloc = std::allocator<T> >
	class set
	{
	public:

		typedef T										key_type;
		typedef T										mapped_type;
		typedef T	value_type;
		typedef	Compare									key_compare;
		typedef Alloc																			allocator_type;

		class value_compare : public std::binary_function<value_type, value_type, bool>
		{
		protected:
			Compare comp;
		public:
			typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;
			value_compare(Compare c): comp(c) {};
			bool operator()(const value_type& lhs, const value_type& rhs) const {return (comp(lhs, rhs));};
		};
	private:
		typedef typename ft::TreeSet<T, key_compare, allocator_type> t_tree;
	public:
		typedef value_type&																		reference;
		typedef const value_type&																const_reference;
		typedef value_type*																		pointer;
		typedef const value_type*																const_pointer;
		typedef typename t_tree::iterator													iterator;
		typedef typename t_tree::const_iterator													const_iterator;
		typedef typename t_tree::const_reverse_iterator											reverse_iterator;
		typedef typename t_tree::const_reverse_iterator											const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator >::difference_type							difference_type;
		typedef typename allocator_type::size_type												size_type;

		explicit set(const Compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, allocator_type(alloc)) {};

		template<typename InputIterator>
		set(InputIterator first, InputIterator last, const Compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, allocator_type(alloc)) {_tree.insert(first, last);};

		set(const set& src) : _tree(src._tree) {};

		set	&operator=(const set& rhs) {_tree = rhs._tree; return (*this);};

		virtual ~set(void) {};

		iterator begin(void) {return (_tree.begin());};
		const_iterator begin(void) const {return (const_iterator(_tree.begin()));};
		iterator end(void) {return (_tree.end());};
		const_iterator end(void) const {return (_tree.end());};
		reverse_iterator rbegin(void) {return (_tree.rbegin());};
		const_reverse_iterator rbegin(void) const {return (_tree.rbegin());};
		reverse_iterator rend(void) {return (_tree.rend());};
		const_reverse_iterator rend(void) const {return (_tree.rend());};
		allocator_type get_allocator(void) const {return (allocator_type(_tree.get_allocator()));};
		bool empty(void) const {return (_tree.empty());};
		size_type size(void) const {return (_tree.size());};
		size_type max_size(void) const {return (_tree.max_size());};
		ft::pair<iterator, bool> insert(const value_type& val) {return (_tree.insert(val));};
		iterator insert(iterator position, const value_type& val) {return (_tree.insert(position, val));};
		template<typename InputIterator>
		void insert(InputIterator first, InputIterator last) {_tree.insert(first, last);};
		void erase(iterator position) {_tree.erase(position);};
		size_type erase(const key_type& key) {return (_tree.erase(key));};
		void erase(iterator first, iterator last) {_tree.erase(first, last);};
		void clear(void) {_tree.clear();};

		void swap(set& other)
		{
			if (this == &other)
				return;
			_tree.swap(other._tree);
		};

		key_compare key_comp(void) const {return (_tree.key_comp());};
		value_compare value_comp(void) const {return (value_compare(key_compare()));};

		iterator find(const key_type& key) {return (_tree.find(key));};
		const_iterator find(const key_type& key) const {return (_tree.find(key));};
		size_type count(const key_type& key) const {return (_tree.count(key));};

		iterator lower_bound(const key_type& key) {return (_tree.lower_bound(key));};
		const_iterator lower_bound(const key_type& key) const {return (_tree.lower_bound(key));};
		iterator upper_bound(const key_type& key) {return (_tree.upper_bound(key));};
		const_iterator upper_bound(const key_type& key) const {return (_tree.upper_bound(key));};

		ft::pair<iterator, iterator> equal_range(const key_type& key) {return (_tree.equal_range(key));};
		ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const {return (_tree.equal_range(key));};

	protected:
		t_tree	_tree;
	};//map

	template<typename T, typename Compare, typename Alloc>
	bool operator==(const set< T, Compare, Alloc>& lhs, const set< T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		if (lhs.empty() && rhs.empty())
			return true;
		typename ft::set<T, Compare, Alloc>::const_iterator first1 = lhs.begin();
		typename ft::set<T, Compare, Alloc>::const_iterator first2 = rhs.begin();
		while (first1 != lhs.end())
		{
			if (first2 == rhs.end() || *first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return true;
	};
	template<typename T, typename Compare, typename Alloc>
	bool operator!=(const set< T, Compare, Alloc>& lhs, const set< T, Compare, Alloc>& rhs) {return (!(lhs == rhs));};
	template<typename T, typename Compare, typename Alloc>
	bool operator<(const set< T, Compare, Alloc>& lhs, const set< T, Compare, Alloc>& rhs)
	{
		if ((lhs.empty() && !rhs.empty()))
			return true;
		if ((lhs.empty() && rhs.empty()))
			return false;
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};
	template<typename T, typename Compare, typename Alloc>
	bool operator>(const set< T, Compare, Alloc>& lhs, const set< T, Compare, Alloc>& rhs)
	{
		if ((!lhs.empty() && rhs.empty()))
			return true;
		if ((lhs.empty() && rhs.empty()))
			return false;
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	};
	template<typename T, typename Compare, typename Alloc>
	bool operator<=(const set< T, Compare, Alloc>& lhs, const set< T, Compare, Alloc>& rhs)
	{
		if ((lhs.empty() && !rhs.empty()))
			return true;
		return ( ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) || lhs == rhs);
	};
	template<typename T, typename Compare, typename Alloc>
	bool operator>=(const set< T, Compare, Alloc>& lhs, const set< T, Compare, Alloc>& rhs)
	{
		if ((!lhs.empty() && rhs.empty()))
			return true;
		return ( ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()) || lhs == rhs);
	};
	template<typename T, typename Compare, typename Alloc>
	void swap(set<T, Compare, Alloc>& lhs, set<T, Compare, Alloc>& rhs) {lhs.swap(rhs);};
} // namespace ft

#endif
