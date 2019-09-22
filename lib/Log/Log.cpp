#include "blop/Log/Log.h"

#include "BoostLogger.h"

using namespace blop;

Logger& Logger::getGlobalLogger()
{
  return BoostLogger::getGlobalBoostLogger();
}
