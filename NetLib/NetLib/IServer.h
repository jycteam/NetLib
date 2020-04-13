#pragma once
#include "../NetLib/pub_header.h"
#include "Message.h"

class IClientProxy{
public:
  //发送消息给对应的 IClient对象
  virtual void Send(const Message* msg) = 0; 
  
  //接受来自IClient对象的消息
  virtual void Recv(Message* msg) = 0; 
  
  //关闭和对应IClient的通信
  virtual void Close() = 0;
};

class IServer
{
public:
  //启动通信Server
  virtual void Start() = 0;
  
  //停止通信Server
  virtual void Stop() = 0;
  
  //发送消息给指定客户端消息
  virtual void Send(IClientProxy* clientProxy, Message* msg) = 0; 
  
  //发送消息给所有已连接客户端消息
  virtual void Send(Message* msg)  = 0; 
  
  // 关闭某个客户端 
  virtual void Close(IClientProxy* client) = 0; 
};


