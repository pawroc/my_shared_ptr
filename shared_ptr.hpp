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
public:
   explicit shared_ptr(T* ptr) try
    : pointee(ptr)
    , ref_count(new size_t(1))
   {
   }
   catch (std::bad_alloc)
   {
       delete ptr;
       throw;
   }

   shared_ptr(const shared_ptr& orig)
    : pointee(orig.pointee)
    , ref_count(orig.ref_count)
   {
      if (ref_count != nullptr)
      {
        ++(*ref_count);
      }
   }

   shared_ptr& operator=(shared_ptr orig) // make implicite copy
   {
       swap(*this, orig);
       return *this;
   }

   ~shared_ptr()
   {
       destroy();
   }

   size_t use_count() const
   {
      return *ref_count;
   }

    friend void swap(shared_ptr& lhs, shared_ptr& rhs)
    {
        using std::swap; // enable ADL

        swap(lhs.pointee, rhs.pointee);
        swap(lhs.ref_count, rhs.ref_count);
    }

private:
    void destroy()
    {
       if (ref_count)
       {
            --(*ref_count);
            if (*ref_count == 0)
            {
                delete ref_count;
                ref_count = nullptr;

                delete pointee;
                pointee = nullptr;
            }
       }
    }

   T* pointee{nullptr};
   size_t* ref_count{nullptr};
};
} // namespace shared_ptr
} // namespace my