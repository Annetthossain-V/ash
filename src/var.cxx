
#include <any>
#include <string>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <cctype>

#include "var.h"

std::unordered_map<std::string, var> vars;

bool var_handler(std::vector<std::string>& lines) {
  std::string var_name = "$";
  var_mode mode = var_mode::i32;
  var container(mode, 1);

  // TODO: add static value type

  if (lines.size() < 4) {
    std::cerr << "let: invalid arguments!" << std::endl;
    return false;
  }

  // name = 1, 2 = '=', 3, = data
  if (lines[2] != "=") {
    std::cerr << "equal operator missing!" << std::endl;
    return false;
  }
  var_name.append(lines[1]);
  
  auto value = lines[3];
  bool all_digits = std::all_of(value.begin(), value.end(), ::isdigit);

  if (all_digits) {
    if (value.find(".") != std::string::npos) {
      mode = var_mode::f32;
      container.set(mode, (float)atof(value.c_str()));
    } else {
      mode = var_mode::i32;
      container.set(mode, atoi(value.c_str()));
    }
    vars.emplace(var_name, container);
  }
  else {
    mode = var_mode::str;
    container.set(mode, value);
    vars.emplace(var_name, container);
  }

  return true;
}

var getvar(std::string& name) {
  auto item = vars.find(name);
  if (item != vars.end()) {
    return item->second;
  } else {
    return var(var_mode::i32, 0);
  }
}

void setvar(var item, std::string& name) {
  vars.emplace(name, item);
}

var::var(var_mode mode, std::any data) {
  this->f32 = new float;
  this->i32 = new int;
  this->set(mode, data);

  return;
}

void var::set(var_mode mode, std::any data) {
  switch (mode) {
    case var_mode::f32:
      *this->f32 = std::any_cast<float>(data);
      break;
    case var_mode::i32:
      *this->i32 = std::any_cast<int>(data);
      break;
    case var_mode::str:
      this->str = std::any_cast<std::string>(data);
      break;
  }

  this->type = mode;
  return;
}

var::~var() {
  delete this->f32;
  delete this->i32; 
  this->str.clear();
  return;
}

std::any var::data(var_mode mode) {
  switch (mode) {
    case var_mode::f32:
      return std::any(*this->f32);
    case var_mode::i32:
      return std::any(*this->i32);
    case var_mode::str:
      return std::any(this->str);
  }
}
