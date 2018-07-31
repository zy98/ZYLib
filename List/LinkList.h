#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Object/Exception.h"
#include <iostream>

using namespace std;

namespace ZYLib{

template <typename T>
class LinkList:public List<T>
{
protected:
    //struct作为结构体，一般不要写成类的形式（添加构造函数）
    struct Node:public Object
    {
        T value;
        Node* next;

        void* operator new(unsigned int size)
        {
            return Object::operator new(size);
        }

        void* operator new(unsigned int size,void* loc)
        {
            (void)size;
            return loc;
        }
    };

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
        return const_cast<LinkList<T>*>(this)->locate(i);
    }

    virtual Node* create()
    {
        return new Node();
    }

    virtual void destroy(Node* pn)
    {
        delete pn;
    }


    //m_head头节点这样写是因为如果T的构造函数中抛出异常，会导致LinkList对象构造异常
    //所以将T对象的内存换为等大小的char数组内存
    //唐的课程中将m_head设置为mutable是为了在get() const函数中调用的locate需要改变m_head的值
    //而我没有用mutable，而是重载了locate const版本的函数；
    struct : public Object
    {
        char instead[sizeof(T)];
        Node* next;
    }m_head;

    int m_length;
    Node* m_current;

public:
    LinkList()
    {
        //由于m_head不是T类型，不会调用Node构造函数赋值，所以要手动赋初始值NULL
        m_head.next=NULL;
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

                Node* pre=locate(i);
                temp->next=pre->next;
                pre->next=temp;
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

                if(m_current == del)//如果m_current指针正好指向要删除的元素，则将其指向下一个元素
                    m_current=m_current->next;

                pre->next=del->next;
                m_length--;
                destroy(del);//delete temp;
            }
            else
            {
                m_head.next=NULL;
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
            ret=-1;//如果查找到最后没有找到（cur == NULL），返回-1
        return ret;
    }

    T get(int i,bool& b) const
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

    T get(int i) const
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
        while(m_head.next)
        {
            Node* cur=m_head.next;
            m_head.next=cur->next;
            m_length--;
            destroy(cur);//delete cur;
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
        unsigned int i=0;
        while(i<step && !end())
        {
            m_current=m_current->next;
            i++;
        }
        return i;
    }

    virtual bool next()
    {
        return move() == 1;//next函数相当于向后移动一次
    }

    ~LinkList()
    {
        clear();
    }

};

}

#endif // LINKLIST_H
