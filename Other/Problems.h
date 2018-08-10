#ifndef PROBLEMS_H
#define PROBLEMS_H

//Static类型数据结构都会使用new T申请内存，如果T为类类型将会多次调用构造函数；
//构造函数过于复杂影响性能，能不能只申请内存，不调用构造函数？

//读懂LinuxLinkList

//LinkQueue使用LinkList时add函数效率低，改用双向循环链表

//用栈实现队列，用队列实现栈

//KMP算法

//递归-汉诺塔-全排列

//为什么在模板类中声明数组要使用static const变量，而普通声明数组只需要用const变量；
//为什么说在模板类中推荐使用enum而不是static const？

#endif // PROBLEMS_H
