#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "Queue.h"
#include "Object/Exception.h"

namespace ZYLib
{

template <typename T,const int N>
class StaticQueue : public Queue<T>
{
protected:
    T m_space[N];
    int m_front;
    int m_rear;
    int m_length;

public:
    StaticQueue()
    {
        m_front=m_rear=m_length=0;
    }

    void add(const T& e)
    {
        if(m_length < N)
        {
            m_space[m_rear]=e;
            m_rear=(m_rear+1)%N;
            m_length++;
        }
        else
        {
            ThrowException(NoEnoughMemoryException,"no enough memory in current Queue");
        }
    }

    void remove()
    {
        if(m_length > 0)
        {
            m_front=(m_front+1)%N;
            m_length--;
        }
        else
        {
            ThrowException(InvalidOperationException,"no element to remove in current Queue");
        }
    }

    T& front() const
    {
        if(m_length > 0)
            return m_space[m_front];
        else
            ThrowException(InvalidOperationException,"no element to remove in current Queue");
    }

    void clear()
    {
        m_front=m_rear=m_length=0;
    }

    int length() const
    {
        return m_length;
    }

    bool isFull()
    {
        return (m_length == N && m_front == m_rear);
    }

    bool isNull()
    {
        return (m_length == 0 && m_front == m_rear);
    }

    int capacity() const
    {
        return N;
    }
};

}


#endif // STATICQUEUE_H
