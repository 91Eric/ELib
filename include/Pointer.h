/*
* @brief : 智能指针抽象类模板实现
* @author: Eric
* @data:   20170626
* @other:因为继承了object是一个抽象类，所以只要Pointer本身不实现析构函数，那它也是抽象类
*/

#ifndef _POINTER_H_
#define _POINTER_H_

#include "Object.h"

namespace ELib {

template<typename T>
class Pointer : public Object
{
protected:
    T* m_pointer;
public:
    Pointer(T* p = NULL)
    {
        m_pointer = NULL;
    }

    T* operator ->()
    {
        return m_pointer;
    }

    T& operator *()
    {
        return *m_pointer;
    }

    const T* operator ->() const
    {
        return m_pointer;
    }

    const T& operator *() const
    {
        return *m_pointer;
    }

    bool isNull() const
    {
        return m_pointer == 0;
    }

    T* get() const
    {
        return  m_pointer;
    }

};

}
#endif // POINTER_H
