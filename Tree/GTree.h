#ifndef GTREE_H
#define GTREE_H

#include "AbsTree.h"
#include "GTreeNode.h"
#include "Object/Exception.h"
#include "Queue/LinkQueue.h"

namespace ZYLib
{

template <typename T>
class GTree:public AbsTree<T>
{
protected:
    inline GTreeNode<T>* get_node(AbsTreeNode<T>* node)
    {
        return dynamic_cast<GTreeNode<T>*>(node);
    }


    GTreeNode<T>* find_node(GTreeNode<T>* node,const T& value) const
    {
        GTreeNode<T>* ret=NULL;
        if(node != NULL)
        {
            if(node->value == value)
            {
                return node;
            }
            else
            {
                for(node->child.begin();!node->child.end() && (ret == NULL);node->child.next())
                {
                    ret=find_node(node->child.current(),value);
                }
            }
        }
        return ret;
    }

    GTreeNode<T>* find_node(GTreeNode<T>* node,GTreeNode<T>* obj) const
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
                for(node->child.begin();!node->child.end() && (ret == NULL);node->child.next())
                {
                    ret=find_node(node->child.current(),obj);
                }
            }
        }
        return ret;
    }

    void free(GTreeNode<T>* node)
    {
        if(node != NULL)
        {
            for(node->child.begin();!node->child.end();node->child.next())
            {
                free(node->child.current());
            }
            if(node->flag())
                delete node;
        }
    }

    GTree<T>* remove_node(GTreeNode<T>* node)
    {
        GTree<T>* ret=new GTree<T>;

        if(ret != NULL && node != NULL)
        {
            if(this->m_root == node)
            {
                this->m_root=NULL;
            }
            else
            {
                LinkList<GTreeNode<T>*>& child=dynamic_cast<GTreeNode<T>*>(node->parent)->child;
                child.remove(child.find(node));
                node->parent=NULL;
            }
            ret->m_root=node;
        }
        else
        {
            delete ret;
            ThrowException(NoEnoughMemoryException,"no enough to create tree");
        }
        return ret;
    }

    //计算树的节点数，空树返回0，没有子节点返回1，有子节点返回count(node.child)+1
    int count_node(GTreeNode<T>* node) const
    {
        int ret=0;
        if(node != NULL)
        {
            ret=1;
            for(node->child.begin();!node->child.end();node->child.next())
            {
                ret+=count_node(node->child.current());
            }
        }
        return ret;
    }

    //计算树的高度，空树返回0，没有子节点返回1，有子节点返回当前父节点下最大子节点数+1；
    int height_node(GTreeNode<T>* node) const
    {
        int ret=0;
        if(node != NULL)
        {
            for(node->child.begin();!node->child.end();node->child.next())
            {
                int max=height_node(node->child.current());
                if(ret < max)
                    ret=max;
            }
            ret+=1;
        }
        return ret;

    }

    ////计算树的度，空树返回0，没有子节点返回0，有子节点返回degree(node.child)+1
    int degree_node(GTreeNode<T>* node) const
    {
        int ret=0;
        if(node != NULL)
        {
            ret=node->child.length();
            for(node->child.begin();!node->child.end();node->child.next())
            {
                int d=degree_node(node->child.current());
                if(ret < d)
                    ret=d;
            }
        }
        return ret;
    }

public:
    GTree(){}
    //将数据元素插入到父节点node之下，如果node为空则插入到根节点
    bool insert(AbsTreeNode<T>* node)
    {
        bool ret= (node != NULL);
        if(ret)
        {
            if(this->m_root == NULL)
            {
                node->parent=NULL;
                this->m_root=node;
            }
            else
            {
                GTreeNode<T>* np=find(node->parent);
                if(np != NULL)
                {
                    GTreeNode<T>* n=dynamic_cast<GTreeNode<T>*>(node);
                    if(np->child.find(n) < 0)//LinkList的find函数返回查找元素的下标，未找到返回-1
                        np->child.insert(n);
                }
                else
                {
                    ThrowException(InvalidParameterException,"Parameter node is invalid!");
                }
            }
        }       
        return ret;
    }

    //创建数据元素赋值value，并插入到父节点node之下，如果node为空则插入到根节点
    bool insert(const T& value,AbsTreeNode<T>* parent)
    {
        bool ret;
        GTreeNode<T>* node=GTreeNode<T>::NewNode();
        if(node != NULL)
        {
            node->value=value;
            node->parent=parent;

            ret=insert(node);

            if(!ret)
            {
                delete node;
            }
        }
        else
        {
            ThrowException(NoEnoughMemoryException,"No enough memory to create node");
        }
        return ret;
    }    
    SharedPointer< AbsTree<T> > remove(const T& value)
    {
        GTree<T>* ret=NULL;
        GTreeNode<T>* node=find(value);

        if(node != NULL)
        {
            ret=remove_node(node);
            this->m_queue.clear();
        }
        return ret;
    }
    SharedPointer< AbsTree<T> > remove(AbsTreeNode<T>* node)
    {
        GTree<T>* ret=NULL;
        node=find(node);

        if(node != NULL)
        {
            ret=remove_node(dynamic_cast<GTreeNode<T>*>(node));
            this->m_queue.clear();
        }
        return ret;
    }

    //根据value查找节点
    GTreeNode<T>* find(const T& value) const
    {
        return find_node(root(),value);
    }
    //根据节点地址查找节点
    GTreeNode<T>* find(AbsTreeNode<T>* node) const
    {
        return find_node(root(),dynamic_cast<GTreeNode<T>*>(node));
    }
    GTreeNode<T>* root() const
    {
        return dynamic_cast< GTreeNode<T>* >(this->m_root);
    }

    int degree() const
    {
        return degree_node(root());
    }
    int count() const
    {
        return count_node(root());
    }
    int height()
    {
        return height_node(root());
    }
    void clear()
    {
        free(root());
        this->m_queue.clear();
    }

    void next()
    {
        if(this->m_queue.length() > 0)
        {
            LinkList< GTreeNode<T>* >& node=get_node(this->m_queue.front())->child;
            for(node.begin();!node.end();node.next())
            {
                this->m_queue.add(node.current());
            }
            this->m_queue.remove();
        }
        else
        {
            ThrowException(InvalidOperationException,"no value move to next");
        }
    }

};

}

#endif // GTREE_H
