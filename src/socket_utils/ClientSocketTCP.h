

#ifndef CLIENT_SOCKET_TCP_H
#define CLIENT_SOCKET_TCP_H

#include "SocketTCP.h"
#include <netinet/in.h>
namespace socket_utils {
class ClientSocketTCP : public SocketTCP {
public:
  ClientSocketTCP();

  /**
   * @brief Connects to a socket.
   * @return 0 if successfully connected. False otherwise
   */
  bool Connect(const std::string &ip, int port);

  struct sockaddr_in GetConnectedDir() const { return this->socket_dir_; }

  explicit operator bool() const;

private:
  bool is_connected_;
  struct sockaddr_in socket_dir_;
};

} // namespace socket_utils
#endif
