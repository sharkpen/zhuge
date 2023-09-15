/*
 File Name: log.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-15
 Last Modified: 2023-09-15
*/
#pragma once
#include <fstream>
#include <string>
#include <iostream>
namespace croot {
namespace lltg {

class Formatter {
  void SetFormat(const std::string &name);
};
class Logger {
  public:
    Logger(const std::string &path) : fstream(path, std::ios::out | std::ios::trunc) {
       if (!fstream.is_open()) {
         std::cerr <<"log file is not ready exit";
         exit(1);
       }
    }
    void Info(int32_t type, const std::string &info) {
      fstream << type << " " << info << std::endl;
    }
    ~Logger() {
      fstream.flush();
      fstream.close();
    }
  private:
    std::ofstream fstream;
};
}  // namespace lltg
}  // namespace croot

