/******************************************************************************
 * Client.cpp
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

#include "LoggerV2/Client.hpp"

#include <array>
#include <cstring>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/algorithm/string/trim.hpp>

#include "absl/flags/flag.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/string_view.h"

#include "LoggerV2/Flags.hpp"
#include "LoggerV2/Log.hpp"

#if defined(unix) || defined(__unix__) || defined(__unix)
#define PREDEF_PLATFORM_UNIX
#endif /* unix */

#if defined(_WIN32)
#define PREDEF_PLATFORM_WINDOWS
#endif /* WIN32 */

#ifdef PREDEF_PLATFORM_UNIX
#include <signal.h>
#include <unistd.h>
#endif /* PREDEF_PLATFORM_UNIX */

#ifdef PREDEF_PLATFORM_WINDOWS
#endif /* PREDEF_PLATFORM_WINDOWS */

ABSL_FLAG(::logging::flags::LogSink, log_sink,
          ::logging::flags::kLogSinkDefault,
          "Sink to use for P7 logging client.");

ABSL_FLAG(::logging::flags::LogName, log_name,
          ::logging::flags::kLogNameDefault,
          "Name to use for p7 client instance.");

ABSL_FLAG(::logging::flags::LoggingEnabled, logging,
          ::logging::flags::kLoggingDefault, "Enable/disable logging with p7.");

ABSL_FLAG(::logging::flags::LogInternalVerbosityLevel, log_int_verb,
          ::logging::flags::kLogIntVerbDefault,
          "Internal log level for P7 logging client.");

ABSL_FLAG(::logging::flags::TraceVerbosityLevel, log_trace_verb,
          ::logging::flags::kLogTraceVerbDefault,
          "Trace log level for trace logging channels.");

ABSL_FLAG(::logging::flags::LogPoolSize, log_pool_size,
          ::logging::flags::kLogPoolSizeDefault,
          "Size of memory pool to use for logging.");

ABSL_FLAG(::logging::flags::LogHelp, log_help,
          ::logging::flags::kLogHelpDefault, "Show P7 log help.  ");

ABSL_FLAG(::logging::flags::LogAddress, log_address,
          ::logging::flags::kLogAddressDefault, "What address to log.");

ABSL_FLAG(::logging::flags::LogPort, log_port,
          ::logging::flags::kLogPortDefault,
          "What port for log server to listen on.");

ABSL_FLAG(::logging::flags::LogPacketSize, log_packet_size,
          ::logging::flags::kLogPacketSizeDefault,
          "Size of log packets in bytes.");

ABSL_FLAG(::logging::flags::LogWindow, log_window,
          ::logging::flags::kLogWindowDefault,
          "Size of log transmission window in packets, used to"
          " optimize transmission speed.  Advanced.  ");

ABSL_FLAG(::logging::flags::LogEto, log_eto, ::logging::flags::kLogEtoDefault,
          "Transmission timeout in seconds before P7 log object "
          "has to be closed.  ");

ABSL_FLAG(
    ::logging::flags::LogFormat, log_format,
    ::logging::flags::kLogFormatDefault,
    "Log item format string for text sinks. See --log_help for more info.");

ABSL_FLAG(::logging::flags::LogFacility, log_facility,
          ::logging::flags::kLogFacilityDefault,
          "Syslog facility to use for syslog sink.");

ABSL_FLAG(::logging::flags::LogDir, log_dir, ::logging::flags::kLogDirDefault,
          "Log directory to create log files in.");

ABSL_FLAG(::logging::flags::LogRoll, log_roll,
          ::logging::flags::kLogRollDefault, "File rolling options and type.");

ABSL_FLAG(::logging::flags::LogFiles, log_files,
          ::logging::flags::kLogFilesDefault,
          "Defines maximum number of log files in destination "
          "folder.");

ABSL_FLAG(::logging::flags::LogFSize, log_fsize,
          ::logging::flags::kLogFSizeDefault,
          "Defines maximum cumulative total size of log files in "
          "destination folder. ");

