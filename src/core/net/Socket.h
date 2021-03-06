/*
 * Copyright (C) 2020 Deranged Senators
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef PLAYERLINK_CORE_SOCKET_H
#define PLAYERLINK_CORE_SOCKET_H
//Network related includes:
//If on windows
#ifdef WIN32
#include <winsock2.h>
#include <WS2tcpip.h>
#include "winsockinit.h"

#pragma comment(lib, "Ws2_32.lib")
//If on Unix or POSIX Compliant Systems
#elif unix
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#endif //WIN64 or Linux checks for the compiler
#ifdef unix
#define SOCKETPOLL poll
#define CLOSESOCKET ::close
#elif _WIN32
#define SOCKETPOLL WSAPoll
#define CLOSESOCKET closesocket
#endif
// Protocols
#include "Protocols.h"
#include "NetConfig.h"
#include "utils/exceptions/RuntimeException.h"
#define SA struct sockaddr
#include <string>
#include <cstring>



namespace PlayerLink{ namespace Core{
    typedef char rawType;
    /**
     * @brief Lowest socket implementation. This class will be used by top level socket implementations
     * @author Hanzalah Ravat
    */
    class Socket {
    public:
        /**
         * @brief Constructs a Socket object
         * @param family Address Family.
         * @param type The type specification for the new socket
         * @param flag The protocol used for data transmission
         * @attention Winsock2.dll is automatically initialised when using this method on a Windows Device
         * @return If no error occurs, socket returns a descriptor referencing the new socket. Otherwise, a value of -1
        */
        Socket(int family, int type, int flag);
        explicit Socket(int fd);
        /**
         * @brief Returns the IP Address of the remote device
         * @return Gets the address of the remote device
        */
        std::string getAddress() const;
        /**
         * @brief
         * @return The port number used for this connection
        */
        uint32_t getPort() const;
        /**
         * @brief
         * @return The socket descriptor used for this socket
        */
        int getSocketDescriptor() const;
        /**
         * @brief Closes the connection
         * @return True if socket closes or false if there was an error while closing the socket
        */
        bool close();
        /**
         * @brief
         * @return true if the socket connection has been closed or false if it is still open
        */
        bool isClosed();
        /**
         * @brief Allows you to set the blocking mode for this file descriptor
         * @param swtch Sets the blocking value
         * @return The result of the blocking, True if blocking was successful or false if there was an issue with changing the blocking status
        */
        bool setBlocking(bool swtch);

        /**
         * @brief
         * @return The last error number
        */
        int getLastError();

    protected:
        /**
         * @brief File Descriptor for this socket instance
        */
        int mSocketFD;
        /**
         * @brief Flag if socket is open or closed
        */
        bool socketIsClosed;
        /**
         * @brief Boolean to determine if blocking is enabled on this socket instance
        */
        bool isBlocked;

    };

}}
#endif //PLAYERLINK_CORE_SOCKET_H