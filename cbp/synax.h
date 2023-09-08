/*
 File Name: synax.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-08
 Last Modified: 2023-09-08
*/
#pragma once
#include <string>
namespace croot {
namespace lltg {

class Token {
};


class SynaxParser {
  public:
   SynaxParser() {
   }
   bool Parse(const std::string& line) {
     return false;
   }

   std::string Error();
  private:
   std::string line;


}



}  // namespace lltg
}  // namespace croot

