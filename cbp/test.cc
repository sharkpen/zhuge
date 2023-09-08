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
  std::vector<std::string> res;
  const std::string d = "import \"sz/sz_common_define.cbp\"";
  strings::split(d, ' ', &res);
  for (auto& r :res) {
    std::cout << "test 1 " << r <<std::endl;
  }
  Parser parser;
  parser.Parse("/home/lijinqi/workspace/zhuge/proto");
  
  return 0;
}

