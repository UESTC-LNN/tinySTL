#include <iostream>

#include "TinySTL_vector.hpp"

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
	vector<int> vec(4,2);
	std::cout<<"vec元素个数:"<<vec.size()<<std::endl;
	std::cout<<"vec容量:"<<vec.max_size()<<std::endl;
	print(vec.begin(),vec.end());

	vec[2]=3;
	print(vec.begin(),vec.end());

	vec.front() = 1;
	print(vec.begin(),vec.end());

	vec.back()=4;
	print(vec.begin(),vec.end());

	vec.push_back(5);
	print(vec.begin(),vec.end());
	std::cout<<"vec元素个数:"<<vec.size()<<std::endl;
	std::cout<<"vec容量:"<<vec.max_size()<<std::endl;

	vec.pop_back();
	print(vec.begin(),vec.end());
	std::cout<<"vec元素个数:"<<vec.size()<<std::endl;
	std::cout<<"vec容量:"<<vec.max_size()<<std::endl;
	
	vec.insert(vec.begin(),0);
	print(vec.begin(),vec.end());
	std::cout<<"vec元素个数:"<<vec.size()<<std::endl;
	std::cout<<"vec容量:"<<vec.max_size()<<std::endl;

	vec.insert(vec.end(),3,-1);
	print(vec.begin(),vec.end());
	std::cout<<"vec元素个数:"<<vec.size()<<std::endl;
	std::cout<<"vec容量:"<<vec.max_size()<<std::endl;


	vec.erase(vec.begin()+1);
	print(vec.begin(),vec.end());
	std::cout<<"vec元素个数:"<<vec.size()<<std::endl;
	std::cout<<"vec容量:"<<vec.max_size()<<std::endl;


	vec.erase(vec.end()-3,vec.end());
	print(vec.begin(),vec.end());
	std::cout<<"vec元素个数:"<<vec.size()<<std::endl;
	std::cout<<"vec容量:"<<vec.max_size()<<std::endl;

	vec.clear();
	print(vec.begin(),vec.end());
	std::cout<<"vec元素个数:"<<vec.size()<<std::endl;
	std::cout<<"vec容量:"<<vec.max_size()<<std::endl;

	
	return 0;
}