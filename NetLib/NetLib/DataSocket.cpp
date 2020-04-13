#include "DataSocket.h"

DataSocket::DataSocket(sock p_socket) : BaseSocket(p_socket), m_connected(false)
{
  if (p_socket != -1)
  {
    socklen_t s = sizeof(m_remoteinfo);
    getpeername(p_socket, (sockaddr*)(&m_remoteinfo), &s);
    m_connected = true;
  }
}

BOOL DataSocket::Connect(ipaddress p_addr, port p_port)
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
  m_remoteinfo.sin_family = AF_INET;
  m_remoteinfo.sin_port = htons(p_port);
  m_remoteinfo.sin_addr.s_addr = p_addr;
  memset(&(m_remoteinfo.sin_zero), 0, 8);

  // now the socket is created, so connect it.
  socklen_t s = sizeof(struct sockaddr);
  err = connect(m_sock, (struct sockaddr*)(&m_remoteinfo), s);
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


int DataSocket::Send(const char* p_buffer, int p_size)
{
  int err;

  if (m_connected == false)
  {
    throw Exception(ENotConnected);
  }

  err = send(m_sock, p_buffer, p_size, 0);
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

int DataSocket::Receive(char* p_buffer, int p_size)
{
  int err;
  if (m_connected == false)
  {
    throw Exception(ENotConnected);
  }
  err = recv(m_sock, p_buffer, p_size, 0);
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

