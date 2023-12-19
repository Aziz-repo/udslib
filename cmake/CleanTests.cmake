file(GLOB test_files ${CMAKE_CURRENT_BINARY_DIR}/test_suit*)

add_custom_command(
  OUTPUT clean_test COMMAND ${CMAKE_COMMAND} -E remove -f CTestTestfile.cmake
                            DartConfiguration.tcl ${test_files})

add_custom_command(OUTPUT clean_test_dir COMMAND ${CMAKE_COMMAND} -E
                                                 remove_directory Testing)

add_custom_target(
  test_clean
  DEPENDS clean_test clean_test_dir
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  VERBATIM)
