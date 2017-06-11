#include <iostream>
#include <cstring>
#include ".//include//Object.h"
#include ".//include/LinkList.h"
#include "./include/Exception.h"
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
    LinkList<int> list;
    for(int i=0;i<5;i++)
        list.insert((i));
    for(list.move(0,2);!list.end();list.next())
        cout<<list.current()<<endl;



    return 0;
}
