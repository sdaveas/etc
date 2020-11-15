cmake_minimum_required(VERSION 3.10)

project(CommsquareTest)

add_executable(${PROJECT_NAME} src/main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

add_subdirectory(tests)

find_package(Catch2 REQUIRED)
