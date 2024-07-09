#include "Queue.h"
#include <iostream>
#include <string>

int main() {
  auto queue_ = socket_utils::Queue<std::string>::GetInstance();

  queue_->Push(std::string("Hola"));

  std::cout << "Queue.top() ->" << queue_->Read() << "\n";
}
