#pragma once
#include "pub_header.h"
#include "SocketTypes.h"
#include "SocketErrors.h"
#include "Socket.h"

class DataSocket : public BaseSocket
{
public:
  DataSocket(sock p_socket = -1);
 
  inline ipaddress GetRemoteAddress() const
  {
    return m_remoteinfo.sin_addr.S_un.S_addr;
  }

  inline port GetRemotePort() const
  {
    return ntohs(m_remoteinfo.sin_port);
  }

  inline bool IsConnected() const
  {
    return m_connected;
  }

  BOOL Connect(ipaddress p_addr, port p_port);

  int Send(const char* p_buffer, int p_size);

  int Receive(char* p_buffer, int p_size);

  void Close();

protected:

  bool m_connected;
  struct sockaddr_in m_remoteinfo;

};

