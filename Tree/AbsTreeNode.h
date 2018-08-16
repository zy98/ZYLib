#ifndef ABSTREENODE_H
#define ABSTREENODE_H

#include "Object/Object.h"

namespace ZYLib
{

template <typename T>
class AbsTreeNode:public Object
{
public:
    T m_value;
    AbsTreeNode<T>* m_parent;

    AbsTreeNode()
    {
        m_parent=NULL;
    }

    AbsTreeNode(T& value,AbsTreeNode<T>* parent=NULL)
    {
        m_value=value;
        m_parent=parent;
    }

    virtual ~AbsTreeNode()=0;

};

template <typename T>
AbsTreeNode<T>::~AbsTreeNode()
{

}


}


#endif // ABSTREENODE_H
