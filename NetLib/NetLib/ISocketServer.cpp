#include "ISocketServer.h"
#include <iostream>


ISocketServer::ISocketServer(){

}

ISocketServer::~ISocketServer()
{
  this->Stop();
};

void ISocketServer::Stop()
{
  mListener.Close();
}

VOID ISocketServer::Start()
{
  bStart = TRUE;
  std::thread linstening_thread(&ISocketServer::ListenFunc, this);
  linstening_thread.detach();

  std::thread handle_msg_thread(&ISocketServer::HandleMsg, this);
  handle_msg_thread.detach();
  return;
}


void ISocketServer::ListenFunc(){

  mListener.Listening(mPort);
  
  while (bStart){
    DataSocket ds = mListener.Accept();
    SocketClientProxy*  scp = new SocketClientProxy(ds);
    scpS.push_back(scp);
    
    // 
    std::lock_guard<std::mutex> lock(messages_lock);
    SocketMessage * msg = new SocketMessage(NEW_CONNECTION, (unsigned char*)&ds, sizeof(DataSocket));
    messages.push_back(msg);


    std::thread recive_msg_thread(&ISocketServer::RecvMessage, this, scp);
    recive_msg_thread.detach();   
	}
}



void ISocketServer::HandleMsg()
{
	while (bStart)
	{
		this->update();
		Sleep(MSG_UPDATA_INTERVAL);
	}
}


void ISocketServer::RecvMessage(IClientProxy* scp)
{
	UINT8 buff[MAX_BUFFER];
	int ret = 0;

	while (true)
	{
    scp->Recv(buff, sizeof(buff));
    
    std::lock_guard<std::mutex> lk(messages_lock);
    RecvData recvData;
    recvData.socketClient = scp;
    memcpy(recvData.data, buff, ret);
    recvData.dataLen = ret;
    SocketMessage * msg = new SocketMessage(RECEIVE, (unsigned char*)&recvData, sizeof(RecvData));
    
    messages.push_back(msg);
	}

DISCONNECT_PROC:
  scp->Close();
	if (OnDisconnect != nullptr)
	{
		std::lock_guard<std::mutex> lk(messages_lock);
		SocketMessage * msg = new SocketMessage(DISCONNECT, (unsigned char*)&socket, sizeof(SOCKET));
		messages.push_back(msg);
	}
}

void ISocketServer::Send(IClientProxy* icp, UINT8* data, UINT32 count)
{
  icp->Send(data, count);
}

void ISocketServer::Send(UINT8*data, UINT32 dataLen)
{
	for (auto& scp : scpS)
	{
    scp->Send(data, dataLen);
	}
}



void ISocketServer::update()
{
	if (messages.size() == 0)
	{
		return;
	}

	messages_lock.lock();

	if (messages.size() == 0)
	{
		messages_lock.unlock();
		return;
	}

	SocketMessage *msg = *(messages.begin());
	messages.pop_front();

	switch (msg->getMsgType())
	{
	case NEW_CONNECTION:
		if (OnNewConnection)
		{
			this->OnNewConnection(*(SOCKET*)msg->getMsgData()->getBytes());
		}
		break;
	case DISCONNECT:
		if (OnDisconnect)
		{
			this->OnDisconnect(*(SOCKET*)msg->getMsgData()->getBytes());
		}
		break;
	case RECEIVE:
		if (OnRecv)
		{
			RecvData* recvData = (RecvData*)msg->getMsgData()->getBytes();
			this->OnRecv(recvData->socketClient, (const char*)recvData->data, recvData->dataLen);
		}
		break;
	default:
		break;
	}

	delete msg;
	messages_lock.unlock();
}