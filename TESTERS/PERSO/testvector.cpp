
#include "testutils.hpp"



static void test_pushback()
{
	NS::vector<int> vec;
	assert(vec.size() == 0);

	vec.push_back(int(0));
	assert(vec.size() == 1);
	assert(vec[0] == 0);

	vec.push_back(int(1));
	assert(vec.size() == 2);
	assert(vec[1] == 1);

	vec.push_back(int(8000));
	assert(vec.size() == 3);
	assert(vec[2] == 8000);

	vec.push_back(int(33));
	assert(vec.size() == 4);
	assert(vec[3] == 33);
}

static void test_assign()
{
	NS::vector<int> vec;
	assert(vec.size() == 0);

	vec.assign(0, int(66));
	assert(vec.size() == 0);

	vec.assign(10, int(5));
	assert(vec.size() == 10);
	assert(vec[2] == 5);
	assert(vec[9] == 5);

	vec.assign(15, int(120));
	assert(vec.size() == 15);
	assert(vec[0] == 120);
	assert(vec[6] == 120);

	vec.assign(5, int(6));
	assert(vec.size() == 5);
	assert(vec[2] == 6);
	assert(vec[3] == 6);

	vec.assign(50, int(9000));
	assert(vec.size() == 50);
	assert(vec[26] == 9000);
	assert(vec[49] == 9000);
}

static void test_assign_iter()
{
	NS::vector<int> vec;
	assert(vec.size() == 0);

	{
		int array[0] = {};

		vec.assign(array, array);
		assert(vec.size() == 0);
	}
	{
		int array[5] = {0, 1, 2, 3, 4};

		vec.assign(array, array + 5);
		assert(vec.size() == 5);
		assert(vec[0] == 0);
		assert(vec[1] == 1);
		assert(vec[2] == 2);
		assert(vec[3] == 3);
		assert(vec[4] == 4);
	}
	{
		int array[2] = {42, 43};

		vec.assign(array, array + 2);
		assert(vec.size() == 2);
		assert(vec[0] == 42);
		assert(vec[1] == 43);
	}
}

static void test_constr()
{
	{
		NS::vector<int> vec(0, int(5));
		assert(vec.size() == 0);
	}
	{
		NS::vector<int> vec(10, int(5));
		assert(vec.size() == 10);
		assert(vec[2] == 5);
		assert(vec[9] == 5);
	}
	{
		NS::vector<int> vec(15, int(120));
		assert(vec.size() == 15);
		assert(vec[0] == 120);
		assert(vec[6] == 120);
	}
	{
		NS::vector<int> vec(5, int(6));
		assert(vec.size() == 5);
		assert(vec[2] == 6);
		assert(vec[3] == 6);
	}
	{
		NS::vector<int> vec(50, int(9000));
		assert(vec.size() == 50);
		assert(vec[26] == 9000);
		assert(vec[49] == 9000);
	}
}

static void test_constr_iter()
{
	{
		int array[0] = {};

		NS::vector<int> vec(array, array);
		assert(vec.size() == 0);
	}
	{
		int array[5] = {0, 1, 2, 3, 4};

		NS::vector<int> vec(array, array + 5);
		assert(vec.size() == 5);
		assert(vec[0] == 0);
		assert(vec[1] == 1);
		assert(vec[2] == 2);
		assert(vec[3] == 3);
		assert(vec[4] == 4);
	}
	{
		int array[2] = {42, 43};

		NS::vector<int> vec(array, array + 2);
		assert(vec.size() == 2);
		assert(vec[0] == 42);
		assert(vec[1] == 43);
	}
}

static void test_assign_copy()
{
	NS::vector<int> vec;
	vec.push_back(int(0));
	vec.push_back(int(1));
	vec.push_back(int(2));

	NS::vector<int> vec2(vec);
	assert(vec2.size() == 3);
	assert(vec2[0] == 0);
	assert(vec2[1] == 1);
	assert(vec2[2] == 2);

	vec2.push_back(int(3));
	assert(vec.size() == 3);
	assert(vec2.size() == 4);

	NS::vector<int> vec3;
	assert(vec3.size() == 0);

	vec3 = vec2;
	assert(vec.size() == 3);
	assert(vec2.size() == 4);
	assert(vec3.size() == 4);

	vec = vec3;
	assert(vec.size() == 4);
	assert(vec2.size() == 4);
	assert(vec3.size() == 4);

	assert(vec[0] == 0);
	assert(vec[1] == 1);
	assert(vec[2] == 2);
	assert(vec[3] == 3);
	assert(vec2[0] == 0);
	assert(vec2[1] == 1);
	assert(vec2[2] == 2);
	assert(vec2[3] == 3);
	assert(vec3[0] == 0);
	assert(vec3[1] == 1);
	assert(vec3[2] == 2);
	assert(vec3[3] == 3);
}

