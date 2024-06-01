
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

inline int SocketTCP::GetFileDescriptor() const {
  return this->socket_file_descriptor_;
}

inline int SocketTCP::Send(const std::string& buffer, int size) const {
  return send(this->socket_file_descriptor_, buffer.c_str(), buffer.size(), 0);
}

inline int SocketTCP::Recv(std::string& buffer, int size) const {
  char* char_buffer = new char[size];
  int received_bytes = recv(this->socket_file_descriptor_, char_buffer, size, 0);
  buffer = std::string(char_buffer);
  delete[] char_buffer;
  return received_bytes;
} 







