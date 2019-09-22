#include "blop/CommandLine/CommandLine.h"

#include "BoostCommandLine.h"

using namespace blop;

std::unique_ptr<CommandLine> CommandLine::makeCommandLine()
{
  return std::make_unique<BoostCommandLine>();
}
