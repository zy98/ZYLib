#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"

namespace ZYLib {

template <typename T>
class SeqList : public List
{
protected:
    T* m_array;
    int m_length;
    int m_capacity;

public:
    bool insert(int i, const T &t)
    {
        bool ret=(i>=0) && (i<=m_length);
        ret=ret && (i<m_capacity);

        if(ret)
        {
            for(int p=m_length-1;p>=i;i++)
            {
                m_array[p+1]=m_array[p];
            }
            m_length++;
        }
    }

    bool remove(int i)
    {
        bool ret=(i>=0) && (i<m_length);

        if(ret)
        {
            for(int p=i;p<m_length;p++)
            {
                m_array[p]=m_array[p+1];
            }
            m_length--;
        }
        return ret;
    }

    bool set(int i, const T &t)
    {
        bool ret=(i>=0) && (i<m_length);

        if(ret)
        {
            m_array[i]=t;
        }
        return ret;
    }

    bool get(int i, T &t) const
    {
        bool ret=(i>=0) && (i<m_length);

        if(ret)
        {
            t=m_array[i];
        }
        return ret;
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        free(m_array);
    }

};

}

#endif // SEQLIST_H
