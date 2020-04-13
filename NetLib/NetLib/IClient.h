#pragma once
#include "pub_header.h"

class IClient
{
public:
  virtual void Connect() = 0;
  virtual void Send(Message* msg) = 0;
  virtual void Recv(Message* msg) = 0;
  virtual void Disconnect() = 0;
};

