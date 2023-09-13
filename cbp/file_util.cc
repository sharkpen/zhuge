/*
 File Name: file_util.cc
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-08
 Last Modified: 2023-09-08
*/
#include "file_util.h"

#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>

#include "strings/strings_utils.h"

namespace croot {
namespace lltg {
std::string trim_path(const std::string &path) {
  const char *path_buffer = path.c_str();
  int start = 0;
  int end = path.size() - 1;
  while (path_buffer[start] == '/' && start <= end) {
    start++;
  }
  while (path_buffer[end] == '/' && start <= end) {
    end--;
  }
  if (start == end) {
    return "";
  }
  return path.substr(start, (end - start) + 1);
}

std::string cut_prefix_path(const std::string &root,
                            const std::string &file_name) {
  if (strings::is_prefix(root, file_name)) {
    return trim_path(
        file_name.substr(root.size(), file_name.size() - root.size()));
  }
  return "";
}
std::string get_file_by_path(const std::string& path) {
  std::string trim = trim_path(path); 
  std::vector<std::string> paths;
  strings::split(trim, '/', &paths);
  if (paths.empty()) {
    return "";
  }
  return paths.back();
};

std::string get_dir_by_path(const std::string& path) {
  std::vector<std::string> paths;
  strings::split(path, '/', &paths);
  if (paths.size() <= 1) {
    return "";
  }
  std::stringstream ss;
  for (int i = 0; i < paths.size() - 1; i++) {
    ss << paths.at(i) << '/';
  }
  return ss.str();
};

}  // namespace lltg
}  // namespace croot
