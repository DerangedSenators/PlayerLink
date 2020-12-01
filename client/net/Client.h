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

#ifndef PLAYERLINK_CORE_CLIENT_H
#define PLAYERLINK_CORE_CLIENT_H

#include <deque>
#include <iostream>
#include <boost/thread.hpp>
#include <mutex>

#include "net/NetConfig.h"
#include "net/tcp/tcpsocket.h"
using namespace PlayerLink;

namespace PlayerLink {
	namespace Client {
		/**
		 * @brief Client Class which is connected to the game and provides an interface to connect to the server
		 * @author Hanzalah Ravat
		*/
		class Client {
		public:
			/**
			 * @brief Constructs a Client Instance. Currently only TCP functionality is available.
			 * @param serveraddr The address of the server
			 * @param port The port to use to connect to the server
			 * @return A Client Type which can be used to access client functions and methods
			*/
			Client(std::string serveraddr, std::string port = DEFAULT_TCP_PORT);
			/*
			 * @brief Deconstructs the Client Object
			*/
			~Client();
			/**
			 * @brief Creates a Session with the server using the provided username
			 * @param usrName This Users username
			 * @return 0 if the session runs and exits successfully
			*/
			bool login(std::string usrname);
			/**
			 * @brief Logs the user out and disconnects the connection from the server
			*/
			void logout();
			/**
			 * @brief Adds a message to the buffer to be sent to the server
			 * @param message The byte array to be sent to the server
			*/
			void addMsgToBuffer(unsigned char* message);
		private:
			/**
			 * @brief Read Loop used to read incoming messages
			*/
			void readLoop();
			/**
			 * @brief Writes messages from buffer to socket
			*/
			void writeLoop();

			bool mRunSignal;

			Core::TCPSocket mClientSocket;

			std::deque<unsigned char*> mMessageQueue;
			std::string mServer, mPort, mUserName;
			std::mutex mExitMutex;
			boost::thread_group mThreadGroup;

		};
	}
}
#endif //PLAYERLINK_CORE_CLIENT_H
