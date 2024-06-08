
#include "SocketTCP.h"
#include <sys/socket.h>
#include <unistd.h>

using namespace socket_utils;

SocketTCP::~SocketTCP() {
  if (*this) {
    close(this->socket_file_descriptor_);
  }
  return;
}

SocketTCP::operator bool() const {
  return (this->socket_file_descriptor_ > 0);
}







