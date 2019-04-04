// http://www.openguru.com/2015/07/a-simple-sharedptr-implementation-in-c.html
#pragma once

#include <iostream>

namespace my
{
namespace shared_ptr
{
template <class T>
class shared_ptr final
{
using ref_cout = size_t*;

public:
    shared_ptr(T* ptr)
    {
        if (use_count == nullptr)
        {
            std::cout << "Creating first shared_ptr\n";
            pointee = ptr;
            use_count = new size_t;
            *use_count = 1;
        }
        else
        {
            ++(*use_count);
            std::cout << "Creating another shared_ptr. use_count = " << *use_count << '\n';
        }
    }

    ~shared_ptr()
    {
        std::cout << "Destroying [" << *use_count << "] object.\n"; 
        --(*use_count);
        if (*use_count == 0)
        {
            std::cout << "Destroying last shared_ptr.\n ";
            delete use_count;
            use_count = nullptr;

            delete pointee;
            pointee = nullptr;
        }
    }

private:
    T* pointee{nullptr};
    ref_cout use_count{nullptr}; 
};
} // namespace shared_ptr
} // namespace my