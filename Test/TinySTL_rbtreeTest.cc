#include "TinySTL_RBTree.hpp"
#include "TinySTL_function.hpp"
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
	less<int> k;
	rb_tree<int,int,identity<int>,less<int> > itree(k);
	std::cout<<itree.size()<<std::endl;

	itree.insert_unique(2);
	itree.insert_unique(4);
	itree.insert_unique(5);
	itree.insert_unique(1);
	itree.insert_unique(3);
	itree.insert_unique(10);
	print(itree.begin(),itree.end());

	rb_tree<int,int,identity<int>,less<int> >::iterator iter = itree.find(10);
	std::cout<<*iter<<std::endl;

	itree.erase(iter);
	print(itree.begin(),itree.end());

	itree.clear();
	print(itree.begin(),itree.end());



	return 0;
}