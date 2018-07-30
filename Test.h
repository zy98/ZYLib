#ifndef TEST_H
#define TEST_H

#include <iostream>
#include "Exception.h"
#include "Object.h"
#include "SmartPointer.h"
#include "StaticList.h"
#include "DynamicList.h"
#include <stdio.h>
#include "List.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "LinkList.h"
#include "StaticLinkList.h"
#include "SharedPointer.h"
#include "CircleList.h"
#include "DualLinkList.h"
#include "StaticStack.h"
#include "LinkStack.h"
#include "StaticQueue.h"
#include "LinkQueue.h"

using namespace std;
using namespace ZYLib;

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

bool is_left(const char& c)
{
    return c == '(' ||
            c == '{' ||
            c == '<' ||
            c == '[' ;
}

bool is_right(const char& c)
{
    return c == ')' ||
            c == '}' ||
            c == '>' ||
            c == ']' ;
}

bool is_match(const char& l,const char& r)
{
    return (l == '(' && r == ')') ||
            (l == '<' && r == '>') ||
            (l == '{' && r == '}') ||
            (l == '[' && r == ']') ||
            (l == '"' && r == '"') ||
            (l == '\'' && r == '\'');
}

bool is_qoute(const char& c)
{
    return c == '\'';
}

bool is_dblqoute(const char& c)
{
    return c == '\"';
}

bool scan(const char* s)
{
    int i=0;
    bool ret=true;
    LinkStack<char> stack;

    while(s[i] != '\0')
    {
        if(is_left(s[i]))
        {
            stack.push(s[i]);
        }
        else if(is_qoute(s[i]))
        {
            if(stack.size() == 0)
            {
                stack.push(s[i]);
            }
            else if(is_qoute(stack.top()))
            {
                stack.pop();
            }
            else
            {
                stack.push(s[i]);
            }
        }
        else if(is_dblqoute(s[i]))
        {
            if(stack.size() == 0)
            {
                stack.push(s[i]);
            }
            else if(is_dblqoute(stack.top()))
            {
                stack.pop();
            }
            else
            {
                stack.push(s[i]);
            }
        }
        else if(is_right(s[i]))
        {
            if(stack.size() > 0)
            {
                if(is_match(stack.top(),s[i]))
                {
                    stack.pop();
                }
                else
                {
                    ret=false;
                    break;
                }
            }
            else
            {
                ret=false;
                break;
            }
        }

        i++;
    }

    while(stack.size() != 0)
    {
        cout<<stack.top()<<endl;
        stack.pop();
    }
    return ret && stack.size() == 0;
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
