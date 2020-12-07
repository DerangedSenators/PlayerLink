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

FIND_PACKAGE(Boost)
IF (Boost_FOUND)
    message("Boost Found")
    message(STATUS "Boost Version: ${Boost_VERSION}")
    message(STATUS "BOOST Path: ${BOOST_ROOT}")
    find_package(Boost 1.74.0 REQUIRED COMPONENTS thread date_time)
    if(WIN32)
        INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
        INCLUDE_DIRECTORIES(${BOOST_LIBRARY_DIR})
    ENDIF()
    ADD_DEFINITIONS( "-DBOOST_ROOT" )
    set( Boost_USE_STATIC_LIBS ON ) # or Off, depending on what you want
    #target_link_libraries(PlayerLink ${BOOST_LIBRARIES})
ENDIF()

