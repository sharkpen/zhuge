/*
 File Name: blocking_queue.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-06-14
 Last Modified: 2023-06-14
*/
#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>
namespace croot {
namespace lltg {

template <typename T>
class BlockingQueue {
 public:
  BlockingQueue(int capacity) : capacity_(capacity) {}

  void Put(const T& item) {
    std::unique_lock<std::mutex> lock(mutex_);
    // 阻塞等待队列非满
    while (queue_.size() == capacity_) {
      not_full_.wait(lock);
    }
    queue_.push(item);
    not_empty_.notify_all();
  }

  T Take() {
    std::unique_lock<std::mutex> lock(mutex_);
    // 阻塞等待队列非空
    while (queue_.empty()) {
      not_empty_.wait(lock);
    }
    T item = queue_.front();
    queue_.pop();
    not_full_.notify_all();
    return item;
  }

 private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable not_empty_;
  std::condition_variable not_full_;
  const int capacity_;
};
}  // namespace lltg
}  // namespace croot

