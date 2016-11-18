cmake_minimum_required(VERSION 3.6)
project(cpp_rtype)

file(
        GLOB_RECURSE
        RTYPE
        src/*.cpp
        include/*.hh
        include/*.hpp
)

include_directories(include)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(cpp_rtype ${SOURCE_FILES})