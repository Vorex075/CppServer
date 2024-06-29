

#ifndef ROOM_H
#define ROOM_H

#include "../../socket_utils/PeerSocketTCP.h"
#include <memory>
#include <mutex>
#include <queue>
#include <unordered_map>


class Room {
  public:
    Room() = default;

    bool AddMember(std::string member_name, std::unique_ptr<socket_utils::PeerSocketTCP> socket_connection);

    /**
     * @brief This method sends a message to all members in the room, but the one
     * that sent the message.
     */
    int BroadcastMsg(const std::string& member_name, const std::string& buffer) const;

    void ListenUsers() const;

  private:
    std::unordered_map<std::string, std::shared_ptr<socket_utils::SocketTCP>> partitipants_;

    std::mutex room_mutex_;
};




#endif
