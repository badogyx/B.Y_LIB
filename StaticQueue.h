#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "Queue.h"
#include "Exception.h"
#include <iostream>
using namespace std;

namespace BYLib
{
    template < typename T, int N >
    class StaticQueue : public Queue<T>
    {
    protected:
        T m_space[N];    //队列储存空间
        int m_front;     //队头标识
        int m_rear;      //队尾标识
        int m_length;    //队列长度
    public:
        StaticQueue()
        {
            m_front = 0;
            m_rear = 0;
            m_length = 0;
        }

        int capacity() const
        {
            return N;
        }

        void add(const T& e)
        {
            if( m_length < N )
            {
                m_space[m_rear] = e;
                m_rear = (m_rear+1) % N;
                m_length++;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No space in current queue...");
            }
        }

        void remove()
        {
            if( m_length > 0 )
            {
                m_front = (m_front + 1) % N;
                m_length--;
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No element in current queue...");
            }
        }

        T front() const
        {
            if( m_length > 0 )
            {
                return m_space[m_front];
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No element in current queue...");
            }
        }

        void clear()
        {
            m_length = 0;
            m_front = 0;
            m_rear = 0;
        }

        int length() const
        {
            return m_length;
        }
    };
}

#endif // STATICQUEUE_H
