/*
 File Name: common.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-12
 Last Modified: 2023-09-12
*/
#pragma once
#include <iostream>
#include <string>
#include <set>
namespace croot {
namespace lltg {

struct Token {
  int line;
  int offset;
  std::string term;
  std::string ToString() {
    return "<" + std::to_string(line) + "," + std::to_string(offset) +
           ">:" + term;
  }
  friend std::ostream &operator<<(std::ostream &cout, Token &token) {
    return cout << "<" << token.line << "," << token.offset
                << ">:" << token.term;
  }
};

struct Const {
  static std::set<std::string> simple_types; 
  static std::set<std::string> normal_types; 
  static std::set<std::string> multi_types; 
};


}  // namespace lltg
}  // namespace croot

