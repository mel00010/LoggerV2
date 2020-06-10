// <experimental/source_location> -*- C++ -*-

// Copyright (C) 2015-2019 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file experimental/source_location
 *  This is a TS C++ Library header.
 */

#ifndef _GLIBCXX_EXPERIMENTAL_SRCLOC
#define _GLIBCXX_EXPERIMENTAL_SRCLOC 1

#include <cstdint>

#ifndef __has_builtin
#define __has_builtin(x) 0  // Compatibility with non-clang compilers.
#endif

namespace std {
#define __cpp_lib_experimental_source_location 201505

struct source_location {
  // 14.1.2, source_location creation
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
        source_location __loc;
        __loc._M_file = __file;
        __loc._M_func = __func;
        __loc._M_line = __line;
        __loc._M_col = __col;
        return __loc;
      }

      constexpr source_location() noexcept
          : _M_file("unknown"), _M_func(_M_file), _M_line(0), _M_col(0) {}

      // 14.1.3, source_location field access
      constexpr uint_least32_t line() const noexcept { return _M_line; }
      constexpr uint_least32_t column() const noexcept { return _M_col; }
      constexpr const char* file_name() const noexcept { return _M_file; }
      constexpr const char* function_name() const noexcept { return _M_func; }

     private:
      const char* _M_file;
      const char* _M_func;
      uint_least32_t _M_line;
      uint_least32_t _M_col;
};
}  // namespace std

#endif
