#ifndef ARRAY_H
#define ARRAY_H

#include "Object/Object.h"
#include "Object/Exception.h"

namespace ZYLib {

//重新封装的数组实现
//提供数组的长度信息
//提供数组对象间的复制
template <typename T>
class Array:public Object
{
protected:
    T* m_array;

public:
    virtual bool set(int i,const T& t)
    {
        bool ret=( i>=0 && i<length() );
        if(ret)
        {
            m_array[i]=t;
        }
        else
        {
            ret=false;
        }
        return ret;
    }

    virtual bool get(int i,T& t)
    {
        bool ret=( i>=0 && i<length() );
        if(ret)
        {
            t=m_array[i];
        }
        else
        {
            ret=false;
        }
        return ret;
    }

    //重载数组操作符
    T& operator[] (int i)
    {
        if(i>=0 && i<length())
        {
            return m_array[i];
        }
        else
        {
            ThrowException(IndexOutOfBoundsException,"operator [] out of index!");
        }

    }

    T operator [](int i) const
    {
        return const_cast<Array<T>&>(*this)[i];
        //调用const函数的必然是const对象，所以先转化成非const对象，再调用其非const的[]操作符；
    }

    virtual int length() const = 0;
};

}

#endif // ARRAY_H
