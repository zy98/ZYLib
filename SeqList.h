#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"

namespace ZYLib {

template <typename T>
class SeqList : public List<T>
{
protected:
    T* m_array;
    int m_length;

public:
    bool insert(int i, const T& t)
    {
        bool ret=(i>=0) && (i<=m_length);
        ret=ret && (i<capacity());

        if(ret)
        {
            for(int p=m_length-1;p>=i;i++)
            {
                m_array[p+1]=m_array[p];
            }
            m_array[i]=t;
            m_length++;
        }
        return ret;
    }

    bool insert(const T& t)
    {
        return insert(m_length,t);
    }

    bool remove(int i)
    {
        bool ret=(i>=0) && (i<m_length);

        if(ret)
        {
            for(int p=i;p<m_length-1;p++)//<m_lengtth-1;是为了移动数组时不会越界，p+1可能越界；
            {
                m_array[p]=m_array[p+1];
            }
            m_length--;
        }
        return ret;
    }

    int find(const T& t)
    {
        int ret=-1;
        for(int i=0;i<length();i++)
        {
            if(m_array[i] == t)
            {
                ret=i;
                break;
            }
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

    T get(int i,bool& b) const
    {
        b=(i>=0) && (i<m_length);

        if(b)
            return m_array[i];
        else
            ThrowException(IndexOutOfBoundsException,"SeqList -> get out of index");
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
        m_length=0;
    }

    //顺序存储线性表的数组访问方式
    T& operator [] (int i)
    {
        if((i>=0) && (i<m_length))
        {
            return m_array[i];
        }
        else
        {
            ThrowException(IndexOutOfBoundsException,"T& SeqList<T>::operator[] out of index!");
        }
    }

    //SeqList及其子类的const对象不能初始化，如何使用const函数？
    T operator [](int i) const
    {
        return const_cast<SeqList<T>&>(*this)[i];
    }

    //顺序存储空间的容量
    virtual int capacity() const =0;

};

}

#endif // SEQLIST_H
