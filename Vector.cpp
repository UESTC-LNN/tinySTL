/*************************************************************************
	> File Name: Vector.impl.h
	> Author: hqwu
	> Mail: wfq703@163.com 
	> Created Time: 2016年09月12日 星期一 19时24分37秒
 ************************************************************************/
#include "Vector.h"
namespace tinySTL{

	template<class T,class Alloc >
	iterator vector::allocate_and_fill(size_t n,const T& x){
		iterator result=dataAllocator::allocate(n);
		uninitialized_fill_n(result,n,x);
		return result;
	}
	template<class T,class Alloc>
	iterator insert(iterator position,const T& value){
		if(finish!=end_of_storage){
			tinySTL::construct(finish,*(finish-1));
			copy_backward(position,finish-1,finish);
			*position=value;
			++finish;
			return position;
		}
		else{
			size_type n=1;
			if(capacity()!=0){
				n=2*(end_of_storage-start);
			}
			iterator new_start=dataAllocator::allocate(n);
			iterator i=tinySTL::uninitialized_copy(start,finish,new_start);
			tinySTL::construct(i,value);
			
			destroy(start,finish);
			deallocate();
			
			start=new_start;
			finish=i+1;
			end_of_storage=start+n;
			return	i;
		}
	}
	
	template<class T,class Alloc>
	void vector::insert(iterator position,size_type n,const T& value){
		if(n!=0){
			size_type roomLeft=end_of_storage-finish;
			if(roomLeft>=n){
				size_type left=finish-position;
				if(left>=n){
					tinySTL::uninitialized_copy(finish-n,finish,finish);
					copy_backward(position,finish-n,finish);
					fill_n(position,n,value);
					finish+=n;
				}
				else{
					tinySTL::uninitialized_copy(position,finish,position+n);
					fill_n(position,left,value);
					tinySTL::uninitialized_fill_n(finish,n-left,value);
					finish+=n;
				}
			}
			else{
				size_type old_size=size();
				size_type new_size=old_size+max(old_size,n);
				iterator new_start=dataAllocator::allocate(new_size);
				iterator i=tinySTL::uninitialized_copy(start,position,new_start);
				i=tinySTL::uninitialized_fill_n(i,n,value);
				i=tinySTL::uninitialized_copy(position,finish,i);
				destroy(start,finish);
				deallocate();
				start=new_start;
				finish=i;
				end_of_storage=start+new_size;			
			}
		}
	}

	template<class T,class Alloc >
	void vector::push_back(const T& value){
		if(finish!=end_of_storage){
			tinySTL::construct(finish,value);
			++finish;
		}
		else{
			insert(end(),value);
		}
	}
	template<class T,class Alloc >
	void vector::pop_back(){
		if(start==0 || start==finish){
			return;
		}
		--finish;
		destroy(&*finish);
	}
	template<class T,class Alloc>
	iterator vector::erase(iterator position){
		if(position+1==finish){
			destroy(&*position);
			--finish;
			return finish; 
		}
		difference_type n=position-start;
		copy(position+1,finish,position);
		--finish;
		destroy(&*finish);
		return (start+n);
	}
	template<class T,class Alloc>
	iterator vector::erase(iterator first,iterator last){
		difference_type n=first-start;
		copy(last,finish,first);
		destroy(finish-(last-first),finish);
		finish=finish-(last-first);
		return (start+n);
	}
	template<class T,class Alloc>
	void vector::clear(){
		erase(start,finish);
	}
	
	

}

