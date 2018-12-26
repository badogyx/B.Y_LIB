/*
 *badog-yang
 * 顺序表
 */
#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"

namespace BYLib
{
    template < typename T >
    class SeqList : public List<T>
    {
    protected:
        T* m_array;           //顺序存储空间
        int m_length;         //当前线性表长度

    public:
        bool insert(int i, const T& e)    //插入数据
        {
            bool ret = ( (0 <= i) && (i <= m_length) );

            ret = ret && (m_length < capacity());

            if(ret)
            {
                for(int p = m_length-1; p >= i; p--)
                {
                    m_array[p + 1] = m_array[p];
                }
                m_array[i] = e;
                m_length++;
            }
            return ret;
        }

        bool insert(const T& e)
        {
            return (insert(m_length, e));
        }

        bool remove(int i)         //删除数据
        {
            bool ret = ( (0 <= i) && (i < m_length) );

            if(ret)
            {
                for(int p = i; p < m_length; p++)
                {
                    m_array[p] = m_array[p+1];
                }
                m_length--;
            }

            return ret;
        }

        bool set(int i, const T& e)    //设置指定数据的值
        {
            bool ret = ( (0 <= i) && (i < m_length) );

            if(ret)
            {
                m_array[i] = e;
            }

            return ret;
        }

        bool get(int i, T& e) const    //得到指定数据的值，得到为真，否则为假.得到的值在e里面
        {
             bool ret = ( (0 <= i) && (i < m_length) );

             if(ret)
             {
                 e = m_array[i];
             }

             return ret;
        }

        int find(const T& e) const
        {
            int ret = -1;
            for(int i = 0; i < m_length; i++)
            {
                if(m_array == e)
                {
                    ret = i;
                    break;
                }
            }
            return ret;
        }

        int length() const         //返回线性表长度
        {
            return m_length;
        }

        void clear()             //清空线性表
        {
            m_length = 0;
        }

        //顺序存储线性表的访问方式
        T& operator[] (int i)
        {
            if( (0 <= i) && (i < m_length) )
            {
                return m_array[i];
            }
            else
            {
                THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
            }
        }

        T operator [](int i) const
        {
            return (const_cast< SeqList<T>& >(*this))[i];
        }

        //顺序空间的容量
        virtual int capacity() const = 0;
    };
}


#endif // SEQLIST_H
