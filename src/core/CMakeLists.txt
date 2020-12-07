# Copyright 2020 Deranged Senators
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# PlayerLink Core Library Components
# Add subdirs
project(PLAYERLINK_CORE)
add_subdirectory(crypto)
add_subdirectory(net)
add_subdirectory(utils)

add_library(
        PLAYERLINK_CORE
        PlayerLinkCore.h

        crypto/hash/sha/sha256.h
        crypto/hash/sha/sha256.cpp

        net/NetConfig.h
        net/Socket.h
        net/ServerCodes.h
        net/Protocols.h
        net/Socket.cpp
        net/tcp/tcpsocket.h
        net/tcp/tcpsocket.cpp

        utils/logger/LogSeverity.h
        utils/logger/Logger.h
        utils/logger/Logger.cpp
        utils/exceptions/RuntimeException.h
        utils/exceptions/RuntimeException.cpp
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set_target_properties(PLAYERLINK_CORE PROPERTIES LINKER_LANGUAGE CXX)
