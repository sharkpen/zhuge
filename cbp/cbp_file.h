/*
 File Name: cbp_file.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-07
 Last Modified: 2023-09-07
*/
#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "file_util.h"
#include "strings/strings_utils.h"
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

class CbpFile {
 public:
  CbpFile(File *context, const std::string &name)
      : name(name), context(context) {}

  bool Parse() { return false; }
  std::vector<std::string> ParseDep() {
    std::vector<std::string> dep;
    int total_lines = context->TotalLines();
    for (int i = 1; i <= total_lines; i++) {
      std::string line = strings::trim(context->Line(i));
      if (strings::is_prefix("import ", line)) {
        std::vector<std::string> res;
        strings::split(line, ' ', &res);
        if (res.size() == 2) {
          dep.push_back(strings::trim(res.at(1), '"'));
        } else {
          std::cerr << " synax error " << name << " line  " << i << std::endl;
        }
      }
    }
    return dep;
  }

 private:
  std::string name;
  File *context;
};

class CbpParser {
 public:
  void GeneratorCbpFiles(const std::string &root,
                         std::vector<std::string> &files) {
    for (const auto &name : files) {
      auto key = cut_prefix_path(root, name);
      File *f = new File();
      std::ifstream file(name);
      if (!file.is_open()) {
        std::cerr << "can not open file " << name << std::endl;
      }
      std::string line;
      while (std::getline(file, line)) {
        f->PutLine(line);
      }
      CbpFile *cbp_file = new CbpFile(f, key);
      cbp_files[key] = cbp_file;
      cbp_deps[key] = cbp_file->ParseDep();
      for (auto dep : cbp_deps[key]) {
        std::cout << "file " << key << " << dep " << dep <<std::endl;
      }
    }
  }


 private:
  std::map<std::string, CbpFile *> cbp_files;
  std::map<std::string, std::vector<std::string>> cbp_deps;
};
}  // namespace lltg
}  // namespace croot

