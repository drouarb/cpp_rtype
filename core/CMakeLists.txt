cmake_minimum_required(VERSION 2.8)
project(rtype_core)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(
        GLOB_RECURSE
        CORE_SRCS
        src/entities/*.cpp
        src/helpers/Stopwatch.cpp
        src/JSON/*.cpp
        src/network/packet/*.cpp
        src/network/listener/*.cpp
        src/network/PacketFactory.cpp
        src/thread/*.cpp
        include/*.hh
        include/*.hpp
)

if (WIN32)
    file(
            GLOB_RECURSE
            CORE_SRCS
            ${CORE_SRCS}
            src/helpers/WindowsStopwatch.cpp
    )
else (WIN32)
    file(
            GLOB_RECURSE
            CORE_SRCS
            ${CORE_SRCS}
            src/network/socket/UnixUDPSocket.cpp
            src/helpers/UnixStopwatch.cpp
    )
endif (WIN32)

include_directories(include)
include_directories(include/JSON)
include_directories(${PROTOBOEUF_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${CORE_SRCS})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

if (NOT WIN32)
    set(DL_LIBRARY dl)
endif(NOT WIN32)

set(RTYPE_CORE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include ${PROTOBOEUF_INCLUDE_DIRS}
        CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

set(RTYPE_CORE_LIBS ${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${PROTOBOEUF_LIBS} ${DL_LIBRARY}
        CACHE INTERNAL "${PROJECT_NAME}: Libraries" FORCE)

if (CORE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(CORE_TESTS)
