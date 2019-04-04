#include <gtest/gtest.h>

#include "shared_ptr.hpp"

namespace ut
{
namespace shared_ptr
{
TEST(Constructor, constructFromPointer) 
{
    EXPECT_EQ(true, true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
} // shared_ptr
} // ut