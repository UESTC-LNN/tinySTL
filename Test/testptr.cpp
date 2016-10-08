/*************************************************************************
	> File Name: testptr.cpp
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: 2016年09月20日 星期二 11时08分17秒
 ************************************************************************/

#include<iostream>
#include <new>
#include <stdlib.h>
using namespace std;

int main(void){

	void *ptr=malloc(sizeof(int));
	cout<<ptr<<endl;
	int *p=new (ptr) int(2);
	cout<<*p<<endl;
	cout<<p<<endl;
	free(p);
	p=0;
	return 0;

}
