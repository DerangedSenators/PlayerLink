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

class TCPServer : public Socket {
public:
	TCPServer();

	void listen(std::string port, int backlog = 5);
	TCPSocket accept();
	void monitorSocket(TCPSocket &fd);
	void unmonitor(TCPSocket& fd);
	
	std::vector<TCPSocket> getSocketEvents(int timeout = 10000);
private:
	std::vector<struct pollfd> mMonitorFDs;
};
#endif