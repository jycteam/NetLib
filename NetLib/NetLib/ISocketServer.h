#pragma once

#include "SocketMessage.h"
#include "ListenSocket.h"
#include "IServer.h"

#define DATA_SIZE 1024
#define MAX_CONNECT 5
#define MAX_BUFFER 1024


/*class SocketPortListener{
public:
  void Listening(UINT16 port){
    mListeningSocket.Listening(port);
  }
  ISocketClient* NewClient(){
    DataSocket ds = mListeningSocket.Accept();
    return 
  }
private:
  ListeningSocket mListeningSocket;
}*/


class SocketClientProxy : IClientProxy{
public:
  SocketClientProxy(DataSocket ds){
    this->ds = ds;
  }

  virtual void Send(UINT8* data, UINT32 len){
    ds.Send((LPSTR)data, len);
  }

  virtual void Recv(UINT8* data, UINT32 datalen){
    ds.Receive((LPSTR)data, datalen);
  }

  virtual void Close(){
    ds.Close();
  }

private:
  DataSocket ds;
};

struct RecvData
{
  IClientProxy* socketClient;
  int dataLen;
  char data[DATA_SIZE];
};


class ISocketServer : IServer
{
public:
  virtual VOID Start();                                               //����ͨ�ŷ���Server��
  virtual void Send(IClientProxy* client, UINT8* data, UINT32 len);     //������Ϣ��ָ���ͻ���
  virtual void Send(UINT8* data, UINT32 len);                      //������Ϣ�������������ӿͻ���
  virtual VOID Stop();

protected:
  //virtual void OnStart(LPWSTR ip) = 0;                                //��Ӧ����������
  virtual void OnNewConnection(IClient* client)=0;                    //��Ӧ�¿ͻ�������
  virtual void OnRecv(IClient* client, UINT8* data, UINT32 count)=0;  //��Ӧ�յ��ͻ�����Ϣ
  virtual void OnDisconnect(IClient* client) = 0;
protected:
	ISocketServer();
	~ISocketServer();
private:
  void ListenFunc();
  void HandleMsg();	//�첽��Ϣ����ص�
  void update();
  void RecvMessage(IClientProxy* icp);

private:
	
  ListeningSocket mListener;
	UINT16 mPort;
  BOOL   bStart;
private:
  std::list<IClient*> scpS;

  std::mutex   messages_lock;
  std::list<SocketMessage*> messages;
  
};
