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

int* String::Next(const char* s)
{
    int len=strlen(s);
    int* next=new int[len];

    if(next)
    {
        int k=0;
        next[0] = 0;

        for(int i=1;i<len;i++)
        {
            while(k > 0 && s[i] != s[k])
                k=next[k-1];

            if(s[i] == s[k])
                k++;

            next[i]=k;
        }
    }
    else
    {
        delete [] next;
        next=NULL;
    }
    return next;
}
int String::kmp(const char* source,const char* aim)
{
    int ret=-1;
    int mlen=strlen(aim);
    int slen=strlen(source);

    if(mlen > 0 && mlen <=slen)
    {
        int* next=Next(aim);

        if(next)
        {
            for(int i=0,f=0;i<slen;i++)
            {
                while(f>0 && source[i] != aim[f])
                    f=next[f-1];

                if(source[i] == aim[f])
                    f++;

                if(f == mlen)
                {
                    ret=i-mlen+1;
                    break;
                }
            }
        }
        delete[] next;
    }
    return ret;
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

//*添加String(char c)构造函数的意义在于当函数的参数为char时可隐式转换为const String&；
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

String& String::operator +=(const char* s)
{
    return *this = *this + s;
}
String& String::operator +=(const String& s)
{
    return *this = *this + s.m_str;
}

String String::operator -(const char* s) const
{
    return String(*this).remove(s);
}
String String::operator -(const String& s) const
{
    return String(*this).remove(s);
}
String& String::operator -=(const char* s)
{
    return (*this).remove(s);
}
String& String::operator -=(const String& s)
{
    return (*this).remove(s);
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

                //如果末尾不添加\0，当在字符串末尾插入一个字符时（const char* s=char c）就会出现一个没有结束符的字符串；
                str[m_length + slen] = '\0';

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

int String::indexOf(const char* s) const
{
    return kmp(m_str,STR(s));
}
int String::indexOf(const String& s) const
{
    return kmp(m_str,s.m_str);
}
String& String::remove(int index,int len)
{
    if(index >= 0 && index < m_length)
    {
        int i=index;
        int m=index + len;

        //依次将m移到i直到字符串末尾；
        while(i < m && m < m_length)
        {
            m_str[i++]=m_str[m++];
        }
        m_str[i]='\0';
        m_length=i;
    }
    return *this;
}
String& String::remove(const char* s)
{
    return remove(indexOf(s), strlen(STR(s)));
}
String& String::remove(const String& s)
{
    return remove(indexOf(s), strlen(s.m_str));
}

String& String::replace(const char* t,const char* s)
{
    int i=indexOf(t);
    if(i >= 0)
    {
        if(strlen(t) == strlen(STR(s)) )
        {
            char* str=m_str+i;
            while(*s != '\0')
                *(str++)=*(s++);
        }
        else
        {
            remove(t);
            insert(i,STR(s));
        }
    }
    return *this;
}
String& String::replace(const char* t,const String& s)
{
    return replace(t,s.m_str);
}
String& String::replace(const String& t,const char* s)
{
    return replace(t.m_str,s);
}
String& String::replace(const String& t,const String& s)
{
    return replace(t.m_str,s.m_str);
}

String String::sub(int i,int len) const
{
    if(i >= 0 && i < m_length)
    {
        if(len > m_length-i) len = m_length-i;

        char* str=reinterpret_cast<char*>(malloc(len+1));
        if(str)
        {
            strncpy(str,m_str+i,len);
            str[len]='\0';
            return String(str);
        }
    }
    else
    {
        ThrowException(IndexOutOfBoundsException,"String String::sub index out of bounds");
    }
    return String();
}

String::~String()
{
    free(m_str);
}

}


