#ifndef _STATICLIST_H_
#define _STATICLIST_H_

#include "Seqlist.h"

namespace ELib
{

template<typename T,int N>
class StaticList:public SeqList<T>
{
protected:
    T m_space[N];
public:
    StaticList()
    {
        this->m_array = m_space;
        this->m_length = 0;
    }
    int capacity()
    {
        return N;
    }
};
}
#endif // _STATICLIST_H_
