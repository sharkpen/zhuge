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
#include "enum.h"
namespace croot {
namespace lltg {

class Field {
  std::string name;
  FieldType type;
  int32_t len;
  std::string ref_field;
  std::string ref_class;
};

class ClassDesp {
  std::string name;
  int32_t len;
  std::vector<Field> fields;
};
}  // namespace lltg
}  // namespace croot

