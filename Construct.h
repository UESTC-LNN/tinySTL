/*************************************************************************
	> File Name: Construct.h
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: 2016年09月11日 星期日 10时37分53秒
 ************************************************************************/


#ifndef __CONSTRUCT_H
#define __CONSTRUCT_H

#include "TypeTraits.h"
namespace tinySTL{

	template<class T1,class T2>
	inline void construct(T1 *p,T2 &value){
			new (p) T1(value);
	}
		
	template<class T>
	inline void destroy(T *p){
		p->~T();
	}

	template<class ForwardIterator>
	inline void destroy(ForwardIterator first,ForwardIterator last){
		typedef typename iterator_traits<ForwardIterator>::is_POD_type is_POD_type;
		__destroy(first,last,is_POD_type());		
	}
	template<class ForwardIterator,class T>
	inline void __destroy(ForwardIterator first,ForwardIterator last,struct __true_type){}
	inline void __destroy(ForwardIterator first,ForwardIterator last,struct __false_type){
		for(;first!=last;++first){
			destroy(&(*first));
		}
	}

	
}


#endif


 
