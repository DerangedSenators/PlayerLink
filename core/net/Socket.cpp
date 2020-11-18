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
    if(!socketIsClosed){
        ::closesocket(mSocketFD);
        socketIsClosed = true;
    }
}
#elif _unix_
void Socket::close() {
    if(!socketIsClosed){
        ::close(mSocketFD);
        socketIsClosed = true;
    }
}
#endif

std::string Socket::getAddress() const {
    sockaddr_in address;
    uint32_t addressLength = sizeof(address);
    if(getpeername(mSocketFD, (sockaddr *)&address, (socklen_t  *)addressLength) < 0){
        throw SocketException("Fetch of Remote Address Failed");
    }
    return inet_ntoa(address.sin_addr);
}

uint32_t Socket::getPort() const{
    sockaddr_in address;
    uint32_t addressLength = sizeof(address);
    if(getpeername(mSocketFD, (sockaddr *)&address, (socklen_t  *)addressLength) < 0){
        throw SocketException("Fetch of Remote Port Failed");
    }
    return ntohs(address.sin_port);
}

#ifdef __linux__ 
bool Socket::setBlocking(bool swtch) {
    int arg = fcntl(mSocketFD, F_GETFL, NULL);
    if (swtch == true) {
        arg &= (~O_NONBLOCK);
    }
    else {
        arg |= O_NONBLOCK;
    }
    fcntl(mSocketFD, F_SETFL, arg);
}
#elif _WIN32
bool Socket::setBlocking(bool swtch) {
    u_long blockMode = 0;
    if (!swtch) {
        blockMode = 1;
    }
    ioctlsocket(mSocketFD, FIONBIO, &blockMode);
    return true;
}
#endif

bool Socket::isClosed() {
    if(!socketIsClosed){
        char optval;
        socklen_t optlen = sizeof(optval);
        int res = getsockopt(mSocketFD,SOL_SOCKET,SO_ERROR,&optval,&optlen);
        if(optval == 0 && res == 0){
            socketIsClosed = true;
        } else{
            socketIsClosed = false;
        }
        return socketIsClosed;
    }
    else {
        return true;
    }
    
}

int Socket::getLastError() {
    return errno;
}