#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "Array.h"
#include "Object/Exception.h"

namespace ZYLib {

template <typename T,const int N>
class StaticArray:public Array<T>
{
protected:
    T m_space[N];

public:
    StaticArray()
    {
        this->m_array=m_space;
    }

    StaticArray(const StaticArray<T,N>& t)
    {
        this->m_array=m_space;
        for(int i=0;i<N;i++)
        {
            this->m_space[i]=t.m_space[i];
        }
    }

    StaticArray<T,N>& operator =(const StaticArray<T,N>& t)
    {
        if(this != &t)
        {
            for(int i=0;i<N;i++)
            {
                this->m_space[i]=t.m_space[i];
                //this->operator [](i)=t[i];
            }
        }
        return *this;
    }

    int length() const
    {
        return N;
    }
};

}

#endif // STATICARRAY_H
