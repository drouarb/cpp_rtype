cmake_minimum_required(VERSION 2.8)
project(rtype_core)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

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
include_directories(../server/include)
include_directories(../server/include/entities)

set(RTYPE_CORE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

foreach (entity_file ${ENTITIES_SRC_FILES})
    get_filename_component(entity_name ${entity_file} NAME_WE)
    add_library(${entity_name} SHARED ${entity_file} ${ENTITIES_HEADER_FILES} ../server/src/entities/EntityAction.cpp )
   #TODO Must be replaced by SHARED
endforeach (entity_file)

if (ENTITIES_TEST)
    enable_testing()
    add_subdirectory(tests)
endif (ENTITIES_TEST)
