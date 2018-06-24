#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"

namespace ZYLib {

template <typename T>
class DynamicList:public SeqList<T>
{
protected:
    int m_capacity;

public:
    DynamicList(int capacity)
    {
        this->m_array=new T[capacity];

        if(this->m_array != NULL)
        {
            m_capacity=capacity;
            this->m_length=0;
        }
        else
        {
            ThrowException(NoEnoughMemoryException,"DynamicList() constructor failed");
        }
    }

    void resize(int capacity)//为什么不用bool返回，要用异常
    {
        if(capacity != m_capacity)
        {
            T* newspace=new T[capacity];
            if(newspace != NULL)
            {
                int newlen=this->m_length<capacity?this->m_length:capacity;
                for(int i=0;i<newlen;i++)
                {
                    newspace[i]=this->m_array[i];
                }

                T* temp=this->m_array;

                this->m_array=newspace;
                m_capacity=capacity;
                this->m_length=newlen;

                delete[] temp;  //delete放在最后是有可能delete是调用析构函数中抛出异常;
            }
            else
            {
                ThrowException(NoEnoughMemoryException,"DynamicList resize no enough memory");
            }
        }
    }

    int capacity() const
    {
        return m_capacity;
    }

    ~DynamicList()
    {
        delete[] this->m_array;
    }

};

}

#endif // DYNAMICLIST_H
