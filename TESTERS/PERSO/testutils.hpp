#include <vector>
#include <stack>
#include <map>
#include <set>
#include <list>
#include <cassert>
#include <cstdlib>


#define ONE_MILLION 1000000
#define TEN_MILLION 10000000
#define HUNDRED_THOUSAND 100000
#define NUM HUNDRED_THOUSAND
#define PRINT true
// #ifndef NS
# define NS ft
# include "../../utils.hpp"
# include "../../vector.hpp"
# include "../../stack.hpp"
# include "../../map.hpp"
# include "../../set.hpp"
// #endif

template<typename T>
void print(T &cont, bool condition)
{
	if (!condition)
	{
		(void)cont;
		return;
	}
	typename T::iterator it = cont.begin();
	for (; it < cont.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << "CONTAINER SIZE: "<< cont.size() << std::endl;
}

void test_map();
void test_set();
void test_vector();
// void test_stack();
