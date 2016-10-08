/*************************************************************************
	> File Name: testABjicheng.cpp
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: 2016年09月28日 星期三 10时28分17秒
 ************************************************************************/

#include<iostream>
using namespace std;

class A{
	public:
	bool x;
	A *left;
	A *right;
	explicit A(bool a=0):x(a),left(NULL),right(NULL){}

};

class B:public A{
	
	public:
	int u;
	B(bool a,int k=0):A(a),u(k){
	
	}
	B(const A &a,int k=0){
		x=a.x;
		left=a.left;
		right=a.right;
		u=k;
	}
	
};
int& getU(A* x){
	return ((B*)x)->u;
}

int main(){
	B b(1,1);
	b.left=(A*)&b;
	b.right=(A*)&b;

	A *qqq=b.left;
	cout<<((B*)qqq)->u<<endl;
	int &hh=getU(qqq);
	hh=2;
	cout<<getU(qqq)<<endl;
	return 0;

}
