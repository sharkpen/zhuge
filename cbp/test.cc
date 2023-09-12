/*
 File Name: test.cc
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-08
 Last Modified: 2023-09-08
*/
#include <iostream>
#include <vector>

#include "cbp_file.h"
#include "file_util.h"
#include "parse.h"
#include "strings/strings_utils.h"
#include "synax.h"
using namespace croot::lltg;

int main() {
  std::string test = "   8< aa> b{b cc}    ;d;d e  ff ddde e";
  StringTokenIterator ite(test);
  std::string token;
  while ((token = ite.NextToken()) != "") {
    std::cout << ite.Offset() << " : " << token << std::endl;
  }

  std::vector<std::string> res;  
  strings::split(test, ' ',&res);
  for (auto t : res) {
    std::cout <<"test 2 " <<t <<std::endl;
  }



  return 0;
}

