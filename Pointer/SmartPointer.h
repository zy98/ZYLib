﻿#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"

namespace ZYLib {

template <typename T>
class SmartPointer : public Pointer<T>
{
public:
    SmartPointer(T* p = NULL):Pointer<T>(p){}

    SmartPointer(const SmartPointer<T>& obj):Pointer<T>(obj.m_pointer)
    {
        //this->m_pointer=obj.m_pointer;
        const_cast<SmartPointer<T>&>(obj).m_pointer=NULL;
    }

    SmartPointer<T>& operator = (const SmartPointer<T>& obj)
    {
        if(this != &obj)
        {
            T* temp=this->m_pointer;
            this->m_pointer=obj.m_pointer;
            const_cast<SmartPointer<T>&>(obj).m_pointer=NULL;
            delete temp;//异常安全
        }
        return *this;
    }

    ~SmartPointer()
    {
        delete this->m_pointer;
    }

};

}

#endif // SMARTPOINTER_H
