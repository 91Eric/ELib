#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_

#include "Stack.h"
#include "LinkList.h"

namespace ELib
{
template <typename T>
class LinkStack : public Stack<T>
{
protected:
      LinkList<T> m_linklist;
public:
      LinkStack() : m_linklist()
      {
          this->m_size = 0;
      }

      void push(const T& e)
      {
          this->m_linklist.insert(0,e);
      }

      void pop()
      {
          if(this->m_linklist.length() > 0)
          {
              this->m_linklist.remove(0);
          }
          else
          {
              THROW_EXCEPTION(InvalidParameterException,"No element in curent stack!");
          }
      }

      T top() const
      {
          if(this->m_linklist.length() > 0)
          {
              return this->m_linklist.get(0);
          }
          else
          {
              THROW_EXCEPTION(InvalidParameterException,"No element in curent stack!");
          }
      }

      int size() const
      {
          return this->m_linklist.length();
      }

      void clear()
      {
          this->m_linklist.clear();
      }

};

}

#endif // LINKSTACK_H
