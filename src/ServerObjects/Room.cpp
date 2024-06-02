

#include "Room.h"


bool Room::AddMember(std::string member_name, 
    std::unique_ptr<socket_utils::PeerSocketTCP> socket_connection) {
  if (this->partitipants_.find(member_name) != this->partitipants_.end()) {
    return false; // The name already exists
  }
  this->partitipants_[member_name] = std::move(socket_connection);
  return true;
}


int Room::SendTo(const std::string& member_name, const std::string& buffer) const {
  if (this->partitipants_.find(member_name) != this->partitipants_.end()) {
    return -1;
  }
  return this->partitipants_.at(member_name)->Send(buffer, buffer.size());
}

std::priority_queue<std::pair<int, std::string>> Room::SendAll(const std::string& buffer) const {
  std::priority_queue<std::pair<int, std::string>> sent_bytes;
  for (const auto& participant: this->partitipants_) {
    int bytes_sent = participant.second->Send(buffer, buffer.size());
    sent_bytes.push({bytes_sent, participant.first});
  }
  return std::move(sent_bytes);
}


