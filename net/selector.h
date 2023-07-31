/*
 File Name: selector.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-07-29
 Last Modified: 2023-07-29
*/
#pragma once
#include <stdint.h>
#include <memory>
#include <unordered_map>
#include "channel.h"
#include "blocking_queue.h"

namespace croot {
namespace lltg {
class Dispatcher {
  public:
    void Route();
    std::shared_ptr<Channel> NextChannel() {
      return blocking_queue_.Take();
    };
  private:
    BlockingQueue<std::shared_ptr<Channel>> blocking_queue_;
};
class DevReader {
  public:
    DevReader(std::shared_ptr<Dispatcher> dispatcher) :
      dispatcher_(dispatcher) {}
    void Start(int32_t port_id);
  private:
    std::shared_ptr<Dispatcher> dispatcher_;
};

class Selector {
  public:
    int Open(int32_t port);
    std::shared_ptr<Channel> select() {
      return dispatcher_->NextChannel();
    };
  private:
    std::shared_ptr<Dispatcher> dispatcher_;
};

}  // namespace lltg
}  // namespace croot

