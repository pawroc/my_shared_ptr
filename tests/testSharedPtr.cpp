#include <gtest/gtest.h>

#include "shared_ptr.hpp"
#include <memory>

namespace ut
{
namespace shared_ptr
{
namespace // anonymous
{
struct Foo
{
   Foo() { std::cout << "Foo() ctor\n"; }
   ~Foo() { std::cout << "\t~Foo() dtor\n"; }
};
} // anonymous namespace

TEST(SharedPtr, basicConstructor_shouldContainOneReferenceCount) 
{
   std::shared_ptr<Foo> origSharedPtr(new Foo);
   my::shared_ptr::shared_ptr<Foo> mySharedPtr(new Foo);
   EXPECT_EQ(origSharedPtr.use_count(), 1);
   EXPECT_EQ(mySharedPtr.use_count(), 1);
}

TEST(SharedPtr, copyContructor_newInstanceRefCountShouldBeTwo) 
{
   std::shared_ptr<Foo> origSharedPtr(new Foo);
   std::shared_ptr<Foo> origSharedPtr2 = origSharedPtr;
   EXPECT_EQ(origSharedPtr.use_count(), 2);
   EXPECT_EQ(origSharedPtr2.use_count(), 2);

   my::shared_ptr::shared_ptr<Foo> mySharedPtr(new Foo);
   my::shared_ptr::shared_ptr<Foo> mySharedPtr2 = mySharedPtr;

   EXPECT_EQ(origSharedPtr.use_count(), 1);
   EXPECT_EQ(origSharedPtr2.use_count(), 1);
}

int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv); 
   return RUN_ALL_TESTS();
}
} // shared_ptr
} // ut