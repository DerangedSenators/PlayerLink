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
#include "TCPServer.h"

namespace PlayerLink{namespace Server{
	TCPServer::TCPServer() : Socket(AF_INET, SOCK_STREAM, AF_UNSPEC) {}

	void TCPServer::listen(std::string port, int backlog) {
		struct addrinfo hostInfo;
		struct addrinfo* hostsInfoList;

		memset(&hostInfo, 0, sizeof hostInfo);

		hostInfo.ai_family = AF_UNSPEC;
		hostInfo.ai_socktype = SOCK_STREAM;
		hostInfo.ai_flags = AI_PASSIVE;

		int status = getaddrinfo(NULL, port.c_str(), &hostInfo, &hostsInfoList);

		if (status != 0) {
			throw SocketException(gai_strerror(status));
		}
		char yes = 1;
		setsockopt(mSocketFD, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

		if (::bind(mSocketFD, hostsInfoList->ai_addr, hostsInfoList->ai_addrlen) == -1) {
			throw SocketException("Error when binding socket to port: " + port);
		}
		if (::listen(mSocketFD, backlog) == -1) {
			throw SocketException("Error when trying to accept socket connection.");
		}
	}

	TCPSocket TCPServer::accept() {
		struct sockaddr_storage clientAddress;
		socklen_t clientAddressSize = sizeof(clientAddress);
		int newSocketFD = ::accept(mSocketFD, (struct sockaddr*)&clientAddress, &clientAddressSize);
		if (newSocketFD == -1) {
			throw SocketException("Error when trying to accept the socket connection");
		}
		return TCPSocket(newSocketFD);
	}

	void TCPServer::monitorSocket(TCPSocket& fd) {
		struct pollfd pollFD;
		pollFD.fd = fd.getSocketDescriptor();
		pollFD.events = POLLIN;
		mMonitorFDs.push_back(pollFD);
	}

	void TCPServer::unmonitor(TCPSocket& fd) {
		std::vector<struct pollfd>::iterator it = mMonitorFDs.begin();
		while (it != mMonitorFDs.end()) {
			if (it->fd == fd.getSocketDescriptor()) {
				it = mMonitorFDs.erase(it);
				break;
			}
			else {
				it++;
			}
		}
	}

	std::vector<TCPSocket> TCPServer::getSocketEvents(int timeout) {
		std::vector<TCPSocket> events;
#ifdef __linux__
		int status = poll(&mMonitorFDs[0], mMonitorFDs.size(), timeout);
#elif _WIN32
		int status = WSAPoll(&mMonitorFDs[0], mMonitorFDs.size(), timeout);
#endif
		if (status == -1) {
			throw SocketException("Error while pooling socket connection");
		}
		else if (status == 0) {
			return events;
		}
		else {
			for (auto pool_fd : mMonitorFDs) {
				if (pool_fd.revents & POLLIN) {
					pool_fd.revents = 0;
					TCPSocket socket(static_cast<int> (pool_fd.fd));
					events.push_back(socket);
				}
			}
			return events;
		}
	}
}}

