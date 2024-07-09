

#ifndef SINGLETON_QUEUE_H
#define SINGLETON_QUEUE_H

#include "../../socket_utils/PeerSocketTCP.h"
#include "SafeQueue/Queue.h"
#include <memory>

namespace socket_utils {
class SingletonQueue {

public:
  SingletonQueue(const SingletonQueue &) = delete;
  SingletonQueue &operator=(const SingletonQueue &) = delete;

  static Queue<SocketTCP> *GetQueue();

private:
  SingletonQueue() = default;
  static std::unique_ptr<Queue<SocketTCP>> queue_;
};

} // namespace socket_utils

#endif
