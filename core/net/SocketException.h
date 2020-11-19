//
// Created by hanzalah on 16/11/2020.
//

#ifndef PLAYERLINK_CORE_SOCKETEXCEPTION_H
#define PLAYERLINK_CORE_SOCKETEXCEPTION_H

#include <string>
#include <exception>

class SocketException : public std::exception {
private:
std::string mUserMessage; //Message for Exception
public:
    SocketException(const std::string &message) throw();
    ~SocketException() throw();
    const char *what() const throw();

};


#endif //PLAYERLINK_CORE_SOCKETEXCEPTION_H
