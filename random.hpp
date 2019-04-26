#ifndef __HEX_GENERATOR
#define __HEX_GENERATOR

#include <vector>
#include <iostream>
#include <sstream>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>
#include <string>

class HexGenerator{
  static unsigned char random_char() {
    std::random_device rd;
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> dis(0, 255);
    return static_cast<unsigned char>(dis(gen));
  }

  public 
    std::string generate_hex(const unsigned int len) {
      std::stringstream ss;
      for(auto i = 0; i < len; i++) {
        auto rc = random_char();
        std::stringstream hexstream;
        hexstream << std::hex << int(rc);
        auto hex = hexstream.str(); 
        ss << (hex.length() < 2 ? '0' + hex : hex);
      }        
      return ss.str();
    }
}
#endif
