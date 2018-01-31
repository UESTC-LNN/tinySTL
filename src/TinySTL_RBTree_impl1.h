/*
#ifndef __TINYSTL_RBTREE_IMPL_H
#define __TINYSTL_RBTREE_IMPL_H

namespace TinySTL
{
//执行前提  不为end()
	template<typename T>
	void rbtreeIterator<T>::increment()
	{
		if(p->right!=0)
		{
			p=p->right;
			while(p->left!=0)
				p=p->left;
		}
		else
		{
			rbtree_node_ptr y = p->parent;
			while(p==y->right)
			{
				p=y;
				y=y->parent;
			}

			if(p->right!=y)
				p=y;

		}
	}
//执行前提  不为begin()
	template<typename T>
	void rbtreeIterator<T>::decrement()
	{
		//if end()?
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
			rbtree_node_ptr y = p->parent;
			while(p==y->left)
			{
				p=y;
				y=y->parent;
			}
			p = y;
		}
	}


	
	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::rbtree_node_ptr rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::getNode()
	{
		return rb_tree_node_allocator::allocate();
	}

	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::rbtree_node_ptr rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::createNode(const Value& val)
	{
		rbtree_node_ptr res=getNode();
		construct(&res->value,val);
		//并未赋值三个指针
		return res;
	}

	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	void rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::putNode(rbtree_node_ptr p)
	{
		rb_tree_node_allocator::deallocate(p);
	}

	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	void rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::deleteNode(rbtree_node_ptr p)
	{
		destroy(&p->value);
		putNode(p);
	}

	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	void rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::init()
	{
		header = createNode();
		leftmost() =header;
		rightmost() = header;
		color(header) = _red;
		root() = 0;
	}


	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::rb_tree(const Compare& comp):node_count(0),key_compare(comp)
	{
		init();
	}

	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	pair<typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::iterator,bool> rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::insert_unique(const Value& val)
	{
		rbtree_node_ptr p = header;
		rbtree_node_ptr x = root();
		bool res = true;;
		while(x != 0)
		{
			p = x;
			res = key_compare(KeyOfValue()(val),key(x));
			if(res)
			{
				x=x->left;
			}
			else
			{
				x=x->right;
			}
		}
		//尚未有一个节点，此时根本没有进入while循环
		if(p==header)
		{
			return pair<iterator,bool>(__insert(x,p,val),true);
		}
		
		iterator j = iterator(p);
		if(res)
		{
			if(j==begin())
			{
				return pair<iterator,bool>(__insert(x,p,val),true);
			}
			else
			{
				--j;
			}
		}

		if(key_compare(key(j.p),KeyOfValue()(val)))
		{
			return pair<iterator,bool>(__insert(x,p,val),true);
		}
		
		return pair<iterator,bool>(j,false);


	}

	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::iterator rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::__insert(rbtree_node_ptr x,rbtree_node_ptr y,const Value& val)
	{
		rbtree_node_ptr z;
		if(y==header || key_compare(KeyOfValue()(val),key(y)))
		{
			z=createNode(val);
			left(y) = z;
			if(y==header)
			{
				root() = z;
				rightmost() = z;
			}
			else if(y == leftmost())
			{
				leftmost() = z;
			}

		}
		else
		{
			z=createNode(val);
			right(y) = z;
			if(rightmost() == y)
			{
				rightmost() = z;
			}
		}

		parent(z) = y;
		left(z) = 0;
		right(z) = 0;

		rb_tree_rebalance(z,header->parent);
		++node_count;
		return iterator(z);


	}



	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	void rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::rb_tree_rebalance(rbtree_node_ptr z,rbtree_node_ptr& root)
	{
		z->color = _red;
		while(z!=root && z->parent->color == _red)
		{
			if(z->parent == z->parent->parent->left)
			{
				rbtree_node_ptr s = z->parent->parent->right;
				if(s!=0 && s->color == _red)
				{
					s->color = _black;
					z->parent->color = _black;
					z->parent->parent->color = _red;
					z = z->parent->parent;

				}
				else
				{
					if(z == z->parent->right)
					{
						z = z->parent;
						rb_tree_rotate_left(z,root);
					}
					z->parent->parent->color = _red;
					z->parent->color =_black;
					rb_tree_rotate_right(z->parent->parent,root);
				}
			
			}
			else
			{
				rbtree_node_ptr s = z->parent->parent->left;
				if(s!=0 && s->color == _red)
				{
					s->color = _black;
					z->parent->color = _black;
					z->parent->parent->color = _red;
					z = z->parent->parent;
				}
				else
				{
					if(z == z->parent->left)
					{
						z=z->parent;
						rb_tree_rotate_right(z,root);
					}
					z->parent->parent->color = _red;
					z->parent->color =_black;
					rb_tree_rotate_left(z->parent->parent,root);
					
				}
			
			}


		}
		root->color = _black;
	}

	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	void rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::rb_tree_rotate_left(rbtree_node_ptr x,rbtree_node_ptr& root)
	{
		rbtree_node_ptr y = x->right;
		x->right = y->left;
		if(y->left !=0 )
			y->left->parent = x;

		y->parent = x->parent;
		if(x==root)
			root = y;
		else if(x->parent->left == x)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
		
		x->parent = y;
		y->left = x;

	}


	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	void rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::rb_tree_rotate_right(rbtree_node_ptr x,rbtree_node_ptr& root)
	{
		rbtree_node_ptr y = x->left;
		x->left = y->right;
		if(y->right!=0)
			y->right->parent = x;

		y->parent = x->parent;
		if(x==root)
			y=root;
		else if(x->parent->left == x)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right =y;
		}

		x->parent = y;
		y->right = x;
	}


	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	void rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::erase(iterator position)
	{
		rbtree_node_ptr to_be_delete = rb_tree_rebalance_for_erase(position.p,root(),leftmost(),rightmost());
		deleteNode(to_be_delete);
		--node_count;
	}
	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::rbtree_node_ptr 
	rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::rb_tree_rebalance_for_erase(rbtree_node_ptr z,rbtree_node_ptr& root,rbtree_node_ptr& leftmost,rbtree_node_ptr& rightmost)
	{
		rbtree_node_ptr y = z;		//实际删除的节点
		rbtree_node_ptr x = 0;     //替代z(y)的节点
		rbtree_node_ptr x_parent;	//删除之后 x 的父节点
		
		if(y->left == 0)                 //这里帮找实际需要删除的y节点  以及 y的子节点 x(上位y)
		{
			x = y->right;
		}
		else if(y->right == 0)
		{
			x = y->left;
		}
		else
		{
			y = y->right;
			while(y->left != 0)
				y = y->left;
			x = y->right;
		}

		if(y == z)
		{
			x_parent = y->parent;
			if(z == root)
			{
				root = x;
			}
			else if(z == z->parent->left)
			{
				z->parent->left = x;
			}
			else
			{
				z->parent->right = x;
			}

			if(x != 0) x->parent = z->parent;

			if(z == leftmost)
			{
				if(z->right == 0 )
					leftmost = z->parent;
				else
					leftmost = rbtree_node<Value>::minimum(x);
			}

			if(z == rightmost)
			{
				if(z->left == 0)
					rightmost = z->parent;
				else
					rightmost = rbtree_node<Value>::maximum(x);
			}
		}
		else
		{
			y->left = z->left;
			z->left->parent = y;
			if(z->right!=y)
			{
				x_parent = y->parent;
				if(x!=0) x->parent = y->parent;
				y->parent->left = x;

				y->right = z->right;
				z->right->parent = y;
			}
			else
			{
				x_parent = y;
			}

			if(z == root)
			{
				root = y;
			}
			else if(z == z->parent->left)
			{
				z->parent->left = y;
			}
			else
			{
				z->parent->right = y;
			}
			y->parent = z->parent;

			swap(y->color,z->color);
			y = z;
		}

		// y： 待删节点   x： 替换y的节点(鸠占鹊巢),此时x也成为标记节点   x_parent: x的父节点
		if(y->color!=_red)
		{
			while(x!=root && (x==0 || x->color == _black))  //为双黑色节点
			{
				if(x == x_parent->left)
				{
					rbtree_node_ptr w = x_parent->right;
					if(w->color == _red)
					{
						w->color = _black;
						x_parent->color = _red;
						rb_tree_rotate_left(x_parent,root);
						w=x_parent->right;
					}
					if((w->left==0 || w->left->color==_black) &&(w->right==0 || w->right->color==_black))
					{
						w->color = _red;
						x = x_parent;
						x_parent = x_parent->parent;
					}
					else
					{
						if(w->right == 0 || w->right->color == _black)
						{
							if(w->left!=0)
								w->left->color = _black;
							w->right->color = _red;
							rb_tree_rotate_right(w,root);
							w = x_parent->right;
						}
						w->color = x_parent->color;
						x_parent->color = _black;
						if(w->right!=0)
							w->right->color = _black;
						rb_tree_rotate_left(x_parent,root);
						break;
					}

				}
				else
				{
					rbtree_node_ptr w = x_parent->left;
					if(w->color == _red)
					{
						w->color = _black;
						x_parent->color = _red;
						rb_tree_rotate_right(x_parent,root);
						w = x_parent->left;
					}

					if((w->left==0||w->left->color==_black)&&(w->right==0||w->right->color==_black))
					{
						w->color = _red;
						x = x_parent;
						x_parent = x_parent->parent;
					}
					else
					{
						if(w->left==0 || w->left->color == _black)
						{
							if(w->right!=0)
								w->right->color = _black;
							w->color = _red;
							rb_tree_rotate_left(w,root);
							w = x_parent->left;
						}
						w->color = x_parent->color;
						x_parent->color = _black;
						if(w->left!=0)
							w->left->color = _black;
						rb_tree_rotate_right(x_parent,root);
						break;
					}
				
				
				}
			}
			if(x!=0) x->color =_black;
		}

		return y;


	}

	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	void rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::clear()
	{
		recurErase(header->parent);
		header->left  = header;
		header->right = header;
		header->parent = 0;

	
	}

	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	void rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::recurErase(rbtree_node_ptr x)
	{
		if(x!=0)
		{
			recurErase(x->left);
			recurErase(x->right);
			deleteNode(x);
		}
	}

	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::~rb_tree()
	{
		clear();
		deleteNode(header);
	}

	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::iterator rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::find(const value_type& val)
	{
		bool isFind = false;
		rbtree_node_ptr res = findRBTree(val,isFind);
		if(isFind)
		{
			return iterator(res);
		}
		else
		{
			return end();
		}
	}

	template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc>
	typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::rbtree_node_ptr 
	rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::findRBTree(const value_type& val,bool& isFind)
	{
		rbtree_node_ptr res = header->parent;
		isFind = false;
		while(res!=0)
		{
			if(key_compare(KeyOfValue()(val),key(res)))
			{
				res = res->left;
			}
			else
			{
				if(key_compare(key(res),KeyOfValue()(val)))
				{
					
				}
				else
				{
					isFind = true;
					break;
				}
			}
		}
		return res;
	}


}
#endif

*/