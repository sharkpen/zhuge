/*
 File Name: class_parser.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-07
 Last Modified: 2023-09-07
*/
#pragma once
#include <string>
#include "class_desp.h" 
namespace croot {
namespace lltg {
class ClassParser {
  public:
    std::string Parse(ClassDesp *type);

};
}  // namespace lltg
}  // namespace croot

