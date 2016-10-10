/*************************************************************************
	> File Name: Functional.h
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: 2016年10月10日 星期一 19时20分58秒
 ************************************************************************/
#ifndef __FUNCTIONAL_H
#define __FUNCTIONAL_H
namespace tinySTL{

	template<class T>
	struct less{
		
			typedef T first_argument_type;
			typedef T second_argument_type;
			typedef bool result_type;
		
			bool operator()(T a,T b){
				return a < b;
			}
	};

	template<class T>
	struct equal_to{
		typedef T first_argument_type;
		typedef T second_argument_type;
		typedef bool result_type;

		bool operator()(T a,T b){
			return a == b;
		}
	
	};



}


#endif
