cmake_minimum_required(VERSION 2.8)
project(rtype_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wdelete-non-virtual-dtor")

file(
        GLOB_RECURSE
        SERVER_SRCS
        src/*.cpp
        include/*.hh
        include/*.hpp
)

include_directories(include)
include_directories(include/entities)
include_directories(${PROTOBOEUF_INCLUDE_DIRS} ${RTYPE_CORE_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SERVER_SRCS})
IF ("${CMAKE_SYSTEM}" MATCHES "Linux")
    target_link_libraries(${PROJECT_NAME} dl)
    target_link_libraries(${PROJECT_NAME} pthread)
endif ()

target_link_libraries(${PROJECT_NAME} rtype_core)


if (CLIENT_TESTS)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLOG_INFO=ON")
    add_library("${PROJECT_NAME}lib" STATIC ${SERVER_SRCS})
    IF ("${CMAKE_SYSTEM}" MATCHES "Linux")
        target_link_libraries(${PROJECT_NAME} dl)
        target_link_libraries(${PROJECT_NAME} pthread)
    endif ()
    target_link_libraries("${PROJECT_NAME}lib" rtype_core)


    enable_testing()
    add_subdirectory(tests)
endif (CLIENT_TESTS)
