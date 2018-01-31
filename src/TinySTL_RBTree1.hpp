/*
#ifndef __TINYSTL_RBTREE_HPP
#define __TINYSTL_RBTREE_HPP

#include "IteratorTiny.hpp"
#include "TinySTL_alloc.h" //compile require TinySTL_alloc.cc file
#include "TinySTL_construct.hpp"
#include "TinySTL_pair.hpp"
#include "TinySTL_algorithm.hpp"

namespace TinySTL
{

typedef bool rbtree_node_color;
const rbtree_node_color _red = true;
const rbtree_node_color _black = false;



template<typename T>
struct rbtree_node
{
	typedef rbtree_node_color color_type;
	typedef rbtree_node<T>* rbtree_node_ptr;

	color_type color;
	T value;
	rbtree_node_ptr parent;
	rbtree_node_ptr left;
	rbtree_node_ptr right;
	
	rbtree_node(color_type co,const T& val,rbtree_node_ptr pa,rbtree_node_ptr le,rbtree_node_ptr ri):color(co),value(val),parent(pa),left(le),right(ri){}
	static rbtree_node_ptr minimum(rbtree_node_ptr x)
	{
		while(x->left != 0)
			x = x->left;
		return x;
	}

	static rbtree_node_ptr maximum(rbtree_node_ptr x)
	{
		while(x->right != 0)
			x = x->right;
		return x;
	}
};

template<typename T>
struct rbtreeIterator
{
	typedef bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef value_type* pointer;
	typedef value_type& reference;

	typedef  typename rbtree_node<T>::color_type color_type; 
	typedef  typename rbtree_node<T>::rbtree_node_ptr rbtree_node_ptr;
	typedef rbtree_node<T> rbtreeNode;

	typedef rbtreeIterator<T> self;
	rbtree_node_ptr p;

	rbtreeIterator(const rbtree_node_ptr& _p = 0):p(_p){}
	bool operator==(const self& x)
	{
		return p==x.p;
	}

	bool operator!=(const self& x)
	{
		return p!=x.p;
	}

	void increment();
	void decrement();

	reference operator*()const {return p->value;}
	pointer operator->()const {return &(p->value);}

	self& operator++() {increment();return *this;}
	self operator++(int) {self tmp = *this;increment();return tmp;}

	self& operator--() {decrement();return *this;}
	self operator--(int) {self tmp = *this;decrement();return tmp;}
	

};

template<typename Key,typename Value,typename KeyOfValue,typename Compare,typename Alloc = alloc>
class rb_tree
{
public:
	typedef rbtreeIterator<Value> iterator;
	typedef rbtreeIterator<const Value> const_iterator;
	
public:
	typedef rbtree_node<Value> rbtreeNode;
	typedef rbtreeNode* rbtree_node_ptr;
	typedef rbtree_node<const Value> rbtreeConstNode;
	typedef rbtreeConstNode* rbtree_const_node_ptr;
	typedef rbtree_node_color color_type;
	typedef simple_alloc<rbtreeNode,Alloc> rb_tree_node_allocator;

	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef Key key_type;
	typedef Value value_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;


protected:
	rbtree_node_ptr header;
	size_type node_count;
	Compare key_compare;

protected:

//construct / destroy / init
	rbtree_node_ptr getNode();
	rbtree_node_ptr createNode(const Value& val=Value());

	void putNode(rbtree_node_ptr p);
	void deleteNode(rbtree_node_ptr p);
	
	void init();
public:
	rb_tree(const Compare& comp);
	~rb_tree();
protected:
	rbtree_node_ptr& root()const {return header->parent;}
	rbtree_node_ptr& leftmost() const {return header->left;}
	rbtree_node_ptr& rightmost() const {return header->right;}

	//以下是取得rbtree_node_ptr x的各项成员的便捷函数
	static rbtree_node_ptr& left(rbtree_node_ptr x){return x->left;}
	static rbtree_node_ptr& right(rbtree_node_ptr x){return x->right;}
	static rbtree_node_ptr& parent(rbtree_node_ptr x){return x->parent;}
	static reference value(rbtree_node_ptr x) {return x->value;}
	static const Key& key(rbtree_node_ptr x) {return KeyOfValue()(value(x));}
	static color_type& color(rbtree_node_ptr x) {return x->color;}

public:
	//iterator
	
	const_iterator changeIteratorToConstIterator(iterator& it)
	{
		
		rbtreeConstNode node(it.p->color,it.p->value,(rbtree_const_node_ptr)(it.p->parent),(rbtree_const_node_ptr)(it.p->left),(rbtree_const_node_ptr)(it.p->right));
		return const_iterator(&node);
	}

	iterator begin() {return iterator(leftmost());}
	const_iterator begin()const
	{
		iterator temp(leftmost());
		return changeIteratorToConstIterator(temp);
	}
	iterator end() { return iterator(header); }
	const_iterator end()const 
	{ 
		iterator temp(leftmost());
		return changeIteratorToConstIterator(temp); 
	}
	//size / capacity
	size_type size()const {return node_count;}
	size_type max_size() const {return size_type(-1);}
	bool empty() const {return node_count==0;}

	rbtree_node_ptr findRBTree(const value_type& val,bool& isFind);
protected:
	iterator __insert(rbtree_node_ptr x,rbtree_node_ptr y,const Value& val);
	 
	void rb_tree_rebalance(rbtree_node_ptr z,rbtree_node_ptr& root);

	void rb_tree_rotate_left(rbtree_node_ptr x,rbtree_node_ptr& root);
	void rb_tree_rotate_right(rbtree_node_ptr x,rbtree_node_ptr& root);
	rbtree_node_ptr rb_tree_rebalance_for_erase(rbtree_node_ptr z,rbtree_node_ptr& root,rbtree_node_ptr& leftmost,rbtree_node_ptr& rightmost);
	
	void recurErase(rbtree_node_ptr x);
public:
	pair<iterator,bool> insert_unique(const Value& val);
	void erase(iterator position);
	void clear();
	iterator find(const value_type& val);

};


}


#include "TinySTL_RBTree_node_impl.h"
#include "TinySTL_RBTree_impl.h"
#endif
*/