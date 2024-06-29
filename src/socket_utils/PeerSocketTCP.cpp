

#include "PeerSocketTCP.h"

using namespace socket_utils;

PeerSocketTCP::PeerSocketTCP(int peer_file_descriptor,
                             struct sockaddr_in client_addr) {
  this->socket_file_descriptor_ = peer_file_descriptor;
  this->client_addr_ = client_addr;
  return;
}

PeerSocketTCP::PeerSocketTCP(PeerSocketTCP &&another_socket) {
  this->client_addr_ = another_socket.client_addr_;
  this->socket_file_descriptor_ = another_socket.socket_file_descriptor_;
  another_socket.socket_file_descriptor_ = -1;
  return;
}

inline PeerSocketTCP::operator bool() const {
  return (this->socket_file_descriptor_ > 0);
}
