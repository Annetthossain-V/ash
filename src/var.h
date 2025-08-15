#pragma once

#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <any>

enum var_mode {
  str,
  f32,
  i32
};

class var {
public:
  var(enum var_mode, std::any data);
private:
  enum var_mode type;
  float f32;
  int i32;
  std::string str;

protected:

};

extern std::unordered_map<short, var> vars;

bool var_handler(std::vector<std::string>& lines);




