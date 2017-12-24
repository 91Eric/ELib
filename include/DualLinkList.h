#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include <iostream>
#include "./include/List.h"
#include "./include/Object.h"
#include "Exception.h"

using namespace std;

namespace ELib
{

template<typename T>
class DualLinkList : public List<T>
{
protected:
    struct Node:public Object
    {
        T value;
        Node* pre;
        Node* next;
    };
    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node* pre;
        Node* next;
    }m_header;

    Node* m_current;
    int m_length;
    int m_step;

    virtual Node* create()
    {
        return new Node();
    }
    virtual void destory(Node *p)
    {
        delete p;
    }

    Node* position(int i) const
    {
        Node* ret = reinterpret_cast<Node *>(&m_header);
        for(int j = 0;j<i;j++)
        {
            ret = ret->next;
        }
        return ret;
    }

public:
    DualLinkList()
    {
        this->m_header.pre = NULL;
        this->m_header.next = NULL;
        this->m_current = NULL;
        this->m_length = 0;
        this->m_step = 0;
    }

    bool insert(int i, const T &e)
    {
        bool ret = (i >= 0) && (i <= this->m_length);

        if(ret)
        {
            Node* toInsert = this->create();

            if(toInsert != NULL)
            {
                Node* current = this->position(i);

                toInsert->value = e;

                toInsert->next = current->next;
                //判断是不是插入0号结点，如果是就要让待插入节点pre为NULL
                if(current != reinterpret_cast<Node*>(&m_header))
                {
                    toInsert->pre = current;
                }
                else
                {
                    toInsert->pre = NULL;
                }
                //如果是尾插，那么后续节点为NULL,不需要pre重定位
                if(current->next != NULL)
                    current->next->pre = toInsert;

                current->next = toInsert;

                this->m_length++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException,"No enough memory to insert LinkList Object");
            }
        }

        return ret;
    }

    bool insert(const T& e)
    {
        return this->insert(this->m_length,e);
    }

    bool remove(int i)
    {
        bool ret = (i >= 0)&&(i < this->m_length);

        if(ret)
        {
            Node* current = position(i);
            Node* toDel = current->next;
            Node* next = toDel->next;

            if(this->m_current == toDel)
            {
                this->m_current = next;
            }

            current->next = next;

            if(next != NULL)
            {
                next->pre = current;
            }

            this->m_length--;

            this->destory(toDel);
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary to remove LinkList Object");
        }

        return ret;
    }

    bool set(int i,const T& e)
    {
        bool ret = (i >= 0)&&(i < this->m_length);

        if(ret)
        {
            this->position(i)->next->value = e;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary to remove LinkList Object");
        }

        return ret;
    }

    bool get(int i,T& e) const
    {
         bool ret = (i >= 0)&&(i < this->m_length);
         if(ret)
         {
             e = this->position(i)->next->value ;
         }
         else
         {
             THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary to remove LinkList Object");
         }

         return ret;
    }

    T get(int i) const
    {
        T ret;
        if(this->get(i,ret))
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary to remove LinkList Object");
        }

        return ret;
    }

    int find(const T& e) const
    {
        int ret = -1;
        int pos = 0;
        Node* current = m_header.next;
        while(current)
        {
            if(current->value == e)
            {
                ret = pos;
                break;
            }
            else
            {
                current = current->next;
                pos++;
            }
        }

        return ret;
    }

    int length() const
    {
        return (this->m_length);
    }
/*
*@function description:释放除头结点外其他所有节点空间
*@author:
*@input:
*@output:
*@other:清除操作的第二种版本，使用remove函数，代码整洁，但是个人认为由于remove函数内部逻辑较为复杂，不如使用版本一
*/
//    void clear()
//    {
//        while (this->m_length > 0)
//        {
//            remove(0);
//        }

//    }

    void clear()
    {
        while (this->m_header.next != NULL)
        {
            Node* toDel = this->m_header.next;

            this->m_header.next = toDel->next;
            //被删除节点的下一节点成为首节点，因此pre必须变为NULL，如果不进行这一步,那么下一个节点的pre就会指向已释放节点
            //不加这一句,正常情况下不会有问题，但是假如析构时有异常，那么就不能保证异常安全.
            toDel->next->pre = NULL;
            this->m_length--;

            this->destory(toDel);
        }
    }

    virtual bool end()
    {
        return (this->m_current == NULL);
    }

    virtual bool move(int i,int step = 1)
    {
        bool ret  = (i >= 0)&&(i < m_length)&&(step > 0);
        if(ret)
        {
            m_current = position(i)->next;   //position获取到的是节点i的前一个节点
            m_step = step;
        }

        return ret;
    }

    virtual bool next()
    {
        int i = 0;

        while(i < m_step && !end())
        {
            m_current = m_current->next;
            i++;
        }

        return (i == m_step);
    }

    virtual bool pre()
    {
        int i = 0;

        while(i < m_step && !end())
        {
            m_current = m_current->pre;
            i++;
        }

        return (i == m_step);
    }

    T current()
    {
        return this->m_current->value;
    }

    void getAll() const
    {
        Node* current = this->m_header.next;
        while (current != NULL)
        {
            cout<<current->value<<endl;
            current = current->next;
        }
    }

    ~DualLinkList()
    {
        this->clear();
    }
};

}

#endif // DULLINKLIST_H
