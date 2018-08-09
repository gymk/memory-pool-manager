#ifndef __CUSTOM_NEW_DELETE_HPP__
    #define __CUSTOM_NEW_DELETE_HPP__

#include <iostream>
#include <cstdlib>

#ifdef ENABLE_CUSTOM_NEW_DELETE_OVERRIDE
void* operator new(std::size_t t)
{
    void * p = malloc(t);

    std::cout << "\tAlloc(" << t << ',' << p << ")\n";
    return p;
}

void operator delete(void * p)
{
    std::cout << "\tDealloc(" << p << ")\n";
    free(p);
}

void* operator new[](std::size_t t)
{
    void * p = malloc(t);

    std::cout << "\tAlloc[](" << t << ',' << p << ")\n";
    return p;
}

void operator delete[](void * p)
{
    std::cout << "\tDealloc[](" << p << ")\n";
    free(p);
}
#endif /* ENABLE_CUSTOM_NEW_DELETE_OVERRIDE */

#endif /* !__CUSTOM_NEW_DELETE_HPP__ */