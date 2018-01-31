#ifndef __TINYSTL_SET_HPP
#define __TINYSTL_SET_HPP

#include "TinySTL_RBTree.hpp"
#include "TinySTL_function.hpp"
#include "TinySTL_alloc.h"
#include "TinySTL_pair.hpp"

namespace TinySTL
{

template<typename Key,typename Compare=less<Key>,typename Alloc = alloc>
class set
{
public:
	typedef Key key_value;
	typedef Key value_type;
	typedef Compare key_compare;
	typedef Compare value_compare;

private:
	typedef rb_tree<key_value,value_type,identity<Key>,key_compare,Alloc> rep_type;

	rep_type t;

public:
	typedef typename rep_type::const_pointer pointer;
	typedef typename rep_type::const_pointer const_pointer;
	typedef typename rep_type::const_reference reference;
	typedef typename rep_type::const_reference const_reference;
	typedef typename rep_type::const_iterator iterator;
	typedef typename rep_type::const_iterator const_iterator;

	typedef typename rep_type::size_type size_type;

public:
	set():t(Compare()){}

public:
	iterator begin()const {return t.begin();}
	iterator end()const {return t.end();}

	bool empty()const {return t.empty();}
	size_type size()const {return t.size();}

	pair<iterator,bool> insert(const value_type& val)
	{
		pair<typename rep_type::iterator,bool> p=t.insert_unique(val);
		return pair<iterator,bool>(iterator(p.first.p),p.second);
	}

	void erase(iterator position)
	{
		typename rep_type::iterator tmp(position.p);
		t.erase(tmp);
	}
};


}


#endif