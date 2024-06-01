

#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>

#ifndef SERVER_SOCK_H
#define SERVER_SOCK_H

namespace socket_utils {
  int CreateTCPSocket(); 
  int Bind(int socket_descriptor, int port);
  int Connect(const std::string& ip, int port);
}



#endif
