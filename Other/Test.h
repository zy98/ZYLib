#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <cstring>
#include "String/String.h"
#include "List/CircleList.h"
#include "QueenSolution.h"
#include "Sort/Sort.h"
#include "Array/DynamicArray.h"
#include "Array/StaticArray.h"
#include "Other/Proxy.h"

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

//#define Swap(a,b) char c=(a);(a)=(b);(b)=(c)

struct Node
{
    int value;
    Node* next;
};



Node* create_list(int begin,unsigned int len)
{
    if(len == 0)
        return NULL;

    Node* ret=reinterpret_cast<Node*>(malloc(sizeof(Node)));
    ret->value=begin;
    ret->next=create_list(begin+1,len-1);

    return ret;
}

void print_list(Node* p)
{
    if(p == NULL)
        printf("NULL\n");
    else
    {
        printf("%d->",p->value);
        print_list(p->next);
    }
}

Node* reverse_list(Node* list)
{
    if(list->next == NULL || list == NULL)
    {
        return list;
    }

    Node* node=list->next;
    Node* ret=reverse_list(node);//返回的是同一个值，if中的list；
    node->next=list;
    list->next=NULL;

    return ret;
}

Node* merge(Node* list1,Node* list2)
{
    if(list1 == NULL)
        return list2;
    else if(list2 == NULL)
        return list1;
    else if(list1->value < list2->value)
    {
        list1->next=merge(list1->next,list2);
        return list1;
    }
    else
    {
        list2->next=merge(list1,list2->next);
        return list2;
    }

}

void destroy_list(Node* del)
{
    if(del == NULL)
        return;

    destroy_list(del->next);
    free(del);
}

//*****
void permutation(char* s,char* ret)
{
    if(*s == '\0')
    {
        cout<<ret<<endl;
    }
    else
    {
        for(int i=0;s[i]!='\0';i++)
        {
            //i==0是自身交换的情况swap(s[0],s[0])
            if(i==0 || s[0] != s[i])
            {
                swap(s[0],s[i]);
                permutation(s+1,ret);
                swap(s[0],s[i]);
            }
        }
    }
}

//*****
void HanoiTower(int n,char a,char b,char c)
{
    if(n == 1)
        cout<<"move:"<<a<<"->"<<c<<endl;
    else
    {
        HanoiTower(n-1,a,c,b);
        HanoiTower(1,a,b,c);
        HanoiTower(n-1,b,a,c);
    }
}

void print_even(Node* list)
{
    if(list != NULL)
    {
        print_even(list->next);
        if(list->value%2 == 0)
            cout<<list->value<<endl;
    }
}









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



#endif // TEST_H
