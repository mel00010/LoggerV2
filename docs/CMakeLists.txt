include(DoxygenTargets)
set(EXTRA_SOURCE_DIRS ${PROJECT_SOURCE_DIR}/samples)
configure_file(Doxyfile.in Doxyfile @ONLY)
add_doxygen(${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/docs-generated/man/man3 DESTINATION /usr/local/man)