add_library(Logging_test INTERFACE)

target_sources(Logging_test
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Log_test.cpp
)
target_link_libraries(Logging_test
  INTERFACE
    Logging::Logging
)
