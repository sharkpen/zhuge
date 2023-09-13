/*
 File Name: file.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-12
 Last Modified: 2023-09-12
*/
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "common.h"
namespace croot {
namespace lltg {

struct FileLine {
  std::stringstream ss;
};

class File {
 public:
  File() {}
  int TotalLines() { return lines.size(); }
  const std::string Line(int num) {
    const FileLine &line = lines.at(num - 1);
    return line.ss.str();
  }
  void PutLine(const std::string &line) {
    lines.emplace_back();
    FileLine &l = lines.back();
    l.ss << line;
  }
  void Print(std::ostream &out = std::cout) {
    int count = 1;
    for (auto &l : lines) {
      //std::cout << count++ << " " << l.ss.str() << std::endl;
      out << l.ss.str() << std::endl;
    }
  }
  friend File &operator<<(File &file, const std::string &str) {
    if (str != Const::NL) {
      if (file.lines.empty()) {
        file.lines.emplace_back();
      }
      FileLine &l = file.lines.back();
      l.ss << str;
    } else {
      file.lines.emplace_back();
    }

    return file;
  }

 private:
  std::vector<FileLine> lines;
};

}  // namespace lltg
}  // namespace croot

