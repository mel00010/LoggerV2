/******************************************************************************
 * Log_test.cpp
 * Copyright (C) 2019  Mel McCalla <melmccalla@gmail.com>
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

#include <ostream>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "LoggerV2/Client.hpp"

using logging::Client;
using logging::Level;
using GELog = logging::Log;

using logging::ModuleHandle;

using src_loc = logging::CustomSourceLocation;

class LogTest : public ::testing::Test {
 public:
  static void SetUpTestCase() {
    client_ = new Client("main");
    log_ = new GELog("main test");
  }
  static void TearDownTestCase() {
    P7_Exceptional_Flush();
    log_ = nullptr;
    client_ = nullptr;
  }
  static Client* client_;
  static GELog* log_;

  int int_test = 5;
  long long_test = 50000000000L;
  void* pointer_test = (void*)0xDEADBEEF;
  std::string string_test = "string test";
};
Client* LogTest::client_ = nullptr;
GELog* LogTest::log_ = nullptr;

TEST_F(LogTest, SendTraceTest) {
  log_->RegisterThread("Test thread");
  int64_t test = 1337;
  log_->CAPTURE(test);

  log_->SendTrace(Level::TRACE, ModuleHandle{}, "Test Trace");
  log_->SendTrace(Level::DEBUG, ModuleHandle{}, "Test Debug");
  log_->SendTrace(Level::INFO, ModuleHandle{}, "Test Info");
  log_->SendTrace(Level::WARNING, ModuleHandle{}, "Test Warning");
  log_->SendTrace(Level::ERROR, ModuleHandle{}, "Test Error");
  log_->SendTrace(Level::CRITICAL, ModuleHandle{}, "Test Critical");
  log_->SendTrace(Level::COUNT, ModuleHandle{}, "Test Count");

  log_->SendTrace(Level::TRACE, ModuleHandle{}, "Test Trace {} {} {} {}",
                  int_test, long_test, pointer_test, string_test);
  log_->SendTrace(Level::TRACE, ModuleHandle{}, "Test SendTrace {} {} {} {} {}",
                  int_test, long_test, pointer_test, string_test, int_test);
  //  log_->SendTrace(Level::TRACE, ModuleHandle{}, "Test Trace {} {} {} {}",
  //                  src_loc::current(), int_test, long_test, pointer_test,
  //                  string_test);

  const ModuleHandle mh = log_->RegisterModule("SendTrace Test").value();

  log_->SendTrace(Level::TRACE, mh, "Test Trace Module");
  log_->SendTrace(Level::DEBUG, mh, "Test Debug Module");
  log_->SendTrace(Level::INFO, mh, " Test Info Module");
  log_->SendTrace(Level::WARNING, mh, "Test Warn Module");
  log_->SendTrace(Level::ERROR, mh, "Test Error Module");
  log_->SendTrace(Level::CRITICAL, mh, "Test Crit Module");
  log_->SendTrace(Level::COUNT, mh, "Test Count Module");

  log_->SendTrace(Level::TRACE, mh, "Test SendTrace Module {} {} {} {} {}",
                  int_test, long_test, pointer_test, string_test, int_test);
}

TEST_F(LogTest, TraceTest) {
  log_->RegisterThread("Test thread");

  log_->Trace("Test Trace");
  log_->Trace("Test Trace {} {} {} {} {}", int_test, long_test, pointer_test,
              string_test, int_test);
  const ModuleHandle mh = log_->RegisterModule("Trace Test").value();
  log_->Trace(mh, "Test Trace Module");
  log_->Trace(mh, "Test Trace Module {} {} {} {} {}", int_test, long_test,
              pointer_test, string_test, int_test);
}
TEST_F(LogTest, DebugTest) {
  log_->RegisterThread("Test thread");

  log_->Debug("Test Debug");
  log_->Debug("Test Debug {} {} {} {} {}", int_test, long_test, pointer_test,
              string_test, int_test);
  const ModuleHandle mh = log_->RegisterModule("Debug Test").value();
  log_->Debug(mh, "Test Debug Module");
  log_->Debug(mh, "Test Debug Module {} {} {} {} {}", int_test, long_test,
              pointer_test, string_test, int_test);
}
TEST_F(LogTest, InfoTest) {
  log_->RegisterThread("Test thread");

  log_->Info("Test Info");
  log_->Info("Test Info {} {} {} {} {}", int_test, long_test, pointer_test,
             string_test, int_test);
  const ModuleHandle mh = log_->RegisterModule("Info Test").value();
  log_->Info(mh, "Test Info Module");
  log_->Info(mh, "Test Info Module {} {} {} {} {}", int_test, long_test,
             pointer_test, string_test, int_test);
}
TEST_F(LogTest, WarningTest) {
  log_->RegisterThread("Test thread");

  log_->Warning("Test Warning");
  log_->Warning("Test Warning {} {} {} {} {}", int_test, long_test,
                pointer_test, string_test, int_test);
  const ModuleHandle mh = log_->RegisterModule("Warning Test").value();
  log_->Warning(mh, "Test Warning Module");
  log_->Warning(mh, "Test Warning Module {} {} {} {} {}", int_test, long_test,
                pointer_test, string_test, int_test);
}
TEST_F(LogTest, ErrorTest) {
  log_->RegisterThread("Test thread");

  log_->Error("Test Error");
  log_->Error("Test Error {} {} {} {} {}", int_test, long_test, pointer_test,
              string_test, int_test);
  const ModuleHandle mh = log_->RegisterModule("Error Test").value();
  log_->Error(mh, "Test Error Module");
  log_->Error(mh, "Test Error Module {} {} {} {} {}", int_test, long_test,
              pointer_test, string_test, int_test);
}
TEST_F(LogTest, CriticalTest) {
  log_->RegisterThread("Test thread");

  log_->Critical("Test Critical");
  log_->Critical("Test Critical {} {} {} {} {}", int_test, long_test,
                 pointer_test, string_test, int_test);
  const ModuleHandle mh = log_->RegisterModule("Critical Test").value();
  log_->Critical(mh, "Test Critical Module");
  log_->Critical(mh, "Test Critical Module {} {} {} {} {}", int_test, long_test,
                 pointer_test, string_test, int_test);
}
TEST_F(LogTest, CountTest) {
  log_->RegisterThread("Test thread");

  log_->Count("Test Count");
  log_->Count("Test Count {} {} {} {} {}", int_test, long_test, pointer_test,
              string_test, int_test);
  const ModuleHandle mh = log_->RegisterModule("Count Test").value();
  log_->Count(mh, "Test Count Module");
  log_->Count(mh, "Test Count Module {} {} {} {} {}", int_test, long_test,
              pointer_test, string_test, int_test);
}

TEST_F(LogTest, CaptureTest) {
  int capture1 = 100;
  int capture2 = 500;
  std::string capture3 = "Test";
  bool capture4 = true;
  short capture5 = 64;
  //  const char* capture6 = "Test23";
  //  long capture7 = 109230942049;
  //  void* capture8 = (void*)0xDEADBEEF;
  //  int capture9 = 2341452;
  //  char capture10 = 'k';

  log_->CAPTURE(capture1);
  log_->CAPTURE(capture1, capture2);
  log_->CAPTURE(capture1, capture2, capture3);
  log_->CAPTURE(capture1, capture2, capture3, capture4);
  log_->CAPTURE(capture1, capture2, capture3, capture4, capture5);
  //  log_->CAPTURE(capture1, capture2, capture3, capture4, capture5, capture6);
  //  log_->CAPTURE(capture1, capture2, capture3, capture4, capture5, capture6,
  //                capture7);
  //  log_->CAPTURE(capture1, capture2, capture3, capture4, capture5, capture6,
  //                capture7, capture8);
  //  log_->CAPTURE(capture1, capture2, capture3, capture4, capture5, capture6,
  //                capture7, capture8, capture9);
  //  log_->CAPTURE(capture1, capture2, capture3, capture4, capture5, capture6,
  //                capture7, capture8, capture9, capture10);
}
