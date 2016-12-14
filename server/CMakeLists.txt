cmake_minimum_required(VERSION 2.8)
project(rtype_server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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

add_executable(${PROJECT_NAME} ${SERVER_SRCS} include/entities/ADynamicObject.hh include/entities/EntityData.hh src/entities/EntityData.cpp include/entities/Entity.hh src/entities/Entity.cpp)
add_library("${PROJECT_NAME}lib" STATIC ${SERVER_SRCS})
target_link_libraries(${PROJECT_NAME} dl)
target_link_libraries(${PROJECT_NAME} rtype_core)
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries("${PROJECT_NAME}lib" dl)
target_link_libraries("${PROJECT_NAME}lib" rtype_core)
target_link_libraries("${PROJECT_NAME}lib" pthread)


if (CLIENT_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(CLIENT_TESTS)
