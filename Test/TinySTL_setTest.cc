#include "TinySTL_set.hpp"
#include <iostream>
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
	set<int> setint;

	setint.insert(2);
	setint.insert(3);
	setint.insert(1);
	setint.insert(6);
	setint.insert(5);
	setint.insert(10);

	print(setint.begin(),setint.end());

	set<int>::iterator it = setint.begin();
	std::cout<<*it<<std::endl;
	++it;
	std::cout<<*it<<std::endl;
	setint.erase(it);
	print(setint.begin(),setint.end());


	return 0;
}