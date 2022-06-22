#pragma once

#include "containers/vector.hpp"
#include <vector>
#include <iostream>
#include <string>

class Test
{
private:
	std::string _res_ft;
	std::string _res_std;
public:
	typedef std::string (*testFunction)(void);
	Test(testFunction test_ft, testFunction test_std) : _res_ft(test_ft()), _res_std(test_std())
	{
	};
	void printAll(void) {
		std::cout<<"\nSTD OUTPUT\n"<<std::endl<<_res_std<<std::endl;
		std::cout<<"\nFT OUTPUT\n"<<std::endl<<_res_ft<<std::endl;
	};
	void printFT(void) {
		std::cout<<"\nFT OUTPUT\n"<<std::endl<<_res_ft<<std::endl;
	};
	void printSTD(void) {
		std::cout<<"\nSTD OUTPUT\n"<<std::endl<<_res_std<<std::endl;
	};
	bool is_same(void)
	{
		return (_res_std == _res_ft);
	};
};
