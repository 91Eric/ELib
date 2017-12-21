#include "./include/Exception.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
using namespace std;

namespace ELib
{

void Exception::init(const char *message, const char *file, int line)
{
    //如果message为NULL会报错，原因是strdup内部调用了strlen（），后者参数不能为NULL,因此这里进行判断
    m_message = (message ? strdup(message) : NULL);
    if(file!=NULL)
    {
        char sl[16]={0};
        #ifdef _linux_
            sprintf(sl,"%d",line);
        #elif
            itoa(sl,line,10);
        #endif
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
