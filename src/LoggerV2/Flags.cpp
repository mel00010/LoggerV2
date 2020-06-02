/******************************************************************************
 * Flags.cpp
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

#include "LoggerV2/Flags.hpp"

#include <string>

#include "absl/flags/declare.h"
#include "absl/flags/flag.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"

#include "LoggerV2/Client.hpp"

ABSL_DECLARE_FLAG(::logging::flags::LogSink, log_sink);
ABSL_DECLARE_FLAG(::logging::flags::LogPoolSize, log_pool_size);
ABSL_DECLARE_FLAG(::logging::flags::LogPacketSize, log_packet_size);

namespace logging::flags {

bool LogSinkIsDefault(const LogSink flag) { return (flag == kLogSinkDefault); }
bool AbslParseFlag(absl::string_view text, LogSink* flag, std::string* error) {
  if (text == "auto") {
    *flag = LogSink::kAuto;
    return true;
  } else if (text == "baical") {
    *flag = LogSink::kBaical;
    return true;
  } else if (text == "binary") {
    *flag = LogSink::kBinary;
    return true;
  } else if (text == "console") {
    *flag = LogSink::kConsole;
    return true;
  } else if (text == "null") {
    *flag = LogSink::kNull;
    return true;
  } else if (text == "syslog") {
    *flag = LogSink::kSyslog;
    return true;
  } else if (text == "text") {
    *flag = LogSink::kText;
    return true;
  }
  *error =
      "Must be one of {\"auto\", \"baical\", \"binary\", \"console\", "
      "\"null\", \"syslog\", \"text\"}.";
  return false;
}

std::string AbslUnparseFlag(const LogSink& flag) {
  switch (flag) {
    case LogSink::kAuto:
      return "auto";
    case LogSink::kBaical:
      return "baical";
    case LogSink::kBinary:
      return "binary";
    case LogSink::kConsole:
      return "console";
    case LogSink::kNull:
      return "null";
    case LogSink::kSyslog:
      return "syslog";
    case LogSink::kText:
      return "text";
  }
  return "unknown";
}
bool LogName::IsDefault() { return (name == kLogNameDefault.name); }
bool AbslParseFlag(absl::string_view text, LogName* flag, std::string* error) {
  if (!absl::ParseFlag(text, &flag->name, error)) {
    return false;
  }
  if (flag->name.length() > LogName::kMaxNameLength) {
    *error =
        absl::StrCat("Value is too long (", text.length(),
                     " characters).  Length must be less than or equal to ",
                     LogName::kMaxNameLength, ". ");
    return false;
  }
  return true;
}
std::string AbslUnparseFlag(const LogName& flag) {
  return absl::UnparseFlag(flag.name);
}

bool LoggingEnabled::IsDefault() {
  return (enabled == kLoggingDefault.enabled);
}
bool AbslParseFlag(absl::string_view text, LoggingEnabled* flag,
                   std::string* error) {
  // No validation to do for now
  if (!absl::ParseFlag(text, &flag->enabled, error)) {
    return false;
  }
  return true;
}
std::string AbslUnparseFlag(const LoggingEnabled& flag) {
  return absl::UnparseFlag(flag.enabled);
}

bool LogIntVerbIsDefault(const LogInternalVerbosityLevel flag) {
  return (flag == kLogIntVerbDefault);
}
bool AbslParseFlag(absl::string_view text, LogInternalVerbosityLevel* flag,
                   std::string* error) {
  if (text == "off") {
    *flag = LogInternalVerbosityLevel::kOff;
    return true;
  } else if (text == "debug") {
    *flag = LogInternalVerbosityLevel::kDebug;
    return true;
  } else if (text == "info") {
    *flag = LogInternalVerbosityLevel::kInfo;
    return true;
  } else if (text == "warning") {
    *flag = LogInternalVerbosityLevel::kWarning;
    return true;
  } else if (text == "error") {
    *flag = LogInternalVerbosityLevel::kError;
    return true;
  } else if (text == "critical") {
    *flag = LogInternalVerbosityLevel::kCritical;
    return true;
  }
  *error = absl::StrCat("Value unknown! (", text,
                        ") Value must be one of \"off\", \"debug\", \"info\", "
                        "\"warning\", \"error\", \"critical\"");
  return false;
}
std::string AbslUnparseFlag(const LogInternalVerbosityLevel& flag) {
  switch (flag) {
    case LogInternalVerbosityLevel::kOff:
      return "off";
    case LogInternalVerbosityLevel::kDebug:
      return "debug";
    case LogInternalVerbosityLevel::kInfo:
      return "info";
    case LogInternalVerbosityLevel::kWarning:
      return "warning";
    case LogInternalVerbosityLevel::kError:
      return "error";
    case LogInternalVerbosityLevel::kCritical:
      return "critical";
  }
  return "unknown";
}

std::ostream& operator<<(std::ostream& os,
                         const LogInternalVerbosityLevel value) {
  switch (value) {
    case LogInternalVerbosityLevel::kOff:
      return os << "off";
    case LogInternalVerbosityLevel::kDebug:
      return os << "debug";
    case LogInternalVerbosityLevel::kInfo:
      return os << "info";
    case LogInternalVerbosityLevel::kWarning:
      return os << "warning";
    case LogInternalVerbosityLevel::kError:
      return os << "error";
    case LogInternalVerbosityLevel::kCritical:
      return os << "critical";
  }
  return os;
}

bool TraceVerbIsDefault(const TraceVerbosityLevel flag) {
  return (flag == kLogTraceVerbDefault);
}
bool AbslParseFlag(absl::string_view text, TraceVerbosityLevel* flag,
                   std::string* error) {
  if (text == "trace") {
    *flag = TraceVerbosityLevel::kTrace;
    return true;
  } else if (text == "debug") {
    *flag = TraceVerbosityLevel::kDebug;
    return true;
  } else if (text == "info") {
    *flag = TraceVerbosityLevel::kInfo;
    return true;
  } else if (text == "warning") {
    *flag = TraceVerbosityLevel::kWarning;
    return true;
  } else if (text == "error") {
    *flag = TraceVerbosityLevel::kError;
    return true;
  } else if (text == "critical") {
    *flag = TraceVerbosityLevel::kCritical;
    return true;
  }
  *error =
      absl::StrCat("Value unknown! (", text,
                   ") Value must be one of \"trace\", \"debug\", \"info\", "
                   "\"warning\", \"error\", \"critical\"");
  return false;
}
std::string AbslUnparseFlag(const TraceVerbosityLevel& flag) {
  switch (flag) {
    case TraceVerbosityLevel::kTrace:
      return "trace";
    case TraceVerbosityLevel::kInfo:
      return "info";
    case TraceVerbosityLevel::kDebug:
      return "debug";
    case TraceVerbosityLevel::kWarning:
      return "warning";
    case TraceVerbosityLevel::kError:
      return "error";
    case TraceVerbosityLevel::kCritical:
      return "critical";
  }
  return "unknown";
}

std::ostream& operator<<(std::ostream& os, const TraceVerbosityLevel value) {
  switch (value) {
    case TraceVerbosityLevel::kTrace:
      return os << "trace";
    case TraceVerbosityLevel::kInfo:
      return os << "info";
    case TraceVerbosityLevel::kDebug:
      return os << "debug";
    case TraceVerbosityLevel::kWarning:
      return os << "warning";
    case TraceVerbosityLevel::kError:
      return os << "error";
    case TraceVerbosityLevel::kCritical:
      return os << "critical";
  }
  return os;
}

bool LogPoolSize::IsDefault() {
  return (pool_size == kLogPoolSizeDefault.pool_size);
}
bool AbslParseFlag(absl::string_view text, LogPoolSize* flag,
                   std::string* error) {
  if (!absl::ParseFlag(text, &flag->pool_size, error)) {
    return false;
  }
  if (flag->pool_size < LogPoolSize::kLogPoolSizeMin) {
    *error = absl::StrCat("Must have a value greater than ",
                          LogPoolSize::kLogPoolSizeMin, ".");
    return false;
  }
  return true;
}
std::string AbslUnparseFlag(const LogPoolSize& flag) {
  return absl::UnparseFlag(flag.pool_size);
}

bool LogHelp::IsDefault() { return (help == kLogHelpDefault.help); }
bool AbslParseFlag(absl::string_view text, LogHelp* flag, std::string* error) {
  if (!absl::ParseFlag(text, &flag->help, error)) {
    return false;
  }

  if (flag->help) {
    *error = kLogHelpTextGeneral;
    return false;
  }
  return true;
}
std::string AbslUnparseFlag(const LogHelp& flag) {
  return absl::UnparseFlag(flag.help);
}

bool LogAddress::IsDefault() { return (address == kLogAddressDefault.address); }
bool AbslParseFlag(absl::string_view text, LogAddress* flag,
                   std::string* error) {
  if (!absl::ParseFlag(text, &flag->address, error)) {
    return false;
  }
  if (flag->IsDefault()) {
    return true;
  }
  if (absl::GetFlag(FLAGS_log_sink) != LogSink::kBaical &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kAuto) {
    *error = absl::StrCat("May not be used with log_sink ",
                          absl::UnparseFlag(absl::GetFlag(FLAGS_log_sink)),
                          ".  Flag may only be used with log_sink=biacal or "
                          "log_sink=auto.");
    return false;
  }
  return true;
}
std::string AbslUnparseFlag(const LogAddress& flag) {
  return absl::UnparseFlag(flag.address);
}

bool LogPort::IsDefault() { return (port == kLogPortDefault.port); }
bool AbslParseFlag(absl::string_view text, LogPort* flag, std::string* error) {
  if (!absl::ParseFlag(text, &flag->port, error)) {
    return false;
  }
  if (flag->IsDefault()) {
    return true;
  }
  if (absl::GetFlag(FLAGS_log_sink) != LogSink::kBaical &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kAuto) {
    *error = absl::StrCat("May not be used with log_sink ",
                          absl::UnparseFlag(absl::GetFlag(FLAGS_log_sink)),
                          ".  Flag may only be used with log_sink=biacal or "
                          "log_sink=auto.");
    return false;
  }

  if (!(flag->port > 0 && flag->port <= LogPort::kPortMax)) {
    *error =
        absl::StrCat("Value must be between 0 and ", LogPort::kPortMax, ".  ");
    return false;
  }
  return false;
}
std::string AbslUnparseFlag(const LogPort& flag) {
  return absl::UnparseFlag(flag.port);
}

bool LogPacketSize::IsDefault() {
  return (packet_size == kLogPacketSizeDefault.packet_size);
}
bool AbslParseFlag(absl::string_view text, LogPacketSize* flag,
                   std::string* error) {
  if (!absl::ParseFlag(text, &flag->packet_size, error)) {
    return false;
  }
  if (flag->IsDefault()) {
    return true;
  }
  if (absl::GetFlag(FLAGS_log_sink) != LogSink::kBaical &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kAuto &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kSyslog) {
    *error = absl::StrCat("May not be used with log_sink ",
                          absl::UnparseFlag(absl::GetFlag(FLAGS_log_sink)),
                          ".  Flag may only be used with log_sink=biacal, "
                          "log_sink=syslog or log_sink=auto.");
    return false;
  }
  if (!(flag->packet_size >= LogPacketSize::kPacketSizeMin &&
        flag->packet_size <= LogPacketSize::kPacketSizeMax)) {
    *error =
        absl::StrCat("Value must be between ", LogPacketSize::kPacketSizeMin,
                     " and ", LogPacketSize::kPacketSizeMax, ".  ");
    return false;
  }
  return false;
}
std::string AbslUnparseFlag(const LogPacketSize& flag) {
  return absl::UnparseFlag(flag.packet_size);
}

bool LogWindow::IsDefault() { return (window == kLogWindowDefault.window); }
bool AbslParseFlag(absl::string_view text, LogWindow* flag,
                   std::string* error) {
  if (!absl::ParseFlag(text, &flag->window, error)) {
    return false;
  }
  if (flag->IsDefault()) {
    return true;
  }
  if (absl::GetFlag(FLAGS_log_sink) != LogSink::kBaical &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kAuto) {
    *error = absl::StrCat("May not be used with log_sink ",
                          absl::UnparseFlag(absl::GetFlag(FLAGS_log_sink)),
                          ".  Flag may only be used with log_sink=biacal "
                          "or log_sink=auto.");
    return false;
  }

  if (flag->window < LogWindow::kLogWindowSizeMin ||
      flag->window >
          static_cast<std::int32_t>(
              absl::GetFlag(FLAGS_log_pool_size).pool_size /
              absl::GetFlag(FLAGS_log_packet_size).packet_size / 2)) {
    *error =
        absl::StrCat("Value must be between ", LogWindow::kLogWindowSizeMin,
                     " and ", "(log_pool_size / log_packet_size) / 2 = (",
                     static_cast<std::int32_t>(
                         absl::GetFlag(FLAGS_log_pool_size).pool_size /
                         absl::GetFlag(FLAGS_log_packet_size).packet_size / 2),
                     ").");
    return false;
  }
  return true;
}
std::string AbslUnparseFlag(const LogWindow& flag) {
  return absl::UnparseFlag(flag.window);
}

bool LogEto::IsDefault() { return (eto == kLogEtoDefault.eto); }
bool AbslParseFlag(absl::string_view text, LogEto* flag, std::string* error) {
  if (!absl::ParseFlag(text, &flag->eto, error)) {
    return false;
  }
  if (flag->IsDefault()) {
    return true;
  }
  if (absl::GetFlag(FLAGS_log_sink) != LogSink::kBaical &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kAuto) {
    *error = absl::StrCat("May not be used with log_sink ",
                          absl::UnparseFlag(absl::GetFlag(FLAGS_log_sink)),
                          ".  Flag may only be used with log_sink=biacal "
                          "or log_sink=auto.");
    return false;
  }
  return true;
}
std::string AbslUnparseFlag(const LogEto& flag) {
  return absl::UnparseFlag(flag.eto);
}

bool LogFormat::IsDefault() { return (format == kLogFormatDefault.format); }
bool AbslParseFlag(absl::string_view text, LogFormat* flag,
                   std::string* error) {
  if (!absl::ParseFlag(text, &flag->format, error)) {
    return false;
  }
  if (absl::GetFlag(FLAGS_log_sink) != LogSink::kText &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kConsole &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kSyslog &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kAuto) {
    if (!flag->IsDefault()) {
      *error = absl::StrCat(
          "May not be used with log_sink ",
          absl::UnparseFlag(absl::GetFlag(FLAGS_log_sink)),
          ".  Flag may only be used with log_sink=text, log_sink=console, ",
          "log_sink=syslog, or log_sink=auto.");
      return false;
    }
  }

  const std::array format_strings = {"cn", "id", "ix", "tf", "tm", "ts", "td",
                                     "tc", "lv", "ti", "tn", "cc", "mi", "mn",
                                     "ff", "fs", "fl", "fn", "ms"};
  std::vector<size_t> positions{};
  size_t pos = flag->format.find("%");
  while (pos != std::string::npos) {
    positions.push_back(pos);
    pos = flag->format.find("%", pos + 1);
  }
  for (auto i : positions) {
    bool found_code = false;
    if ((i + 2) >= flag->format.length()) {
      *error =
          absl::StrCat(std::string(i + strlen("Invalid value: "), ' '),
                       std::string(flag->format.length() - i, '^'),
                       "\nFound format string delimiter character '%' too "
                       "close to end of string at position ",
                       i, ". \nNot enough room for format node to be valid.  ");
      return false;
    }
    for (auto format : format_strings) {
      if (flag->format[i + 1] == format[0] &&
          flag->format[i + 2] == format[1]) {
        found_code = true;
        break;
      }
    }
    if (!found_code) {
      *error = absl::StrCat("Invalid value:  '", flag->format, "'.\n",
                            std::string(i + strlen("Invalid value:  '"), ' '),
                            "^^^\nFound format string delimiter character '%' "
                            "followed by unknown sequence '",
                            flag->format.substr(i + 1, i + 2), "' .");
      return false;
    }
  }

  return true;
}
std::string AbslUnparseFlag(const LogFormat& flag) {
  return absl::UnparseFlag(flag.format);
}

bool LogFacility::IsDefault() {
  return (facility == kLogFacilityDefault.facility);
}
bool AbslParseFlag(absl::string_view text, LogFacility* flag,
                   std::string* error) {
  if (!absl::ParseFlag(text, &flag->facility, error)) {
    return false;
  }
  if (flag->IsDefault()) {
    return true;
  }
  if (absl::GetFlag(FLAGS_log_sink) != LogSink::kSyslog) {
    *error = absl::StrCat("May not be used with log_sink ",
                          absl::UnparseFlag(absl::GetFlag(FLAGS_log_sink)),
                          ".  Flag may only be used with log_sink=syslog.");
    return false;
  }
  return true;
}
std::string AbslUnparseFlag(const LogFacility& flag) {
  return absl::UnparseFlag(flag.facility);
}

bool LogDir::IsDefault() { return (dir == kLogDirDefault.dir); }
bool AbslParseFlag(absl::string_view text, LogDir* flag, std::string* error) {
  if (!absl::ParseFlag(text, &flag->dir, error)) {
    return false;
  }
  if (flag->IsDefault()) {
    return true;
  }
  if (absl::GetFlag(FLAGS_log_sink) != LogSink::kBinary &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kText &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kAuto) {
    *error = absl::StrCat("May not be used with log_sink ",
                          absl::UnparseFlag(absl::GetFlag(FLAGS_log_sink)),
                          ".  Flag may only be used with log_sink=text, "
                          "log_sink=binary or log_sink=auto.");
    return false;
  }
  return true;
}
std::string AbslUnparseFlag(const LogDir& flag) {
  return absl::UnparseFlag(flag.dir);
}

bool LogRoll::IsDefault() { return (roll == kLogRollDefault.roll); }
bool AbslParseFlag(absl::string_view text, LogRoll* flag, std::string* error) {
  if (!absl::ParseFlag(text, &flag->roll, error)) {
    return false;
  }
  if (flag->IsDefault()) {
    return true;
  }
  if (absl::GetFlag(FLAGS_log_sink) != LogSink::kBinary &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kText &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kAuto) {
    *error = absl::StrCat("May not be used with log_sink ",
                          absl::UnparseFlag(absl::GetFlag(FLAGS_log_sink)),
                          ".  Flag may only be used with log_sink=text, "
                          "log_sink=binary or log_sink=auto.");
    return false;
  }
  return true;
}
std::string AbslUnparseFlag(const LogRoll& flag) {
  return absl::UnparseFlag(flag.roll);
}

bool LogFiles::IsDefault() { return (files == kLogFilesDefault.files); }
bool AbslParseFlag(absl::string_view text, LogFiles* flag, std::string* error) {
  if (!absl::ParseFlag(text, &flag->files, error)) {
    return false;
  }
  if (flag->IsDefault()) {
    return true;
  }
  if (absl::GetFlag(FLAGS_log_sink) != LogSink::kBinary &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kText &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kAuto) {
    *error = absl::StrCat("May not be used with log_sink ",
                          absl::UnparseFlag(absl::GetFlag(FLAGS_log_sink)),
                          ".  Flag may only be used with log_sink=text, "
                          "log_sink=binary or log_sink=auto.");
    return false;
  }
  return true;
}
std::string AbslUnparseFlag(const LogFiles& flag) {
  return absl::UnparseFlag(flag.files);
}

bool LogFSize::IsDefault() { return (fsize == kLogFSizeDefault.fsize); }
bool AbslParseFlag(absl::string_view text, LogFSize* flag, std::string* error) {
  if (!absl::ParseFlag(text, &flag->fsize, error)) {
    return false;
  }
  if (flag->IsDefault()) {
    return true;
  }

  if (flag->fsize > LogFSize::kLogFSizeMax) {
    *error = absl::StrCat("Value must be between 0  and ",
                          LogFSize::kLogFSizeMax, ".  ");
    return false;
  }
  if (absl::GetFlag(FLAGS_log_sink) != LogSink::kBinary &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kText &&
      absl::GetFlag(FLAGS_log_sink) != LogSink::kAuto) {
    *error = absl::StrCat("May not be used with log_sink ",
                          absl::UnparseFlag(absl::GetFlag(FLAGS_log_sink)),
                          ".  Flag may only be used with log_sink=text, "
                          "log_sink=binary or log_sink=auto.");
    return false;
  }
  return true;
}
std::string AbslUnparseFlag(const LogFSize& flag) {
  return absl::UnparseFlag(flag.fsize);
}

} /* namespace logging::flags */
