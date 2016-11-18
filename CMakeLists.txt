cmake_minimum_required(VERSION 3.6)
project(cpp_rtype)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(cpp_rtype ${SOURCE_FILES})