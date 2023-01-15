cmake_minimum_required(VERSION 3.16.3)
project(project_two LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(omr
        STATIC
        src/grid.cpp
        src/makegraph.cpp
        src/util.cpp)

target_include_directories(omr PUBLIC include)

add_executable(test app/test.cpp)
add_executable(timetillzero app/timetillzero.cpp)
target_link_libraries(test PUBLIC omr)
target_link_libraries(timetillzero PUBLIC omr)