#include "String.h"
#include <cstring>
#include <cstdlib>
#include "Object/Exception.h"

namespace ZYLib
{
//char c代码优化问题

void String::init(const char* s)
{
    m_str=strdup(STR(s));

    if(m_str)
    {
        m_length=strlen(STR(s));
    }
    else
    {
        ThrowException(NoEnoughMemoryException,"no memory to init String");
    }
}

String::String()
{
    init("");
}

String::String(const char* s)
{
    init(s);
}

String::String(const String& s)
{
    init(s.m_str);
}

String::String(char c)
{
    char s[]={c,'\0'};
    init(s);
}

int String::length()
{
    return m_length;
}

const char* String::str() const
{
    return m_str;
}

bool String::operator ==(const String& s) const
{
    return strcmp(m_str,s.m_str) == 0;
}
bool String::operator ==(const char* s) const
{
    if(s != NULL)
        return strcmp(m_str,s) == 0;
    else
        ThrowException(InvalidParameterException,"pointer can not be NULL in operator ==");
}

bool String::operator !=(const String& s) const
{
    return !(*this == s);
}
bool String::operator !=(const char* s) const
{
    return !(*this == s);
}

bool String::operator >(const String& s) const
{
    return (strcmp(m_str,s.m_str) > 0);
}
bool String::operator >(const char* s) const
{
    if(s != NULL)
        return strcmp(m_str,s) > 0;
    else
        ThrowException(InvalidParameterException,"pointer can not be NULL in operator >");
}
bool String::operator <(const String& s) const
{
    return (strcmp(m_str,s.m_str) < 0);
}
bool String::operator <(const char* s) const
{
    if(s != NULL)
        return strcmp(m_str,s) < 0;
    else
        ThrowException(InvalidParameterException,"pointer can not be NULL in operator <");
}

bool String::operator >=(const String& s) const
{
    return (strcmp(m_str,s.m_str) >= 0);
}
bool String::operator >=(const char* s) const
{
    if(s != NULL)
        return strcmp(m_str,s) >= 0;
    else
        ThrowException(InvalidParameterException,"pointer can not be NULL in operator >=");
}

bool String::operator <=(const String& s) const
{
    return (strcmp(m_str,s.m_str) <= 0);
}
bool String::operator <=(const char* s) const
{
    if(s != NULL)
        return strcmp(m_str,s) <= 0;
    else
        ThrowException(InvalidParameterException,"pointer can not be NULL in operator <=");
}

String String::operator +(const char* s) const
{
    if(strlen(STR(s)) != 0)
    {
        String ret;

        int len=strlen(m_str)+strlen(STR(s));
        char* str=reinterpret_cast<char*>(malloc(len+1));

        if(str)
        {
            strcpy(str,m_str);
            strcat(str,s);

            free(ret.m_str);

            ret.m_str=str;
            ret.m_length=len;
        }
        else
        {
            ThrowException(NoEnoughMemoryException,"no enough memmory to add string");
        }

        return ret;
    }
    else
    {
        return *this;
    }
}
String String::operator +(const String& s) const
{
    return (*this + s.m_str);
}
String String::operator +(char c) const
{
    char s[]={c,'\0'};
    return (*this + s);
}

String& String::operator +=(const char* s)
{
    return *this = *this + s;
}
String& String::operator +=(const String& s)
{
    return *this = *this + s.m_str;
}
String& String::operator +=(char c)
{
    char s[]={c,'\0'};
    return *this = *this + s;
}

String& String::operator =(const char* s)
{
    if(m_str != s)
    {
        char* str=strdup(STR(s));
        if(str)
        {
            free(m_str);
            m_str=str;
            m_length=strlen(s);
        }
        else
        {
            ThrowException(NoEnoughMemoryException,"no enough memory to assign string");
        }
    }
    return *this;
}
String& String::operator =(const String &s)
{
    return *this = s.m_str;
}
String& String::operator =(char c)
{
    char s[]={c,'\0'};
    return *this = s;
}

char& String::operator[] (int i)
{
    if(0 <= i && i < m_length)
    {
        return m_str[i];
    }
    else
    {
        ThrowException(IndexOutOfBoundsException,"index out of String");
    }
}
char String::operator[] (int i) const
{
    return const_cast<String&>(*this)[i];
}

bool String::startWith(const char* s) const
{
    bool ret=true;
    if(s != NULL)
    {
        int len=strlen(s)-1;
        for(int i=0;i<len;i++)
            ret = ret && s[i] == m_str[i];
    }
    else
    {
        ret=false;
    }
    return ret;
}
bool String::startWith(const String& s) const
{
    return startWith(s.m_str);
}
bool String::endOf(const char* s) const
{
    bool ret=true;

    if(s != NULL)
    {
        int strl=strlen(m_str)-1;
        int sl=strlen(s)-1;
        while(sl > 0 && strl > 0)
        {
            if(m_str[strl] != s[sl])
            {
                ret=false;
                break;
            }
            sl--;
            strl--;
        }
    }
    else
    {
        ret=false;
    }
    return ret;
}
bool String::endOf(const String& s) const
{
    return endOf(s.m_str);
}

String& String::insert(int index,const char* s)
{
    if( (0 <= index) && (index <= m_length) )
    {
        if(s != NULL && s != '\0')
        {
            int slen=strlen(s);
            char* str=reinterpret_cast<char*>(malloc(m_length + slen + 1));

            if(str != NULL)
            {
                strncpy(str,m_str,index);
                strncpy(str+index,s,slen);
                strncpy(str+index+slen,m_str+index,m_length-index);

                //str[m_length + slen] = '\0';

                free(m_str);
                m_str=str;
                m_length=m_length+slen;
            }
            else
            {
                ThrowException(NoEnoughMemoryException,"String no enough memory to insert");
            }
        }
    }
    else
    {
        ThrowException(IndexOutOfBoundsException,"String index out of bounds");
    }

    return *this;
}
String& String::insert(int index, const String& s)
{
    return insert(index,s.m_str);
}

String& String::trim()
{
    int b=0;
    int e=m_length-1;
    while(m_str[b] == ' ') b++;
    while(m_str[e] == ' ') e--;

    m_str[e+1]='\0';
    for(int i=0;i+b<=e+1;i++) //e+1表示字符串后的\0，将字符串中的b到e+1向前移动；与b==0无关；
    {
        m_str[i]=m_str[i+b];
    }

    m_length=e-b+1;

    return *this;
}

/*
 * 改进
String& String::trim()
{
    char* str=m_str+m_length;
    int count=0;
    while(*--str == ' ') count++;
    *(str+1)='\0'; //去掉尾部空格
    m_length-=count;

    str=m_str;
    count=0;//空格个数

    while(*str == ' ')
        count++,str++;

    while(*str != '\0')
    {
        *(str-count) = *str;
        str++;
    }
    *(str-count) = *str;   //将非空格字符向前移动count个，最后将字符串结束符移动；
    m_length-=count;

    return *this;
}
*/

String::~String()
{
    free(m_str);
}

}


