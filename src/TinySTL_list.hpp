#ifndef __TINYSTL_LIST_HPP
#define __TINYSTL_LIST_HPP
#include <stddef.h>
#include "TinySTL_alloc.h"   //require "TinySTL_alloc.cc"
#include "TinySTL_construct.hpp"

namespace TinySTL
{

template<typename T>
struct node
{
	node<T>* prev;
	node<T>* next;
	T data;
	node(const T& val=T()):prev(0),next(0),data(val){}
	node(const T& val,node<T>* prev_,node<T>* next_):prev(prev_),next(next_),data(val){}
	bool operator==(const node<T>& nod)
	{
		return prev==nod.prev && next==nod.next && data==nod.data;
	}
	
	bool operator!=(const node<T>& nod)
	{
		return prev!=nod.prev || next!=nod.next || data!=nod.data;
	}

};


template<typename T>
struct listIterator
{
	typedef bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer;
	typedef T& reference;

	typedef node<T>* nodePtr;
	typedef listIterator<T> self;

	nodePtr p;

	listIterator(const nodePtr& _p = 0):p(_p){}
	bool operator==(const listIterator<T>& iter)
	{
		return p==iter.p;
	}
	bool operator!=(const listIterator<T>& iter)
	{
		return p!=iter.p;
	}
	reference operator*()const
	{
		return (*p).data;
	}
	pointer operator->()const
	{
		return &((*p).data);
	}

	self& operator++()
	{
		p = (nodePtr)(p->next);
		return *this;
	}
	
	self operator++(int)
	{
		self tmp = *this;
		p = (nodePtr)(p->next);
		return tmp;
	}
	
	self& operator--()
	{
		p = (nodePtr)(p->prev);
		return *this;
	}
	
	self operator--(int)
	{
		self tmp = *this;
		p = (nodePtr)(p->prev);
		return tmp;
	}

};


template<typename T,typename Alloc = alloc>
class list
{
	public:
		typedef T value_type;
		typedef size_t size_type;
		typedef T& reference;


		typedef node<T>* nodePtr;
		typedef listIterator<T> iterator;
		typedef listIterator<const T> const_iterator;

		typedef simple_alloc<node<T>,Alloc> list_node_allocator;
	protected:
		iterator head;
		iterator tail;
	protected:
	//请求allocator分配内存并构造
		nodePtr newNode(const T& value=T());
	//delete node
		void deleteNode(nodePtr p);
		

	public: //Iterator
		iterator begin(){return head;}
		iterator end() {return tail;}
		

	public: //construct and destroy
		list();
		//list(size_type n,const T& value);
		~list();
	public:  // about capacity
		bool empty(){return begin()==end();}
		//size_type size();

	public:  //element access
		reference front() 
		{
			
			return *begin();
		}
		reference back() 
		{
			return (tail.p->prev->data);
		}
	public:
		void push_front(const T& value);
		void pop_front();
		void push_back(const T& value);
		void pop_back();
	
	protected: //insert
		template<typename InputIterator>
		void insert_aux(iterator position,InputIterator first,InputIterator last);

	public:
		iterator insert(iterator position,const T& value);
		template<typename InputIterator>
		void insert(iterator position,InputIterator first,InputIterator last);		
	public: //erase
		iterator erase(iterator position);

	protected:
	//并不处理[first,last)先后节点的关系，只适合list.begin(),list.end()调用，请小心食用
		void transfer(iterator position,iterator first,iterator last);

	public:
		void splice(iterator position,list<T,Alloc>& other);


};


}
#include "TinySTL_list_impl.h"
#endif