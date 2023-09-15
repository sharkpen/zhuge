/*
 File Name: base64_test.cc
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-15
 Last Modified: 2023-09-15
*/
#include "base64.h"

#include <iostream>

int main() {
  char buffer[500];
  for (int i = 0; i < 500; i++) {
    buffer[i] = i;
  }
  std::string original_text = "Hello, World!";  // 要编码的原始文本

  // Base64编码
  std::string encoded_text = base64_encode((unsigned char*)buffer, 500);
  std::cout << "Encoded: " << encoded_text << std::endl;

  // Base64解码
  std::string decoded_text = base64_decode(encoded_text);
  for (int i = 0; i < 500; i++) {
    if (decoded_text[i] != buffer[i]) {
      std::cout << "check failed" <<std::endl;
    }
  }
}

