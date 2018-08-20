﻿#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include "List.h"
#include "Object/Exception.h"

namespace ZYLib
{

template <typename T>
class DualLinkList:public List<T>
{
protected:
    struct Node:public Object
    {
        T value;
        Node* next;
        Node* pre;
    };

    struct : public Object
    {
        char instead[sizeof(T)];
        Node* next;
        Node* pre;
    }m_head;

    //定位到i-1个节点
    Node* locate(int i)
    {
        Node* pre=reinterpret_cast<Node*>(&m_head);
        for(int p=0;p<i;p++)
        {
            pre=pre->next;
        }
        return pre;
    }

    Node* locate(int i) const
    {
        return const_cast<DualLinkList<T>*>(this)->locate(i);
    }

    virtual Node* create()
    {
        return new Node();
    }

    virtual void destroy(Node* pn)
    {
        delete pn;
    }

    int m_length;
    Node* m_current;



public:
    DualLinkList()
    {
        //由于m_head不是T类型，不会调用Node构造函数赋值，所以要手动赋初始值NULL
        m_head.next=NULL;
        m_head.pre=NULL;
        m_current=NULL;
        m_length=0;
    }

    bool insert(int i,const T& t)
    {
        bool ret=( (0<=i && i<=m_length) );
        if(ret)
        {
            Node* temp=create();

            if(temp != NULL)
            {
                temp->value=t;

                Node* last=locate(i);
                Node* next=last->next;

                temp->next=last->next;
                last->next=temp;

                //如果插入位置不是0，就将插入节点的前驱指针指向上一个节点，否则就置为0
                if(i != 0)
                    temp->pre=last;
                else
                    temp->pre=NULL;

                //如果插入位置不是链表末尾，就将下一个元素的前驱指针指向插入节点
                if(next != NULL)
                    next->pre=temp;

                m_length++;
            }
            else
            {
                ThrowException(NoEnoughMemoryException,"no enough memory to create new element");
            }
        }
        else
        {
            ThrowException(IndexOutOfBoundsException,"LinkList insert out of Index!");
        }
        return ret;
    }

    bool insert(const T& t)
    {
        return insert(m_length,t);
    }

    bool remove(int i)
    {
        bool ret=( (0<=i) && (i<m_length));
        if(ret)
        {
            if(m_length > 0)
            {
                Node* pre=locate(i);
                Node* del=pre->next;
                Node* next=del->next;

                if(m_current == del)//如果m_current指针正好指向要删除的元素，则将其指向下一个元素
                    m_current=m_current->next;

                pre->next=del->next;
                if(next != NULL)
                    next->pre=del->pre;

                m_length--;
                destroy(del);//delete temp;
            }
            else
            {
                m_head.next=NULL;
                m_head.pre=NULL;
                m_current=NULL;
            }
        }
        else
        {
            ThrowException(IndexOutOfBoundsException,"LinkList remove out of Index!");
        }
        return ret;
    }

    bool set(int i,const T& t)
    {
        bool ret=( (0<=i) && (i<m_length));
        if(ret)
        {
            locate(i)->next->value=t;
        }
        else
        {
            ThrowException(IndexOutOfBoundsException,"LinkList set out of Index!");
        }
        return ret;
    }

    int find(const T &t)
    {
        int ret=-1;
        Node* cur=m_head.next;
        while(cur)
        {
            ret++;

            if(cur->value == t)
                break;

            cur=cur->next;
        }

        if(cur == NULL)
            ret=-1;

        return ret;
    }

    T& get(int i,bool& b) const
    {
        b=( (0<=i) && (i<m_length));
        if(b)
        {
            return locate(i)->next->value;
        }
        else
        {
            ThrowException(IndexOutOfBoundsException,"LinkList get out of Index!");
        }
    }

    T& get(int i) const
    {
        bool b;
        return get(i,b);
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        while(m_length > 0)
        {
            remove(0);
        }
    }

    //用于遍历LinkList的函数，实现在O(n)内遍历
    virtual int begin(unsigned int start = 0)
    {
        if(start == 0)
            m_current=m_head.next;
        else
        {
            start = move(start);
        }
        return start;
    }

    virtual bool end()
    {
        return m_current == NULL;
    }

    virtual T& current()
    {
        return m_current->value;
    }

    //返回值表示移动的次数
    virtual int move(unsigned int step=1)
    {
        int i=0;
        while(i<step && !end())
        {
            m_current=m_current->next;
            i++;
        }
        return i;
    }

    virtual int movePre(int step=1)
    {
        int i=0;
        while(i<step && m_current != NULL)
        {
            m_current=m_current->pre;
            i++;
        }
        return i;
    }

    virtual bool next()
    {
        return move() == 1;
    }

    virtual bool pre()
    {
        return movePre() == 1;
    }

    ~DualLinkList()
    {
        clear();
    }
};

}

#endif // DUALLINKLIST_H
