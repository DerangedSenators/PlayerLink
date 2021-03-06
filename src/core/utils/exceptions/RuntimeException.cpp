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

#include "RuntimeException.h"
#include "utils/logger/Logger.h"

namespace PlayerLink{namespace Core{

    RuntimeException::RuntimeException(const char* message,
                                       const boost::source_location &location)
            : runtime_error(message) {
        runtimeMessage = message;
    }
    const char* RuntimeException::what() const throw() {
        Logger* logger = Logger::getLogger();
        logger->log(ERROR,runtimeMessage);
        return runtimeMessage;
    }
}}