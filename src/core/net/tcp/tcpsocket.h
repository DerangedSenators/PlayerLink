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
#include "net/Socket.h"
#define TIMEOUT_SECONDS 2
#define TIMEOUT_MICROSECONDS 0

namespace PlayerLink{namespace Core{
	/// <summary>
/// TCPSocket Class extends the base socket class
/// </summary>
	class TCPSocket : public Socket {
	public:
		explicit TCPSocket(int fd);
		explicit TCPSocket();

		/**
		 * @brief Connects to an address and port
		 * @param address The destination address
		 * @param port The destination port
		 * @return True if connection was successful and false if there was a problem
		*/
		bool connect(std::string address, std::string port);
		/**
		 * @brief Connects to an address and port with a timeout
		 * @param address The destination address
		 * @param port The destination port
		 * @param seconds The number of seconds to wait for a reply
		 * @param microseconds The number of microseconds to wait for a reply
		 * @return True if connection was successful and false if there was a problem
		*/
		bool connectWithTimeout(std::string address, std::string port, int seconds = TIMEOUT_SECONDS, int microseconds = TIMEOUT_MICROSECONDS);
		/**
		 * @brief Checks if the remote machine can recieve
		 * @param timeout The number of microseconds to wait before returning false
		 * @return True if remote is able to recieve packets and false if it can't or does not respond
		*/
		bool canReceive(int timeout = 10000);

		size_t recieve(void* buffer, size_t bufferLength);
		size_t recieveAll(void* buffer, size_t bufferLength);
		/**
		 * @brief Recieves bytes from the remote
		 * @return an char* type used to hold incoming bytes
		*/
		unsigned char* recieveBytes();

		bool setRecvTimeout(int seconds = TIMEOUT_SECONDS, int microseconds = TIMEOUT_MICROSECONDS);

		size_t send(void const* buffer, size_t bufferLength);
		size_t sendAll(void const* buffer, size_t bufferLength);
		/**
		 * @brief Sends bytes to remote
		 * @param message The bytes in a unsigned char*
		 * @return True if message was recieved successfully
		*/
		bool sendBytes(unsigned char* message);
		bool setSendTimeout(int seconds = TIMEOUT_SECONDS, int microseconds = TIMEOUT_MICROSECONDS);
	private:
		struct pollfd mPollFD;
	};
}}
#endif