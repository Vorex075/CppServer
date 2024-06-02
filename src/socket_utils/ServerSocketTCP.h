
#ifndef SERVER_SOCKET_TCP_H
#define SERVER_SOCKET_TCP_H

#include "SocketTCP.h"
#include "PeerSocketTCP.h"

namespace socket_utils {
  class ServerSocketTCP: public SocketTCP {
    public:
      /**
       * @brief Default constructor. Opens a TCP socket and 
       * binds it to an ip and port.
       * @param ip The ip to bind the socket. By default is localhost
       * @param port The port to bind the socket. By deafult is 8080
       */
      ServerSocketTCP(const std::string& ip = "127.0.0.1", int port = 8080);

      ~ServerSocketTCP() = default;

      /**
       * @brief Sets the socket to listen
       * @param conections The number of the buffer of conections for the socket. 
       * By default is 5.
       * @return -1 if an error ocurred. errno has the error code.
       */
      int Listen(int conections = 5) const;

      PeerSocketTCP Accept() const;

      virtual explicit operator bool() const;

    private:
      bool bind_;
  };
}


#endif
