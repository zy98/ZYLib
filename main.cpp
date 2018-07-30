#include "Test.h"
#include <stdlib.h>
#include <vector>

using namespace std;
using namespace ZYLib;

void josephus(int num,int start,int count)
{
    CircleList<int> list;
    for(int i=1;i<=num;i++)
        list.insert(i);

    list.begin();
    list.move(start-1);
    while(!list.end())
    {
        list.move(count-1);
        cout<<list.current()<<endl;
        list.remove(list.find(list.current()));
    }
}

//Static类型数据结构都会使用new T申请内存，如果T为类类型将会多次调用构造函数；
//构造函数过于复杂影响性能，能不能只申请内存，不调用构造函数？

//读懂LinuxLinkList

//LinkQueue使用LinkList时add函数效率低，改用双向循环链表

//用栈实现队列，用队列实现栈
int main()
{
    LinkQueue<int> que;

    for(int i=0;i<10;i++)
    {
        que.add(i);
    }
    cout<<que.length()<<endl;
    for(int i=0;i<10;i++)
    {
        cout<<que.front()<<endl;
        que.remove();
    }
    que.clear();
    cout<<que.length()<<endl;
}
