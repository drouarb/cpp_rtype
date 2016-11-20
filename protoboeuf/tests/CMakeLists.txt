enable_testing()

include_directories(../include)
include_directories(../src)

file(
        GLOB_RECURSE
        PROTOBOEUF_TESTS_SOURCES
        network/utils/NetworkIntegerTest.cpp
        network/utils/NetworkStringTest.cpp
        network/utils/NetworkVectorTest.cpp
        network/packet/APacketTest.cpp
        network/packet/APacketDataTest.cpp
)

foreach(test ${PROTOBOEUF_TESTS_SOURCES})
    get_filename_component(test_name ${test} NAME_WE)
    add_executable(${test_name} ${test})
    add_test(${test_name} ${test_name})
endforeach(test)

