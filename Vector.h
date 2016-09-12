/*************************************************************************
	> File Name: Vector.h
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: 2016年09月11日 星期日 19时40分39秒
 ************************************************************************/
#ifndef __VECTOR_H
#define __VECTOR_H

#include "Allocator.h"
#include "UninitializedFunctions.h"

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
			vector():start(0),finish(0),end_of_storage(0){}
			vector(size_type n,const T& x){fill_initialize(n,x);}
			vector(int n,const T& x){fill_initialize(n,x);}
			vector(long n,const T& x){fill_initialize(n,x);}
			explicit vector(size_type n){fill_initialize(n,T());}

			~vector(){
				destroy(start,finish);
				deallocate();
			}

		public:
			inline iterator begin(){return start;}
			inline iterator end(){return finish;}
			inline size_type size(){return (finish-size);}
			inline size_type capacity(){return (end_of_storage-start);}
			bool empty(){return begin()==end();}

		public:	
			void clear();
			void push_back(const T& value);
			void pop_back();
			iterator insert(iterator position,const T& value);
			void insert(iterator position,const T& n,const T& value);
			template<class InputIterator>
			void insert(iterator position,InputIterator first,InputIterator last);
			iterator erase(iterator position);
			iterator erase(iterator first,iterator last);

		private:
			iterator insert_aux(iterator position,const T& x);
	
	
	
	
	};


}
#endif
