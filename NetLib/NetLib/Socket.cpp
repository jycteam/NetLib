#include "pub_header.h"
#include "Socket.h"

class System
{
public:
  System(){
<<<<<<< HEAD

=======
>>>>>>> 0e532d0159a3dfe201d7538a72b57c286c767740
    WSAStartup(MAKEWORD(2, 2), &m_WSAData);//windows need this
  }

  ~System(){
    WSACleanup();//����API����
  }
protected:
  WSADATA m_WSAData;
};

<<<<<<< HEAD
//System g_system;
=======
System g_system;
>>>>>>> 0e532d0159a3dfe201d7538a72b57c286c767740



void BaseSocket::Close()
{
  closesocket(m_sock);
  m_sock = -1;
}

void BaseSocket::SetBlocking(bool p_blockmode)
{
  int err;
  unsigned long mode = !p_blockmode;
  err = ioctlsocket(m_sock, FIONBIO, &mode);
  if (err == -1)
  {
    throw(Exception(GetError()));
  }

  m_isblocking = p_blockmode;
}

BaseSocket::BaseSocket(sock p_socket) : m_sock(p_socket)
{
  if (p_socket != -1)
  {
    socklen_t s = sizeof(m_localinfo);
    getsockname(p_socket, (sockaddr*)(&m_localinfo), &s);
  }

  // the socket is blocking by default
  m_isblocking = true;
}

