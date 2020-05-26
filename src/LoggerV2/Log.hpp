/******************************************************************************
 * Log.hpp
 * Copyright (C) 2020  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of LoggerV2.
 *
 * LoggerV2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LoggerV2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LoggerV2.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/
#ifndef SRC_LOGGERV2_LOG_HPP_
#define SRC_LOGGERV2_LOG_HPP_

#include <cstdarg>
#include <cstddef>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <utility>

#include <boost/predef.h>
#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

#include "LoggerV2/CustomSourceLocation.hpp"
#include "LoggerV2/source_location.h"
#include "LoggerV2/str_const.hpp"
#include "P7_Trace.h"

#if __has_include(<glm/gtx/io.hpp>)
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/io.hpp>
#endif /* __has_include(<glm/gtx/io.hpp>) */

namespace logging {

#ifndef LOG_func_max_args
#define LOG_func_max_args 5  // default maximum size is 5
#endif                       /* LOG_func_max_args */

enum class Level : std::uint8_t {
  TRACE = EP7TRACE_LEVEL_TRACE,
  DEBUG = EP7TRACE_LEVEL_DEBUG,
  INFO = EP7TRACE_LEVEL_INFO,
  WARNING = EP7TRACE_LEVEL_WARNING,
  ERROR = EP7TRACE_LEVEL_ERROR,
  CRITICAL = EP7TRACE_LEVEL_CRITICAL,
  COUNT = EP7TRACE_LEVEL_COUNT
};

inline constexpr eP7Trace_Level convert(const Level level) {
  switch (level) {
    case Level::TRACE:
      return EP7TRACE_LEVEL_TRACE;
    case Level::DEBUG:
      return EP7TRACE_LEVEL_DEBUG;
    case Level::INFO:
      return EP7TRACE_LEVEL_INFO;
    case Level::WARNING:
      return EP7TRACE_LEVEL_WARNING;
    case Level::ERROR:
      return EP7TRACE_LEVEL_ERROR;
    case Level::CRITICAL:
      return EP7TRACE_LEVEL_CRITICAL;
    case Level::COUNT:
      return EP7TRACE_LEVEL_COUNT;
  }
  return EP7TRACE_LEVEL_TRACE;
}

inline constexpr Level convert(const eP7Trace_Level level) {
  switch (level) {
    case EP7TRACE_LEVEL_TRACE:
      return Level::TRACE;
    case EP7TRACE_LEVEL_DEBUG:
      return Level::DEBUG;
    case EP7TRACE_LEVEL_INFO:
      return Level::INFO;
    case EP7TRACE_LEVEL_WARNING:
      return Level::WARNING;
    case EP7TRACE_LEVEL_ERROR:
      return Level::ERROR;
    case EP7TRACE_LEVEL_CRITICAL:
      return Level::CRITICAL;
    case EP7TRACE_LEVEL_COUNT:
      return Level::COUNT;
  }
  return Level::TRACE;
}

struct ModuleHandle {
  std::string name;
  IP7_Trace::hModule module;
};

class Log {
 public:
  Log() noexcept = default;
  Log& operator=(const Log& rhs) = default;
  Log(const Log& rhs) = default;
  Log& operator=(Log& rhs) noexcept = default;
  Log(Log& rhs) noexcept = default;

  explicit Log(const std::string name);
  ~Log() noexcept;

  void swap(Log& other) noexcept {
    using std::swap;
    swap(other.trace_, trace_);
  }

 private:
  using sl = std::source_location;

 public:
  inline IP7_Trace* get_trace() const { return trace_; }

  /**
   * @brief Registers a thread with a name for nice log output
   *
   * @param name Name to associate with thread
   * @param thread_id ID of thread.  If id == 0, then the current
   * thread will be used.
   * @return Returns true on success, false on failure.
   */
  inline bool RegisterThread(const std::string& name,
                             const std::uint32_t thread_id = 0) const {
    return trace_->Register_Thread(name.c_str(), thread_id);
  }
  /**
   * @brief Unregisters a thread
   *
   * @param thread_id ID of thread to unregister. If id == 0,
   * then the current thread will be used.
   * @return Returns true on success, false on failure.
   */
  inline bool UnregisterThread(const std::uint32_t thread_id = 0) const {
    return trace_->Unregister_Thread(thread_id);
  }

