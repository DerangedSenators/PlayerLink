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
