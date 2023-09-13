/*
 File Name: test.cc
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-08
 Last Modified: 2023-09-08
*/
#include <iostream>
#include <sstream>
#include <vector>

#include "cbp_file.h"
#include "file_util.h"
#include "parse.h"
#include "strings/strings_utils.h"
#include "synax.h"
#include "file.h"
using namespace croot::lltg;
auto &NL =  Const::NL;

int main() {
  std::string path = "/home/lijinqi/workspace/zhuge/build/cbp";
  /*std::string test = "   8< aa> b{b cc}    ;d;d e  ff ddde e";
  StringTokenIterator ite(test);
  std::string token;
  while ((token = ite.NextToken()) != "") {
    std::cout << ite.Offset() << " : " << token << std::endl;
  }

  std::vector<std::string> res;
  strings::split(test, ' ', &res);
  for (auto t : res) {
    std::cout << "test 2 " << t << std::endl;
  }
  std::stringstream ss;
  ss << "a";
  std::cout << ss.str() << std::endl;
  ss << "b";
  std::cout << ss.str() << std::endl;
  ss << "pppppp" << std::endl;
  std::cout << ss.str();
  ss << "cc";
  std::cout << ss.str() << std::endl;*/
  /*File file;
  file << "hahahah" << "\n";
  file << "aaaaaa ";
  file << "bbbbb";
  file << "\n";
  file.Print();*/
  std::cout << get_file_by_path(path) <<std::endl;
  std::cout << get_dir_by_path(path) <<std::endl;

  return 0;
}

