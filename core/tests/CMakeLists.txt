enable_testing()

include_directories(../include)
include_directories(../src)
file(
        GLOB_RECURSE
        CORE_TESTS_SOURCES
        network/packet/PacketTest.cpp
        network/packet/testPacketAck.cpp
        network/packet/testPacketPing.cpp
        network/packet/testPacketDeleteEntity.cpp
        network/packet/testPacketErrorGame.cpp
        network/packet/testPacketErrorHandShake.cpp
        network/packet/testPacketErrorList.cpp
        network/packet/testPacketErrorScore.cpp
        network/packet/testPacketGameJoin.cpp
        network/packet/testPacketGameList.cpp
        network/packet/testPacketPong.cpp
        network/packet/testPacketCancelEvent.cpp
        network/packet/testPacketEventError.cpp
        network/packet/testPacketLeaderBoard.cpp
        network/packet/testPacketMoveEntity.cpp
        network/packet/testPacketPlayerAttack.cpp
        network/packet/testPacketPlayerMove.cpp
        network/packet/testPacketPlaySound.cpp
        network/packet/testPacketRegister.cpp
        network/packet/testPacketSpawnEntity.cpp
        network/packet/testPacketSyn.cpp
        network/packet/testPacketSynAck.cpp
        network/packet/testPacketUpdateEntity.cpp

)

foreach(test ${CORE_TESTS_SOURCES})
    get_filename_component(test_name ${test} NAME_WE)
    add_executable(${test_name} ${test})
    target_link_libraries(${test_name} rtype_core protoboeuf pthread)
    add_test(${test_name} ${test_name})
endforeach(test)

if (NOT WIN32)
    add_executable(UnixUDPSocketTest network/socket/UnixUDPSocketTest.cpp)
    target_link_libraries(UnixUDPSocketTest rtype_core protoboeuf pthread)
    add_test(UnixUDPSocketTest UnixUDPSocketTest)
endif(NOT WIN32)