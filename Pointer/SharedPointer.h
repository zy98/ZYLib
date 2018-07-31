#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "Pointer.h"
#include "Object/Exception.h"

using namespace std;
namespace ZYLib
{

template <typename T>
class SharedPointer:public Pointer<T>
{
protected:
    int* m_ref;

    void assign(const SharedPointer<T>& obj)
    {
        this->m_pointer=obj.m_pointer;
        this->m_ref=obj.m_ref;

        if(this->m_ref)
            (*this->m_ref)++;
    }

public:
    SharedPointer(T* p=NULL):Pointer<T>(p),m_ref(NULL)
    {
        if(p)
        {
            if(!(m_ref=new int(1)))//这个实现看起来巨鸡儿诡异，不知道怎么改
                ThrowException(NoEnoughMemoryException,"no memory to create SharedPoninter::m_ref");
        }

    }

    SharedPointer(const SharedPointer<T>& obj):Pointer<T>(NULL)
    {
        assign(obj);
    }

    SharedPointer<T>& operator =(const SharedPointer<T>& obj)
    {
        if(this != &obj)
        {
            clear();
            assign(obj);
        }
        return *this;
    }

    void clear()
    {
        T* pointer=this->m_pointer;
        int* ref=m_ref;

        this->m_pointer=NULL;
        m_ref=NULL;

        if(ref)
        {
            (*ref)--;
            if(*ref == 0)
            {
                delete ref;
                delete pointer;
            }
        }
    }

    int getref()
    {
        int ret=-1;
        if(m_ref)
        {
            ret=*m_ref;
        }
        return ret;
    }

    ~SharedPointer()
    {
        clear();
    }
};

template <typename T>
bool operator ==(const SharedPointer<T>& l,const SharedPointer<T>& r)
{
    return l.get() == r.get();
}

template <typename T>
bool operator != (const SharedPointer<T>& l,const SharedPointer<T>& r)
{
    return !(l == r);
}

}

#endif // SHAREDPOINTER_H
