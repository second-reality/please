#include "BoostLogger.h"

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>

using namespace blop;

void BoostLogger::log(enum LogLevel level, const std::string& message)
{
  if (!fileOutputActive_)
    return;

  switch (level)
  {
    case Logger::LogLevel::Info:
      BOOST_LOG_TRIVIAL(info) << message;
      break;
    case Logger::LogLevel::Debug:
      BOOST_LOG_TRIVIAL(debug) << message;
      break;
    case Logger::LogLevel::Error:
      BOOST_LOG_TRIVIAL(error) << message;
      break;
    case Logger::LogLevel::Warning:
      BOOST_LOG_TRIVIAL(warning) << message;
      break;
  }
}

void BoostLogger::setLogFile(const std::string& path)
{
  boost::log::add_file_log(path); 
  fileOutputActive_ = true;
}

void BoostLogger::activateDebug()
{
  debug_ = true;
}

bool BoostLogger::isDebugActivated() const
{
  return debug_;
}

BoostLogger::BoostLogger(): debug_(false),
                            fileOutputActive_(false)
{
}

BoostLogger& BoostLogger::getGlobalBoostLogger()
{
  static BoostLogger logger;
  return logger;
}
