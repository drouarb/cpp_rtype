//
// Created by greg on 09/12/2016.
//

#ifndef CPP_RTYPE_CORETEST_HPP
#define CPP_RTYPE_CORETEST_HPP

//#define LOG_INFO
#include <map>
#include "../include/Core.hh"

enum METHOD_CALLED : int {
    CORE_SET_CLIENT,
    CORE_REMOVE_CLIENT,
    NETWORK_MANAGER_clientRegister,
    NETWORK_MANAGER_clientDisconnect,
    NETWORK_MANAGER_clientJoin,
    NETWORK_MANAGER_clientPlayerAttack,
    NETWORK_MANAGER_clientPlayerMove,
    NETWORK_MANAGER_clientPlayerQuit,
    END
};

extern std::map<METHOD_CALLED, bool> status;

class NetworkManagerTest : public server::NetworkManager
{
public:
    NetworkManagerTest(server::Core *core);

    void setCore(server::Core *core);;

    void clientRegister(server::clientId_t src, const std::string &name) override;

    void clientDisconnect(server::clientId_t src) override;

    void clientJoin(server::clientId_t src, server::gameId_t game) override;

    void clientPlayerAttack(server::clientId_t src, server::attackId_t attackId, server::round_t tick) override;

    void clientPlayerMove(server::clientId_t src, server::speed_t vectX, server::speed_t vectY) override;

    void clientPlayerQuit(server::clientId_t src) override;
};

class CoreTest : public server::Core {
public:
    CoreTest(const std::string &path, server::NetworkManager *networkManager) : Core(path, networkManager) {}

    void setClient(server::Client &client, int id) override;

    void removeClient(server::Client &client) override;

    void run() override;

    void run(server::round_t maxTick);
};

class PacketFactoryTest : public network::PacketFactory {
public:
    PacketFactoryTest(unsigned short port);

    void send(const network::packet::IPacket &packet, unsigned long fd) const override;
};

class PacketFactoryNoNetwork : public network::PacketFactory {
public:
    PacketFactoryNoNetwork(unsigned short port);

    void send(const network::packet::IPacket &packet, unsigned long fd) const override;
};

#endif //CPP_RTYPE_CORETEST_HPP
