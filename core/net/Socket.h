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
#pragma comment(lib, "Ws2_32.lib")
//If on Unix or POSIX Compliant Systems
#elif UNIX
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#endif //WIN64 or Linux checks for the compiler
#ifdef __unix__
#define SOCKETPOLL poll
#define CLOSESOCKET close
#elif _WIN32
#define SOCKETPOLL WSAPoll
#define CLOSESOCKET closesocket
#endif
// Protocols
#include "Protocols.h"
#include "NetConfig.h"
#include "SocketException.h"
#define SA struct sockaddr
#include <string>
#include <cstring>


namespace PlayerLink{namespace Core{
    typedef char rawType;
    Socket(int family, int type, int flag);
    explicit Socket(int fd);
    /**
     * @brief 
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
}}

/**
 * @brief Lowest socket implementation. This class will be used by top level socket implementations
 * @author Hanzalah Ravat
*/


    /**
     * @brief Lowest socket implementation. This class will be used by top level socket implementations
    */

 



#endif //PLAYERLINK_CORE_SOCKET_H