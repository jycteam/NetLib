#pragma once
#include "../NetLib/pub_header.h"
#include "Message.h"

class IClientProxy{
public:
  //������Ϣ����Ӧ�� IClient����
  virtual void Send(const Message* msg) = 0; 
  
  //��������IClient�������Ϣ
  virtual void Recv(Message* msg) = 0; 
  
  //�رպͶ�ӦIClient��ͨ��
  virtual void Close() = 0;
};

class IServer
{
public:
  //����ͨ��Server
  virtual void Start() = 0;
  
  //ֹͣͨ��Server
  virtual void Stop() = 0;
  
  //������Ϣ��ָ���ͻ�����Ϣ
  virtual void Send(IClientProxy* clientProxy, Message* msg) = 0; 
  
  //������Ϣ�����������ӿͻ�����Ϣ
  virtual void Send(Message* msg)  = 0; 
  
  // �ر�ĳ���ͻ��� 
  virtual void Close(IClientProxy* client) = 0; 
};


