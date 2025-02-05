cmake_minimum_required(VERSION 3.10)
set(SubProjectName "lab_3")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${SubProjectName}_lib src/parent.h main.cpp src/utils.h src/parent.cpp src/consts/Consts.h src/sharedFile/SharedFile.cpp src/sharedMem/SharedMem.cpp src/sharedSem/SharedSem.cpp)
add_executable(${SubProjectName}_parent_exe src/parent.cpp)
add_executable(${SubProjectName}_child_exe src/child.cpp)
add_executable(${SubProjectName}_exe main.cpp)

target_link_libraries(${SubProjectName}_parent_exe PRIVATE ${SubProjectName}_lib)
target_link_libraries(${SubProjectName}_child_exe PRIVATE ${SubProjectName}_lib)
target_link_libraries(${SubProjectName}_exe PRIVATE ${SubProjectName}_lib)

add_executable(${SubProjectName}_tests tests/test.cpp)
target_link_libraries(${SubProjectName}_tests ${SubProjectName}_lib gtest_main)

add_test(NAME {SubProjectName}_Tests COMMAND ${SubProjectName}_tests)