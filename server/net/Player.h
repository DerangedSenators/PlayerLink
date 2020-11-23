#ifndef PLAYERLINK_SERVER_PLAYER_H
#define PLAYERLINK_SERVER_PLAYER_H
typedef struct Player {
	Player(){}
	Player(std::string id, std::string userName, std::string ip) {
		mID = id;
		mUserName = userName;
		mIP = ip;
	}
	std::string mID, mUserName, mIP;
}Player;
#endif