#include <iostream>
#include <cstring>
#include ".//include//Object.h"
#include "./include//StaticList.h"
#include ".//include//CricleList.h"
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

    StaticList<Test,5> t;
    t.insert(0,Test(3));
    t = t;
//    Test a;
   // t.get(0,a);
    return 0;
}
