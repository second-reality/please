set(SOURCE
    BoostLogger.cpp
    Log.cpp
    )

set(LIB_DEPS
    boost_log
    boost_system
    boost_thread
    pthread
    )

add_library(Log ${SOURCE})
target_link_libraries(Log ${LIB_DEPS})
