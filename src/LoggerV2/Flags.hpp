/******************************************************************************
 * Flags.hpp
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
#ifndef SRC_LOGGERV2_FLAGS_HPP_
#define SRC_LOGGERV2_FLAGS_HPP_

#include <array>
#include <cstring>
#include <string>
#include <vector>

#include <boost/algorithm/string/trim.hpp>

#include "absl/flags/flag.h"
#include "absl/strings/string_view.h"

#include "LoggerV2/Client.hpp"

namespace logging::flags {

enum class LogSink : std::uint8_t {
  kBaical,
  kBinary,
  kText,
  kConsole,
  kSyslog,
  kAuto,
  kNull
};
inline constexpr LogSink kLogSinkDefault = LogSink::kAuto;
bool LogSinkIsDefault(const LogSink flag);
bool AbslParseFlag(absl::string_view text, LogSink* flag, std::string* error);
std::string AbslUnparseFlag(const LogSink& flag);

struct LogName {
  explicit LogName(absl::string_view name_) : name(name_) {}
  bool IsDefault();

  std::string name;
  static inline constexpr size_t kMaxNameLength = 96;
};
inline const LogName kLogNameDefault = LogName{""};

bool AbslParseFlag(absl::string_view text, LogName* flag, std::string* error);
std::string AbslUnparseFlag(const LogName& flag);

enum class LogInternalVerbosityLevel : std::int32_t {
  kOff = -1,
  kDebug = 0,
  kInfo = 1,
  kWarning = 2,
  kError = 3,
  kCritical = 4
};
inline constexpr LogInternalVerbosityLevel kLogIntVerbDefault =
    LogInternalVerbosityLevel::kOff;
bool LogIntVerbIsDefault(const LogInternalVerbosityLevel flag);

bool AbslParseFlag(absl::string_view text, LogInternalVerbosityLevel* flag,
                   std::string* error);
std::string AbslUnparseFlag(const LogInternalVerbosityLevel& flag);
std::ostream& operator<<(std::ostream& os,
                         const LogInternalVerbosityLevel value);

enum class TraceVerbosityLevel : std::int32_t {
  kTrace = 0,
  kDebug = 1,
  kInfo = 2,
  kWarning = 3,
  kError = 4,
  kCritical = 5
};
inline constexpr TraceVerbosityLevel kLogTraceVerbDefault =
    TraceVerbosityLevel::kTrace;
bool TraceVerbIsDefault(const TraceVerbosityLevel flag);

bool AbslParseFlag(absl::string_view text, TraceVerbosityLevel* flag,
                   std::string* error);
std::string AbslUnparseFlag(const TraceVerbosityLevel& flag);
std::ostream& operator<<(std::ostream& os, const TraceVerbosityLevel value);

struct LogPoolSize {
  explicit LogPoolSize(int size) : pool_size(size) {}
  bool IsDefault();

  int pool_size;
  static inline constexpr std::int32_t kLogPoolSizeMin = 16;
};
inline const LogPoolSize kLogPoolSizeDefault = LogPoolSize{4096};
bool AbslParseFlag(absl::string_view text, LogPoolSize* flag,
                   std::string* error);
std::string AbslUnparseFlag(const LogPoolSize& flag);

struct LoggingEnabled {
  explicit LoggingEnabled(bool enable) : enabled(enable) {}
  bool IsDefault();

  bool enabled;
};
inline const LoggingEnabled kLoggingDefault = LoggingEnabled{true};
bool AbslParseFlag(absl::string_view text, LoggingEnabled* flag,
                   std::string* error);
std::string AbslUnparseFlag(const LoggingEnabled& flag);

struct LogHelp {
  explicit LogHelp(bool help_) : help(help_) {}
  bool IsDefault();

  bool help;
};
inline const LogHelp kLogHelpDefault = LogHelp{false};
bool AbslParseFlag(absl::string_view text, LogHelp* flag, std::string* error);
std::string AbslUnparseFlag(const LogHelp& flag);

struct LogAddress {
  explicit LogAddress(std::string address_) : address(address_) {}
  bool IsDefault();

  std::string address;
};
inline const LogAddress kLogAddressDefault = LogAddress{"127.0.0.1"};
bool AbslParseFlag(absl::string_view text, LogAddress* flag,
                   std::string* error);
std::string AbslUnparseFlag(const LogAddress& flag);

struct LogPort {
  explicit LogPort(std::int32_t port_) : port(port_) {}
  bool IsDefault();

  std::int32_t port;
  static inline constexpr std::int32_t kPortMax = 65535;
};
inline const LogPort kLogPortDefault = LogPort{9010};
bool AbslParseFlag(absl::string_view text, LogPort* flag, std::string* error);
std::string AbslUnparseFlag(const LogPort& flag);

struct LogPacketSize {
  explicit LogPacketSize(std::int32_t size) : packet_size(size) {}
  bool IsDefault();

  std::int32_t packet_size;
  static inline constexpr std::int32_t kPacketSizeMin = 512;
  static inline constexpr std::int32_t kPacketSizeMax = 65535;
};
inline const LogPacketSize kLogPacketSizeDefault = LogPacketSize{512};
bool AbslParseFlag(absl::string_view text, LogPacketSize* flag,
                   std::string* error);
std::string AbslUnparseFlag(const LogPacketSize& flag);

struct LogWindow {
  explicit LogWindow(std::int32_t window_) : window(window_) {}
  bool IsDefault();

  std::int32_t window;
  static inline constexpr std::int32_t kLogWindowSizeMin = 1;
};
inline const LogWindow kLogWindowDefault = LogWindow{0};
bool AbslParseFlag(absl::string_view text, LogWindow* flag, std::string* error);
std::string AbslUnparseFlag(const LogWindow& flag);

struct LogEto {
  explicit LogEto(std::int32_t eto_) : eto(eto_) {}
  bool IsDefault();

  std::int32_t eto;
};
inline const LogEto kLogEtoDefault = LogEto{0};
bool AbslParseFlag(absl::string_view text, LogEto* flag, std::string* error);
std::string AbslUnparseFlag(const LogEto& flag);

struct LogFormat {
  explicit LogFormat(std::string format_) : format(format_) {}
  bool IsDefault();

  std::string format;
};
inline const LogFormat kLogFormatDefault =
    LogFormat{"%cn #%ix [%tf] %lv Tr:#%ti:%tn CPU:%cc Md:%mn{%fs:%fl:%fn} %ms"};
bool AbslParseFlag(absl::string_view text, LogFormat* flag, std::string* error);
std::string AbslUnparseFlag(const LogFormat& flag);

struct LogFacility {
  explicit LogFacility(std::int32_t facility_) : facility(facility_) {}
  bool IsDefault();

  std::int32_t facility;
};
inline const LogFacility kLogFacilityDefault = LogFacility{1};
bool AbslParseFlag(absl::string_view text, LogFacility* flag,
                   std::string* error);
std::string AbslUnparseFlag(const LogFacility& flag);

struct LogDir {
  explicit LogDir(std::string dir_) : dir(dir_) {}
  bool IsDefault();

  std::string dir;
};
inline const LogDir kLogDirDefault = LogDir{""};
bool AbslParseFlag(absl::string_view text, LogDir* flag, std::string* error);
std::string AbslUnparseFlag(const LogDir& flag);

struct LogRoll {
  explicit LogRoll(std::string roll_) : roll(roll_) {}
  bool IsDefault();

  std::string roll;
};
inline const LogRoll kLogRollDefault = LogRoll{""};
bool AbslParseFlag(absl::string_view text, LogRoll* flag, std::string* error);
std::string AbslUnparseFlag(const LogRoll& flag);

struct LogFiles {
  explicit LogFiles(std::int32_t files_) : files(files_) {}
  bool IsDefault();

  std::int32_t files;
};
inline const LogFiles kLogFilesDefault = LogFiles{0};
bool AbslParseFlag(absl::string_view text, LogFiles* flag, std::string* error);
std::string AbslUnparseFlag(const LogFiles& flag);

struct LogFSize {
  explicit LogFSize(std::int64_t size) : fsize(size) {}
  bool IsDefault();

  std::int64_t fsize;
  static inline constexpr std::int64_t kLogFSizeMax = 4294967296;
};
inline const LogFSize kLogFSizeDefault = LogFSize{0};
bool AbslParseFlag(absl::string_view text, LogFSize* flag, std::string* error);
std::string AbslUnparseFlag(const LogFSize& flag);

} /* namespace logging::flags */

#endif /* SRC_LOGGERV2_FLAGS_HPP_ */
