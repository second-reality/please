// Command line handling library

#ifndef BLOP_COMMANDLINE_COMMANDLINE_H
#define BLOP_COMMANDLINE_COMMANDLINE_H

#include <memory>
#include <string>

namespace blop
{

class CommandLine
{
public:
  virtual ~CommandLine() = default;

  // type of argument for one option
  enum class ArgumentType
  {
    None,
    OnePositiveInt,
    OneString
  };

  // register an option for CommandLine with arguments @argType, named
  // @optionName and with short name @optionNameShort (may be empty),
  // and a description of help @optionDescription. If option must be precised by
  // user, @mandatory must be true.
  virtual void addOption(enum ArgumentType argType,
                         const std::string& optionName,
                         const std::string& optionNameShort,
                         const std::string& optionDescription,
                         bool mandatory) = 0;

  // Parse arguments in @argv. Return true if no error is found.
  // If error is found, @error contains it.
  virtual bool parseArguments(int argc, char* argv[],
                              std::string& error) = 0;

  // return help for CommandLine
  virtual std::string getHelp(const std::string& programName) const = 0;

  // return true if option @optionName is set by user
  virtual bool isOptionSet(const std::string& optionName) const = 0;

  // get value associated to one option @optionName.
  // If option is not of the good ArgumentType, return false.
  // If option is not set, return false.
  virtual bool getOnePositiveIntOption(const std::string& optionName,
                                       unsigned int& value) const = 0;
  virtual bool getOneStringOption(const std::string& optionName,
                                  std::string& value) const = 0;

  // factory for commandLine
  static std::unique_ptr<CommandLine> makeCommandLine();
};

}

#endif
