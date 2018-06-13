#include <iostream>
#include "Exception.h"
#include "Object.h"
#include "SmartPointer.h"
#include <stdio.h>
#include "Test.h"


using namespace std;
using namespace ZYLib;




int main()
{
    InvalidOperationException* a=new InvalidOperationException();

    delete a;
    return 0;
}
