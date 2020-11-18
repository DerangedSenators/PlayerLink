//
// Created by Hanzalah Ravat on 10/11/2020.
//

#ifndef PLAYERLINK_SERVER_CLIENT_H
#define PLAYERLINK_SERVER_CLIENT_H

#include "net/Socket.h"
class Client {
public:
    /**
     * Constructs a Client Type
     * @param playerID A unique ID for the player
     * @param sockaddrIn SockAddr information for the client
     */
    Client(int playerID,sockaddr_in sockaddrIn);

private:
    sockaddr_in sockaddrIn;
    int playerID;

};


#endif //PLAYERLINK_SERVER_CLIENT_H
