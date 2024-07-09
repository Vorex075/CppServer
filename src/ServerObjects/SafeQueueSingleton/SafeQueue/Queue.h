

#ifndef QUEUE_H
#define QUEUE_H

#include <condition_variable>
#include <iterator>
#include <mutex>
#include <queue>

namespace socket_utils {
template <class T> class Queue {
public:
  bool Push(T &&value);

  /**
   * @return A copy of the element at the front of the queue
   */
  T ReadFront() const { return this->queue_.front(); };

  /**
   * @brief Removes the element at the front of the queue
   * @return True if an element was removed. False otherwise (ex. The queue is
   * empty)
   */
  bool Pop();

  /**
   *  @brief Removes the element at the front of the queue
   *  @return The element that was removed
   * */
  T GetFront() const;

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

namespace socket_utils {

template <class T> bool Queue<T>::Push(T &&value) {
  std::lock_guard<std::mutex> guard(this->queue_mutex_);
  this->queue_.push(std::move(value));
  return true;
}

template <class T> T Queue<T>::GetFront() const {
  std::lock_guard<std::mutex> guard(this->queue_mutex_);
  T value = this->queue_.front();
  return std::move(value);
}

template <class T> bool Queue<T>::Pop() {
  std::lock_guard<std::mutex> guard(this->queue_mutex_);
  if (this->Empty()) {
    return false;
  }
  this->queue_.pop();
  return true;
}

} // namespace socket_utils

#endif
