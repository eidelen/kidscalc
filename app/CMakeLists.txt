cmake_minimum_required(VERSION 3.11)

PROJECT(kidscalcapp)

MESSAGE(STATUS "Building kidscalc examples")

# fetch latest argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

add_executable(kidscalcapp main.cpp)
target_link_libraries(kidscalcapp kidscalclib argparse )
target_compile_features(kidscalcapp PRIVATE cxx_std_17 )

