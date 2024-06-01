#include "../socket_utils/server_sock.h"
#include <cstdio>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>




int main() {
  int server_socket_descriptor = socket_utils::CreateTCPSocket();
  if (socket_utils::Bind(server_socket_descriptor, 8080)) {
    std::cout << "There was an error while trying to bind into port 8080 -> " << strerror(errno) << "\n";
    return -1;
  }

  if (listen(server_socket_descriptor, 5)) {
    std::cout << "There was an error while trying to listen -> " << strerror(errno) << "\n";
    return -1;
  }

  int tries = 0;
  while (true) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);
    int peer_conection = accept(server_socket_descriptor, (struct sockaddr *)&client_addr, &client_addr_size);
    if (peer_conection < 0) {
      std::cout << "There was an error while trying to accept a conection\n";
      close(server_socket_descriptor);
      return -1;
    }
    std::cout << "NUEVA CONEXIÓN\n";
    std::string str = "Hola -> " + std::to_string(tries++) + " xdd";
    send(peer_conection, str.c_str(), str.size(), 0);
  std::cout << "msg enviado -> " << str << "\n";
  }

}
