#include <iostream>
#include <cstring>
#include ".//include//Object.h"
#include ".//include/LinkList.h"

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
    LinkList<Test> list;
    for(int i=0;i<5;i++)
        list.insert(Test(i));
    Test t(3);
    cout<<list.find(t)<<endl;



    return 0;
}
