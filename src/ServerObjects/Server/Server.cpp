

#include "Server.h"
#include "../Room/Room.h"

#include <cstring>
#include <iostream>
#include <map>
#include <thread>

Server::Server(std::string ip, int port) : socket_(ip, port) {};

bool Server::Run(int n_conections) {
  if (this->socket_.Listen(n_conections) < 0) {
    int errnum = errno;
    std::cerr << "An error ocurred while trying to listen.\n";
    std::cerr << "Errno(" << errnum << std::strerror(errnum);
  }
  std::map<std::string, Room> rooms;
  while (true) {
    auto peer_sock_ptr =
        std::make_shared<socket_utils::PeerSocketTCP>(this->socket_.Accept());
    std::thread thread(HandleNewClient, peer_sock_ptr);
    thread.detach();
  }
}

void HandleNewClient(std::shared_ptr<socket_utils::PeerSocketTCP> client) {
  auto name = AskUserName(client.get());
  // SERVER MAIN POINT
}

std::string AskUserName(socket_utils::PeerSocketTCP *client) {
  std::string get_command = "GET user_name";
  if (socket_utils::SendData(client, get_command.c_str(), get_command.size()) <=
      0) {
    return "";
  };

  char user_name[255];
  memset(user_name, 0, 255); // Set every char to 0

  socket_utils::RecvData(client, user_name, 255);
  return std::string(user_name);
}
