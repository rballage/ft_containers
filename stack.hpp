template<class T, class Container = ft::vector<T> >
class stack
{
private:

protected:
	Container c;
public:
	typedef typename Container							container_type;
	typedef typename container_type::value_type			value_type;
	typedef typename container_type::size_type			size_type;
	typedef typename container_type::reference			reference;
	typedef typename container_type::const_reference	const_reference;

	explicit stack(const Container& cont = Container()) : c(cont) {};
	stack(const stack& other) : c(other.c) {};
	~stack() {};
	stack &operator=( const stack& other ) {};

	template< class T, class Container >
	bool operator==( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs ) {return lhs.c == rhs.c;};
	template< class T, class Container >
	bool operator!=( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs ) {return lhs.c != rhs.c;};
	template< class T, class Container >
	bool operator<( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs ) {return lhs.c < rhs.c;};
	template< class T, class Container >
	bool operator<=( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs ) {return lhs.c <= rhs.c;};
	template< class T, class Container >
	bool operator>( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs ) {return lhs.c > rhs.c;};
	template< class T, class Container >
	bool operator>=( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs ) {return lhs.c >= rhs.c;};

	size_type size() const {return (c.size());};
	bool empty() const {return (c.empty());};
	value_type &top() {return (c.back());};
	const value_type &top() const {return (c.back());};
	void push(const value_type &val) {c.push_back(val);};
	void pop(void) {c.pop_back();};
};
