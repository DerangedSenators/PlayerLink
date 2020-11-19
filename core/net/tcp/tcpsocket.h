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
	bool setRecvTimeout(int seconds = TIMEOUT_SECONDS, int microseconds = TIMEOUT_MICROSECONDS);

	size_t send(void const* buffer, size_t bufferLength);
	size_t sendAll(void const* buffer, size_t bufferLength);
	bool setSendTimeout(int seconds = TIMEOUT_SECONDS, int microseconds = TIMEOUT_MICROSECONDS);
private:
	struct pollfd mPollFD;
};
#endif