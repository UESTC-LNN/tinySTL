/*************************************************************************
	> File Name: Iterator.h
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: 2016年09月11日 星期日 16时10分15秒
 ************************************************************************/
#ifndef __ITERATOR_H
#define __ITERATOR_H

namespace tinySTL{

	struct input_iterator_tag{};
	struct output_iterator_tag{};
	struct forward_iterator_tag:public struct input_iterator_tag{};
	struct bidirectional_iterator_tag:public struct forward_iterator_tag{};
	struct random_access_iterator_tag:public struct bidirectional_iterator_tag{};

	template<class Category,class T,class Distance=ptrdiff_t,class Pointer=T*,class Reference=T&>
	class iterator{
		typedef Category iterator_category;
		typedef T value_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Distance difference_type;
	};

	template<class Iterator>
	class iterator_traits{
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::difference_type difference_type;
	};

	template<class Iterator>
	class iterator_traits<Iterator*>{
		typedef Iterator value_type;
		typedef Iterator* pointer;
		typedef Iterator& reference;
		typedef size_t difference_type;
		typedef random_access_iterator_tag iterator_category;
	
	};

	template<class Iterator>
	class iterator_traits<const Iterator*>{
		typedef Iterator value_type;
		typedef const Iterator* pointer;
		typedef const Iterator& reference;
		typedef size_t difference_type;
		typedef random_access_iterator_tag iterator_category;
	
	};

	template<class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category 
	iterator_category(Iterator iter){
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type*
	difference_type(Iterator iter){
		return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::value_type*
	value_type(Iterator iter){
		return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
	__distance(Iterator first,Iterator last,struct input_iterator_tag){
		typename iterator_traits<Iterator>::difference_type n=0;
		for(;first!=last;++first){
			++n;
		}
		return n;
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
	__distance(Iterator first,Iterator last,struct random_access_iterator_tag){
//		typename iterator_traits<Iterator>::difference_type n=0
		return last-first;
	}

	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type
	distance(Iterator first,Iterator last){
		return __distance(first,last,iterator_category(first));
	}




}


#endif
