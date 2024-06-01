

#ifndef PEER_SOCKET_TCP_H
#define PEER_SOCKET_TCP_H
#include "SocketTCP.h"



namespace socket_utils {
  class ServerSocketTCP;

  class PeerSocketTCP: public SocketTCP {
    public:
      explicit operator bool() const;

    private:
      friend ServerSocketTCP; 
      PeerSocketTCP(int peer_file_descriptor);

  };
}




#endif
