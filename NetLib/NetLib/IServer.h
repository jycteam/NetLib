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
  virtual void Send(IClientProxy* clientProxy, UINT8* data, UINT32 len) = 0; //���͸�ָ���ͻ�������
  virtual void Send(UINT8* data, UINT32 len) = 0; //
  virtual void Stop() = 0;

protected:
  virtual void OnStart(LPWSTR ip) = 0;  //��Ӧ����������
  virtual void OnNewConnection(IClient* client) = 0; //��Ӧ�¿ͻ�������
  virtual void OnRecv(IClient* client, UINT8* data, UINT32 count) = 0; //��Ӧ�յ��ͻ�����Ϣ
  virtual void OnDisconnect(IClient* client) = 0;
};


