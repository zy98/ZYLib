#include "Test.h"

using namespace std;
using namespace ZYLib;
#define N 10

int main()
{
    DynamicList<int> a(10);
    pd(a.capacity());
    pd(a.length());

    for(int i=0;i<N;i++)
    {
        a.insert(i,i);
    }

    for(int i=0;i<N;i++)
        pd(a[i]);

    a.resize(5);
    pd(a.capacity());
    pd(a.length());
    for(int i=0;i<a.length();i++)
        pd(a[i]);




}
