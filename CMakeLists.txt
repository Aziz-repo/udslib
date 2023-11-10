cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-11") # set the compiler to support c++20 features
project(udslib
    VERSION 1.0.0
    DESCRIPTION "ISO-14229 implementation"
    LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SRC src)
set(TEST test)

include_directories(inc)
include_directories(SYSTEM /usr/include/c++/${CMAKE_CXX_COMPILER_VERSION})

file(GLOB uds ${SRC}/*.cpp)
file(GLOB testFiles ${TEST}/*.cpp)

add_executable(${PROJECT_NAME}  main.cpp ${uds})
target_link_options(${PROJECT_NAME} PUBLIC -std=c++20 -Wall)
include(CTest)
add_subdirectory(external)

if(BUILD_TESTING)
  add_executable(example ${testFiles})
  target_link_libraries(example PRIVATE GTest::gtest_main)
  
  include(GoogleTest)
  gtest_discover_tests(example)
endif()
