

#ifndef SOCKET_CONECTION_H
#define SOCKET_CONECTION_H

#include <string>

namespace socket_utils {
  class SocketTCP {
    public:
      /**
       * @brief Creates a socket. If there was an error, the file descriptor of the socket will be negative.
       */
      SocketTCP(): socket_file_descriptor_(-1) {};
      SocketTCP(SocketTCP&&) = delete;
      /**
       * @brief Closes the socket
       */
      virtual ~SocketTCP();

      int GetSocketFD() const { return this->socket_file_descriptor_; }
      /**
       * @return True if the file descriptor is not negative. 
       * False otherwise.
       */
      virtual explicit operator bool() const = 0;

    protected:
      int socket_file_descriptor_;
  };

}



#endif
