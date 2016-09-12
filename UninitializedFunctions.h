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

	
	template<class InputIterator,class ForwardIterator>
	ForwardIterator __uninitialized_copy(InputIterator first,InputIterator last,
										ForwardIterator result,struct __true_type){
		return copy(first,last,result);
	
	}

	template<class InputIterator,class ForwardIterator>
	ForwardIterator __uninitialized_copy(InputIterator first,InputIterator last,
										ForwardIterator result,struct __false_type){
		ForwardIterator cur=result;
		for(;first!=last;++first){
			tinySTL::construct(&*cur,*first);
			++cur;
		}
		return cur;

	
	}

	template<class InputIterator,class ForwardIterator>
	inline ForwardIterator uninitialized_copy(InputIterator first,InputIterator last,
										ForwardIterator result){
		typedef typename type_traits<InputIterator>::is_POD_type is_POD_type;
		return __uninitialized_copy(first,last,result,is_POD_type());
	}

	inline char* uninitialized_copy(char *first,char* last,char* result){
		memmove(result,first,last-first);
		return result+last-first;
	}

	inline wchar_t* uninitialized_copy(wchar_t *first,wchar_t* last,wchar_t* result){
		memmove(result,first,sizeof(wchar_t)*(last-first));
		return result+last-first;
	}
	
	/*************************************************************************************/

	template<class ForwardIterator,class T>
	void __uninitialized_fill(ForwardIterator first,ForwardIterator last,const T& x,struct __true_type){
		fill(first,last,x);
	}

	template<class ForwardIterator,class T>
	void __uninitialized_fill(ForwardIterator first,ForwardIterator last,const T& x,struct __false_type){
		ForwardIterator cur=first;
		for(;cur!=last;++first){
			tinySTL::construct(&*cur,x);
		}
	}


	template<class ForwardIterator,class T>
	inline void uninitialized_fill(ForwardIterator first,ForwardIterator last,const T& x){
		typedef typename type_traits<ForwardIterator>::is_POD_type is_POD_type;
		__uninitialized_fill(first,last,x,is_POD_type());
	}

	/*************************************************************************************/
	template<class ForwardIterator,class Size,class T>
	ForwardIterator __uninitialized_fill_n(ForwardIterator first,Size n,const T& x,struct __true_type){
		return fill_n(first,n,x);
	}

	template<class ForwardIterator,class Size,class T>
	ForwardIterator __uninitialized_fill_n(ForwardIterator first,Size n,const T& x,struct __false_type){
		ForwardIterator cur=first;
		for(;n!=0;--n){
			tinySTL::construct(&*cur,x);
			++cur;
		}
		return cur;
	}


	template<class ForwardIterator,class Size,class T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first,Size n,const T& x){
		typedef typename type_traits<ForwardIterator>::is_POD_type is_POD_type;
		return __uninitialized_fill_n(first,n,x,is_POD_type());
	}



}

#endif