static void test_accessors()
{
	NS::vector<int> vec;
	vec.push_back(int(0));
	vec.push_back(int(1));
	vec.push_back(int(2));

	assert(vec[0] == 0);
	assert(vec[1] == 1);
	assert(vec[2] == 2);

	assert(vec.at(0) == 0);
	assert(vec.at(1) == 1);
	assert(vec.at(2) == 2);

	bool exception = false;
	try
	{
		vec.at(3);
	}
	catch (const std::out_of_range &e)
	{
		exception = true;
	}
	assert(exception);

	assert(vec.front() == 0);
	assert(vec.back() == 2);
}

static void test_capacity()
{
	NS::vector<int> vec;
	assert(vec.empty());
	assert(vec.size() == 0);

	vec.push_back(int(0));
	vec.push_back(int(1));
	vec.push_back(int(2));

	assert(!vec.empty());
	assert(vec.size() == 3);

	vec.reserve(50);
	assert(vec.capacity() >= 50);
	vec.reserve(50);
	assert(vec.capacity() >= 50);
	vec.reserve(20);
	assert(vec.capacity() >= 50);
	vec.reserve(10);
	assert(vec.capacity() >= 50);
	vec.reserve(0);
	assert(vec.capacity() >= 50);
	vec.reserve(60);
	assert(vec.capacity() >= 60);
	vec.reserve(10);
	assert(vec.capacity() >= 60);
	vec.reserve(0);
	assert(vec.capacity() >= 60);

	vec.clear();
	assert(vec.size() == 0);
	assert(vec.empty());
	assert(vec.capacity() >= 60);
}

static void test_iterator()
{
	NS::vector<int> vec;
	assert(vec.size() == 0);
	assert(vec.begin() == vec.end());

	vec.push_back(int(0));
	assert(vec.size() == 1);
	assert(vec.begin() + 1 == vec.end());

	vec.push_back(int(1));
	assert(vec.size() == 2);
	assert(vec.begin() + 2 == vec.end());

	vec.push_back(int(2));
	assert(vec.size() == 3);
	assert(vec.begin() + 3 == vec.end());
	assert(vec.begin() == vec.end() - 3);

	const NS::vector<int> &vec2 = vec;

	NS::vector<int>::const_iterator ite = vec2.begin();
	assert((*ite) == 0);
	assert(*ite == 0);
	assert(++ite == vec2.begin() + 1);
	assert((*ite) == 1);
	assert(*ite == 1);
	assert(ite++ == vec2.begin() + 1);
	assert(ite == vec2.begin() + 2);
	assert((*ite) == 2);
	assert(*ite == 2);
	assert(++ite == vec2.end());
	assert(--ite == vec2.end() - 1);
	assert(*ite == 2);
	assert(ite-- == vec2.end() - 1);
	assert(ite == vec2.end() - 2);
	assert(*ite == 1);
	assert(--ite == vec2.begin());
	assert(*ite == 0);
}

static void test_reverse_iterator()
{
	NS::vector<int> vec;
	vec.push_back(int(0));
	vec.push_back(int(1));
	vec.push_back(int(2));

	NS::vector<int>::reverse_iterator ite =
		vec.rbegin();
	assert(*ite == 2);
	++ite;
	assert(*ite == 1);
	++ite;
	assert(*ite == 0);
	++ite;
	assert(ite == vec.rend());
}

static void test_insert_one()
{
	NS::vector<int> vec;

	vec.reserve(2);
	assert(vec.insert(vec.begin(), int(5)) == vec.begin());
	assert(vec.size() == 1);
	assert(vec[0] == 5);

	assert(vec.insert(vec.begin() + 1, int(5)) == vec.begin() + 1);
	assert(vec.size() == 2);
	assert(vec[1] == 5);
}

static void test_insert()
{
	NS::vector<int> vec;
	vec.reserve(12);
	assert(vec.size() == 0);

	vec.insert(vec.begin(), 0, int(66));
	assert(vec.size() == 0);

	vec.insert(vec.begin(), 10, int(120));
	assert(vec.size() == 10);
	assert(vec[2] == 120);
	assert(vec[9] == 120);

	vec.insert(vec.begin() + 3, 2, int(33));
	assert(vec.size() == 12);
	assert(vec[3] == 33);
	assert(vec[6] == 120);
}

