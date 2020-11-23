//
// Created by Hanzalah Ravat on 08/11/2020.
//

#ifndef PLAYERLINK_CORE_LOGGER_H
#define PLAYERLINK_CORE_LOGGER_H


#include <string>
#include <mutex>
#include "LogSeverity.h"

class Logger{
private:
    static Logger* mInstance;
    static std::mutex mMutex;
    Logger();
    ~Logger();

public:
    /**
     * Singleton Class should not be cloneable
     */
     Logger(Logger &otherLogger) = delete;

     /**
      * Singleton classes must not be assignable
      */
      void operator = (const Logger&) = delete;

      static Logger *getLogger();

      void log(LogSeverity severity, std::string message);

};

#endif //PLAYERLINK_CORE_LOGGER_H
