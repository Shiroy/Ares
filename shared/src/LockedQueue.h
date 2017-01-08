#pragma once

#include <mutex>
#include <queue>

template<class T>
class LockedQueue : protected std::queue<T> {
 public:
  LockedQueue() {
    std::queue<T>();
  }

  void push_back(const T &elem) {
    std::lock_guard <std::mutex> lck(m_mutex);
    std::queue<T>::push(elem);
  }

  void pop() {
    std::lock_guard <std::mutex> lck(m_mutex);
    std::queue<T>::pop();
  }

  T &front() {
    std::lock_guard <std::mutex> lck(m_mutex);
    return std::queue<T>::front();
  }

  int size() const {
    return std::queue<T>::size();
  }

 private:
  std::mutex m_mutex;
};
