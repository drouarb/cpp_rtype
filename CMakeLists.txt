cmake_minimum_required(VERSION 2.8)
project(cpp_rtype)

option(RTYPE_TESTS "Enable test compilation" OFF)

include(CTest)
set(PROTOBOEUF_TESTS ${RTYPE_TESTS})
add_subdirectory(protoboeuf)

set(CORE_TESTS ${RTYPE_TESTS})
add_subdirectory(core)
