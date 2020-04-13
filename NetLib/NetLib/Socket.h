#pragma once

//#include "pub_header.h"
#include "SocketTypes.h"
#include "SocketErrors.h"

class BaseSocket
{
public:
  inline sock GetSock() const
  {
    return m_sock;
  }

  inline port GetLocalPort() const
  {
    return ntohs(m_localinfo.sin_port);
  }

  inline ipaddress GetLocalAddress() const
  {
    return m_localinfo.sin_addr.s_addr;
  }
  void Close();

  void SetBlocking(bool p_blockmode);

protected:
  BaseSocket(sock p_socket = -1);
  sock m_sock;
  struct sockaddr_in m_localinfo;
  bool m_isblocking;
};
