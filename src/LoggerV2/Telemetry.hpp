/******************************************************************************
 * Telemetry.hpp
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
#ifndef SRC_LOGGERV2_TELEMETRY_HPP_
#define SRC_LOGGERV2_TELEMETRY_HPP_

#include <cstdarg>
#include <cstddef>
#include <optional>
#include <string>
#include <utility>

#include "P7_Telemetry.h"

namespace logging {

class Telemetry;

/**
 * @brief Handle for a telemetry channel
 */
struct TelemetryChannelHandle {
  std::string name; /**< @brief Name of the channel */
  std::uint16_t id; /**< @brief ID of the channel */

  /** @brief Pointer to the Telemetry object it is associated with */
  const Telemetry* telemetry;

  /**
   * @brief Swaps two TelemetryChannelHandle objects
   *
   * @param other Other TelemetryChannelHandle object to swap with
   */
  void swap(TelemetryChannelHandle& other) noexcept {
    using std::swap;
    swap(other.name, name);
    swap(other.id, id);
    swap(other.telemetry, telemetry);
  }
  /**
   * @brief Adds a sample to a counter
   *
   * @param value Value to add to the counter
   * @return Returns true on success, false on failure
   */
  bool Add(const double value) const;
};
/**
 * @brief Swaps two TelemetryChannelHandle objects
 *
 * @param a TelemetryChannelHandle object to swap
 * @param b TelemetryChannelHandle object to swap
 */
inline void swap(TelemetryChannelHandle& a,
                 TelemetryChannelHandle& b) noexcept {
  a.swap(b);
}

/**
 * @brief Holds a telemetry log channel
 */
class Telemetry {
 public:
  Telemetry() noexcept = default;
  Telemetry& operator=(const Telemetry& rhs) = default;
  Telemetry(const Telemetry& rhs) = default;
  Telemetry& operator=(Telemetry&& rhs) noexcept = default;
  Telemetry(Telemetry&& rhs) noexcept = default;

  explicit Telemetry(const std::string name);
  ~Telemetry() noexcept;

  /**
   * @brief Creates a new telemetry counter.
   *
   * @param name Name of the counter.  Must be unique.  Max length 64
   *        characters.
   * @param counter_min Minimal counter value for visualization.  Can be changed
   *        later from viewer.
   * @param counter_alarm_min Alarm counter value for visualization.  Values
   *        below this will be highlighted. Can be changed later from viewer.
   * @param counter_max Maximal counter value for visualization.  Can be changed
   *        later from viewer.
   * @param counter_alarm_max Alarm counter value for visualization.  Values
   *        above this will be highlighted. Can be changed later from viewer.
   * @param enabled Specifies if counter is enabled or disabled by default.  Can
   *        be changed later from viewer.
   * @return Returns a handle to the channel if successfully created
   */
  inline std::optional<TelemetryChannelHandle> Create(
      const std::string& name, const double counter_min,
      const double counter_alarm_min, const double counter_max,
      const double counter_alarm_max, const bool enabled) const {
    TelemetryChannelHandle handle{};
    handle.name = name;
    handle.telemetry = this;
    return (telemetry_->Create(name.c_str(), counter_min, counter_alarm_min,
                               counter_max, counter_alarm_max, enabled,
                               &(handle.id)))
               ? std::optional<TelemetryChannelHandle>(handle)
               : std::nullopt;
  }
  /**
   * @brief Adds a sample to a counter
   *
   * @param handle Handle to the counter to add to
   * @param value Value to add to the counter
   * @return Returns true on success, false on failure
   */
  inline bool Add(const TelemetryChannelHandle& handle,
                  const double value) const {
    return telemetry_->Add(handle.id, value);
  }
  /**
   * @brief Finds a counter by name
   *
   * @param name Name of counter to find
   * @return Returns a handle to the counter if found
   */
  inline std::optional<TelemetryChannelHandle> Find(
      const std::string& name) const {
    TelemetryChannelHandle handle{};
    handle.name = name;
    handle.telemetry = this;
    return (telemetry_->Find(name.c_str(), &(handle.id)))
               ? std::optional<TelemetryChannelHandle>(handle)
               : std::nullopt;
  }

  /**
   * @brief Swaps two telemetry objects
   *
   * @param other Other telemetry object to swap
   */
  void swap(Telemetry& other) noexcept {
    using std::swap;
    swap(telemetry_, other.telemetry_);
  }

 private:
  IP7_Telemetry* telemetry_ = nullptr;
};

/**
 * @brief Swaps two telemetry objects
 *
 * @param a Telemetry object to swap
 * @param b Telemetry object to swap
 */
inline void swap(Telemetry& a, Telemetry& b) noexcept { a.swap(b); }

} /* namespace logging */

#endif /* SRC_LOGGERV2_TELEMETRY_HPP_ */
