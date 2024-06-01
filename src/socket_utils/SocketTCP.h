

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
      virtual int Send(const std::string& buffer, int size) const;
      virtual int Recv(std::string& buffer, int size) const;
      /**
       * @return True if the file descriptor is not negative. 
       * False otherwise.
       */
      virtual explicit operator bool() const = 0;

      /**
       * @return The file descriptor of the socket
       */
      int GetFileDescriptor() const;
    protected:
      int socket_file_descriptor_;
  };

}



#endif
