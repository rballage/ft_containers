#ifndef MONKEY_STACK
# define MONKEY_STACK 
#endif
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <utility>
#ifndef SSTR
# define SSTR( x ) (static_cast< std::ostringstream & >( ( std::ostringstream() << std::dec << (x) ) ).str())
#endif
#ifndef NAMESPACE
# define NAMESPACE ft
#endif
#ifndef _P
# define _P NAMESPACE::pair
#endif
#include <includes.hpp>
#include <input_iterator.hpp>
#include <common.hpp>
class logger logger;
int main()
{
	typedef NAMESPACE::stack<std::string> C;
}
