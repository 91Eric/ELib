#ifndef _STATICARRAY_H_
#define _STATICARRAY_H_
#include "Object.h"
#include "Array.h"
#include <iostream>

namespace ELib
{

template<typename T,int N>
class StaticArray : public Array<T> //此处犯了一个错误  public Array应该带参数，即Array<T> ，自己写成了 Array！！
{
protected:
    T m_space[N];
public:
    StaticArray();
    int length() const;  //请不要忘记const
    StaticArray(const StaticArray<T,N>& e);    //此处使用委托构造StaticArray()也可以
    StaticArray<T,N>& operator =(const StaticArray<T,N>& e);
};

template<typename T,int N>
StaticArray<T,N> :: StaticArray()
{
    this->m_array = m_space;
}

template<typename T,int N>
StaticArray<T,N> :: StaticArray(const StaticArray<T,N>& e)    //此处使用委托构造StaticArray()也可以
{
    this->m_array = this->m_space;  //这一步只是将m_array进行空间的指定，是初始化部分。和拷贝本身无关！！！！
    /*
     !!!!!!!这里存在一个误区 StaticArray<T,5> StaticArray<T,6>是不同的类型，因此不能拷贝或赋值，因此不需要判断最小长度!!!!!!!
    int length = (this->length() < e.length() ? this->length() : e.length());

    for(int i=0;i<length;i++)
        this->m_space[i] = e.m_space[i];
     */
    //正确做法
    for(int i=0;i<N;i++)
        this->m_space[i] = e.m_space[i];
}

template<typename T,int N>
StaticArray<T,N>& StaticArray<T,N>:: operator =(const StaticArray<T,N>& e)
{
    if(this != &e)
    {
        for(int i=0;i<N;i++)
            this->m_space[i] = e.m_space[i];
    }
    return *this;
}

template<typename T,int N>
int StaticArray<T,N> :: length() const
{
    return N;
}



}




#endif // STATICARRAY_H
