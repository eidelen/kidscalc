cmake_minimum_required(VERSION 3.0)

PROJECT(kidscalclib)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(KC_INC_FOLDERS inc)

INCLUDE_DIRECTORIES(${KC_INC_FOLDERS})
FILE(GLOB  KC_INCLUDES        inc/*.h)
FILE(GLOB  KC_SOURCES         src/*.cpp)

ADD_LIBRARY(kidscalclib STATIC ${KC_INCLUDES} ${KC_SOURCES} )
target_include_directories(kidscalclib INTERFACE ${KC_INC_FOLDERS} )
target_compile_features(kidscalclib PRIVATE cxx_std_17 )

option(TESTKC  "TEST" ON)
IF(${TESTKC})
    MESSAGE(STATUS "KidsCalc tests activated")

    # Download and build gtest
    include(FetchContent)
    FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    FILE(GLOB_RECURSE  KC_TESTS_INC       test/*.h)
    FILE(GLOB_RECURSE  KC_TESTS_SRC       test/*.cpp)

    add_executable(runKCLibTests ${KC_TESTS_INC} ${KC_TESTS_SRC})
    target_link_libraries(runKCLibTests kidscalclib gtest_main  )
    target_compile_features(runKCLibTests PRIVATE cxx_std_17 )
ENDIF()

