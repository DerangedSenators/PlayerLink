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
#include "GameServer.h"


namespace PlayerLink{namespace Server{
	GameServer::GameServer() : mRunSignal(true) {
		mTCPServerSocket.listen(DEFAULT_TCP_PORT);
	}

	GameServer::~GameServer() {}

	void GameServer::start(std::string name) {
		//	new mServerThreads();
		mServerThreads.create_thread(boost::bind(&GameServer::acceptLoop, this));
		mServerThreads.create_thread(boost::bind(&GameServer::readLoop, this));
		mServerThreads.create_thread(boost::bind(&GameServer::writeLoop, this));
		mServerThreads.join_all();
		mTCPServerSocket.close();
		// Log Server Closure

	}
	void GameServer::acceptLoop() {
		while (mRunSignal) {
			TCPSocket client = mTCPServerSocket.accept();
			std::string clientPort = std::to_string(client.getPort());
			// ADD LOG INPUT HERE TO LOG THE CONNECTION
			mQueueMutex.lock();
			char username[DEFAULT_BUFFER_SIZE];
			int result = client.recieve(&username, sizeof username); //Recieve a username to build up a player
			if (result > 0) {
				Player mPlayer(std::to_string(client.getSocketDescriptor()), username, std::to_string(client.getPort()));
				mPlayers[mPlayer.mIP + ":" + mPlayer.mID] = mPlayer;
			}
			else {
				client.close();
				throw SocketException("Unable to recieve bytes from client" + client.getAddress());
			}
			mQueueMutex.unlock();

			// Sleep for a bit
			std::this_thread::sleep_for(std::chrono::microseconds(SLEEP_DELAY));

		}
	}

	void GameServer::readLoop() {
		while (mRunSignal) {
			if (!mPlayers.empty()) {
				std::vector<TCPSocket> events = mTCPServerSocket.getSocketEvents(SLEEP_DELAY);
				for (auto& client : events) {
					char recvBytes[DEFAULT_BUFFER_SIZE];
					int iResult = client.recieve(&recvBytes, sizeof recvBytes);
					if (iResult == 0 || ((recvBytes != NULL) && (recvBytes[0] == '\0')) || reinterpret_cast<long>(recvBytes) == DISCONNECT_REQUEST_CODE) {
						disconnectClient(client); // Disconnect the client from the server as they have sent an empty message
					}
					else {
						//	PlayerMessage m(client.getSocketDescriptor(), &recvBytes);
					}
				}
			}
		}
	}

	void GameServer::writeLoop() {
		while (mRunSignal) {
			if (!mPlayers.empty() && !mMessageQueue.empty()) {
				Message msg = mMessageQueue.front();
				mQueueMutex.lock();
				for (auto& client : mClients) {
					if (client.getSocketDescriptor() != msg.mSockID) {
						//Send message here!
						//WIP if message does not send, unlock the mutex and disconnect the client
						//Unlock the mutex. Good to go
					}
					mMessageQueue.pop_front();
					//mQueueMutex.unlock();
				}
				mQueueMutex.unlock();
				std::this_thread::sleep_for(std::chrono::microseconds(SLEEP_DELAY));
			}
		}
	}
	void GameServer::disconnectClient(TCPSocket& client) {
		mQueueMutex.lock();
		std::vector<TCPSocket>::iterator clientIT = mClients.begin();
		while (clientIT != mClients.end()) {
			if (clientIT->getSocketDescriptor() == client.getSocketDescriptor()) {
				Player player = mPlayers[clientIT->getAddress() + ":" + std::to_string(clientIT->getSocketDescriptor())];
				// Log user disconnect
				clientIT = mClients.erase(clientIT);
				mPlayers.erase(clientIT->getAddress() + ":" + std::to_string(clientIT->getSocketDescriptor()));

				mTCPServerSocket.unmonitor(client);
				client.close();
				break;

			}
			else {
				clientIT++;
			}
		}
	}

	const std::string GameServer::currentTime()
	{
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
		// for more information about date/time format %Y-%m-%d.
		strftime(buf, sizeof(buf), "%X", &tstruct);

		return buf;
	}
}}

