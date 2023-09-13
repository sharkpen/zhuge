/*
 File Name: type_desp.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-07
 Last Modified: 2023-09-07
*/
#pragma once
#include <string>
#include <cstdint> 
#include <vector>
#include <sstream>
#include <memory>
#include "common.h"
#include "enum.h"
#include "print.h"
#include "context.h"
#include "file.h"
namespace croot {
namespace lltg {

struct Type {
  std::string name;
  int32_t len = 0;
  std::string type = "";
  std::string ref_field = "";
  std::string ref_class = "";
  std::string ToString() {
    std::stringstream ss;
    ss <<"( ";
    ss << type;
    if (type == "ref") {
      ss <<", " <<ref_class << " )";
      return ss.str();
    }
    if (Const::simple_types.count(type)) {
      if (len > 0) {
        ss << "[" << len << "], " << name << ")";
        return ss.str();
      } else {
        ss << ", " << name << ")";
        return ss.str();
      }
    } 
    if (type == "array") {
      ss << "array<";
      if (len > 0) {
        ss << len << ", " << ref_class << "> ," <<name << ")";
        return ss.str();
      }
      if (ref_field != "") {
        ss << "ref " << ref_field << ", " << ref_class << ">, " << name << ")"; 
        return ss.str();
      }
      std::cerr << "illegal Type" << std::endl;
      exit(1);
    }
    std::cerr << "unsupport type " << type << std::endl;
    exit(1);
  }
};

struct ClassDesp {
  std::string name;
  std::vector<Type> fields;
};



}  // namespace lltg
}  // namespace croot

