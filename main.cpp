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

};


int main()
{

    LinkList<Test> s1;
    Test t1(3);
    s1.insert(t1);
    Test t2;
    s1.get(0,t2);
    cout<<t2.a<<endl;
    s1.clear();

//    for(int i=0;i<5;i++)
//    {
//        int j = i;
//        s1.insert(j);
//    }
//    cout<<s1.length()<<endl;
//    int j=88;
//    s1.get(5,j);
//    cout<<j<<endl;
//    for(int i=0;i<5;i++)
//    {
//        int j;
//        s1.get(i,j);
//        cout<<j<<endl;
//    }
    return 0;
}
