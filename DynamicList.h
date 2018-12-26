/*
 *badog-yang
 * 动态单链表
 */
#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "SeqList.h"

namespace BYLib
{

    template < typename T >
    class DynamicList : public SeqList<T>
    {
    protected:
        int m_capacity;            //顺序储存空间大小
    public:
        DynamicList(int capacity)   //申请空间
        {
            this->m_array = new T[capacity];
            if(this->m_array != NULL)
            {
                this->m_length = 0;
                this->m_capacity = capacity;
            }
            else
            {
                THROW_EXCEPTION(NOEnoughMemoryException, "no memory to create dynamic object...");
            }
        }

        int capacity() const
        {
            return m_capacity;
        }

        void resize(int capacity)   //重新设置储存空间大小
        {
            T* array = new T[capacity];
            if(array != NULL)
            {
                int length = (this->m_length < capacity ? this->m_length : capacity);
                for(int i=0; i<length; i++)
                {
                    array[i] = this->m_array[i];
                }

                T* temp = this->m_array;

                this->m_array = array;
                this->m_capacity = capacity;
                this->m_length = length;

                delete[] temp;
            }
            else
            {
                THROW_EXCEPTION(NOEnoughMemoryException, "no memory to resize dynamic object...");
            }
        }

        ~DynamicList()
        {
            delete[] this->m_array;
        }
    };

}

#endif // DYNAMICLIST_H
