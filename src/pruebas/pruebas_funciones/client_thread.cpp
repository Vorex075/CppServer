#include "../../ServerObjects/Server/ServerOptions.h"
#include "../../socket_utils/ClientSocketTCP.h"
#include "../../socket_utils/server_sock.h"

#include <arpa/inet.h>
#include <cctype>
#include <cerrno>
#include <cstring>
#include <exception>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

void ListenSocket(socket_utils::ClientSocketTCP *socket) {
  while (true) {
    char buffer[1024];
    memset(buffer, 0, 1024);
    int received_bytes = socket_utils::RecvData(socket, buffer, 1024);

    if (received_bytes <= 0) {
      continue;
    }
    std::cout << "Received msg: -> " << buffer << "\n";
  }
  std::cout << "FIN LISTENSOCKET\n";
}

void WriteSocket(socket_utils::ClientSocketTCP *socket) {
  std::string buffer;
  while (true) {
    buffer.clear();
    std::cin >> buffer;

    if (buffer.size() > 1024) {
      std::cout << "Mu grande crack\n";
      continue;
    }
    std::cerr << "Mensaje enviado -> " << std::endl;
    socket_utils::SendData(socket, buffer.c_str(), buffer.size());
  }
  std::cout << "FIN WRITESOCKET\n";
}

void ShowClientMenu() {
  std::cout << "0. Exit\n 1. Connect\n";
  return;
}

/**
 *  @brief Checks whether the string is a positive number or not
 *  @return True if is a positive number. False otherwise.
 * */
bool ValidNumber(const std::string &number) {
  if (number.empty()) {
    return false;
  }
  bool is_valid = true;
  for (const auto &element : number) {
    if (!isdigit(element)) {
      is_valid = false;
      break;
    }
  }
  if (is_valid) {
    return (number[0] != '-'); // isdigit accepts negative number. We do not
  }
  return false;
}

bool ValidOption(const unsigned int number_of_options,
                 const std::string &option) {
  if (!ValidNumber(option)) {
    return false;
  }
  int number = 0;
  try {
    number = std::stoi(option);
  } catch (std::exception &exception) {
    std::cerr << "Exeption ocurred while trying to convert option to number\n";
    std::cerr << "Reason: " << exception.what() << "\n";
    return false;
  }
  return (0 <= number <= number_of_options);
}

void ClearTerminal() {
  std::cout << "\033[2J\033[1;1H";
  return;
}

unsigned int GetClientOption() {
  const unsigned short int kNumber_of_options = 2;
  std::string option;
  ShowClientMenu();
  std::cout << "Option: ";
  std::cin >> option;

  while (ValidOption(kNumber_of_options, option)) {
    std::cout << "Invalid option. Try Again\n";
    ClearTerminal();
    std::cout << "Option: ";
    std::cin >> option;
  };
  return std::stoi(option);
}

bool ConnectToServer(const std::string ip, const int port) {
  socket_utils::ClientSocketTCP client_socket;
  if (!client_socket.Connect(ip, port)) {
    const int kErrorcode = errno;
    std::cerr << "Error while trying to connect to " << ip << ":" << port
              << "\nError code is: " << kErrorcode << "("
              << strerror(kErrorcode) << ")\n";
    return false;
  }
  return true;
}

server::Serveroptions GetServerOption() {}

void StartClient() {
  {
    unsigned int option = GetClientOption();
    if (option == 0) {
      return;
    }
  }
  if (!ConnectToServer("127.0.0.1", 8080)) {
    return;
  }
  std::cout << "Successfully connected to the server!\n";
  server::ServerOptions option = GetServerOption();
}

int main() {

  socket_utils::ClientSocketTCP client_socket;
  if (!client_socket.Connect(std::string("127.0.0.1"), 8080)) {
    const int kErrcode = errno;
    std::cerr << "Error while trying to connect to 127.0.0.1:8080\n";
    std::cerr << "Errno is " << kErrcode << ". (" << strerror(kErrcode)
              << ")\n";
  }
  char buffer[255];
  memset(buffer, 0, sizeof(buffer));
  socket_utils::RecvData(&client_socket, buffer, sizeof(buffer));
  std::string buffer_str(buffer);
  if (buffer_str != "ASK option") {
    return 1;
  }

  server::ServerOptions option = server::ServerOptions::JOIN_ROOM;
  socket_utils::SendData(&client_socket, &option, sizeof(option));
  socket_utils::SendData(&client_socket, "200", sizeof("200"));

  std::thread t1(ListenSocket, &client_socket);
  std::thread t2(WriteSocket, &client_socket);

  t1.join();
  t2.join();
}
