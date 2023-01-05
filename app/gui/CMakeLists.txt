cmake_minimum_required(VERSION 3.11)

PROJECT(kidscalcgui VERSION 1.0 LANGUAGES CXX)

option(BUILDGUI "Build GUI" OFF)
IF(${BUILDGUI})

    MESSAGE(STATUS "Building kidscalc GUI")

    set(CMAKE_AUTOMOC ON)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)

    find_package(Qt6 6.2 COMPONENTS Quick Gui REQUIRED)

    qt_add_executable(kidscalcgui
        main.cpp
    )

    target_link_libraries(kidscalcgui PRIVATE kidscalclib  Qt6::Gui  Qt6::Quick )
    target_compile_features(kidscalcgui PRIVATE cxx_std_17 )

    qt_add_qml_module(kidscalcgui
        URI kc
        VERSION 1.0
        QML_FILES main.qml
    )

ENDIF()
