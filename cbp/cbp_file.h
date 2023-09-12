/*
 File Name: cbp_file.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-07
 Last Modified: 2023-09-07
*/
#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include <sstream>

#include "class_desp.h"
#include "context.h"
#include "file.h"
#include "file_util.h"
#include "print.h"
#include "strings/strings_utils.h"
#include "synax.h"
#include "synax_util.h"

namespace croot {
namespace lltg {

class CbpFile {
 public:
  CbpFile(File *file, const std::string &name) : name(name), file(file) {}

  void ParseDep() {
    int total_lines = file->TotalLines();
    for (int i = 1; i <= total_lines; i++) {
      std::string line = strings::trim(file->Line(i));
      if (strings::is_prefix("import ", line)) {
        std::vector<std::string> res;
        strings::split(line, ' ', &res);
        if (res.size() == 2) {
          deps.push_back(strings::trim(res.at(1), '"'));
        } else {
          std::cerr << " synax error " << name << " line  " << i << std::endl;
        }
      }
    }
  }
  void ParseNote(std::shared_ptr<ParseContext> context, TokenParser &parser) {
    auto &token = parser.CurrentToken();
    int note_line = token.line;
    while (true) {
      token = parser.NextToken();
      if (token.line == -1 && token.offset == -1) {
        break;
      }
      if (token.line > note_line) {
        break;
      }
    }
  }
  void ParseDefine(std::shared_ptr<ParseContext> context, TokenParser &parser) {
    auto name_token = parser.NextToken();
    int note_line = name_token.line;
    std::stringstream ss;
    
    while (true) {
      auto token = parser.NextToken();
      if (token.line == -1 && token.offset == -1) {
        break;
      }
      if (token.line > note_line) {
        break;
      }
      ss << token.term;
    }
    auto field_context = context->contexts[name];
    field_context->define_maps[name_token.term] = ss.str();
  }
  void ParseField(std::shared_ptr<ParseContext> context, TokenParser &parser) {
    Token token = parser.CurrentToken();
    std::cout << token << std::endl;
    while(token.term != ";") {
      token = parser.NextToken();
      print_err(token, name);
    }
    
  }
  
  void ParseStruct(std::shared_ptr<ParseContext> context, TokenParser &parser) {
    Token struct_name = parser.NextToken();
    if (!is_correct_struct_name(struct_name.term)) {
      print_err(struct_name, "not a correct struct name");
    }
    Token left_brackets = parser.NextToken();
    if ("{" != left_brackets.term) {
      print_err(struct_name, "struct define should start with {");
    }
    auto cbp_context = context->contexts[name];
    auto class_desp = std::make_shared<ClassDesp>();
    cbp_context->classes_desp[struct_name.term] = class_desp;
    Token token = parser.NextToken();
    while(true) {
      if (token.term == "##" || strings::is_prefix("##", token.term)) {
        ParseNote(context, parser);
        continue;
      }
      if (token.term != "}") {
        ParseField(context, parser);
      }
    }
    parser.NextToken();
  }

  void ParseImport(std::shared_ptr<ParseContext> context, TokenParser &parser) {
    parser.NextToken();
    parser.NextToken();
  }

  void ParseMacro(std::shared_ptr<ParseContext> context, TokenParser &parser) {
    parser.NextToken();
    while (true) {
      auto token = parser.CurrentToken();
      if (token.term == "##" || strings::is_prefix("##", token.term)) {
        ParseNote(context, parser);
        continue;
      }
      if (token.term == "#define") {
        ParseDefine(context, parser);
        continue;
      }
      token = parser.NextToken();
      if (token.line == -1 && token.offset == -1) {
        break;
      }
      std::cout << "test " <<std::endl;
    }
  }
  static std::string GetDefineValue(const std::string &value,
      const std::string &name, std::shared_ptr<ParseContext> context) {
    context->contexts[name];
    return "";
  }
  File* GenerateNewFile(TokenParser &parser, std::shared_ptr<ParseContext> context) {
    auto &token = parser.NextToken();
    int line = token.line;
    while (token.line != -1 && token.offset != -1) {
      auto term = token.term;

    }
    

    return nullptr;
  }
  bool PreParseSelf(std::shared_ptr<ParseContext> context) {
    for (const auto &dep_name : deps) {
      if (context->parse_success.count(dep_name) == 0) {
        return false;
      }
    }
    auto cbp_context = std::make_shared<CbpFileContext>();
    context->contexts[name] = cbp_context;

    cbp_context->deps = deps;

    TokenParser parser(this->file);
    ParseMacro(context, parser);
    parser.Reset();
    context->parse_success.insert(name);

    return true;
  }
  int GetDepFilesNum() { return deps.size(); }

  std::string GetName() { return name; }

 private:
  std::vector<std::string> deps;
  std::string name;
  File *file;
};

struct CbpFileDepGroup {
  std::vector<CbpFile *> files;
  int dep_num;
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
      cbp_file->ParseDep();
      order_files.push_back(cbp_file);
      std::cout << "cbp parser " << key
                << " dep :" << cbp_file->GetDepFilesNum() << std::endl;
    }
  }

  void ParseOrder() {
    std::sort(order_files.begin(), order_files.end(),
              [](CbpFile *a, CbpFile *b) {
                return a->GetDepFilesNum() < b->GetDepFilesNum();
              });
    int order_num = -1;

    for (auto file : order_files) {
      if (file->GetDepFilesNum() != order_num) {
        auto group = std::make_shared<CbpFileDepGroup>();
        group->files.push_back(file);
        group->dep_num = file->GetDepFilesNum();
        order_num = file->GetDepFilesNum();
        cbp_groups.push_back(group);
      } else {
        cbp_groups.back()->files.push_back(file);
      }
    }
  }

  bool ParserCbpFiles(std::shared_ptr<ParseContext> context) {
    for (auto group : cbp_groups) {
      int success = 0;
      while (true) {
        int mark = success;
        for (auto file : group->files) {
          if (file->PreParseSelf(context)) {
            success++;
          }
        }
        if (success == group->files.size()) {
          break;
        }
        if (mark == success) {
          std::cout << success << "   " << group->files.size() << std::endl;
          std::cerr << "file dependency recursion ";
          for (auto file : group->files) {
            if (context->parse_success.count(file->GetName()) == 0) {
              std::cerr << " " << file->GetName() << std::endl;
            }
          }
          return false;
        }
      }
    }
    return true;
  }

 private:
  std::vector<std::shared_ptr<CbpFileDepGroup>> cbp_groups;
  std::vector<CbpFile *> order_files;
  std::map<std::string, CbpFile *> cbp_files;
  std::map<std::string, std::vector<std::string>> cbp_deps;
};
}  // namespace lltg
}  // namespace croot

