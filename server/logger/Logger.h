//
// Created by hanzalah on 08/11/2020.
//

#ifndef PLAYERLINK_CORE_LOGGER_H
#define PLAYERLINK_CORE_LOGGER_H


#include <string>

class Logger {
    static Logger getLogger();

    static void createNewLogger(std::string path,int opcode);

    static void log(std::string message);
};


#endif //PLAYERLINK_CORE_LOGGER_H
