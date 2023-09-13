/*
 File Name: context.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-12
 Last Modified: 2023-09-12
*/
#pragma once
#include <string>
#include <map>
#include <memory>
#include <set>
#include <vector>

namespace croot {
namespace lltg {
class ClassDesp;
class Type;

struct OneClassContext{
  std::shared_ptr<ClassDesp> current_class_desp;
  int pased_class_num = 0;
  std::map<std::string, Type> types;
};

struct CbpFileContext {
  std::vector<std::string> deps;
  std::map<std::string, std::string> define_maps;
  std::map<std::string, std::shared_ptr<ClassDesp>> classes_desp;
  std::vector<std::shared_ptr<ClassDesp>> ordered_classes_desp;
};

struct ParseContext {
  std::set<std::string> parse_success; 
  std::map<std::string, std::shared_ptr<CbpFileContext>> contexts;
};

  
}  // namespace lltg
}  // namespace croot

