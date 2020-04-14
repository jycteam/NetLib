#include "DataSocket.h"

DataSocket::DataSocket(sock p_socket) : BaseSocket(p_socket), m_connected(false)
{
  if (p_socket != -1)
  {
<<<<<<< HEAD
    socklen_t s = sizeof(remote);
    getpeername(p_socket, (sockaddr*)(&remote), &s);
=======
    socklen_t s = sizeof(m_remoteinfo);
    getpeername(p_socket, (sockaddr*)(&m_remoteinfo), &s);
>>>>>>> 0e532d0159a3dfe201d7538a72b57c286c767740
    m_connected = true;
  }
}

<<<<<<< HEAD
BOOL DataSocket::Connect(const std::string& ip, UINT16 port)
=======
BOOL DataSocket::Connect(ipaddress p_addr, port p_port)
>>>>>>> 0e532d0159a3dfe201d7538a72b57c286c767740
{
  int err;
  if (m_connected == true)
  {
    throw Exception(EAlreadyConnected);
  }

  if (m_sock == -1)
  {
    m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_sock == -1)
    {
      throw Exception(GetError());
    }
  }

  // set up the socket address structure
<<<<<<< HEAD
  remote.sin_family = AF_INET;
  remote.sin_port = htons(port);
  remote.sin_addr.s_addr = inet_addr(ip.c_str());
  memset(&(remote.sin_zero), 0, 8);

  // now the socket is created, so connect it.
  socklen_t s = sizeof(struct sockaddr);
  err = connect(m_sock, (struct sockaddr*)(&remote), s);
=======
  m_remoteinfo.sin_family = AF_INET;
  m_remoteinfo.sin_port = htons(p_port);
  m_remoteinfo.sin_addr.s_addr = p_addr;
  memset(&(m_remoteinfo.sin_zero), 0, 8);

  // now the socket is created, so connect it.
  socklen_t s = sizeof(struct sockaddr);
  err = connect(m_sock, (struct sockaddr*)(&m_remoteinfo), s);
>>>>>>> 0e532d0159a3dfe201d7538a72b57c286c767740
  if (err == -1)
  {
    throw Exception(GetError());
  }

  m_connected = true;

  // to get the local port, you need to do a little more work
  err = getsockname(m_sock, (struct sockaddr*)(&m_localinfo), &s);
  if (err != 0)
  {
    throw Exception(GetError());
  }
  return TRUE;
}


<<<<<<< HEAD
int DataSocket::Send(const Message* msg)
=======
int DataSocket::Send(const char* p_buffer, int p_size)
>>>>>>> 0e532d0159a3dfe201d7538a72b57c286c767740
{
  int err;

  if (m_connected == false)
  {
    throw Exception(ENotConnected);
  }

<<<<<<< HEAD
  err = send(m_sock, (char*)msg->getBytes(), msg->getSize(), 0);
=======
  err = send(m_sock, p_buffer, p_size, 0);
>>>>>>> 0e532d0159a3dfe201d7538a72b57c286c767740
  if (err == -1)
  {
    Error e = GetError();
    if (e != EOperationWouldBlock)
    {
      throw Exception(e);
    }
    err = 0;
  }
  return err;
}

<<<<<<< HEAD
int DataSocket::Recv(Message* msg)
=======
int DataSocket::Receive(char* p_buffer, int p_size)
>>>>>>> 0e532d0159a3dfe201d7538a72b57c286c767740
{
  int err;
  if (m_connected == false)
  {
    throw Exception(ENotConnected);
  }
<<<<<<< HEAD
  //err = recv(m_sock, msg->getBytes(), p_size, 0);
=======
  err = recv(m_sock, p_buffer, p_size, 0);
>>>>>>> 0e532d0159a3dfe201d7538a72b57c286c767740
  if (err == 0)
  {
    throw Exception(EConnectionClosed);
  }
  if (err == -1)
  {
    throw Exception(GetError());
  }

  return err;
}

void DataSocket::Close()
{
  if (m_connected == true)
  {
    shutdown(m_sock, 2);
  }
  BaseSocket::Close();
  m_connected = false;
}

