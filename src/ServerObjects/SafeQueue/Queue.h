

#ifndef QUEUE
#define QUEUE

#include <atomic>
#include <condition_variable>
#include <deque>
#include <filesystem>
#include <mutex>
#include <optional>
#include <queue>

#include <optional>

namespace socket_utils {
template <class T> class Queue {
  Queue() = default;
  ~Queue() = default;

  bool PushBack(T &&value);

  /**
   * @return A copy of the element at the front of the queue
   */
  T ReadFront() const;

  /**
   * @brief Removes the element at the front of the queue
   * @return True if an element was removed. False otherwise (ex. The queue is
   * empty)
   */
  bool PopFront() { this->queue_.pop(); };

  bool Empty() const { return this->queue_.empty(); };

private:
  std::queue<T> queue_;
  std::mutex queue_mutex_;
};
} // namespace socket_utils

// Implementation
namespace socket_utils {
template <class T> bool Queue<T>::PushBack(T &&value) {
  std::lock_guard<std::mutex> guard(this->queue_mutex_);
  this->queue_.push(std::forward(value));
  return true;
}

template <class T> T Queue<T>::ReadFront() const {
  std::lock_guard<std::mutex> guard(this->queue_mutex_);
  T value = this->queue_.front();
  return std::move(value);
}

} // namespace socket_utils

#endif
