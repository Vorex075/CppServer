

#ifndef PEER_SOCKET_TCP_H
#define PEER_SOCKET_TCP_H
#include "SocketTCP.h"
#include <netinet/in.h>

namespace socket_utils {
class ServerSocketTCP;

class PeerSocketTCP : public SocketTCP {
public:
  explicit operator bool() const;
  PeerSocketTCP(PeerSocketTCP &&peer_sock);

private:
  friend ServerSocketTCP;
  PeerSocketTCP(int peer_file_descriptor, struct sockaddr_in client_addr);
  struct sockaddr_in client_addr_;
};
} // namespace socket_utils

#endif
