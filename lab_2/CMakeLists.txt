cmake_minimum_required(VERSION 3.10)
set(SubProjectName "lab_2")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${SubProjectName}_lib main.cpp src/circle_area/circle_area.h src/threadwork/threadwork.cpp src/monte_carlo/monte_carlo.h)
add_executable(${SubProjectName}_exe main.cpp)

target_link_libraries(${SubProjectName}_exe PRIVATE ${SubProjectName}_lib)

add_executable(${SubProjectName}_tests tests/test.cpp)
target_link_libraries(${SubProjectName}_tests ${SubProjectName}_lib gtest_main)

add_test(NAME {SubProjectName}_Tests COMMAND ${SubProjectName}_tests)