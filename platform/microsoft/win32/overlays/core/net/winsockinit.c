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
#include <WinSock2.h>
#include <Windows.h>

#include "winsockinit.h"

bool init(){
    int iResult;
    WSADATA wsaData;
    iResult = WSAStartup(MAKEWORD(2,2),&wsaData);
    if(iResult !=0){
        //Throw some exception
        return false;
    } else{
        return true;
    }
}