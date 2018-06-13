﻿#ifndef LIST_H
#define LIST_H

#include "Object.h"

namespace ZYLib {

template <typename T>
class List : public Object
{
    virtual bool insert(int i,const T& t) =0;
    virtual bool remove(int i) =0;
    virtual bool set(int i,const T& t) =0;
    virtual bool get(int i,T& t) const =0;
    virtual int length() const =0;
    virtual void clear() =0;
};

}


#endif // LIST_H