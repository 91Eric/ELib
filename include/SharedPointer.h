#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H
#include <cstdlib>
#include "Pointer.h"
#include "Exception.h"

namespace ELib {
template<typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int* m_ref;

    void assign(SharedPointer<T>& obj)
    {
        this->m_ref = obj.m_ref;
        this->m_pointer = obj.m_pointer;
        if(this->m_ref)
        {
            *(this->m_ref)++;
        }
    }
public:
    SharedPointer(T* p = NULL):m_ref(NULL)
    {
        if(p) //针对M_REF进行处理，
        {
            m_ref = static_cast<int*>(malloc(sizeof(int)));
            if(this->m_ref)
            {
                *(this->m_ref) = 1;
                 this->m_pointer = p;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No enough memeory  to create SharedPointer!");
            }
        }
    }

    SharedPointer(const SharedPointer<T>& obj)
    {
        assign(obj);
    }

    void clear()
    {
        T* toDel = this->m_pointer;
        int* ref = this->m_ref;

        this->m_pointer = NULL;
        this->m_ref = NULL;
        if(ref)    //如果本身计数已经指向某个空间，那么就得将计数减一
        {
            (*ref)--;
            if(*ref == 0) //如果计数已经是0 说明指向的空间已经没有指针了，必须销毁
            {
                free(ref);
                delete toDel;
            }
        }
    }

    bool operator ==(const SharedPointer<T>& obj)
    {
        return this->m_pointer == obj.m_pointer;
    }

    bool operator !=(const SharedPointer<T>& obj)
    {
        return !(*this == obj);
    }

    SharedPointer operator =(const SharedPointer<T>& obj)
    {
        if(this != &obj)
        {
            clear();
            assign(obj);
        }
        return *this;
    }


     ~SharedPointer()
    {
        clear();
    }
};
}
#endif // SHAREDPOINTER_H
