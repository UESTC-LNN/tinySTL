#include "TinySTL_alloc.h"
#include "TinySTL_construct.hpp"

#include <iostream>
using namespace TinySTL;

int main()
{
	int *ptr = static_cast<int*>(alloc::allocate(sizeof(int)));
	construct(ptr,4);
	std::cout<<(*ptr)<<std::endl;
	//destroy(ptr);
	//alloc::free_all();
	return 0;


}