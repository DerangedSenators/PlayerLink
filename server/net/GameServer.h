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
class GameServer {
public:
	GameServer();
	~GameServer();

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