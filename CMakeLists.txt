cmake_minimum_required(VERSION 3.16)
project(udslib)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-11") # set the compiler to support c++20 features
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SRC src)


include_directories(inc)
include_directories(SYSTEM /usr/include/c++/${CMAKE_CXX_COMPILER_VERSION})

file(GLOB uds ${SRC}/*.cpp)

add_executable(${PROJECT_NAME}  main.cpp ${uds})
target_link_options(${PROJECT_NAME} PUBLIC -std=c++20 -Wall)
