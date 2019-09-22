#include "BoostCommandLine.h"

#include "blop/BuildInfo/BuildInfo.h"

#include <sstream>

using namespace blop;

template<typename T>
static auto boostOptionValue(bool mandatory)
{
  auto res = boost::program_options::value<T>();
  if (mandatory)
  {
    res->required();
  }
  return res;
}

template<typename T>
static bool getValueForOption(const std::string& optionName,
                              const boost::program_options::variables_map& vm,
                              T& value)
{
  try
  {
    value = vm[optionName].as<T>();
    return true;
  }
  catch (...)
  {
   return false;
  }
}

void BoostCommandLine::addOption(enum ArgumentType argType,
                                 const std::string& optionName,
                                 const std::string& optionNameShort,
                                 const std::string& optionDescription,
                                 bool mandatory)
{
  if (optionName.empty())
    return;

  std::string namesString = optionName;
  if (!optionNameShort.empty())\
  {
    namesString += ",";
    namesString += optionNameShort;
  }

  switch (argType)
  {
    case ArgumentType::None:
      options_.add_options()(namesString.c_str(), optionDescription.c_str());
      break;
    case ArgumentType::OneString:
      options_.add_options()(namesString.c_str(),
                             boostOptionValue<std::string>(mandatory),
                             optionDescription.c_str());
      break;
    case ArgumentType::OnePositiveInt:
      options_.add_options()(namesString.c_str(),
                             boostOptionValue<unsigned int>(mandatory),
                             optionDescription.c_str());
      break;
  };
}

bool BoostCommandLine::parseArguments(int argc, char* argv[],
                                      std::string& error)
{
  try
  {
    // do not allow positional parameters
    boost::program_options::positional_options_description empty;

    boost::program_options::store(
      boost::program_options::command_line_parser(argc, argv).
        options(options_).
        positional(empty).
        run(),
        values_
      );
    boost::program_options::notify(values_);
    return true;
  }
  catch(boost::program_options::unknown_option& e)
  {
    error = e.get_option_name();
  }
  catch(boost::program_options::required_option& e)
  {
    error = "option " + e.get_option_name() + " is required";
  }
  catch(boost::program_options::invalid_command_line_syntax& e)
  {
    error = "option " + e.get_option_name() + " needs argument";
  }
  catch(boost::program_options::invalid_option_value& e)
  {
    error = "option " + e.get_option_name() + " has invalid argument";
  }
  return false;
}

std::string BoostCommandLine::getHelp(const std::string& programName) const
{
  std::string help;
  std::stringstream stream;
  stream << "help for " << programName << '\n';
  stream << "program built from git " << BuildInfo::getGitHash() << '\n';
  stream << options_;
  return stream.str();
}

bool BoostCommandLine::isOptionSet(const std::string& optionName) const
{
  return values_.count(optionName);
}

bool BoostCommandLine::getOnePositiveIntOption(const std::string& optionName,
                                               unsigned int& value) const
{
  return getValueForOption<unsigned int>(optionName, values_, value);
}

bool BoostCommandLine::getOneStringOption(const std::string& optionName,
                                          std::string& value) const
{
  return getValueForOption<std::string>(optionName, values_, value);
}
