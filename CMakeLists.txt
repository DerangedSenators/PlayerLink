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
project(PlayerLink
        VERSION 1.0.0
        DESCRIPTION "Multiplayer API written in C++. Can be used for multiplayer games where server side processing needs to be kept as low as possible"
        )

set(CMAKE_CXX_STANDARD 20)

include_directories(src/core)

# add_library(
#     PlayerLink_Core_UNIX
# )

include(include/boost.cmake)
add_subdirectory(src/core)
add_subdirectory(src/client)
add_subdirectory(src/server)

target_link_libraries(PLAYERLINK_CORE PRIVATE Boost::thread)

IF(WIN32)
        add_subdirectory(src/platform/microsoft/win32/overlays/core)
        target_link_libraries(PLAYERLINK_CORE PRIVATE PLAYERLINK_CORE_WIN32)
#ELSEIF(UNIX)
#        target_link_libraries(PlayerLink_Core PRIVATE PlayerLink_Core_UNIX)
ENDIF()
target_link_libraries(PLAYERLINK_SERVER PRIVATE PLAYERLINK_CORE)
target_link_libraries(PLAYERLINK_CLIENT PRIVATE PLAYERLINK_CORE)


