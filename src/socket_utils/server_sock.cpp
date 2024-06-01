

#include "server_sock.h"

namespace socket_utils {
  int CreateTCPSocket() {
    int socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_descriptor < 0) {
      // In errno there is the actual error
      return -1;
    }
    return socket_descriptor;
  }
  int Bind(int socket_descriptor, int port) {
    struct sockaddr_in socket_address;
    memset(&socket_address, 0, sizeof(socket_address)); // Set all values at socket_address to 0
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY;
    socket_address.sin_port = htons(port);

    return bind(socket_descriptor, (struct sockaddr *) &socket_address, sizeof(socket_address));
  }
}
