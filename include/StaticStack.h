#ifndef _STATICSTACK_H_
#define _STATICSTACK_H_

#include "Stack.h"
#include "Exception.h"

namespace ELib
{
template<typename T,int N>
class StaticStack : public Stack<T>
{
private:
    T m_space[N]; //这里要求类对象必须有默认构造函数
    int m_top;
    int m_size;
public:
    StaticStack()
    {
        this->m_top = -1;
        this->m_size = 0;
    }

    void push(const T& e)
    {
        if(this->m_size < N)
        {
            this->m_size[this->m_top + 1] = e;  //这里不直接使用this->m_sapce[++this->m_top] = e;的原因是防止e为类对象时，赋值操作出现异常，破坏异常安全
            this->m_top++;
            this->m_size++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No space in current stack!");
        }
    }

    void pop()
    {
        if(this->m_size > 0)
        {
            this->m_top--;
            this->m_size--;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"No element in curent stack!");
        }
    }

    T top() const
    {
        if(this->m_size > 0)
        {
            return this->m_size[this->m_top];
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException,"No element in curent stack!");
        }
    }

    int size() const
    {
        return this->m_size;
    }

    int capacity() const
    {
        return N;
    }

    void clear()
    {
        this->m_top = -1;
        this->m_size = 0;
    }

    ~StaticStack()
    {
        this->clear();
    }
};

}
#endif // STATICSTACK_H
