add_library(Logging_Logging STATIC "")
add_library(Logging::Logging ALIAS Logging_Logging)

target_sources(Logging_Logging
  PRIVATE
    Client.cpp
    Flags.cpp
    Log.cpp
    Telemetry.cpp
    SendTrace.inc
    LogMetaMetaFuncs.inc
    LogMetaFuncs.inc
    LogFuncs.inc
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Client.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CustomSourceLocation.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Flags.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Log.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/str_const.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Telemetry.hpp
)
if(not DEFINED DISABLE_PCH)
    target_precompile_headers(Logging_Logging
      PUBLIC
        "Client.hpp"
        "CustomSourceLocation.hpp"
        "Flags.hpp"
        "Log.hpp"
        "Telemetry.hpp"
        "str_const.hpp"
    )
endif()
target_include_directories(Logging_Logging
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../
)

target_link_libraries(Logging_Logging
  PUBLIC
    p7
    fmt::fmt
    absl::flags
    absl::flags_usage
    absl::flags_parse
    absl::strings
)