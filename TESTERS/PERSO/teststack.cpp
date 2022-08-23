

#include "testutils.hpp"


static void test_push_pop()
{
	NS::stack<int> s;
	assert(s.size() == 0);
	assert(s.empty());

	s.push(int(0));
	assert(s.size() == 1);
	assert(!s.empty());
	assert(s.top() == 0);

	s.push(int(1));
	assert(s.size() == 2);
	assert(!s.empty());
	assert(s.top() == 1);

	s.push(int(2));
	assert(s.size() == 3);
	assert(!s.empty());
	assert(s.top() == 2);

	s.push(int(3));
	assert(s.size() == 4);
	assert(!s.empty());
	assert(s.top() == 3);

	s.push(int(4));
	assert(s.size() == 5);
	assert(!s.empty());
	assert(s.top() == 4);

	s.pop();
	assert(s.size() == 4);
	assert(!s.empty());
	assert(s.top() == 3);

	s.pop();
	assert(s.size() == 3);
	assert(!s.empty());
	assert(s.top() == 2);

	s.pop();
	assert(s.size() == 2);
	assert(!s.empty());
	assert(s.top() == 1);

	s.pop();
	assert(s.size() == 1);
	assert(!s.empty());
	assert(s.top() == 0);

	s.pop();
	assert(s.size() == 0);
	assert(s.empty());
}

static void test_assign_copy()
{
	NS::stack<int> s;
	s.push(int(0));
	s.push(int(1));
	s.push(int(2));

	NS::stack<int> s2(s);
	assert(s2.size() == 3);
	assert(s2.top() == 2);
	s2.pop();
	assert(s2.size() == 2);
	assert(s2.top() == 1);
	s2.pop();
	assert(s2.size() == 1);
	assert(s2.top() == 0);
	s2.pop();
	assert(s2.size() == 0);

	s2.push(int(0));
	assert(s2.size() == 1);
	s2.push(int(1));
	assert(s2.size() == 2);
	s2.push(int(2));
	assert(s2.size() == 3);

	s2.push(int(3));
	assert(s.size() == 3);
	assert(s2.size() == 4);

	NS::stack<int> s3;
	assert(s3.size() == 0);

	s3 = s2;
	assert(s.size() == 3);
	assert(s2.size() == 4);
	assert(s3.size() == 4);

	s = s3;
	assert(s.size() == 4);
	assert(s2.size() == 4);
	assert(s3.size() == 4);

	assert(s.size() == 4);
	assert(s.top() == 3);
	s.pop();
	assert(s.size() == 3);
	assert(s.top() == 2);
	s.pop();
	assert(s.size() == 2);
	assert(s.top() == 1);
	s.pop();
	assert(s.size() == 1);
	assert(s.top() == 0);
	s.pop();
	assert(s.size() == 0);

	assert(s2.size() == 4);
	assert(s2.top() == 3);
	s2.pop();
	assert(s2.size() == 3);
	assert(s2.top() == 2);
	s2.pop();
	assert(s2.size() == 2);
	assert(s2.top() == 1);
	s2.pop();
	assert(s2.size() == 1);
	assert(s2.top() == 0);
	s2.pop();
	assert(s2.size() == 0);

	assert(s3.size() == 4);
	assert(s3.top() == 3);
	s3.pop();
	assert(s3.size() == 3);
	assert(s3.top() == 2);
	s3.pop();
	assert(s3.size() == 2);
	assert(s3.top() == 1);
	s3.pop();
	assert(s3.size() == 1);
	assert(s3.top() == 0);
	s3.pop();
	assert(s3.size() == 0);
}

static void test_swap()
{
	int array[5] = {0, 1, 2, 3, 4};
	NS::stack<int> s(NS::vector<int>(array, array + 5));

	int array2[3] = {2, 3, 1};
	NS::stack<int> s2(NS::vector<int>(array2, array2 + 3));

	ft::swap(s, s2);
	assert(s.size() == 3);
	assert(s2.size() == 5);
	assert(s.top() == 1);
	assert(s2.top() == 4);

	ft::swap(s2, s);
	assert(s.size() == 5);
	assert(s2.size() == 3);
	assert(s.top() == 4);
	assert(s2.top() == 1);
}

static void test_cmp_eq()
{
	int array[5] = {0, 1, 2, 3, 4};
	NS::stack<int> s(NS::vector<int>(array, array + 5));
	NS::stack<int> s2(s);

	assert(s == s2);
	assert(s >= s2);
	assert(s <= s2);

	s2.push(50);
	assert(s != s2);
	assert(s < s2);
	assert(s <= s2);
	assert(s2 > s);
	assert(s2 >= s);

	s.push(200);
	assert(s != s2);
	assert(s > s2);
	assert(s >= s2);
	assert(s2 < s);
	assert(s2 <= s);
}

void test_stack()
{
	test_push_pop();
	test_assign_copy();
	test_swap();
	test_cmp_eq();
}
