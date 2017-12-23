/*
* @brief : 实现单向循环链表
* @author: Eric
* @data:   20170716 14：20
* @other: 所有成员需要使用this->形式，否则有些编译器会提示变量不在此范围内
*/
#ifndef _CRICLELIST_H_
#define _CRICLELIST_H_

#include "LinkList.h"
#include "Object.h"
#include "Exception.h"

namespace ELib {

template<typename T>
class CircleList : public LinkList<T>
{

protected:
    typedef typename LinkList<T>::Node Node;
    Node* last() const  //如果考虑效率，可以增加一个尾指针
    {
        return this->position(this->m_length-1)->next;
    }
    void last_to_first()  //这里只完成了首尾重新相连中尾部重新指向新的0位置节点 ，前面的步骤已经完成
    {
        last()->next = this->m_header.next;
    }
    int mod(int i)
    {
        return (this->m_length == 0) ? 0:i % (this->m_length);
    }

public:
    CircleList() : LinkList<T>::LinkList() //这里构造函数不需要，系统会自动生成，而且工作就是linklist的工作
    {
    }

    bool insert(int i,const T& e)
    {
          bool ret = true;
          i = i % (this->m_length + 1); //这里必须是length+1 ，如果直接取length就成了在尾部插入，这时候不需要首尾重新相连
          ret = LinkList<T>::insert(i,e); //经过前一步i肯定不会超过m_length,所以ret肯定是true.这里直接调用父类的，完成节点指针重定位

          if(ret && (i == 0))  //如果实在0节点插入，则首尾重新链接
          {
              this->last_to_first(); //
          }

        return ret;
    }

    bool insert(const T& e) //尾插
    {
        return this->insert(this->m_length,e);
    }

    bool remove(int i)
    {
        bool ret = true;
        i = mod(i);   //这里是对length取余，因为加入length 就是3 i也是3 那就是尾节点后面即头结点
        if(i == 0)
        {
            Node* toDel = this->m_header.next;
            if(toDel != NULL)
            {
                this->m_header.next = toDel->next; //头结点指向1号节点
                this->m_length--;
                if(this->m_length > 0)  //不是空链表再进行操作
                {
                    this->last_to_first();
                    if(this->m_current == toDel)    //这里防止循环过程中删除导致CURRENT失效
                    {
                        this->m_current = toDel->next;
                    }
                }
                else   //空链表就将头结点置空
                {
                    this->m_header.next = NULL;
                    this->m_current = NULL;
                }
                this->destory(toDel);
            }
            else
            {
                ret =false;
            }
        }
        else
        {
            ret = LinkList<T>::remove(i);
        }

        return ret;
    }

    bool set(int i,const T& e)
    {
        return LinkList<T>::set(mod(i),e);
    }

    bool get(int i,T& e) const
    {
        return LinkList<T>::get(mod(i));
    }

    T get(int i) const
    {
        return LinkList<T>::get(mod(i));  //这一句 其实没用，为了规范
    }

    int find(const T&e) const
    {
        int ret = -1;
        int pos = 0;
        Node* current = this->m_header.next;
        for(int  i = 0;i < this->m_length;i++)
        {
            if(current->value == e)
            {
                ret = i;
                break;
            }
        }
        return ret;
    }

    void clear()
    {
        while(this->m_length > 1)  //有了 length就不用使用指针是否指向
        {
            remove(1);  //这里不是remove（0），是为了效率，因为0 的时候需要节点重定位，效率低
        }
        if(this->m_length == 1)
        {
            Node* toDel = this->m_header.next;

            this->m_header.next = NULL;
            this->m_current = NULL;
            this->m_length = 0;
        }
    }

    bool move(int i,int step = 1)
    {
        return LinkList<T>::move(mod(i),step);
    }

    bool end()
    {
        return (this->m_length == 0) || (this->m_current == NULL);

    }

    ~CircleList()
    {
        this->clear();
    }
};

}

#endif // CRICLELINKLIST_H
