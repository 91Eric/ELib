#include <iostream>
#include <cstring>
#include ".//include//Object.h"
#include ".//include/LinkList.h"
#include "./include/StaticArray.h"
using namespace std;
using namespace ELib;
class Test
{

public:
    int a;
    Test(int m=0):a(m)
    {

    }
    bool operator ==(const Test& e)
    {
        return (this->a == e.a);
    }

};


int main()
{

    return 0;
}
