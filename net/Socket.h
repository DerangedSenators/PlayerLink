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
#endif //PLAYERLINK_CORE_SOCKET_H
