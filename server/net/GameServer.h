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
#ifndef PLAYERLINK_SERVER_GAME_SERVER_H
#define PLAYERLINK_SERVER_GAME_SERVER_H
#include <mutex>
#include <thread>
#include <map>
#include <deque>
#include <vector>
#include <chrono>
#include <boost/thread.hpp>

#include "TCPServer.h"
#include "Message.h"
#include "Player.h"
#include "net/ServerCodes.h"

#define THREAD_COUNT 3
/**
 * @brief A GameServer object which is used to host a game or lobby. It uses three threads to efficiently do this; An accept thread to allow new players to join, a read thread to read packets sent by players to the server and a write thread to relay those messages to the other players
*/
class GameServer {
public:
	/**
	 * @brief Constructs a GameServer
	 * @return 
	*/
	GameServer();
	~GameServer();
	/**
	 * @brief Starts the GameServer
	 * @param name 
	*/
	void start(std::string name);
private:
	/**
	 * @brief 
	 * @param arg 
	 * @return 
	
	friend void* doServerAccept(void* arg);
	friend void* doServerRead(void* arg);
	friend void* doServerWrite(void* arg);
	*/
	void acceptLoop();
	void readLoop();
	void writeLoop();

	void disconnectClient(TCPSocket& client);
	
	const std::string currentTime();

	bool mRunSignal;
	TCPServer mTCPServerSocket;

	std::string mRoomName;
	std::deque<Message> mMessageQueue;
	std::vector<TCPSocket> mClients;
	std::map<std::string, Player> mPlayers;

	std::mutex mQueueMutex;
	boost::thread mAcceptThread, mReadThread, mWriteThread;
	boost::thread_group mServerThreads;
	
};
#endif