cmake_minimum_required(VERSION 3.0)

set(PROJ "nibbler")

project(${PROJ})

include_directories(../../../games/${PROJ}/include)
include_directories(../../../arcade_core/include)
include_directories(../../../interface)

file(
    GLOB
    SRCS
    ../../../games/${PROJ}/src/*.cpp
    ../../../games/${PROJ}/src/*/*.cpp
)
add_library(${PROJ} SHARED ${SRCS})
target_compile_options(${PROJ} PRIVATE -Wall -Wextra)