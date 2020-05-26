/******************************************************************************
 * Client.hpp
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
#ifndef SRC_LOGGERV2_CLIENT_HPP_
#define SRC_LOGGERV2_CLIENT_HPP_

#include <array>
#include <cstdarg>
#include <cstddef>
#include <string>

#include "P7_Client.h"
#include "absl/flags/flag.h"

namespace logging {

inline constexpr std::string_view kLogHeaderHelpText(
    R"raw(P7 Logging arguments:)raw");

inline constexpr std::string_view kLogGeneralHelpText(R"raw(
General arguments:)raw");
inline constexpr std::string_view kLogSinkHelpText(R"____raw____(
--log_sink        - Select data flow direction.
                    Availiable sinks:
                      * baical  - Write to Baical server over network
                                  (fast and efficient)
                      * binary  - Write to local binary file
                                  (fast and efficient)
                      * text    - Write to local text file
                                  (slow compared to binary/baical)
                      * syslog  - Write to syslog server
                                  (slow compared to binary/baical)
                      * console - Write to console
                                  (slow compared to binary/baical)
                      * auto    - Write to baical server if connection is
                                  established, otherwise write to text sink.
                                  Note: connection timeout is 250 ms!
                      * null    - Drop all incoming data
                    Default value is "baical"
                    Examples:
                      --log_sink=baical
                      --log_sink=text
                      --log_sink=null)____raw____");
inline constexpr std::string_view kLogNameHelpText(R"____raw____(
--log_name        - P7 client name. Max length is about 96 characters, by
                    default it is the name of the host process.
                    Example:
                      --log_name=Client)____raw____");
inline constexpr std::string_view kLoggingHelpText(R"____raw____(
--logging         - Enable/disable log engine. By default logging is on.
                    Examples:
                      --logging=true
                      --logging=false)____raw____");
inline constexpr std::string_view kLogIntVerbHelpText(R"____raw____(
--log_int_verb    - Set the log verbosity level. Allows writing internal P7
                    logs to a text file or to stdout.
                    Do not use --log_int_verb parameter to turn off
                    application logging, as it only affects internal logs.
                    Availiable verbosity levels:
                      -1 : Off
                       0 : Info
                       1 : Debug
                       2 : Warning
                       3 : Error
                       4 : Critical
                    Default value is "-1" (Off).
                    Example: --log_int_verb=0
                      On Linux all P7 internal logs will be redirected to
                      stdout, on Windows the folder "P7.Logs" will be
                      created in the host process folder and all further logs
                      will be stored there.)____raw____");
inline constexpr std::string_view kLogTraceVerbHelpText(R"____raw____(
--log_trace_verb  - Set the verbosity level for trace streams and associated
                    modules. Availiable verbosity levels:
                      0 : Trace
                      1 : Debug
                      2 : Info
                      3 : Warning
                      4 : Error
                      5 : Critical
                    Default value is "0" (Trace).
                    Example: --log_trace_verb=4)____raw____");
inline constexpr std::string_view kLogPoolSizeHelpText(R"____raw____(
--log_pool_size   - Set the size of the internal buffer pool in KiB.
                    Min value = 16(KiB). Max value is limited by OS and HW.
                    Default value = 4MiB.
                    Example:
                      16 KiB allocation: --log_pool_size=16
                       1 MiB allocation: --log_pool_size=1024
                       2 MiB allocation: --log_pool_size=2048
                       4 MiB allocation: --log_pool_size=4096
                       8 MiB allocation: --log_pool_size=8192
                      16 MiB allocation: --log_pool_size=16384
                      32 MiB allocation: --log_pool_size=32768
                      64 MiB allocation: --log_pool_size=65536)____raw____");
inline constexpr std::string_view kLogHelpHelpText(R"____raw____(
--log_help       - Print log help text and quit)____raw____");

inline constexpr std::string_view kLogBaicalSyslogHelpText(
    R"raw(
--log_sink=baical, --log_sink=syslog:)raw");

inline constexpr std::string_view kLogAddressHelpText(R"____raw____(
--log_address     - Set server address (IPV4, IPV6, NetBios name)
                    Examples:
                      --log_address=127.0.0.1
                      --log_address=::1
                      --log_address=MyPC
                    Default address is 127.0.0.1)____raw____");
inline constexpr std::string_view kLogPortHelpText(R"____raw____(
--log_port        - Set server port. Default port is 9009
                    Example: --log_port=9010)____raw____");
inline constexpr std::string_view kLogPacketSizeHelpText(R"____raw____(
--log_packet_size - Set packet size in bytes. Min value = 512 bytes.
                    Max value = 65535 bytes. Default value = 512 bytes.
                    You should specify optimum packet size for your network,
                    usually it is MTU.
                    Example: --log_packet_size=1476)____raw____");
inline constexpr std::string_view kLogWindowHelpText(R"____raw____(
--log_window      - Set the size of the transmission window in packets,
                    used to optimize transmission speed. Usually it is not
                    necessary to modify this parameter.
                    Min value = 1.
                    Max value = ((log_pool_size/log_packet_size size)/2).)____raw____");
inline constexpr std::string_view kLogEtoHelpText(R"____raw____(
--log_eto         - Set the transmission timeout (in seconds) when P7 object
                    has to be closed.
                    Example usage scenarios:
                      * Application sending data to Baical server through P7
                      * For some reason connection with Baical has been lost
                      * Some data is still inside P7 buffers and P7 tries to
                        deliver it
                      * Application was closed by user. "--log_eto" value is
                        used to specify time in
                         during which P7 will attempt to deliver
                        the remaining data.)____raw____");
inline constexpr std::string_view kLogBinaryTextHelpText(R"raw(
--log_sink=binary, --log_sink=text:)raw");
inline constexpr std::string_view kLogDirHelpText(R"____raw____(
--log_dir         - Directory where P7 files will be created, if it is
                    not specified process directory will be used.
                    Examples:
                      --log_dir=/home/user/logs/
                      --log_dir=C:\Logs\)____raw____");
inline constexpr std::string_view kLogFilesHelpText(R"____raw____(
--log_files       - Defines maximum number of log files in destination
                    folder. When the number of log files exceeds this
                    number, the oldest files will be deleted first.)____raw____");
inline constexpr std::string_view kLogRollHelpText(R"____raw____(
--log_roll        - Specify file rolling value & type. There are three
                    rolling types:
                      * Rolling by file size, measured in megabytes
                        ("mb" command postfix).
                      * Rolling by logging duration, measured in hours,
                        1000 hours max ("hr" command postfix).
                      * Rolling by exact time in hours and minutes
                        ("tm" command postfix), user can specify one or
                         many rolling times.
                    Rolling value consists of 2 parts:
                      * digit
                      * postfix: hr, mb, tm
                    Examples:
                      --log_roll=100mb
                      --log_roll=24hr
                      --log_roll=1hr
                      --log_roll=10:30tm
                      --log_roll=12:00,00:00tm
                      --log_roll=00:00,06:00,12:00,18:00tm)____raw____");
inline constexpr std::string_view kLogFSizeHelpText(R"____raw____(
--log_fsize       - Define the maximum P7 log file cumulative size in MiB
                    for the destination folder.)____raw____");
inline constexpr std::string_view kLogTextConsoleSyslogHelpText(R"raw(
--log_sink=text, --log_sink=console, --log_sink=syslog:)raw");
inline constexpr std::string_view kLogFormatHelpText(R"____raw____(
--log_format      - Set the log message format string.
                    Example:
                      Input:   --log_format="{%cn} [%ts] %lv %ms"
                      Outputs: {c_name} [45.23.392.123.245] error Message
                    Availiable format specifiers:
                      * "%cn" - channel name
                      * "%id" - message ID
                      * "%ix" - message index
                      * "%tf" - full time
                                  YY.MM.DD HH.MM.SS.mils.mics.nans
                      * "%tm" - time medium
                                  HH.MM.SS.mils.mics.nans
                      * "%ts" - time short
                                  MM.SS.mils.mics.nans
                      * "%td" - time difference between current and prev.
                                  +SS.mils.mics.nans
                      * "%tc" - time stamp in 100 nanoseconds intervals
                      * "%lv" - level (error, warning, etc)
                      * "%ti" - thread ID
                      * "%tn" - thread name
                      * "%cc" - CPU core
                      * "%mi" - module ID
                      * "%mn" - module name
                      * "%ff" - file path + name
                      * "%fs" - file name
                      * "%fl" - file line
                      * "%fn" - function name
                      * "%ms" - message)____raw____");
inline constexpr std::string_view kLogFacilityHelpText(R"____raw____(
--log_facility    - Set the Syslog facility, for more details see:
                    https://tools.ietf.org/html/rfc3164#page-8)____raw____");

namespace detail {
template <typename T>
static inline std::string ReplaceAllInString(const T& data,
                                             const std::string& to_search,
                                             const std::string& replace_str) {
  std::string copy = std::string(data);
  size_t pos = copy.find(to_search);
  while (pos != std::string::npos) {
    copy.replace(pos, to_search.size(), replace_str);
    // Get the next occurrence
    pos = copy.find(to_search, pos + replace_str.size());
  }
  return copy;
}
} /* namespace detail */

