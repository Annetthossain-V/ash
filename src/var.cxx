
#include <string>
#include <map>
#include <iostream>

#include "var.h"

std::unordered_map<short, var> vars;

bool var_handler(std::vector<std::string>& lines) {

  if (lines.size() < 4) {
    std::cerr << "let: invalid arguments!" << std::endl;
    return false;
  }

  

  return true;
}
