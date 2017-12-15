#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
using namespace std;

namespace ELib {

class Object
{
public:
    Object();
    void* operator new(size_t size) throw();
    void operator delete(void* p);
    void* operator new[](size_t size) throw();
    void operator delete[](void* p);
    bool operator ==(const Object& obj);  //这里实现的是地址相等与否的比较，即是否是同一个对象
    bool operator !=(const Object& obj);
    virtual ~Object() = 0;
};


}

#endif // OBJECT_H
