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


namespace network {
    namespace socket {
        /*!
         * @interface ISocket
         * @brief Interface for all socket
         */
        class ISocket {
        public:
            virtual ~ISocket() { }

            /*!
             * @brief Start a thread on poll() and return
             * @return false if a thread is already running or failed to instantiate
             */
            virtual bool run() = 0;

            /*!
             * @brief Start processing network on current thread
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
             */
            virtual void broadcast(std::vector<uint8_t> *data) = 0;

            /*!
             * @brief Send data to a client
             * @param data Data to send
             * @param dest Id of the receiver
             */
            virtual void send(std::vector<uint8_t> *data, int dest) = 0;

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
        };
    }
}

#endif //CPP_RTYPE_ISOCKET_HH