inline const std::string kLogHelpTextGeneral =
    std::string(::logging::kLogGeneralHelpText) +
    detail::ReplaceAllInString(::logging::kLogSinkHelpText, "\n", "\n  ") +
    detail::ReplaceAllInString(::logging::kLogNameHelpText, "\n", "\n  ") +
    detail::ReplaceAllInString(::logging::kLoggingHelpText, "\n", "\n  ") +
    detail::ReplaceAllInString(::logging::kLogIntVerbHelpText, "\n", "\n  ") +
    detail::ReplaceAllInString(::logging::kLogTraceVerbHelpText, "\n", "\n  ") +
    detail::ReplaceAllInString(::logging::kLogPoolSizeHelpText, "\n", "\n  ") +
    detail::ReplaceAllInString(::logging::kLogHelpHelpText, "\n", "\n  ");

inline const std::string kLogHelpTextBaicalSyslog =
    std::string(::logging::kLogBaicalSyslogHelpText) +
    detail::ReplaceAllInString(::logging::kLogAddressHelpText, "\n", "\n  ") +
    detail::ReplaceAllInString(::logging::kLogPortHelpText, "\n", "\n  ") +
    detail::ReplaceAllInString(::logging::kLogPacketSizeHelpText, "\n",
                               "\n  ") +
    detail::ReplaceAllInString(::logging::kLogWindowHelpText, "\n", "\n  ") +
    detail::ReplaceAllInString(::logging::kLogEtoHelpText, "\n", "\n  ");

