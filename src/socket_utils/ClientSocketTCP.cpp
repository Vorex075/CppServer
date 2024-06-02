

#include "ClientSocketTCP.h"
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>


using namespace socket_utils;


int ClientSocketTCP::Connect(const std::string& ip, int port) const {
  struct sockaddr_in server_address;
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port);
  if (inet_pton(AF_INET, ip.c_str(), &server_address.sin_addr) <= 0) {
    return -1;
  }
  return connect(this->socket_file_descriptor_, (struct sockaddr *) &server_address, sizeof(server_address));
}
