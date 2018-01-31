#include "IteratorTiny.hpp"
#include <iostream>
#include <assert.h>
#include <string.h>
#include <typeinfo>
using namespace TinySTL;

template<typename T>
class vectorIterTiny:public iterator<random_access_iterator_tag,T>
{
	
		

};
template<typename T>
class vectorTiny
{
public:
	typedef vectorIterTiny<T> iterator;


};





int main()
{
	vectorTiny<int> vec;
	vectorTiny<int>::iterator iter;
	struct random_access_iterator_tag test_random_access_iterator_tag;
	assert(strcmp(typeid(iterator_category(iter)).name(),typeid(test_random_access_iterator_tag).name())==0);
	return 0;

}