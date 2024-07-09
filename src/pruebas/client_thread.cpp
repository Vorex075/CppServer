#include "../socket_utils/ClientSocketTCP.h"
#include "../socket_utils/server_sock.h"

#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

void ListenSocket(socket_utils::ClientSocketTCP *socket) {
  while (true) {
    char buffer[1024];
    memset(buffer, 0, 1024);
    int received_bytes = socket_utils::RecvData(socket, buffer, 1024);

    if (received_bytes <= 0) {
      continue;
    }
    std::cout << "Received msg: -> " << buffer << "\n";
  }
  std::cout << "FIN LISTENSOCKET\n";
}

void WriteSocket(socket_utils::ClientSocketTCP *socket) {
  std::string buffer;
  while (true) {
    buffer.clear();
    std::cin >> buffer;

    if (buffer.size() > 1024) {
      std::cout << "Mu grande crack\n";
      continue;
    }
    std::cerr << "Mensaje enviado -> " << std::endl;
    socket_utils::SendData(socket, buffer.c_str(), buffer.size());
  }
  std::cout << "FIN WRITESOCKET\n";
}

int main() {

  socket_utils::ClientSocketTCP client_socket;
  if (!client_socket.Connect(std::string("127.0.0.1"), 8080)) {
    const int kErrcode = errno;
    std::cerr << "Error while trying to connect to 127.0.0.1:8080\n";
    std::cerr << "Errno is " << kErrcode << ". (" << strerror(kErrcode)
              << ")\n";
  }

  std::thread t1(ListenSocket, &client_socket);
  std::thread t2(WriteSocket, &client_socket);

  t1.join();
  t2.join();
}
