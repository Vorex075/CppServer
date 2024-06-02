#include "../socket_utils/server_sock.h"
#include "../socket_utils/ServerSocketTCP.h"
#include "../socket_utils/PeerSocketTCP.h"

#include <cstdio>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>




int main() {
  socket_utils::ServerSocketTCP serv_socket("127.0.0.1", 8080);
  serv_socket.Listen(5);
  std::cout << "Socket created with fd -> " << serv_socket.GetFileDescriptor() << "\n\n";
  int tries;
  while (true) {
    struct sockaddr_in client_addr;
    socket_utils::PeerSocketTCP peer_sock(serv_socket.Accept());
    std::string str = "hola -> " + std::to_string(tries++);
    peer_sock.Send(str, str.size());
  }

  // int server_socket_descriptor = socket_utils::CreateTCPSocket();
  // if (socket_utils::Bind(server_socket_descriptor, 8080)) {
  //   std::cout << "There was an error while trying to bind into port 8080 -> " << strerror(errno) << "\n";
  //   return -1;
  // }
  //
  // if (listen(server_socket_descriptor, 5)) {
  //   std::cout << "There was an error while trying to listen -> " << strerror(errno) << "\n";
  //   return -1;
  // }
  //
  // int tries = 0;
  // while (true) {
  //   struct sockaddr_in client_addr;
  //   socklen_t client_addr_size = sizeof(client_addr);
  //   int peer_conection = accept(server_socket_descriptor, (struct sockaddr *)&client_addr, &client_addr_size);
  //   if (peer_conection < 0) {
  //     std::cout << "There was an error while trying to accept a conection\n";
  //     close(server_socket_descriptor);
  //     return -1;
  //   }
  //   std::cout << "NUEVA CONEXIÓN\n";
  //   std::string str = "Hola -> " + std::to_string(tries++) + " xdd";
  //   send(peer_conection, str.c_str(), str.size(), 0);
  // std::cout << "msg enviado -> " << str << "\n";
  // }

}
