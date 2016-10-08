/*************************************************************************
	> File Name: Vector.impl.h
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: 2016年09月12日 星期一 19时24分37秒
 ************************************************************************/
#include "Vector.h"
namespace tinySTL{

	template<class T,class Alloc=Allocator<T> >
	iterator vector::allocate_and_fill(size_t n,const T& x){
		iterator result=dataAllocator::allocate(n);
		uninitialized_fill_n(result,n,x);
		return result;
	}
}

