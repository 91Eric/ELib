/*
* @brief :
* @author: Eric
* @data:
* @other: 修改get函数为const函数，原先没有，这是一个bug
*/
#ifndef _ARRAY_H_
#define _ARRAY_H_
#include "Object.h"
#include "Exception.h"

namespace ELib
{

//Defination of Array template
template<typename T>
class Array:public Object
{
protected:
    T *m_array;
public:
    virtual bool get(int i ,T& e) const;
    virtual bool set(int i,const T& e);
    virtual int length() const = 0;

    T& operator[](int i);
    T operator [](int i) const;
};

//Implementation of Array template

template<typename T>
bool Array<T> :: get(int i ,T& e) const
{
    bool ret = ((i>=0)&&(i<length()));
    if(ret)
    {
        e = m_array[i];
    }
    else
    {
         THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary!");
    }
    return ret;
}

template<typename T>
bool Array<T> :: set(int i,const T& e)
{
    //此处不等于length的原因是：如果是length那么就是当前元素已有的末尾，假设数组已经满员，那么势必造成越界，因此此处编程假定，只在已经
     bool ret = ((i>=0)&&(i<length()));
     if(ret)
     {
         m_array[i] = e;
     }
     return ret;
 }

template<typename T>
T& Array<T> :: operator[](int i)
{
    cout<<"...."<<endl;
      if((i>=0)&&(i<length()))
      {
          return  m_array[i];
      }
      else
      {
           THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary!");
      }
}

template<typename T>
T Array<T> :: operator [](int i) const
{
    cout<<"!!!"<<endl;
    return (const_cast<Array<T>&>(*this))[i]; //代码复用
}



}


#endif // ARRAY_H
