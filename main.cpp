#include "Test.h"
#include <stdlib.h>
#include <vector>

using namespace std;
using namespace ZYLib;

//Static类型数据结构都会使用new T申请内存，如果T为类类型将会多次调用构造函数；
//构造函数过于复杂影响性能，能不能只申请内存，不调用构造函数？

//读懂LinuxLinkList

//LinkQueue使用LinkList时add函数效率低，改用双向循环链表

//用栈实现队列，用队列实现栈

void test1()
{
    String str("   Hello,World   ");
    cout<<str.str()<<endl;

    cout<<str.trim().str()<<"123"<<endl;
    cout<<str.length()<<endl;
    cout<<str.insert(10,"!").str()<<endl;
}

void test2()
{
    cout<<"test2 begin:"<<endl;

    String s[]={"E","D","C","B","A"};
    String min=s[0];
    for(int i=0;i<5;i++)
    {
        if(min > s[i])
            min=s[i];
    }
    cout<<"min:"<<min.str()<<endl;

    cout<<"test2 end:"<<endl;
}

int main()
{
    test1();

    //test2();

}
