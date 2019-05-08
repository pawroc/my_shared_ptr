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
      ++(*ref_count);
   }

   ~shared_ptr()
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