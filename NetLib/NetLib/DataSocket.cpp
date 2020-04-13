#include "DataSocket.h"

DataSocket::DataSocket(sock p_socket) : BaseSocket(p_socket), m_connected(false)
{
  if (p_socket != -1)
  {
    socklen_t s = sizeof(remote);
    getpeername(p_socket, (sockaddr*)(&remote), &s);
    m_connected = true;
  }
}

BOOL DataSocket::Connect(const std::string& ip, UINT16 port)
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
  remote.sin_family = AF_INET;
  remote.sin_port = htons(port);
  remote.sin_addr.s_addr = inet_addr(ip.c_str());
  memset(&(remote.sin_zero), 0, 8);

  // now the socket is created, so connect it.
  socklen_t s = sizeof(struct sockaddr);
  err = connect(m_sock, (struct sockaddr*)(&remote), s);
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


int DataSocket::Send(const Message* msg)
{
  int err;

  if (m_connected == false)
  {
    throw Exception(ENotConnected);
  }

  err = send(m_sock, (char*)msg->getBytes(), msg->getSize(), 0);
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

int DataSocket::Recv(Message* msg)
{
  int err;
  if (m_connected == false)
  {
    throw Exception(ENotConnected);
  }
  //err = recv(m_sock, msg->getBytes(), p_size, 0);
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

