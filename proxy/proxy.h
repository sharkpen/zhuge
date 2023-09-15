/*
 File Name: proxy.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-13
 Last Modified: 2023-09-13
*/
#pragma once
#include <string>
#include <thread>
#include <memory>
#include <arpa/inet.h>

#include "socket.h"
#include "base64.h"



namespace croot {
namespace lltg {

void inline do_proxy(Socket* reader, Socket* sender) {
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


    len = reader->Read(length, buffer + 8);
    if (len <= 0) {
      std::cerr << reader->Info() << " read error " << len << std::endl;
      break;
    }


    std::cout << "msg type : " << type <<std::endl;
    std::cout << "msg length : " << length <<std::endl;
    std::cout << "msg : " << base64_encode((unsigned char const*)(buffer + 8), length) <<std::endl;
    std::cout << "<--------------------------->" <<std::endl;

    len = reader->Read(4, buffer + 8 + length);
    if (len <= 0) {
      std::cerr << reader->Info() << " read error " << len << std::endl;
      break;
    }
    len = sender->Send(length +12, buffer);
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
    if (server->Accept() != -1) {
      client= std::make_shared<Socket>(remote_ip, remote_port);
      if (client->Connect() != -1) {
        read_thread = std::make_shared<std::thread>(do_proxy, server.get(), client.get());
        write_thread = std::make_shared<std::thread>(do_proxy, client.get(), server.get());
        read_thread->join();
        write_thread->join();
      }
    };
  };

 private:
  std::shared_ptr<std::thread> read_thread;
  std::shared_ptr<std::thread> write_thread;
  int listen_port;
  int remote_port;
  std::shared_ptr<Socket> server;
  std::shared_ptr<Socket> client;
  std::string remote_ip;
};

}  // namespace lltg
}  // namespace croot

