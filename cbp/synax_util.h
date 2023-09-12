/*
 File Name: synax_util.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-12
 Last Modified: 2023-09-12
*/
#pragma once
#include <cctype>
#include <string>
#include "strings/strings_utils.h"
namespace croot {
namespace lltg {


bool inline is_correct_struct_name(const std::string &name) {
  if (strings::is_blank(name)) {
    return false;
  }
  const char* p = name.c_str();
  char h = p[0];
  if (!std::isalpha(h)) {
    return false;
  }

  for (int i = 1; i < name.size(); i++) {
    char c = name.c_str()[i];
    if (std::isalnum(c)) {
      continue;
    }
    return false;
  }
  return true;
};

}  // namespace lltg
}  // namespace croot

