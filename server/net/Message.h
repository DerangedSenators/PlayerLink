#ifndef PLAYERLINK_SERVER_MESSAGE_H
#define PLAYERLINK_SERVER_MESSAGE_H
typedef struct Message {
	Message() {}
	Message(int sock_id, char* bytes) {
		mSockID = sock_id;
		mBytes = bytes;
	}
	int mSockID;
	char* mBytes;
} PlayerMessage;
#endif