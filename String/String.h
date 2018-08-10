#ifndef STRING_H
#define STRING_H
#include "Object/Object.h"

namespace ZYLib
{

#define STR(s) s ? s : ""

class String:public Object
{
protected:
    char* m_str;
    int m_length;

    void init(const char* s);

    static int* Next(const char* s);
    static int kmp(const char* source,const char* aim);
public:
    String();
    String(const char* s);
    String(const String& s);
    //添加String(char c)构造函数的意义在于当函数的参数为char时可隐式转换为const String&；
    String(char c);

    bool operator ==(const String& s) const;
    bool operator ==(const char* s) const;
    bool operator !=(const String& s) const;
    bool operator !=(const char* s) const;
    bool operator >(const String& s) const;
    bool operator >(const char* s) const;
    bool operator <(const String& s) const;
    bool operator <(const char* s) const;
    bool operator >=(const String& s) const;
    bool operator >=(const char* s) const;
    bool operator <=(const String& s) const;
    bool operator <=(const char* s) const;

    String operator +(const char* s) const;
    String operator +(const String& s) const;
    String& operator +=(const char* s);
    String& operator +=(const String& s);

    String operator -(const char* s) const;
    String operator -(const String& s) const;
    String& operator -=(const char* s);
    String& operator -=(const String& s);

    String& operator =(const char* s);
    String& operator =(const String& s);

    char& operator[] (int i);
    char operator[] (int i) const;

    bool startWith(const char* s) const;
    bool startWith(const String& s) const;
    bool endOf(const char* s) const;
    bool endOf(const String& s) const;

    String& insert(int index,const char* s);
    String& insert(int index, const String& s);
    String& trim();

    int indexOf(const char* s) const;
    int indexOf(const String& s) const;
    String& remove(int index,int len);
    String& remove(const char* s);
    String& remove(const String& s);

    String& replace(const char* t,const char* s);
    String& replace(const char* t,const String& s);
    String& replace(const String& t,const char* s);
    String& replace(const String& t,const String& s);

    String sub(int i,int len) const;


    int length();
    const char* str() const;

    ~String();
};

}


#endif // STRING_H
