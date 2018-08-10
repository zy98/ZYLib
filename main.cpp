#include "Other/Test.h"
#include <stdlib.h>
#include <ctime>
#include <vector>

using namespace std;
using namespace ZYLib;


Test t[1000];
TestProxy pt[1000];

int main()
{   
    bool flag=false;
    for(int i=0;i<1000;i++)
    {
        t[i].id=i;
        pt[i]=t[i];
    }

    clock_t begin=clock();

    for(int i=0;i<1000;i++)
    {
        Sort::Bubble(pt,1000,flag);
        flag=!flag;
    }

    clock_t end=clock();

    cout<<(end-begin)/1000<<endl;
}