namespace logging {

#ifdef PREDEF_PLATFORM_UNIX
extern "C" void HandleUnixSigAbrt([[maybe_unused]] int sig,
                                  [[maybe_unused]] siginfo_t* siginfo,
                                  [[maybe_unused]] void* context) {
  P7_Exceptional_Flush();
  std::exit(EXIT_SUCCESS);
}
extern "C" void HandleUnixSigBus([[maybe_unused]] int sig,
                                 [[maybe_unused]] siginfo_t* siginfo,
                                 [[maybe_unused]] void* context) {
  P7_Exceptional_Flush();
  std::exit(EXIT_SUCCESS);
}
extern "C" void HandleUnixSigFpe([[maybe_unused]] int sig,
                                 [[maybe_unused]] siginfo_t* siginfo,
                                 [[maybe_unused]] void* context) {
  P7_Exceptional_Flush();
  std::exit(EXIT_SUCCESS);
}
extern "C" void HandleUnixSigHup([[maybe_unused]] int sig,
                                 [[maybe_unused]] siginfo_t* siginfo,
                                 [[maybe_unused]] void* context) {
  P7_Exceptional_Flush();
  std::exit(EXIT_SUCCESS);
}
extern "C" void HandleUnixSigIll([[maybe_unused]] int sig,
                                 [[maybe_unused]] siginfo_t* siginfo,
                                 [[maybe_unused]] void* context) {
  P7_Exceptional_Flush();
  std::exit(EXIT_SUCCESS);
}
extern "C" void HandleUnixSigInt([[maybe_unused]] int sig,
                                 [[maybe_unused]] siginfo_t* siginfo,
                                 [[maybe_unused]] void* context) {
  P7_Exceptional_Flush();
  std::exit(EXIT_SUCCESS);
}
extern "C" void HandleUnixSigPipe([[maybe_unused]] int sig,
                                  [[maybe_unused]] siginfo_t* siginfo,
                                  [[maybe_unused]] void* context) {
  P7_Exceptional_Flush();
  std::exit(EXIT_SUCCESS);
}
extern "C" void HandleUnixSigPwr([[maybe_unused]] int sig,
                                 [[maybe_unused]] siginfo_t* siginfo,
                                 [[maybe_unused]] void* context) {
  P7_Exceptional_Flush();
  std::exit(EXIT_SUCCESS);
}
extern "C" void HandleUnixSigQuit([[maybe_unused]] int sig,
                                  [[maybe_unused]] siginfo_t* siginfo,
                                  [[maybe_unused]] void* context) {
  P7_Exceptional_Flush();
  std::exit(EXIT_SUCCESS);
}
extern "C" void HandleUnixSigSegv([[maybe_unused]] int sig, siginfo_t* siginfo,
                                  [[maybe_unused]] void* context) {
  ::logging::Log log = ::logging::Log("main");
  log.Critical("Segmentation fault!");
  log.Error("siginfo->si_addr  = {}", siginfo->si_addr);
  log.Error("siginfo->si_errno = {}", siginfo->si_errno);
  log.Error("siginfo->si_code  = {}", siginfo->si_code);
  P7_Exceptional_Flush();
  std::exit(EXIT_SUCCESS);
}
extern "C" void HandleUnixSigTstp([[maybe_unused]] int sig,
                                  [[maybe_unused]] siginfo_t* siginfo,
                                  [[maybe_unused]] void* context) {
  P7_Exceptional_Flush();
  std::exit(EXIT_SUCCESS);
}
extern "C" void HandleUnixSigSys([[maybe_unused]] int sig,
                                 [[maybe_unused]] siginfo_t* siginfo,
                                 [[maybe_unused]] void* context) {
  P7_Exceptional_Flush();
  std::exit(EXIT_SUCCESS);
}
extern "C" void HandleUnixSigTerm([[maybe_unused]] int sig,
                                  [[maybe_unused]] siginfo_t* siginfo,
                                  [[maybe_unused]] void* context) {
  P7_Exceptional_Flush();
  std::exit(EXIT_SUCCESS);
}
extern "C" void HandleUnixSigXcpu([[maybe_unused]] int sig,
                                  [[maybe_unused]] siginfo_t* siginfo,
                                  [[maybe_unused]] void* context) {
  P7_Exceptional_Flush();
  std::exit(EXIT_SUCCESS);
}
extern "C" void HandleUnixSigXfsz([[maybe_unused]] int sig,
                                  [[maybe_unused]] siginfo_t* siginfo,
                                  [[maybe_unused]] void* context) {
  P7_Exceptional_Flush();
  std::exit(EXIT_SUCCESS);
}

void Client::RegisterUnixCrashHandlers() {
  struct sigaction action {};
  action.sa_flags = SA_SIGINFO;

  action.sa_sigaction = &HandleUnixSigAbrt;
  if (sigaction(SIGABRT, &action, nullptr) < 0) {
    throw std::runtime_error("Signal handler registration failed for SIGABRT");
  }

  action.sa_sigaction = &HandleUnixSigBus;
  if (sigaction(SIGBUS, &action, nullptr) < 0) {
    throw std::runtime_error("Signal handler registration failed for SIGBUS");
  }

  action.sa_sigaction = &HandleUnixSigFpe;
  if (sigaction(SIGFPE, &action, nullptr) < 0) {
    throw std::runtime_error("Signal handler registration failed for SIGFPE");
  }

  action.sa_sigaction = &HandleUnixSigHup;
  if (sigaction(SIGHUP, &action, nullptr) < 0) {
    throw std::runtime_error("Signal handler registration failed for SIGHUP");
  }

  action.sa_sigaction = &HandleUnixSigIll;
  if (sigaction(SIGILL, &action, nullptr) < 0) {
    throw std::runtime_error("Signal handler registration failed for SIGILL");
  }

  action.sa_sigaction = &HandleUnixSigInt;
  if (sigaction(SIGINT, &action, nullptr) < 0) {
    throw std::runtime_error("Signal handler registration failed for SIGINT");
  }

  action.sa_sigaction = &HandleUnixSigPipe;
  if (sigaction(SIGPIPE, &action, nullptr) < 0) {
    throw std::runtime_error("Signal handler registration failed for SIGPIPE");
  }

  action.sa_sigaction = &HandleUnixSigPwr;
  if (sigaction(SIGPWR, &action, nullptr) < 0) {
    throw std::runtime_error("Signal handler registration failed for SIGPWR");
  }

  action.sa_sigaction = &HandleUnixSigQuit;
  if (sigaction(SIGQUIT, &action, nullptr) < 0) {
    throw std::runtime_error("Signal handler registration failed for SIGQUIT");
  }

  action.sa_sigaction = &HandleUnixSigSegv;
  if (sigaction(SIGSEGV, &action, nullptr) < 0) {
    throw std::runtime_error("Signal handler registration failed for SIGSEGV");
  }

  action.sa_sigaction = &HandleUnixSigTstp;
  if (sigaction(SIGTSTP, &action, nullptr) < 0) {
    throw std::runtime_error("Signal handler registration failed for SIGTSTP");
  }

  action.sa_sigaction = &HandleUnixSigSys;
  if (sigaction(SIGSYS, &action, nullptr) < 0) {
    throw std::runtime_error("Signal handler registration failed for SIGSYS");
  }

  action.sa_sigaction = &HandleUnixSigTerm;
  if (sigaction(SIGTERM, &action, nullptr) < 0) {
    throw std::runtime_error("Signal handler registration failed for SIGTERM");
  }

  action.sa_sigaction = &HandleUnixSigXcpu;
  if (sigaction(SIGXCPU, &action, nullptr) < 0) {
    throw std::runtime_error("Signal handler registration failed for SIGXCPU");
  }

  action.sa_sigaction = &HandleUnixSigXfsz;
  if (sigaction(SIGXFSZ, &action, nullptr) < 0) {
    throw std::runtime_error("Signal handler registration failed for SIGXFSZ");
  }
}
#endif /* PREDEF_PLATFORM_UNIX */

#ifdef PREDEF_PLATFORM_WINDOWS
extern "C" void HandleWindowsCrash() { P7_Exceptional_Flush(); }
void Client::RegisterWindowsCrashHandlers() { P7_Set_Crash_Handler(); }
#endif /* PREDEF_PLATFORM_WINDOWS */

std::string Client::CreateClientConfig() {
  std::string client_params{};
  std::string sink_name{};
  if (absl::GetFlag(FLAGS_log_sink) == flags::LogSink::kBaical) {
    sink_name = "Baical";
  } else if (absl::GetFlag(FLAGS_log_sink) == flags::LogSink::kBinary) {
    sink_name = "FileBin";
  } else if (absl::GetFlag(FLAGS_log_sink) == flags::LogSink::kText) {
    sink_name = "FileTxt";
  } else if (absl::GetFlag(FLAGS_log_sink) == flags::LogSink::kSyslog) {
    sink_name = "Syslog";
  } else if (absl::GetFlag(FLAGS_log_sink) == flags::LogSink::kConsole) {
    sink_name = "Console";
  } else if (absl::GetFlag(FLAGS_log_sink) == flags::LogSink::kAuto) {
    sink_name = "Auto";
  } else if (absl::GetFlag(FLAGS_log_sink) == flags::LogSink::kNull) {
    sink_name = "Null";
  } else {
    sink_name = flags::AbslUnparseFlag(absl::GetFlag(FLAGS_log_sink));
  }
  absl::StrAppend(&client_params, "/P7.Sink=", sink_name, " ");
  if (!absl::GetFlag(FLAGS_log_name).IsDefault()) {
    absl::StrAppend(&client_params,
                    "/P7.Name=", absl::GetFlag(FLAGS_log_name).name, " ");
  }
  if (!absl::GetFlag(FLAGS_logging).IsDefault()) {
    absl::StrAppend(&client_params, "/P7.On=",
                    std::to_string(absl::GetFlag(FLAGS_logging).enabled), " ");
  }
  if (!flags::LogIntVerbIsDefault(absl::GetFlag(FLAGS_log_int_verb))) {
    absl::StrAppend(&client_params,
                    "/P7.Verb=" + std::to_string(static_cast<std::int32_t>(
                                      absl::GetFlag(FLAGS_log_int_verb))),
                    " ");
  }
  if (!absl::GetFlag(FLAGS_log_window).IsDefault()) {
    absl::StrAppend(
        &client_params, "/P7.Pool=",
        std::to_string(absl::GetFlag(FLAGS_log_pool_size).pool_size), " ");
  }

  if (!absl::GetFlag(FLAGS_log_address).IsDefault()) {
    absl::StrAppend(&client_params,
                    "/P7.Addr=", absl::GetFlag(FLAGS_log_address).address, " ");
  }
  if (!absl::GetFlag(FLAGS_log_port).IsDefault()) {
    absl::StrAppend(&client_params, "/P7.Port=",
                    std::to_string(absl::GetFlag(FLAGS_log_port).port), " ");
  }
  if (!absl::GetFlag(FLAGS_log_packet_size).IsDefault()) {
    absl::StrAppend(
        &client_params, "/P7.PSize=",
        std::to_string(absl::GetFlag(FLAGS_log_packet_size).packet_size), " ");
  }
  if (!absl::GetFlag(FLAGS_log_window).IsDefault()) {
    absl::StrAppend(&client_params, "/P7.Window=",
                    std::to_string(absl::GetFlag(FLAGS_log_window).window),
                    " ");
  }
  if (!absl::GetFlag(FLAGS_log_eto).IsDefault()) {
    absl::StrAppend(&client_params, "/P7.Eto=",
                    std::to_string(absl::GetFlag(FLAGS_log_eto).eto), " ");
  }
  if (!absl::GetFlag(FLAGS_log_format).IsDefault()) {
    absl::StrAppend(&client_params, "/P7.Format=\"",
                    absl::GetFlag(FLAGS_log_format).format, "\" ");
  }
  if (!absl::GetFlag(FLAGS_log_facility).IsDefault()) {
    absl::StrAppend(&client_params, "/P7.Facility=",
                    std::to_string(absl::GetFlag(FLAGS_log_facility).facility),
                    " ");
  }
  if (!absl::GetFlag(FLAGS_log_dir).IsDefault()) {
    absl::StrAppend(&client_params,
                    "/P7.Dir=", absl::GetFlag(FLAGS_log_dir).dir, " ");
  }
  if (!absl::GetFlag(FLAGS_log_roll).IsDefault()) {
    absl::StrAppend(&client_params,
                    "/P7.Roll=", absl::GetFlag(FLAGS_log_roll).roll, " ");
  }
  if (!absl::GetFlag(FLAGS_log_files).IsDefault()) {
    absl::StrAppend(&client_params, "/P7.Files=",
                    std::to_string(absl::GetFlag(FLAGS_log_files).files), " ");
  }
  if (!absl::GetFlag(FLAGS_log_fsize).IsDefault()) {
    absl::StrAppend(&client_params, "/P7.FSize=",
                    std::to_string(absl::GetFlag(FLAGS_log_fsize).fsize), " ");
  }

  boost::algorithm::trim(client_params);
  return client_params;
}

Client::Client(const std::string name) {
  using namespace std::literals::string_literals;

  if ((client_ = P7_Get_Shared(name.c_str())) == nullptr) {
#ifdef PREDEF_PLATFORM_UNIX
    RegisterUnixCrashHandlers();
#endif /* PREDEF_PLATFORM_UNIX */

#ifdef PREDEF_PLATFORM_WINDOWS
    RegisterWindowsCrashHandlers();
#endif /* PREDEF_PLATFORM_WINDOWS */
    std::string client_params = CreateClientConfig();

    if ((client_ = P7_Create_Client(client_params.c_str())) == nullptr) {
      std::cerr << "P7_Create_Client failed" << std::endl;
      throw std::runtime_error("P7_Create_Client failed");
      return;
    }
    if (!client_->Share(name.c_str())) {
      throw std::runtime_error("client_->Share("s + name + ") failed."s);
    }
    // Intentionally increase ref counter so that the logger isn't created
    // and destroyed constantly and to enable log support for crashes
    client_->Add_Ref();
  }
}

Client::~Client() noexcept {
  if (client_ != nullptr) {
    client_->Release();
  }
}

} /* namespace logging */
