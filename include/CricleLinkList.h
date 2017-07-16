#ifndef _CRICLELINKLIST_H_
#define _CRICLELINKLIST_H_

#include "List.h"
#include "Object.h"
#include "Exception.h"

namespace ELib {

template<typename T>
class CircleLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* next;
    }m_header;

    int m_length;

public:
    CircleLinkList()
    {
       this->m_header.next = reinterpret_cast<Node *>(&(this->m_header));  //初始情况下 头结点指向头结点
       this->m_length = 0;
    }

    bool insert(int i,const T& e)
    {
        bool ret = (i >= 0)&&(i <= m_length);
        if(ret)
        {
            Node* node = new Node();
            if(node)
            {
                Node* current = position(i);
                node->next = current->next;
                node->value = e;
                current->next = node;
                m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No enough memory to insert CircleLinkList Object");
            }
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary to insert CircleLinkList Object");
        }

        return ret;
    }

    bool insert(const T& e) //尾插
    {
        return insert(m_length,e);
    }

    bool remove(int i)
    {
        bool ret = (i>0)&&(i<m_length);
        if(ret)
        {
           Node* current = position(i);

           Node* toDel = current->next;
           current->next = toDel->next;
           delete toDel;
           m_length--;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary to remove CircleLinkList Object");
        }

        return ret;
    }

    bool set(int i,const T& e)
    {
        bool ret = ((i>=0)&&(i<m_length));
        if(ret)
        {
            Node* current = position(i);

            current->next->value = e;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary to set CircleLinkList Object");
        }

        return ret;
    }

    bool get(int i,T& e) const
    {
        bool ret = ((i>=0)&&(i<m_length));
        if(ret)
        {
            Node* current = position(i);

            e = current->next->value;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary to get CircleLinkList Object");
        }

        return ret;
    }

    T get(int i) const
    {
        T ret;
        if(get(i,ret))
        {
            return ret;
        }
        else   //这个其实没用，因为 get(int i,T& e) const已经处理了越界问题，为了规范
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary to get CircleLinkList Object");
        }

        return ret;  //这一句 其实没用，为了规范
    }

    int length() const  //这里的const
    {
        return m_length;
    }

    int find(const T&e) const
    {
        int ret = -1;
        int pos = 0;
        Node* current = m_header.next;
        while(current != reinterpret_cast<Node*>(&m_header))
        {
            if(current->value == e)
            {
                ret = pos;
                break;
            }
            else
            {
                pos++;
                current = current->next;
            }
        }

        return ret;
    }

    Node* position(int i) const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);
        for(int j = 0;j<i;j++)
        {
            ret = ret->next;
        }
        return ret;
    }

    void clear()
    {
        Node* current = m_header.next;
        while(current != reinterpret_cast<Node*>(&m_header))
        {
            Node* toDel = current;
            current = current->next;
            delete toDel;
        }
        m_length = 0;
        m_header.next = reinterpret_cast<Node *>(&(m_header));
    }
    ~CircleLinkList()
    {
        this->clear();
    }
};

}

#endif // CRICLELINKLIST_H
