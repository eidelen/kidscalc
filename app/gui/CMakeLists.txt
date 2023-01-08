cmake_minimum_required(VERSION 3.11)

PROJECT(kidscalcgui VERSION 1.0 LANGUAGES CXX)

option(BUILDGUI "Build GUI" OFF)
IF(${BUILDGUI})

    MESSAGE(STATUS "Building kidscalc GUI")

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    set(CMAKE_INCLUDE_CURRENT_DIR ON)

    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    find_package(Qt6 6.2 COMPONENTS Widgets REQUIRED)

    set(PROJECT_SOURCES
            main.cpp
            mainwindow.cpp
            mainwindow.h
            mainwindow.ui
            gameparam.cpp
            gameparam.h
            gameparam.ui
    )

    qt_add_executable(kidscalcgui
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    target_link_libraries(kidscalcgui PRIVATE kidscalclib  Qt6::Widgets)
    target_compile_features(kidscalcgui PRIVATE cxx_std_17 )

    qt_finalize_executable(kidscalcgui)

ENDIF()
