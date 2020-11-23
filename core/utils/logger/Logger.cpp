//
// Created by hanzalah on 08/11/2020.
//

#include "Logger.h"
Logger::Logger() {}
Logger::~Logger() {}

Logger * Logger::getLogger() {
    std::lock_guard<std::mutex> lock(mMutex);
    if(mInstance == nullptr){
        mInstance = new Logger();
    }
    return mInstance;
}