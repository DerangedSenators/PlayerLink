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

#ifndef PLAYERLINK_CORE_SOCKETEXCEPTION_H
#define PLAYERLINK_CORE_SOCKETEXCEPTION_H

#include <string>
#include "utils/exceptions/RuntimeException.h"

namespace PlayerLink{namespace Core{
    class SocketException : public RuntimeException {
    private:
        std::string mUserMessage; //Message for Exception
    public:
        /**
         * @brief Creates a SocketException
         * @param message A description of the error
         * @return
        */
        SocketException(std::string  message) throw();
        ~SocketException() throw();
        const char* what() const throw();

    };
}}
 
 /**
 * @brief Socket Exception class used for socket errors
*/



#endif //PLAYERLINK_CORE_SOCKETEXCEPTION_H