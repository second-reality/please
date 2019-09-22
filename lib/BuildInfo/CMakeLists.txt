set(SOURCE
    BuildInfo.cpp
    )

# we include CMAKE_BINARY_DIR to get generated header for build info
include_directories(${CMAKE_BINARY_DIR})
add_library(BuildInfo ${SOURCE})
