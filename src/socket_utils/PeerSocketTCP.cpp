

#include "PeerSocketTCP.h"

using namespace socket_utils;

PeerSocketTCP::PeerSocketTCP(int peer_file_descriptor) {
  this->socket_file_descriptor_ = peer_file_descriptor;
  return;
}

inline PeerSocketTCP::operator bool() const {
  return (this->socket_file_descriptor_ > 0);
}
