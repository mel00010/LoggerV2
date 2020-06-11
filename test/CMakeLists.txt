include(GetGoogleTest)

if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
  # coverage target setup
  include(CodeCoverage)
  append_coverage_compiler_flags()
  set(COVERAGE_EXCLUDES
    '${PROJECT_SOURCE_DIR}/test/*'
    '/usr/include/c++/6/*'
    '/usr/include/c++/7/*'
    '/usr/include/c++/8/*'
    '/usr/local/include/boost/*'
  )
  setup_target_for_coverage(NAME coverage EXECUTABLE test/tests DEPENDENCIES tests)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_executable(tests "")

else()
  add_executable(tests "")
endif()
target_sources(tests
  PRIVATE
    main_test.cpp
)

target_include_directories(tests
  PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)
if(NOT DEFINED DISABLE_PCH)
    target_precompile_headers(tests REUSE_FROM Logging::Logging)
endif()

set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
message("$ENV{LD_LIBRARY_PATH}")
target_link_libraries(tests
  Logging_test

  # $<TARGET_FILE> is used to prevent shared linking of gtest
  gtest
  gmock
  gmock_main
  pthread
)
add_subdirectory(Logging)