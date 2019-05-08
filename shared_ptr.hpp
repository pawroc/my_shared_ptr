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
   explicit shared_ptr(T* ptr)
   {
      if (ref_count == nullptr)
      {
         pointee = ptr;
         try
         {
            ref_count = new size_t(1);
         }
         catch(std::bad_alloc)
         {
            delete ref_count;
            throw; // rethrow std::bad_alloc further
         }
      }
   }

   shared_ptr(const shared_ptr& orig)
   {
      if (this == &orig)
      {
          return;
      }
      pointee = orig.pointee;
      ref_count = orig.ref_count;
      if (ref_count != nullptr)
      {
        ++(*ref_count);
      }
   }

   shared_ptr& operator=(const shared_ptr& orig)
   {
       if (this == &orig)
       {
           return *this;
       }

       if (ref_count)
       {
           if (*ref_count > 1)
           {
               --(*ref_count);
           }
           else
           {
               delete ref_count;
               ref_count = nullptr;

               delete pointee;
               pointee = nullptr;
           }
       }

       ref_count = orig.ref_count;
       pointee = orig.pointee;
       ++(*ref_count);

       return *this;
   }

   ~shared_ptr()
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

   size_t use_count() const
   {
      return *ref_count;
   }

private:
   T* pointee{nullptr};
   size_t* ref_count{nullptr}; 
};
} // namespace shared_ptr
} // namespace my