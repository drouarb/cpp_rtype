enable_testing()

include_directories(../include)
include_directories(../src)

file(
        GLOB_RECURSE
        ENTITIES_TESTS_SOURCES
        *.cpp
)

foreach (test ${ENTITIES_TESTS_SOURCES})
    get_filename_component(test_name ${test} NAME_WE)
    add_executable(${test_name} ${test} ../../server/src/EntityAction.cpp)
    string(REGEX REPLACE "Test" "" lib_name ${test_name} )
    target_link_libraries(${test_name} ${lib_name})
    add_test(${test_name} ${test_name})
endforeach (test)

