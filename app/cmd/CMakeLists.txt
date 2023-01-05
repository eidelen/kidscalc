cmake_minimum_required(VERSION 3.11)

PROJECT(kidscalccmd)

MESSAGE(STATUS "Building kidscalc cmd application")

# fetch latest argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

add_executable(kidscalccmd main.cpp)
target_link_libraries(kidscalccmd kidscalclib argparse )
target_compile_features(kidscalccmd PRIVATE cxx_std_17 )

