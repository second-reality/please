#ifndef BLOP_LOG_BOOSTLOGGER_H
#define BLOP_LOG_BOOSTLOGGER_H

#include "blop/Log/Log.h"

namespace blop
{

class BoostLogger: public Logger
{
public:
  virtual ~BoostLogger() = default;

  virtual void log(enum LogLevel level, const std::string& message) override;
  virtual void setLogFile(const std::string& path) override;
  virtual void activateDebug() override;
  virtual bool isDebugActivated() const override;

  static BoostLogger& getGlobalBoostLogger();
private:
  BoostLogger();
  bool debug_;
  bool fileOutputActive_;
};

}

#endif
