#include "TinySTL_uninitialized.hpp"
#include "TinySTL_alloc.h"
#include <iostream>

using namespace TinySTL;

class Testclass
{
	public:
		explicit Testclass(int n):_n(n){}
		explicit Testclass(const Testclass& u)
		{
			_n=u._n;
			std::cout<<"Copy construction Testclass"<<std::endl;
		}
	private:
		int _n;

};

int main()
{
	int *intptr = simple_alloc<int,alloc>::allocate(10);
	uninitialized_fill(intptr,intptr+10,4);
	std::cout<<intptr[4]<<std::endl;

	Testclass testclass(4);
	Testclass* testptr = simple_alloc<Testclass,alloc>::allocate(5);
	uninitialized_fill_n(testptr,5,testclass);

	simple_alloc<int,alloc>::deallocate(intptr,10);
	simple_alloc<Testclass,alloc>::deallocate(testptr,10);

	return 0;




}