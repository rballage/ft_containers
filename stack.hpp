template<class T, class Container = std::deque<T> >
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

	explicit stack(const Container& cont = Container()) {};
	stack(const stack& other) {};
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
};
