cmake_minimum_required(VERSION 2.8)
project(cpp_rtype)

option(RTYPE_TESTS "Enable test compilation" OFF)

include(CTest)
set(PROTOBOEUF_TESTS ${RTYPE_TESTS})
add_subdirectory(protoboeuf)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(
        GLOB_RECURSE
        RTYPE
        src/*.cpp
        include/*.hh
        include/*.hpp
)

include_directories(include)
include_directories(${PROTOBOEUF_INCLUDE_DIRS})

set(SOURCE_FILES src/main.cpp)
add_executable(cpp_rtype ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} protoboeuf)
