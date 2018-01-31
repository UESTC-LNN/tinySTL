#ifndef __TINYSTL_ALLOC_H
#define __TINYSTL_ALLOC_H

#include <cstdlib> //for new\free

 



namespace TinySTL
{

class __alloc_bigsize
{
	private:
		static void* oom_malloc(size_t);
		static void* oom_realloc(void*,size_t);
		static void (*__malloc_alloc_oom_handler)();
	
	public:
		static void* allocate(size_t n)
		{
			void* res=malloc(n);
			if(0==res) res=oom_malloc(n);
			return res;
		}

		static void deallocate(void* p,size_t)
		{
			free(p);
		}

		static void* reallocate(void* p,size_t n)
		{
			void* res=realloc(p,n);
			if(0==res) res=oom_realloc(p,n);
			return res;
		}


		static void (*set_malloc_handler(void(*f)()))()
		{
			void (*old)()=__malloc_alloc_oom_handler;
			__malloc_alloc_oom_handler=f;
			return old;
		}

		static void free_all();
};

typedef __alloc_bigsize malloc_alloc;

enum {__ALIGN=8};
enum {__MAX_BYTES=128};
enum {__NFREELISTS = __MAX_BYTES/__ALIGN};


class alloc
{
	private:
		union obj
		{
			union obj* free_list_link;
			char data[1];
		};

	private:
		static obj* free_list[__NFREELISTS];
		
		static char* start_free;
		static char* end_free;
		static size_t heap_size;

	private:
		static size_t ROUND_UP(size_t bytes)
		{
			return ((bytes+__ALIGN-1) & ~(__ALIGN-1));
		}

		static size_t FREELIST_INDEX(size_t bytes)
		{
			return ((bytes+__ALIGN-1)/__ALIGN-1);
		}

		static void* refill(size_t);
		static void* chunk_alloc(size_t ,int&);

	public:
		static void* allocate(size_t);
		static void  deallocate(void*,size_t);
		static void* reallocate(void* p,size_t,size_t);
		//static void free_all();
};

template<typename T,typename Alloc>
class simple_alloc
{
public:
	static T* allocate(size_t n)
	{
		return 0==n? 0 : static_cast<T*>(Alloc::allocate(n*sizeof(T)));
	}
	static T* allocate()
	{
		return static_cast<T*>(Alloc::allocate(sizeof(T)));
	}
	static void deallocate(T* p,size_t n)
	{
		if(0!=n)
		{
			Alloc::deallocate(p,sizeof(T)*n);
		}
	}
	static void deallocate(T* p)
	{
		Alloc::deallocate(p,sizeof(T));
	}
};




}





#endif