static void test_insert_iter()
{
	NS::vector<int> vec;
	vec.reserve(7);
	assert(vec.size() == 0);

	{
		int array[5] = {0, 1, 2, 3, 4};

		vec.insert(vec.begin(), array, array + 5);
		assert(vec.size() == 5);
		assert(vec[0] == 0);
		assert(vec[1] == 1);
		assert(vec[2] == 2);
		assert(vec[3] == 3);
		assert(vec[4] == 4);
	}
	{
		int array[0] = {};

		vec.insert(vec.begin() + 2, array, array);
		assert(vec.size() == 5);
	}
	{
		int array[2] = {42, 43};

		vec.insert(vec.begin() + 2, array, array + 2);
		assert(vec.size() == 7);
		assert(vec[0] == 0);
		assert(vec[1] == 1);
		assert(vec[2] == 42);
		assert(vec[3] == 43);
		assert(vec[4] == 2);
		assert(vec[5] == 3);
		assert(vec[6] == 4);
	}
}

static void test_erase()
{
	NS::vector<int> vec;
	int array[5] = {0, 1, 2, 3, 4};
	vec.insert(vec.begin(), array, array + 5);

	assert(vec.erase(vec.begin()) == vec.begin());
	assert(vec.size() == 4);
	assert(vec[0] == 1);

	assert(vec.erase(vec.begin() + 2) == vec.begin() + 2);
	assert(vec.size() == 3);
	assert(vec[2] == 4);
}

static void test_erase_range()
{
	NS::vector<int> vec;
	int array[5] = {0, 1, 2, 3, 4};
	vec.insert(vec.begin(), array, array + 5);

	vec.erase(vec.begin() + 1, vec.end() - 1);
	assert(vec.size() == 2);
	assert(vec[0] == 0);
	assert(vec[1] == 4);

	vec.erase(vec.begin(), vec.begin());
	assert(vec.size() == 2);
	assert(vec[0] == 0);
	assert(vec[1] == 4);
}

static void test_pop_back()
{
	NS::vector<int> vec;
	int array[5] = {0, 1, 2, 3, 4};
	vec.insert(vec.begin(), array, array + 5);

	assert(vec.size() == 5);
	vec.pop_back();
	assert(vec.size() == 4);
	vec.pop_back();
	assert(vec.size() == 3);
	vec.pop_back();
	assert(vec.size() == 2);
	vec.pop_back();
	assert(vec.size() == 1);
	vec.pop_back();
	assert(vec.size() == 0);
}

static void test_resize()
{
	NS::vector<int> vec;

	vec.resize(3, int(0));
	assert(vec.size() == 3);
	assert(vec[0] == 0);
	assert(vec[1] == 0);
	assert(vec[2] == 0);

	vec.resize(2, int(5));
	assert(vec.size() == 2);
	assert(vec[0] == 0);
	assert(vec[1] == 0);

	vec.resize(5, int(99));
	assert(vec.size() == 5);
	assert(vec[0] == 0);
	assert(vec[1] == 0);
	assert(vec[2] == 99);
	assert(vec[3] == 99);
	assert(vec[4] == 99);
}

static void test_swap()
{
	int array[5] = {0, 1, 2, 3, 4};
	NS::vector<int> vec(array, array + 5);

	int array2[3] = {2, 3, 1};
	NS::vector<int> vec2(array2, array2 + 3);

	vec.swap(vec2);
	assert(vec.size() == 3);
	assert(vec2.size() == 5);
	assert(vec[0] == 2);
	assert(vec2[0] == 0);

	ft::swap(vec2, vec);
	assert(vec.size() == 5);
	assert(vec2.size() == 3);
	assert(vec[0] == 0);
	assert(vec2[0] == 2);
}

static void test_cmp_eq()
{
	int array[5] = {0, 1, 2, 3, 4};
	NS::vector<int> vec(array, array + 5);
	NS::vector<int> vec2(vec);

	assert(vec == vec2);
	assert(vec >= vec2);
	assert(vec <= vec2);

	vec2.push_back(50);
	assert(vec != vec2);
	assert(vec < vec2);
	assert(vec <= vec2);
	assert(vec2 > vec);
	assert(vec2 >= vec);

	vec.push_back(200);
	assert(vec != vec2);
	assert(vec > vec2);
	assert(vec >= vec2);
	assert(vec2 < vec);
	assert(vec2 <= vec);
}

void test_vector()
{
	test_pushback();
	test_assign();
	test_assign_iter();
	test_constr();
	test_constr_iter();
	test_assign_copy();
	test_accessors();
	test_capacity();
	test_iterator();
	test_reverse_iterator();
	test_insert_one();
	test_insert();
	test_insert_iter();
	test_erase();
	test_erase_range();
	test_pop_back();
	test_resize();
	test_swap();
	test_cmp_eq();
}
