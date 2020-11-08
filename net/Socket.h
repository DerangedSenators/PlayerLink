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
//If on Unix or POSIX Compliant Systems
#elif __unix__
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif //WIN64 or Linux checks for the compiler
// Protocols
#include "Protocols.h"
#define DEFAULT_TCP_PORT 270500
#define DEFAULT_UDP_PORT 200800
#define SA struct sockaddr

/**
 * The simplest Socket interface. Enforces sending/recieving of data
 * @author Hanzalah Ravat
 */
class Socket{
    /**
     * Task to be completed when Bytes are recieved from remote
     * @param bytes An array of bytes
     */
    virtual void onBytesRecv(char bytes[]) = 0;
public:
    /**
     * Takes a set of bytes and sends to the remote
     * @param message The message in the form of bytes
     */
    void BytesSend(char *message);

};
#endif //PLAYERLINK_CORE_SOCKET_H
