#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "LinkList.h"

namespace ZYLib
{


template <typename T>
class CircleList:public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;

    Node* last()
    {
        return this->locate(this->m_length-1)->next;
    }

    void last_to_first()
    {
        if(this->m_head.next != NULL)
        {
            last()->next=this->m_head.next;
        }
    }

    int mod(int i) const
    {
        return this->m_length == 0 ? 0: (i % this->m_length);
    }

public:
    bool insert(int i, const T &t)
    {
        i=i%(this->m_length+1);
        bool ret=LinkList<T>::insert(i,t);

        if(ret && mod(i) == 0)
            last_to_first();

        return ret;
    }

    bool insert(const T& t)
    {
        return insert(this->m_length,t);
    }

    bool remove(int i)
    {
        bool ret=LinkList<T>::remove(mod(i));
        if(ret && mod(i) == 0)
            last_to_first();
        return ret;
    }

    bool set(int i, const T& t)
    {
        return LinkList<T>::set(mod(i),t);
    }

    T& get(int i, bool &b) const
    {
        return LinkList<T>::get(mod(i),b);
    }

    T& get(int i) const
    {
        return LinkList<T>::get(mod(i));
    }

    int find(const T &t)
    {
        int ret;
        Node* cur=this->m_head.next;

        for(ret=0;ret<this->m_length;ret++)
        {
            if(cur->value == t)
                break;
            cur=cur->next;
        }

        if(ret == this->m_length) ret=-1;

        return ret;
    }

    void clear()
    {
        Node* cur=this->m_head.next;
        while(this->m_length > 0 && cur != NULL)
        {
            Node* temp=cur;
            cur=cur->next;

            this->m_length--;
            this->destroy(temp);
        }
        this->m_head.next=NULL;
        this->m_current=NULL;

        /*
        while(this->m_length > 1)
            remove(1);

        if(this->m_length == 1)
        {
            Node* del=this->m_head.next;

            this->m_head.next=NULL;
            this->m_length=0;
            this->m_current=0;

            this->destroy(del);
        }
        */
    }

    //用于遍历CircleList的函数继承自LinkList，实现在O(n)内遍历
    bool end()
    {
        return this->m_length == 0 || this->m_head.next == NULL;
    }

    //返回值表示移动的次数
    int move(unsigned int step=1)
    {
        return LinkList<T>::move(mod(step));
    }

    ~CircleList()
    {
        clear();
    }
};

}

#endif // CIRCLELIST_H
