/*************************************************************************
	> File Name: testObj.cpp
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: Fri 09 Sep 2016 01:56:30 PM CST
 ************************************************************************/
#include <iostream>
using namespace std;

union obj{
	union obj *link;
	char client_data[1];
};

int main(){
	char v1[10]={1,2,3,4,5,6,7,8,9,10};
	char v2[10]={11,12,13,14,15,16,17,18,19,20};

	union obj *p=(union obj*)v1;
	p->link=(union obj*)v2;

	cout<<"             union obj p  "<<(void*)v1<<endl;
	cout<<"       union obj p->link  "<<(void*)p->link<<endl;
	cout<<"union obj p->client_data  "<<(void*)p->client_data<<endl;
	return 0;
	


}
