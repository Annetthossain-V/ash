
#include <any>
#include <string>
#include <unordered_map>
#include <iostream>

#include "var.h"

std::unordered_map<std::string, var> vars;

bool var_handler(std::vector<std::string>& lines) {
  std::string vname = "$";
  var_mode mode;
  var container(var_mode::i32, 1);

  if (lines.size() < 4) {
    std::cerr << "let: invalid arguments!" << std::endl;
    return false;
  }

  // name = 1, 2 = '=', 3, = data
  if (lines[2] != "=") {
    std::cerr << "equal operator missing!" << std::endl;
    return false;
  }

  vname.append(lines[1]);
  
  std::string& check_str = lines[3];


  // else if (check_str.contains(".")) {
    // float handler
  // }
  //else {
  //  // integer handler
  //  mode = var_mode::i32;
  //  std::any data = std::atoi(lines[3].c_str());
  //  container.set(mode, data);
  //}
  

  return true;
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
