

#ifndef NODE_H
#define NODE_H

#include <memory>
template <class T> class QueueNode {
public:
  QueueNode(T &&new_value) : value(std::forward(new_value)) {}
  ~QueueNode() = default;

  QueueNode(QueueNode<T> &&another_node);      // Move constructor
  QueueNode(const QueueNode<T> &another_node); // Copy constructor

  T &ReadValue() const { return this->value; }

  T GetValue() { return std::move(this->value); }

  bool SetNext(std::unique_ptr<QueueNode<T>> next_node) {
    this->next_ = std::move(next_node);
  }

  QueueNode *Next() const { return this->next_.get(); }

private:
  std::unique_ptr<T> next_;
  T value;
};

template <class T> QueueNode<T>::QueueNode(QueueNode<T> &&another_node) {
  this->value = std::move(another_node.value);
  this->next_ = another_node.next_;
  return;
}

template <class T> QueueNode<T>::QueueNode(const QueueNode<T> &another_node) {
  this->value = another_node.value;
  this->next_ = std::unique_ptr<T>(*another_node.next_);
  return;
}

#endif
