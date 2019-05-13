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
   Foo(const Foo&) { std::cout << "Foo() copy ctor\n"; }
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

TEST(SharedPtr, constructor_twoSharedPointers_shouldHaveOneRefCount) 
{
   std::shared_ptr<Foo> origSharedPtr1(new Foo);
   std::shared_ptr<Foo> origSharedPtr2(new Foo);
   EXPECT_EQ(origSharedPtr1.use_count(), 1);
   EXPECT_EQ(origSharedPtr2.use_count(), 1);

   my::shared_ptr::shared_ptr<Foo> mySharedPtr1(new Foo);
   my::shared_ptr::shared_ptr<Foo> mySharedPtr2(new Foo);

   EXPECT_EQ(mySharedPtr1.use_count(), 1);
   EXPECT_EQ(mySharedPtr2.use_count(), 1);
}

TEST(SharedPtr, copyContructor_newInstance_RefCountShouldBeTwo) 
{
   std::shared_ptr<Foo> origSharedPtr(new Foo);
   std::shared_ptr<Foo> origSharedPtr2 = origSharedPtr;
   EXPECT_EQ(origSharedPtr.use_count(), 2);
   EXPECT_EQ(origSharedPtr2.use_count(), 2);

   my::shared_ptr::shared_ptr<Foo> mySharedPtr(new Foo);
   my::shared_ptr::shared_ptr<Foo> mySharedPtr2 = mySharedPtr;

   EXPECT_EQ(mySharedPtr.use_count(), 2);
   EXPECT_EQ(mySharedPtr2.use_count(), 2);
}

TEST(SharedPtr, destructor_afterDeletionOfOneCopy_useCountShouldBeDerceased) 
{
    std::shared_ptr<Foo> origSharedPtr(new Foo);
    // Local scope
    {
        std::shared_ptr<Foo> origSharedPtr2 = origSharedPtr;
        EXPECT_EQ(origSharedPtr.use_count(), 2);
        EXPECT_EQ(origSharedPtr2.use_count(), 2);
    }
    EXPECT_EQ(origSharedPtr.use_count(), 1);

    my::shared_ptr::shared_ptr<Foo> mySharedPtr(new Foo);
    // Local scope
    {
        my::shared_ptr::shared_ptr<Foo> mySharedPtr2 = mySharedPtr;
        EXPECT_EQ(mySharedPtr.use_count(), 2);
        EXPECT_EQ(mySharedPtr2.use_count(), 2);
    }
    EXPECT_EQ(mySharedPtr.use_count(), 1);
}

TEST(SharedPtr, assignmentOperator) 
{
   std::shared_ptr<Foo> origSharedPtr(new Foo);
   std::shared_ptr<Foo> origSharedPtr2 = origSharedPtr;
   std::shared_ptr<Foo> origSharedPtr3(new Foo);

    origSharedPtr3 = origSharedPtr;
    EXPECT_EQ(origSharedPtr3.use_count(), origSharedPtr.use_count());
    EXPECT_EQ(origSharedPtr3.use_count(), 3);

   my::shared_ptr::shared_ptr<Foo> mySharedPtr(new Foo);
   my::shared_ptr::shared_ptr<Foo> mySharedPtr2 = mySharedPtr;
   my::shared_ptr::shared_ptr<Foo> mySharedPtr3(new Foo);

    mySharedPtr3 = mySharedPtr;
    EXPECT_EQ(mySharedPtr3.use_count(), mySharedPtr.use_count());
    EXPECT_EQ(mySharedPtr3.use_count(), 3);
}


int main(int argc, char **argv) {
   ::testing::InitGoogleTest(&argc, argv); 
   return RUN_ALL_TESTS();
}
} // shared_ptr
} // ut