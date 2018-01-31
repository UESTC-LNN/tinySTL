#include "TinySTL_alloc.h"

#ifndef __THROW_BAD_ALLOC		
#include<iostream> 
#include <unistd.h>
#define __THROW_BAD_ALLOC std::cerr<<"out of memory"<<std::endl;exit(1);
#endif

namespace TinySTL
{

//*__alloc_bigsize
	void (*__alloc_bigsize::__malloc_alloc_oom_handler)() =0;

	void* __alloc_bigsize::oom_malloc(size_t n)
	{
		void (*my_alloc_handler)();
		void *res;

		for(;;)
		{
			my_alloc_handler=__malloc_alloc_oom_handler;
			if(0==my_alloc_handler){__THROW_BAD_ALLOC;}
			(*my_alloc_handler)();
			res=malloc(n);
			if(res) return res;
		}

	}


	void* __alloc_bigsize::oom_realloc(void* p,size_t n)
	{
		void (*my_alloc_handler)();
		void *res;

		for(;;)
		{
			my_alloc_handler=__malloc_alloc_oom_handler;
			if(0==my_alloc_handler){__THROW_BAD_ALLOC;}
			(*my_alloc_handler)();
			res=realloc(p,n);
			if(res) return res;
		}
	}

//alloc
	alloc::obj* alloc::free_list[__NFREELISTS]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	char* alloc::start_free=0;

	char* alloc::end_free=0;

	size_t alloc::heap_size=0;

	void* alloc::allocate(size_t n)
	{
		obj** my_free_list;
		obj* result;

		if(n > static_cast<size_t>(__MAX_BYTES))
		{
			return (malloc_alloc::allocate(n));
		}

		my_free_list=free_list+FREELIST_INDEX(n);
		result = *my_free_list;
		if(0==result)
		{
			void* r=refill(ROUND_UP(n));
			return r;
		}
		*my_free_list=result->free_list_link;
		return result;
	}

	void alloc::deallocate(void* p,size_t n)
	{
		obj** my_free_list;
		
		if(n>static_cast<size_t>(__MAX_BYTES))
		{
			malloc_alloc::deallocate(p,n);
		}

		my_free_list=free_list+FREELIST_INDEX(n);

		obj* q=static_cast<obj*>(p);
		
		q->free_list_link=*my_free_list;
		*my_free_list=q;
	}

	void* alloc::refill(size_t n)
	{
		int nobjs=20;

		char* chunk=static_cast<char*>(chunk_alloc(n,nobjs));

		obj** my_free_list;

		if(1==nobjs)
		{
			return chunk;
		}

		void* res=chunk;

		my_free_list= free_list +FREELIST_INDEX(n);

		obj* next = (obj*)(chunk+n);
		*my_free_list = next;
		obj* current;
		
		int i=1;
		for(;;++i)
		{
			current=next;
			next=(obj*)((char*)(next)+n);
			if(i!=nobjs-1)
			{
				current->free_list_link= next;
			}
			else
			{
				current->free_list_link=0;
				break;
			}
		
		}
		return res;

	}

	void* alloc::chunk_alloc(size_t size,int& nobjs)
	{
		char* result;
		size_t total_size = size * nobjs;
		size_t bytes_left = end_free - start_free;

		if(bytes_left >= total_size)
		{
			result=start_free;
			start_free+=total_size;
			return result;
		}
		else if(bytes_left >= size)
		{
			nobjs=bytes_left/size;
			total_size = size*nobjs;
			result=start_free;
			start_free+=total_size;
			return result;
		}
		else
		{
			size_t bytes_to_get = 2 * total_size + ROUND_UP(heap_size>>4);
			if(bytes_left>0)
			{
				
				obj** my_free_list = free_list + FREELIST_INDEX(bytes_left);
				obj *q = (obj*)(start_free);
				q->free_list_link = *my_free_list;
				*my_free_list = q;

				
			}
		
			start_free = static_cast<char*>(malloc(bytes_to_get));
			if(0==start_free)
			{
				int i;
				obj** my_free_list;
				obj* p;

				for(i=size;i<=__MAX_BYTES;i=i+__ALIGN)
				{
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;
					if(0!=p)
					{
						start_free = (char*)(p);
						end_free = start_free + i;

						*my_free_list = p->free_list_link;

						return chunk_alloc(size,nobjs);
					}
				}
				end_free = 0;
				start_free = static_cast<char*>(malloc_alloc::allocate(bytes_to_get));
			
			
			}
			heap_size +=bytes_to_get;
			end_free = start_free+bytes_to_get;

			return (chunk_alloc(size,nobjs));
		
		}
	
	}


	void* alloc::reallocate(void* p,size_t old_size,size_t new_size)
	{
		deallocate(p,old_size);
		p = allocate(new_size);
		return p;
	

	}

/* 实现不了的。因为内存不能一块块释放。。
	void alloc::free_all()
	{
		
		int offset = 0;
		for(;offset < __NFREELISTS;++offset)
		{
			obj** my_free_list = free_list+offset;
			obj* p = *my_free_list;
			
			size_t bloc = (offset+1)*__ALIGN;
			while(p)
			{
				void* tmp = p;
				p = p->free_list_link;
				free(tmp);

			}
			*my_free_list=0;
		}
	}
*/

}