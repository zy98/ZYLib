#ifndef BTREE_H
#define BTREE_H

#include "AbsTree.h"
#include "BTreeNode.h"
#include "Object/Exception.h"
#include "Array/DynamicArray.h"
#include "stdio.h"
#include <iostream>

using namespace std;

namespace ZYLib
{

enum BTNodePos
{
    Any,
    Left,
    Right
};

enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder,
    LevelOrder
};

template <typename T>
class BTree:public AbsTree<T>
{
protected:
    inline BTreeNode<T>* get_node(AbsTreeNode<T>* node) const
    {
        return dynamic_cast<BTreeNode<T>*>(node);
    }

    BTreeNode<T>* find_node(BTreeNode<T>* node,const T& value) const
    {
        BTreeNode<T>* ret=NULL;
        if(node != NULL)
        {
            if(node->value == value)
            {
                return node;
            }
            else
            {
                if(ret == NULL) ret=find_node(node->left,value);
                if(ret == NULL) ret=find_node(node->right,value);
            }
        }
        return ret;
    }

    BTreeNode<T>* find_node(BTreeNode<T>* node,BTreeNode<T>* obj) const
    {
        BTreeNode<T>* ret=NULL;
        if(node != NULL)
        {
            if(node == obj)
            {
                return node;
            }
            else
            {
                if(ret == NULL) ret=find_node(node->left,obj);
                if(ret == NULL) ret=find_node(node->right,obj);
            }
        }
        return ret;
    }

    bool insert_node(BTreeNode<T>* node,BTreeNode<T>* parent,BTNodePos pos)
    {
        bool ret= (node != NULL) && (parent != NULL);
        if(ret )
        {
            if(pos == Any)
            {
                if(parent->left == NULL) parent->left=node;
                else if(parent->right == NULL) parent->right=node;
                else ret=false;
            }
            else if(pos == Left)
            {
                if(parent->left == NULL) parent->left=node;
                else ret=false;
            }
            else if(pos == Right)
            {
                if(parent->right == NULL) parent->right=node;
                else ret=false;
            }
        }
        else
        {
            ThrowException(InvalidParameterException,"Parameter is invalid ");
        }
        return ret;
    }

    void free(BTreeNode<T>* node)
    {
        if(node != NULL)
        {
            free(node->left);
            free(node->right);
            if(node->flag())
                delete node;
        }
    }

    BTree<T>* remove_node(BTreeNode<T>* node)
    {
        BTree<T>* ret=new BTree<T>;
        if(ret != NULL && node != NULL)
        {
            if(this->m_root == node)
            {
                ret->m_root=this->m_root;
                this->m_root=NULL;
            }
            else
            {
                BTreeNode<T>* parent=get_node(find(node)->parent);
                if(parent != NULL)
                {
                    if(parent->left == node)
                    {
                        parent->left=NULL;
                    }
                    else if(parent->right == node)
                    {
                        parent->right=NULL;
                    }
                    node->parent=NULL;
                    ret->m_root=node;
                }
            }
        }
        else
        {
            delete ret;
            ThrowException(NoEnoughMemoryException,"no enough memory to create BTree");
        }
        return ret;
    }

    int count_node(BTreeNode<T>* node) const
    {
        if(node != NULL)
            return count_node(node->left)+count_node(node->right)+1;
        return 0;
    }

    int degree_node(BTreeNode<T>* node) const
    {
        int ret=0;
        if(node != NULL)
        {
            ret=(!!node->left + !!node->right);
            if(ret != 2)
            {
                BTreeNode<T>* btn[]={node->left,node->right};
                for(int i=0;i<2;i++)
                {
                    int d=degree_node(btn[i]);
                    if(ret<d)
                        ret=d;
                }
            }
        }
        return ret;
    }

    int height_node(BTreeNode<T>* node) const
    {
        if(node != NULL)
        {
            int a=height_node(node->left);
            int b=height_node(node->right);
            return (a>b?a:b) + 1;
        }
        return 0;
    }

    void pre_order(BTreeNode<T>* node,LinkQueue<BTreeNode<T>*>& ret)
    {
        if(node != NULL)
        {
            ret.add(node);
            pre_order(node->left,ret);
            pre_order(node->right,ret);
        }
    }

    void in_order(BTreeNode<T>* node,LinkQueue<BTreeNode<T>*>& ret)
    {
        if(node != NULL)
        {
            in_order(node->left,ret);
            ret.add(node);
            in_order(node->right,ret);
        }
    }

