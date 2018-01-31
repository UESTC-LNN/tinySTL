#ifndef __TINYSTL_LIST_IMPL_H
#define __TINYSTL_LIST_IMPL_H

namespace TinySTL
{

	template<typename T,typename Alloc>
	typename list<T,Alloc>::nodePtr list<T,Alloc>::newNode(const T& value)
	{
		nodePtr ptr=list_node_allocator::allocate();
		construct(ptr,node<T>(value));
		return ptr;
	}
	template<typename T,typename Alloc>
	void list<T,Alloc>::deleteNode(nodePtr p)
	{
		p->prev = p->next = 0;
		destroy(p);
		list_node_allocator::deallocate(p);
	}

	template<typename T,typename Alloc>
	list<T,Alloc>::list()
	{
		head.p=newNode();
		tail.p=head.p;
	}

	template<typename T,typename Alloc>
	void list<T,Alloc>::push_front(const T& value)
	{
		nodePtr newnode = newNode(value);
		newnode->next = head.p;
		head.p->prev = newnode;
		head.p = newnode;
	}
	template<typename T,typename Alloc>
	void list<T,Alloc>::pop_front()
	{
		nodePtr nextnode = head.p->next;
		nextnode->prev = 0;
		nodePtr tmp  = head.p;
		head.p=nextnode;
		deleteNode(tmp);
	}

	template<typename T,typename Alloc>
	void list<T,Alloc>::push_back(const T& value)
	{
		nodePtr newnode = newNode();
		newnode->prev = tail.p;
		tail.p->next = newnode;
		tail.p->data = value;
		tail.p = newnode;
	}

	template<typename T,typename Alloc>
	void list<T,Alloc>::pop_back()
	{
		nodePtr prevnode = tail.p->prev;
		prevnode->next = 0;
		nodePtr tmp  = tail.p;
		tail.p = prevnode;
		deleteNode(tmp);
	}
	template<typename T,typename Alloc>
	list<T,Alloc>::~list()
	{
		
		for(;head!=tail;)
		{
			nodePtr tmpnode= head.p;
			++head;
			deleteNode(tmpnode);

		}
		deleteNode(tail.p);
	
	}

	template<typename T,typename Alloc>
	template<typename InputIterator>
	void list<T,Alloc>::insert_aux(iterator position,InputIterator first,InputIterator last)
	{
		for(--last;first!=last;--last)
		{
			position = insert(position,*first);
		}
		insert(position,*last);
	}


	template<typename T,typename Alloc>
	typename list<T,Alloc>::iterator list<T,Alloc>::insert(iterator position,const T& value)
	{
		if(position == begin())
		{
			push_front(value);
			return head;
		}
		else if(position == end())
		{
			//fixme：有点bug 不是返回tail
			iterator ret = position;
			push_back(value);
			return ret;
		}
		else
		{
			nodePtr newnode = newNode(value);
			nodePtr prevnode = position.p->prev;
			prevnode->next = newnode;
			newnode->prev = prevnode;
			newnode->next = position.p;
			position.p->prev = newnode;
			position.p = newnode;
			return position;
		}
	}
	template<typename T,typename Alloc>
	typename list<T,Alloc>::iterator list<T,Alloc>::erase(iterator position)
	{
		if(position == begin())
		{
			pop_front();
			return begin();
		}
		else if(position == end())
		{
			//实际应该弹出异常,这里直接返回end()，不做改动
			return end();
		}
		else
		{
			nodePtr prevNode = position.p->prev;
			nodePtr nextNode = position.p->next;
			prevNode->next = nextNode;
			nextNode->prev = prevNode;
			deleteNode(position.p);
			return iterator(nextNode);
		}
	}

	template<typename T,typename Alloc>
	template<typename InputIterator>
	void list<T,Alloc>::insert(iterator position,InputIterator first,InputIterator last)
	{
		insert_aux(position,first,last);
	}


	template<typename T,typename Alloc>
	void list<T,Alloc>::transfer(iterator position,iterator first,iterator last)
	{
		if(first==last) 
			return;

		if(position == begin())
		{
			nodePtr old_head = position.p;
			nodePtr lastPrev = last.p->prev;
			first.p->prev = 0;
			head.p = first.p;
			old_head->prev = lastPrev;
			lastPrev->next = old_head;
		}
		else
		{
			nodePtr positionPrev = position.p->prev;
			nodePtr lastPrev = last.p->prev;
			positionPrev->next = first.p;
			first.p->prev = positionPrev;
			position.p->prev = lastPrev;
			lastPrev->next = position.p;
		}
	}

	template<typename T,typename Alloc>
	void list<T,Alloc>::splice(iterator position,list<T,Alloc>& other)
	{
		transfer(position,other.begin(),other.end());
		other.head = other.tail;
		nodePtr dummyNode = tail.p;
		dummyNode->prev =dummyNode->next =0;

	}




}

#endif