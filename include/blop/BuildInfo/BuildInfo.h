/// Provides information about build (git version, ...)

#ifndef BLOP_BUILDINFO_BUILDINFO_H
#define BLOP_BUILDINFO_BUILDINFO_H

#include <string>

namespace blop
{
class BuildInfo
{
public:
  BuildInfo() = delete;
  
  static std::string getGitHash();
};
}

#endif
