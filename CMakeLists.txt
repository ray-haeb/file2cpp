cmake_minimum_required(VERSION 2.8.4)
project(file2cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(file2cpp ${SOURCE_FILES})