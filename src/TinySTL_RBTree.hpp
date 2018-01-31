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

	struct rbtree_node_base
	{
		typedef rbtree_node_color color_type;
		

		color_type color;
		rbtree_node_base* parent;
		rbtree_node_base* left;
		rbtree_node_base* right;

		rbtree_node_base():color(_red),parent(0),left(0),right(0) { }

	};

	rbtree_node_base* RBTreeIncrement(rbtree_node_base* p);
	rbtree_node_base* RBTreeDecrement(rbtree_node_base* p);
	rbtree_node_base* RBTreeMinimum(rbtree_node_base* p);
	rbtree_node_base* RBTreeMaximum(rbtree_node_base* p);


	template<typename Value>
	struct rbtree_node:public rbtree_node_base
	{
		Value value;
		rbtree_node(const Value& val):rbtree_node_base(),value(val) { }
	};


	template<typename T,typename Pointer,typename Reference>
	struct rbtree_iterator
	{
		typedef rbtree_iterator<T,Pointer,Reference> this_type;
		typedef rbtree_iterator<T,T*,T&> iterator;
		typedef rbtree_iterator<T,const T*,const T&> const_iterator;

		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef rbtree_node_base base_node_type;
		typedef rbtree_node<T> node_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef bidirectional_iterator_tag iterator_category;

		node_type* p;

		rbtree_iterator();
		rbtree_iterator(node_type* pNode);
		rbtree_iterator(const this_type& x);

		reference operator*()const;
		pointer operator->()const;

		rbtree_iterator& operator++();
		rbtree_iterator operator++(int);

		rbtree_iterator& operator--();
		rbtree_iterator operator--(int);

		bool operator==(const this_type& x){return p==x.p;}
		bool operator!=(const this_type& x){return p!=x.p;}


	};

	template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc = alloc>
	class rb_tree
	{
		public:
			typedef rbtree_node_color color_type;
			typedef ptrdiff_t difference_type;
			typedef size_t size_type;
			typedef Key key_type;
			typedef Value value_type;
			typedef value_type* pointer;
			typedef value_type& reference;
			typedef const value_type* const_pointer;
			typedef const value_type& const_reference;

			typedef rbtree_node<value_type> rbtreeNode;
			typedef rbtreeNode* rbtree_node_ptr;
		
			typedef simple_alloc<rbtreeNode,Alloc> rb_tree_node_allocator;

		public:
			typedef rbtree_iterator<value_type,pointer,reference> iterator;
			typedef rbtree_iterator<value_type,const_pointer,const_reference> const_iterator;

			
		protected:
			rbtree_node_ptr header;
			size_type node_count;
			Compare key_compare;	

		protected:
			//construct / destroy / init
			rbtree_node_ptr getNode();
			rbtree_node_ptr createNode(const Value& val = Value());

			void putNode(rbtree_node_ptr p);
			void deleteNode(rbtree_node_ptr p);

			void init();

		public:
			rb_tree(const Compare& comp);
			~rb_tree();
		protected:
			rbtree_node_ptr& root()const { return (rbtree_node_ptr&)header->parent; }
			rbtree_node_ptr& leftmost() const { return (rbtree_node_ptr&)header->left; }
			rbtree_node_ptr& rightmost() const { return (rbtree_node_ptr&)header->right; }

			static rbtree_node_ptr& left(rbtree_node_ptr x)
			{
				return (rbtree_node_ptr&)(x->left);
			}
			static rbtree_node_ptr& right(rbtree_node_ptr x)
			{
				return (rbtree_node_ptr&)(x->right);
			}
			static rbtree_node_ptr& parent(rbtree_node_ptr x)
			{
				return (rbtree_node_ptr&)(x->parent);
			}
			static reference value(rbtree_node_ptr x)
			{
				return x->value;
			}
			static const key_type& key(rbtree_node_ptr x)
			{
				return KeyOfValue()(value(x));
			}
			static color_type& color(rbtree_node_ptr x)
			{
				return (color_type&)(x->color);
			}

		public:
			iterator begin() {return iterator(leftmost());}
			const_iterator begin()const{return const_iterator(leftmost());}

			iterator end() {return iterator(header);}
			const_iterator end()const {return const_iterator(header);}

			size_type size()const { return node_count; }
			size_type max_size() const { return size_type(-1); }

			bool empty() const { return node_count == 0; }

		protected:
			iterator __insert(rbtree_node_ptr x, rbtree_node_ptr y, const Value& val);
			void rb_tree_rebalance(rbtree_node_ptr z, rbtree_node_ptr& root);
			void rb_tree_rotate_left(rbtree_node_ptr x, rbtree_node_ptr& root);
			void rb_tree_rotate_right(rbtree_node_ptr x, rbtree_node_ptr& root);
			void recurErase(rbtree_node_ptr x);
			rbtree_node_ptr rb_tree_rebalance_for_erase(rbtree_node_ptr z, rbtree_node_ptr& root, rbtree_node_ptr& leftmost, rbtree_node_ptr& rightmost);
			rbtree_node_ptr findRBTree(const value_type& val, bool& isFind);
		public:
			pair<iterator, bool> insert_unique(const Value& val);
			void clear();

			void erase(iterator position);
		
			iterator find(const value_type& val);


		
	};
}


#include "TinySTL_RBTree_node_impl.h"
#include "TinySTL_RBTree_impl.h"
#endif