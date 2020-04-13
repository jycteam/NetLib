#pragma once
#include "SocketTypes.h"
#include "SocketErrors.h"
#include "Socket.h"
#include "DataSocket.h"

class ListeningSocket : public BaseSocket
{
public:
  ListeningSocket();
  void Listening(port p_port);
  DataSocket Accept();
  inline bool IsListening() const{
    return m_listening;
  }
  void Close();
protected:
  bool m_listening;               // is the socket listening?
};