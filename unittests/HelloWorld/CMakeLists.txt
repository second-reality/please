set(SOURCE
    HelloWorldTest.cpp
    )

set(LIB_DEPS
    HelloWorld
    )

add_library(HelloWorld-test ${SOURCE})
target_link_libraries(HelloWorld-test ${LIB_DEPS})
