cmake_minimum_required(VERSION 3.15)
project(Playground)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(../libWad libWad)

add_executable(Playground playground.cpp)
target_link_libraries(Playground PRIVATE Wad)
target_include_directories(Playground PRIVATE ../libWad)

add_executable(Dump wad_dump.cpp)
target_link_libraries(Dump PRIVATE Wad)
target_include_directories(Dump PRIVATE ../libWad)