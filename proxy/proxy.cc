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
#include "proxy.h"

using namespace croot::lltg;

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "argument error"; 
    exit(1);
  }
  char * listen_port = argv[1];
  char* remote_host = argv[2];
  char* remote_port = argv[3];
  int lp = std::atoi(listen_port);
  std::string rh(remote_host);
  int rp = std::atoi(remote_port);

  
  TcpProxy proxy(rh, rp, lp);
  proxy.Start();


  return 0;
}

