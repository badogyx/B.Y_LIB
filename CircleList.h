/*
 *badog-yang
 *循环链表
 */
#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include"LinkList.h"

namespace BYLib
{
    template < typename T >
    class CircleList : public LinkList<T>
    {
    protected:
        typedef typename LinkList<T>::Node Node;
        Node* last()
        {
            return this->position(this->m_length-1)->next;
        }

        void last_to_first()
        {
            last()->next = this->m_header.next;
        }

        int mod(int i) const
        {
            return (this->m_length == 0) ? 0 : (i % this->m_length);
        }

    public:
        bool insert(const T& e)
        {
            return insert(this->m_length, e);
        }

        bool insert(int i, const T& e)
        {
            bool ret = true;

            i = i % (this->m_length + 1);

            ret = LinkList<T>::insert(i, e);

            if( ret && (i == 0) )
            {
                last_to_first();
            }

            return ret;
        }

        bool remove(int i)
        {
            bool ret = true;

            i = mod(i);

            if(i == 0)
            {
                Node* toDel = this->m_header.next;
                if( toDel != NULL )
                {
                    this->m_header.next = toDel->next;
                    this->m_length--;

                    if(this->m_length > 0)
                    {
                        last_to_first();

                        if(this->m_current == toDel)
                        {
                            this->m_current = toDel->next;
                        }
                    }
                    else
                    {
                        this->m_header.next = NULL;
                        this->m_current = NULL;
                    }
                    LinkList<T>::destroy(toDel);
                }
                else
                {
                    ret = false;
                }
            }
            else
            {
                ret = LinkList<T>::remove(i);
            }

            return ret;
        }

        bool set(int i, const T& e)
        {
            return LinkList<T>::set(mod(i), e);
        }

        T get(int i) const
        {
            return LinkList<T>::get(mod(i));
        }

        bool get(int i, const T& e) const
        {
            return LinkList<T>::get(mod(i), e);
        }

        int find(const T& e) const
        {
            int ret = -1;

            Node* silder = this->m_header.next;

            for(int i = 0; i < this->m_length; i++)
            {
                if( silder->value == e )
                {
                    ret = i;
                    break;
                }
                silder = silder->next;
            }

            return ret;
        }

        void clear()
        {
            while( this->m_length > 1 )
            {
                remove(1);
            }
            if( this->m_length == 1 )
            {
                Node* toDel = this->m_header.next;

                this->m_header.next = NULL;
                this->m_current = NULL;
                this->m_length = 0;

                this->destroy(toDel);
            }
        }

        bool move(int i, int step)
        {
            return LinkList<T>::move(mod(i), step);
        }

        bool end()
        {
            return ( (this->m_length == 0) || (this->m_current == NULL) );
        }

        ~CircleList()
        {
            clear();
        }

    };

}

#endif // CIRCLELIST_H
