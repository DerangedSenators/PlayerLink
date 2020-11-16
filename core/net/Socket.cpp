//
// Created by hanzalah on 16/11/2020.
//

#include "Socket.h"

Socket::Socket(int family, int type, int flag) : socketIsClosed(false) {
    mSocketFD = ::socket(family,type,flag);
    if(mSocketFD == -1){
        throw SocketException("Error when creating Socket");
    }
}

Socket::Socket(int fd) :mSocketFD(fd), socketIsClosed(false){}

int Socket::getSocketDescriptor() const {return mSocketFD;}

#ifdef _WIN32

void Socket::close() {
    if(!IsClosed){
        ::closesocket(mSocketFD);
        IsClosed = true;
    }
}
#elif _unix_
void Socket::close() {
    if(!IsClosed){
        ::close(mSocketFD);
        IsClosed = true;
    }
}
#endif

std::string Socket::getAddress() const {
    sockaddr_in address;
    uint32_t addressLength = sizeof(address);
    if(getpeername(mSocketFD, reinterpret_cast<sockaddr *>(&address), reinterpret_cast<socklen_t *>(addressLength)) < 0){
        throw SocketException("Fetch of Remote Address Failed");
    }
    return inet_ntoa(address.sin_addr);
}

uint32_t Socket::getPort() const{
    sockaddr_in address;
    uint32_t addressLength = sizeof(address);
    if(getpeername(mSocketFD, reinterpret_cast<sockaddr *>(&address), reinterpret_cast<socklen_t *>(addressLength)) < 0){
        throw SocketException("Fetch of Remote Port Failed");
    }
    return ntohs(address.sin_port);
}
//
// WIP: Find portable or Win32API Equivalent of fcntl
bool Socket::setBlocking(bool swtch) {
    isBlocked = swtch;
}

bool Socket::isClosed() {
    if(!socketIsClosed){
        int optval;
        socklen_t optlen = sizeof(optval);
        int res = getsockopt(mSocketFD,SOL_SOCKET,SO_ERROR,&optval,&optlen);
        if(optval == 0 && res == 0){
            socketIsClosed = true;
        } else{
            socketIsClosed = false;
        }
    }
}

int Socket::getLastError() {
    return errno;
}