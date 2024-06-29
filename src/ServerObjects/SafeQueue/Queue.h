


#ifndef QUEUE
#define QUEUE


#include <atomic>
#include <condition_variable>
#include <deque>
#include <mutex>
#include <optional>
#include <queue>


namespace socket_utils {
  template<class T>
  class Queue {
    Queue() = default;
    ~Queue() = default;

    bool PushBack(T&& value);

    /**
     * @return A copy of the element at the front of the queue
     */
    std::optional<T> ReadFront() const;

    std::optional<T> GetFront();
    
    /**
     * @brief Removes the element at the front of the queue
     * @return True if an element was removed. False otherwise (ex. The queue is empty)
     */
    bool PopFront();
    bool Empty() const;
    private:
      std::queue<T> queue_;
      std::mutex queue_mutex_;
  };
}


// Implementation
namespace socket_utils {
  template<class T>
  bool Queue<T>::PushBack(T&& value) {
    std::lock_guard<std::mutex> guard(this->queue_mutex_); 
    this->queue_.push(std::forward(value));
    return true;
  }

  template<class T>
  std::optional<T> Queue<T>::ReadFront() const {
    std::lock_guard<std::mutex> guard(this->queue_mutex_);
    if (this->Empty()) {
      return std::nullopt;
    }
    T value = this->queue_.front();
    return std::move(value);
  }

  template<class T>
  std::optional<T> Queue<T>::GetFront() {
    std::lock_guard<std::mutex> guard(this->queue_mutex_);
    if (this->Empty()) {
      return std::nullopt;
    }
    T value = this->queue_.erase()
    return std::move(this->queue_.);
  } 

  



}




#endif
