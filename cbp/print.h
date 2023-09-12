/*
 File Name: print.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-12
 Last Modified: 2023-09-12
*/
#pragma once
#include <string>
#include <iostream>
#include "synax.h"
#include "common.h"
namespace croot {
namespace lltg {

void inline print_err(const Token &token, const std::string &msg) {
  std::cerr << msg <<std::endl;
  std::cerr << "synax error at line : " << token.line
    << " offset : " << token.offset <<std::endl;
}

}  // namespace lltg
}  // namespace croot

