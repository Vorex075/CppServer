

#include "ServerSocketTCP.h"
#include "PeerSocketTCP.h"
#include "SocketTCP.h"
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>


using namespace socket_utils;

ServerSocketTCP::ServerSocketTCP(const std::string& ip, int port): SocketTCP() {
  this->socket_file_descriptor_ = socket(AF_INET, SOCK_STREAM, 0);
  if (this->socket_file_descriptor_ <= 0) {
    return;
  }
  struct sockaddr_in socket_address;
  // Set all values of socket_address to 0
  memset(&socket_address, 0, sizeof(socket_address));
  socket_address.sin_family = AF_INET;
  socket_address.sin_addr.s_addr = INADDR_ANY;
  socket_address.sin_port = htons(port);

  this->bind_ = bind(this->socket_file_descriptor_, 
      (struct sockaddr*) &socket_address, 
      sizeof(socket_address));
  return;
}

inline ServerSocketTCP::operator bool() const {
  return ((this->socket_file_descriptor_ > 0) &&
      this->bind_ == true);
}

int ServerSocketTCP::Listen(int conections) const {
  return listen(this->socket_file_descriptor_, conections);
}

PeerSocketTCP ServerSocketTCP::Accept() const {
  struct sockaddr_in client_address;
  socklen_t client_address_len = sizeof(client_address);
  int peer_fd = accept(this->socket_file_descriptor_, 
      (struct sockaddr *) &client_address, &client_address_len);
  return PeerSocketTCP(peer_fd, client_address);
}
