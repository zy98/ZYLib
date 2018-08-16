#ifndef GTREENODE_H
#define GTREENODE_H

#include "AbsTreeNode.h"
#include "List/LinkList.h"

namespace ZYLib
{

template <typename T>
class GTreeNode:public AbsTreeNode<T>
{
public:
    LinkList< GTreeNode<T>* > m_child;


    GTreeNode():AbsTreeNode<T>()
    {

    }

    ~GTreeNode()
    {

    }
};

}

#endif // GTREENODE_H
