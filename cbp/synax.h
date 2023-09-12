/*
 File Name: synax.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-08
 Last Modified: 2023-09-08
*/
#pragma once
#include <memory>
#include <ostream>
#include <string>
#include <iostream>
#include "context.h"
#include "file.h"
#include "common.h"
namespace croot {
namespace lltg {


class StringTokenIterator {
 public:
  StringTokenIterator(const std::string &line) : line(line) {}
  std::string NextToken() {
    const static std::set<char> uniq_chars{'[',']','<', '>', ';', '{', '}'};
    const char* p = line.c_str();
    int current_offset = offset; 
    while (current_offset < line.size() && p[current_offset] == ' ') {
      current_offset++;
    }
    offset = current_offset;
    if (uniq_chars.count(p[offset]) > 0) {
        return line.substr(offset++, 1);
    }
    

    while (current_offset < line.size() && p[current_offset] != ' ') {
      current_offset++;
      if (uniq_chars.count(p[current_offset]) > 0) {
        break;
      }
    }
    len = current_offset - offset;
    if (len == 0) {
      return "";
    }
    std::string term = line.substr(offset, len);
    offset = current_offset;

    return term;
  }
  int Offset() {
    return offset - len;
  }
 private:
  int offset = 0;
  int len = 0;
  std::string line;
};

class TokenParser {
 public:
  TokenParser(File *file) { this->file = file; }
  Token& NextToken() {
    if (line_ite == nullptr) {
        line_ite = std::make_shared<StringTokenIterator>(file->Line(line));
    }
    std::string term = line_ite->NextToken();
    if (term == "") {
      if (line >= file->TotalLines()) {
        token.line = -1;
        token.offset = -1;
        token.term = "";
        std::cout << token <<std::endl;
        return token;
      };
      line++;
      line_ite = std::make_shared<StringTokenIterator>(file->Line(line)); 
      return NextToken();
    } else {
      token.term = term;
      token.line = line;
      token.offset = line_ite->Offset();
      std::cout << token <<std::endl;
      return token;
    }
  }
  Token& CurrentToken() {
    return token;
  }
  void Reset() {
    line = 1;
    line_ite = nullptr;
  }

 private:
  Token token;
  int line = 1;
  std::shared_ptr<StringTokenIterator> line_ite;
  File *file;
};



}  // namespace lltg
}  // namespace croot

