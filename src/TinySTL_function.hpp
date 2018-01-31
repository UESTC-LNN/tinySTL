#ifndef __TINYSTL_FUNCTION_HPP
#define __TINYSTL_FUNCTION_HPP

//include  unary_function /  binary_function  / identity 



namespace TinySTL
{

//一元
template<typename Arg,typename Result>
struct unary_function
{
	typedef Arg argument_type;
	typedef Result result_type;
};


template<typename Arg1,typename Arg2,typename Result>
struct binary_function
{
	typedef Arg1 first_argument_type;
	typedef Arg2 second_argument_type;
	typedef Result result_type;
};

template<typename T>
struct identity:public unary_function<T,T>
{
	const T& operator()(const T& x) const {return x;}
};

template<class pair>
struct select1st:public unary_function<pair,typename pair::first_type>
{
	const typename pair::first_type& operator()(const pair& x) const
	{
		return x.first;
	}
};

template<class pair>
struct select2nd:public unary_function<pair,typename pair::second_type>
{
	const typename pair::second_type& operator()(const pair& x) const
	{
		return x.second;
	}
};


template<typename T>
struct less:public binary_function<T,T,bool>
{
	bool operator()(const T& x,const T& y)const
	{
		return x<y;
	}
};

template<typename T>
struct greater:public binary_function<T,T,bool>
{
	bool operator()(const T& x,const T& y)const
	{
		return x>y;
	}
};


}

#endif