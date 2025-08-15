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
  var(var_mode mode, std::any data);
  ~var();
  
  std::any data(var_mode mode);
  void set(var_mode mode, std::any data);
private:
  var_mode type;
  float* f32;
  int* i32;
  std::string str;

protected:

};

extern std::unordered_map<std::string, var> vars;

bool var_handler(std::vector<std::string>& lines);




