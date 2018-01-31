#include "TinySTL_algorithm.hpp"

#include <iostream>
#include <vector>
#include <list>
using namespace TinySTL;

int main()
{
	std::cout<<"测试1"<<std::endl;
	const char ccs[5]={'a','b','c','d','e'};
	char ccd[5];
	copy(ccs,ccs+5,ccd);

	std::cout<<"测试2"<<std::endl;
	const wchar_t wccs[5]={'a','b','c','d','e'};
	wchar_t wccd[5];
	copy(wccs,wccs+5,wccd);
	
	std::cout<<"测试3"<<std::endl;
	int is[5]={1,2,3,4,5};
	int os[5];
	copy(is,is+5,os);

	std::cout<<"测试4"<<std::endl;
	const int cis[5]={1,2,3,4,5};
	int cos[5];
	copy(cis,cis+5,cos);
/*
	std::cout<<"测试5"<<std::endl;
	std::vector<int> vecint(is,is+5);
	TinySTL::copy(vecint.begin(),vecint.end(),cos);

	std::cout<<"测试6"<<std::endl;
	std::list<int> lisint(is,is+5);
	TinySTL::copy(lisint.begin(),lisint.end(),cos);
*/
	return 0;
}