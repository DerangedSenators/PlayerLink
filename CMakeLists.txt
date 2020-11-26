
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

cmake_minimum_required(VERSION 3.17)
project(PlayerLink)

set(CMAKE_CXX_STANDARD 20)

include_directories(core)
# PlayerLink Core Library Components
add_library(
        PlayerLink_Core
        core/crypto/hash/sha/sha256.cpp
        core/crypto/hash/sha/sha256.h

        core/crypto/pki/DFH.c

        core/net/Protocols.h
        core/net/Socket.h
        core/net/NetConfig.h 
        core/net/SocketException.cpp 
        core/net/SocketException.h 
        core/net/Socket.cpp 
        core/net/tcp/tcpsocket.h 
        core/net/tcp/tcpsocket.cpp 
        core/utils/logger/Logger.cpp
        core/utils/logger/Logger.h
        core/utils/logger/LogSeverity.h
 )

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    message("Boost Found")
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    INCLUDE_DIRECTORIES(${BOOST_LIBRARY_DIR})
    ADD_DEFINITIONS( "-DBOOST_ALL_NO_LIB " )
    set( Boost_USE_STATIC_LIBS ON ) # or Off, depending on what you want
ENDIF()
find_package(Boost COMPONENTS thread REQUIRED)

 #add_library(
 #    PlayerLink_Core_WIN32
 #)
# add_library(
#     PlayerLink_Core_UNIX
# )
# PlayerLink Client Shared Library (DLL)
add_library(
        PlayerLink_Client SHARED

        client/net/Client.cpp client/net/Client.h )
# Build Server Program
add_executable(
        PlayerLink_Server
        server/main.cpp
        server/net/ServerSocket.cpp
        server/net/ServerSocket.h
        server/room/Client.cpp
        server/room/Client.h
        server/room/GameRoom.cpp
        server/room/GameRoom.h
        server/net/TCPServer.h 
        server/net/TCPServer.cpp
        server/net/Message.h
        server/net/Player.h
        server/net/GameServer.h
        server/net/GameServer.cpp
 )
 
target_link_libraries(PlayerLink_Core PRIVATE Boost::thread)
#
#IF(WIN32)
#    target_link_libraries(PlayerLink_Core PRIVATE PlayerLink_Core_WIN32)
#ELSEIF(UNIX)
#    target_link_libraries(PlayerLink_Core PRIVATE PlayerLink_Core_UNIX)
#ENDIF()
target_link_libraries(PlayerLink_Server PRIVATE PlayerLink_Core)
target_link_libraries(PlayerLink_Client PRIVATE PlayerLink_Core)


