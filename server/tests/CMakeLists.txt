enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLOG_INFO=ON -g")

add_library("lib${PROJECT_NAME}" STATIC ${SERVER_SRCS})
SET_TARGET_PROPERTIES("lib${PROJECT_NAME}" PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

include_directories(${RTYPE_SERVER_INCLUDE_DIRS})

file(
        GLOB_RECURSE
        SERVER_TESTS_SOURCES
        JoinQuitTest.cpp
        PlayerAttackAndMoveTest.cpp
)

if (NOT ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/levels ${CMAKE_BINARY_DIR}/server/tests/levels)
endif(NOT ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

foreach(test ${SERVER_TESTS_SOURCES})
    get_filename_component(test_name ${test} NAME_WE)
    add_executable(${test_name} ${test} ProjTester.cpp NetworkManagerTester.cpp)
    target_link_libraries(${test_name} lib${PROJECT_NAME} ${RTYPE_CORE_LIBS})
    add_test(${test_name} ${test_name})
endforeach(test)

add_executable(CollisionTest CollisionTest.cpp)
target_link_libraries(CollisionTest lib${PROJECT_NAME} ${RTYPE_CORE_LIBS})