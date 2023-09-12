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
#include "class_desp.h"

namespace croot {
namespace lltg {

struct CbpFileContext {
  std::vector<std::string> deps;
  std::map<std::string, std::string> define_maps;
  std::map<std::string, std::shared_ptr<ClassDesp>> classes_desp;
};

struct ParseContext {
  std::set<std::string> parse_success; 
  std::map<std::string, std::shared_ptr<CbpFileContext>> contexts;
};

  
}  // namespace lltg
}  // namespace croot

