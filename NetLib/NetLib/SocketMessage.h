#pragma once
  
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#include <list>
#include <thread>
#include <mutex>
#include <WinSock2.h>
#include "Data.h"

#pragma comment(lib, "WS2_32.lib")

#define MSG_UPDATA_INTERVAL 200  //ºÁÃë

enum MessageType
{
	DISCONNECT,
	RECEIVE,
	NEW_CONNECTION
};

class SocketMessage
{
private:
	MessageType msgType;
	Data* msgData;

public:
	SocketMessage(MessageType type, unsigned char* data, int dataLen)
	{
		msgType = type;
		msgData = new Data();
		msgData->copy(data, dataLen);
	}

	SocketMessage(MessageType type)
	{
		msgType = type;
		msgData = nullptr;
	}

	Data* getMsgData() { return msgData; }
	MessageType getMsgType() { return msgType; }

	~SocketMessage()
	{
		if (msgData)
			delete msgData;
	}
};
