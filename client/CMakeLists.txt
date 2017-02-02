cmake_minimum_required(VERSION 2.8)
project(rtype_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)

find_package(Boost REQUIRED)


file(
        GLOB_RECURSE
        CLIENT_SRCS
        src/*.cpp
        include/*.hh
        include/*.hpp
)

if (WIN32)
    file(
            GLOB_RECURSE
            CLIENT_SRCS
            ${CLIENT_SRCS}
            resources/resources.rc
    )
endif(WIN32)

include_directories(include)
include_directories(${SFML_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROTOBOEUF_INCLUDE_DIRS} ${RTYPE_CORE_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${CLIENT_SRCS})
target_link_libraries(${PROJECT_NAME} ${RTYPE_CORE_LIBS})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
if (UNIX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif()

if (${UNIX})
    target_link_libraries(${PROJECT_NAME} -lX11)
endif(${UNIX})

if (CLIENT_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(CLIENT_TESTS)
