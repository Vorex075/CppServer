

#include "Room.h"
#include "../../socket_utils/server_sock.h"

bool Room::AddMember(
    std::string member_name,
    std::shared_ptr<socket_utils::PeerSocketTCP> socket_connection) {

  if (this->partitipants_.find(member_name) != this->partitipants_.end()) {
    return false; // The name already exists
  }

  this->partitipants_[member_name] = std::move(socket_connection);
  return true;
}

bool Room::BroadcastMsg(const std::string &member_name,
                        const std::string &buffer) const {
  if (this->partitipants_.find(member_name) != this->partitipants_.end()) {
    return -1;
  }
  bool sent_data{false};
  for (const auto &element : this->partitipants_) {
    if (socket_utils::SendData(element.second.get(), buffer.c_str(),
                               buffer.size()) > 0) {
      sent_data = true;
    };
  }
  return true;
}
