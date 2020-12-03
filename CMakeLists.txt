
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

include_directories(src/core)

# PlayerLink Core Library Components
add_library(
        PlayerLink_Core
        src/core/crypto/hash/sha/sha256.cpp
        src/core/crypto/hash/sha/sha256.h

        src/core/crypto/pki/DFH.c

        src/core/net/Protocols.h
        src/core/net/Socket.h
        src/core/net/NetConfig.h
        src/core/net/SocketException.cpp
        src/core/net/SocketException.h
        src/core/net/Socket.cpp
        src/core/net/tcp/tcpsocket.h
        src/core/net/tcp/tcpsocket.cpp
        src/core/utils/logger/Logger.cpp
        src/core/utils/logger/Logger.h
        src/core/utils/logger/LogSeverity.h
 )

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    message("Boost Found")
    message(STATUS "Boost Version: ${Boost_VERSION}")
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
    INCLUDE_DIRECTORIES(${BOOST_LIBRARY_DIR})
    ADD_DEFINITIONS( "-DBOOST_ALL_NO_LIB " )
    set( Boost_USE_STATIC_LIBS ON ) # or Off, depending on what you want
ENDIF()
find_package(Boost 1.74.0 REQUIRED COMPONENTS thread date_time)

 add_library(
     PlayerLink_Core_WIN32
         src/platform/microsoft/win32/overlays/core/net/winsockinit.c
         src/platform/microsoft/win32/overlays/core/net/winsockinit.h
 )
# add_library(
#     PlayerLink_Core_UNIX
# )
# PlayerLink Client Shared Library (DLL)
add_library(
        PlayerLink_Client SHARED

        src/client/net/Client.cpp
        src/client/net/Client.h
)
# Build Server Program
add_executable(
        PlayerLink_Server

        src/server/main.cpp
        src/server/net/ServerSocket.cpp
        src/server/net/ServerSocket.h
        src/server/room/Client.cpp
        src/server/room/Client.h
        src/server/room/GameRoom.cpp
        src/server/room/GameRoom.h
        src/server/net/TCPServer.h
        src/server/net/TCPServer.cpp
        src/server/net/Message.h
        src/server/net/Player.h
        src/server/net/GameServer.h
        src/server/net/GameServer.cpp
  )
 
target_link_libraries(PlayerLink_Core PRIVATE Boost::thread)

IF(WIN32)
        target_link_libraries(PlayerLink_Core PRIVATE PlayerLink_Core_WIN32)
#ELSEIF(UNIX)
#        target_link_libraries(PlayerLink_Core PRIVATE PlayerLink_Core_UNIX)
ENDIF()
target_link_libraries(PlayerLink_Server PRIVATE PlayerLink_Core)
target_link_libraries(PlayerLink_Client PRIVATE PlayerLink_Core)


