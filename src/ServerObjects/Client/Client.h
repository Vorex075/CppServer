
#ifndef CLIENT_H
#define CLIENT_H

#include "../../socket_utils/ClientSocketTCP.h"
#include "../Server/Server.h"

#include <iostream>

namespace client {

enum class ClientOption { CONNECT, EXIT, NONE };

ClientOption ConvertToClientOption(const unsigned int num);

/**
 *  @brief Shows in terminal the menu of options the client can do
 * */
void ShowClientMenu();

/**
 *  @brief Checks whether the string is a positive number or not
 *  @return True if is a positive number. False otherwise.
 * */
bool ValidNumber(const std::string &number) noexcept;

/**
 *  @brief Checks whether the option is valid or not.
 * */
bool ValidOption(const unsigned int number_of_options,
                 const std::string &option) noexcept;

void ClearTerminal();

/**
 *  @brief Asks the client an option.
 * */
ClientOption GetClientOption();

bool ConnectToServer(const std::string ip, const int port);

server::ServerOptions GetServerOption();

void StartClient();
} // namespace client

#endif