inline const std::string kLogHelpTextBinaryText =
    std::string(::logging::kLogBinaryTextHelpText) +
    detail::ReplaceAllInString(::logging::kLogDirHelpText, "\n", "\n  ") +
    detail::ReplaceAllInString(::logging::kLogFilesHelpText, "\n", "\n  ") +
    detail::ReplaceAllInString(::logging::kLogRollHelpText, "\n", "\n  ") +
    detail::ReplaceAllInString(::logging::kLogFSizeHelpText, "\n", "\n  ");

inline const std::string kLogHelpTextTextConsoleSyslog =
    std::string(::logging::kLogTextConsoleSyslogHelpText) +
    detail::ReplaceAllInString(::logging::kLogFormatHelpText, "\n", "\n  ") +
    detail::ReplaceAllInString(::logging::kLogFacilityHelpText, "\n", "\n  ");

inline const std::string kLogHelpTextAll =
    std::string(::logging::kLogHeaderHelpText) +
    detail::ReplaceAllInString(::logging::kLogHelpTextGeneral, "\n", "\n  ") +
    detail::ReplaceAllInString(::logging::kLogHelpTextBaicalSyslog, "\n",
                               "\n  ") +
    detail::ReplaceAllInString(::logging::kLogHelpTextBinaryText, "\n",
                               "\n  ") +
    detail::ReplaceAllInString(::logging::kLogHelpTextTextConsoleSyslog, "\n",
                               "\n  ");

class Client {
 public:
  Client() noexcept = default;
  Client& operator=(const Client& rhs) = default;
  Client(const Client& rhs) = default;
  Client& operator=(Client&& rhs) noexcept = default;
  Client(Client&& rhs) noexcept = default;

  explicit Client(const std::string name);

  ~Client() noexcept;

  IP7_Client* client() { return client_; }

 private:
  void RegisterUnixCrashHandlers();
  void RegisterWindowsCrashHandlers();
  std::string CreateClientConfig();

  IP7_Client* client_ = nullptr;
};

} /* namespace logging */

#endif  // SRC_LOGGERV2_CLIENT_HPP_
