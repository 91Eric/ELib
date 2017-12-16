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

namespace ELib
{

/*
* @Class Description :线性表顺序存储结构顶层父类，使用m_array作为内存分配的媒介，具体分配交给子类
* @Other :虽然重载了数组操作符，但是他只能用在已经插入之后的元素获取或者修改，这一点对比数组类
*/

template<typename T>
class SeqList:public List<T>
{
public:
    bool insert(const T& e);
    bool insert(int i,const T& e);
    bool remove(int i);
    bool set(int i,const T& e) ;
    bool get(int i,T& e) const;
    int length() const ;  //这里的const，原因在于非const对象可以转换为const对象，因此提供const版本的，可以省去非const版本
    void clear();
    virtual int capacity() = 0; //因为这是线性表顺序存储的基类，不产生实际对象，因此不需要容量操作
    int find(const T& e) const;

    /*
    这里需要重载运算符的原因是，我们将真正的内存分配交给了子类，只是通过m_array这个指针进行操作，
    */
    T& operator[](int i);
    T operator[](int i) const;//对比两个函数，为什么常量函数返回对象而不是引用
protected:
    T* m_array;
    int m_length;
};

template<typename T>
bool SeqList<T>::insert(int i,const T& e)   //这里使用const原因在于，如果使用 sl.insert(1),这种方式不会报错，否则会报错
{
    bool ret = (i>=0)&&(i<=m_length);  //判断是否在范围之内,因为必须在已经插入的元素范围内插入元素,等于时是尾插
    ret &= ((m_length+1)<=capacity());  //判断是否还有空余
    if(ret)
    {
        for(int j = m_length - 1;j >= i;j--)
        {
            m_array[j + 1] = m_array[j];
        }
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
    bool ret = (i>=0)&&(i < m_length);  //注意此处 没有等号，和insert函数进行对比！！！！,没有等号可以防止超出范围，或者元素为空时，删除0位置
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
    bool ret =(i>=0)&&(i < m_length);
    if(ret)
        e = m_array[i];
    return ret;
}
template<typename T>
bool SeqList<T>::set(int i,const T& e)
{
    bool ret =(i>=0)&&(i < m_length);
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
int SeqList<T>::length() const
{
    return m_length;
}

template<typename T>
T& SeqList<T>::operator[](int i)
{
    if((i>=0)&&(i<m_length))
    {
        return m_array[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary!");
    }
}

/*
* @Function Description :
* @Input parameters :
* @Return Value :
* @Other :为什么返回对象 而不是引用，因为返回引用的话 就会出现 可以通过 const_cast将其强转为非const引用从而对常量对象进行修改，并且为了实现代码复用，
* 我们将当前对象 const-this const_cast 为 noconst-this对象，然后调用 noconst-this版本的重载函数
*/
template<typename T>
T SeqList<T>::operator[](int i) const
{
    return (const_cast<SeqList<T>&>(*this))[i]; //代码复用， 因为代码和前面的重载完全一样，注意 怎么从const转为非const
}

template<typename T>
int SeqList<T> :: find(const T& e) const
{
    int ret = -1;

    for(int i=0;i<m_length;i++)
    {
        if(m_array[i] == e)
        {
            ret = i;
            break;
        }
    }
    return ret;
}

}

#endif // __SEQLIST_H_
