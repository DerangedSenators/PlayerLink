#ifndef PLAYERLINK_SERVER_TCP_SERVER_H
#define PLAYERLINK_SERVER_TCP_SERVER_H
#include <vector>
#include "net/tcp/tcpsocket.h"

class __declspec(dllimport) TCPServer : public Socket {
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