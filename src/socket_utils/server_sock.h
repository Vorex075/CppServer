

#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>
#include "SocketTCP.h"

#ifndef SERVER_SOCK_H
#define SERVER_SOCK_H

namespace socket_utils {
  template<class T>
  inline int SendData(const SocketTCP* socket, T* buffer, unsigned int size) {
    return send(socket->GetSocketFD(), buffer, size, 0);
  }
  
  template<class T>
  inline int RecvData(const SocketTCP* socket, T* buffer, unsigned int size) {
    return recv(socket->GetSocketFD(), buffer, size, 0);
  }}



#endif
