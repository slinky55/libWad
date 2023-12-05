cmake_minimum_required(VERSION 3.15)
project(Wad
        LANGUAGES CXX
        VERSION 0.1.0
        DESCRIPTION "A WAD file library written in C++"
)

add_library(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE Wad.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})