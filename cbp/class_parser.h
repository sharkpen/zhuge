/*
 File Name: class_parser.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-07
 Last Modified: 2023-09-07
*/
#pragma once
#include <filesystem>
#include <memory>
#include <sstream>
#include <string>

#include "cbp_file.h"
#include "class_desp.h"
#include "common.h"
#include "context.h"
#include "file_util.h"
#include "print.h"
#include "strings/strings_utils.h"
namespace croot {
namespace lltg {
class CppClassFile {
 public:
  CppClassFile(CbpFile *file) { this->file = file; }
  void Parse(std::shared_ptr<ParseContext> context) {
    cpp_file = new File();
    std::string name = file->GetName();
    auto cbp_context = context->contexts[name];
    ParseHeader();
    for (auto class_desp : cbp_context->ordered_classes_desp) {
      std::shared_ptr<OneClassContext> one_context =
          std::make_shared<OneClassContext>();
      one_context->current_class_desp = class_desp;
      ParseClassHeader(class_desp);
      ParseClass(class_desp, context, one_context);
      ParseClassTail(class_desp, one_context);
    }
    ParseTail();
  }
  void ParseHeader() {
    *cpp_file << "#include <cstring>" << Const::NL;
    *cpp_file << "#include <cstdint>" << Const::NL;
    *cpp_file << "#include <iostream>" << Const::NL;
    *cpp_file << "#include <string>" << Const::NL;
    *cpp_file << "#pragma pack(push, 1)" << Const::NL;
  }
  void ParseTail() {
    *cpp_file << "#pragma pack(pop)" << Const::NL;
  }
  std::shared_ptr<ClassDesp> GetClassDesp(
      const std::string &file_name, const std::string &class_name,
      std::shared_ptr<ParseContext> context) {
    auto cbp_context = context->contexts[file_name];
    if (cbp_context->classes_desp.count(class_name) > 0) {
      return cbp_context->classes_desp[class_name];
    } else {
      for (auto d : cbp_context->deps) {
        auto desp = GetClassDesp(d, class_name, context);
        if (desp != nullptr) {
          return desp;
        }
      }
    }
    return nullptr;
  }
  void ParseClassHeader(std::shared_ptr<ClassDesp> class_desp) {
    *cpp_file << "struct ";
    *cpp_file << class_desp->name;
    *cpp_file << " {" << Const::NL;
  }
  void ParseClassTail(std::shared_ptr<ClassDesp> class_desp,
                      std::shared_ptr<OneClassContext> context) {
    *cpp_file << "void print(std::ostream &out = std::cout) {"
              << Const::NL;
    for (auto &entry : context->types) {
      std::string name = entry.second.name;
      std::string type = entry.second.type;
      int len = entry.second.len;
      if (len == 0 && Const::simple_types.count(type) > 0) {
        *cpp_file << "out << \"name: " << name << " value: \" <<  this->"
                  << name << " << std::endl;" << Const::NL;
        continue;
      }
      if (len > 0 && Const::simple_types.count(type) > 0) {
        if (type == "char") {
          *cpp_file << "out << \"name: " << name << " value: \";";
          *cpp_file << "out.write(" << name << "," << std::to_string(len) << ");" << Const::NL;
        }
      }
    }

    *cpp_file << "};" << Const::NL;

    *cpp_file << "};" << Const::NL;
  }
  void ParseClass(std::shared_ptr<ClassDesp> class_desp,
                  std::shared_ptr<ParseContext> context,
                  std::shared_ptr<OneClassContext> one_context) {
    for (auto f : class_desp->fields) {
      std::string type = TypeTrans(f.type);
      if (Const::simple_types.count(f.type) > 0 && f.len <= 0) {
        (one_context->types[f.name]) = f;
        *cpp_file << type << " " << f.name << ";" << Const::NL;
        *cpp_file << type << " "
                  << "get_" << f.name << "()"
                  << "{" << Const::NL;
        *cpp_file << "return " << f.name << ";";
        *cpp_file << "};" << Const::NL;

        *cpp_file << "void "
                  << "set_" << f.name << "(" << type << " " << f.name << ")"
                  << "{" << Const::NL;
        *cpp_file << "this->" << f.name << " = " << f.name << ";";
        *cpp_file << "};" << Const::NL;
        continue;
      }
      if (Const::simple_types.count(f.type) > 0 && f.len > 0) {
        (one_context->types[f.name]) = f;
        *cpp_file << type << " " << f.name << "[" << std::to_string(f.len)
                  << "];" << Const::NL;
        *cpp_file << "int len_" << f.name << "() {" << Const::NL << "return "
                  << std::to_string(f.len) << ";};" << Const::NL;

        *cpp_file << "const " << f.type << "* "
                  << "get_" << f.name << "()"
                  << "{" << Const::NL;
        *cpp_file << "return " << f.name << ";";
        *cpp_file << "};" << Const::NL;

        *cpp_file << "void "
                  << "set_" << f.name << "(" << type << "* " << f.name
                  << ", int len"
                  << ")"
                  << "{" << Const::NL;
        *cpp_file << "std::memcpy(this->" << f.name << ",  " << f.name
                  << ", len);";
        *cpp_file << "};" << Const::NL;
        continue;
      }
      if (f.type == "array") {
        if (f.len >= 0 && f.ref_field == "") {
          (one_context->types[f.name]) = f;
          *cpp_file << f.ref_class << " " << f.name << "["
                    << std::to_string(f.len) << "];" << Const::NL;
          *cpp_file << f.ref_class << "* get_" << f.name << "(int pos)"
                    << "{" << Const::NL;
          *cpp_file << "return (" << f.name << " + pos);"
                    << "}" << Const::NL;
          *cpp_file << "int len_" << f.name << "() {" << Const::NL << "return "
                    << std::to_string(f.len) << ";};" << Const::NL;

          *cpp_file << "void "
                    << "set_" << f.name << "(" << f.ref_class << "* " << f.name
                    << ", int pos"
                    << ")"
                    << "{" << Const::NL;
          *cpp_file << "std::memcpy((this->" << f.name << " + pos),  " << f.name
                    << ", sizeof(" << f.ref_class << "));";
          *cpp_file << "};" << Const::NL;
          continue;
        }
        if (f.len == 0 && f.ref_field != "") {
          auto last = one_context->current_class_desp->fields.back();
          if (last.name != f.name) {
            std::cerr << "dynamic len field must be last " << f.name;
            exit(1);
          }
          (one_context->types[f.name]) = f;
          std::string ref_field = f.ref_field;
          if (one_context->types.count(ref_field) == 0) {
            std::cerr << "dynamic len field ref data " << f.ref_field
                      << " do not exists";
            exit(1);
          }
          auto ref = (one_context->types)[ref_field];
          if (!strings::is_prefix("int", ref.type)) {
            std::cerr << "dynamic len field ref data type " << f.ref_field
                      << " is not  int " << ref.type << std::endl;
            exit(1);
          }
          (one_context->types[f.name]) = f;

          *cpp_file << f.ref_class << " " << f.name << "["
                    << std::to_string(f.len) << "];" << Const::NL;
          *cpp_file << f.ref_class << "* get_" << f.name << "(int pos)"
                    << "{" << Const::NL;
          *cpp_file << "return (" << f.name << " + pos);"
                    << "}" << Const::NL;
          *cpp_file << "int len_" << f.name << "() {" << Const::NL
                    << "return (int)this->" << ref.name << ";};" << Const::NL;

          *cpp_file << "void "
                    << "set_" << f.name << "(" << f.ref_class << "* " << f.name
                    << ", int pos"
                    << ")"
                    << "{" << Const::NL;
          *cpp_file << "std::memcpy((this->" << f.name << " + pos),  " << f.name
                    << ", sizeof(" << f.ref_class << "));";
          *cpp_file << "};" << Const::NL;
        }
      }
      if (f.type == "ref") {
        auto msg_desp = GetClassDesp(file->GetName(), f.ref_class, context);
        if (msg_desp == nullptr) {
          std::cerr << "ref type can't not be found " << f.ref_class;
          exit(1);
        }
        ParseClass(msg_desp, context, one_context);
      }
    }
  }

  void Print(const std::string &path = ".") {
    std::string name = file->GetName();
    std::string file_name = name.substr(0, name.size() - 4);
    std::string full_path = path + "/" + file_name + ".h";
    std::cout << "full path " << full_path << std::endl;
    std::string dir = get_dir_by_path(full_path);

    if (!std::filesystem::exists(dir)) {
      std::filesystem::create_directory(dir);
    }

    std::ofstream outputFile(full_path);

    if (!outputFile.is_open()) {
      std::cerr << "open file error" << std::endl;
      exit(1);
    }
    cpp_file->Print(outputFile);

    outputFile.close();

    // 检查文件是否成功关闭
    if (outputFile.fail()) {
      std::cerr << "can not close file" << std::endl;
      exit(1);
    }
  };

 private:
  CbpFile *file;
  File *cpp_file;
};
}  // namespace lltg
}  // namespace croot

