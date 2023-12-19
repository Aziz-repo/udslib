cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_COMPILER "/usr/bin/g++-11") # set the compiler to support c++20
                                          # features
project(
  libuds
  VERSION 1.0.0
  DESCRIPTION "ISO-14229 implementation"
  LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC src)
set(TEST test)
set(UDS uds)
set(PARSER config)
set(EXCEPTION exception)
set(EXTERNAL external)

set(EXTERNAL_LIBS_HEADERS ${EXTERNAL}/toml11/)

option(BUILD_DOC "Build documentation" OFF)
option(BUILD_TEST "Build the test suit" OFF)

include_directories(${UDS}/inc)
include_directories(${PARSER}/inc)
include_directories(${EXCEPTION}/inc)

file(GLOB uds ${UDS}/${SRC}/*.cpp)
file(GLOB config ${PARSER}/${SRC}/*.cpp)
file(GLOB testFiles ${TEST}/*.cpp)
file(GLOB exception ${EXCEPTION}/*.h)

add_executable(${PROJECT_NAME} main.cpp ${config} ${uds} ${exception})
target_include_directories(${PROJECT_NAME} PRIVATE ${EXTERNAL_LIBS_HEADERS})
target_link_options(${PROJECT_NAME} PUBLIC -std=c++20 -Wall)

include(cmake/UpdateSubmodules.cmake)

if(BUILD_TEST)
  if(BUILD_TESTING)
    include(cmake/GenerateTests.cmake)
  endif()
endif()

if(BUILD_DOC)
  include(cmake/GenerateDocs.cmake)
endif()
