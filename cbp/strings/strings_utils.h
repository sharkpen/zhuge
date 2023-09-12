/*
 File Name: strings_utils.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-08
 Last Modified: 2023-09-08
*/
#pragma once
#include <string>
#include <vector>
namespace croot {
namespace lltg {
namespace strings {

void inline split(const std::string &str,
    char split, std::vector<std::string> *result) {
  const char* str_buffer = str.c_str();
  int pre = -1;
  for (int i = 0; i < str.size(); i++) {
    if (str_buffer[i] == split) {
      if (i > pre + 1) {
        result->push_back(str.substr(pre + 1, i - pre - 1));
        pre = i;
      }
    }
  }
  if (pre + 1 < str.size() - 1) {
    result->push_back(str.substr(pre + 1, str.size() - pre - 1));
  }
}

std::string inline trim(const std::string &str, char w = ' ') { 
  const char* str_buffer = str.c_str();
  int start = 0;
  int end = str.size() - 1;
  while(str_buffer[start] == w && start <= end) {
    start++;
  }
  while(str_buffer[end] == w && start <= end) {
    end--;
  }
  if (start >= end) {
    return "";
  }
  return str.substr(start, end - start + 1);
}

bool inline is_prefix(const std::string &prefix, const std::string &sen) {
  if (prefix.size() > sen.size()) {
    return false;
  }

  const char *prefix_buff = prefix.c_str();
  const char *sen_buff = sen.c_str();
  for (int i = 0; i < prefix.size(); i++) {
    if (prefix_buff[i] != sen_buff[i]) {
      return false;
    }
  }
  return true;
}
bool inline is_suffix(const std::string &suffix, const std::string &sen) {
  if (suffix.size() > sen.size()) {
    return false;
  }
  const char *suffix_buff = suffix.c_str();
  const char *sen_buff = sen.c_str();
  for (int i = 0; i < suffix.size(); i++) {
    if (suffix_buff[suffix.size() - i - 1] != sen_buff[sen.size() - i - 1]) {
      return false;
    }
  }
  return true;
}

bool inline is_blank(const std::string &str) {
  return "" == trim(str, ' ');
}

bool inline string2int(const std::string &str, int64_t *value) {
  return 0;
}

}  // namespace strings
}  // namespace lltg
}  // namespace croot

