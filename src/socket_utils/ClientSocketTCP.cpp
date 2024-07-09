

#include "ClientSocketTCP.h"
#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>

using namespace socket_utils;

ClientSocketTCP::ClientSocketTCP() {
  this->socket_file_descriptor_ = socket(AF_INET, SOCK_STREAM, 0);
  this->is_connected_ = false;
  memset(&this->socket_dir_, 0, sizeof(this->socket_dir_));
  return;
}

bool ClientSocketTCP::Connect(const std::string &ip, int port) {
  if (this->is_connected_) {
    return false;
  }
  memset(&this->socket_dir_, 0, sizeof(this->socket_dir_));
  this->socket_dir_.sin_family = AF_INET;
  this->socket_dir_.sin_port = htons(port);
  if (inet_pton(AF_INET, ip.c_str(), &this->socket_dir_.sin_addr) <= 0) {
    return false;
  }
  if (connect(this->socket_file_descriptor_,
              (struct sockaddr *)&this->socket_dir_,
              sizeof(this->socket_dir_)) < 0) {
    return false;
  }
  this->is_connected_ = true;
  return this->is_connected_;
}

ClientSocketTCP::operator bool() const {
  return (this->socket_file_descriptor_ > 0 && this->is_connected_);
}
