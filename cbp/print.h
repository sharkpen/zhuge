/*
 File Name: print.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-12
 Last Modified: 2023-09-12
*/
#pragma once
#include <iostream>
#include <string>

#include "common.h"
#include "synax.h"
namespace croot {
namespace lltg {

void inline print_err(const Token &token, const std::string &file,
                      const std::string &msg = "") {
  std::cerr << "file :" << file << std::endl;
  std::cerr << "error at " << token <<std::endl;
  std::cerr << "msg : " << msg << std::endl;
  exit(1);
}

void inline print_info(const Token &token, const std::string &file,
                      const std::string &msg = "") {
  std::cout << "file :" << file << std::endl;
  std::cout << "current token " << token <<std::endl;
  std::cout << "msg : " << msg << std::endl;
}

}  // namespace lltg
}  // namespace croot

