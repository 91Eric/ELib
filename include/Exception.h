#ifndef _EXCEPTION_H
#define _EXCEPTION_H

namespace DTLib
{

#define THROW_EXCEPTION(e,m) (throw e(m,__FILE__,__LINE__))

class Exception   //顶层异常的抽象基类
{
public:
    Exception(const char* message);
    Exception(const char* file,int line);
    Exception(const char* message,const char* file,int line);

    Exception(const Exception& e);
    Exception& operator=(const Exception& e);

    virtual const char* message() const;
    virtual const char* location() const;

    virtual ~Exception()=0;   //纯虚函数被实现了，就变为虚函数，C++规定，所有析构函数必须有实现！！！！
protected:
    char* m_message;
    char* m_location;

    void init(const char* messagg,const char* file,int line);

};

class ArithmeticExxception:public Exception //计算异常
{
public:
    ArithmeticExxception():Exception(0){}  //显式调用父类构造函数 Exception(const char* message),其中message 为NULL ,这样分配的m_message实际是NULL
    ArithmeticExxception(const char* message):Exception(message){}
    ArithmeticExxception(const char* file,int line):Exception(file,line){}
    ArithmeticExxception(const char* message,const char* file,int line):Exception(message,file,line){}

    ArithmeticExxception(const ArithmeticExxception& e):Exception(e){}   //拷贝构造函数直接调用父类的构造函数

    ArithmeticExxception& operator=(const ArithmeticExxception& e)
    {
        Exception::operator =(e);
        return *this;
    }
};

class IndexOutOfBoundsExceptio:public Exception  //越界
{
public:
    IndexOutOfBoundsExceptio():Exception(0) {}
    IndexOutOfBoundsExceptio(const char* message):Exception(message){}
    IndexOutOfBoundsExceptio(const char* file,int line):Exception(file,line){}
    IndexOutOfBoundsExceptio(const char* message,const char* file,int line):Exception(message,file,line){}

    IndexOutOfBoundsExceptio(const IndexOutOfBoundsExceptio& e):Exception(e){}

    IndexOutOfBoundsExceptio& operator =(const IndexOutOfBoundsExceptio& e)
    {
        Exception::operator =(e);
        return *this;
    }
};

class NullPointerException:public Exception  //空指针
{
public:
    NullPointerException():Exception(0){}
    NullPointerException(const char* message):Exception(message){}
    NullPointerException(const char* file,int line):Exception(file,line){}
    NullPointerException(const char* message,const char* file,int line):Exception(message,file,line){}

    NullPointerException(const NullPointerException& e):Exception(e){}

    NullPointerException& operator =(const NullPointerException& e)
    {
        Exception::operator =(e);
        return *this;
    }

};

class NoEnoughMemoryException:public Exception  //内存不足
{
public:
    NoEnoughMemoryException():Exception(0){}
    NoEnoughMemoryException(const char* message):Exception(message){}
    NoEnoughMemoryException(const char* file,int line):Exception(file,line){}
    NoEnoughMemoryException(const char* message,const char* file,int line):Exception(message,file,line){}

    NoEnoughMemoryException(const NoEnoughMemoryException& e):Exception(e){}
    NoEnoughMemoryException& operator =(const NoEnoughMemoryException& e)
    {
        Exception::operator =(e);
        return *this;
    }

};
class InvalidParameterException:public Exception  //参数错误
{

};

}


#endif // EXCEPTION_H
