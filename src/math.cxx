#include <stdexcept>
#include <vector>
#include <string>

#include "math.h"
#include "var.h"

namespace math {

std::vector<std::string> commands;
bool breakl = false;

void math_handler(std::vector<std::string>& line) {

  if (line.size() < 4)
    throw std::runtime_error("incorrect size");

  if (line[1] == "cond")
    return cond_handler(line);

  throw std::runtime_error("unimplemented");

  return;
}

void cond_handler(std::vector<std::string>& line) {
  throw std::runtime_error("cond unimplemented");

  return;
}

void cond_runner(std::vector<std::string>& line) {}

void cond_if(std::vector<std::string>& line) {}

void cond_while(std::vector<std::string>& line) {}


}
