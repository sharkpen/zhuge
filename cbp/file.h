/*
 File Name: file.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-12
 Last Modified: 2023-09-12
*/
#pragma once
#include <string>
#include <vector>
namespace croot {
namespace lltg {

  class File {
 public:
  int TotalLines() { return lines.size(); }
  const std::string &Line(int num) { return lines.at(num - 1); }
  void PutLine(const std::string &line) { lines.push_back(line); }

 private:
  std::vector<std::string> lines;
};

}  // namespace lltg
}  // namespace croot

