#pragma once
#include "pub_header.h"

class IClient
{
public:
<<<<<<< HEAD
  virtual void Connect() = 0;
  virtual void Send(Message* msg) = 0;
  virtual void Recv(Message* msg) = 0;
  virtual void Disconnect() = 0;
=======
  virtual VOID Connect(LPSTR serverIP, UINT16 port, BOOL isAsyn = TRUE) = 0;
  virtual void Send(UINT8* data, UINT32 datalen) = 0;
  virtual void Disconnect() = 0;

private:
  virtual void OnConnected(BOOL bConnect) = 0;
  virtual void OnRecv(UINT8* data, UINT32 datalen) = 0;
  virtual void OnDisconnect() = 0; //
>>>>>>> 0e532d0159a3dfe201d7538a72b57c286c767740
};

