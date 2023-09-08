/*
 File Name: echo_server.cc
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-08-16
 Last Modified: 2023-08-16
*/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // 创建 socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket." << std::endl;
        return 1;
    }

    // 设置服务器地址
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8081); // 使用端口号 12345

    // 绑定到指定地址和端口
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error binding socket." << std::endl;
        close(serverSocket);
        return 1;
    }

    // 开始监听
    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Error listening on socket." << std::endl;
        close(serverSocket);
        return 1;
    }

    std::cout << "Server is listening on port 12345..." << std::endl;

    // 接受客户端连接
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == -1) {
        std::cerr << "Error accepting client connection." << std::endl;
        close(serverSocket);
        return 1;
    }

    std::cout << "Connected to client." << std::endl;

    char buffer[1024];
    while (true) {
        // 接收客户端消息
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::cerr << "Client disconnected." << std::endl;
            break;
        }

        // 发送收到的消息回客户端
        send(clientSocket, buffer, bytesRead, 0);
    }

    // 关闭连接
    close(clientSocket);
    close(serverSocket);

    return 0;
}
