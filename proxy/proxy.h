/*
 File Name: proxy.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-13
 Last Modified: 2023-09-13
*/
#pragma once
#include <arpa/inet.h>

#include <memory>
#include <string>
#include <thread>

#include "base64.h"
#include "log.h"
#include "socket.h"

namespace croot {
namespace lltg {

void inline do_proxy(Socket* reader, Socket* sender, Logger* logger) {
  int32_t type;
  int32_t length;
  int32_t checksum;
  char buffer[5000];

  while (true) {
    int len = reader->Read(4, buffer);
    if (len <= 0) {
      std::cerr << reader->Info() << " read error " << len << std::endl;
      break;
    }
    type = ntohl(*(int32_t*)(buffer));

    len = reader->Read(4, buffer + 4);
    if (len <= 0) {
      std::cerr << reader->Info() << " read error " << len << std::endl;
      break;
    }
    int length = ntohl(*(int32_t*)(buffer + 4));
    if (length > 0) {
      len = reader->Read(length, buffer + 8);
      if (len <= 0) {
        std::cerr << reader->Info() << " read error " << len << std::endl;
        break;
      }
    }
    logger->Info(type,
                 base64_encode((unsigned char const*)(buffer + 8), length));

    len = reader->Read(4, buffer + 8 + length);
    if (len <= 0) {
      std::cerr << reader->Info() << " read error " << len << std::endl;
      break;
    }
    len = sender->Send(length + 12, buffer);
    if (len <= 0) {
      std::cerr << sender->Info() << " send error " << len << std::endl;
      break;
    }
  }
}

class TcpProxy {
 public:
  TcpProxy(std::string remote_ip, int remote_port, int listen_port) {
    this->listen_port = listen_port;
    this->remote_ip = remote_ip;
    this->remote_port = remote_port;
  }
  void Start() {
    server = std::make_shared<Socket>("0.0.0.0", listen_port);
    if (server->Listen() == -1) {
      exit(1);
    }
    while (true) {
      if (server->Accept() != -1) {
        client = std::make_shared<Socket>(remote_ip, remote_port);
        if (client->Connect() != -1) {
          reader_logger = std::make_shared<Logger>("reader_logger.log");
          writer_logger = std::make_shared<Logger>("writer_logger.log");
          read_thread = std::make_shared<std::thread>(
              do_proxy, server.get(), client.get(), writer_logger.get());
          write_thread = std::make_shared<std::thread>(
              do_proxy, client.get(), server.get(), reader_logger.get());
          read_thread->join();
          write_thread->join();
          client->Close();
          server->Close();
          std::cerr << "connection reset" << std::endl;
        }
      }
    };
  };

 private:
  std::shared_ptr<std::thread> read_thread;
  std::shared_ptr<Logger> reader_logger;
  std::shared_ptr<Logger> writer_logger;
  std::shared_ptr<std::thread> write_thread;
  int listen_port;
  int remote_port;
  std::shared_ptr<Socket> server;
  std::shared_ptr<Socket> client;
  std::string remote_ip;
};

}  // namespace lltg
}  // namespace croot

