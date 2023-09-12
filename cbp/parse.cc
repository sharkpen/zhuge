/*
 File Name: test.cc
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-08
 Last Modified: 2023-09-08
*/
#include "file_util.h"
#include <iostream>
#include <vector>
#include "cbp_file.h"
#include "file_util.h"
#include "parse.h"
#include "strings/strings_utils.h"
using namespace croot::lltg;

int main() {
  
  Parser parser;
  //parser.Parse("/home/lijinqi/workspace/zhuge/proto");
  parser.Parse("/Users/sharkpen/workapace/zhuge/proto");
  
  return 0;
}

