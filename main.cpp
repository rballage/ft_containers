
// #include "containers/list.hpp"
// #include "containers/queue.hpp"
// #include "containers/stack.hpp"
#include <cassert>
#include "vector.hpp"
#include "Test.hpp"
#include <vector>
#include <sstream>
#include "map.hpp"
#include <cstdlib>
#include <ctime>

std::string vector_reserve_ft()
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
	using std::endl;
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
	using std::endl;
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
	using std::endl;
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
	{
		vector<int> myvector;
		int sum (0);

		for (int i=1;i<=10;i++) myvector.push_back(i);

		while (!myvector.empty())
		{
		   sum += myvector.back();
		   myvector.pop_back();
		}

		out << "total: " << sum << '\n';

	}
	res = out.str();
	return res;
}
std::string vector_empty_std(void)
{
	std::string res;
	std::ostringstream out;
	using std::vector;
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
	{
		vector<int> myvector;
		int sum (0);

		for (int i=1;i<=10;i++) myvector.push_back(i);

		while (!myvector.empty())
		{
		   sum += myvector.back();
		   myvector.pop_back();
		}

		out << "total: " << sum << '\n';

	}
	res = out.str();
	return res;
}

std::string vector_push_back_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using std::endl;

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
	using std::endl;

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
	using std::endl;

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
	using std::endl;

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
std::string vector_size_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using std::endl;

		vector<int> vec(1);
	// vec.clear();
    out << "0. size: " << vec.size() << '\n';

    for (int i=0; i<10; i++) vec.push_back(i);
    out << "1. size: " << vec.size() << '\n';

    vec.insert (vec.end()-1,10,100);
    out << "2. size: " << vec.size() << '\n';

    vec.pop_back();
	out << "3. size: " << vec.size() << '\n';
	{
		vector<int> myints;
		out << "0. size: " << myints.size() << '\n';

		for (int i=0; i<10; i++) myints.push_back(i);
		out << "1. size: " << myints.size() << '\n';

		myints.insert (myints.end(),10,100);
		out << "2. size: " << myints.size() << '\n';

		myints.pop_back();
		out << "3. size: " << myints.size() << '\n';
	}

	res = out.str();
	return res;
}
std::string vector_size_std(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using std::endl;

	vector<int> vec(1);
	// vec.clear();
    out << "0. size: " << vec.size() << '\n';

    for (int i=0; i<10; i++) vec.push_back(i);
    out << "1. size: " << vec.size() << '\n';

    vec.insert (vec.end()-1,10,100);
    out << "2. size: " << vec.size() << '\n';

    vec.pop_back();
	out << "3. size: " << vec.size() << '\n';
	{
		vector<int> myints;
		out << "0. size: " << myints.size() << '\n';

		for (int i=0; i<10; i++) myints.push_back(i);
		out << "1. size: " << myints.size() << '\n';

		myints.insert (myints.end(),10,100);
		out << "2. size: " << myints.size() << '\n';

		myints.pop_back();
		out << "3. size: " << myints.size() << '\n';
	}

	res = out.str();
	return res;
}
std::string vector_insert_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using std::endl;

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
	{
		vector<int> myvector (3,100);
		vector<int>::iterator it;

		it = myvector.begin();
		it = myvector.insert ( it , 200 );

		// myvector.insert (it,2,300);
		//
		// // "it" no longer valid, get a new one:
		it = myvector.begin();
		//
		vector<int> anothervector (2,400);
		myvector.insert (it+2,anothervector.begin(),anothervector.end());
		//
		int myarray [] = { 501,502,503 };
		myvector.insert (myvector.begin(), myarray, myarray+3);

		out << "myvector contains:";
		for (it=myvector.begin(); it<myvector.end(); it++)
		  out << ' ' << *it;
		out << '\n';
	}
	res = out.str();
	return res;
}
std::string vector_insert_std(void)
{
	std::string res;
	std::ostringstream out;
	using std::vector;
	using std::endl;

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
	{
		vector<int> myvector (3,100);
		vector<int>::iterator it;

		it = myvector.begin();
		it = myvector.insert ( it , 200 );

		myvector.insert (it,2,300);

		// "it" no longer valid, get a new one:
		it = myvector.begin();

		vector<int> anothervector (2,400);
		myvector.insert (it+2,anothervector.begin(),anothervector.end());

		int myarray [] = { 501,502,503 };
		myvector.insert (myvector.begin(), myarray, myarray+3);

		out << "myvector contains:";
		for (it=myvector.begin(); it<myvector.end(); it++)
		  out << ' ' << *it;
		out << '\n';
	}
	res = out.str();
	return res;
}
std::string vector_erase_std(void)
{
	std::string res;
	std::ostringstream out;
	using std::vector;
	using std::endl;

	{
		vector<int> vec; 	vec.push_back(1);vec.push_back(2);vec.push_back(3);vec.push_back(4);vec.push_back(5);vec.push_back(6);vec.push_back(7);vec.push_back(8);vec.push_back(9);vec.push_back(10);

		out << "erase first elem \nsize: "<< vec.size() << endl;
		vec.erase(vec.begin());
		out << "size after erase: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		out << "vec: ";

		while (it != end) {
			out << ", " << *it++;
		}
		out << endl;
	}
	{
		vector<int> vec; 	vec.push_back(1);vec.push_back(2);vec.push_back(3);vec.push_back(4);vec.push_back(5);vec.push_back(6);vec.push_back(7);vec.push_back(8);vec.push_back(9);vec.push_back(10);

		out << "erase first elem \nsize: "<< vec.size() << endl;
		vec.erase(vec.begin() + 1);
		vec.erase(vec.begin() + 3);
		out << "size after erase: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		out << "vec: ";

		while (it != end) {
			out << ", " << *it++;
		}
		out << endl;
	}
	{
		vector<int> vec; 	vec.push_back(1);//vec.push_back(2);vec.push_back(3);vec.push_back(4);vec.push_back(5);vec.push_back(6);vec.push_back(7);vec.push_back(8);vec.push_back(9);vec.push_back(10);

		out << "erase first elem \nsize: "<< vec.size() << endl;
		vec.erase(vec.begin());
		out << "size after erase: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		out << "vec: ";

		while (it != end) {
			out << ", " << *it++;
		}
		out << endl;
	}

	res = out.str();
	return res;
}
std::string vector_erase_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using std::endl;

	{
		vector<int> vec; 	vec.push_back(1);vec.push_back(2);vec.push_back(3);vec.push_back(4);vec.push_back(5);vec.push_back(6);vec.push_back(7);vec.push_back(8);vec.push_back(9);vec.push_back(10);

		out << "erase first elem \nsize: "<< vec.size() << endl;
		vec.erase(vec.begin());
		out << "size after erase: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		out << "vec: ";

		while (it != end) {
			out << ", " << *it++;
		}
		out << endl;
	}
	{
		vector<int> vec; 	vec.push_back(1);vec.push_back(2);vec.push_back(3);vec.push_back(4);vec.push_back(5);vec.push_back(6);vec.push_back(7);vec.push_back(8);vec.push_back(9);vec.push_back(10);

		out << "erase first elem \nsize: "<< vec.size() << endl;
		vec.erase(vec.begin() + 1);
		vec.erase(vec.begin() + 3);
		out << "size after erase: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		out << "vec: ";

		while (it != end) {
			out << ", " << *it++;
		}
		out << endl;
	}
	{
		vector<int> vec; 	vec.push_back(1);//vec.push_back(2);vec.push_back(3);vec.push_back(4);vec.push_back(5);vec.push_back(6);vec.push_back(7);vec.push_back(8);vec.push_back(9);vec.push_back(10);

		out << "erase first elem \nsize: "<< vec.size() << endl;
		vec.erase(vec.begin());
		out << "size after erase: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		out << "vec: ";

		while (it != end) {
			out << ", " << *it++;
		}
		out << endl;
	}

	res = out.str();
	return res;
}
std::string vector_erase_range_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using std::endl;

	{
		vector<int> vec; 	vec.push_back(1);vec.push_back(2);vec.push_back(3);vec.push_back(4);vec.push_back(5);vec.push_back(6);vec.push_back(7);vec.push_back(8);vec.push_back(9);vec.push_back(10);

		out << "erase first elem \nsize: "<< vec.size() << endl;
		vec.erase(vec.begin(), vec.begin() + 3);
		out << "size after erase: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		out << "vec: ";

		while (it != end) {
			out << ", " << *it++;
		}
		out << endl;
	}
	{
		vector<int> vec; 	vec.push_back(1);vec.push_back(2);vec.push_back(3);vec.push_back(4);vec.push_back(5);vec.push_back(6);vec.push_back(7);vec.push_back(8);vec.push_back(9);vec.push_back(10);

		out << "erase first elem \nsize: "<< vec.size() << endl;
		vec.erase(vec.begin(), vec.end() - 3);
		out << "size after erase: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		out << "vec: ";

		while (it != end) {
			out << ", " << *it++;
		}
		out << endl;
	}
	{
		vector<int> vec; 	vec.push_back(1);vec.push_back(2);vec.push_back(3);vec.push_back(4);vec.push_back(5);vec.push_back(6);vec.push_back(7);vec.push_back(8);vec.push_back(9);vec.push_back(10);

		out << "erase first elem \nsize: "<< vec.size() << endl;
		vec.erase(vec.begin(), vec.end());
		out << "size after erase: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		out << "vec: ";

		while (it != end) {
			out << ", " << *it++;
		}
		out << endl;
	}
	res = out.str();
	return res;
}
std::string vector_erase_range_std(void)
{
	std::string res;
	std::ostringstream out;
	using std::vector;
	using std::endl;
	{
		vector<int> vec; 	vec.push_back(1);vec.push_back(2);vec.push_back(3);vec.push_back(4);vec.push_back(5);vec.push_back(6);vec.push_back(7);vec.push_back(8);vec.push_back(9);vec.push_back(10);

		out << "erase first elem \nsize: "<< vec.size() << endl;
		vec.erase(vec.begin(), vec.begin() + 3);
		out << "size after erase: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		out << "vec: ";

		while (it != end) {
			out << ", " << *it++;
		}
		out << endl;
	}
	{
		vector<int> vec; 	vec.push_back(1);vec.push_back(2);vec.push_back(3);vec.push_back(4);vec.push_back(5);vec.push_back(6);vec.push_back(7);vec.push_back(8);vec.push_back(9);vec.push_back(10);

		out << "erase first elem \nsize: "<< vec.size() << endl;
		vec.erase(vec.begin(), vec.end() - 3);
		out << "size after erase: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		out << "vec: ";

		while (it != end) {
			out << ", " << *it++;
		}
		out << endl;
	}
	{
		vector<int> vec; 	vec.push_back(1);vec.push_back(2);vec.push_back(3);vec.push_back(4);vec.push_back(5);vec.push_back(6);vec.push_back(7);vec.push_back(8);vec.push_back(9);vec.push_back(10);

		out << "erase first elem \nsize: "<< vec.size() << endl;
		vec.erase(vec.begin(), vec.end());
		out << "size after erase: "<< vec.size() << endl;
		vector<int>::iterator it = vec.begin();
		vector<int>::iterator end = vec.end();
		out << "vec: ";

		while (it != end) {
			out << ", " << *it++;
		}
		out << endl;
	}

	res = out.str();
	return res;
}
std::string vector_strings_general_std(void)
{
	std::string res;
	std::ostringstream out;
	using std::vector;
	using std::endl;
	{
		vector<std::string> vec;
		out<< vec.size()<< endl;
	}
	{
		vector<std::string> vec(10, "hello");
		out<< vec.size()<< endl;
		for (size_t i = 0; i < vec.size(); i++) {
			out << "["<< vec[i] <<"]" <<endl;
		}
	}
	{
		std::string test("test");
		vector<std::string> vec(10, test);
		out<< vec.size()<< endl;
		for (size_t i = 0; i < vec.size(); i++) {
			out << "["<< vec[i] <<"]" <<endl;
		}
	}
	res = out.str();
	return res;
}

