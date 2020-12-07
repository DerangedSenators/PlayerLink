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

#include "Logger.h"
#include <fstream>
#include <chrono>
#include <ctime>
#define SPACE +" "+
namespace PlayerLink{namespace Core{
    Logger* Logger::mInstance = nullptr;
    std::mutex Logger::mMutex;
    Logger::Logger() {}
    Logger::~Logger() {}

    Logger* Logger::getLogger() {
        std::lock_guard<std::mutex> lock(mMutex);
        if (mInstance == nullptr) {
            mInstance = new Logger();
        }
        return mInstance;
    }
    void Logger::log(LogSeverity severity, std::string message,const boost::source_location& location)
    {
   
        //timing
        using Clock = std::chrono::steady_clock;
        auto tick = Clock::now;
        const std::string str_time = boost::posix_time::to_iso_string(boost::posix_time::second_clock::local_time());
        std::string fName = location.file_name();
        std::string lFunction = location.function_name();
        std::string locationSTR = fName + lFunction;
        std::string strSeverity;
        switch(severity){
            case FATAL:
                strSeverity = "FATAL";
                break;
            case ERROR:
                strSeverity = "ERROR";
                break;
            case WARNING:
                strSeverity = "WARNING";
                break;
            case INFO:
                strSeverity = "INFO";
                break;
            case DEBUG:
                strSeverity = "DEBUG";
                break;
            case TRACE:
                strSeverity = "TRACE";
                break;
        }
        std::string logSev = "LOGSEVERITY: " + strSeverity SPACE "Location: " + locationSTR  SPACE + "Message: " SPACE message;
        //files the logger
        std::ofstream logFile;
        logFile.open("LOG FILE.txt",std::ios_base::app);
        std::string out =  "[" + str_time SPACE logSev + "]";
        logFile << out;
        logFile << "\n";
        logFile.close();

    }
}}

