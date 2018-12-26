#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "LinkList.h"
#include "Stack.h"

namespace BYLib
{
    template < typename T >
    class LinkStack : public Stack<T>
    {
    protected:
        LinkList<T> m_stack;
    public:
        void push(const T& e)
        {
            m_stack.insert(0,e);
        }

        void pop()
        {
            if( m_stack.length() > 0 )
            {
                m_stack.remove(0);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No element in current stack...");
            }
        }

        T top() const
        {
            if( m_stack.length() > 0 )
            {
                return m_stack.get(0);
            }
            else
            {
                THROW_EXCEPTION(InvalidOperationException, "No element in current stack...");
            }
        }

        void clear()
        {
            m_stack.clear();
        }

        int size() const
        {
            return m_stack.length();
        }
    };
}


#endif // LINKSTACK_H
