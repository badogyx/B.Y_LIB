/*
 *badog-yang
 * 动态数组类
 */
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"

namespace BYLib
{
    template < typename T >
    class DynamicArray : public Array<T>
    {
    protected:
        int m_length;

        T* copy(T* array, int len, int newlen)       //复制操作
        {
            T* ret = new T[newlen];
            if( ret != NULL )
            {
                int size = (len < newlen ? len : newlen);

                for(int i=0; i<size; i++)
                {
                    ret[i] = array[i];
                }

            }
            return ret;
        }

        void update(T* array, int length)      //更新操作，防止异常错误
        {
            if( array != 0 )
            {
                T* temp = this->m_array;

                this->m_array = array;
                this->m_length = length;

                delete[] temp;
            }
            else
            {
                THROW_EXCEPTION(NOEnoughMemoryException, "no memory to update dynamicArray object...");
            }
        }

        void init(T* array, int length)      //初始化操作
        {
            if( array != 0 )
            {
                this->m_array = array;
                this->m_length = length;
            }
            else
            {
                THROW_EXCEPTION(NOEnoughMemoryException, "no memory to create dynamicArray object...");
            }
        }

    public:
        DynamicArray(int length = 0)
        {
            init(new T[length], length);
        }

        DynamicArray(const DynamicArray<T>& obj)
        {
            init( copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length );
        }

        DynamicArray<T>& operator = (const DynamicArray<T>& obj)
        {
            if(this != &obj)
            {
                T* array = copy( obj.m_array, obj.m_length, obj.m_length );

                update( array, obj.m_length );
            }

            return *this;
        }

        int length() const
        {
            return m_length;
        }

        void resize(int length)
        {
            if( length != m_length )
            {
                update(copy(this->m_array, m_length, length), length);
            }

        }

        ~DynamicArray()
        {
            delete[] this->m_array;
        }
    };

}


#endif // DYNAMICARRAY_H
