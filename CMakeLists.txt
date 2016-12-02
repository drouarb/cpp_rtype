cmake_minimum_required(VERSION 2.8)
project(cpp_rtype)

option(RTYPE_TESTS "Enable test compilation" OFF)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})

include(CTest)
set(PROTOBOEUF_TESTS ${RTYPE_TESTS})
add_subdirectory(protoboeuf)

set(CORE_TESTS ${RTYPE_TESTS})
add_subdirectory(core)

set(CLIENT_TESTS ${RTYPE_TESTS})
add_subdirectory(client)

set(SERVER_TESTS ${RTYPE_TESTS})
add_subdirectory(server)

set(ENTITIES_TESTS ${RTYPE_TESTS})
add_subdirectory(Entities)
