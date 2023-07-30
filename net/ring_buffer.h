/*
 File Name: ring_buffer.h
 Author:
 Email: @croot.com
 Created: 2023-07-31
 Last Modified: 2023-07-31
*/
#pragma once
#include <array>
#include <atomic>
#include <memory>
namespace croot {
namespace lltg {
template <typename T, int N = 1024>
class RingBuffer {
 public:
  explicit RingBuffer() : head_(0), tail_(0) {}

  bool isEmpty() const { return head_ == tail_; }

  bool isFull() const { return (tail_ + 1) % N == head_; }

  bool Push(const T& value) {
    size_t tail = tail_.load();
    size_t head = head_.load();
    if ((tail +1) % N == head) {
      return false;
    }

    buffer_[tail] = value;
    tail_.store((tail + 1) % N);
    return true;
  }

  bool Pop(T* value) {
    size_t tail = tail_.load();
    size_t head = head_.load();
    if (tail == head) {
      return false;
    }

    *value = buffer_[head_];
    head_.store((head_ + 1) % N);
    return true;
  }

 private:
  std::array<T, N> buffer_;
  std::atomic<size_t> head_;
  std::atomic<size_t> tail_;
};

}  // namespace lltg
}  // namespace croot

