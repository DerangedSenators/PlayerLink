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
#ifndef PLAYERLINK_CORE_TCPSOCKET_H
#define PLAYERLINK_CORE_TCPSOCKET_H
#ifdef __linux__
#include <poll.h>
#endif
#include "net/Socket.h"
#define TIMEOUT_SECONDS 2
#define TIMEOUT_MICROSECONDS 0

/// <summary>
/// TCPSocket Class extends base socket class
/// </summary>
class TCPSocket : public Socket {
public:
	explicit TCPSocket(int fd);
	explicit TCPSocket();

	bool connect(std::string address, std::string port);
	bool connectWithTimeout(std::string address, std::string port, int seconds = TIMEOUT_SECONDS, int microseconds = TIMEOUT_MICROSECONDS);

	bool canReceive(int timeout = 10000);
	size_t recieve(void* buffer, size_t bufferLength);
	size_t recieveAll(void* buffer, size_t bufferLength);
	unsigned char* TCPSocket::recieveBytes();
	bool setRecvTimeout(int seconds = TIMEOUT_SECONDS, int microseconds = TIMEOUT_MICROSECONDS);

	size_t send(void const* buffer, size_t bufferLength);
	size_t sendAll(void const* buffer, size_t bufferLength);
	bool sendBytes(unsigned char* message);
	bool setSendTimeout(int seconds = TIMEOUT_SECONDS, int microseconds = TIMEOUT_MICROSECONDS);
private:
	struct pollfd mPollFD;
};
#endif