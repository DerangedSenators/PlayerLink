//
// Created by hanzalah on 10/11/2020.
//

#ifndef PLAYERLINK_SERVER_GAMEROOM_H
#define PLAYERLINK_SERVER_GAMEROOM_H
#include "Client.h"
#define MAX_PLAYERS 8 // For the default game room... Allow 8 concurrent connections to take place
/**
 * A GameRoom is a class which holds all players in a game
 */
class GameRoom {
public:
    /**
     * Broadcasts a message to all participants of a room
     * @param message
     */
    void broadcast(char* message);

private:
    Client clients[MAX_PLAYERS];

};


#endif //PLAYERLINK_SERVER_GAMEROOM_H
