include(CTest)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external)
add_executable(test_suit ${testFiles} ${uds})
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CleanTests.cmake)
target_link_libraries(test_suit PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(test_suit)
