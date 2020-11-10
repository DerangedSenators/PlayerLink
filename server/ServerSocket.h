//
// Created by hanzalah on 08/11/2020.
//

#ifndef PLAYERLINK_CORE_SERVERSOCKET_H
#define PLAYERLINK_CORE_SERVERSOCKET_H

#include "../net/Socket.h"
#include "logger/Logger.h"
#define MAX 80
class ServerSocket {

public:
    ServerSocket();

};

void clearBuffer(char *buffer);

void processInput(char buffer[]);
#endif //PLAYERLINK_CORE_SERVERSOCKET_H
