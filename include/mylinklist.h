#ifndef MYLINKLIST_H
#define MYLINKLIST_H
/*
* @brief : 单链表模板实现，自己的另一种思路，会有问题，这个问题主要是关于异常安全的，平时可不考虑
* @author: Eric
* @data  : 20170531
* @other:
*/
#include "List.h"
#include "Object.h"
#include "Exception.h"


namespace ELib {

template<typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object       //内部类定义完成即可使用 ，由于 默认是public，因此外部类可以直接访问内部类的成员变量，否则不能访问
    {
        T value;
        Node* next;
    };
    mutable Node* m_header;    //使用指针更简单，为什么使用匿名内部类
    int m_length;

public:
    LinkList();
    bool insert(const T& e); //尾插
    bool insert(int i,const T& e);
    bool remove(int i);
    bool set(int i,const T& e);
    bool get(int i,T& e) const;
    T get(int i) const;
    int length() const;

    /*
    * @Function Description : 获取到位置 i 的节点指针
    * @Input parameters :
    * @Return Value :
    * @Other : 由于使用了内部类，使用 outer：：inter  的方式在模板外部实现有错误，暂时没找到解决办法，后续进行改进。
    */

    Node* position(int i) const//必须是const因为后续的get()是const函数，const函数不能调用非const！
    {
        Node* ret = m_header;
        for(int j = 0;j<i;j++)
        {
            ret = ret->next;
        }
        return ret;
    }
    void clear();
    ~LinkList();

};

template<typename T>
LinkList<T> :: LinkList()
{
    this->m_header = new Node();  //这里会造成一开始的问题！  第二 构造函数不是异常安全的！！！
    if(this->m_header != NULL)
        this->m_length = 0;
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException,"No enough memory to init LinkList Object");
    }
}

template<typename T>
bool LinkList<T> :: insert(int i,const T& e)
{
    bool ret = ((i>=0)&&(i<=m_length));
    if(ret)
    {
        Node* node = new Node();
        if(node != NULL)
        {
            Node*  current =position(i);

            node->value = e;
            node->next = current->next;
            current->next = node;

            this->m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException,"No enough memory to insert LinkList Object");
        }
    }

    return ret;
}

template<typename T>
bool LinkList<T> :: insert(const T& e)
{
    return insert(m_length,e);
}

template<typename T>
bool LinkList<T> :: remove(int i)
{
    bool ret = ((i>=0)&&(i<this->m_length));
    if(ret)
    {
        Node* current =  position(i);

        Node* toDel = current->next;
        current->next = toDel->next;
        delete toDel;

        this->m_length--;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsExceptio,"Index is out of boundary to remove LinkList Object");
    }


    return ret;
}

template<typename T>
bool LinkList<T> :: set(int i,const T& e)
{
    bool ret = ((i>=0)&&(i<m_length));
    if(ret)
    {
        Node* current = position(i);

        current->next->value = e;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsExceptio,"Index is out of boundary to set LinkList Object");
    }

    return ret;
}

template<typename T>
bool LinkList<T> :: get(int i,T& e) const
{
    bool ret = ((i>=0)&&(i<m_length));
    if(ret)
    {
        Node* current = position(i);

        e = current->next->value;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsExceptio,"Index is out of boundary to get LinkList Object");
    }

    return ret;
}

template<typename T>
T LinkList<T> :: get(int i) const
{
    T ret;
    if(get(i,ret))
    {
        return ret;
    }
    else  //个人理解，get函数已经处理了越界异常，这里没有实际意义，可能为了规范
    {
        THROW_EXCEPTION(IndexOutOfBoundsExceptio,"Index is out of boundary to get LinkList Object");
    }

    return ret;
}

template<typename T>
int LinkList<T> :: length() const
{
    return this->m_length;
}

template<typename T>
void LinkList<T> :: clear()
{
    while(m_header->next != NULL)
    {
        Node* toClear =m_header->next;
        m_header->next= toClear->next;

        delete toClear;
    }
    m_length = 0;
}

template<typename T>
LinkList<T> :: ~LinkList()
{
    this->clear();
    delete m_header;

}


}

#endif // MYLINKLIST_H
