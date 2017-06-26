/*
* @brief : 重构了智能指针
* @author: Eric
* @data:
* @other: 将原先的 * -> get（）等删除，因为父类Pointer已经实现了
*/
#ifndef _SMARTPOINTER_H
#define _SMARTPOINTER_H

#include "Pointer.h"

namespace ELib
{
template<typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p=NULL): Pointer<T>(p)
    {

    }
    SmartPointer(const SmartPointer<T>& obj);  //拷贝构造函数用来初始化对象，不需要先delete,因为默认的m_pointer就是NULL，对比 operator=

    SmartPointer<T>& operator=(const SmartPointer<T>& obj);

    ~SmartPointer()
    {
        delete this->m_pointer;
    }

};

template<typename T>
SmartPointer<T> ::  SmartPointer(const SmartPointer<T>& obj)  //拷贝构造函数用来初始化对象，不需要先delete,因为默认的m_pointer就是NULL，对比 operator=
{
    this->m_pointer=obj.m_pointer;
     //此处是为了保证堆空间只被一个智能指针指向，因此原对象指针要置NULL,首先类型转换，因为参数是const不能修改
    //注意！！ 转换的参数仍然是SmartPointer<T>并且是引用
    const_cast<SmartPointer<T>&>(obj).m_pointer=NULL;
}

template<typename T>
SmartPointer<T>& SmartPointer<T> :: operator=(const SmartPointer<T>& obj)
{
    if(this!=&obj)
    {
        T* tmp = this->m_pointer;//此处应该先保存，毕竟如果是类对象的会触发析构函数，有可能有异常

        this->m_pointer=obj.m_pointer;
         //此处是为了保证堆空间只被一个智能指针指向，因此原对象指针qingkong,首先类型转换，因为参数是const不能修改
        //注意！！ 转换的参数仍然是SmartPointer<T>并且是引用
        const_cast<SmartPointer<T>&>(obj).m_pointer=NULL;
        delete tmp;
    }
    return *this;
}

}


#endif // SMARTPOINTER_H
