//
// Created by Hanzalah Ravat on 08/11/2020.
//

#ifndef PLAYERLINK_CORE_LOGGER_H
#define PLAYERLINK_CORE_LOGGER_H


#include <string>
#include "LogSeverity.h"

class Logger {
// Fields
public:

private:
    std::string filePath;
    LogSeverity loggingSeverity;
//Method Declarations
public:
    /**
     * Will log the message if the severity is within recording range.
     * @param level  The log severity
     * @param message The message to be logged
     */
    static void log(LogSeverity level,std::string message);

private:
    void writeAllLogs();
    /**
     * Formats a log before writing to log file
     * @param message The message sent from the application
     * @param severity The severity of the Log
     */
    void formatLog(std::string message,LogSeverity severity);
    /**
     * Appends a Log
     * @param log
     */
    void appendLog(std::string log);
};


#endif //PLAYERLINK_CORE_LOGGER_H
