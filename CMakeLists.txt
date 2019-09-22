cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(code)

# Linux only!
if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  message(FATAL_ERROR "Only Linux is supported")
endif()

# Gather some information about current build and generate header
# Note: having this here implies that cmake runs for every build
execute_process(COMMAND git --git-dir=${CMAKE_SOURCE_DIR}/.git rev-parse HEAD
                OUTPUT_VARIABLE GIT_HEAD
                OUTPUT_STRIP_TRAILING_WHITESPACE)
if("${GIT_HEAD}" STREQUAL "")
  message(FATAL_ERROR "Can't get git SHA-1 for HEAD")
endif()
file(WRITE ${CMAKE_BINARY_DIR}/GeneratedBuildInfoNew.h
     "#define BUILDINFO_GIT_HEAD \"${GIT_HEAD}\"")
execute_process(COMMAND cmake -E copy_if_different
                ${CMAKE_BINARY_DIR}/GeneratedBuildInfoNew.h
                ${CMAKE_BINARY_DIR}/GeneratedBuildInfo.h)

# compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# compile using ccache
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)

# Compiler debug flags - we use GCC sanitizers
set(COMMON_FLAGS_DEBUG
    -fsanitize=undefined #-fsanitize=address
    -fno-sanitize=vptr
    -fno-omit-frame-pointer
    )
set(C_ONLY_FLAGS_DEBUG
    )
set(C_FLAGS_DEBUG "${COMMON_FLAGS_DEBUG} ${C_ONLY_FLAGS_DEBUG}")
string(REGEX REPLACE ";" " " C_FLAGS_DEBUG "${C_FLAGS_DEBUG}")
set(CXX_ONLY_FLAGS_DEBUG
    )
set(CXX_FLAGS_DEBUG "${COMMON_FLAGS_DEBUG} ${CXX_ONLY_FLAGS_DEBUG}")
string(REGEX REPLACE ";" " " CXX_FLAGS_DEBUG "${CXX_FLAGS_DEBUG}")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${C_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_DEBUG}")

# Compiler flags - warnings for the win!
set(COMMON_FLAGS
    -Wall -Wextra -Wpedantic -Werror
    -Wl,-rpath,$ORIGIN/lib # to load shared objects from lib folder
    ${COMPILE_EXTRA_FLAGS} # can be given when calling cmake
    )
set(C_ONLY_FLAGS
    -std=c11
    )
set(C_FLAGS "${COMMON_FLAGS} ${C_ONLY_FLAGS}")
string(REGEX REPLACE ";" " " C_FLAGS "${C_FLAGS}")
set(CXX_ONLY_FLAGS
    -std=c++14
    -Wold-style-cast
    -Woverloaded-virtual
    -Wsuggest-override
    -Wzero-as-null-pointer-constant
    -DBOOST_ALL_DYN_LINK
    )
set(CXX_FLAGS "${COMMON_FLAGS} ${CXX_ONLY_FLAGS}")
string(REGEX REPLACE ";" " " CXX_FLAGS "${CXX_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}")

# we set output dir to a tmp folder, please will copy those binaries and their
# dependencies in /bin folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tmp_bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/ar)

# Useful variables that are used to parameter build
#set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_VERBOSE_MAKEFILE 1) # use VERBOSE=1 with make
#set(CMAKE_C_COMPILER gcc)
#set(CMAKE_CXX_COMPILER g++)
#set(CMAKE_AR gcc-ar)
#set(CMAKE_RANLIB gcc-ranlib)

# Here goes our stuff to build
include_directories(include)

# libraries

add_subdirectory(lib/BuildInfo/)
add_subdirectory(lib/CommandLine/)
add_subdirectory(lib/HelloWorld/)
add_subdirectory(lib/Log/)

# binaries
add_subdirectory(src/hello_world/)
add_subdirectory(src/unittests/)

# unit tests
# for each library unit tested, you must edit src/unittests/CMakeLists.txt too
add_subdirectory(unittests/HelloWorld/)
