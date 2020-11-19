//
// Created by hanzalah on 16/11/2020.
//

#include "SocketException.h"

SocketException::SocketException(const std::string &message)
    throw (): mUserMessage(message){}

    SocketException::~SocketException() throw() {}
    const char *SocketException::what() const throw() {
    return mUserMessage.c_str();
}
