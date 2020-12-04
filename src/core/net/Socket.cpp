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
#include "Socket.h"


namespace PlayerLink {namespace Core {
#ifdef UNIX
    Socket::Socket(int family, int type, int flag) : socketIsClosed(false) {
        mSocketFD = ::socket(family, type, flag);
        if (mSocketFD == -1) {
            throw SocketException("Error when creating Socket");
        }
    }
#elif WIN32
        Socket::Socket(int family, int type, int flag) : socketIsClosed(false) {
        // Initialise Winsock
            if(init() == 1) {
                mSocketFD = ::socket(family, type, flag);
                if (mSocketFD == -1) {
                    throw SocketException("Error when creating Socket");
                }
            } else {
                throw SocketException("Error: Unable to initialise Winsock2.dll");
            }
        }
#endif
    Socket::Socket(int fd) :mSocketFD(fd), socketIsClosed(false) {}

    int Socket::getSocketDescriptor() const { return mSocketFD; }
  
    std::string Socket::getAddress() const {
        sockaddr_in address;
        uint32_t addressLength = sizeof(address);
        if (getpeername(mSocketFD, (sockaddr*)&address, (socklen_t*)addressLength) < 0) {
            throw SocketException("Fetch of Remote Address Failed");
        }
        return inet_ntoa(address.sin_addr);
    }

    uint32_t Socket::getPort() const {
        sockaddr_in address;
        uint32_t addressLength = sizeof(address);
        if (getpeername(mSocketFD, (sockaddr*)&address, (socklen_t*)addressLength) < 0) {
            throw SocketException("Fetch of Remote Port Failed");
        }
        return ntohs(address.sin_port);
    }

#ifdef UNIX 
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
        if (!socketIsClosed) {
            char optval;
            socklen_t optlen = sizeof(optval);
            int res = getsockopt(mSocketFD, SOL_SOCKET, SO_ERROR, &optval, &optlen);
            if (optval == 0 && res == 0) {
                socketIsClosed = true;
            }
            else {
                socketIsClosed = false;
            }
            return socketIsClosed;
        }
        else {
            return true;
        }

    }
    bool Socket::close() {
        if (!socketIsClosed) {
            int status = CLOSESOCKET(mSocketFD);
            return status == 0;
        }
        return true;
    }
    int Socket::getLastError() {
        return errno;
    }
}}


