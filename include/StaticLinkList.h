#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "../include/LinkList.h"

namespace ELib
{

/*
*@calss description:
*@other:这个类仍然使用m_header进行管理，切记！看父类的insert函数，本类只是对内存分配做了改变，其他没变
* 如果没有析构函数，调用父类的析构函数，有父类析构函数调用了虚函数，而在析构函数里，虚函数无用，导致调用父类的destory函数，错误的释放内存空间
*/
template<typename T,int N>
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

/*
*@calss description:这个类继承自Node仅仅是因为 要重载 placement new,由于继承体系问题，不能直接在LinkList类里面重载，因为不同子类内存分配不一样，
* 所以在子类中产生新的子类，实现自己的内存分配策略,反正两个类结构完全一致，内存布局一样,可通用
*@other:
*/
    struct SNode : public Node
    {

        //placement new 只负责调用构造函数，不负责内存分配
        void* operator new(size_t i,void* loc)
        {
            (void)i;
            return loc;
        }


    };
    unsigned char m_space[sizeof(Node)*N];
    int m_used[N];

protected:
    Node* create()
    {
        SNode* ret = NULL;  //这里使用SNode是因为自定义的内存策略是这个类实现的，后期返回还是Node
        for(int i = 0;i < N;i++)
        {
            if(!m_used[i])
            {
                ret = reinterpret_cast<SNode*>(&m_space) + i;
                ret = new(ret)SNode();
                m_used[i] = 1;
                break;
            }
        }

        return reinterpret_cast<Node*>(ret);
    }

    void destory(Node*& p)
    {
        SNode* space = reinterpret_cast<SNode*>(&m_space);
        SNode* ps = dynamic_cast<SNode*>(p);
        for(int i = 0;i < N;i++)
        {
            if(ps == space + i)
            {
                m_used[i] = 0;
                ps->~SNode();
                break;
            }
        }
    }

public:
    StaticLinkList()
    {
        for(int i = 0;i < N;i++)
        {
            m_used[i] = 0;
        }
    }

    int capacity() const
    {
        return N;
    }

    ~StaticLinkList()
    {
        //这里虽然调用了父类的clear函数，但是析构函数中不会发生多态，因此，destory函数只能是本类的
        this->clear();
    }

};

}

#endif // STATICLINKLIST_H
