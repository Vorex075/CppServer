

#ifndef SERVER_H
#define SERVER_H

#include "../../socket_utils/ServerSocketTCP.h"
#include "../../socket_utils/server_sock.h"
#include <memory>
#include <string>
class Server {
public:
  Server(std::string ip, int port);

  /**
   *  @brief Starts the server
   * */
  bool Run(int n_conections);

  /**
   *  @brief Checks if the server is ready to be run
   * */
  bool IsReady() const { return (bool)this->socket_; }

private:
  socket_utils::ServerSocketTCP socket_;
};

void HandleNewClient(std::shared_ptr<socket_utils::PeerSocketTCP> client);

/**
 *  @brief Ask the client user name.
 *  @return The client user name. If "" (emty string) is returned, an error
 * ocurred. Error code will be in errno
 * */
std::string AskUserName(socket_utils::PeerSocketTCP *client);

#endif
