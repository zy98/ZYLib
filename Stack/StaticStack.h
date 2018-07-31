#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Object/Exception.h"

namespace ZYLib
{

template <typename T,const int N>
class StaticStack : public Stack<T>
{
protected:
    T m_space[N];
    int m_top;
    int m_size;

public:
    StaticStack()
    {
        m_top=-1;
        m_size=0;
    }

    void push(const T& obj)
    {
        if(m_size < N)
        {
            m_space[m_top+1]=obj;
            m_top++;
            m_size++;
        }
        else
        {
            ThrowException(InvalidOperationException,"invalidOperator in this stack");
        }
    }

    void pop()
    {
        if(m_size > 0)
        {
            m_top--;
            m_size--;
        }
        else
        {
            ThrowException(InvalidOperationException,"invalidOperator in this stack");
        }
    }

    T top() const
    {
        if(m_size > 0)
            return m_space[m_top];
        else
            ThrowException(InvalidOperationException,"invalidOperator in this stack");
    }

    void clear()
    {
        m_top=-1;
        m_size=0;
    }

    int size() const
    {
        return m_size;
    }

    int capacity() const
    {
        return N;
    }
};

}

#endif // STATICSTACK_H