std::string vector_strings_general_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using std::endl;
	{
		vector<std::string> vec;
		out<< vec.size()<< endl;
	}
	{
		vector<std::string> vec(10, "hello");
		out<< vec.size()<< endl;
		for (size_t i = 0; i < vec.size(); i++) {
			out << "["<< vec[i] <<"]" <<endl;
		}
	}
	{
		std::string test("test");
		vector<std::string> vec(10, test);
		out<< vec.size()<< endl;
		for (size_t i = 0; i < vec.size(); i++) {
			out << "["<< vec[i] <<"]" <<endl;
		}
	}

	res = out.str();
	return res;
}

std::string vector__ft(void)
{
	std::string res;
	std::ostringstream cout;
	using ft::vector;
	using std::endl;
	vector<int> JOHN;
	vector<int> BOB(5, 8);
	cout << "BOB(5, 8) : ";
	for (size_t i = 0; i < BOB.size(); i++)
		cout << BOB[i] << ' ';
	cout << '\n';
	vector<int> MIKE(BOB);

	// CTORs
	cout << "\nCTORS\n";
	cout << "Empty is empty ? " << std::boolalpha << JOHN.empty() << '\n';
	cout << "BOB is empty? " << BOB.empty() << '\n';

	cout << "Size of JOHN " << JOHN.size() << std::endl;
	cout << "Size of BOB " << BOB.size() << std::endl;
	cout << "Size of MIKE " << MIKE.size() << std::endl;


	// RESIZE
	size_t	bob_resize = 2;
	cout << "\nRESIZE\n";
	BOB.resize(bob_resize);
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 53\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_resize)
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 58\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 63\n";

	size_t	mike_resize = 9;
	bob_resize = 0;

	BOB.resize(bob_resize);
	cout << "BOB is empty now ? " << BOB.empty() << '\n';
	MIKE.resize(mike_resize, 3);
	/*






	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 86\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_resize)
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 91\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= mike_resize)
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 96\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	// RESERVE
	cout << "\nRESERVE\n";

	size_t	john_reserve = 5;
	size_t	bob_reserve = 3;
	size_t	mike_reserve = 83;

	JOHN.reserve(john_reserve);
	BOB.reserve(bob_reserve);
	MIKE.reserve(mike_reserve);
	/*






	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= john_reserve)
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 120\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_reserve)
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 125\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= mike_reserve)
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 130\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	//AT
	cout << "\nAT\n";
	try
	{
		cout << MIKE.at(2) << '\n';
		cout << MIKE.at(87) << '\n';
	}
	catch (std::out_of_range& oor)
	{
		(void)oor;
		cout << "OOR error caught\n";
	}

	// FRONT / BACK
	cout << "\nFRONT / BACK\n";
	cout << "front() of MIKE : " << MIKE.front() << '\n';
	cout << "back() of MIKE : " << MIKE.back() << '\n';

	//ASSIGN
	cout << "\nASSIGN\n";
	BOB.assign(42, 7);

	//ASSIGN RANGE
	cout << "\nASSIGN RANGE\n";
	vector<int>	assign_range;
	assign_range.assign(8, 5);
	assign_range.assign(BOB.begin() + 1, BOB.end() - 2);

	//EMPTY
	cout << "\nEMPTY\n";
	cout << "BOB is empty ? " << BOB.empty() << '\n';
	cout << "BOB at(41) : " << BOB.at(41) << '\n';

	//PUSH/POP_BACK
	cout << "\nPUSH/POP_BACK\n";
	BOB.push_back(53);
	cout << "last elem of BOB : " << BOB.back() << '\n';
	BOB.pop_back();
	cout << "last elem of BOB : " << BOB.back() << '\n';

	//INSERT
	cout << "\nINSERT\n";
	vector<int>	insert_in_me;
	for (int i = 0; i < 15; i++)
		insert_in_me.push_back(i);
	for (size_t i = 0; i < insert_in_me.size(); i++)
		cout << insert_in_me.at(i) << ' ';
	cout << '\n';

	vector<int>::iterator	tmp;
	tmp = insert_in_me.begin() + 4;
	insert_in_me.insert(tmp, 8, 42);
	for (size_t i = 0; i < insert_in_me.size(); i++)
		cout << insert_in_me.at(i) << ' ';
	cout << '\n';

	vector<int>::const_iterator const_it(insert_in_me.begin());
	cout << "Const it : " << std::endl;
	cout << *const_it << '\n';
//	*const_it = 89; // Does not compile because it's a const_iterator


	//INSERT
	cout << "\nINSERT\n";
	vector<int>	std_insert_in_me;
	for (int i = 0; i < 15; i++)
		std_insert_in_me.push_back(i);
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		cout << std_insert_in_me.at(i) << ' ';
	cout << '\n';

	vector<int>::iterator	std_tmp;
	std_tmp = std_insert_in_me.begin() + 4;
	std_insert_in_me.insert(std_tmp, 8, 42);
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		cout << std_insert_in_me.at(i) << ' ';
	cout << '\n';


	//INSERT RANGE
	cout << "\nINSERT RANGE\n";
	vector<int>	insert_bis;
	for (int i = 0; i < 7; i++)
		insert_bis.push_back(3 * i);
	for (size_t i = 0; i < insert_bis.size(); i++)
		cout << insert_bis[i] << ' ';
	cout << '\n';

	insert_bis.insert(insert_bis.begin() + 5, insert_in_me.begin(), insert_in_me.end());
	for (size_t i = 0; i < insert_bis.size(); i++)
		cout << insert_bis[i] << ' ';
	cout << '\n';


	//ERASE
	cout << "\nERASE\n";
	vector<int>	erase_in_me;
	for (int i = 0; i < 15; i++)
		erase_in_me.push_back(2 * i);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			cout << ' ';
		cout << erase_in_me.at(i) << ' ';
	}
	cout << '\n';

	erase_in_me.erase(erase_in_me.begin() + 7);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			cout << ' ';
		cout << erase_in_me.at(i) << ' ';
	}
	cout << '\n';

	erase_in_me.erase(erase_in_me.begin() + 2, erase_in_me.begin() + 6);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			cout << ' ';
		cout << erase_in_me.at(i) << ' ';
	}
	cout << '\n';

	//SWAP
	cout << "\nSWAP\n";
	BOB.swap(MIKE);
	/*




	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 272\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 277\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 282\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	MIKE.swap(JOHN);
	/*




	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 298\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 303\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 308\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	//CLEAR
	cout << "\nCLEAR\n";
	JOHN.clear();
	MIKE.clear();
	/*




	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 327\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 332\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 337\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	//NON MEMBER Functions
	cout << "\nNON MEMBER functions\n";
	swap(BOB, MIKE);
	/*




	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 355\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 360\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 365\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	//RELATIONAL OPERATORS
	cout << "\nRELATIONAL OPERATORS\n";
	vector<int> MIKE_2(MIKE);
	cout << "MIKE and BOB are equal ? " << (MIKE == BOB) << '\n';
	cout << "MIKE and MIKE_2 are equal ? " << (MIKE == MIKE_2) << '\n';

	cout << "\nReal Vector\n";
	// vector<int> real(5,7);
	//
	// // real.assign(5, 7);
	// for (vector<int>::iterator it = real.begin(); it != real.end(); it++)
	// 	cout << *it << " ";
	// cout << '\n';

	cout << std::endl;
	res = cout.str();
	return res;
}
std::string vector__std(void)
{
	std::string res;
	std::ostringstream cout;
	using ft::vector;
	using std::endl;
	vector<int> JOHN;
	vector<int> BOB(5, 8);
	cout << "BOB(5, 8) : ";
	for (size_t i = 0; i < BOB.size(); i++)
		cout << BOB[i] << ' ';
	cout << '\n';
	vector<int> MIKE(BOB);

	// CTORs
	cout << "\nCTORS\n";
	cout << "Empty is empty ? " << std::boolalpha << JOHN.empty() << '\n';
	cout << "BOB is empty? " << BOB.empty() << '\n';

	cout << "Size of JOHN " << JOHN.size() << std::endl;
	cout << "Size of BOB " << BOB.size() << std::endl;
	cout << "Size of MIKE " << MIKE.size() << std::endl;


	// RESIZE
	size_t	bob_resize = 2;
	cout << "\nRESIZE\n";
	BOB.resize(bob_resize);
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 53\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_resize)
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 58\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 63\n";

	size_t	mike_resize = 9;
	bob_resize = 0;

	BOB.resize(bob_resize);
	cout << "BOB is empty now ? " << BOB.empty() << '\n';
	MIKE.resize(mike_resize, 3);
	/*






	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 86\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_resize)
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 91\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= mike_resize)
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 96\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	// RESERVE
	cout << "\nRESERVE\n";

	size_t	john_reserve = 5;
	size_t	bob_reserve = 3;
	size_t	mike_reserve = 83;

	JOHN.reserve(john_reserve);
	BOB.reserve(bob_reserve);
	MIKE.reserve(mike_reserve);
	/*






	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= john_reserve)
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 120\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= bob_reserve)
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 125\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= mike_reserve)
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 130\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	//AT
	cout << "\nAT\n";
	try
	{
		cout << MIKE.at(2) << '\n';
		cout << MIKE.at(87) << '\n';
	}
	catch (std::out_of_range& oor)
	{
		(void)oor;
		cout << "OOR error caught\n";
	}

	// FRONT / BACK
	cout << "\nFRONT / BACK\n";
	cout << "front() of MIKE : " << MIKE.front() << '\n';
	cout << "back() of MIKE : " << MIKE.back() << '\n';

	//ASSIGN
	cout << "\nASSIGN\n";
	BOB.assign(42, 7);

	//ASSIGN RANGE
	cout << "\nASSIGN RANGE\n";
	vector<int>	assign_range;
	assign_range.assign(8, 5);
	assign_range.assign(BOB.begin() + 1, BOB.end() - 2);

	//EMPTY
	cout << "\nEMPTY\n";
	cout << "BOB is empty ? " << BOB.empty() << '\n';
	cout << "BOB at(41) : " << BOB.at(41) << '\n';

	//PUSH/POP_BACK
	cout << "\nPUSH/POP_BACK\n";
	BOB.push_back(53);
	cout << "last elem of BOB : " << BOB.back() << '\n';
	BOB.pop_back();
	cout << "last elem of BOB : " << BOB.back() << '\n';

	//INSERT
	cout << "\nINSERT\n";
	vector<int>	insert_in_me;
	for (int i = 0; i < 15; i++)
		insert_in_me.push_back(i);
	for (size_t i = 0; i < insert_in_me.size(); i++)
		cout << insert_in_me.at(i) << ' ';
	cout << '\n';

	vector<int>::iterator	tmp;
	tmp = insert_in_me.begin() + 4;
	insert_in_me.insert(tmp, 8, 42);
	for (size_t i = 0; i < insert_in_me.size(); i++)
		cout << insert_in_me.at(i) << ' ';
	cout << '\n';

	vector<int>::const_iterator const_it(insert_in_me.begin());
	cout << "Const it : " << std::endl;
	cout << *const_it << '\n';
//	*const_it = 89; // Does not compile because it's a const_iterator


	//INSERT
	cout << "\nINSERT\n";
	vector<int>	std_insert_in_me;
	for (int i = 0; i < 15; i++)
		std_insert_in_me.push_back(i);
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		cout << std_insert_in_me.at(i) << ' ';
	cout << '\n';

	vector<int>::iterator	std_tmp;
	std_tmp = std_insert_in_me.begin() + 4;
	std_insert_in_me.insert(std_tmp, 8, 42);
	for (size_t i = 0; i < std_insert_in_me.size(); i++)
		cout << std_insert_in_me.at(i) << ' ';
	cout << '\n';


	//INSERT RANGE
	cout << "\nINSERT RANGE\n";
	vector<int>	insert_bis;
	for (int i = 0; i < 7; i++)
		insert_bis.push_back(3 * i);
	for (size_t i = 0; i < insert_bis.size(); i++)
		cout << insert_bis[i] << ' ';
	cout << '\n';

	insert_bis.insert(insert_bis.begin() + 5, insert_in_me.begin(), insert_in_me.end());
	for (size_t i = 0; i < insert_bis.size(); i++)
		cout << insert_bis[i] << ' ';
	cout << '\n';


	//ERASE
	cout << "\nERASE\n";
	vector<int>	erase_in_me;
	for (int i = 0; i < 15; i++)
		erase_in_me.push_back(2 * i);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			cout << ' ';
		cout << erase_in_me.at(i) << ' ';
	}
	cout << '\n';

	erase_in_me.erase(erase_in_me.begin() + 7);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			cout << ' ';
		cout << erase_in_me.at(i) << ' ';
	}
	cout << '\n';

	erase_in_me.erase(erase_in_me.begin() + 2, erase_in_me.begin() + 6);
	for (size_t i = 0; i < erase_in_me.size(); i++)
	{
		if (erase_in_me[i] < 10)
			cout << ' ';
		cout << erase_in_me.at(i) << ' ';
	}
	cout << '\n';

	//SWAP
	cout << "\nSWAP\n";
	BOB.swap(MIKE);
	/*




	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 272\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 277\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 282\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	MIKE.swap(JOHN);
	/*




	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 298\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 303\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 308\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	//CLEAR
	cout << "\nCLEAR\n";
	JOHN.clear();
	MIKE.clear();
	/*




	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 327\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 332\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 337\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	//NON MEMBER Functions
	cout << "\nNON MEMBER functions\n";
	swap(BOB, MIKE);
	/*




	*/
	cout << "Size of JOHN " << JOHN.size() << std::endl;
	if (JOHN.capacity() >= JOHN.size())
		cout << "Capacity of JOHN is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 355\n";
	cout << "Size of BOB " << BOB.size() << std::endl;
	if (BOB.capacity() >= BOB.size())
		cout << "Capacity of BOB is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 360\n";
	cout << "Size of MIKE " << MIKE.size() << std::endl;
	if (MIKE.capacity() >= MIKE.size())
		cout << "Capacity of MIKE is sufficient\n";
	else
		std::cerr << "THERE IS A PROBLEM ON LINE 365\n";
	for (size_t i = 0; i < MIKE.size(); i++)
		cout << MIKE[i] << ' ';
	cout << std::endl;

	//RELATIONAL OPERATORS
	cout << "\nRELATIONAL OPERATORS\n";
	vector<int> MIKE_2(MIKE);
	cout << "MIKE and BOB are equal ? " << (MIKE == BOB) << '\n';
	cout << "MIKE and MIKE_2 are equal ? " << (MIKE == MIKE_2) << '\n';

	cout << "\nReal Vector\n";
	// vector<int> real(5,7);
	// // real.assign(5, 7);
	// for (vector<int>::iterator it = real.begin(); it != real.end(); it++)
	// 	cout << *it << " ";
	// cout << '\n';

	cout << std::endl;
	res = cout.str();
	return res;
}


