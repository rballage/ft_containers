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
	using std::endl;
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
	using std::endl;
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
	using std::endl;
	vector<int> vec(10, 255);
	vector<int> vec2;
	int i = 0;
	while (i != 10) {
		out << "vec: "<< vec.at(i++) << std::endl;
	}
	try {
		out << "vec: "<< vec.at(-1) << std::endl;
	}
	catch (const std::exception& e) {
		(void)e;out << "test" << endl;
	}
	try {
		out << "vec: "<< vec.at(100) << std::endl;
	}
	catch (const std::exception& e) {
		(void)e;out << "test" << endl;
	}
	try {
		out << "vec: "<< vec2.at(0) << std::endl;
	}
	catch (const std::exception& e) {
		(void)e;out << "test" << endl;
	}
	try {
		out << "vec: "<< vec2.at(100) << std::endl;
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
	using std::endl;
	vector<int> vec(10, 255);
	vector<int> vec2;
	int i = 0;
	while (i != 10) {
		out << "vec: "<< vec.at(i++) << std::endl;
	}
	try {
		out << "vec: "<< vec.at(-1) << std::endl;
	}
	catch (const std::exception& e) {
		(void)e;out << "test" << endl;
	}
	try {
		out << "vec: "<< vec.at(100) << std::endl;
	}
	catch (const std::exception& e) {
		(void)e;out << "test" << endl;
	}
	try {
		out << "vec: "<< vec2.at(0) << std::endl;
	}
	catch (const std::exception& e) {
		(void)e;out << "test" << endl;
	}
	try {
		out << "vec: "<< vec2.at(100) << std::endl;
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
	using std::endl;
	vector<int> vec(10, 255);
	vector<int> vec2(vec);

	vector<int>::iterator it = vec.begin();
	vector<int>::iterator end = vec.end();
	while (it != end) {
		out << "vec: "<< *it << std::endl; it++;
	}
	it = vec2.begin();
	end = vec2.end();
	while (it != end) {
		out << "vec2: " << *it << std::endl; it++;
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
	using std::endl;
	vector<int> vec(10, 255);
	vector<int> vec2(vec);

	vector<int>::iterator it = vec.begin();
	vector<int>::iterator end = vec.end();
	while (it != end) {
		out << "vec: "<< *it << std::endl; it++;
	}
	it = vec2.begin();
	end = vec2.end();
	while (it != end) {
		out << "vec2: " << *it << std::endl; it++;
	}
	res = out.str();
	return res;
}
std::string vector_clear_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using std::endl;

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
	using std::endl;
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
	using std::endl;

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
	using std::endl;

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

	// at_test.printAll();

	return 0;
}
