#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "Stack.h"
#include "List/LinkList.h"
#include "Object/Exception.h"

namespace ZYLib
{

template <typename T>
class LinkStack : public Stack<T>
{
protected:
    LinkList<T> list;

public:
    void push(const T& obj)
    {
        list.insert(0,obj);
    }

    void pop()
    {
        if(list.length() > 0)
        {
            list.remove(0);
        }
        else
        {
            ThrowException(InvalidOperationException,"no element in current LinkStack");
        }
    }

    T top() const
    {
        if(list.length() > 0)
        {
            return list.get(0);
        }
        else
        {
            ThrowException(InvalidOperationException,"no element in current LinkStack");
        }
    }

    void clear()
    {
        list.clear();
    }

    int size() const
    {
        return list.length();
    }
};

}

#endif // LINKSTACK_H
