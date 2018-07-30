#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace ZYLib {

template <typename T,const int N>
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;
    unsigned char m_space[sizeof(Node)*N];
    bool m_used[N];

    Node* create()
    {
        Node* ret=NULL;
        for(int i=0;i<N;i++)
        {
            if(m_used[i])
            {
                ret=reinterpret_cast<Node*>(m_space)+i;
                ret=new(ret) Node();
                m_used[i]=false;
                break;
            }
        }
        return ret;
    }

    void destroy(Node* pn)
    {
        Node* pc=reinterpret_cast<Node*>(m_space);
        for(int i=0;i<N;i++)
        {
            if(pn == pc+i)
            {
                m_used[i]=true;
                pn->~Node();
                break;
            }
        }
    }

public:
    StaticLinkList()
    {
        for(int i=0;i<N;i++)
            m_used[i]=true;
    }
};

}

#endif // STATICLINKLIST_H
