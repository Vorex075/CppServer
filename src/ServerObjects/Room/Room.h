

#ifndef ROOM_H
#define ROOM_H

#include "../../socket_utils/PeerSocketTCP.h"
#include <memory>
#include <mutex>
#include <queue>
#include <unordered_map>

namespace socket_utils {
class Room {
public:
  Room() = default;

  Room(const Room &another_room);

  bool
  AddMember(std::string member_name,
            std::shared_ptr<socket_utils::PeerSocketTCP> socket_connection);

  /**
   * @brief This method sends a message to all members in the room, but the one
   * that sent the message.
   */
  bool BroadcastMsg(const std::string &member_name,
                    const std::string &buffer) const;

  void ListenUsers() const;

  unsigned int NumberOfUsers() const { return this->partitipants_.size(); }

private:
  std::unordered_map<std::string, std::shared_ptr<socket_utils::SocketTCP>>
      partitipants_;

  std::mutex room_mutex_;
};
namespace rooms {}

} // namespace socket_utils
#endif
