#include "tcpsocket.h"

namespace PlayerLink{namespace Core{

}}

TCPSocket::TCPSocket(int fd) : Socket(fd) {
	mPollFD.fd = mSocketFD;
	mPollFD.events = POLLIN;
}

TCPSocket::TCPSocket() : Socket(AF_INET, SOCK_STREAM, AF_UNSPEC) {}

bool TCPSocket::connect(std::string address, std::string port) {
	struct addrinfo hostInfo;
	struct addrinfo* hostsInfoList;

	memset(&hostInfo, 0, sizeof hostInfo);

	hostInfo.ai_family = AF_UNSPEC;
	hostInfo.ai_socktype = SOCK_STREAM;
	hostInfo.ai_flags = AF_UNSPEC;

	int status = getaddrinfo(address.c_str(), port.c_str(), &hostInfo, &hostsInfoList);
	if (status != 0) {
		throw SocketException(gai_strerror(status));
	}

	status = ::connect(mSocketFD, hostsInfoList->ai_addr, hostsInfoList->ai_addrlen);
	freeaddrinfo(hostsInfoList);

	if (status == -1) {
		throw SocketException("Error whilst connecting socket to: " + address + ": " + port);
	}
	mPollFD.fd = mSocketFD;
	mPollFD.events = POLLIN;
}

bool TCPSocket::connectWithTimeout(std::string address, std::string port, int seconds, int microseconds) {
	fd_set fdset;
	struct timeval tval;

	// Set Blocking
	setBlocking(false);

	struct addrinfo hostInfo;
	struct addrinfo* hostsInfoList;

	memset(&hostInfo, 0, sizeof hostInfo);

	hostInfo.ai_family = AF_UNSPEC;
	hostInfo.ai_socktype = SOCK_STREAM;
	hostInfo.ai_flags = AF_UNSPEC;

	int status = getaddrinfo(address.c_str(), port.c_str(), &hostInfo, &hostsInfoList);
	if (status != 0) {
		throw SocketException(gai_strerror(status));
	}

	::connect(mSocketFD, hostsInfoList->ai_addr, hostsInfoList->ai_addrlen);
	freeaddrinfo(hostsInfoList);

	FD_ZERO(&fdset);
	FD_SET(mSocketFD,&fdset);

	tval.tv_sec = seconds;
	tval.tv_usec = microseconds;

	if (select(mSocketFD + 1, NULL, &fdset, NULL, &tval) == 1) {
		char sockErr; //DOUBLECHECK
		socklen_t length = sizeof sockErr;
		getsockopt(mSocketFD, SOL_SOCKET, SO_ERROR, &sockErr, &length);
		if (sockErr != 0) {
			throw SocketException("Error whilst connecting socket to: " + address + ": " + port);
		}
	}
	else {
		throw SocketException("Error whilst connecting socket to: " + address + ": " + port);
	}
	setBlocking(true);
	mPollFD.fd = mSocketFD;
	mPollFD.events = POLLIN;
}
bool TCPSocket::canReceive(int timeout) {
#ifdef __linux__
	int status = poll(&mPollFD, 1, timeout);
#elif _WIN32
	int status = WSAPoll(&mPollFD, 1, timeout);
#endif
	if (status == -1) {
		throw SocketException("Error while pooling connection");
	}
	else if (status == 0) {
		return false;
	}
	else if (mPollFD.revents & POLLIN) {
		mPollFD.revents = 0;
		return true;
	}
	return false;
}

size_t TCPSocket::recieve(void* buffer, size_t bufferLength) {
	return ::recv(mSocketFD, (rawType *)buffer, bufferLength, 0);
}

size_t TCPSocket::recieveAll(void* buffer, size_t bufferLength) {
	size_t result, toReturn = 0;
	while (toReturn < bufferLength) {
		result = ::recv(mSocketFD, (rawType*)buffer, bufferLength, 0);
		if (result < 0) {
			throw SocketException("Error while receiving information from the Socket");
		} else if (result == 0){
			break;
		}
		buffer = static_cast<char*>(buffer) + result;
		toReturn += result;
	}
	return toReturn;
}

unsigned char* TCPSocket::recieveBytes() {
	uint32_t length;
	// Recieve network byte order
	if (recieveAll(&length, sizeof length) != sizeof length) {
		return 0;
	}

	length = ntohl(length);
	unsigned char* message;
	if (recieveAll(&message, length) != length) {
		return 0;
	}
	else {
		return message;
	}

}

size_t TCPSocket::send(void const* buffer, size_t bufferLength) {
	return ::send(mSocketFD, (rawType*)buffer, bufferLength, 0);
}

size_t TCPSocket::sendAll(void const* buffer, size_t bufferLength) {
	size_t result, toReturn = 0;
	while (toReturn < bufferLength) {
		result = ::send(mSocketFD, (rawType*)buffer, bufferLength, 0);
		if (result < 0) {
			throw SocketException("Error while receiving information from the Socket");
		}
		else if (result == 0) {
			break;
		}
		buffer = static_cast<const char*>(buffer) + result;
		toReturn += result;
	}
	return toReturn;
}

bool TCPSocket::sendBytes(unsigned char* message) {
	bool success = true; // Innocent until proven Guilty
	size_t byteLen = sizeof message;
	byteLen = htonl(byteLen);
	// Send length to remote
	if (sendAll(&byteLen, sizeof byteLen) != sizeof byteLen) {
		success = false;
	}
	if (success == true && sendAll(message, sizeof message) != sizeof message) {
		success = false;
	}
	return success;
}

bool TCPSocket::setSendTimeout(int seconds, int microseconds) {
	struct timeval timeout;
	timeout.tv_sec = seconds;
	timeout.tv_usec = microseconds;

	if (setsockopt(mSocketFD, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout)) < 0) {
		return false;
	}
	return true;
}

bool TCPSocket::setRecvTimeout(int seconds, int microseconds) {
	struct timeval timeout;
	timeout.tv_sec = seconds;
	timeout.tv_usec = microseconds;

	if (setsockopt(mSocketFD, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) < 0) {
		return false;
	}
	return true;
}
