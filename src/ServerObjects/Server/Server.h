

#ifndef SERVER_H
#define SERVER_H

#include "../../socket_utils/ServerSocketTCP.h"
#include "../../socket_utils/server_sock.h"
#include "../Room/Room.h"
#include "ServerOptions.h"
#include <map>
#include <memory>
#include <string>

typedef std::shared_ptr<socket_utils::PeerSocketTCP> ClientSocketPtr;
typedef std::map<std::string, std::shared_ptr<socket_utils::Room>> RoomMap;

namespace server {

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

void HandleNewClient(ClientSocketPtr client,
                     std::shared_ptr<socket_utils::Room>);

/**
 *  @brief Ask the client user name.
 *  @return The client user name. If "" (empty string) is returned, an error
 * ocurred. Error code will be in errno
 * */
std::string AskUserName(socket_utils::PeerSocketTCP *client);

/**
 *  @brief Ask the client what to do.
 *  @return A ServerOptions Object.
 * */
ServerOptions AskOption(socket_utils::PeerSocketTCP *client);

/**
 *  @brief Ask the client for the name of the room.
 *  @return The name of the room. If "" (empty string) is returned, an erro
 * ocurred. Error code will be in errno
 * */
std::string AskRoom(socket_utils::PeerSocketTCP *client);

/**
 *  @brief Reads the client status response
 *  @return The status code, as a string
 * */
std::string ReadStatus(socket_utils::PeerSocketTCP *client);

/**
 *  @brief Sends the list of rooms to the user.
 *  @return True if it worked. False otherwise (error code in errno)
 * */
bool SendListOfRooms(socket_utils::PeerSocketTCP *client,
                     std::shared_ptr<RoomMap> rooms);

/**
 *  @brief Joins a user connection to an specific room.
 *  @param client The pointer to the PeerSocketTCP object, that holds the
 * conection with the user.
 *  @param client_name The name of the client.
 *  @param room_name The name of the room.
 *  @param rooms A pointer to the map with all name-room relations
 *  @return True if the user joined the room. False otherwise.
 * */
bool JoinRoom(ClientSocketPtr client, std::string &&client_name,
              const std::string &room_name, std::shared_ptr<RoomMap> rooms);

/**
 * @brief Creates a new room
 * @param client The client conection
 * @param rooms A pointer to the map with all name-room relations
 * @return A string with the name of the new room created. If "" (empty string)
 * is returned, an error ocurred. Error code will be in errno.
 * */
std::string CreateRoom(socket_utils::PeerSocketTCP *client,
                       std::shared_ptr<RoomMap> rooms);

} // namespace server
#endif
