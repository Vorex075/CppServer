#include "../socket_utils/ClientSocketTCP.h"

#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

  socket_utils::ClientSocketTCP client_socket;
  client_socket.Connect(std::string("127.0.0.1"), 8080);
  std::string buffer;
  buffer.resize(1024);
  client_socket.Recv(buffer, buffer.size());
  std::cout << buffer << "\n";
}