  /**
   * @brief Registers a module with a name and creates a module
   * handle
   *
   * @param name Module name
   * @return Returns a module handle if successfully created
   */
  inline std::optional<ModuleHandle> RegisterModule(
      const std::string& name) const {
    ModuleHandle handle{};
    handle.name = name;
    return (trace_->Register_Module(name.c_str(), &(handle.module))
                ? std::optional<ModuleHandle>(handle)
                : std::nullopt);
  }

  inline void SetVerbosity(const Level level) const {
    SetVerbosity(ModuleHandle{"", nullptr}, level);
  }
  inline void SetVerbosity(const ModuleHandle& handle,
                           const Level level) const {
    trace_->Set_Verbosity(handle.module, convert(level));
  }
  inline Level GetVerbosity() const {
    return GetVerbosity(ModuleHandle{"", nullptr});
  }
  inline Level GetVerbosity(const ModuleHandle& handle) const {
    return convert(trace_->Get_Verbosity(handle.module));
  }

  template <typename... Args>
  void RawTrace(const Level level, const std::uint16_t id,
                const ModuleHandle& handle, const CustomSourceLocation loc,
                const std::string& format, const Args... all) const {
    if (!trace_->Trace_Managed(
            id, convert(level), handle.module, loc.line(), loc.file_name(),
            loc.function_name(),
            fmt::format(format, std::forward<const Args>(all)...).c_str())) {
      std::cerr << "P7 Trace_Managed returned false!" << std::endl;
    }
  }

