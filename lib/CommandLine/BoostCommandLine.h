// implement CommandLine using Boost.program_options
#ifndef BLOP_COMMANDLINE_BOOSTCOMMANDLINE_H
#define BLOP_COMMANDLINE_BOOSTCOMMANDLINE_H

#include "blop/CommandLine/CommandLine.h"

#include <boost/program_options.hpp>

namespace blop
{

class BoostCommandLine: public CommandLine
{
public:
  virtual ~BoostCommandLine() = default;

  virtual void addOption(enum ArgumentType argType,
                         const std::string& optionName,
                         const std::string& optionNameShort,
                         const std::string& optionDescription,
                         bool mandatory) override;

  virtual bool parseArguments(int argc, char* argv[],
                              std::string& error) override;

  virtual std::string getHelp(const std::string& programName) const override;

  virtual bool isOptionSet(const std::string& optionName) const override;

  virtual bool getOnePositiveIntOption(const std::string& optionName,
                                       unsigned int& value) const override;
  virtual bool getOneStringOption(const std::string& optionName,
                                  std::string& value) const override;

private:
  boost::program_options::options_description options_;
  boost::program_options::variables_map values_;
};

}

#endif
