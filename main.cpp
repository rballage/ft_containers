// #include "containers/list.hpp"
// #include "containers/map.hpp"
// #include "containers/queue.hpp"
// #include "containers/stack.hpp"
#include <cassert>
#include "containers/vector.hpp"
#include "Test.hpp"
#include <vector>
#include <sstream>

std::string vector_reserve_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using endl;
	vector<int> vec(10, 255);
	// vector<int> vec2;
	// int i = 0;
	out << vec.capacity() << endl;

	vec.reserve(10);
	out << vec.capacity() << endl;

	res = out.str();
	return res;
}
std::string vector_reserve_std(void)
{
	std::string res;
	std::ostringstream out;
	using std::vector;
	using endl;
	vector<int> vec(10, 255);
	// vector<int> vec2;
	// int i = 0;
	out << vec.capacity() << endl;

	vec.reserve(10);
	out << vec.capacity() << endl;

	res = out.str();
	return res;
}
std::string vector_at_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using endl;
	vector<int> vec(10, 255);
	vector<int> vec2;
	int i = 0;
	while (i != 10) {
		out << "vec: "<< vec.at(i++) << endl;
	}
	try {
		out << "vec: "<< vec.at(-1) << endl;
	}
	catch (const std::exception& e) {
		(void)e;out << "test" << endl;
	}
	try {
		out << "vec: "<< vec.at(100) << endl;
	}
	catch (const std::exception& e) {
		(void)e;out << "test" << endl;
	}
	try {
		out << "vec: "<< vec2.at(0) << endl;
	}
	catch (const std::exception& e) {
		(void)e;out << "test" << endl;
	}
	try {
		out << "vec: "<< vec2.at(100) << endl;
	}
	catch (const std::exception& e) {
		(void)e;out << "test" << endl;
	}
	res = out.str();
	return res;
}
std::string vector_at_std(void)
{
	std::string res;
	std::ostringstream out;
	using std::vector;
	using endl;
	vector<int> vec(10, 255);
	vector<int> vec2;
	int i = 0;
	while (i != 10) {
		out << "vec: "<< vec.at(i++) << endl;
	}
	try {
		out << "vec: "<< vec.at(-1) << endl;
	}
	catch (const std::exception& e) {
		(void)e;out << "test" << endl;
	}
	try {
		out << "vec: "<< vec.at(100) << endl;
	}
	catch (const std::exception& e) {
		(void)e;out << "test" << endl;
	}
	try {
		out << "vec: "<< vec2.at(0) << endl;
	}
	catch (const std::exception& e) {
		(void)e;out << "test" << endl;
	}
	try {
		out << "vec: "<< vec2.at(100) << endl;
	}
	catch (const std::exception& e) {
		(void)e;out << "test" << endl;
	}
	res = out.str();
	return res;
}

std::string vector_constructions_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using endl;
	vector<int> vec(10, 255);
	vector<int> vec2(vec);

	vector<int>::iterator it = vec.begin();
	vector<int>::iterator end = vec.end();
	while (it != end) {
		out << "vec: "<< *it << endl; it++;
	}
	it = vec2.begin();
	end = vec2.end();
	while (it != end) {
		out << "vec2: " << *it << endl; it++;
	}
	res = out.str();
	return res;
}
std::string vector_constructions_std(void)
{
	std::string res;
	std::ostringstream out;
	using std::vector;
	using std::cout;
	using endl;
	vector<int> vec(10, 255);
	vector<int> vec2(vec);

	vector<int>::iterator it = vec.begin();
	vector<int>::iterator end = vec.end();
	while (it != end) {
		out << "vec: "<< *it << endl; it++;
	}
	it = vec2.begin();
	end = vec2.end();
	while (it != end) {
		out << "vec2: " << *it << endl; it++;
	}
	res = out.str();
	return res;
}
std::string vector_clear_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using endl;

	vector<int> vec(10, 255);
	out << vec.size() << endl;
	vec.clear();
	out << vec.size() << endl;
	vector<int> vec2(1, 255);
	out << vec2.size() << endl;
	vec2.clear();
	out << vec2.size() << endl;
	vector<int> vec3;
	out << vec3.size() << endl;
	vec3.clear();
	out << vec3.size() << endl;

	res = out.str();
	return res;
}
std::string vector_clear_std(void)
{
	std::string res;
	std::ostringstream out;
	using std::vector;
	using std::cout;
	using endl;
	vector<int> vec(10, 255);
	out << vec.size() << endl;
	vec.clear();
	out << vec.size() << endl;
	vector<int> vec2(1, 255);
	out << vec2.size() << endl;
	vec2.clear();
	out << vec2.size() << endl;
	vector<int> vec3;
	out << vec3.size() << endl;
	vec3.clear();
	out << vec3.size() << endl;
	res = out.str();
	return res;
}

