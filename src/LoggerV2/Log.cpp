/******************************************************************************
 * Log.cpp
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

#include "LoggerV2/Log.hpp"

#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "P7_Trace.h"

#include "LoggerV2/Client.hpp"

namespace logging {

Log::Log(const std::string name) {
  using namespace std::literals::string_literals;

  if ((trace_ = P7_Get_Shared_Trace(name.c_str())) == nullptr) {
    Client client("main");
    stTrace_Conf trace_conf{};
    trace_conf.pContext = nullptr;
    trace_conf.qwTimestamp_Frequency = 0;
    trace_conf.pTimestamp_Callback = nullptr;
    trace_conf.pVerbosity_Callback = nullptr;
    trace_conf.pConnect_Callback = nullptr;

    if ((trace_ = P7_Create_Trace(client.client(), name.c_str(),
                                  &trace_conf)) == nullptr) {
      throw std::runtime_error("P7_Create_Trace failed");
    }
    if (!trace_->Share(name.c_str())) {
      throw std::runtime_error("trace_->Share("s + name.c_str() + ") failed."s);
    }
    // Intentionally increase ref counter so that the logger isn't created
    // and destroyed constantly and to enable log support for crashes
    //    trace_->Add_Ref();
  }
}

Log::~Log() noexcept {
  if (trace_ != nullptr) {
    trace_->Release();
  }
}

} /* namespace logging */
