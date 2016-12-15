cmake_minimum_required(VERSION 2.8)
project(rtype_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)

file(
        GLOB_RECURSE
        CLIENT_SRCS
        src/*.cpp
        include/*.hh
        include/*.hpp
)

include_directories(include)
include_directories(${SFML_INCLUDE_DIR})
include_directories(${PROTOBOEUF_INCLUDE_DIRS} ${RTYPE_CORE_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${CLIENT_SRCS})
target_link_libraries(${PROJECT_NAME} rtype_core)
target_link_libraries(${PROJECT_NAME} protoboeuf pthread)
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})

if (CLIENT_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(CLIENT_TESTS)