std::string vector_resize2_ft(void)
{
	std::string res;
	std::ostringstream out;
	using ft::vector;
	using std::endl;
	vector<int> vec(4);
	vector<int> vec2(4);
	vector<int>::iterator it = vec.begin();
	vector<int>::iterator end = vec.end();
	vector<int>::iterator it2 = vec2.begin();
	vector<int>::iterator end2 = vec2.end();

	// while (it != end) {
	// 	out << "vec: "<< *it << endl; it++;
	// }
	// while (it2 != end2) {
	// 	out << "vec2: "<< *it2 << endl; it2++;
	// }
	//
	// out << "==: " << (vec == vec2) << " | !=: " << (vec != vec2) << std::endl;
	// out << "<: " << (vec <  vec2) << " | <=: " << (vec <= vec2) << std::endl;
	// out << ">: " << (vec >  vec2) << " | >=: " << (vec >= vec2) << std::endl;
	// out << "==: " << (vec2 == vec) << " | !=: " << (vec2 != vec) << std::endl;
	// out << "<: " << (vec2 <  vec) << " | <=: " << (vec2 <= vec) << std::endl;
	// out << ">: " << (vec2 >  vec) << " | >=: " << (vec2 >= vec) << std::endl;
	vec.resize(6);
	it = vec.begin();
	end = vec.end();
	it2 = vec2.begin();
	end2 = vec2.end();
	while (it != end) {
		out << "vec: "<< *it << endl; it++;
	}
	while (it2 != end2) {
		out << "vec2: "<< *it2 << endl; it2++;
	}
	out << "==: " << (vec == vec2) << " | !=: " << (vec != vec2) << std::endl;
	out << "<: " << (vec <  vec2) << " | <=: " << (vec <= vec2) << std::endl;
	out << ">: " << (vec >  vec2) << " | >=: " << (vec >= vec2) << std::endl;
	out << "==: " << (vec2 == vec) << " | !=: " << (vec2 != vec) << std::endl;
	// out << "<: " << (vec2 <  vec) << " | <=: " << (vec2 <= vec) << std::endl;
	// out << ">: " << (vec2 >  vec) << " | >=: " << (vec2 >= vec) << std::endl;

	vec2[2] = 42;

	// out << "==: " << (vec == vec2) << " | !=: " << (vec != vec2) << std::endl;
	// out << "<: " << (vec <  vec2) << " | <=: " << (vec <= vec2) << std::endl;
	// out << ">: " << (vec >  vec2) << " | >=: " << (vec >= vec2) << std::endl;
	// out << "==: " << (vec2 == vec) << " | !=: " << (vec2 != vec) << std::endl;
	// out << "<: " << (vec2 <  vec) << " | <=: " << (vec2 <= vec) << std::endl;
	// out << ">: " << (vec2 >  vec) << " | >=: " << (vec2 >= vec) << std::endl;
	it = vec.begin();
	end = vec.end();
	it2 = vec2.begin();
	end2 = vec2.end();
	while (it != end) {
		out << "vec: "<< *it << endl; it++;
	}
	while (it2 != end2) {
		out << "vec2: "<< *it2 << endl; it2++;
	}
	res = out.str();
	return res;
}
std::string vector_resize2_std(void)
{
	std::string res;
	std::ostringstream out;
	using std::vector;
	using std::endl;
	vector<int> vec(4);
	vector<int> vec2(4);
	vector<int>::iterator it = vec.begin();
	vector<int>::iterator end = vec.end();
	vector<int>::iterator it2 = vec2.begin();
	vector<int>::iterator end2 = vec2.end();

	// while (it != end) {
	// 	out << "vec: "<< *it << endl; it++;
	// }
	// while (it2 != end2) {
	// 	out << "vec2: "<< *it2 << endl; it2++;
	// }
	// out << "==: " << (vec == vec2) << " | !=: " << (vec != vec2) << std::endl;
	// out << "<: " << (vec <  vec2) << " | <=: " << (vec <= vec2) << std::endl;
	// out << ">: " << (vec >  vec2) << " | >=: " << (vec >= vec2) << std::endl;
	// out << "==: " << (vec2 == vec) << " | !=: " << (vec2 != vec) << std::endl;
	// out << "<: " << (vec2 <  vec) << " | <=: " << (vec2 <= vec) << std::endl;
	// out << ">: " << (vec2 >  vec) << " | >=: " << (vec2 >= vec) << std::endl;

	vec.resize(6);

	it = vec.begin();
	end = vec.end();
	it2 = vec2.begin();
	end2 = vec2.end();
	while (it != end) {
		out << "vec: "<< *it << endl; it++;
	}
	while (it2 != end2) {
		out << "vec2: "<< *it2 << endl; it2++;
	}
	out << "==: " << (vec == vec2) << " | !=: " << (vec != vec2) << std::endl;
	out << "<: " << (vec <  vec2) << " | <=: " << (vec <= vec2) << std::endl;
	out << ">: " << (vec >  vec2) << " | >=: " << (vec >= vec2) << std::endl;
	out << "==: " << (vec2 == vec) << " | !=: " << (vec2 != vec) << std::endl;
	// out << "<: " << (vec2 <  vec) << " | <=: " << (vec2 <= vec) << std::endl;
	// out << ">: " << (vec2 >  vec) << " | >=: " << (vec2 >= vec) << std::endl;

	vec2[2] = 42;

	// out << "==: " << (vec == vec2) << " | !=: " << (vec != vec2) << std::endl;
	// out << "<: " << (vec <  vec2) << " | <=: " << (vec <= vec2) << std::endl;
	// out << ">: " << (vec >  vec2) << " | >=: " << (vec >= vec2) << std::endl;
	// out << "==: " << (vec2 == vec) << " | !=: " << (vec2 != vec) << std::endl;
	// out << "<: " << (vec2 <  vec) << " | <=: " << (vec2 <= vec) << std::endl;
	// out << ">: " << (vec2 >  vec) << " | >=: " << (vec2 >= vec) << std::endl;
	it = vec.begin();
	end = vec.end();
	it2 = vec2.begin();
	end2 = vec2.end();
	while (it != end) {
		out << "vec: "<< *it << endl; it++;
	}
	while (it2 != end2) {
		out << "vec2: "<< *it2 << endl; it2++;
	}
	res = out.str();
	return res;
}

