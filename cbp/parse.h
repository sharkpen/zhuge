/*
 File Name: parse.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-07
 Last Modified: 2023-09-07
*/
#pragma once
#include <string>
#include <iostream>
#include <filesystem>

#include "cbp_file.h"
namespace croot {
namespace lltg {

class Parser {
 private:
  std::vector<CbpFile *> files;
  void ListFiles(const std::string &root, std::vector<std::string> *files) {
    try {
      for (const auto &entry : std::filesystem::directory_iterator(root)) {
        if (entry.is_directory()) {
          // 如果是子目录，递归遍历
          ListFiles(entry.path().string(), files);
        } else if (entry.is_regular_file()) {
          // 如果是文件，打印文件名
          std::cout << entry.path().filename() << std::endl;
          std::cout << entry.path().string() << std::endl;
          files->push_back(entry.path().string());
        }
      }
    } catch (const std::exception &ex) {
      std::cerr << "遍历文件夹时出现错误：" << ex.what() << std::endl;
    }
  }

 public:
  void Parse(const std::string &root){
    CbpParser parser;
    std::vector<std::string> files;
    ListFiles(root, &files);
    parser.GeneratorCbpFiles(root, files);

  };
};

}  // namespace lltg
}  // namespace croot

