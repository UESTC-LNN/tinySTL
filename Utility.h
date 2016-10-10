/*************************************************************************
	> File Name: Utility.h
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: 2016年10月09日 星期日 20时28分16秒
 ************************************************************************/
#ifndef __UTILITY_H
#define __UTILITY_H

namespace tinySTL{

	template <class T>
	void swap(T a,T b){
		T temp=b;
		b=a;
		a=temp;
	}

	template<class T1,class T2>
	class pair{
		public:
			typedef T1 first_type;
			typedef T2 second_type;

		public:
			T1 first;
			T2 second;

		public:
			pair(){}
			template<class U,class V>
			pair(const pair<U,V>& x):first(x.first),second(x.second){}

			pair(const first_type& a,const second_type& b):first(a),second(b){}

		public:
			pair& operator=(const pair& pr){
				first=pr.first;
				second=pr.second;
				return *this;
			}
			void swap(pair& pr){
				tinySTL::swap(first,pr.first);
				tinySTL::swap(second,pr.second);
			}

		public:
			template<class T1,class T2>
			friend bool operator==(const pair<T1,T2>& a,const pair<T1,T2>& b );
			template<class T1,class T2>
			friend bool operator!=(const pair<T1,T2>& a,const pair<T1,T2>& b );
			template<class T1,class T2>
			friend bool operator>(const pair<T1,T2>& a,const pair<T1,T2>&  b);
			template<class T1,class T2>
			friend bool operator<(const pair<T1,T2>& a,const pair<T1,T2>&  b);
			template<class T1,class T2>
			friend bool operator>=(const pair<T1,T2>& a,const pair<T1,T2>&  b);
			template<class T1,class T2>
			friend bool operator<=(const pair<T1,T2>& a,const pair<T1,T2>&  b);
			template<class T1,class T2>
			friend void swap(pair<T1,T2>& a,pair<T1,T2>& b);

	};

	
			template<class T1,class T2>
			friend bool operator==(const pair<T1,T2>& a,const pair<T1,T2>& b ){
				return a.first==b.first && a.second==b.second;
			}
			template<class T1,class T2>
			friend bool operator!=(const pair<T1,T2>& a,const pair<T1,T2>& b ){
				return a.first!=b.first || a.second!=b.second;
			}
			template<class T1,class T2>
			friend bool operator>(const pair<T1,T2>& a,const pair<T1,T2>& b ){
				return a.first>b.first || (a.first==b.first && a.second>b.second);
			}
			template<class T1,class T2>
			friend bool operator<(const pair<T1,T2>& a,const pair<T1,T2>& b ){
				return a.first<b.first || (a.first==b.first && a.second<b.second);
			}
			template<class T1,class T2>
			friend bool operator>=(const pair<T1,T2>& a,const pair<T1,T2>& b ){
				return !(a<b);
			}
			template<class T1,class T2>
			friend bool operator<=(const pair<T1,T2>& a,const pair<T1,T2>& b ){
				return !(a>b);
			}
			template<class T1,class T2>
			friend void swap(pair<T1,T2>& a,pair<T1,T2>& b){
				a.swap(b);
			}

			template<class U,class V>
			pair<U,V> make_pair(const U& u,const V& v){
				return pair<U,V>(u,v);
			}
} 


#endif
