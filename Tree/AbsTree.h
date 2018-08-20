#ifndef ABSTREE_H
#define ABSTREE_H

#include "Object/Object.h"
#include "Tree/AbsTreeNode.h"
#include "Pointer/SharedPointer.h"
#include "Queue/LinkQueue.h"
#include "Object/Exception.h"


namespace ZYLib
{

template <typename T>
class AbsTree:public Object
{
protected:
    AbsTreeNode<T>* m_root;
    LinkQueue<AbsTreeNode<T>*> m_queue;

    AbsTree(const AbsTree<T>&);
    AbsTree<T>& operator = (const AbsTree<T>&);

public:
    AbsTree(){ m_root=NULL;}
    virtual bool insert(AbsTreeNode<T>* node)=0;
    virtual bool insert(const T& value,AbsTreeNode<T>* parent)=0;
    virtual SharedPointer< AbsTree<T> > remove(const T& value)=0;
    virtual SharedPointer< AbsTree<T> > remove(AbsTreeNode<T>* node)=0;
    virtual AbsTreeNode<T>* find(const T& value) const =0;
    virtual AbsTreeNode<T>* find(AbsTreeNode<T>* node) const =0;
    virtual AbsTreeNode<T>* root() const=0;
    virtual int degree() const=0;
    virtual int count() const=0;
    virtual int height()=0;
    virtual void clear()=0;

    virtual void begin()
    {
        if(root() != NULL)
        {
            m_queue.clear();
            m_queue.add(root());
        }
    }

    virtual T current()
    {
        if(!end())
            return m_queue.front()->value;
        else
            ThrowException(InvalidOperationException,"no value in current tree");
    }


    virtual bool end()
    {
        return m_queue.length() == 0;
    }

    virtual void next()=0;
};

}


#endif // ABSTREE_H
