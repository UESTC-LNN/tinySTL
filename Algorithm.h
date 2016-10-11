/*************************************************************************
	> File Name: Algorithm.h
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: 2016年09月12日 星期一 11时11分22秒
 ************************************************************************/
#ifndef __ALGORITHM_H
#define __ALGORITHM_H
#include <cstring>
#include <utility>
#include "Iterator.h"
#include "TypeTraits.h"
namespace tinySTL{
	
	//fill
	template<class ForwardIterator,class T>
	void fill(ForwardIterator first,ForwardIterator last,const T& value){
		for(;first!=last;++first){
			*first = value;
		}
	}
	
	inline void fill(char *first,char *last,const char& value){
		memset(first,value,last-first);
	}

	inline void fill(wchar_t *first,wchar_t *last,wchar_t& value){
		memset(first,value,sizeof(wchar_t)*(last-first));
	}
	//fill_n
	template<class OutputIterator,class Size,class T>
	OutputIterator fill_n(OutputIterator first,Size n,const T& value){
		for(;n!=0;--n,++first){
			*first=value;
		}
		return first;
	}

	template<class Size>
	char* fill_n(char* first,Size n,const char& value){
		memset(first,value,n);
		return first+n;
	}
	template<class Size>
	wchar_t* fill_n(wchar_t* first,Size n,const wchar_t& value){
		memset(first,value,n*sizeof(wchar_t));
		return first+n;
	}

	//min
	template<class T>
	const T& min(const T& a,const T& b){
		return a < b ? a : b;
	}

	template<class T,class Compare>
	const T& min(const T& a,const T& b,Compare comp){
		return (comp(a,b))? a : b;
	}

	//max
	template<class T>
	const T& max(const T& a,const T& b){
		return a > b? a : b;
	} 

	template<class T,class Compare>
	const T& max(const T& a,const T& b,Compare comp){
		return (comp(a,b))? a : b;
	}


	//distance
	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
	__distance(Iterator first,Iterator last,struct input_iterator_tag){
		typename iterator_traits<Iterator>::difference_type n=0;
		for(;first!=last;++first){
			++n;
		}
		return n;
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
	__distance(Iterator first,Iterator last,struct random_access_iterator_tag){
//		typename iterator_traits<Iterator>::difference_type n=0
		return last-first;
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
	distance(Iterator first,Iterator last){
		return __distance(first,last,iterator_category(first));
	}
	//advance

	template<class InputIterator,class Distance>
	inline void __advance(InputIterator &iter,Distance n,struct input_iterator_tag){
		while(n--){
			++iter;
		}		
	}

	template<class InputIterator,class Distance>
	inline void __advance(InputIterator &iter,Distance n,struct random_access_iterator_tag){
		iter+=n;
	}

	template<class InputIterator,class Distance>
	inline void __advance(InputIterator &iter,Distance n,struct bidirectional_iterator_tag){
		if(n>=0){
			while(n--){
				++iter;
			}
		}
		else{
			while(n++){
				--iter;
			}
		}
	}

	template<class InputIterator,class Distance>
	inline void advance(InputIterator &iter,Distance n){
		typedef typename iterator_traits<InputIterator>::category category;
		__advance(iter,n,category());
	}
	//copy
	
	template<class InputIterator,class OutputIterator>
	inline OutputIterator __copy_dispatch(InputIterator first,InputIterator last,OutputIterator result){
		`	
	}
	
	

	template<class InputIterator,class OutputIterator>
	inline OutputIterator copy(InputIterator first,InputIterator last,OutputIterator result){
		return __copy_dispatch(first,last,result);
	}

	template<>
	inline char* copy(char* first,char* last,char* result){
		memcpy(result,first,last-first);
		return result+last-first;
	}
	template<>
	inline wchar_t* copy(wchar_t* first,wchar_t last,wchar_t* result){
		memcpy(result,first,sizeof(wchar_t)*(last-first));
		return result+last-first;
	}
}

#endif
