cmake_minimum_required(VERSION 2.8)
project(rtype_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if (NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdelete-non-virtual-dtor -g")
endif(NOT WIN32)

file(
        GLOB_RECURSE
        SERVER_SRCS
        src/*.cpp
        include/*.hh
        include/*.hpp
        tests/ProjTester.cpp
)

include_directories(tests)
include_directories(include)
include_directories(../core/include/entities)
include_directories(${RTYPE_CORE_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SERVER_SRCS})

target_link_libraries(${PROJECT_NAME} ${RTYPE_CORE_LIBS})

set(RTYPE_SERVER_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include ${RTYPE_CORE_INCLUDE_DIRS}
        CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

if (SERVER_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif (SERVER_TESTS)
