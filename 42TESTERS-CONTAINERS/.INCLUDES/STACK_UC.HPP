#ifndef STACK_HPP
# define  STACK_HPP

// #include "utils.hpp"
#include "vector.hpp"

namespace ft
{
	template<class T, class Container = ft::vector<T> >
	class stack
	{
	private:

	protected:
		Container c;
	public:
		typedef  Container	container_type;
		typedef typename container_type::value_type			value_type;
		typedef typename container_type::size_type			size_type;
		typedef typename container_type::reference			reference;
		typedef typename container_type::const_reference	const_reference;

		explicit stack(const Container& cont = Container()) : c(cont) {};
		stack(const stack& other) : c(other.c) {};
		~stack() {return;};
		stack &operator=( const stack& other ) { c = other.c; return *this;};

		template< class TYPE, class CONT >
		friend bool operator==( const stack<TYPE, CONT>& left, const stack<TYPE, CONT>& right );
		template< class TYPE, class CONT >
		friend bool operator<( const stack<TYPE, CONT>& left, const stack<TYPE, CONT>& right );



		size_type size() const {return (c.size());};
		bool empty() const {return (c.empty());};
		reference top() {return (c.back());};
		const_reference top() const {return (c.back());};
		void push(const value_type &val) {c.push_back(val);};
		void pop(void) {c.pop_back();};
	};
	template< class TYPE, class CONT >
	bool operator==( const stack<TYPE, CONT>& left, const stack<TYPE, CONT>& right ) {return left.c == right.c;};
	template< class TYPE, class CONT >
	bool operator<( const stack<TYPE, CONT>& left, const stack<TYPE, CONT>& right ) {return left.c < right.c;};
	template< class T, class Container >
	bool operator!=( const ft::stack<T,Container>& left, const ft::stack<T,Container>& right ) {return !(left == right);};

	template< class T, class Container >
	bool operator<=( const ft::stack<T,Container>& left, const ft::stack<T,Container>& right ) {return (left < right || left == right);};

	template< class T, class Container >
	bool operator>( const ft::stack<T,Container>& left, const ft::stack<T,Container>& right ) {return (right < left);};

	template< class T, class Container >
	bool operator>=( const ft::stack<T,Container>& left, const ft::stack<T,Container>& right ) {return (right < left || right == left);};
}

#endif
