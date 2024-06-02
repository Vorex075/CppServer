

#include "PeerSocketTCP.h"

using namespace socket_utils;

PeerSocketTCP::PeerSocketTCP(int peer_file_descriptor, struct sockaddr_in client_addr) {
  this->socket_file_descriptor_ = peer_file_descriptor;
  this->client_addr_ = client_addr;
  return;
}

inline PeerSocketTCP::operator bool() const {
  return (this->socket_file_descriptor_ > 0);
}
