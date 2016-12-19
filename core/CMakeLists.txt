cmake_minimum_required(VERSION 2.8)
project(rtype_core)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(
        GLOB_RECURSE
        CORE_SRCS
        src/network/packet/*.cpp
        src/network/listener/*.cpp
        src/network/PacketFactory.cpp
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
include_directories(${PROTOBOEUF_INCLUDE_DIRS})

add_library(${PROJECT_NAME} STATIC ${CORE_SRCS})

set(RTYPE_CORE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

if (CORE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(CORE_TESTS)
