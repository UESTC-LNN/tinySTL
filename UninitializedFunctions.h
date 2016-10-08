/*************************************************************************
	> File Name: UninitializedFunctions.h
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: 2016年09月12日 星期一 10时13分35秒
 ************************************************************************/

#ifndef __UNINITIALIZEDFUNCTIONS_H
#define __UNINITIALIZEDFUNCTIONS_H

#include "Construct.h"
#include "Iterator.h"
#include "Algorithm.h"
#include "TypeTraits.h"

namespace tinySTL{

	/******************************copy********************************/
	template<class InputIterator,class ForwardIterator>
	ForwardIterator __uninitialized_copy_aux(InputIterator first,InputIterator last,
										ForwardIterator result,struct __true_type){
		return copy(first,last,result);
	
	}

	template<class InputIterator,class ForwardIterator>
	ForwardIterator __uninitialized_copy_aux(InputIterator first,InputIterator last,
										ForwardIterator result,struct __false_type){
		ForwardIterator cur=first;
		for(;cur!=last;++cur){
			tinySTL::construct(&*(result+(cur-first)),*cur);
		}
		return cur;

	
	}

	template<class InputIterator,class ForwardIterator,class T>
	inline ForwardIterator __uninitialized_copy(InputIterator first,InputIterator last,
										ForwardIterator result,T*){
		typedef typename type_traits<T>::is_POD_type is_POD_type;
		return __uninitialized_copy_aux(first,last,result,is_POD_type());
	}

	template<class InputIterator,class ForwardIterator>
	inline ForwardIterator uninitialized_copy(InputIterator first,InputIterator last,ForwardIterator result){
		return __uninitialized_copy(first,last,result,value_type(first));	
	}

	inline char* uninitialized_copy(char *first,char* last,char* result){
		memmove(result,first,last-first);
		return result+last-first;
	}

	inline wchar_t* uninitialized_copy(wchar_t *first,wchar_t* last,wchar_t* result){
		memmove(result,first,sizeof(wchar_t)*(last-first));
		return result+last-first;
	}
	
	/*************************************fill*******************************************/

	template<class ForwardIterator,class T>
	void __uninitialized_fill_aux(ForwardIterator first,ForwardIterator last,const T& x,struct __true_type){
		fill(first,last,x);
	}

	template<class ForwardIterator,class T>
	void __uninitialized_fill_aux(ForwardIterator first,ForwardIterator last,const T& x,struct __false_type){
		ForwardIterator cur=first;
		for(;cur!=last;++cur){
			tinySTL::construct(&*cur,x);
		}
	}

	template<class ForwardIterator,class T,class T1>
	inline void __uninitialized_fill(ForwardIterator first,ForwardIterator last,const T& x,T1*){
		typedef typename type_traits<T1>::is_POD_type is_POD_type;
		__uninitialized_fill_aux(first,last,x,is_POD_type());
	}

	template<class ForwardIterator,class T>
	inline void uninitialized_fill(ForwardIterator first,ForwardIterator last,const T& x){
		__uninitialized_fill(first,last,x,value_type(first));
	}

	/************************************fill n********************************************/
	template<class ForwardIterator,class Size,class T>
	ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first,Size n,const T& x,struct __true_type){
		return fill_n(first,n,x);
	}

	template<class ForwardIterator,class Size,class T>
	ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first,Size n,const T& x,struct __false_type){
		ForwardIterator cur=first;
		for(;n!=0;--n){
			tinySTL::construct(&*cur,x);
			++cur;
		}
		return cur;
	}



	template<class ForwardIterator,class Size,class T.class T1>
	inline ForwardIterator __uninitialized_fill_n(ForwardIterator first,Size n,const T& x,T1*){
		typedef typename type_traits<T1>::is_POD_type is_POD_type;
		return __uninitialized_fill_n_aux(first,n,x,is_POD_type());
	}

	template<class ForwardIterator,class Size,class T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first,Size n,const T& x){
		return __uninitialized_fill_n(first,n,x,value_type(first));
	}



}

#endif
