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
#include "Client.h"
#include <net\ServerCodes.h>

namespace PlayerLink{namespace Client{

	Client::Client(std::string server, std::string port) : mRunSignal(true) {
		mServer = server;
		mPort = port;
		// Try to connnect to the server
		mClientSocket.connectWithTimeout(server.c_str(), port.c_str(), TIMEOUT_SECONDS, TIMEOUT_MICROSECONDS);
	}

	Client::~Client() {
		if (mRunSignal) {
			mExitMutex.lock();
			mClientSocket.sendBytes((unsigned char *) DISCONNECT_REQUEST_CODE);
			mClientSocket.close();
			mRunSignal = false;
			mExitMutex.unlock();
		}
	}

	bool Client::login(std::string usrName) {
		mUserName = usrName;
		unsigned char* userNameAsChar;
		mClientSocket.sendBytes((unsigned char *)usrName.c_str());
		mThreadGroup.create_thread(boost::bind(&Client::readLoop,this));
		mThreadGroup.create_thread(boost::bind(&Client::writeLoop,this));

		mThreadGroup.join_all();
		mClientSocket.close();
		return 0;
	}

	void Client::logout() {
		mClientSocket.sendBytes((unsigned char*) DISCONNECT_REQUEST_CODE);
		mExitMutex.lock();
		mRunSignal = false;
		mExitMutex.unlock();
	}

	void Client::addMsgToBuffer(unsigned char* message) {
		mMessageOutQueue.push_back(message);
	}

	void Client::readLoop() {
		unsigned char* bytes;
		while (mRunSignal) {
			if (mClientSocket.canReceive(SLEEP_DELAY)) {
				bytes = mClientSocket.recieveBytes();
				mMessageInQueue.push_back(bytes);
				std::this_thread::sleep_for(std::chrono::microseconds(SLEEP_DELAY));
			}
		}
	}

	void Client::writeLoop() {
		unsigned char* outMsg;
		char outBuff[DEFAULT_BUFFER_SIZE] = { 0 };
		while (mRunSignal) {
			// WIP: Get the buffer and write it to the outmsg
			if (!mMessageOutQueue.empty()) {
				//Check if the buffer holds the exit message. If it is, run the logout method...
				outMsg = mMessageOutQueue.front();
				if (outMsg[0] == DISCONNECT_REQUEST_CODE) {
					logout();
				}
				else {
					mMessageOutQueue.pop_front();
					mClientSocket.sendBytes(outMsg);
				}
				outMsg = NULL;
				memset(outBuff, 0, DEFAULT_BUFFER_SIZE);
			}
		}
	}
}}