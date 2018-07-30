#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "Queue.h"
#include "LinkList.h"

namespace ZYLib
{

template <typename T>
class LinkQueue : public Queue<T>
{
protected:
    LinkList<T> list;

public:
    void add(const T& e)
    {
        list.insert(e);
    }

    void remove()
    {
        if(list.length() > 0)
        {
            list.remove(0);
        }
        else
        {
            ThrowException(InvalidOperationException,"no element in current queue");
        }
    }
    T front() const
    {
        if(list.length() > 0)
            return list.get(0);
        else
            ThrowException(InvalidOperationException,"no element in current queue");
    }

    void clear()
    {
        list.clear();
    }

    int length() const
    {
        return list.length();
    }
};

}

#endif // LINKQUEUE_H
