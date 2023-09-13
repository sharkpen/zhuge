/*
 File Name: common.cc
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-12
 Last Modified: 2023-09-12
*/
#include "common.h"
using namespace croot::lltg;

const std::set<std::string> Const::normal_types{"char",
  "int8","int16","int32", "int64", "double", "float", "array"};
const std::set<std::string> Const::simple_types{"char",
  "int8","int16","int32", "int64", "double", "float"};
const std::set<std::string> Const::multi_types{"char[", "array<"};
const std::string Const::NL = "\n";

