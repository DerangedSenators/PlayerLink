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
        core/net/NetConfig.h core/net/SocketException.cpp core/net/SocketException.h core/net/Socket.cpp core/net/tcp/tcpsocket.h core/net/tcp/tcpsocket.cpp 
)
# PlayerLink Client Shared Library (DLL)
add_library(
        PlayerLink_Client SHARED

        client/net/Client.cpp client/net/Client.h)
# Build Server Program
add_executable(
        PlayerLink_Server
        server/main.cpp
        server/net/ServerSocket.cpp
        server/net/ServerSocket.h
        core/utils/logger/Logger.cpp
        core/utils/logger/Logger.h
        core/utils/logger/LogSeverity.h
        server/room/Client.cpp
        server/room/Client.h
        server/room/GameRoom.cpp
        server/room/GameRoom.h
        server/net/TCPServer.h 
        server/net/TCPServer.cpp
)

target_link_libraries(PlayerLink_Server PRIVATE PlayerLink_Core)
target_link_libraries(PlayerLink_Client PRIVATE PlayerLink_Core)