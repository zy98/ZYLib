#ifndef LIST_H
#define LIST_H

#include "Object.h"

namespace ZYLib {

template <typename T>
class List : public Object
{
protected:
    List(const List<T>&);
    T& operator= (const List<T>&);//容器类禁用拷贝构造和赋值操作符

public:
    List(){}
    virtual bool insert(const T& t) =0;
    virtual bool insert(int i,const T& t) =0;
    virtual bool remove(int i) =0;
    virtual bool set(int i,const T& t) =0;
    virtual T get(int i,bool& b) const =0;
    virtual T get(int i) const =0;

    //find在没有重载==操作符的类中会出错
    //解决办法：可以将自定义类继承自Object，在Object中实现==和!=;
    virtual int find(const T& t) =0;
    virtual int length() const =0;
    virtual void clear() =0;
};

}


#endif // LIST_H
