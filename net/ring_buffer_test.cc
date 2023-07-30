/*
 File Name: ring_buffer_test.cc
 Author: 
 Email: @croot.com
 Created: 2023-07-31
 Last Modified: 2023-07-31
*/
#include <thread>
#include <iostream>
#include "ring_buffer.h"
using namespace croot::lltg;

int main() {
  RingBuffer<int32_t, 1024> buffer;
  std::thread t1([&buffer](){
      int c = 0;
      while(true) {
      buffer.Push(c++);
      }
      });
  std::thread t2([&buffer](){
      int c = 0;
      while(true) {
        int v;
        if(buffer.Pop(&v)) {
            std::cout << v <<std::endl;
        }
      }
      });
  t1.join();
  t2.join();
}