int main(void)
{
	// Test construction_test(&vector_constructions_ft, &vector_constructions_std);
	// assert(construction_test.is_same());
	//
	// Test clear_test(&vector_clear_ft, &vector_clear_std);
	// assert(clear_test.is_same());
	//
	// Test empty_test(&vector_empty_ft, &vector_empty_std);
	// // empty_test.printAll();
	//
	// assert(empty_test.is_same());
	//
	// Test at_test(&vector_at_ft, &vector_at_std);
	// assert(at_test.is_same());
	//
	// Test reserve_test(&vector_reserve_ft, &vector_reserve_std);
	// assert(reserve_test.is_same());
	//
	// Test push_back_test(&vector_push_back_ft, &vector_push_back_std);
	// // push_back_test.printAll();
	// assert(push_back_test.is_same());
	//
	// Test resize_test(&vector_resize_ft, &vector_resize_std);
	// // resize_test.printAll();
	// assert(resize_test.is_same());
	//
	// Test insert_test(&vector_insert_ft, &vector_insert_std);
	// // insert_test.printAll();
	// // assert(insert_test.is_same());
	//
	// Test erase_test(&vector_erase_ft, &vector_erase_std);
	// // erase_test.printAll();
	// assert(erase_test.is_same());
	//
	// Test erase_range_test(&vector_erase_range_ft, &vector_erase_range_std);
	// // erase_range_test.printAll();
	// assert(erase_range_test.is_same());
	//
	// Test size_test(&vector_size_ft, &vector_size_std);
	// // size_test.printAll();
	// assert(size_test.is_same());
	// Test strings_general_test(&vector_strings_general_ft, &vector_strings_general_std);
	// // strings_general_test.printAll();
	// assert(strings_general_test.is_same());
	// Test vector_test(&vector__ft, &vector__std);
	// // vector_test.printAll();
	// assert(vector_test.is_same());
	// Test vector_test_weird(&vector_resize2_ft, &vector_resize2_std);
	// vector_test_weird.printAll();
	// assert(vector_test_weird.is_same());

	// at_test.printAll();
	std::srand(std::time(0));
	ft::map<int, int> m;
	// std::pair<int, int> p0(12,5);
	// std::pair<int, int> p2(4,5);
	// std::pair<int, int> p3(5,5);
	// std::pair<int, int> p1(2,5);
	// m.insert(p0);
	// m.insert(p1);
	// m.insert(p2);
	// m.insert(p3);
	int i = 0;
	while (i < 42)
		m.insert(std::make_pair<int,int>(std::rand(),i++));
	// m.insert(p);
	// i = 0;
	m.print();
	// m.clear();
	return 0;
}
