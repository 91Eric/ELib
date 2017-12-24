/*
* @brief : 单链表模板实现
* @author: Eric
* @data  : 20170531
* @other:
*/
#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#include "List.h"
#include "Object.h"
#include "Exception.h"

namespace ELib {

template<typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object   //内部类定义完成即可使用 ，由于 默认是public，因此外部类可以直接访问内部类的成员变量，否则不能访问
    {
        T value;
        Node* next;
    };
   // mutable Node m_header;    //重点！！ 由于get函数会改变对象的 指针域，而函数又是 const 因此加上这个  ，但是顺序表不需要没因为他们是直接获取
    //原始的用法存在问题，加入一个类的构造函数有异常抛出，那么 就会 导致构造 m_header 时导致value 触发构造函数，但是这时候程序员并没有构造任何关于类的
    //对象，荣然抛出异常，因此不合理。个人解决方案，把m_header 换成指针，别人的思路:匿名类
    mutable struct SNode: public Object
    {
        char reserved[sizeof(T)]; //占位符，代替T value
        Node* next;
    }m_header;
    Node* m_current;
    int m_step;
    int m_length;

protected:
    virtual Node* create()
    {
        return new Node();
    }
    virtual void destory(Node*& p)
    {
        delete p;
        p = NULL;
    }

    Node* position(int i) const;
public:
    LinkList();
    bool insert(const T& e); //尾插
    bool insert(int i,const T& e);
    bool remove(int i);
    bool set(int i,const T& e);
    bool get(int i,T& e) const;
    virtual T get(int i) const;
    int length() const;  //这里的const
    int find(const T&e) const;
    virtual bool move(int i,int step = 1);
    virtual bool end();
    virtual bool next();
    virtual T current();


    void clear();
    ~LinkList();
};

/*
* @Function Description :获取到位置 i 的节点指针 position()函数的模板类外实现方式
* @Input parameters :
* @Return Value :
* @Other : 由于使用了内部类，使用 outer<T>：：inter  的方式在模板外部实现,
* 由于模板的特殊性，outer<T>::inter编译器无法断定是类型还是变量，因此加上typename 指明这是类型,
* 否则出现如下错误need ‘typename’ before ‘ELib::LinkList<T>::Node’ because ‘ELib::LinkList<T>’ is a dependent scope
* 错误原因分析如下：编译器不知道LinkList<T>::Node 代表的是一个类型还是说LinkList<T>内部的一个成员（::作用符可以进行成员访问）
*/
template<typename T>
typename LinkList<T>::Node* LinkList<T> ::position(int i) const //
{
    LinkList<T>::Node* ret = reinterpret_cast<LinkList<T>::Node *>(&m_header);   //强转 ，两个在内存上完全一样
    for(int j = 0;j<i;j++)
    {
        ret = ret->next;
    }
    return ret;  //这里由于局部指针指向的是堆上的内存，因此返回这个指针没问题，有问题的是指向栈上的指针
}

template<typename T>
LinkList<T> :: LinkList()
{
    this->m_header.next = NULL;
    this->m_length = 0;
    this->m_step = 0;
    this->m_current = NULL;
}

/*
* @Function Description :
* @Input parameters :
* @Return Value :
* @Other : 这里的插入i是指他想变成第几个位置的节点 ，而不是在第几个节点之前或者之后插入，这样就和删除对应起来了
*/
template<typename T>
bool LinkList<T> :: insert(int i,const T& e)
{
    bool ret = ((i>=0)&&(i<=m_length));
    if(ret)
    {
        Node* node =create();
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
        if(m_current == toDel)   //这里是为了防止使用新的迭代方式中存在删除操作导致m_current失效，类似迭代器失效
        {
            m_current = toDel->next;
        }
        current->next = toDel->next;
        this->m_length--; //为了防止对象在析构时抛出异常导致长度不变，因此需要将长度更改放在前面
        destory(toDel);
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary to remove LinkList Object");
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
        THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary to set LinkList Object");
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
        THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary to get LinkList Object");
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
    else   //这个其实没用，因为 get(int i,T& e) const已经处理了越界问题，为了规范
    {
        THROW_EXCEPTION(IndexOutOfBoundsException,"Index is out of boundary to get LinkList Object");
    }

    return ret;  //这一句 其实没用，为了规范

}

template<typename T>
int LinkList<T> :: length() const
{
    return this->m_length;
}

template<typename T>
int LinkList<T> :: find(const T&e) const
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

template<typename T>
bool LinkList<T> :: move(int i,int step)
{
    bool ret  = (i >= 0)&&(i < m_length)&&(step > 0);
    if(ret)
    {
        m_current = position(i)->next;   //position获取到的是节点i的前一个节点
        m_step = step;
    }

    return ret;
}

template<typename T>
bool LinkList<T> :: end()
{
    return (m_current == NULL);
}

template<typename T>
bool LinkList<T> :: next()
{
    int i = 0;
    while(i < m_step && !end())
    {
        m_current = m_current->next;
        i++;
    }

    return (i == m_step);
}

template<typename T>
T LinkList<T> ::  current()
{
    if(!end())
    {
        return m_current->value;
    }
    else
    {

        THROW_EXCEPTION(InvalidParameterException,"No  value at current position...");
    }
}

template<typename T>
void LinkList<T> :: clear()
{
    /* 我的初始思路
   Node* current = &m_header;
   while(current !=NULL)
   {
       Node* toClear = current->next;
       m_header.next= toClear->next;

       delete toClear;
   }
   m_length = 0;
   */
    //改进思路
    while(m_header.next != NULL)
    {
        Node* toClear =m_header.next;
        m_header.next= toClear->next;
        m_length--;  //出于异常安全，同remove()函数
        destory(toClear);
    }
}

template<typename T>
LinkList<T> :: ~LinkList()
{
    this->clear(); //由于头结点不是指针，因此不需要释放头结点
}

}


#endif // LINKLIST_H
