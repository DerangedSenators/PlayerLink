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

add_subdirectory(crypto)
add_subdirectory(net)
add_subdirectory(utils)

add_library(
        PLAYERLINK_CORE
        PlayerLinkCore.h

        ${CRYPTO_SOURCES}

        ${NET_SOURCES}
        ${UTILS_EXCEPTION_SOURCES}
        ${UTILS_LOGGER_SOURCES}
)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set_target_properties(PLAYERLINK_CORE PROPERTIES LINKER_LANGUAGE CXX)