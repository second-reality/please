set(SOURCE
    main.cpp
    )

set(LIB_DEPS
    HelloWorld
    )

add_executable(hello_world ${SOURCE})
target_link_libraries(hello_world ${LIB_DEPS})
