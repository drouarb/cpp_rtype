cmake_minimum_required(VERSION 2.8)
project(rtype_core)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

file(
        GLOB_RECURSE
        ENTITIES_SRC_FILES
        src/*.cpp
)

file(
        GLOB_RECURSE
        ENTITIES_HEADER_FILES
        include/*.hh
)

include_directories(include)
include_directories(${RTYPE_CORE_INCLUDE_DIRS})

foreach (entity_file ${ENTITIES_SRC_FILES})
    get_filename_component(entity_name ${entity_file} NAME_WE)
    add_library(${entity_name} SHARED ${entity_file} ${ENTITIES_HEADER_FILES})
    set_target_properties(${entity_name} PROPERTIES PREFIX "")
    target_link_libraries(${entity_name} ${RTYPE_CORE_LIBS})
endforeach (entity_file)

if (ENTITIES_TEST)
    enable_testing()
    add_subdirectory(tests)
endif (ENTITIES_TEST)
