#pragma  once

#include "IClient.h"
#include "pub_header.h"
#include "DataSocket.h"
#include "SocketMessage.h"

class ISocketClient : public IClient
{
public:
  virtual VOID Connect(LPSTR serverIP, UINT16 port, BOOL isAsyn = TRUE);
  virtual void Send(UINT8* data, UINT32 datalen);
  virtual void Disconnect();

private:
  virtual void OnRecv(UINT8* data, UINT32 datalen) = 0;
  virtual void OnDisconnect() = 0; 

protected:
	ISocketClient(void);
  ISocketClient(DataSocket ds);
	~ISocketClient(void);

private:
	void HandleMsg();
	void RecvMessageFunc();
  void addMessage(SocketMessage* msg);

private:
	DataSocket mDataSocekt;
	std::list<SocketMessage*> messages;
	std::mutex   message_lock;
  BOOL isAsyn = TRUE;
};

