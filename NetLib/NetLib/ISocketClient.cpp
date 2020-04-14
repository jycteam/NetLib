#include "ISocketClient.h"

ISocketClient::ISocketClient(void) : mDataSocekt()
{
  
}

ISocketClient::ISocketClient(DataSocket ds)
{
  this->mDataSocekt = ds;
}


ISocketClient::~ISocketClient(void){
	this->Disconnect();
}



VOID ISocketClient::Connect(LPSTR serverIP, UINT16 port, BOOL isAsyn)
{
  mDataSocekt.Connect(inet_addr(serverIP), port);
  
  if (this->isAsyn){
    std::thread recvThread(&ISocketClient::RecvMessageFunc, this);
    recvThread.detach();

    std::thread th(&ISocketClient::HandleMsg, this);
    th.detach();
  }
  return;
}

void ISocketClient::Disconnect()
{
  mDataSocekt.Close();
  for (auto msg : messages)
  {
    delete msg;
  }
  messages.clear();
}


void ISocketClient::RecvMessageFunc()
{
  char recvBuf[MAX_BUFFER];
  while (true)
	{
    int ret = mDataSocekt.Receive(recvBuf, sizeof(recvBuf));
		if (ret > 0)
		{
      addMessage(new SocketMessage(RECEIVE, (unsigned char*)recvBuf, ret));
		}
	}

  mDataSocekt.Close();

  this->OnDisconnect();
}

void ISocketClient::addMessage(SocketMessage* msg){
  std::lock_guard<std::mutex> lk(message_lock);
  messages.push_back(msg);
}



void ISocketClient::Send(UINT8* data, UINT32 datalen)
{
  mDataSocekt.Send((LPSTR)data, datalen);
}


void ISocketClient::HandleMsg()
{
  BOOL bStart = TRUE;
  while (bStart)
  {
    message_lock.lock();
    SocketMessage *msg = *(messages.begin());
    messages.pop_front();
    message_lock.unlock();

    switch (msg->getMsgType())
    {
    case RECEIVE:
      if (OnRecv)
      {
        this->OnRecv((UINT8*)msg->getMsgData()->getBytes(), msg->getMsgData()->getSize());
      }
      break;
    }
    delete msg;
    
  }
}
