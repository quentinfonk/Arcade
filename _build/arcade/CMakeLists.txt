cmake_minimum_required(VERSION 3.0)

set(PROJ "arcade")

project(${PROJ})

include_directories(../../arcade_core/include)
include_directories(../../interface)

file(
    GLOB
    SRCS
    ../../arcade_core/src/*.cpp
    ../../arcade_core/src/*/*.cpp
)
set (CMAKE_CXX_FLAGS "-ldl -g3")
add_executable(${PROJ} ${SRCS})
target_compile_options(${PROJ} PRIVATE -Wall -Wextra )