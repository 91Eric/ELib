#include "./include/Exception.h"
#include <cstring>
#include <cstdlib>
#include <cassert>
using namespace std;

namespace ELib
{

void Exception::init(const char *message, const char *file, int line)
{
//    if(message == NULL)    //如果message为NULL会报错，原因是内部调用了strlen（），后者参数不能为NULL,因此开辟一个空间
//    {
//        m_message = reinterpret_cast<char*>(malloc(1));
//        *m_message = '\0';
//    }
//    else
//    {
//         m_message=strdup(message);
//    }
    m_message = (message ? strdup(message) : NULL);
    if(file!=NULL)
    {
        char sl[16]={0};
        itoa(line,sl,10);
        m_location=static_cast<char*>(malloc(strlen(file)+strlen(sl)+2));
        strcpy(m_location,file);
        strcat(m_location,":");
        strcat(m_location,sl);

    }
    else
    {
        m_location=NULL;
    }
}

Exception::Exception(const char* message)
{
    init(message,NULL,0);
}
Exception::Exception(const char* file,int line)
{
    init(NULL,file,line);
}
Exception::Exception(const char* message,const char* file,int line)
{
    init(message,file,line);
}

Exception::Exception(const Exception &e)
{
    m_message=strdup(e.m_message);
    m_location=strdup(e.m_location);
}
Exception& Exception:: operator=(const Exception& e)
{
    if(this!=&e)
    {
        free(m_message);
        free(m_location);

        m_message=strdup(e.m_message);
        m_location=strdup(e.m_location);
    }
    return *this;
}

const char* Exception::message() const
{
    return m_message;
}
const char* Exception::location() const
{
    return m_location;
}

Exception::~Exception()
{
    free(m_message);
    free(m_location);
}

}


/*
int main（）
{
try
{
    throw Exception("test",__FILE__,__LINE__);
}
catch(const Exception& e)//此处const可有可无
{
}
}

*/


