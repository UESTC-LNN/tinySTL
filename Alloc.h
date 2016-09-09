/*************************************************************************
	> File Name: Alloc.h
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: Fri 09 Sep 2016 01:22:21 PM CST
 ************************************************************************/

#ifndef __ALLOC_H
#define __ALLOC_H

#include <cstdlib>

namespace tinySTL{
	
	class malloc_alloc{
		public:
			static void* allocate(size_t n){
				void *result=malloc(n);
				if(0==result){
						
				}
				return result;
			}
			static void* realloc(void *p,size_t sz){
				void *result=realloc(n);
				if(0==result){
				
				}
				return result;
				
			}
			static dealloc(void *p){
				free(p);
			}
	}
	enum { __ALIGN=8};
	enum { __MAX_BYTES=128};
	enum { __NFREELISTS=__MAX_BYTES/__ALIGN};
	class alloc{
		private:
			union obj {
				union obj *link;
				char client_data[0];
			};
		private:
			static char *start;
			static char *end;
			static size_t heap_size;
			static obj *free_list[__NFREELISTS];

		private:
			static size_t ROUND_UP(size_t bytes){
				return ((bytes+__ALIGN-1) & ~(__ALIGN-1));
			}
			static size_t FREELIST_INDEX(size_t n){
				return ((n+__ALIGN)/__ALIGN-1);
			}
		public:
			static void* allocate(size_t n){
				if(0==n){
					return NULL;
				}
				if(n>128){
					return malloc_alloc::allocate(n);
				}
				else{
					obj *my_free_list=free_list+FREELIST_INDEX(n);
					if(NULL==my_free_list){
						void *r=refill(ROUND_UP(n));
						return r;
					}
					obj* result=*my_free_list;
					*my_free_list=result->link;
					return obj;
				}

				
			}
			
			static void* refill(size_t n){
				int nobjs=20;
				char *chunk=chunk_alloc(n,nobjs);
				
				if(1==nobjs){
					return chunk;
				}
				obj *my_free_list=free_list+FREELIST_INDEX(n);
				obj *result=(obj*)chunk;
				obj *next=result+n;
				*my_free_list=next;
				obj *current;
				int i=0;
				for(i=1;;++i){
					current=next;
					if(nobjs-1==i){
						break;
					}
					next=(obj*)((char*)next+n);
					current->link=next;

				}
				current->link=NULL;
				return result;
			}
			char * chunk_alloc(size_t sz,int &nobjs){
				char *result;
				size_t total_size=sz*nobjs;
				size_t bytes_left=end-start;

				if(bytes_left>total_size){
					result=start;
					start+=total_size;
					return result;
				}
				else if(bytes_left>sz){
					
				}
			}
	
	}


}
