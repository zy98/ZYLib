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
    LinkList< GTreeNode<T>* > child;

    static GTreeNode<T>* NewNode()
    {
        GTreeNode<T>* ret=new GTreeNode<T>;
        if(ret != NULL)
        {
            ret->m_flag=true;
            return ret;
        }
        else
            return NULL;
    }

    ~GTreeNode()
    {

    }


};

}

#endif // GTREENODE_H
