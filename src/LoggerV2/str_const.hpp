/******************************************************************************
 * str_const.hpp
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
#ifndef SRC_LOGGERV2_STR_CONST_HPP_
#define SRC_LOGGERV2_STR_CONST_HPP_

#include <cstdint>
#include <utility>

#if __cpp_impl_three_way_comparison
#include <compare>
#endif /* __cpp_impl_three_way_comparison */

namespace logging {

class str_const {  // constexpr string
 public:
  char p_[1000]{};
  const std::size_t sz_;

  int constexpr length(const char* str) {
    return *str ? 1 + length(str + 1) : 0;
  }

  template <std::size_t N>
  constexpr str_const(const char (&a)[N]) : p_(a), sz_(N - 1) {}

  constexpr str_const(const char* a) : sz_(length(a)) {
    for (std::size_t i = 0; i != sz_; ++i) p_[i] = a[i];
  }
  constexpr char operator[](std::size_t n) {
    return n < sz_ ? p_[n] : throw std::out_of_range("");
  }
  constexpr operator char const *() const { return p_; }
  constexpr std::size_t size() { return sz_; }
#if __cpp_impl_three_way_comparison
  constexpr auto operator<=>(const str_const&) const = default;
#endif /* __cpp_impl_three_way_comparison */
};

} /* namespace logging */

#endif /* SRC_LOGGERV2_STR_CONST_HPP_ */
