#ifndef GTREE_H
#define GTREE_H

#include "AbsTree.h"
#include "GTreeNode.h"
#include "Object/Exception.h"

namespace ZYLib
{

template <typename T>
class GTree:public AbsTree<T>
{
protected:
    GTreeNode<T>* find(GTreeNode<T>* node,const T& value) const
    {
        GTreeNode<T>* ret=NULL;
        if(node != NULL)
        {
            if(node->m_value == value)
            {
                return node;
            }
            else
            {
                for(node->m_child.begin();!node->m_child.end() && (ret == NULL);node->m_child.next())
                {
                    ret=find(node->m_child.current(),value);
                }
            }
        }
        return ret;
    }

    GTreeNode<T>* find(GTreeNode<T>* node,GTreeNode<T>* obj) const
    {
        GTreeNode<T>* ret=NULL;
        if(node != NULL && obj != NULL)
        {
            if(node == obj)
            {
                return node;
            }
            else
            {
                for(node->m_child.begin();!node->m_child.end() && (ret == NULL);node->m_child.next())
                {
                    ret=find(node->m_child.current(),obj);
                }
            }
        }
        return ret;
    }

public:
    GTree(){}
    //将数据元素插入到父节点node之下，如果node为空则插入到根节点
    bool insert(AbsTreeNode<T>* node)
    {
        bool ret;
        if(ret = (this->m_root == NULL) )
        {
            node->m_parent=NULL;
            this->m_root=node;
        }
        else
        {
            GTreeNode<T>* np=find(node->m_parent);
            if(ret = (np != NULL) )
            {
                GTreeNode<T>* n=dynamic_cast<GTreeNode<T>*>(node);
                if(np->m_child.find(n) < 0)//LinkList的find函数返回查找元素的下标，未找到返回-1
                    np->m_child.insert(n);
            }
            else
            {
                ThrowException(InvalidParameterException,"Parameter node is invalid!");
            }
        }
        return ret;
    }

    //创建数据元素赋值value，并插入到父节点node之下，如果node为空则插入到根节点
    bool insert(const T& value,AbsTreeNode<T>* parent)
    {
        bool ret;
        GTreeNode<T>* node=new GTreeNode<T>;
        if(ret = (node != NULL))
        {
            node->m_value=value;
            node->m_parent=parent;

            ret=insert(node);
        }
        else
        {
            ThrowException(NoEnoughMemoryException,"No enough memory to create node");
        }
        return ret;
    }    
    SharedPointer< AbsTree<T> > remove(const T& value)
    {

    }
    SharedPointer< AbsTree<T> > remove(AbsTreeNode<T>* node)
    {

    }

    //根据value查找节点
    GTreeNode<T>* find(const T& value) const
    {
        return find(root(),value);
    }
    //根据节点地址查找节点
    GTreeNode<T>* find(AbsTreeNode<T>* node) const
    {
        return find(root(),dynamic_cast<GTreeNode<T>*>(node));
    }
    GTreeNode<T>* root() const
    {
        return dynamic_cast< GTreeNode<T>* >(this->m_root);
    }

    int degree() const
    {

    }
    int count() const
    {

    }
    int height()
    {

    }
    void clear()
    {

    }

};

}

#endif // GTREE_H
