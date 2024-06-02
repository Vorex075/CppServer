

#ifndef CLIENT_SOCKET_TCP_H
#define CLIENT_SOCKET_TCP_H

#include "SocketTCP.h"
namespace socket_utils {
  class ClientSocketTCP: public SocketTCP {
    public:
      ClientSocketTCP() : SocketTCP(), is_connected_(false) {};

      /**
       * @brief Connects to a socket. 
       * @return 0 if successfully connected. False otherwise 
       */
      int Connect(const std::string& ip, int port) const;

      explicit operator bool() const;

    private:
      bool is_connected_;

  };

}
#endif
