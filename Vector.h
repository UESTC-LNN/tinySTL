/*************************************************************************
	> File Name: Vector.h
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: 2016年09月11日 星期日 19时40分39秒
 ************************************************************************/
#ifndef __VECTOR_H
#define __VECTOR_H
#include <type_traits>
#include "Allocator.h"
#include "UninitializedFunctions.h"
#include "Algorithm.h"
namespace tinySTL{

	template<class T,class Alloc=Allocator<T> >
	class vector{
		public:
			typedef T value_type;
			typedef value_type* pointer;
			typedef value_type* iterator;
			typedef value_type& reference;
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
		private:
			iterator start;
			iterator finish;
			iterator end_of_storage;
			typedef Alloc dataAllocator;

		private:
			iterator allocate_and_fill(size_t n,const T& x);
			iterator fill_initialize(size_t n,const T& x){
				start=allocate_and_fill(n,x);
				finish=start+n;
				end_of_storage=finish;
			}
			void deallocate(){
				if(start){
					dataAllocator::deallocate(start,size_t(end_of_storage-start));
				}
			}

		public:
			/***constructor****/
			vector():start(0),finish(0),end_of_storage(0){}
			vector(size_type n,const T& x){fill_initialize(n,x);}
			vector(int n,const T& x){fill_initialize(n,x);}
			vector(long n,const T& x){fill_initialize(n,x);}
			explicit vector(size_type n){fill_initialize(n,T());}
			
			/***destructor*****/
			~vector(){
				destroy(start,finish);
				deallocate();
			}

		public:
			//iterator
			inline iterator begin(){return start;}
			inline iterator end(){return finish;}

			//capacity
			inline size_type size(){return (finish-start);}
			inline size_type capacity(){return (end_of_storage-start);}
			bool empty(){return begin()==end();}

		public:
			//access
			reference front(){return *(end()-1)}
			reference back(){return *begin()}
			reference operator[](size_type n){return *(begin()+(difference_type)n)}
			
		public:
			void push_back(const T& value);
			void pop_back();
			iterator erase(iterator position);
			iterator erase(iterator first,iterator last);
			iterator insert(iterator position,const T& value);
			void insert(iterator position,size_type n,const T& value);
			void insert(iterator position,iterator first,iterator last);
			void clear();
			void resize(size_type new_size,const T& value);

	
	
	
	};


}
#endif
