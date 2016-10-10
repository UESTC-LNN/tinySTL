/*************************************************************************
	> File Name: testAlgorithmFill.cpp
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: 2016年10月10日 星期一 20时00分21秒
 ************************************************************************/

#include<iostream>
#include "../Algorithm.h"

int main(){

	wchar_t s[10];
	tinySTL::fill(s,s+10,wchar_t(10));
	for(int i=0;i<10;++i){
		std::cout<<s[i]<<"  ";
	}
	std::cout<<std::endl;
	tinySTL::fill(s,s+10,wchar_t(-1));
	for(int i=0;i<10;++i){
		std::cout<<s[i]<<"  ";
	}
	std::cout<<std::endl;
	tinySTL::fill(s,s+10,wchar_t(266));
	for(int i=0;i<10;++i){
		std::cout<<s[i]<<"  ";
	}
	std::cout<<std::endl;
	

	return 0;

}
