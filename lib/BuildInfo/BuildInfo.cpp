#include "blop/BuildInfo/BuildInfo.h"
#include "GeneratedBuildInfo.h"
#include <string>

using namespace blop;

std::string BuildInfo::getGitHash()
{
  return std::string(BUILDINFO_GIT_HEAD);
}
