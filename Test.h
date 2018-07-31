#ifndef TEST_H
#define TEST_H

#include <iostream>
#include "String/String.h"
#include "List/CircleList.h"

using namespace std;
using namespace ZYLib;

#define pd(x) printf("%s:%d\n",#x,x)
#define pc(c) printf("%s:%c\n",#c,c)
#define ps(s) printf("%s:%s\n",#s,s)
#define pt(t) printf("%s\n",t)
#define pf(f) printf("%s:%f\n",#f,f)
#define plf(f) printf("%s:%lf\n",#f,f)
#define px(x) printf("%s:0X%X\n",#x,x)
#define pp(p) printf("%s:%p\n",#p,p)
#define pn printf("\n")

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

class Test:public Object
{
    int m_id;
public:
    Test()
    {
        cout<<"Test()"<<endl;
    }
    Test(int id)
    {
        m_id=id;
    }
    ~Test()
    {
        cout<<"~Test()"<<endl;
    }
};

class Child:public Test
{
public:
    int k;
};



#endif // TEST_H
