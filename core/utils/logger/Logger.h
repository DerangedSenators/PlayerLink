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

#ifndef PLAYERLINK_CORE_LOGGER_H
#define PLAYERLINK_CORE_LOGGER_H


#include <string>
#include <mutex>
#include "LogSeverity.h"

namespace PlayerLink{namespace Core{
    /**
     * @brief A Singelton Logger class which will be used by PlayerLink to create logs based on a severity level and append to a logfile
     * @author Hanzalah Ravat
     * @author Ashwin Jaimal
     */
    class Logger {
    private:
        static Logger* mInstance;
        static std::mutex mMutex;
        Logger();
        ~Logger();

    public:
        /**
         * Singleton Class should not be cloneable. Constructor used to prevent multiple instances of Logger
         */
        Logger(Logger& otherLogger) = delete;

        /**
         * Singleton classes must not be assignable. This method will prevent the class from being assingned
         */
        void operator = (const Logger&) = delete;

        /**
         * Gets the running logger instance pointer
         * @return A pointer to the Logger Instance in memory
         */
        static Logger* getLogger();
        /**
         * Method used to log an event
         * @param severity The Severity level of the log
         * @param message The message which will be written into the logfile
         */
        void log(LogSeverity severity, std::string message);

    };
}}



#endif //PLAYERLINK_CORE_LOGGER_H
