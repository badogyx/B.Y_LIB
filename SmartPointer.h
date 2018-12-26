/*
 * badog-yang
 * 智能指针类 一个智能指针只能指向一个不同的对象
*/
#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"

namespace BYLib
{
    template< typename T >
    class SmartPointer : public Pointer<T>
    {
        T* m_pointer;
        
    public:
        SmartPointer( T* p = NULL ) : Pointer<T>(p)
        {

        }
        
        SmartPointer( const SmartPointer<T>& obj )
        {
            this->m_pointer = obj.m_pointer;
            const_cast< SmartPointer<T>& >(obj).m_pointer = NULL;
        }
        
        SmartPointer<T>& operator = ( const SmartPointer<T>& obj )
        {
            if( this != &obj )
            {
                T* p = this->m_pointer;
                m_pointer = obj.m_pointer;
                const_cast< SmartPointer<T>& >(obj).m_pointer = NULL;
                delete p;
            }
            return *this;
        }
        
        ~SmartPointer()
        {
            delete m_pointer;
        }
    };
    
}

#endif // SMARTPOINTER_H