std::string vector_empty_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using endl;

	vector<int> vec(10, 255);
	out << vec.empty() << endl;
	vec.clear();
	out << vec.empty() << endl;
	vector<int> vec2(1, 255);
	out << vec2.empty() << endl;
	vec2.clear();
	out << vec2.empty() << endl;
	vector<int> vec3;
	out << vec3.empty() << endl;
	vec3.clear();
	out << vec3.empty() << endl;

	res = out.str();
	return res;
}
std::string vector_empty_std(void)
{
	std::string res;
	std::ostringstream out;
	using std::vector;
	using std::cout;
	using endl;

	vector<int> vec(10, 255);
	out << vec.empty() << endl;
	vec.clear();
	out << vec.empty() << endl;
	vector<int> vec2(1, 255);
	out << vec2.empty() << endl;
	vec2.clear();
	out << vec2.empty() << endl;
	vector<int> vec3;
	out << vec3.empty() << endl;
	vec3.clear();
	out << vec3.empty() << endl;

	res = out.str();
	return res;
}

std::string vector_push_back_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using endl;

	{
		vector<int> vec(10, 255);
	// vec.clear();
		vec.push_back(5);
		vec.push_back(5);
		vec.push_back(5);
		out << vec.capacity() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		while (it != end) {
			out << "vec: "<< *it << endl; it++;
		}
	}
	{
		vector<int> vec(10, 255);
		vec.clear();
		vec.push_back(5);
		out << vec.capacity() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		while (it != end) {
			out << "vec: "<< *it << endl; it++;
		}
	}
	// out << vec.empty() << endl;
	// vector<int> vec2(1, 255);
	// out << vec2.empty() << endl;
	// vec2.clear();
	// out << vec2.empty() << endl;
	// vector<int> vec3;
	// out << vec3.empty() << endl;
	// vec3.clear();
	// out << vec3.empty() << endl;

	res = out.str();
	return res;
}
std::string vector_push_back_std(void)
{
	std::string res;
	std::ostringstream out;
	using std::vector;
	using std::cout;
	using endl;

	{
		vector<int> vec(10, 255);
	// vec.clear();
		vec.push_back(5);
		vec.push_back(5);
		vec.push_back(5);
		out << vec.capacity() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		while (it != end) {
			out << "vec: "<< *it << endl; it++;
		}
	}
	{
		vector<int> vec(10, 255);
		vec.clear();
		vec.push_back(5);
		out << vec.capacity() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		while (it != end) {
			out << "vec: "<< *it << endl; it++;
		}
	}
	// out << vec.empty() << endl;
	// vector<int> vec2(1, 255);
	// out << vec2.empty() << endl;
	// vec2.clear();
	// out << vec2.empty() << endl;
	// vector<int> vec3;
	// out << vec3.empty() << endl;
	// vec3.clear();
	// out << vec3.empty() << endl;

	res = out.str();
	return res;
}
std::string vector_resize_std(void)
{
	std::string res;
	std::ostringstream out;
	using std::vector;
	using std::cout;
	using endl;

	{
		vector<int> vec(1, 0);
	// vec.clear();
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(7);
	vec.push_back(8);
	vec.push_back(9);
	vec.push_back(10);
		out << "capacity: "<< vec.capacity() << endl;
		out << "size: "<< vec.size() << endl;
		out << "resizing to smaller size.\n";
		vec.resize(2);
		out << "capacity: "<< vec.capacity() << endl;
		out << "size: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		while (it != end) {
			out << "vec: "<< *it << endl; it++;
		}
	}
	{
		vector<int> vec(10, 255);
		out << "capacity: "<< vec.capacity() << endl;
		out << "size: "<< vec.size() << endl;
		out << "resizing to bigger size.\n";
		vec.resize(20);
		out << "capacity: "<< vec.capacity() << endl;
		out << "size: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		while (it != end) {
			out << "vec: "<< *it << endl; it++;
		}
	}
	res = out.str();
	return res;
}
std::string vector_resize_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using std::cout;
	using endl;

	{
		vector<int> vec(1,0);
	// vec.clear();
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(7);
	vec.push_back(8);
	vec.push_back(9);
	vec.push_back(10);
		out << "capacity: "<< vec.capacity() << endl;
		out << "size: "<< vec.size() << endl;
		out << "resizing to smaller size.\n";
		vec.resize(2);
		out << "capacity: "<< vec.capacity() << endl;
		out << "size: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		while (it != end) {
			out << "vec: "<< *it << endl; it++;
		}
	}
	{
		vector<int> vec(10, 255);
		out << "capacity: "<< vec.capacity() << endl;
		out << "size: "<< vec.size() << endl;
		out << "resizing to bigger size.\n";
		vec.resize(20);
		out << "capacity: "<< vec.capacity() << endl;
		out << "size: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		while (it != end) {
			out << "vec: "<< *it << endl; it++;
		}
	}
	res = out.str();
	return res;
}
std::string vector_insert_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using std::cout;
	using endl;

	{
		vector<int> vec(5,0);

		out << "capacity: "<< vec.capacity() << endl;
		vec.insert(vec.begin()+1,2, 111);
		out << "capacity: "<< vec.capacity() << endl;
		vec.insert(vec.begin()+2,2, 222);
		out << "capacity: "<< vec.capacity() << endl;
		vec.insert(vec.begin()+4,15, 444);
		out << "capacity: "<< vec.capacity() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		while (it != end) {
			out << "vec: "<< *it << endl; it++;
		}
		out << "size: "<< vec.size() << endl<< endl;
	}
	{
		vector<int> vec(5,0);
		vector<int>::iterator test;
		out << "capacity: "<< vec.capacity() << endl;
		test = vec.insert(vec.begin()+1, 111);
		out << "capacity: "<< vec.capacity() << "\t | returned iterator value:"<< *test << endl;
		test = vec.insert(vec.begin()+2, 222);
		out << "capacity: "<< vec.capacity() << "\t | returned iterator value:"<< *test << endl;
		test = vec.insert(vec.begin()+4, 444);
		out << "capacity: "<< vec.capacity() << "\t | returned iterator value:"<< *test << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		while (it != end) {
			out << "vec: "<< *it << endl; it++;
		}
		out << "size: "<< vec.size() << endl<< endl;
	}
	{
		vector<int> vec;
		vector<int>::iterator test;
		out << "capacity: "<< vec.capacity() << endl;
		test = vec.insert(vec.begin(), 111);
		out << "capacity: "<< vec.capacity() << "\t | returned iterator value:"<< *test << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		while (it != end) {
			out << "vec: "<< *it << endl; it++;
		}
		out << "size: "<< vec.size() << endl<< endl;
	}
	res = out.str();
	return res;
}
std::string vector_insert_std(void)
{
	std::string res;
	std::ostringstream out;
	using std::vector;
	using std::cout;
	using endl;

	{
		vector<int> vec(5,0);

		out << "capacity: "<< vec.capacity() << endl;
		vec.insert(vec.begin()+1,2, 111);
		out << "capacity: "<< vec.capacity() << endl;
		vec.insert(vec.begin()+2,2, 222);
		out << "capacity: "<< vec.capacity() << endl;
		vec.insert(vec.begin()+4,15, 444);
		out << "capacity: "<< vec.capacity() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		while (it != end) {
			out << "vec: "<< *it << endl; it++;
		}
		out << "size: "<< vec.size() << endl<< endl;
	}
	{
		vector<int> vec(5,0);
		vector<int>::iterator test;
		out << "capacity: "<< vec.capacity() << endl;
		test = vec.insert(vec.begin()+1, 111);
		out << "capacity: "<< vec.capacity() << "\t | returned iterator value:"<< *test << endl;
		test = vec.insert(vec.begin()+2, 222);
		out << "capacity: "<< vec.capacity() << "\t | returned iterator value:"<< *test << endl;
		test = vec.insert(vec.begin()+4, 444);
		out << "capacity: "<< vec.capacity() << "\t | returned iterator value:"<< *test << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		while (it != end) {
			out << "vec: "<< *it << endl; it++;
		}
		out << "size: "<< vec.size() << endl<< endl;
	}
	{
		vector<int> vec;
		vector<int>::iterator test;
		out << "capacity: "<< vec.capacity() << endl;
		test = vec.insert(vec.end(), 111);
		// test = vec.insert(vec.end(), 222);
		out << "capacity: "<< vec.capacity() << "\t | returned iterator value:"<< *test << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		while (it != end) {
			out << "vec: "<< *it << endl; it++;
		}
		out << "size: "<< vec.size() << endl<< endl;
	}
	res = out.str();
	return res;
}


int main(void)
{
	Test construction_test(&vector_constructions_ft, &vector_constructions_std);
	assert(construction_test.is_same());
	Test clear_test(&vector_clear_ft, &vector_clear_std);
	assert(clear_test.is_same());
	Test empty_test(&vector_empty_ft, &vector_empty_std);
	assert(empty_test.is_same());
	Test at_test(&vector_at_ft, &vector_at_std);
	assert(at_test.is_same());
	Test reserve_test(&vector_reserve_ft, &vector_reserve_std);
	assert(reserve_test.is_same());
	Test push_back_test(&vector_push_back_ft, &vector_push_back_std);
	// push_back_test.printAll();
	assert(push_back_test.is_same());
	Test resize_test(&vector_resize_ft, &vector_resize_std);
	// resize_test.printAll();
	assert(resize_test.is_same());
	Test insert_test(&vector_insert_ft, &vector_insert_std);
	insert_test.printAll();
	assert(insert_test.is_same());

	// at_test.printAll();

	return 0;
}