    void post_order(BTreeNode<T>* node,LinkQueue<BTreeNode<T>*>& ret)
    {
        if(node != NULL)
        {
            post_order(node->left,ret);
            post_order(node->right,ret);
            ret.add(node);
        }
    }

    void level_order(LinkQueue<BTreeNode<T>*>& ret)
    {
        LinkQueue<BTreeNode<T>*> temp;
        if(this->root() != NULL)
        {
            temp.add(this->root());

            while(temp.length() != 0)
            {
                BTreeNode<T>* node=temp.front();
                if(node->left != NULL)
                {
                    temp.add(node->left);
                }
                if(node->right != NULL)
                {
                    temp.add(node->right);
                }

                ret.add(node);
                temp.remove();
            }
        }
    }

    BTreeNode<T>* clone_tree(BTreeNode<T>* node)
    {
        BTreeNode<T>* ret=NULL;
        if(node != NULL)
        {
            ret=BTreeNode<T>::NewNode();
            if(ret != NULL)
            {
                ret->value=node->value;
                ret->left=clone_tree(node->left);
                ret->right=clone_tree(node->right);

                if(ret->left != NULL)
                    ret->left->parent=ret;
                if(ret->right != NULL)
                    ret->right->parent=ret;
            }
            else
            {
                ThrowException(NoEnoughMemoryException,"no enough memory to create new BTreeNode");
            }
        }
        return ret;
    }

    bool compare(BTreeNode<T>* lnode,BTreeNode<T>* rnode)
    {
        if(lnode == rnode)
        {
            return true;
        }
        else if(lnode != NULL && rnode != NULL)
        {
            return (lnode->value == rnode->value) && compare(lnode->left,rnode->left) && compare(lnode->right,rnode->right);
        }
        else
        {
            return false;
        }
    }

    BTreeNode<T>* add_tree(BTreeNode<T>* ln,BTreeNode<T>* rn)
    {
        if(ln != NULL && rn == NULL)
        {
            return clone_tree(ln);
        }
        else if(ln == NULL && rn != NULL)
        {
            return clone_tree(rn);
        }
        else if(ln != NULL && rn != NULL)
        {
            BTreeNode<T>* ret=BTreeNode<T>::NewNode();
            if(ret != NULL)
            {
                ret->value=ln->value+rn->value;

                if( (ret->left=add_tree(ln->left,rn->left)) != NULL)
                    ret->left->parent=ret;

                if( (ret->right=add_tree(ln->right,rn->right)) != NULL)
                    ret->right->parent=ret;
            }
            else
            {
                ThrowException(NoEnoughMemoryException,"no enough memory to create new BTreeNode");
            }
            return ret;
        }
        else
        {
            return NULL;
        }
    }

    void switch_to_queue(BTTraversal order,LinkQueue<BTreeNode<T>*>& queue)
    {
        switch (order)
        {
        case PreOrder:
            pre_order(root(),queue);
            break;
        case InOrder:
            in_order(root(),queue);
            break;
        case PostOrder:
            post_order(root(),queue);
            break;
        case LevelOrder:
            level_order(queue);
            break;
        default:
            ThrowException(InvalidParameterException,"invalid parameter order");
            break;
        }
    }
public:
    bool insert(BTreeNode<T>* node,BTNodePos pos)
    {
        bool ret= (node != NULL);
        if(ret)
        {
            if(this->root() == NULL)
            {
                node->parent=NULL;
                this->m_root=node;
            }
            else
            {
                BTreeNode<T>* parent=find(node->parent);
                if(parent != NULL)
                {
                    ret=insert_node(node,parent,pos);
                }
                else
                {
                    ThrowException(InvalidParameterException,"node->parent is invalid");
                }
            }
        }
        return ret;
    }

    bool insert(AbsTreeNode<T>* node)
    {
        return insert(get_node(node),Any);
    }

    bool insert(const T& value,BTreeNode<T>* parent,BTNodePos pos)
    {
        BTreeNode<T>* node=BTreeNode<T>::NewNode();
        bool ret= (node != NULL);
        if(ret)
        {
            node->parent=parent;
            node->value=value;

            if(this->m_root == NULL)
            {
                node->parent=NULL;
                this->m_root=node;
            }
            else
            {
                parent=find(parent);
                ret=insert_node(node,parent,pos);

                if(!ret)
                {
                    delete node;
                }
            }
        }
        else
        {
            ThrowException(NoEnoughMemoryException,"no enough memory to create new BTreeNode");
        }
        return ret;
    }

