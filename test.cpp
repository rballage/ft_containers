#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "set.hpp"

#define ONE_MILLION 1000000
#define TEN_MILLION 10000000
#define HUNDRED_THOUSAND 100000
#define TYPE int
#define NS ft

void	insert_map(bool print)
{
	NS::map<long> truc;
	for (long i = 0; i < ONE_MILLION; i++) {
		truc.insert(i);
	}
	if (print)
	{
		vec::iterator it = truc.begin();

		while (it != truc.end()) {
			std::cout << *it++ << " ";
		}
		std::cout << std::endl;
	}
}

int		main(void)
{

	return (0);
}
