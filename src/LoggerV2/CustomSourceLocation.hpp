/******************************************************************************
 * CustomSourceLocation.hpp
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
#ifndef SRC_LOGGERV2_CUSTOMSOURCELOCATION_HPP_
#define SRC_LOGGERV2_CUSTOMSOURCELOCATION_HPP_

#ifndef __has_builtin
#define __has_builtin(x) 0  // Compatibility with non-clang compilers.
#endif

namespace logging {

struct CustomSourceLocation {
 public:
  constexpr CustomSourceLocation(const char* file, const char* func,
                                 const std::uint_least32_t line,
                                 const std::uint_least32_t col = 0) noexcept
      : file_(file), func_(func), line_(line), col_(col) {}
  constexpr CustomSourceLocation() noexcept
      : file_("unknown"), func_(file_), line_(0), col_(0) {}

  // 14.1.2, source_location creation
  static constexpr CustomSourceLocation current(
#if __has_builtin(__builtin_FILE)
      const char* __file = __builtin_FILE(),
#else  /* __has_builtin(__builtin_FILE) */
      const char* __file = "unknown",
#endif /* __has_builtin(__builtin_FILE) */
#if __has_builtin(__builtin_FUNCTION)
      const char* __func = __builtin_FUNCTION(),
#else  /* __has_builtin(__builtin_FUNCTION) */
      const char* __func = "unknown",
#endif /* __has_builtin(__builtin_FUNCTION) */
#if __has_builtin(__builtin_LINE)
      int __line = __builtin_LINE(),
#else  /* __has_builtin(__builtin_LINE) */
      int __line = 0,
#endif /* __has_builtin(__builtin_LINE) */
#if __has_builtin(__builtin_COLUMN)
      int __col = __builtin_COLUMN()
#else  /* __has_builtin(__builtin_COLUMN) */
      int __col = 0
#endif /* __has_builtin(__builtin_COLUMN) */
          ) noexcept {

    CustomSourceLocation __loc;
    __loc.file_ = __file;
    __loc.func_ = __func;
    __loc.line_ = __line;
    __loc.col_ = __col;
    return __loc;
  }

  // 14.1.3, source_location field access
  constexpr std::uint_least32_t line() const noexcept { return line_; }
  constexpr std::uint_least32_t column() const noexcept { return col_; }
  constexpr const char* file_name() const noexcept { return file_; }
  constexpr const char* function_name() const noexcept { return func_; }

 private:
  const char* file_;
  const char* func_;
  std::uint_least32_t line_;
  std::uint_least32_t col_;
};

} /* namespace logging */

#endif /* SRC_LOGGERV2_CUSTOMSOURCELOCATION_HPP_ */
