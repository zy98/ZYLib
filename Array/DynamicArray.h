#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Object/Exception.h"

namespace ZYLib {

template <typename T>
class DynamicArray:public Array<T>
{
protected:
    int m_length;

    T* copy(const DynamicArray<T>& obj,int newlen)
    {
        T* space = new T[newlen];
        if(space != NULL)
        {
            int len=obj.length()<newlen?obj.length():newlen;
            for(int i=0;i<len;i++)
            {
                space[i]=obj.m_array[i];
            }
            this->m_length=len;
        }
        else
        {
            ThrowException(NoEnoughMemoryException,"No enough momery to copy DynamicArray");
        }
        return space;
    }

    void update(T* array,int length)
    {
        T* temp=this->m_array;
        this->m_array=array;
        m_length=length;
        delete[] temp;
    }

    void init(T* array,int length)
    {
        if(array != NULL)
        {
            this->m_array=array;
            this->m_length=length;
        }
        else
        {
            ThrowException(NoEnoughMemoryException,"No enough momery to intitialize DynamicArray");
        }
    }

public:
    DynamicArray(int length)
    {
        init(new T[length],length);
    }

    DynamicArray(const DynamicArray<T>& t)
    {
        init(copy(t, t.m_length), t.m_length);
    }

    DynamicArray<T>& operator = (const DynamicArray<T>& t)
    {
        if(this != &t)
        {
            if(m_length != t.length())
            {
                update(copy(t,t.length()), t.length());
            }
            else
            {
                for(int i=0;i<m_length;i++)
                    this->m_array[i]=t.m_array[i];
            }
        }
        return *this;
    }

    void resize(int length)
    {
        update(copy(*this,length),length);
    }

    int length() const
    {
        return m_length;
    }

    ~DynamicArray()
    {
        delete[] this->m_array;
    }

};

}

#endif // DYNAMICARRAY_H
