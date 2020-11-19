//
// Created by hanzalah on 07/11/2020.
//

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
// Protocols
#include "Protocols.h"
#include "NetConfig.h"
#include "SocketException.h"
#define SA struct sockaddr
#include <string>
#include <cstring>

typedef char rawType;

class Socket{
public:
    Socket(int family, int type, int flag);
    explicit Socket(int fd);

    std::string getAddress() const;
    uint32_t getPort() const;

    int getSocketDescriptor() const;

    void close();
    bool isClosed();

    bool setBlocking(bool swtch);


    int getLastError();

protected:
    int mSocketFD;
    bool socketIsClosed;
    bool isBlocked;
};
#endif //PLAYERLINK_CORE_SOCKET_H