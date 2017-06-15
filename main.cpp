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
    const StaticArray<int,5> arr;
    const_cast<StaticArray<int,5>&>(arr).set(1,22);
    cout<<"...."<<arr[1]<<endl;
    return 0;
}
