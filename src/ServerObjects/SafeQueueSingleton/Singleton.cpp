

#include "Singleton.h"

namespace socket_utils {
Queue<SocketTCP> *SingletonQueue::GetQueue() {
  if (queue_ == nullptr) {
    queue_ = std::make_unique<Queue<SocketTCP>>();
  }
  return this->queue_.get();
}

} // namespace socket_utils
