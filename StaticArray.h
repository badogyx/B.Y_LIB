/*
 *badog-yang
 * 静态数组类
 */
#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "Array.h"

namespace BYLib
{
    template < typename T, int N >
    class StaticArray : public Array<T>
    {
    protected:
        T m_space[N];

    public:
        StaticArray()
        {
            this->m_array = m_space;
        }

        //拷贝构造和赋值操作
        StaticArray(const StaticArray<T, N>& obj)
        {
            this->Array = m_space;

            for(int i = 0; i<N; i++)
            {
                m_space[i] = obj.m_space[i];
            }

        }

        StaticArray<T, N>& operator = (const StaticArray<T, N>& obj)
        {
            if(this != &obj)
            {

                for(int i = 0; i<N; i++)
                {
                    m_space[i] = obj.m_space[i];
                }

            }

            return *this;
        }

        int length() const         //返回数组长度
        {
            return N;
        }
    };
}


#endif // STATICARRAY_H
