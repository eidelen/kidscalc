cmake_minimum_required(VERSION 3.0)

PROJECT(kidscalcapp)

MESSAGE(STATUS "Building kidscalc examples")

add_executable(kidscalcapp main.cpp)
target_link_libraries(kidscalcapp kidscalclib )
target_compile_features(kidscalcapp PRIVATE cxx_std_17 )

