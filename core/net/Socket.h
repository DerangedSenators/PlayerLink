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
#ifdef _WIN32
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
//If on Unix or POSIX Compliant Systems
#elif __unix__
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <poll.h>
#endif //WIN64 or Linux checks for the compiler
#ifdef __unix__
#define SOCKETPOLL poll
#elif _WIN32
#define SOCKETPOLL WSAPoll
#endif
// Protocols
#include "Protocols.h"
#include "NetConfig.h"
#include "SocketException.h"
#define SA struct sockaddr
#include <string>
#include <cstring>

typedef char rawType;
/**
 * @brief Lowest socket implementation. This class will be used by top level socket implementations
*/
class Socket{
public:
    /**
     * @brief Constructs a Socket object
     * @param family Address Family. 
     * @param type The type specification for the new socket
     * @param flag The protocol used for data transmission
     * @return If no error occurs, socket returns a descriptor referencing the new socket. Otherwise, a value of -1
    */
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
    */
    void close();
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
#endif //PLAYERLINK_CORE_SOCKET_H