 public:
  /* If non-type template parameters of user-defined type are permitted, use
   * them so that we may pass unlimited arguments to the Log functions.
   * Otherwise, use the old preprocessor metaprogramming.
   */
//#if (BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(9, 0, 0)) || \
//    defined(__IN_ECLIPSE_PARSER__)
#if defined(__IN_ECLIPSE_PARSER__)
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void SendTrace(const Level level, const ModuleHandle& handle,
                 const std::string& format, const Args... all) const {
    RawTrace(std::forward<const Level>(level), 0,
             std::forward<const ModuleHandle&>(handle),
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Trace(const std::string& format, const Args... all) const {
    RawTrace(Level::TRACE, 0, ModuleHandle{},
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Trace(const ModuleHandle& handle, const std::string& format,
             const Args... all) const {
    RawTrace(Level::TRACE, 0, std::forward<const ModuleHandle&>(handle),
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Debug(const std::string&& format, const Args... all) const {
    RawTrace(Level::DEBUG, 0, ModuleHandle{},
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Debug(const ModuleHandle& handle, const std::string& format,
             const Args... all) const {
    RawTrace(Level::DEBUG, 0, std::forward<const ModuleHandle&>(handle),
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Info(const std::string& format, const Args... all) const {
    RawTrace(Level::INFO, 0, ModuleHandle{},
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Info(const ModuleHandle& handle, const std::string& format,
            const Args... all) const {
    RawTrace(Level::INFO, 0, std::forward<const ModuleHandle&>(handle),
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }

  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Warn(const std::string& format, const Args... all) const {
    RawTrace(Level::WARNING, 0, ModuleHandle{},
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Warn(const ModuleHandle& handle, const std::string& format,
            const Args... all) const {
    RawTrace(Level::WARNING, 0, std::forward<const ModuleHandle&>(handle),
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Warning(const std::string& format, const Args... all) const {
    RawTrace(Level::WARNING, 0, ModuleHandle{},
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Warning(const ModuleHandle& handle, const std::string& format,
               const Args... all) const {
    RawTrace(Level::WARNING, 0, std::forward<const ModuleHandle&>(handle),
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }

  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Error(const std::string& format, const Args... all) const {
    RawTrace(Level::ERROR, 0, ModuleHandle{},
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Error(const ModuleHandle& handle, const std::string& format,
             const Args... all) const {
    RawTrace(Level::ERROR, 0, std::forward<const ModuleHandle&>(handle),
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Critical(const std::string& format, const Args... all) const {
    RawTrace(Level::CRITICAL, 0, ModuleHandle{},
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Critical(const ModuleHandle& handle, const std::string& format,
                const Args... all) const {
    RawTrace(Level::CRITICAL, 0, std::forward<const ModuleHandle&>(handle),
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Crit(const std::string& format, const Args... all) const {
    RawTrace(Level::CRITICAL, 0, ModuleHandle{},
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Crit(const ModuleHandle& handle, const std::string& format,
            const Args... all) const {
    RawTrace(Level::CRITICAL, 0, std::forward<const ModuleHandle&>(handle),
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Count(const std::string& format, const Args... all) const {
    RawTrace(Level::COUNT, 0, ModuleHandle{},
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
  template <typename... Args,
            str_const file_name = str_const(sl::current().file_name()),
            str_const function_name = str_const(sl::current().function_name()),
            std::uint_least32_t line = sl::current().line(),
            std::uint_least32_t column = sl::current().column()>
  void Count(const ModuleHandle& handle, const std::string& format,
             const Args... all) const {
    RawTrace(Level::COUNT, 0, std::forward<const ModuleHandle&>(handle),
             CustomSourceLocation{file_name, function_name, line, column},
             std::forward<const std::string&>(format),
             std::forward<const Args>(all)...);
  }
#else /* BOOST_COMP_GNUC <= BOOST_VERSION_NUMBER(9, 0, 0) */
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/logical/and.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/logical/or.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/punctuation/paren.hpp>
#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/seq/cat.hpp>
#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/preprocessor/slot/slot.hpp>
#include <boost/preprocessor/variadic/to_seq.hpp>

#ifndef TRUE
#define TRUE 1
#endif  // TRUE
#ifndef FALSE
#define FALSE 0
#endif  // FALSE

#define LOG_func_names                                                       \
  (10, (SendTrace, Trace, Debug, Info, Warn, Warning, Error, Critical, Crit, \
        Count))
#define LOG_funcs_level_p_enabled \
  (10, (TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE))
#define LOG_funcs_level_value                                           \
  (10, (NULL, Level::TRACE, Level::DEBUG, Level::INFO, Level::WARNING,  \
        Level::WARNING, Level::ERROR, Level::CRITICAL, Level::CRITICAL, \
        Level::COUNT))

#define LOG_function_max_iter 10
#define BOOST_PP_ITERATION_LIMITS (0, LOG_function_max_iter - 1)
#define BOOST_PP_FILENAME_1 "LoggerV2/LogMetaMetaFuncs.inc"

#ifndef __IN_ECLIPSE_PARSER__
#include BOOST_PP_ITERATE()
#endif /* __IN_ECLIPSE_PARSER__ */
#undef BOOST_PP_ITERATION_LIMITS
#undef BOOST_PP_FILENAME_1
#undef LOG_func_names
#undef LOG_funcs_level_p_enabled
#undef LOG_funcs_level_value

#endif /* BOOST_COMP_GNUC >= BOOST_VERSION_NUMBER(9, 0, 0) */
 private:
  IP7_Trace* trace_ = nullptr;
};

/* Define the CAPTURE macro for up to 10 arguments. */
/**
 * @brief
 *
 */
#define CAPTURE(...) \
  BOOST_PP_OVERLOAD(__LOG_INTERNAL_CAPTURE_, __VA_ARGS__)(__VA_ARGS__)

// clang-format off
#define __LOG_INTERNAL_CAPTURE_1(elem1) \
Trace(BOOST_PP_STRINGIZE(elem1) " = {} ", elem1)
#define __LOG_INTERNAL_CAPTURE_2(elem1, elem2) \
Trace(                                       \
    BOOST_PP_STRINGIZE(elem1) " = {} | "     \
    BOOST_PP_STRINGIZE(elem2) " = {}",       \
elem1, elem2)
#define __LOG_INTERNAL_CAPTURE_3(elem1, elem2, elem3) \
Trace(                                              \
    BOOST_PP_STRINGIZE(elem1) " = {} | "            \
    BOOST_PP_STRINGIZE(elem2) " = {} | "            \
    BOOST_PP_STRINGIZE(elem3) " = {}",              \
elem1, elem2, elem3)
#define __LOG_INTERNAL_CAPTURE_4(elem1, elem2, elem3, elem4) \
Trace(                                                     \
    BOOST_PP_STRINGIZE(elem1) " = {} | "                   \
    BOOST_PP_STRINGIZE(elem2) " = {} | "                   \
    BOOST_PP_STRINGIZE(elem3) " = {} | "                   \
    BOOST_PP_STRINGIZE(elem4) " = {}",                     \
elem1, elem2, elem3, elem4)
#define __LOG_INTERNAL_CAPTURE_5(elem1, elem2, elem3, elem4, elem5) \
Trace(                                                            \
    BOOST_PP_STRINGIZE(elem1) " = {} | "                          \
    BOOST_PP_STRINGIZE(elem2) " = {} | "                          \
    BOOST_PP_STRINGIZE(elem3) " = {} | "                          \
    BOOST_PP_STRINGIZE(elem4) " = {} | "                          \
    BOOST_PP_STRINGIZE(elem5) " = {}",                            \
elem1, elem2, elem3, elem4, elem5)
#define __LOG_INTERNAL_CAPTURE_6(elem1, elem2, elem3, elem4, elem5, elem6) \
Trace(                                                                   \
    BOOST_PP_STRINGIZE(elem1) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem2) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem3) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem4) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem5) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem6) " = {}",                                   \
elem1, elem2, elem3, elem4, elem5, elem6)
#define __LOG_INTERNAL_CAPTURE_7(elem1, elem2, elem3, elem4, elem5, elem6, \
                               elem7)                                    \
Trace(                                                                   \
    BOOST_PP_STRINGIZE(elem1) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem2) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem3) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem4) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem5) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem6) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem7) " = {}",                                   \
elem1, elem2, elem3, elem4, elem5, elem6, elem7)
#define __LOG_INTERNAL_CAPTURE_8(elem1, elem2, elem3, elem4, elem5, elem6, \
                               elem7, elem8)                             \
Trace(                                                                   \
    BOOST_PP_STRINGIZE(elem1) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem2) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem3) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem4) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem5) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem6) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem7) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem8) " = {}",                                   \
elem1, elem2, elem3, elem4, elem5, elem6, elem7, elem8)
#define __LOG_INTERNAL_CAPTURE_9(elem1, elem2, elem3, elem4, elem5, elem6, \
                               elem7, elem8, elem9)                      \
Trace(                                                                   \
    BOOST_PP_STRINGIZE(elem1) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem2) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem3) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem4) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem5) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem6) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem7) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem8) " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem9) " = {}",                                   \
elem1, elem2, elem3, elem4, elem5, elem6, elem7, elem8, elem9)
#define __LOG_INTERNAL_CAPTURE_10(elem1, elem2, elem3, elem4, elem5, elem6, \
                                elem7, elem8, elem9, elem10)              \
Trace(                                                                    \
    BOOST_PP_STRINGIZE(elem1)  " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem2)  " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem3)  " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem4)  " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem5)  " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem6)  " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem7)  " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem8)  " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem9)  " = {} | "                                 \
    BOOST_PP_STRINGIZE(elem10) " = {}",                                   \
elem1, elem2, elem3, elem4, elem5, elem6, elem7, elem8, elem9, elem10)

// clang-format on

inline void swap(Log& a, Log& b) noexcept { a.swap(b); }

} /* namespace logging */

#endif /* SRC_LOGGERV2_LOG_HPP_ */
