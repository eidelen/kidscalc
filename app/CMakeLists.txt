cmake_minimum_required(VERSION 3.0)

PROJECT(kidscalcapp)

MESSAGE(STATUS "Building kidscalc examples")

# get argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
    GIT_TAG        40a3888f151256bba95c45860af381b2b73752e8
)
FetchContent_MakeAvailable(argparse)

add_executable(kidscalcapp main.cpp)
target_link_libraries(kidscalcapp kidscalclib argparse )
target_compile_features(kidscalcapp PRIVATE cxx_std_17 )

