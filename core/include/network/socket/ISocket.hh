//
// Created by drouar_b on 12/6/16.
//

#ifndef CPP_RTYPE_ISOCKET_HH
#define CPP_RTYPE_ISOCKET_HH

#include <cstdint>
#include <vector>
#include <network/listener/ISocketConnectionListener.hh>
#include <network/listener/ISocketDisconnectionListener.hh>
#include <network/listener/ISocketDataListener.hh>

#define POLL_TIMEOUT 100
#define SOCKET_BUFFER 65507
#define PING_TIME 1000
#define MAX_PINGS 5
#define HANDSHAKE_TIMEOUT 1000

namespace network {
    namespace socket {
        /*!
         * @interface ISocket
         * @brief Interface for all socket
         */
        class ISocket {
        public:
            /*!
             * @enum e_socketType
             * @brief Type of the socket
             */
            enum e_socketType {
                CLIENT,
                SERVER
            };

            /*!
             * @enum e_socketStatus
             * @brief Socket Status
             */
            enum e_socketStatus {
                DISCONNECTED,
                CONNECTING,
                CONNECTED,
                STOPPING,
            };

            virtual ~ISocket() {}

            /*!
             * @brief Start a thread on poll() and return
             * @return false if a thread is already running or failed to instantiate
             */
            virtual bool run() = 0;

            /*!
             * @brief Start processing network on current thread
             * @throw throw std::runtime_error if socket already running or failed to connect
             */
            virtual void poll() = 0;

            /*!
             * @brief Stop the thread started with run()
             * @return false if no thread is running true if stopped
             */
            virtual bool stop() = 0;

            /*!
             * @brief Send data to all already connected clients
             * @param data Data to send
             * @throw If the socket isn't running
             */
            virtual void broadcast(const std::vector<uint8_t> &data) = 0;

            /*!
             * @brief Send data to a client
             * @param data Data to send
             * @param dest Id of the receiver
             * @throw If the socket isn't running
             */
            virtual void send(const std::vector<uint8_t> &data, unsigned long dest) = 0;

            /*!
             * @brief Register a listener who listen for a new successful connection
             * @param listener Instance of the listener
             */
            virtual void registerConnectionListener(listener::ISocketConnectionListener *listener) = 0;

            /*!
             * @brief Remove a connection listener from the notified list
             * @param listener Instance of the listener
             */
            virtual void unregisterConnectionListener(listener::ISocketConnectionListener *listener) = 0;

            /*!
             * @brief Register a listener who listen for a client disconnection
             * @param listener Instance of the listener
             */
            virtual void registerDisconnectionListener(listener::ISocketDisconnectionListener *listener) = 0;

            /*!
             * @brief Remove a disconnection listener from the notified list
             * @param listener Instance of the listener
             */
            virtual void unregisterDisconnectionListener(listener::ISocketDisconnectionListener *listener) = 0;

            /*!
             * @brief Register a listener for data received
             * @param listener Instance of the listener
             */
            virtual void registerDataListener(listener::ISocketDataListener *listener) = 0;

            /*!
             * @brief Remove a disconnection listener from the notified list
             * @param listener Instance of the listener
             */
            virtual void unregisterDataListener(listener::ISocketDataListener *listener) = 0;

            /*!
             * @brief Get if the socket is a server or a client
             * @return type of the socket
             */
            virtual e_socketType getType() = 0;

            /*!
             * @brief Get if the socket is running
             * @return status of the socket
             */
            virtual e_socketStatus getStatus() = 0;
        };
    }
}

#endif //CPP_RTYPE_ISOCKET_HH
