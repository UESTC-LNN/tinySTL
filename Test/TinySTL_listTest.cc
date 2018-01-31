#include <iostream>

#include "TinySTL_list.hpp"
#include "TinySTL_algorithm.hpp"
using namespace TinySTL;

template<typename InputIterator>
void print(InputIterator first,InputIterator last)
{
	while(first!=last)
	{
		std::cout<<*first<<"\t";
		++first;
	}
	std::cout<<std::endl;
}

int main()
{
	list<int> lisint;
	lisint.push_back(1);
	lisint.push_back(2);
	lisint.push_back(3);
	lisint.push_back(4);
	lisint.push_back(5);
	lisint.push_back(6);
	print(lisint.begin(),lisint.end());
/*
	lisint.pop_back();
	print(lisint.begin(),lisint.end());


	lisint.push_front(0);
	print(lisint.begin(),lisint.end());

	lisint.pop_front();
	print(lisint.begin(),lisint.end());
	list<int>::iterator sear;
	list<int>::iterator iter = find(lisint.begin(),lisint.end(),2);
	sear = lisint.insert(iter,100);
	std::cout<<*iter<<std::endl;
	std::cout<<*sear<<std::endl;
	print(lisint.begin(),lisint.end());


	lisint.insert(lisint.begin(),100);
	print(lisint.begin(),lisint.end());

	lisint.insert(lisint.end(),100);
	print(lisint.begin(),lisint.end());

	iter = find(lisint.begin(),lisint.end(),3);
	sear = lisint.erase(iter);
	//std::cout<<*iter<<std::endl;
	std::cout<<*sear<<std::endl;
	print(lisint.begin(),lisint.end());
*/
	//lisint.pop_back(); segment fault

	list<int> other;
	other.push_back(101);
	other.push_back(102);
	other.push_back(103);
	other.push_back(104);
	other.push_back(105);
	other.push_back(106);
	print(other.begin(),other.end());

	lisint.splice(lisint.begin(),other);	
	print(lisint.begin(),lisint.end());
	print(other.begin(),other.end());

	return 0;


}