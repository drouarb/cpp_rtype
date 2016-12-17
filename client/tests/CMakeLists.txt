enable_testing()

include_directories(../include)
include_directories(../src)
include_directories(${SFML_INCLUDE_DIRS})

file(
        GLOB_RECURSE
        CORE_TESTS_SOURCES
)

foreach(test ${CORE_TESTS_SOURCES})
    get_filename_component(test_name ${test} NAME_WE)
    add_executable(${test_name} ${test})
    add_test(${test_name} ${test_name})
endforeach(test)

file(
        GLOB_RECURSE
        UI_TEST_SOURCES
        UITest.cpp
)

add_executable(UITest ${UI_TEST_SOURCES})
target_link_libraries(UITest ${SFML_LIBRARIES})
add_test(UITest UITest)