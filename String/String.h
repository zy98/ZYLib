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
public:
    String();
    String(const char* s);
    String(const String& s);
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
    String operator +(char c) const;
    String& operator +=(const char* s);
    String& operator +=(const String& s);
    String& operator +=(char c);

    String& operator =(const char* s);
    String& operator =(const String& s);
    String& operator =(char s);

    char& operator[] (int i);
    char operator[] (int i) const;

    bool startWith(const char* s) const;
    bool startWith(const String& s) const;
    bool endOf(const char* s) const;
    bool endOf(const String& s) const;

    String& insert(int index,const char* s);
    String& insert(int index, const String& s);

    String& trim();

    int length();
    const char* str() const;

    ~String();
};

}


#endif // STRING_H
