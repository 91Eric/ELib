#ifndef _DYNAMICLIST_H_
#define _DYNAMICLIST_H_

#include "SeqList.h"


/*
这里的动态是指可以动态的更改大小，不是指链表形式的动态添加，因为我们默认还是固定长度
*/
namespace ELib
{

template<typename T>
class DynamicList:public SeqList<T>
{
protected:
    int m_capacity;
public:
    DynamicList(int capacity);
    int capacity() const;
    void resize(int capacity);

    ~DynamicList()
    {
        delete[] this->m_array;
        this->m_array = NULL;
    }
};

template<typename T>
DynamicList<T> :: DynamicList(int capacity)
{
    thisd->m_array = new T[capacity];
    if(this->m_array != NULL)
    {
        this->m_capacity = capacity;
        this->m_length = 0;
    }
    else
    {
        THROW_EXECPTION(NoEnoughMemoryException,"No enough memory to construct DynamicList Object");
    }
}

template<typename T>
void DynamicList<T> :: resize(int capacity)
{
    if(capacity != this->m_capacity)
    {
        T *array = new T[capacity];
        if(array != NULL)
        {
            int length = (this->m_length < capacity ? this->m_length : capacity);
            for(i = 0;i<length;i++)
            {
                array[i] = this->m_array[i];   //假如这里出现异常，也不会影响原先的结构，因为是在新的内存上处理的，但是会造成内存泄漏，没办法顾全，
                                                //个人想法，是不是可以try catch,然后delete掉呢
            }
        /*
        感觉可以直接删除 ，不需要这个对象，毕竟已经分配成功，没有其他异常类 ，
        但是！！ 这是错误的认识，因为对于类而言 delete 触发析构函数，假如析构函数抛出了异常，那么就会导致，原先的数据被破坏了

        */
            T *tmp = this->m_array;
            this->m_array = array;
            this->m_capacity = capacity;
            this->length = length;
            delete[] tmp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No enough memory to resize DynamicList Object");
        }
    }
}

template<typename T>
int DynamicList<T> ::capacity() const
{
    return this->m_capacity;
}

}
#endif // _DYNAMICLIST_H_
