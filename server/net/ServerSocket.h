//
// Created by Hanzalah on 08/11/2020.
//

#ifndef PLAYERLINK_SERVER_SOCKET_H
#define PLAYERLINK_SERVER_SOCKET_H

#include "net/Socket.h"
#define MAX  //Max size of a buffer
class ServerSocket {

public:
    /**
     * Constructs a ServerSocket with a specified listening port
     * @param protocol The Stream Protocol
     * @param port The Port that the client is expected to connect to
     */
    ServerSocket(Protocols protocol, int port);
    /**
     * Constructs a ServerSocket
     * @param protocol The Stream Protocol
     */
    ServerSocket(Protocols protocol);


private:
    /**
     * Clears the buffer
     * @param buffer
     */
    void clearBuffer(char *buffer);
    /**
     * Processes an input from a client
     * @param buffer
     */
    void processInput(char buffer[]);
};
#endif //PLAYERLINK_SERVER_SOCKET_H
