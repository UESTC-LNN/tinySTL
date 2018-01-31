# tinySTL


完成情况：
1、空间分配
2、vector
3、list
4、RBtree
5、set

已经全部实现了基本的功能(find\insert\erase等)，其他拓展功能可通过这些基本功能完成,并提供了一些测试例子。


收获：
看《stl源码剖析》和github https://github.com/electronicarts/EASTL 摸索终于搞定了const_iterator中的一些问题
在这readme上写一下

struct node_base
{
    node* left;
    ……
};
template<typename T>
struct node:public node_base
{
    T value;
};

template<typename T,typename Reference,typename Pointer>
struct nodeIterator
{
    typename T value_type;
    typename Reference reference;
    typename Pointer pointer;
    typename node<T> node_type;
    
    node_type* p;
    
    nodeIterator(node_type* _p):p(_p){}
    
    reference operator*(){……}
    pointer operator->(){……}
};

template<typename Key, typename Value, typename KeyOfValue, typename Compare, typename Alloc = alloc>
class rb_tree
{
public:
			typedef Key key_type;
			typedef Value value_type;
			typedef value_type* pointer;
			typedef value_type& reference;
			typedef const value_type* const_pointer;
			typedef const value_type& const_reference;

			typedef rbtree_iterator<value_type,pointer,reference> iterator;
			typedef rbtree_iterator<value_type,const_pointer,const_reference> const_iterator;
 };
 
 起初看书老是不知道为啥iterator的template参数要带3个(T,Reference,Pointer)，于是自作聪明带一个，于是发生了转换不了的情形，啥原因？
 由于只带一个参数T,所以
 			typedef rbtree_iterator<value_type> iterator;
			typedef rbtree_iterator<const value_type> const_iterator;
      
  于是在iterator和const_iterator的类中：
      node<T>* p;
      node<const T>* p;
     
  这就很尴尬了，比如给我们一个iterator it，如何变成const_iterator？
      it.p是node<T>*类型，并不能用来作为const_iterator构造函数的参数，因为它需要的参数类型是node<const T>* ！
    
  所以这里需要3个参数，此时无论iterator还是const_iterator，其p的类型均为node<T>* 可互相作为参数来构造另外一个！
  两者不同仅在于reference和pointer，所以我们需要3个参数(T,Reference,Pointer)。
  
