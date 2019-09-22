set(SOURCE
    BoostCommandLine.cpp
    CommandLine.cpp
    )

set(LIB_DEPS
    BuildInfo
    boost_program_options
    )

add_library(CommandLine ${SOURCE})
target_link_libraries(CommandLine ${LIB_DEPS})
