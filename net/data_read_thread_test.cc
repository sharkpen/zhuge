/*
 File Name: data_read_thread_test.cc
 Author: 
 Email: @croot.com
 Created: 2023-07-31
 Last Modified: 2023-07-31
*/
#include "data_read_thread.h"
using namespace croot::lltg;

int main(int argc, char* argv[]) {
  DevReader reader;
  reader.Start(argc, argv);
  reader.ReadBuffer();
}


