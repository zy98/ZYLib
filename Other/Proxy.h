#ifndef PROXY_H
#define PROXY_H

#include "Sort/Sort.h"


struct Test
{
    int id;
    int data1[1000];
    double data2[500];

    bool operator > (Test& obj)
    {
        return id > obj.id;
    }

    bool operator >= (Test& obj)
    {
        return id >= obj.id;
    }

    bool operator < (Test& obj)
    {
        return id < obj.id;
    }

    bool operator <= (Test& obj)
    {
        return id <= obj.id;
    }
};

class TestProxy
{
protected:
    Test* m_test;

public:

    int& id()
    {
        return m_test->id;
    }

    int* data1() const
    {
        return m_test->data1;
    }

    Test& test() const
    {
        return *m_test;
    }

    double* data2() const
    {
        return m_test->data2;
    }

    bool operator > (TestProxy& obj)
    {
        return id() > obj.id();
    }

    bool operator >= (TestProxy& obj)
    {
        return id() >= obj.id();
    }

    bool operator < (TestProxy& obj)
    {
        return id() < obj.id();
    }

    bool operator <= (TestProxy& obj)
    {
        return id() <= obj.id();
    }

    Test& operator= (Test& obj)
    {
        m_test=&obj;
        return obj;
    }
};

#endif // PROXY_H
