#ifndef BTREENODE_H
#define BTREENODE_H

#include "AbsTreeNode.h"
#include "Object/Exception.h"

namespace ZYLib
{

template <typename T>
class BTreeNode:public AbsTreeNode<T>
{
public:
    BTreeNode<T>* left;
    BTreeNode<T>* right;

    BTreeNode()
    {
        left=NULL;
        right=NULL;
    }

    static BTreeNode<T>* NewNode()
    {
        BTreeNode<T>* ret=new BTreeNode<T>();
        if(ret != NULL)
        {
            ret->m_flag=true;
            return ret;
        }
        else
        {
            delete ret;
            ret=NULL;
        }
        return ret;
    }

    ~BTreeNode()
    {

    }

};

}

#endif // BTREENODE_H
