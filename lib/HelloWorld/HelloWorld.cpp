#include "blop/CommandLine/CommandLine.h"
#include "blop/HelloWorld/HelloWorld.h"
#include "blop/Log/Log.h"

#include <cstdlib>
#include <iostream>

using namespace blop;

int HelloWorld::main(int argc, char* argv[])
{
  (void)argc;
  (void)argv;

  //  log
  Logger::getGlobalLogger().setLogFile("/tmp/lol.log");
  BLOP_LOG_INFO("helloLog! " << 42);

  // options
  std::unique_ptr<CommandLine> cliPointer = CommandLine::makeCommandLine();
  CommandLine& cli = *cliPointer;

  const std::string stringToDisplayOption = "string-to-display";
  const std::string intToDisplayOption = "int-to-display";
  const std::string helpOption = "help";
  cli.addOption(CommandLine::ArgumentType::OneString,
                stringToDisplayOption,
                "",
                "string to display",
                true);
  cli.addOption(CommandLine::ArgumentType::OnePositiveInt,
                intToDisplayOption,
                "",
                "int to display",
                true);
  cli.addOption(CommandLine::ArgumentType::None,
                helpOption,
                "h",
                "print help",
                false);

  std::string cliError;
  if (!cli.parseArguments(argc, argv, cliError))
  {
    BLOP_LOG_ERROR("error on command line: " << cliError);
    return EXIT_FAILURE;
  }

  if (cli.isOptionSet(helpOption))
  {
    std::cout << cli.getHelp("hello_world");
    return EXIT_SUCCESS;
  }

  std::string strToDisplay;
  unsigned int intToDisplay = 0;
  cli.getOneStringOption(stringToDisplayOption, strToDisplay);
  cli.getOnePositiveIntOption(intToDisplayOption, intToDisplay);

  // print what options asked
  BLOP_LOG_INFO("display: " << strToDisplay << "|" << intToDisplay);

  return 0;
}

int HelloWorld::getAnswerToLifeUniverseAndEverything()
{
  return 42;
}
