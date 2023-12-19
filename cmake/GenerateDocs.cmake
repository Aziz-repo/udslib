# Adapted from https://vicrucann.github.io/tutorials/quick-cmake-doxygen/

# TODO: fix this bs
find_package(Doxygen)
if(DOXYGEN_FOUND)
  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  message(STATUS "Doxygen build started")

  add_custom_command(
    OUTPUT remove_doc
    COMMAND ${CMAKE_COMMAND} -E remove_directory doc/
    VERBATIM)

  file(GLOB generated_files ${CMAKE_CURRENT_BINARY_DIR}/doc/*)
  add_custom_command(
    OUTPUT clean_doc
    COMMAND rm -rf ${generated_files} Doxyfile CMakeDoxyfile.in
            CMakeDoxygenDefaults.cmake
    VERBATIM)

  add_custom_command(OUTPUT doc_dir COMMAND ${CMAKE_COMMAND} -E make_directory
                                            doc)

  add_custom_target(
    doc
    DEPENDS doc_dir
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT} MAIN_DEPENDENCY ${DOXYGEN_OUT}
            ${DOXYGEN_IN}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM)

  add_custom_target(
    doc_clean
    DEPENDS remove_doc clean_doc
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Cleaning docs"
    VERBATIM)
else(DOXYGEN_FOUND)
  message(ERROR "Doxgen need to be installed to generate doxygen documentation")
endif(DOXYGEN_FOUND)
