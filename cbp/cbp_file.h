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
#include <sstream>
#include <string>
#include <vector>

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
      if ("##" == token.term || strings::is_prefix("##", token.term)) {
        break;
      }
      if (token.line > note_line) {
        break;
      }
      ss << token.term;
    }
    std::string value = ss.str();
    auto field_context = context->contexts[name];
    field_context->define_maps[name_token.term] = value;
  }

  Type ParseField(std::shared_ptr<ParseContext> context, TokenParser &parser) {
    Token token = parser.CurrentToken();
    std::string type = token.term;
    Type ttype;
    ttype.type = type;
    if (type == "ref") {
      token = parser.NextToken();
      std::string ref_class = token.term;
      token = parser.NextToken();
      if (token.term != ";") {
        print_err(token, name, "error ; missing");
      }
      ttype.ref_class = ref_class;
      print_info(token, name, ttype.ToString());
      token = parser.NextToken();
      return ttype;
    } else {
      if (Const::normal_types.count(type) == 0) {
        print_err(token, name, "parse type err : illegal type");
      }
      token = parser.NextToken();
      if (token.term == "[") {
        if (Const::simple_types.count(type) == 0) {
          print_err(token, name, "error [ missing ");
        }
        token = parser.NextToken();
        int64_t v;
        if (strings::string2int(token.term, &v)) {
          ttype.len = v;
        } else {
          if (v <= 0) {
            print_err(token, name, "must be a positive integer");
          }
        }
        token = parser.NextToken();
        if (token.term != "]") {
          print_err(token, name, "error ] missing unclose brackets");
        }
        token = parser.NextToken();
        std::string field_name = token.term;
        ttype.name = field_name;
        token = parser.NextToken();
        if (token.term != ";") {
          print_err(token, name, "error ; missing");
        }
        print_info(token, name, ttype.ToString());
        token = parser.NextToken();
        return ttype; 
      }
      if (token.term == "<") {
        if (type != "array") {
          print_err(token, name, "error < missing");
        }
        token = parser.NextToken();
        if (token.term == "ref") {
          token = parser.NextToken();
          std::string ref_field = token.term;
          ttype.ref_field = ref_field;
          token = parser.NextToken();
          if (token.term != ",") {
            print_err(token, name, "error , missing");
          }
          token = parser.NextToken();
          std::string ref_class = token.term;
          ttype.ref_class = ref_class;
          token = parser.NextToken();
          if (token.term != ">") {
            print_err(token, name, "error > missing");
          }
          token = parser.NextToken();
          std::string field_name = token.term;
          ttype.name = field_name;
          token = parser.NextToken();
          if (token.term != ";") {
            print_err(token, name, "error ; missing");
          }
          print_info(token, name, ttype.ToString());
          token = parser.NextToken();
          return ttype;
        } 
        int64_t v;
        if (strings::string2int(token.term, &v)) {
          ttype.len = v;
          token = parser.NextToken();
          if (token.term != ",") {
            print_err(token, name, "error , missing");
          }
          token = parser.NextToken();
          std::string ref_class = token.term;
          ttype.ref_class = ref_class;
          token = parser.NextToken();
          if (token.term != ">") {
            print_err(token, name, "error > missing");
          }
          token = parser.NextToken();
          std::string field_name = token.term;
          ttype.name = field_name;
          token = parser.NextToken();
          if (token.term != ";") {
            print_err(token, name, "error ; missing");
          }
          print_info(token, name, ttype.ToString());
          token = parser.NextToken();
          return ttype;
        }
        print_err(token, name, "field array parse array");
      }
      std::string field_name = token.term;
      if (is_correct_struct_name(field_name)) {
        ttype.name = field_name;
        token = parser.NextToken();
        if (token.term != ";") {
          print_err(token, name, "error ; missing");
        }
        print_info(token, name, ttype.ToString());
        token = parser.NextToken();
        return ttype;
      } else {
        print_err(token, name, "field is no correct");
      }
    }
    print_err(token, name, "parse field error");
    return ttype;
  }

  /*void ParseField(std::shared_ptr<ParseContext> context, TokenParser &parser) {
    Token token = parser.CurrentToken();
    Type type = ParseType(context, parser);
    std::string field_name = parser.CurrentToken().term;
    token = parser.NextToken();
    if (token.term != ";") {
      print_err(token, name);
    } else {
      parser.NextToken();
    }
  }*/

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
    cbp_context->ordered_classes_desp.push_back(class_desp);
    class_desp->name = struct_name.term;
    Token token = parser.NextToken();
    while (token.term != "}") {
      token = parser.CurrentToken();
      if (token.term == "##" || strings::is_prefix("##", token.term)) {
        ParseNote(context, parser);
        continue;
      }
      auto type = ParseField(context, parser);
      token = parser.CurrentToken();
      class_desp->fields.push_back(type);
    }
    class_desps.push_back(class_desp);
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
    }
  }

  void ParseCbp(std::shared_ptr<ParseContext> context, TokenParser &parser) {
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
    }
  }
  static std::string GetDefineValue(const std::string &value,
                                    const std::string &name,
                                    std::shared_ptr<ParseContext> context) {
    auto cbp_context = context->contexts[name];
    if (cbp_context->define_maps.count(value) > 0) {
      std::string result = cbp_context->define_maps.at(value);
      if (is_field_type(result)) {
        return result;
      } else {
        return GetDefineValue(result, name, context);
      }
    } else {
      for (auto &dep : cbp_context->deps) {
        auto result = GetDefineValue(value, dep, context);
        if (result != "") {
          return result;
        }
      }
    }
    return "";
  }

  File *GenerateNewFile(TokenParser &parser,
                        std::shared_ptr<ParseContext> context) {
    File *f = new File();
    auto &token = parser.NextToken();
    int line = token.line;
    std::stringstream ss;
    while (token.line != -1 && token.offset != -1) {
      std::string term = token.term;
      if (token.term == "##" || strings::is_prefix("##", token.term)) {
        ParseNote(context, parser);
        continue;
      }
      if (token.term == "#define") {
        ParseDefine(context, parser);
        continue;
      }
      auto result = GetDefineValue(term, name, context);
      if (result != "") {
        term = result;
      }
      if (token.line > line) {
        f->PutLine(ss.str());
        ss.clear();
        ss.str("");
        line = token.line;
      }
      ss << term << ' ';
      token = parser.NextToken();
    }
    f->PutLine(ss.str());
    return f;
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
    File *f = GenerateNewFile(parser, context);
    file = f;
    file->Print();
    context->parse_success.insert(name);
    return true;
  }
  bool ParseSelf(std::shared_ptr<ParseContext> context) {
    auto cbp_context = std::make_shared<CbpFileContext>();
    context->contexts[name] = cbp_context;
    TokenParser parser(this->file);
    auto token = parser.NextToken();
    while (token.line != -1) {
      token = parser.CurrentToken();
      if (token.line == -1 && token.offset == -1) {
        break;
      }
      if (token.term == "import") {
        ParseImport(context, parser);
        continue;
      }
      if (token.term == "struct") {
        ParseStruct(context, parser);
        continue;
      }
      token = parser.NextToken();
    }
    return true;
  }
  int GetDepFilesNum() { return deps.size(); }

  std::string GetName() { return name; }

 private:
  std::vector<std::shared_ptr<ClassDesp>> class_desps;
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
      if (!strings::is_suffix(".cbp", name)) {
        continue;
      }
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
      // std::cout << "cbp parser " << key
      //           << " dep :" << cbp_file->GetDepFilesNum() << std::endl;
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
          // std::cout << success << "   " << group->files.size() << std::endl;
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
    for (auto f : order_files) {
      f->ParseSelf(context);
    }
    return true;
  }
  std::vector<CbpFile*> GetOrderFiles() {
    return order_files;
  }

 private:
  std::vector<std::shared_ptr<CbpFileDepGroup>> cbp_groups;
  std::vector<CbpFile *> order_files;
  std::map<std::string, CbpFile *> cbp_files;
  std::map<std::string, std::vector<std::string>> cbp_deps;
};
}  // namespace lltg
}  // namespace croot

