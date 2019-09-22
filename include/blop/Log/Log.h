// A log library

#ifndef BLOP_LOG_LOG_H
#define BLOP_LOG_LOG_H

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

// internal macro to log with a specific level
#define BLOP_LOG_WITH_LEVEL__(level, M)                                       \
  do {                                                                        \
    std::ostringstream stream;                                                \
    std::time_t now =                                                         \
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()); \
    stream <<                                                                 \
      "[" << std::put_time(std::localtime(&now), "%D %H:%M:%S") << "] " << M; \
    const std::string& str = stream.str();                                    \
    std::cout << str << '\n';                                                 \
    blop::Logger::getGlobalLogger().log(level, str);                          \
  } while (0)

// macros to use for logging
#define BLOP_LOG_INFO(M)\
  BLOP_LOG_WITH_LEVEL__(blop::Logger::LogLevel::Info, "[info] " << M)
#define BLOP_LOG_ERROR(M)\
  BLOP_LOG_WITH_LEVEL__(blop::Logger::LogLevel::Error, "[error] " << M)
#define BLOP_LOG_WARNING(M)\
  BLOP_LOG_WITH_LEVEL__(blop::Logger::LogLevel::Warning, "[warning] " << M)
// Logging debug has no cost when debug is not activated (message string is not
// constructed)
#define BLOP_LOG_DEBUG(M)                                                    \
  do {                                                                       \
    if (blop::Logger::getGlobalLogger().isDebugActivated())                  \
    {                                                                        \
      BLOP_LOG_WITH_LEVEL__(blop::Logger::LogLevel::Debug, "[debug] " << M); \
    }                                                                        \
  } while (0)

namespace blop
{

// Interface for logger
// By default, no file is set for logging, debug is deactivated and all log is
// made on std::cout as well.
class Logger
{
public:
  // level of logging
  enum class LogLevel
  {
    Info,
    Error,
    Warning,
    Debug
  };

  virtual ~Logger() = default;

  // log a @message of a given @level
  // \n is automatically added.
  virtual void log(enum LogLevel level, const std::string& message) = 0;

  // change file for log by using @path
  virtual void setLogFile(const std::string& path) = 0;
  virtual void activateDebug() = 0;
  virtual bool isDebugActivated() const = 0;

  // return a reference to log object to use
  static Logger& getGlobalLogger();
};

}

#endif
