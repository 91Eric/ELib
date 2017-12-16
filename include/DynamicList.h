#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"

namespace ELib
{

template<typename T>
class DynamicList : public SeqList<T>
{
protected:
    int m_capacity;

public:
    DynamicList(int capacity)
    {
        this->m_array = new T[capacity];
        if(this->m_array != NULL)
        {
            this->m_length = 0;
            m_capacity = capacity;
        }
        else
            throw "no enough memory";
    }

    void resize(int newcapacity)
    {
        if(m_capacity != newcapacity)
        {
            T* space = new T[newcapacity];
            if(space != NULL)
            {
                int length = (this->m_length < newcapacity ? this->m_length : newcapacity);

                for(int i = 0;i < length;i++)
                {
                    space[i] = this->m_array[i];
                }

                T* tmp = this->m_array;

                this->m_array = space;
                this->m_capacity = newcapacity;
                this->m_length = length;

                delete[] tmp;

            }
        }
    }

    int capacity()
    {
        return this->m_capacity;
    }

    ~DynamicList()
    {
        delete this->m_array;
    }
};

}

#endif // DYNAMICLIST_H
