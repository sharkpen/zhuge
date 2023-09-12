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
#include <set>
#include "strings/strings_utils.h"
#include "common.h"
namespace croot {
namespace lltg {


bool inline is_correct_struct_name(const std::string &name) {
  if (strings::is_blank(name)) {
    return false;
  }
  const char* p = name.c_str();
  char h = p[0];
  if (!std::isalpha(h) && h != '_') {
    return false;
  }

  for (int i = 1; i < name.size(); i++) {
    char c = name.c_str()[i];
    if (std::isalnum(c) || c == '_') {
      continue;
    }
    return false;
  }
  return true;
};

bool inline is_field_type(const std::string &name) {
  if (Const::normal_types.count(name) > 0) {
    return true;
  }
  if (strings::is_prefix("char[", name)) {
    return true;
  }
  if (strings::is_prefix("array<", name)) {
    return true;
  }
  return false;
}

}  // namespace lltg
}  // namespace croot

