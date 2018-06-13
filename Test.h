#ifndef TEST_H
#define TEST_H

#include <iostream>
#include "Exception.h"
#include "Object.h"
#include "SmartPointer.h"
#include <stdio.h>
#include "List.h"

using namespace std;
using namespace ZYLib;

#define ThrowException(e,m) throw e(m,__FILE__,__LINE__)
#define Cout(x)  cout<<x<<endl


#define pd(x) printf("%s:%d\n",#x,x)
#define pc(c) printf("%s:%c\n",#c,c)
#define ps(s) printf("%s:%s\n",#s,s)
#define pt(t) printf("%s\n",t)
#define pf(f) printf("%s:%f\n",#f,f)
#define plf(f) printf("%s:%lf\n",#f,f)
#define px(x) printf("%s:0X%X\n",#x,x)
#define pp(p) printf("%s:%p\n",#p,p)
#define pn printf("\n")

class Test:public Object
{
public:
    int i;
    int j;
    Test()
    {
        cout<<"test()"<<endl;
    }
    Test(int a,int b)
    {
        cout<<"test:"<<a<<b<<endl;
        i=a;
        j=b;
    }
    ~Test()
    {
        cout<<"~test()"<<i<<j<<endl;
    }
};

class Child:public Test
{
public:
    int k;
};

#endif // TEST_H
