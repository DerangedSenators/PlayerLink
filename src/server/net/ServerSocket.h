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
#ifndef PLAYERLINK_SERVER_SOCKET_H
#define PLAYERLINK_SERVER_SOCKET_H

#include "net/Socket.h"
#define MAX  //Max size of a buffer

using namespace PlayerLink::Core;
namespace PlayerLink{namespace Server{
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
        void clearBuffer(char* buffer);
        /**
         * Processes an input from a client
         * @param buffer
         */
        void processInput(char buffer[]);
    };
}}


#endif //PLAYERLINK_SERVER_SOCKET_H
