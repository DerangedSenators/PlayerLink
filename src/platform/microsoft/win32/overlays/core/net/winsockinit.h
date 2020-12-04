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

#ifndef PLAYERLINK_WINSOCKINIT_H
#define PLAYERLINK_WINSOCKINIT_H

/*
 * @file winsockinit.c
 * @author Hanzalah Ravat
 * @brief The methods included within this file are used by Windows editions of PlayerLink to initialise the Winsock2 Library
 *
 * As Winsock2 is available within a DLL, all processes must initialise the use of the DLL before being able to make winsock-function calls.
 * It also performs a check to ensure that Winsock features are fully present
 * @see https://docs.microsoft.com/en-us/windows/win32/winsock/initializing-winsock
 */

#include <WinSock2.h>
#include <Windows.h>

/*
 * Attempts to initialise winsock2.dll
 * @return true if startup succeeds
 * @return false if there is an error when trying to initialise Winsock2.dll
 */
int init(void);

#endif //PLAYERLINK_WINSOCKINIT_H
