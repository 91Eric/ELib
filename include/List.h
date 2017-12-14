#ifndef _LIST_H_
#define _LIST_H_

#include "Object.h"

namespace ELib
{
template<typename T>
class List : public Object
{
protected:
    List(const T&);    //容器类一般要禁止拷贝和赋值操作，因在顶层类中把这两个函数设置为protected即可，不需要private或者使用delete说明符
    List<T>& operator=(const T&);  //由于在类内，所以 T 可以省略  List& operator=(const T&);
public:
    List(){}   //由于上面提供了拷贝函数，因此需要自己添加默认构造函数，否则没法生成子类对象！知识点：继承中的构造，默认构造函数
    virtual bool insert(const T& e) =0; //尾插
    virtual bool insert(int i,const T& e) = 0;
    virtual bool remove(int i) = 0;
    virtual bool set(int i,const T& e) = 0;
    virtual bool get(int i,T& e) const = 0;
    virtual int find(const T& e) const = 0;  //由于相等运算符的使用，如果使用自定义类型那么久的定义自己的==重载函数，我觉得可以
    virtual int length() const = 0;  //这里的const
    virtual void clear() = 0;
};

}

#endif // _LIST_H_


