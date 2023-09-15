/*
 File Name: socket.h
 Author: lijinqi
 Email: lijinqi@croot.com
Created: 2023-06-11
 Last Modified: 2023-06-11
*/
#pragma once
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>

#include <cstdint>
#include <iostream>
#include <string>

namespace croot {
namespace lltg {

class Socket {
 public:
  Socket(const std::string& host, int port) : host(host), port(port) {}
  std::string Info() { return host + ":" + std::to_string(port); }
  int Connect() {
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address {};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    if (inet_pton(AF_INET, host.c_str(), &(server_address.sin_addr)) <= 0) {
      std::cerr << "Invalid address." << std::endl;
      return -1;
    }
    std::cout <<"connext" << std::endl;
    if (connect(client_socket, (struct sockaddr*)&server_address,
                sizeof(server_address)) == -1) {
      std::cerr << "Failed to connect to server." << std::endl;
      return -1;
    }
    std::cout <<"connext" << std::endl;
    return 0;
  }
  int Listen() {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
      std::cerr << "Failed to create socket" << std::endl;
      return -1;
    }
    std::cout << "1" << std::endl;
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_socket, reinterpret_cast<sockaddr*>(&server_address),
             sizeof(server_address)) == -1) {
      std::cerr << "Failed to bind socket" << std::endl;
      return false;
    }
    std::cout << "2" << std::endl;
    int listen_result = listen(server_socket, SOMAXCONN);
    if (listen_result == -1) {
      std::cerr << "Failed to listen on socket" << std::endl;
      return -1;
    }
    std::cout << "3" << std::endl;
    return listen_result;
  }
  int Accept() {
    sockaddr_in client_address{};
    socklen_t client_address_length = sizeof(client_address);
    client_socket =
        accept(server_socket, reinterpret_cast<sockaddr*>(&client_address),
               &client_address_length);
    if (client_socket == -1) {
      std::cerr << "Failed to accept client connection" << std::endl;
    }
    return client_socket;
  }

  int Send(int32_t length, char* buffer) {
    int len = send(client_socket, buffer, length, 0);
    if (len == 0) {
      return 0;
    }
    if (len == -1) {
      return -1;
    }
    while (len != length) {
      if (len < 0) {
        return -1;
      }
      len += send(client_socket, (buffer + len), length - len, 0);
    }
    return length;
  }

  int Read(int32_t length, char* buffer) {
    int len =  recv(client_socket, buffer, length, 0);
    if (len <= 0) {
      return len;
    }
    while(len < length) {
      int l = recv(client_socket, buffer, length - len, 0);
      if (l <= 0) {
        return l;
      }
      len += l;
    }
    return len;
  }

  void Close() { close(client_socket); }

 private:
  std::string host;
  int port;
  int client_socket = -1;
  int server_socket = -1;
};

}  // namespace lltg
}  // namespace croot

