// #include "containers/list.hpp"
// #include "containers/map.hpp"
// #include "containers/queue.hpp"
// #include "containers/stack.hpp"
#include "containers/vector.hpp"
#include <iostream>

int main(void)
{
	{
		ft::vector<int> vec(1000, 255);
		ft::vector<int> vec2(vec);
		// (void)vec;
		// (void)vec2;
		ft::vector<int>::iterator it = vec.begin();
		ft::vector<int>::iterator end = vec.end();
		while (it != end) {
			std::cout << *it << std::endl; it++;
		}
		it = vec2.begin();
		end = vec2.end();
		while (it != end) {
			std::cout << *it << std::endl; it++;
		}
	}
	return 0;
}
