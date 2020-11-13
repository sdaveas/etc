cmake_minimum_required(VERSION 3.10)

project(CommsquareTest)

# find_package(Catch2 MODULE REQUIRED)

include_directories(src/)

# add_subdirectory(src)

add_executable(${PROJECT_NAME} src/main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

add_subdirectory(tests)
