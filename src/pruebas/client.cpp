#include "../socket_utils/server_sock.h"

#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
  int client_socket_descriptor = socket_utils::CreateTCPSocket();
  struct sockaddr_in serv_addr;
  const char* dir_serv = "127.0.0.1";
  const int port = 8080;

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  if (inet_pton(AF_INET, dir_serv, &serv_addr.sin_addr) <= 0) {
    std::cout << "Dirección no válida -> " << strerror(errno) << "\n";
  return -1;
  }
  if (connect(client_socket_descriptor, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
    std::cout << "Error al conectar con el servidor -> " << strerror(errno) << "\n";
    return -1;
  }
  char buffer[1024];
  recv(client_socket_descriptor, &buffer, 1024, 0);
  std::cout << std::string(buffer) << "\n";
  sleep(10);
}
