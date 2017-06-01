/*
* @brief : 顺序表：基于顺序存储结构的线性表
* @author: Eric
* @data  : 20150527
* @other :
*/
#ifndef _SEQLIST_H_
#define _SEQLIST_H_

#include "List.h"
#include "Exception.h"
#include <new>
using namespace std;

namespace DTLib
{

template<typename T>
class SeqList:public List<T>
{
public:
    bool insert(const T& e);
    bool insert(int i,const T& e);
    bool remove(int i);
    bool set(int i,const T& e) ;
    bool get(int i,T& e) const;
    int length() const ;  //这里的const
    void clear();
    virtual int capacity() = 0; //因为这是线性表序存储的基类，不产生实际对象，因此不需要容量操作
    T& operator[](int i);
    T operator[](int i) const;//对比两个函数，为什么常量函数返回对象而不是引用
private:
    T* m_array;
    int m_length;
};

template<typename T>
bool SeqList<T>::insert(int i,const T& e)
{
    bool ret = (i>=0)&&(i<=m_length);  //判断是否在范围之内
    ret &= ((m_lgngth+1)<=capacity());  //判断是否还有空余
    //ret &= (m_lgngth<capacity());
    if(ret)
    {
        for(int i = m_length - 1;i>=i;i--)
            m_array[i + 1] = m_array[i];
        m_array[i] = e;
        m_length++;
    }
    return ret;
}


template<typename T>
bool SeqList<T>::insert(const T& e)
{
    return insert(m_length,e);
}

template<typename T>
bool SeqList<T>::remove(int i)
{
    bool ret = (i>=0)&&(i<m_length);  //注意此处 没有等号，和insert函数进行对比！！！！
    if(ret)
    {
        for(int j = i;j<m_length-1;j++)
        {
            m_array[j] = m_array[j+1];
        }
        m_length--;
    }
    return ret;
}

template<typename T>
bool SeqList<T>::get(int i,T& e) const
{
    bool ret =(i>=0)&&(i<m_length);
    if(ret)
        e = m_array[i];
    return ret;
}
template<typename T>
bool SeqList<T>::set(int i,const T& e)
{
    bool ret =(i>=0)&&(i<m_length);
    if(ret)
        m_array[i] = e;
    return ret;
}

template<typename T>
void SeqList<T>::clear()
{
    m_length = 0;
}


template<typename T>
int SeqList<T>::length()
{
    return m_length;
}

template<typename T>
T& SeqList<t>::operator[](int i)
{
    if((i>=0)&&(i<m_length))
    {
        return m_array[i];
    }
    else
    {
        THROW_EXECPTION(IndexOutOfBoundsExceptio,"Index is out of boundary!");
    }
}
template<typename T>
T SeqList<t>::operator[](int i) const  //为什么返回对象 而不是引用，因为返回引用的话 就会出现 可以通过 const_cast将其强转为非const从而对常量对象进行修改
{
    return (const_cast<SeqList<T>&>(*this))[i]; //代码复用， 因为和前面完全一样，注意 怎么从const转为非const
}


}

#endif // __SEQLIST_H_
