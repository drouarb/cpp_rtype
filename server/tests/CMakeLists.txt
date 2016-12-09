enable_testing()

include_directories(../../include)
include_directories(../include)
include_directories(../src)

file(
        GLOB_RECURSE
        CORE_TESTS_SOURCES
        *.cpp
)



foreach(test ${CORE_TESTS_SOURCES})
    get_filename_component(test_name ${test} NAME_WE)
    add_executable(${test_name} ${test})
    target_link_libraries(${test_name} ${PROJECT_NAME}lib)
    add_test(${test_name} ${test_name})
endforeach(test)

