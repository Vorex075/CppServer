

#include "Server.h"

#include <cstring>
#include <iostream>
#include <memory>
#include <thread>

namespace server {
Server::Server(std::string ip, int port) : socket_(ip, port) {};

bool Server::Run(int n_conections) {
  if (this->socket_.Listen(n_conections) < 0) {
    int errnum = errno;
    std::cerr << "An error ocurred while trying to listen.\n";
    std::cerr << "Errno(" << errnum << std::strerror(errnum);
  }
  std::shared_ptr<RoomMap> rooms(std::make_shared<RoomMap>());
  while (true) {
    auto peer_sock_ptr =
        std::make_shared<socket_utils::PeerSocketTCP>(this->socket_.Accept());
    // std::thread thread(HandleNewClient, peer_sock_ptr, std::ref(rooms));
    // thread.detach();
  }
}

void HandleNewClient(ClientSocketPtr client, std::shared_ptr<RoomMap> rooms) {
  auto name = server::AskUserName(client.get());
  auto option = AskOption(client.get());
  switch (option) {
  case server::ServerOptions::EXIT:
    return; // The socket closes.
  case server::ServerOptions::CREATE_ROOM:
    // JoinRoom(client, std::move(name), CreateRoom(client.get(), rooms),
    // rooms);
    break;
  case server::ServerOptions::JOIN_ROOM:
    // JoinRoom(client, std::move(name), AskRoom(client.get()), rooms);
    break;
  default:
    // Any other option is not valid at first. Socket connection closes
    break;
  }
  return;
}

std::string AskUserName(socket_utils::PeerSocketTCP *client) {
  const std::string kAsk_usr_name_command = "ASK user_name 255";
  if (socket_utils::SendData(client, kAsk_usr_name_command.c_str(),
                             kAsk_usr_name_command.size()) <= 0) {
    return ""; // Error ocurred
  };
  char user_name[255];
  memset(user_name, 0, 255); // Set every char to 0
  socket_utils::RecvData(client, user_name, 255);
  return std::string(user_name);
}

ServerOptions AskOption(socket_utils::PeerSocketTCP *client) {
  const std::string kAsk_option_command = "ASK option";
  if (socket_utils::SendData(client, kAsk_option_command.c_str(),
                             kAsk_option_command.size()) <= 0) {
    return ServerOptions::EXIT; // Error ocurred
  }
  ServerOptions user_option;
  socket_utils::RecvData(client, &user_option, sizeof(user_option));
  return user_option;
}

std::string AskRoom(socket_utils::PeerSocketTCP *client) {
  const std::string kAsk_room_name_command = "ASK room_name 255";
  if (socket_utils::SendData(client, kAsk_room_name_command.c_str(),
                             kAsk_room_name_command.size()) <= 0) {
    return "";
  }
  char room_name[255];
  memset(room_name, 0, sizeof(room_name));
  socket_utils::RecvData(client, room_name, sizeof(room_name));
  return std::string(room_name);
}

std::string ReadStatus(socket_utils::PeerSocketTCP *client) {
  char status_code[255];
  memset(status_code, 0, sizeof(status_code));
  if (socket_utils::RecvData(client, status_code, sizeof(status_code)) <= 0) {
    return ""; // There was an error
  }
  return std::string(status_code);
}

bool SendListOfRooms(socket_utils::PeerSocketTCP *client,
                     std::shared_ptr<RoomMap> rooms) {
  const unsigned int number_of_rooms = rooms->size();
  const std::string kSending_rooms_command =
      "SEND room_list " + std::to_string(number_of_rooms);
  if (socket_utils::SendData(client, kSending_rooms_command.c_str(),
                             kSending_rooms_command.size()) <= 0) {
    return false; // There was an error
  }
  std::string status_code_str(ReadStatus(client));
  if (status_code_str != "200") {
    return false; // Something went wrong. Code should be 200.
  }
  std::string rooms_msg;
  for (const auto &element : *rooms) {
    std::string room = element.first + "," +
                       std::to_string(element.second->NumberOfUsers()) + ";";
    if (rooms_msg.size() + element.first.size() < 1024) {
      rooms_msg += room;
    } else {
      socket_utils::SendData(client, rooms_msg.c_str(), rooms_msg.size());
      rooms_msg = room;
    }
  }
  if (socket_utils::SendData(client, rooms_msg.c_str(), rooms_msg.size()) <=
      0) {
    return false; // There was an error
  }
  socket_utils::SendData(client, rooms_msg.c_str(),
                         0); // Send empty message to end.
  return true;
}

bool JoinRoom(ClientSocketPtr client, std::string &&client_name,
              const std::string &room_name, std::shared_ptr<RoomMap> rooms);

std::string CreateRoom(socket_utils::PeerSocketTCP *client,
                       std::shared_ptr<RoomMap> rooms);
} // namespace server
