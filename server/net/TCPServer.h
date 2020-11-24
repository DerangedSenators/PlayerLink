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
#ifndef PLAYERLINK_SERVER_TCP_SERVER_H
#define PLAYERLINK_SERVER_TCP_SERVER_H
#include <vector>
#include "net/tcp/tcpsocket.h"
/**
 * @brief TCPServer class based on Socket Class. Uses TCP communication and also functions as a server to listen and monitor socket connections
*/
class TCPServer : public Socket {
public:
	/**
	 * @brief Constructs a TCPServer object
	 * @return 
	*/
	TCPServer();
	/**
	 * @brief Listens to incoming bytes on a specified port
	 * @param port The port you wish to monitor
	 * @param backlog 
	*/
	void listen(std::string port, int backlog = 5);
	/**
	 * @brief Method to accept incomming connection request
	 * @return TCPSocket Object used to hold information and methods to send/recieve information from them
	*/
	TCPSocket accept();
	/**
	 * @brief Monitors the provided socket
	 * @param fd The File Descriptor for the socket you want to monitor
	*/
	void monitorSocket(TCPSocket &fd);
	/**
	 * @brief Stops monitoring the provided socket
	 * @param fd The File Descriptor for the socket you no longer want to monitor
	*/
	void unmonitor(TCPSocket& fd);
	/**
	 * @brief Gets the socket Events
	 * @param timeout 
	 * @return SocketEvents in a vector
	*/
	std::vector<TCPSocket> getSocketEvents(int timeout = 10000);
private:
	std::vector<struct pollfd> mMonitorFDs;
};
#endif