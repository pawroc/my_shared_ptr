cmake_minimum_required(VERSION 3.14.0)
project(tests LANGUAGES C CXX)

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
find_package(GMock CONFIG REQUIRED)

set(SOURCES testConstructors.cpp)

# Do not append STATIC / SHARED specifier unless you really know what you do
# Use -DBUILD_SHARED_LIBS=ON/OFF instead of this ugly way
add_executable(ut_constructors ${SOURCES})
target_include_directories(ut_constructors PUBLIC ${GTEST_INCLUDE_DIR})

# GMock::gmock and GTest::main will be linked automatically
target_link_libraries(ut_constructors GMock::main my::shared_ptr)

add_test(NAME testConstructors
         COMMAND ut_constructors
)