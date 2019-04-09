cmake_minimum_required(VERSION 3.14.0)
project(tests LANGUAGES C CXX)

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
find_package(GMock CONFIG REQUIRED)

set(SOURCES testSharedPtr.cpp)

# Do not append STATIC / SHARED specifier unless you really know what you do
# Use -DBUILD_SHARED_LIBS=ON/OFF instead of this ugly way
add_executable(ut_shared_ptr ${SOURCES})
target_include_directories(ut_shared_ptr PUBLIC ${GTEST_INCLUDE_DIR})

# GMock::gmock and GTest::main will be linked automatically
target_link_libraries(ut_shared_ptr GMock::main my::shared_ptr)
add_definitions(-DCTEST_OUTPUT_ON_FAILURE=1)

add_test(NAME test_shared_ptr
         COMMAND ut_shared_ptr
)