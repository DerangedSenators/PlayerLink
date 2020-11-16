cmake_minimum_required(VERSION 3.17)
project(PlayerLink)

set(CMAKE_CXX_STANDARD 20)

# PlayerLink Core Library Components
add_library(
        PlayerLink_Core
        crypto/hash/sha/sha256.cpp
        crypto/hash/sha/sha256.h

        crypto/pki/DFH.c

        net/Protocols.h
        net/Socket.h
        net/NetConfig.h)
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
        utils/logger/Logger.cpp
        utils/logger/Logger.h
        utils/logger/LogSeverity.h
        server/room/Client.cpp
        server/room/Client.h
        server/room/GameRoom.cpp
        server/room/GameRoom.h
)

target_link_libraries(PlayerLink_Server PRIVATE PlayerLink_Core)
target_link_libraries(PlayerLink_Client PRIVATE PlayerLink_Core)