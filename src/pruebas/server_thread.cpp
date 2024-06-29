#include "../socket_utils/PeerSocketTCP.h"
#include "../socket_utils/ServerSocketTCP.h"
#include "../socket_utils/server_sock.h"

#include <csignal>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

void handlesignal(int signum) {
  std::cout << "SEÑAL -> " << signum << "received\n";
  return;
}

int main() {
  signal(SIGINT, handlesignal);
  socket_utils::ServerSocketTCP serv_socket("127.0.0.1", 8080);
  serv_socket.Listen(5);
  int tries = 0;
  struct sockaddr_in client_addr;
  socket_utils::PeerSocketTCP peer_sock(serv_socket.Accept());
  std::cout << "accepted connection\n";

  char buffer[1024];
  while (true) {
    int bytes = socket_utils::RecvData(&peer_sock, buffer, sizeof(buffer));

    if (bytes <= 0) {
      std::cerr << "Error reading data or connection closed\n";
    }
    buffer[bytes] = '\0'; // Ajusta el tamaño del string para que coincida
                          // con los bytes recibidos
    std::cout << "Bytes read -> " << bytes << "\n";
    std::cout << "Mensaje recibido: " << buffer << "\n";
    std::string str = "hola -> " + std::to_string(tries++);
    socket_utils::SendData(&peer_sock, str.c_str(), str.size());

    std::cout << "msg sent -> " << str << "\n";
  }
  std::cout << "FIN WHILE TRUE\n";
}
