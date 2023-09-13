/*
 File Name: parse.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-07
 Last Modified: 2023-09-07
*/
#pragma once
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

#include "cbp_file.h"
#include "context.h"
#include "class_parser.h"
namespace croot {
namespace lltg {

class Parser {
  private:
    std::string output_dir = ".";
 private:
  std::vector<CbpFile *> files;
  void ListFiles(const std::string &root, std::vector<std::string> *files) {
    try {
      for (const auto &entry : std::filesystem::directory_iterator(root)) {
        if (entry.is_directory()) {
          ListFiles(entry.path().string(), files);
        } else if (entry.is_regular_file()) {
          files->push_back(entry.path().string());
        }
      }
    } catch (const std::exception &ex) {
      std::cerr << "遍历文件夹时出现错误：" << ex.what() << std::endl;
    }
  }

 public:
  void Parse(const std::string &root) {
    CbpParser parser;
    std::vector<std::string> files;
    ListFiles(root, &files);
    parser.GeneratorCbpFiles(root, files);
    parser.ParseOrder();
    std::shared_ptr<ParseContext> context = std::make_shared<ParseContext>();
    parser.ParserCbpFiles(context);
    auto cbp_files = parser.GetOrderFiles();
    std::vector<std::shared_ptr<CppClassFile>> cpp_files;
    for (auto f : cbp_files) {
      std::shared_ptr<CppClassFile> cpp_class_file = std::make_shared<CppClassFile>(f);
      cpp_files.push_back(cpp_class_file);
      cpp_class_file->Parse(context);
    }
    for (auto f : cpp_files) {
      f->Print();
    }
  };
};

}  // namespace lltg
}  // namespace croot

