#ifndef ABSTREENODE_H
#define ABSTREENODE_H

#include "Object/Object.h"

namespace ZYLib
{

template <typename T>
class AbsTreeNode:public Object
{
protected:
    bool m_flag;

    AbsTreeNode(const AbsTreeNode<T>&);
    AbsTreeNode<T>& operator = (const AbsTreeNode<T>&);

    void* operator new(unsigned int size)
    {
        return Object::operator new(size);
    }

public:
    T value;
    AbsTreeNode<T>* parent;

    AbsTreeNode()
    {
        parent=NULL;
        m_flag=false;
    }

    AbsTreeNode(T& value,AbsTreeNode<T>* parent=NULL)
    {
        value=value;
        parent=parent;
    }

    bool flag() const
    {
        return m_flag;
    }

    virtual ~AbsTreeNode()=0;

};

template <typename T>
AbsTreeNode<T>::~AbsTreeNode()
{

}


}


#endif // ABSTREENODE_H
