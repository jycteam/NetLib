#pragma once
#include "../NetLib/pub_header.h"
#include "IClient.h"

class IClientProxy{
public:
  virtual void Send(UINT8* data, UINT32 len) = 0;
  virtual void Recv(UINT8* data, UINT32 datalen) = 0;
  virtual void Close() = 0;
};

class IServer
{
public:
  virtual VOID Start() = 0;
  virtual void Send(IClientProxy* clientProxy, UINT8* data, UINT32 len) = 0; //发送给指定客户端数据
  virtual void Send(UINT8* data, UINT32 len) = 0; //
  virtual void Stop() = 0;

protected:
  virtual void OnStart(LPWSTR ip) = 0;  //响应服务器启动
  virtual void OnNewConnection(IClient* client) = 0; //响应新客户端连接
  virtual void OnRecv(IClient* client, UINT8* data, UINT32 count) = 0; //响应收到客户端消息
  virtual void OnDisconnect(IClient* client) = 0;
};


