
#include "Client.h"

namespace client {

ClientOption ConvertToClientOption(const unsigned int num) {
  ClientOption option;
  switch (num) {
  case 0:
    option = ClientOption::EXIT;
    break;
  case 1:
    option = ClientOption::CONNECT;
    break;
  default:
    option = ClientOption::NONE;
  }
  return option;
}

void ShowClientMenu() {
  std::cout << "0. Exit\n 1. Connect\n";
  return;
}

/**
 *  @brief Checks whether the string is a positive number or not
 *  @return True if is a positive number. False otherwise.
 * */
bool ValidNumber(const std::string &number) noexcept {
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
                 const std::string &option) noexcept {
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

ClientOption GetClientOption() {
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
  return ConvertToClientOption(std::stoi(option));
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

server::ServerOptions GetServerOption() { return server::ServerOptions::EXIT; }

void StartClient() {

  ClientOption option = GetClientOption();
  if (option == ClientOption::EXIT) {
    return;
  }
  if (option == ClientOption::CONNECT) {
    if (!ConnectToServer("127.0.0.1", 8080)) {
      return;
    }
    std::cout << "Successfully connected to the server!\n";
    server::ServerOptions serv_option = GetServerOption();
  } else {
    return;
  }
}

} // namespace client
