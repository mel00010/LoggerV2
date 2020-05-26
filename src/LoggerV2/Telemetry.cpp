/******************************************************************************
 * Telemetry.cpp
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

#include "LoggerV2/Telemetry.hpp"

#include <iostream>
#include <optional>
#include <ostream>
#include <stdexcept>
#include <string>

#include "P7_Telemetry.h"

#include "LoggerV2/Client.hpp"

namespace logging {

bool TelemetryChannelHandle::Add(const double value) const {
  if (telemetry != nullptr) {
    return telemetry->Add(*this, value);
  }
  return false;
}

Telemetry::Telemetry(const std::string name) {
  using namespace std::literals::string_literals;

  if ((telemetry_ = P7_Get_Shared_Telemetry(name.c_str())) == nullptr) {
    Client client("main");

    stTelemetry_Conf telem_conf{};
    telem_conf.pContext = nullptr;
    telem_conf.qwTimestamp_Frequency = 0;
    telem_conf.pTimestamp_Callback = nullptr;
    telem_conf.pEnable_Callback = nullptr;
    telem_conf.pConnect_Callback = nullptr;

    if ((telemetry_ = P7_Create_Telemetry(client.client(), name.c_str(),
                                          &telem_conf)) == nullptr) {
      std::cerr << "P7_Create_Telemetry failed" << std::endl;
      throw std::runtime_error("P7_Create_Telemetry failed");
    }
    if (!telemetry_->Share(name.c_str())) {
      throw std::runtime_error("telemetry_->Share("s + name + ") failed."s);
    }
    // Intentionally increase ref counter so that the logger isn't created
    // and destroyed constantly and to enable log support for crashes
    telemetry_->Add_Ref();
  }
}

Telemetry::~Telemetry() noexcept {
  if (telemetry_ != nullptr) {
    telemetry_->Release();
  }
}

} /* namespace logging */
