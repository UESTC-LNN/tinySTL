#include "TinySTL_construct.hpp"
#include <iostream>
using namespace TinySTL;
int main()
{
	int* p=static_cast<int*>(::operator new(sizeof(int)));
	construct(p,3);
	std::cout<<*p<<std::endl;
	destroy(p);
	::operator delete(p);
	return 0;


}