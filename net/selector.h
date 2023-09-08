/*
 File Name: selector.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-07-29
 Last Modified: 2023-07-29
*/
#pragma once
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <netinet/in.h>
#include <arpa/inet.h>
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
    int listen(int32_t port) {
      listen_fd = socket(AF_INET, SOCK_STREAM, 0);
      if (listen_fd == -1) {
        std::cerr << "Error creating socket\n";
        return 1; 
      }

      int optval = 1;
      if(setsockopt(listen_fd, SOL_SOCKET,
            SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        std::cerr << "Error setting socket option\n";
        close(listen_fd);
        return 1;
      }

      sockaddr_in server_addr;
      server_addr.sin_family = AF_INET;
      server_addr.sin_addr.s_addr = INADDR_ANY;
      server_addr.sin_port = htons(port);
      if (bind(listen_fd, (struct sockaddr*)&server_addr,
            sizeof(server_addr)) == -1) {
        std::cerr << "Error binding address \n";
        close(listen_fd);
        return 1;
      }

      if (::listen(listen_fd, 5) == -1) {
        std::cerr << "Error listen port \n";
        close(listen_fd);
        return 1;
      }

      int epoll_fd = epoll_create1(0);
      if (epoll_fd == -1) {
        std::cerr << "Error creating epoll\n";
        close(listen_fd);
      }

      struct epoll_event event;
      event.events = EPOLLIN;
      event.data.fd = listen_fd;
      if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event) == -1) {
        std::cerr << "Error adding socket to epoll\n";
        close(listen_fd);
        close(epoll_fd);
        return 1;
      }

      return 0;
    };
    std::shared_ptr<Channel> select() {
      return next_channels.Take();
    };
  private:
    BlockingQueue<std::shared_ptr<Channel>> next_channels;
    std::unordered_map<int, std::shared_ptr<Channel>> channels;
    int listen_fd;
    std::shared_ptr<Dispatcher> dispatcher_;
};

}  // namespace lltg
}  // namespace croot

