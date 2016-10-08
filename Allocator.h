/*************************************************************************
	> File Name: Allocator.h
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: 2016年09月11日 星期日 14时15分00秒
 ************************************************************************/
#ifndef __ALLOCATOR_H
#define __ALLOCATOR_H

#include "Construct.h"
#include "Alloc.h"
#include <cassert>
namespace tinySTL{

	template<class T>
	class Allocator{
		public:
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
			typedef const T* const_pointer;
			typedef const T& const_reference;
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
		public:
			T* allocate();
			T* allocate(size_t n);
			void deallocate(T* p);
			void deallocate(T* p,size_t n);
			

		public:
			static void construct(T* p,T value);
			static void construct(T* p);
			static void destroy(T* p);
			static void destroy(T* first,T* last);
			
	
	}

	template<class T>
	T* Allocator::allocate(){
		return static_cast<T*>(alloc::allocate(sizeof(T)));
	}

	template<class T>
	T* Allocator::allocate(size_t n){
		if(0==n){
			return NULL;
		}
		return static_cast<T*>(alloc::allocate(sizeof(T)*n));
	}

	template<class T>
	void Allocator::deallocate(T* p){
		if(NULL==p){
			return;
		}
		alloc::deallocate(p,sizeof(T));

	}

	template<class T>
	void Allocator::deallocate(T* p,size_t n){
		if(0==n ||NULL ==p){
			return;
		}
		alloc::deallocate(sizeof(T)*n);
	}
	template<class T>
	void Allocator::construct(T* p,T value){
		if(NULL==p){
			return;
		}
		tinySTL::construct(p,value);
	}	
	template<class T>
	void Allocator::construct(T* p){
		if(NULL==p){
			return;
		}
		tinySTL::construct(p,T());
	}
	template<class T>
	void Allocator::destroy(T* p){
		tinySTL::destroy(p);
	}

	template<class T>
	void Allocator::destroy(T* first,T* last){
		tinySTL::destroy(first,last);
	}


}
#endif
