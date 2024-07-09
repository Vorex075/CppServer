

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
public:
  static Queue<T> &GetInstance();

  bool Push(T &&value);

  /**
   * @return A copy of the element at the front of the queue
   */
  T Read() const { return this->queue_.front(); };

  /**
   * @brief Removes the element at the front of the queue
   * @return True if an element was removed. False otherwise (ex. The queue is
   * empty)
   */
  void Pop() { this->queue_.pop(); };

  T Get() const;

  bool Empty() const { return this->queue_.empty(); };

protected:
  Queue() = default;
  ~Queue() = default;

  friend std::unique_ptr<Queue<T>> std::make_unique<Queue<T>>();

private:
  std::queue<T> queue_;
  std::mutex queue_mutex_;
};
} // namespace socket_utils

// Implementation
namespace socket_utils {

template <class T> Queue<T> &Queue<T>::GetInstance() {
  static Queue<T> instance;
  return instance;
}

template <class T> bool Queue<T>::Push(T &&value) {
  std::lock_guard<std::mutex> guard(this->queue_mutex_);
  this->queue_.push(std::move(value));
  return true;
}

template <class T> T Queue<T>::Get() const {
  std::lock_guard<std::mutex> guard(this->queue_mutex_);
  T value = this->queue_.front();
  return std::move(value);
}

} // namespace socket_utils

#endif
