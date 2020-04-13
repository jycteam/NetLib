#pragma once
#include "pub_header.h"
#include "SocketTypes.h"
#include "SocketErrors.h"
#include "Socket.h"

class DataSocket : public BaseSocket
{
public:
  DataSocket(sock p_socket = -1);

  BOOL Connect(const std::string& ip, UINT16 port);
  
  int Send(const Message* msg);
  
  int Recv(Message* msg);
  
  void Close();

protected:
  bool m_connected;
  struct sockaddr_in remote;

};

