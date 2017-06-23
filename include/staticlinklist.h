#ifndef _STATICLINKLIST_H_
#define _STATICLINKLIST_H_

#include "Object.h"
#include "LinkList.h"

namespace ELib {

template<typename T,int N>
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;   //这里就是解决找不到Node

    struct SNode : public Node  //继承而不是直接使用Node的原因是 ，我们需要重载new
    {
      void* operator new(size_t size,void* loc)   //针对具体的类类型。使用placement new 必须重载new操作符！
      {
          size = size;
          return loc;
      }

    };

    unsigned char m_space[sizeof(SNode)*N];
    bool m_used[N];

public:

    StaticLinkList()
    {
        for(int i =0;i<N;i++)
        {
            m_used[i] = false;
        }
    }

    Node* create()
    {
        SNode* ret = NULL;
        for(int i = 0;i<N;i++)
        {
            if(!m_used[i])
            {
                ret = reinterpret_cast<SNode*>(m_space) + i;  // 这只是分配空间，没有调用构造函数
                ret = new(ret)SNode(); //这里NEW的用法！！。标准new用法，只不过平常很少用
                m_used[i] = true;
                break;
            }
        }

        return ret;
    }
    void destory(Node* p)
    {
        SNode* space = reinterpret_cast<SNode*>(m_space);
        SNode* ps = reinterpret_cast<SNode*>(p);
        for(int i = 0;i<N;i++)
        {
            if(ps == space + i)
            {
                if(m_used[i])
                {
                    m_used[i] = false;
                    ps->~SNode();  //必须这样
                    //delete ps;
                    break;
                }
            }
        }
    }
    virtual ~StaticLinkList() {}
};

}



#endif // STATICLINKLIST_H
