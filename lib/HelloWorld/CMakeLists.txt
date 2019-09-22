set(SOURCE
    HelloWorld.cpp
    )

set(LIB_DEPS
    CommandLine
    Log
    )

add_library(HelloWorld ${SOURCE})
target_link_libraries(HelloWorld ${LIB_DEPS})
