/*
* @brief : 动态数组类模板的实现，继承自Array这一模板类
* @author: Eric
* @data: 20170529
* @other: 对于存在的代码重复可以进一步进行代码优化
*/


#ifndef _DYNAMICARRAY_H_
#define _DYNAMICARRAY_H_

#include "Array.h"
#include "Exception.h"

namespace DTLib
{

template<typename T>
class DynamicArray: public Array<T>
{
protected:
    int m_length;   //不需要capacity，因为数组不存在容量和数据长度的问题，只有一个数组长度
protected:

public:
    DynamicArray(int length);
    DynamicArray(const DynamicArray<T>& e);
    DynamicArray<T>& operator= (const DynamicArray<T>& e);  //DynamicArray& operator= (const DynamicArray& e); 忘记加<>!!

    int length() const;
    void resize(int length);

    ~DynamicArray()
    {
        delete[] this->m_array;
        this->m_array = NULL;
    }
};

template<typename T>
DynamicArray<T> :: DynamicArray(int length)
{
    this->m_array = new T(length);
    if(this->m_array != NULL)
    {
        this->m_length = length;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException,"No enough memeory to construct DynamicArray Object");
    }
}

template<typename T>
DynamicArray<T> :: DynamicArray(const DynamicArray<T>& e)
{
    this->m_array = new T(e.m_length);
    if(this->m_array != NULL)
    {
        this->m_length = e.m_length;
        for(int i = 0;i<e.m_length;i++)
        {
            this->m_array[i] = e.m_array[i];
        }
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException,"No enough memeory to copy construct DynamicArray Object");
    }
}

template<typename T>
DynamicArray<T>&  DynamicArray<T> :: operator= (const DynamicArray<T>& e)
{
    if(this != &e)
    {
        T* array = new T[e.m_length];
        if(array != NULL)
        {
            for(int i = 0;i<e.m_length;i++)
            {
                array[i] = e.m_array[i];
            }

            T* tmp = this->m_array;    //异常安全机制
            this->m_array = array;
            this->m_length = e.m_length;
            delete[] tmp;    //delete[] ,别忘记[]
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No enough memory to operator= DynamicArray Object");
        }
        return *this;
    }
}

template<typename T>
void DynamicArray<T> :: resize(int length)
{
    if(this->m_length != length)
    {
        T* array = new T[length];
        if(array != NULL)
        {
            int length = (this->m_length < length ? this->m_length : length);
            for(int i = 0;i<length;i++)
            {
                array[i] = this->m_array[i];
            }

            T* tmp = this->m_array;   //异常安全机制
            this->m_array = array;
            this->m_length = length;
            delete[] tmp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No enough memory to resize DynamicArray Object");
        }
    }
}

template<typename T>
int DynamicArray<T> :: length() const
{
    return m_length;
}


}

#endif // DYNAMICARRAY_H
