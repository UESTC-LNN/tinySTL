/*************************************************************************
	> File Name: Vector.impl.h
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: 2016年09月12日 星期一 19时24分37秒
 ************************************************************************/
#ifndef __VECTOR_IMPL_H
#define __VECTOR_IMPL_H


namespace tinySTL{

	template<class T,class Alloc=Allocator<T> >
	iterator vector::allocate_and_fill(size_t n,const T& x){
		iterator result=dataAllocator::allocate(n);
		uninitialized_fill_n(result,n,x);
		return result;
	}

	iterator insert_aux(iterator position,const T& x){
		if(finish!=end_of_storage){
			dataAllocator::construct(finish,*(finish-1));
			T x_copy=x;
			copy_backward(position,finish-1,finish);			++finish;
			*position=x_copy;
		}	
	}


}

#endif
