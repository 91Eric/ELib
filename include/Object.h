#ifndef OBJECT_H
#define OBJECT_H

namespace ELib {

class Object
{
public:
    Object();
    void* operator new(unsigned int size) throw();
    void operator delete(void* p);
    void* operator new[](unsigned int size) throw();
    void operator delete[](void* p);
    virtual ~Object() = 0;
};


}

#endif // OBJECT_H
