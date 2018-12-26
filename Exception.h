/*
 *badog-yang
 * 异常处理 
 */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Object.h"

namespace BYLib 
{

#define THROW_EXCEPTION(e, m) (throw e(m, __FILE__, __LINE__))

    class Exception : public Object
    {
        
    private:
        char* m_location;
        char* m_message;
        
        void init(const char* message, const char* file, int line);
        
    public:
        Exception(const char* message);
        Exception(const char* file, int line);
        Exception(const char* message, const char* file, int line);
        
        Exception(const Exception& e);
        Exception& operator = (const Exception& e);
        
        virtual const char* message() const;        //错误信息
        virtual const char* location() const;       //具体错误地点
        
        virtual ~Exception() = 0;
    };
    
    class ArithmeticException : public Exception
    {
    public:
        ArithmeticException() : Exception(0) { }
        ArithmeticException(const char* message) : Exception(message) { }
        ArithmeticException(const char* file, int line) : Exception(file, line) { }
        ArithmeticException(const char* message, const char*file, int line) : Exception(message, file, line) { }
        
        ArithmeticException(const ArithmeticException& e) : Exception(e) { }
        
        ArithmeticException operator =(const ArithmeticException& e)
        {
            Exception::operator =(e);
            
            return *this;
        }
        
    };
    
    class NullPointerException : public Exception
    {
    public:
        NullPointerException() : Exception(0) { }
        NullPointerException(const char* message) : Exception(message) { }
        NullPointerException(const char* file, int line) : Exception(file, line) { }
        NullPointerException(const char* message, const char*file, int line) : Exception(message, file, line) { }
        
        NullPointerException(const NullPointerException& e) : Exception(e) { }
        
        NullPointerException operator =(const NullPointerException& e)
        {
            Exception::operator =(e);
            
            return *this;
        }
        
    };
    
    class IndexOutOfBoundsException : public Exception
    {
    public:
        IndexOutOfBoundsException() : Exception(0) { }
        IndexOutOfBoundsException(const char* message) : Exception(message) { }
        IndexOutOfBoundsException(const char* file, int line) : Exception(file, line) { }
        IndexOutOfBoundsException(const char* message, const char*file, int line) : Exception(message, file, line) { }
        
        IndexOutOfBoundsException(const IndexOutOfBoundsException& e) : Exception(e) { }
        
        IndexOutOfBoundsException operator =(const IndexOutOfBoundsException& e)
        {
            Exception::operator =(e);
            
            return *this;
        }
        
    };
    
    class NOEnoughMemoryException : public Exception
    {
    public:
        NOEnoughMemoryException() : Exception(0) { }
        NOEnoughMemoryException(const char* message) : Exception(message) { }
        NOEnoughMemoryException(const char* file, int line) : Exception(file, line) { }
        NOEnoughMemoryException(const char* message, const char*file, int line) : Exception(message, file, line) { }
        
        NOEnoughMemoryException(const NOEnoughMemoryException& e) : Exception(e) { }
        
        NOEnoughMemoryException operator =(const NOEnoughMemoryException& e)
        {
            Exception::operator =(e);
            
            return *this;
        }
        
    };
    
    class InvalidParameterException : public Exception
    {
    public:
        InvalidParameterException() : Exception(0) { }
        InvalidParameterException(const char* message) : Exception(message) { }
        InvalidParameterException(const char* file, int line) : Exception(file, line) { }
        InvalidParameterException(const char* message, const char*file, int line) : Exception(message, file, line) { }
        
        InvalidParameterException(const InvalidParameterException& e) : Exception(e) { }
        
        InvalidParameterException operator =(const InvalidParameterException& e)
        {
            Exception::operator =(e);
            
            return *this;
        }
        
    };
    
    class InvalidOperationException : public Exception
    {
    public:
        InvalidOperationException() : Exception(0) { }
        InvalidOperationException(const char* message) : Exception(message) { }
        InvalidOperationException(const char* file, int line) : Exception(file, line) { }
        InvalidOperationException(const char* message, const char*file, int line) : Exception(message, file, line) { }
        
        InvalidOperationException(const InvalidOperationException& e) : Exception(e) { }
        
        InvalidOperationException operator =(const InvalidOperationException& e)
        {
            Exception::operator =(e);
            
            return *this;
        }
        
    };
}


#endif // EXCEPTION_H
