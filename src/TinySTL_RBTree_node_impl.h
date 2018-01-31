#ifndef __TINYSTL_RBTREE_NODE_IMPL_H
#define __TINYSTL_RBTREE_NODE_IMPL_H

namespace TinySTL
{

	rbtree_node_base* RBTreeIncrement(rbtree_node_base* p)
	{
		if(p->right!=0)
		{
			p=p->right;
			while(p->left!=0)
				p=p->left;
		}
		else
		{
			rbtree_node_base* y = p->parent;
			while(p==y->right)
			{
				p=y;
				y=y->parent;
			}

			if(p->right!=y)
				p=y;

		}
		return p;
	}

	rbtree_node_base* RBTreeDecrement(rbtree_node_base* p)
	{
		if(p->color==_red && p->parent->parent==p)
			p=p->right;
		else if(p->left!=0)
		{
			p=p->left;
			while(p->right!=0)
				p=p->right;
		}
		else 
		{
			rbtree_node_base* y = p->parent;
			while(p==y->left)
			{
				p=y;
				y=y->parent;
			}
			p = y;
		}
		return p;
	}

	rbtree_node_base* RBTreeMinimum(rbtree_node_base* p)
	{
		while(p->left!=0)
			p=p->left;
		return p;

	}
	rbtree_node_base* RBTreeMaximum(rbtree_node_base* p)
	{
		while(p->right!=0)
			p=p->right;
		return p;
	}


	template<typename T,typename Pointer,typename Reference>
	rbtree_iterator<T,Pointer,Reference>::rbtree_iterator():p(0)
	{
	
	}

	template<typename T,typename Pointer,typename Reference>
	rbtree_iterator<T,Pointer,Reference>::rbtree_iterator(node_type* pNode):p(pNode)
	{
	
	}

	template<typename T,typename Pointer,typename Reference>
	rbtree_iterator<T,Pointer,Reference>::rbtree_iterator(const this_type& x):p(x.p)
	{
	
	}

	template<typename T,typename Pointer,typename Reference>
	typename rbtree_iterator<T,Pointer,Reference>::reference rbtree_iterator<T,Pointer,Reference>::operator*()const
	{
		return p->value;
	}

	template<typename T,typename Pointer,typename Reference>
	typename rbtree_iterator<T,Pointer,Reference>::pointer rbtree_iterator<T,Pointer,Reference>::operator->()const
	{
		return &(p->value);
	}

	template<typename T,typename Pointer,typename Reference>
	typename rbtree_iterator<T,Pointer,Reference>::this_type& rbtree_iterator<T,Pointer,Reference>::operator++()
	{
		p = static_cast<node_type*>(RBTreeIncrement(p));
		return *this;
	}

	template<typename T,typename Pointer,typename Reference>
	typename rbtree_iterator<T,Pointer,Reference>::this_type rbtree_iterator<T,Pointer,Reference>::operator++(int)
	{
		this_type tmp(*this);
		p = static_cast<node_type*>(RBTreeIncrement(p));
		return tmp;
	}

	template<typename T,typename Pointer,typename Reference>
	typename rbtree_iterator<T,Pointer,Reference>::this_type& rbtree_iterator<T,Pointer,Reference>::operator--()
	{
		p = static_cast<node_type*>(RBTreeDecrement(p));
		return *this;
	}

	template<typename T,typename Pointer,typename Reference>
	typename rbtree_iterator<T,Pointer,Reference>::this_type rbtree_iterator<T,Pointer,Reference>::operator--(int)
	{
		this_type tmp(*this);
		p = static_cast<node_type*>(RBTreeDecrement(p));
		return *this;
	}



}
#endif