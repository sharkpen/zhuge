/*
 File Name: client.cc
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-08-16
 Last Modified: 2023-08-16
*/
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <chrono>

int main(int argc, char *argv[]) {
//  const char *server_ip = "10.1.1.2";  // 服务器的IP地址
  char *server_ip = NULL;  // 服务器的IP地址
  if (argc > 1) {
    server_ip = argv[1];
  } else {
    char ip[] = "10.1.1.2";
    server_ip = ip;
  }
  std::cout << "use ip " << server_ip << std::endl;
  int server_port = 8081;              // 服务器的端口号
  char buffer[500];                                      //
  char response[500];

  // 创建Socket
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    std::cerr << "Error creating socket" << std::endl;
    return 1;
  }

  // 设置服务器信息
  sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(server_port);
  inet_pton(AF_INET, server_ip, &server_address.sin_addr);

  // 连接服务器
  if (connect(client_socket, (struct sockaddr *)&server_address,
              sizeof(server_address)) == -1) {
    std::cerr << "Error connecting to server" << std::endl;
    close(client_socket);
    return 1;
  }
  while(true) {
    // 发送数据
    auto start_time = std::chrono::high_resolution_clock::now();
    if (send(client_socket, buffer, 500, 0) == -1) {
      std::cerr << "Error sending data" << std::endl;
      close(client_socket);
      return 1;
    }

    // 接收服务器响应
    if (recv(client_socket, response, 500, 0) == -1) {
      std::cerr << "Error receiving data" << std::endl;
      close(client_socket);
      return 1;
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << "Time elapsed: " << duration.count() << " microseconds" << std::endl;
  }

  // 关闭Socket连接
  close(client_socket);

  return 0;
}

