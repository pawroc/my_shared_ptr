cmake_minimum_required(VERSION 3.14.0)

include(cmake/variableDefinitions.cmake)
include(cmake/HunterGate.cmake)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.135.tar.gz"
    SHA1 "72eecdf1dea9fb6299d7fb61bbd00bd4ca170fa4"
)

project(shared_ptr LANGUAGES C CXX)

add_library(shared_ptr INTERFACE)
add_library(my::shared_ptr ALIAS shared_ptr)

target_include_directories(shared_ptr
INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:my_shared_ptr>
)

enable_testing()

add_subdirectory(tests)