    bool insert(const T& value,AbsTreeNode<T>* parent)
    {
        return insert(value,get_node(parent),Any);
    }

    SharedPointer< AbsTree<T> > remove(const T& value)
    {
        BTree<T>* ret=NULL;
        BTreeNode<T>* node=find(value);

        if(node != NULL)
        {
            ret = remove_node(node);
            this->m_queue.clear();
        }
        return ret;
    }

    SharedPointer< AbsTree<T> > remove(AbsTreeNode<T>* node)
    {
        BTree<T>* ret=NULL;
        node=find(node);

        if(node != NULL)
        {
            ret = remove_node(get_node(node));
            this->m_queue.clear();
        }
        return ret;
    }

    BTreeNode<T>* find(const T& value) const
    {
        return find_node(root(),value);
    }

    BTreeNode<T>* find(AbsTreeNode<T>* node) const
    {
        return find_node(root(),dynamic_cast<BTreeNode<T>*>(node));
    }

    BTreeNode<T>* root() const
    {
        return get_node(this->m_root);
    }

    SharedPointer<Array<T> > traversal(BTTraversal order)
    {
        DynamicArray<T>* ret=NULL;
        LinkQueue<BTreeNode<T>*> queue;

        switch_to_queue(order,queue);

        if(queue.length() > 0)
        {
            ret=new DynamicArray<T>(queue.length());
            if(ret != NULL)
            {
                for(int i=0;queue.length() != 0;i++)
                {
                    ret->set(i,queue.front()->value);
                    queue.remove();
                }
            }
            else
            {
                ThrowException(NoEnoughMemoryException,"no enough memory to create Array");
            }
        }
        return ret;
    }

    //将二叉树按照order指定的方式转化成双向链表
    //此过程会破坏二叉树的父子结构，当前二叉树变成空树
    BTreeNode<T>* thread(BTTraversal order)
    {
        BTreeNode<T>* node=NULL;
        return thread(order,node);
    }

    BTreeNode<T>* thread(BTTraversal order,BTreeNode<T>*& tail)
    {
        LinkQueue<BTreeNode<T>*> queue;
        switch_to_queue(order,queue);

        BTreeNode<T>* ret=NULL;
        if(queue.length() > 0)
        {
            ret=queue.front();
            BTreeNode<T>* slider=ret;

            slider->left=NULL;
            queue.remove();

            while(queue.length() != 0)
            {
                slider->right=queue.front();
                queue.front()->left=slider;

                slider=queue.front();
                queue.remove();
            }
            tail=slider;

            slider->right=NULL;
            this->m_root=NULL;
        }
        return ret;
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

    ~BTree()
    {
        clear();
    }

    void next()
    {
        if(this->m_queue.length() > 0)
        {
            BTreeNode<T>* node=get_node(this->m_queue.front());

            if(node->left != NULL)
                this->m_queue.add(node->left);
            if(node->right != NULL)
                this->m_queue.add(node->right);

            this->m_queue.remove();
        }
    }

    SharedPointer<BTree<T> > clone()
    {
       return clone(root());
    }

    SharedPointer<BTree<T> > clone(BTreeNode<T>* node)
    {
        node=find(node);
        if(node != NULL)
        {
            BTree<T>* ret=new BTree<T>;
            if(ret != NULL)
            {
                ret->m_root=clone_tree(node);
                return ret;
            }
            else
            {
                delete ret;
                ThrowException(NoEnoughMemoryException,"no memory to create new BTree");
            }
        }
        else
        {
            ThrowException(InvalidParameterException,"SharedPointer<BTree<T> > clone(BTreeNode<T>* node) node is invalid");
        }

    }

    SharedPointer<BTree<T> > add(const BTree<T>& tree)
    {
        BTree<T>* ret=new BTree<T>;
        if(ret != NULL)
        {
            ret->m_root=add_tree(root(),tree.root());
        }
        else
        {
            ThrowException(NoEnoughMemoryException,"no memory to create new BTree");
        }
        return ret;
    }

    SharedPointer<BTree<T> > operator + (const BTree<T>& tree)
    {
        return (*this).add(tree);
    }

    bool operator ==(const BTree<T>& tree)
    {
        return compare(root(),tree.root());
    }

    bool operator !=(const BTree<T>& tree)
    {
        return !(*this == tree);
    }

};

}


#endif // BTREE_H
