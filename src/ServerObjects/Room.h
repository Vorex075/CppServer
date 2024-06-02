

#ifndef ROOM_H
#define ROOM_H

#include "../socket_utils/PeerSocketTCP.h"
#include <memory>
#include <queue>
#include <unordered_map>


class Room {
  public:
    Room() = default;

    bool AddMember(std::string member_name, std::unique_ptr<socket_utils::PeerSocketTCP> socket_connection);

    int SendTo(const std::string& member_name, const std::string& buffer) const;
    std::priority_queue<std::pair<int, std::string>> SendAll(const std::string& buffer) const;
  private:
    std::unordered_map<std::string, std::unique_ptr<socket_utils::PeerSocketTCP>> partitipants_;
};




#endif
