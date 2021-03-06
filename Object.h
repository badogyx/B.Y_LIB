/*
 *badog-yang
 * 顶层父类
 */
#ifndef OBJECT_H
#define OBJECT_H

#include <cstddef>

namespace BYLib 
{
    class Object
    {
    public:
        void* operator new(size_t size) throw();
        void operator delete(void* p);
        void* operator new[](size_t size) throw();
        void operator delete[](void* p);
        bool operator ==(const Object& obj);
        bool operator !=(const Object& obj);
        virtual ~Object() = 0;
    };
}

#endif // OBJECT_H
