# Adapted from https://vicrucann.github.io/tutorials/quick-cmake-doxygen/

find_package(Doxygen)
if (DOXYGEN_FOUND)
  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_BINARY_DIR}/Doxyfile)

  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  message(STATUS "Doxygen build started")

  add_custom_target(doc ALL
    COMMAND ${DOXYGEN_EXCUTABLE} ${DOXYGEN_IN}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM 
  )
else (DOXYGEN_FOUND)
  message(ERROR "Doxgen need to be installed to generate doxygen documentation")
endif (DOXYGEN_FOUND)
