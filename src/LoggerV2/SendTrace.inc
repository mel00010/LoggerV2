/******************************************************************************
 * SendTrace.inc
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

//#ifndef BOOST_PP_ITERATION
//#include <cstdarg>
//#include <cstddef>
//#include <optional>
//#include <string>
//#include <string_view>
//#include <utility>
//
//#include <experimental/source_location>
//
//#include <boost/preprocessor/iteration/iterate.hpp>
//#include <boost/preprocessor/repetition.hpp>
//#include <boost/preprocessor/repetition/enum_params.hpp>
//#endif

#define LOG_max_iter 24
#define LOG_func_name() Count
#define LOG_level_enabled TRUE
#define LOG_level_value COUNT

#define BOOST_PP_ITERATION_LIMITS (8, LOG_max_iter - 1)
#define BOOST_PP_FILENAME_2 "LoggerV2/LogMetaFuncs.inc"
#include BOOST_PP_ITERATE()
#undef BOOST_PP_ITERATION_LIMITS
#undef BOOST_PP_FILENAME_2

#undef LOG_max_iter
#undef LOG_func_name
#undef LOG_level_enabled
#undef LOG_level_value

#ifndef SENDTRACE_print_args
#define SENDTRACE_print_args(z, n, data) \
  const BOOST_PP_CAT(T, n) BOOST_PP_CAT(t, n),
#endif  // SENDTRACE_print_args

#ifndef SENDTRACE_print_forwards
#define SENDTRACE_print_forwards(z, n, data) \
  , std::forward<const BOOST_PP_CAT(T, n)>(BOOST_PP_CAT(t, n))
#endif  // SENDTRACE_print_forwards

#define n BOOST_PP_ITERATION()

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Trace(const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  Trace(std::forward<const std::experimental::source_location>(loc),
        std::forward<const std::string>(format)
            BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Trace(const std::uint16_t id, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::TRACE, ModuleHandle{},
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Trace(const ModuleHandle handle, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  SendTrace(0, Level::TRACE, std::forward<const ModuleHandle>(handle),
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Trace(const std::uint16_t id, const ModuleHandle handle,
           const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::TRACE,
            std::forward<const ModuleHandle>(handle),
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Debug(const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  SendTrace(0, Level::DEBUG, ModuleHandle{},
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Debug(const std::uint16_t id, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::DEBUG, ModuleHandle{},
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}
template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Debug(const ModuleHandle handle, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  SendTrace(0, Level::DEBUG, std::forward<const ModuleHandle>(handle),
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}
template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Debug(const std::uint16_t id, const ModuleHandle handle,
           const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::DEBUG,
            std::forward<const ModuleHandle>(handle),
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Info(const std::string format,
          BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
              const std::experimental::source_location loc =
                  std::experimental::source_location::current()) {
  SendTrace(0, Level::INFO, ModuleHandle{},
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Info(const std::uint16_t id, const std::string format,
          BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
              const std::experimental::source_location loc =
                  std::experimental::source_location::current()) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::INFO, ModuleHandle{},
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Info(const ModuleHandle handle, const std::string format,
          BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
              const std::experimental::source_location loc =
                  std::experimental::source_location::current()) {
  SendTrace(0, Level::INFO, std::forward<const ModuleHandle>(handle),
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Info(const std::uint16_t id, const ModuleHandle handle,
          const std::string format,
          BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
              const std::experimental::source_location loc =
                  std::experimental::source_location::current()) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::INFO,
            std::forward<const ModuleHandle>(handle),
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Warning(const std::string format,
             BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                 const std::experimental::source_location loc =
                     std::experimental::source_location::current()) {
  SendTrace(0, Level::WARNING, ModuleHandle{},
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Warning(const std::uint16_t id, const std::string format,
             BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                 const std::experimental::source_location loc =
                     std::experimental::source_location::current()) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::WARNING,
            ModuleHandle{},
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Warning(const ModuleHandle handle, const std::string format,
             BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                 const std::experimental::source_location loc =
                     std::experimental::source_location::current()) {
  SendTrace(0, Level::WARNING, std::forward<const ModuleHandle>(handle),
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Warning(const std::uint16_t id, const ModuleHandle handle,
             const std::string format,
             BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                 const std::experimental::source_location loc =
                     std::experimental::source_location::current()) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::WARNING,
            std::forward<const ModuleHandle>(handle),
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Error(const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  SendTrace(0, Level::ERROR, ModuleHandle{},
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Error(const std::uint16_t id, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::ERROR, ModuleHandle{},
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Error(const ModuleHandle handle, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  SendTrace(0, Level::ERROR, std::forward<const ModuleHandle>(handle),
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Error(const std::uint16_t id, const ModuleHandle handle,
           const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::ERROR,
            std::forward<const ModuleHandle>(handle),
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Critical(const std::string format,
              BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                  const std::experimental::source_location loc =
                      std::experimental::source_location::current()) {
  SendTrace(0, Level::CRITICAL, ModuleHandle{},
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Critical(const std::uint16_t id, const std::string format,
              BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                  const std::experimental::source_location loc =
                      std::experimental::source_location::current()) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::CRITICAL,
            ModuleHandle{},
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Critical(const ModuleHandle handle, const std::string format,
              BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                  const std::experimental::source_location loc =
                      std::experimental::source_location::current()) {
  SendTrace(0, Level::CRITICAL, std::forward<const ModuleHandle>(handle),
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Critical(const std::uint16_t id, const ModuleHandle handle,
              const std::string format,
              BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                  const std::experimental::source_location loc =
                      std::experimental::source_location::current()) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::CRITICAL,
            std::forward<const ModuleHandle>(handle),
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Count(const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  SendTrace(0, Level::COUNT, ModuleHandle{},
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Count(const std::uint16_t id, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::COUNT, ModuleHandle{},
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}
template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Count(const ModuleHandle handle, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  SendTrace(0, Level::COUNT, std::forward<const ModuleHandle>(handle),
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}
template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Count(const std::uint16_t id, const ModuleHandle handle,
           const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const std::experimental::source_location loc =
                   std::experimental::source_location::current()) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::COUNT,
            std::forward<const ModuleHandle>(handle),
            std::forward<const std::experimental::source_location>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Trace(const std::string format, BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                                         const CustomSourceLocation loc) {
  SendTrace(0, Level::TRACE, ModuleHandle{},
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Trace(const std::uint16_t id, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const CustomSourceLocation loc) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::TRACE, ModuleHandle{},
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Trace(const ModuleHandle handle, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const CustomSourceLocation loc) {
  SendTrace(0, Level::TRACE, std::forward<const ModuleHandle>(handle),
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Trace(const std::uint16_t id, const ModuleHandle handle,
           const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const CustomSourceLocation loc) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::TRACE,
            std::forward<const ModuleHandle>(handle),
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Debug(const std::string format, BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                                         const CustomSourceLocation loc) {
  SendTrace(0, Level::DEBUG, ModuleHandle{},
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Debug(const std::uint16_t id, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const CustomSourceLocation loc) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::DEBUG, ModuleHandle{},
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}
template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Debug(const ModuleHandle handle, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const CustomSourceLocation loc) {
  SendTrace(0, Level::DEBUG, std::forward<const ModuleHandle>(handle),
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}
template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Debug(const std::uint16_t id, const ModuleHandle handle,
           const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const CustomSourceLocation loc) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::DEBUG,
            std::forward<const ModuleHandle>(handle),
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Info(const std::string format, BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                                        const CustomSourceLocation loc) {
  SendTrace(0, Level::INFO, ModuleHandle{},
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Info(const std::uint16_t id, const std::string format,
          BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
              const CustomSourceLocation loc) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::INFO, ModuleHandle{},
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Info(const ModuleHandle handle, const std::string format,
          BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
              const CustomSourceLocation loc) {
  SendTrace(0, Level::INFO, std::forward<const ModuleHandle>(handle),
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Info(const std::uint16_t id, const ModuleHandle handle,
          const std::string format,
          BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
              const CustomSourceLocation loc) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::INFO,
            std::forward<const ModuleHandle>(handle),
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Warning(const std::string format,
             BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                 const CustomSourceLocation loc) {
  SendTrace(0, Level::WARNING, ModuleHandle{},
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Warning(const std::uint16_t id, const std::string format,
             BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                 const CustomSourceLocation loc) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::WARNING,
            ModuleHandle{}, std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Warning(const ModuleHandle handle, const std::string format,
             BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                 const CustomSourceLocation loc) {
  SendTrace(0, Level::WARNING, std::forward<const ModuleHandle>(handle),
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Warning(const std::uint16_t id, const ModuleHandle handle,
             const std::string format,
             BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                 const CustomSourceLocation loc) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::WARNING,
            std::forward<const ModuleHandle>(handle),
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Error(const std::string format, BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                                         const CustomSourceLocation loc) {
  SendTrace(0, Level::ERROR, ModuleHandle{},
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Error(const std::uint16_t id, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const CustomSourceLocation loc) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::ERROR, ModuleHandle{},
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Error(const ModuleHandle handle, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const CustomSourceLocation loc) {
  SendTrace(0, Level::ERROR, std::forward<const ModuleHandle>(handle),
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Error(const std::uint16_t id, const ModuleHandle handle,
           const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const CustomSourceLocation loc) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::ERROR,
            std::forward<const ModuleHandle>(handle),
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Critical(const std::string format,
              BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                  const CustomSourceLocation loc) {
  SendTrace(0, Level::CRITICAL, ModuleHandle{},
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Critical(const std::uint16_t id, const std::string format,
              BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                  const CustomSourceLocation loc) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::CRITICAL,
            ModuleHandle{}, std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Critical(const ModuleHandle handle, const std::string format,
              BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                  const CustomSourceLocation loc) {
  SendTrace(0, Level::CRITICAL, std::forward<const ModuleHandle>(handle),
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Critical(const std::uint16_t id, const ModuleHandle handle,
              const std::string format,
              BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                  const CustomSourceLocation loc) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::CRITICAL,
            std::forward<const ModuleHandle>(handle),
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Count(const std::string format, BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
                                         const CustomSourceLocation loc) {
  SendTrace(0, Level::COUNT, ModuleHandle{},
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Count(const std::uint16_t id, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const CustomSourceLocation loc) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::COUNT, ModuleHandle{},
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}
template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Count(const ModuleHandle handle, const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const CustomSourceLocation loc) {
  SendTrace(0, Level::COUNT, std::forward<const ModuleHandle>(handle),
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}
template <BOOST_PP_ENUM_PARAMS(n, class T)>
void Count(const std::uint16_t id, const ModuleHandle handle,
           const std::string format,
           BOOST_PP_REPEAT(n, SENDTRACE_print_args, ~)
               const CustomSourceLocation loc) {
  SendTrace(std::forward<const std::uint16_t>(id), Level::COUNT,
            std::forward<const ModuleHandle>(handle),
            std::forward<const CustomSourceLocation>(loc),
            std::forward<const std::string>(format)
                BOOST_PP_REPEAT(n, SENDTRACE_print_forwards, ~));
}

#undef n

#ifdef SENDTRACE_print_args
#undef SENDTRACE_print_args
#endif  // SENDTRACE_print_args

#ifdef SENDTRACE_print_forwards
#undef SENDTRACE_print_forwards
#endif  // SENDTRACE_print_forwards
